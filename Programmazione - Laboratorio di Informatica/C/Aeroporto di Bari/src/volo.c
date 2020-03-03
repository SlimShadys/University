/**
 * @file volo.c
 *
 * Questo file contiene le implementazioni dei prototipi
 * dichiarati nel file volo.h
 * @version 1
 * @date 13/05/2019
 * @authors Gianmarco Scarano
 */

/// Librerie necessarie per il corretto funzionamento del programma.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "volo.h"
#include "menu.h"
#include "controlli.h"

/**
 * Acquisisce l'ultimo numero ID tra tutti i voli, posizionandosi all'ultima
 * posizione e immagazzinando in una variabile il suddetto ID.
 *
 * @pre La funzione, per funzionare correttamente, ha bisogno che il file dei
 * 		voli sia correttamente caricato nel sistema.
 * @post L'intero restituito sarà "ID", nel caso in cui il file esista.
 * 		 Verrà restituito 0 se non ci sono voli, oppure se il file non esiste.
 */
int ID_Volo() {

	/**
	 * Struct del volo
	 */
	volo elenco;

	/**
	 * File dei voli inizializzato a NULL
	 */
	FILE *voli = NULL;

	if( (voli = fopen("voli.dat", "rb") ) == NULL) {
		printf("Errore nell'apertura.");
		return 0;
	}
	else {

		///All'inizio l'ID del volo sarà pari a 0.
		int id = 0;

		///Tramite fseek(), mi sposto all'ultimo rigo del file,
		/// attraverso SEEK_END. Poi, aggiungendo -1 all'offset,
		/// sono in grado di posizionarmi all'ultimo volo del file.
		fseek(voli, (-1)*sizeof(volo), SEEK_END);
		fread(&elenco, sizeof(volo), 1, voli);

		///Leggendo il volo, copio l'ultimo ID nella variabile "id"
		id = elenco.id;

		///Se l'ultimo ID è <= 0 (significa che l'ultimo volo è stato cancellato)
		/// allora, prendo l'ID del penultimo volo.
		if (elenco.id <= 0) {
			voli = fopen("voli.dat", "rb");

			///Mi sposto al penultimo volo
			fseek(voli, (-2)*sizeof(volo), SEEK_END);
			fread(&elenco, sizeof(volo), 1, voli);

			///Riassegno il penultimo ID nella variabile "id"
			id = elenco.id+1;

			fclose(voli);
		}
		fclose(voli);

		///Alla funzione, ritorno l'intero (ID) trovato.
		return id;
	}
}

/**
 * La seguente funzione, permette di resettare la struct volo
 * prima di inserire un nuovo volo. In questo modo evito indesiderate
 * memorizzazioni precedenti.
 *
 * @pre La funzione, per funzionare correttamente, ha bisogno che la struct
 * 		volo sia correttamente visibile nel file
 * @post Sarà restituita una struct volo pari a 0.
 */
void resetVolo(volo *elenco1) {
	memset(elenco1, 0, sizeof(*elenco1)); ///Resetto a 0 tutti i membri della struct volo.
}

/**
 * La seguente funzione, permette di caricare sul file un nuovo volo.
 * Chiede tutti i relativi campi del volo stesso, effettua controlli
 * e alla fine scrive su file.
 * La funzione ha codice F04
 *
 * @pre La funzione, per funzionare correttamente, ha bisogno che il file dei
 * 		voli sia correttamente caricato nel sistema.
 * @post Le informazioni del volo immesso saranno scritte sul file.
 */
int inputVoli(FILE *voli) {

	if( (voli = fopen("voli.dat", "rb+") ) == NULL) {
		printf("Errore nell'apertura.");
		fclose(voli);
		return 0;
	}
	else {

		/**
		 * Struct del volo
		 */
		volo elenco;

		/**
		 * Variabile che mi farà uscire dai cicli
		 */
		int correct = 0;

		/**
		 * Variabile su cui copierò il valore dell'ultimo volo presente nel sistema
		 * e successivamente lo assegnerò al volo che si intende aggiungere,
		 * ovviamente incrementandolo di 1. (id+1)
		 */
		int id = 0;

		voli = fopen("voli.dat","ab+");

		///Ricavo l'ID dell'ultimo volo
		id = ID_Volo();

		///Mi posiziono all'ultima riga del file
		fseek(voli, sizeof(volo), SEEK_END);

		///Resetto la struct del volo, prima di immettere dati
		resetVolo(&elenco);

		printf("\n\n---- V O L O    N U M E R O    %d ----\n", id+1);

		///Finchè correct è diverso da 1, ciclo
		while (correct != 1) {

			/**
			 * Dichiaro un vettore temporaneo per il codice volo
			 */
			char codice_volo_temp[MAX_CODICE_VOLO+1];

			printf("\nCodice del volo: ");
			scanf("%s", codice_volo_temp);

			/// La funzione ControlloCodiceVolo(), restituisce 1 o 0.
			/// Se è 1 (significa che il codice volo è stato inserito correttamente)
			/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
			correct = ControlloCodiceVolo(codice_volo_temp, MAX_CODICE_VOLO, 1);

			///Le prime due lettere del codice devono essere maiuscole
			/// Es. FR8252
			codice_volo_temp[0] = toupper(codice_volo_temp[0]);
			codice_volo_temp[1] = toupper(codice_volo_temp[1]);

			///Copio il codice volo dal vettore temporaneo alla struct
			strcpy(elenco.codice_volo, codice_volo_temp);
		}

		correct = 0;

		while (correct != 1) {
			printf("Nome compagnia del volo: ");
			scanf("%s", elenco.nomecompagnia);

			/// La funzione ControlloNomeCompagnia(), restituisce 1 o 0.
			/// Se è 1 (significa che il nome della compagnia è stato inserito correttamente)
			/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
			correct = ControlloNomeCompagnia(elenco);

			///La prima lettera deve essere maiuscola.
			/// Es. (ryanair => Ryanair)
			elenco.nomecompagnia[0] = toupper(elenco.nomecompagnia[0]);

			///Faccio diventare minuscole le restanti lettere, a partire dalla posizione 1.
			/// Es. (RyaNAIr => Ryanair)
			for (int i = 1; i < MAX_NOME_COMPAGNIA+1; i++) {
				elenco.nomecompagnia[i] = tolower(elenco.nomecompagnia[i]);
			}

		}

		correct = 0;

		while (correct != 1) {
			printf("Aeroporto di partenza del volo: ");
			scanf("%s", elenco.tratta_partenza);

			/// La funzione ControlloTrattaPartenza(), restituisce 1 o 0.
			/// Se è 1 (significa che la tratta di partenza è stata inserita correttamente)
			/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
			correct = ControlloTrattaPartenza(elenco);

			///La prima lettera deve essere maiuscola.
			/// Es. (bari => Bari)
			elenco.tratta_partenza[0] = toupper(elenco.tratta_partenza[0]);

			///Faccio diventare minuscole le restanti lettere, a partire dalla posizione 1.
			/// Es. (BaRI => Bari)
			for (int i = 1; i < MAX_TRATTA_PARTENZA+1; i++) {
				elenco.tratta_partenza[i] = tolower(elenco.tratta_partenza[i]);
			}

		}

		correct = 0;

		while (correct != 1) {
			printf("Aeroporto di arrivo del volo: ");
			scanf("%s", elenco.tratta_arrivo);

			/// La funzione ControlloTrattaArrivo(), restituisce 1 o 0.
			/// Se è 1 (significa che la tratta di arrivo è stata inserita correttamente)
			/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
			correct = ControlloTrattaArrivo(elenco);

			///La prima lettera deve essere maiuscola.
			/// Es. (londra => Londra)
			elenco.tratta_arrivo[0] = toupper(elenco.tratta_arrivo[0]);

			///Faccio diventare minuscole le restanti lettere, a partire dalla posizione 1.
			/// Es. (LonDRa => Londra)
			for (int i = 1; i < MAX_TRATTA_ARRIVO+1; i++) {
				elenco.tratta_arrivo[i] = tolower(elenco.tratta_arrivo[i]);
			}
		}

		correct = 0;

		while (correct != 1) {
			fflush(stdin); ///Svuoto eventuale buffer
			printf("Modello aereo del volo: ");

			///Uso la fgets per poter memorizzare al massimo due nomi.
			/// Es. (Boeing 747).
			fgets(elenco.modello_aereo, MAX_MODELLO_AEREO, stdin);

			/// La funzione ControlloModelloAereo(), restituisce 1 o 0.
			/// Se è 1 (significa che il modello dell'aereo è stato inserito correttamente)
			/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
			correct = ControlloModelloAereo(elenco);

			///La prima lettera deve essere maiuscola.
			/// Es. (boeing => Boeing)
			elenco.modello_aereo[0] = toupper(elenco.modello_aereo[0]);

			///Faccio diventare minuscole le restanti lettere, a partire dalla posizione 1.
			/// Es. (BoEING => Boeing)
			for (int i = 1; i < MAX_MODELLO_AEREO+1; i++) {
				elenco.modello_aereo[i] = tolower(elenco.modello_aereo[i]);
			}

			///La fgets è conosciuta per inserire un carattere newline alla fine del vettore.
			/// Tramite questo algoritmo, controllo se alla fine del vettore stesso, è stato
			/// inserito un carattere newline (\n). Se sì, lo faccio diventare un
			/// carattere nullo (\0).
			if ((elenco.modello_aereo[0] != '\0') && (elenco.modello_aereo[strlen(elenco.modello_aereo) -1] == '\n')) {
				elenco.modello_aereo[strlen(elenco.modello_aereo) -1] = '\0';
			}
		}

		correct = 0;

		while (correct != 1) {
			printf("Mese del volo: ");
			scanf("%s", elenco.datadivolo.mese);

			/// La funzione ControlloMese(), restituisce 1 o 0.
			/// Se è 1 (significa che il mese del volo è stato inserito correttamente)
			/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
			correct = ControlloMese(elenco);
		}

		correct = 0;

		while (correct != 1) {
			printf("Giorno del volo: ");
			scanf("%s", elenco.datadivolo.giorno);

			/// La funzione ControlloGiorno(), restituisce 1 o 0.
			/// Se è 1 (significa che il giorno del volo è stato inserito correttamente)
			/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
			correct = ControlloGiorno(elenco);
		}

		correct = 0;

		while (correct != 1) {
			printf("Anno del volo: ");
			scanf("%s", elenco.datadivolo.anno);

			/// La funzione ControlloAnno(), restituisce 1 o 0.
			/// Se è 1 (significa che l'anno del volo è stato inserito correttamente)
			/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
			correct = ControlloAnno(elenco);
		}

		correct = 0;

		while (correct != 1) {
			printf("Ora e minuti della partenza del volo (separati da spazio): ");
			scanf("%s%s", elenco.ora_partenza, elenco.minuti_partenza);

			/// La funzione ControlloOrarioPartenza(), restituisce 1 o 0.
			/// Se è 1 (significa che l'orario di partenza è stato inserito correttamente)
			/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
			correct = ControlloOrarioPartenza(elenco);
		}

		correct = 0;

		while (correct != 1) {
			printf("Ora e minuti dell'arrivo del volo (separati da spazio): ");
			scanf("%s%s", elenco.ora_arrivo, elenco.minuti_arrivo);

			/// La funzione ControlloOrarioArrivo(), restituisce 1 o 0.
			/// Se è 1 (significa che l'orario di arrivo è stato inserito correttamente)
			/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
			correct = ControlloOrarioArrivo(elenco);
		}

		correct = 0;

		while (correct != 1) {
			printf("Durata del volo (in minuti): ");
			scanf("%s", elenco.durata);

			/// La funzione ControlloDurata(), restituisce 1 o 0.
			/// Se è 1 (significa che la durata del volo sia stata inserita correttamente)
			/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
			correct = ControlloDurata(elenco);
		}

		///Aumento "id" (il quale contiene l'ID dell'ultimo volo) di 1 e lo assegno al volo
		/// che sto per registrare
		elenco.id = id+1;

		///All'inizio, il volo è aperto per il check-in
		elenco.chiusura_checkin = 0;

		///Scrivo su file e successivamente lo chiudo
		fwrite(&elenco, 1, sizeof(volo), voli);

		fclose(voli); ///Chiudo per prima, la prima apertura del file
		fclose(voli); ///Chiudo la seconda apertura del file

		return 1;
	}
}

/**
 * La seguente funzione, permette di leggere da file TUTTI i voli presenti.
 * Infine chiede all'utente se vuole tornare al menù precedente o uscire
 * dal programma.
 *
 * @pre La funzione, per funzionare correttamente, ha bisogno che il file dei
 * 		voli sia correttamente caricato nel sistema.
 * @post Le informazioni dei voli presenti saranno stampate.
 */
int letturaVoli(FILE *voli) {

	/**
	 * Variabile contatore
	 */
	unsigned short int p = 0;

	/**
	 * Variabile che mi permette di
	 * leggere tutto il file
	 */
	int read = 1;

	/**
	 * Variabile che mi permette di sapere quante
	 * prenotazioni ci sono nel sistema.
	 */
	int found = 0;

	/**
	 * Variabile che mi permette di sapere se l'occorrenza
	 * richiesta è stata trovata o meno.
	 */
	int notfound = 0;

	/**
	 * Struct volo
	 */
	volo elenco;

	/**
	 * Variabile che conterrà la scelta dell'utente per il menù
	 */
	unsigned short int sceltautente = 0;

	if( (voli = fopen("voli.dat", "rb") ) == NULL) {
		printf("Errore nell'apertura.");
		return 0;
	}
	else {

		///Leggo fino alla fine del file
		while( !(feof(voli)))
		{
			///Quando read è pari a 0, il file è finito
			int read = fread(&elenco, sizeof(volo), 1, voli);

			if ( read > 0) {
				///Se il codice del volo e il nome della compagnia sono diversi
				/// dal carattere nullo, allora stampa il volo
				if (elenco.codice_volo[0] != '\0' && elenco.nomecompagnia[0] != '\0') {
					printf("\n\n---- V O L O    N U M E R O    %d ----\n", elenco.id);
					printf("\nCodice volo: %s", elenco.codice_volo);
					printf("\nNome compagnia: %s", elenco.nomecompagnia);
					printf("\nAeroporto di partenza : %s", elenco.tratta_partenza);
					printf("\nAeroporto di arrivo : %s", elenco.tratta_arrivo);
					printf("\nModello aereo: %s", elenco.modello_aereo);
					printf("\nData del volo: %2s-%2s-%4s", elenco.datadivolo.giorno, elenco.datadivolo.mese, elenco.datadivolo.anno);
					printf("\nPartenza: %s:%s", elenco.ora_partenza, elenco.minuti_partenza);
					printf("\nArrivo: %s:%s", elenco.ora_arrivo, elenco.minuti_arrivo);
					printf("\nDurata del volo: %s min.", elenco.durata);
					printf("\nCheck-in chiuso: %d", elenco.chiusura_checkin);
					/*for (int i = 0; i < MAX_POSTI; i++) {
						printf("\nVettore numero %d -> %d",i,elenco.posti[i]);
						//Decommenta per verificare l'effettiva aggiunta di un posto.
						//Ricorda il posto e verrà stampato,
						//Vettore numero "posto" -> 1
					}*/
				}
			}

		}

	}

	///Chiudo i voli
	fclose(voli);

	///Apro il file in sola lettura.
	voli = fopen("voli.dat", "rb");

	///Leggi il file finchè read non arriva a 0.
	while( read != 0)
	{
		/// Quando read arriva a 0, significa che il file è finito.
		read = fread(&elenco, sizeof(volo), 1, voli);

		if ( read > 0) {
			///Per verificare se un utente ha una prenotazione disponibile, controllo se
			/// l'orario di arrivo (Es. 18), precedentemente convertito in intero,
			/// è minore di MAX_ORA_VOLO (23). Verifico la stessa cosa per l'orario di partenza.
			/// Se le due condizioni combaciano, allora significa che nel vettore p[num], esiste una prenotazione,
			/// quindi la stampo.
			if (elenco.codice_volo[0] == '\0') {
				///Aumento il contatore delle prenotazioni
				notfound++;
			}
			else {
				found++;
			}
		}
	}

	///Chiudo il file
	fclose(voli);

	printf("\n\nCi sono %d voli presenti del sistema. %d sono stati cancellati dal sistema.\n", found, notfound);

	///Inizializzo i vettori usati per la ricerca e tutte le altre variabili
	/// per una eventuale nuova ricerca.
	found = 0;
	notfound = 0;
	read = 1;

	///Finchè p è diverso da 1, ciclo.
	while (p != 1) {
		printf("\n\nTornare al menu' o chiudere il programma?");
		printf("\n1) Torna al menu'");
		printf("\n2) Chiudi il programma");
		printf("\nLA TUA SCELTA: ");
		scanf("%hu", &sceltautente); ///Immagazzino la scelta dell'utente nella variabile sceltautente.

		///Programmazione difensiva che cattura i caratteri, nel caso in cui l'utente
		/// abbia immesso dei caratteri invece dei numeri.
		/// Converto i caratteri in numeri e li faccio ricadere nel "default" della switch,
		/// stampando un messaggio d'errore.
		if (p != getchar()) {
		}

		if (sceltautente == 1) {
			p = 1; ///Esco dal while e quindi la funzione termina.
			 	   ///Terminata la funzione, mi ritrovo al menù
			return 1;
		}

		if (sceltautente == 2) {
			exit(0); ///Esco completamente dal programma
			return 1;
		}
	}
	return 1;
}

/**
 * La seguente funzione, permette di modificare da file i voli presenti.
 * Tramite un menù interattivo, chiede all'utente quale volo e quali campi
 * del volo intende modificare e si comporta a dovere.
 * La funzione ha codice F05.
 *
 * @pre La funzione, per funzionare correttamente, ha bisogno che il file dei
 * 		voli sia correttamente caricato nel sistema.
 * @post Le modifiche dei voli verranno successivamente salvate sul file.
 */
int modificaVoli(FILE *voli) {

	/**
	 * Struct del volo
	 */
	volo elenco;

	/**
	 * Inizializzo il file dei voli a NULL
	 */
	voli = NULL;

	/**
	 * Variabile che userò per immagazzinare l'ID
	 * dell'utente da modificare.
	 */
	char idvolo[2] = "\0";

	/**
	 * Variabile che userò per convertire l'ID dell'utente
	 * da char a int.
	 */
	int id_volo = 0;

	/**
	 * Variabile contatore
	 */
	int correct = 0;

	/**
	 * Variabile contatore
	 */
	int correct2 = 0;

	/**
	 * Contatore che mi permette di ritornare al menu
	 * una volta arrivato a 0.
	 */
	int wrong = 3;

	/**
	 * Variabile che conterrà l'ID del volo da eliminare
	 */
	int id_volo_eliminato = 0;

	/**
	 * Contatore che mi permetterà di uscire dal ciclo while.
	 */
	unsigned short int s = 0;

	/**
	 * Variabile che conterrà la scelta dell'utente durante
	 * la visualizzazione del menù.
	 */
	unsigned short int scelta_utente = 0;

	/**
	 * Vettore su cui memorizzare la tratta di partenza
	 * che l'utente immette al momento della modifica.
	 */
	char partenza_temporanea[MAX_TRATTA_PARTENZA+1];

	/**
	 * Vettore su cui memorizzare la tratta di arrivo
	 * che l'utente immette al momento della modifica.
	 */
	char arrivo_temporaneo[MAX_TRATTA_ARRIVO+1];

	/**
	 * Vettore su cui memorizzare il nome compagnia
	 * che l'utente immette al momento della modifica.
	 */
	char nome_compagnia_temporaneo[MAX_NOME_COMPAGNIA+1];

	///Finchè correct è diverso da 1, ciclo
	while (correct != 1) {
		if( (voli = fopen("voli.dat", "rb+") ) == NULL) {
			printf("Errore nell'apertura.");
			return 0;
			correct = 1;
		}
		else
		{
			///Finchè correct2 è diverso da 1, ciclo
			while (correct2 != 1) {
				printf("\nDi quale volo vuoi cambiare le informazioni?");
				printf("\nID VOLO: ");
				scanf("%s", idvolo);

				///Trasformo in intero l'ID immesso precedentemente
				id_volo = atoi(idvolo);

				///Tramite fseek(), mi muovo al volo richiesto dall'utente, con il giusto offset.
				fseek(voli, (id_volo-1)*sizeof(volo), SEEK_SET);
				fread(&elenco, sizeof(volo), 1, voli);

				///Stampo il volo solo se il codice del volo è diverso dal carattere nullo
				/// e se l'utente ha messo un ID diverso da 0.
				if (elenco.codice_volo[0] != '\0' && id_volo != 0)
				{
					printf("\n------ Hai scelto questo volo ! ------");
					printf("\n\n---- V O L O    N U M E R O    %d ----\n", elenco.id);
					printf("\nCodice volo: %s", elenco.codice_volo);
					printf("\nNome compagnia: %s", elenco.nomecompagnia);
					printf("\nAeroporto di partenza : %s", elenco.tratta_partenza);
					printf("\nAeroporto di arrivo : %s", elenco.tratta_arrivo);
					printf("\nModello aereo: %s", elenco.modello_aereo);
					printf("Data del volo: %2s-%2s-%4s", elenco.datadivolo.giorno, elenco.datadivolo.mese, elenco.datadivolo.anno);
					printf("\nPartenza: %s:%s", elenco.ora_partenza, elenco.minuti_partenza);
					printf("\nArrivo: %s:%s", elenco.ora_arrivo, elenco.minuti_arrivo);
					printf("\nDurata del volo: %s min.", elenco.durata);
					printf("\nCheck-in chiuso: %d\n", elenco.chiusura_checkin);
					correct = 1; ///Esco dai due cicli
					correct2 = 1; ///Esco dai due cicli
				}
				///Nell'else ricado, se l'utente mette un ID volo non valido.
				else {
					printf("\nNessun volo trovato con questo ID!");
					wrong--; ///All'inizio wrong sarà uguale a 3.
					///Quando wrong raggiungerà 0, allora mostrerò il menu.
					if (wrong != 0) {
						printf("\nHai ancora %d possibilita', poi sarai rimandato al menu'.\n", wrong);
					}
				}
				if (wrong == 0) {
					mostraMenu();
				}
			}
		}
	}

	fflush(stdin); ///Svuoto eventuale buffer

	correct = 0;

	while (s != 1) {	///Finchè s è uguale a 1, eseguo il loop.
		printf("\n1) Modifica tratta partenza");
		printf("\n2) Modifica tratta arrivo");
		printf("\n3) Modifica nome compagnia");
		printf("\n4) Elimina volo");
		printf("\n5) Leggi le informazioni di questo volo");
		printf("\n6) Visualizza la mappa dei posti per questo volo");
		printf("\n7) Ritorna al menu precedente (menu utente)");
		printf("\n8) Esci dal programma");
		printf("\n-------------------------------------");
		printf("\nLA TUA SCELTA: ");
		scanf("%hu", &scelta_utente); ///Immagazzino la scelta nella variabile scelta_utente.

		///Programmazione difensiva che cattura i caratteri, nel caso in cui l'amministratore
		/// abbia immesso dei caratteri invece dei numeri.
		/// Converto i caratteri in numeri e li faccio ricadere nel "default" della switch,
		/// stampando un messaggio d'errore.
		if (s != getchar()) {
		}

		switch (scelta_utente) { ///Switch per controllare cosa l'utente ha immesso
		case 1:
			voli = fopen("voli.dat", "rb");

			///Tramite fseek(), mi muovo al volo richiesto dall'utente, con il giusto offset.
			fseek(voli, (id_volo-1)*sizeof(volo), SEEK_SET);
			fread(&elenco, sizeof(volo), 1, voli);

			printf("Vecchia tratta partenza: %s\n", elenco.tratta_partenza);
			fclose(voli);

			///Finchè correct è diverso da 1, ciclo.
			while (correct != 1) {
				printf("Immetti la nuova tratta di partenza: ");
				scanf("%s", partenza_temporanea);

				/// La funzione ControlloTrattaPartenzaTemporaneo(), restituisce 1 o 0.
				/// Se è 1 (significa che la tratta di partenza è stata inserita correttamente)
				/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
				correct = ControlloTrattaPartenzaTemporaneo(partenza_temporanea, MAX_TRATTA_PARTENZA);

				///La prima lettera deve essere maiuscola
				/// Es. (bari => Bari)
				partenza_temporanea[0] = toupper(partenza_temporanea[0]);

				///Le restanti lettere devono essere minuscole
				/// Es. (BaRI => Bari)
				for (int i = 1; i < MAX_TRATTA_PARTENZA+1; i++) {
					partenza_temporanea[i] = tolower(partenza_temporanea[i]);
				}
			}

			voli = fopen("voli.dat", "rb+");

			///Tramite fseek(), mi posiziono al volo giusto tramite "id_volo", dopo di che mi muovo nel
			/// giusto membro (elenco.tratta_partenza).
			fseek(voli, (id_volo-1)*sizeof(volo) + (((char *) &elenco.tratta_partenza) - ((char *) &elenco)), SEEK_SET);

			///Copio quello che l'utente ha immesso, nel membro tratta_partenza
			strcpy(elenco.tratta_partenza, partenza_temporanea);

			///Scrivo solamente quel membro e chiudo il file
			fwrite(&elenco.tratta_partenza, sizeof(elenco.tratta_partenza), 1, voli);
			fclose(voli);

			correct = 0;
			break;
		case 2:
			voli = fopen("voli.dat", "rb");

			///Tramite fseek(), mi muovo al volo richiesto dall'utente, con il giusto offset.
			fseek(voli, (id_volo-1)*sizeof(volo), SEEK_SET);
			fread(&elenco, sizeof(volo), 1, voli);

			printf("Vecchia tratta arrivo: %s\n", elenco.tratta_arrivo);
			fclose(voli);

			///Finchè correct è diverso da 1, ciclo.
			while (correct != 1) {
				printf("Immetti la nuova tratta di arrivo: ");
				scanf("%s", arrivo_temporaneo);

				/// La funzione ControlloTrattaArrivoTemporaneo(), restituisce 1 o 0.
				/// Se è 1 (significa che la tratta di arrivo è stata inserita correttamente)
				/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
				correct = ControlloTrattaArrivoTemporaneo(arrivo_temporaneo, MAX_TRATTA_ARRIVO);

				///La prima lettera deve essere maiuscola
				/// Es. (bari => Bari)
				arrivo_temporaneo[0] = toupper(arrivo_temporaneo[0]);

				///Le restanti lettere devono essere minuscole
				/// Es. (BaRI => Bari)
				for (int i = 1; i < MAX_TRATTA_ARRIVO+1; i++) {
					arrivo_temporaneo[i] = tolower(arrivo_temporaneo[i]);
				}
			}

			voli = fopen("voli.dat", "rb+");

			///Tramite fseek(), mi posiziono al volo giusto tramite "id_volo", dopo di che mi muovo nel
			/// giusto membro (elenco.tratta_arrivo).
			fseek(voli, (id_volo-1)*sizeof(volo) + (((char *) &elenco.tratta_arrivo) - ((char *) &elenco)), SEEK_SET);

			///Copio quello che l'utente ha immesso, nel membro tratta_arrivo
			strcpy(elenco.tratta_arrivo, arrivo_temporaneo);

			///Scrivo solamente quel membro e chiudo il file
			fwrite(&elenco.tratta_arrivo, sizeof(elenco.tratta_arrivo), 1, voli);
			fclose(voli);

			correct = 0;
			break;
		case 3:
			voli = fopen("voli.dat", "rb");

			///Tramite fseek(), mi muovo al volo richiesto dall'utente, con il giusto offset.
			fseek(voli, (id_volo-1)*sizeof(volo), SEEK_SET);
			fread(&elenco, sizeof(volo), 1, voli);

			printf("Vecchio nome compagnia: %s\n", elenco.nomecompagnia);
			fclose(voli);

			///Finchè correct è diverso da 1, ciclo
			while (correct != 1) {
				printf("Immetti il nuovo nome compagnia: ");
				scanf("%s", nome_compagnia_temporaneo);

				/// La funzione ControlloNomeCompagniaTemporaneo(), restituisce 1 o 0.
				/// Se è 1 (significa che il nome compagnia è stato inserito correttamente)
				/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
				correct = ControlloNomeCompagniaTemporaneo(nome_compagnia_temporaneo, MAX_NOME_COMPAGNIA);

				///La prima lettera deve essere maiuscola
				/// Es. (ryanair => Ryanair)
				nome_compagnia_temporaneo[0] = toupper(nome_compagnia_temporaneo[0]);

				///Le restanti lettere devono essere minuscole
				/// Es. (RyanAIR => Ryanair)
				for (int i = 1; i < MAX_NOME_COMPAGNIA+1; i++) {
					nome_compagnia_temporaneo[i] = tolower(nome_compagnia_temporaneo[i]);
				}
			}

			voli = fopen("voli.dat", "rb+");

			///Tramite fseek(), mi posiziono al volo giusto tramite "id_volo", dopo di che mi muovo nel
			/// giusto membro (elenco.nomecompagnia).
			fseek(voli, (id_volo-1)*sizeof(volo) + (((char *) &elenco.nomecompagnia) - ((char *) &elenco)), SEEK_SET);

			///Copio quello che l'utente ha immesso, nel membro nomecompagnia
			strcpy(elenco.nomecompagnia, nome_compagnia_temporaneo);

			///Scrivo solamente quel membro e chiudo il file
			fwrite(&elenco.nomecompagnia, sizeof(elenco.nomecompagnia), 1, voli);
			fclose(voli);

			correct = 0;
			break;
		case 4:

			///Funzione F05a

			voli = fopen("voli.dat", "rb+");

			///Tramite fseek(), mi muovo al volo richiesto dall'utente, con il giusto offset.
			fseek(voli, (id_volo-1)*sizeof(volo), SEEK_SET);
			fread(&elenco, sizeof(volo), 1, voli);

			///Immagazzino l'ID di questo volo in una variabile,
			/// per poi stamparla successivamente
			id_volo_eliminato = elenco.id;
			fclose(voli);

			voli = fopen("voli.dat", "rb+");
			///Faccio la stessa operazione di prima tramite fseek().
			/// La rifaccio poichè nel caso in cui non la facessi,
			/// e lasciassi l'fseek() precedente, l'algoritmo
			/// non prende il giusto volo per un motivo strano.
			fseek(voli, (id_volo-1)*sizeof(volo), SEEK_SET);

			///Resetto tutta la stuct del volo
			memset(&elenco, 0, sizeof(elenco));
			printf("\nIl volo numero %d e' stato cancellato con successo!\n", id_volo_eliminato);

			///Aggiorno il file scrivendo una struct azzerata e chiudo il file
			fwrite(&elenco, sizeof(volo), 1, voli);
			fclose(voli);
			break;
		case 5:
			voli = fopen("voli.dat", "rb");
			///Tramite fseek(), mi muovo al volo richiesto dall'utente, con il giusto offset.
			fseek(voli, (id_volo-1)*sizeof(volo), SEEK_SET);
			fread(&elenco, sizeof(volo), 1, voli);

			///Effettuo una semplice stampa del volo
			printf("\n\n---- V O L O    N U M E R O    %d ----\n", elenco.id);
			printf("\nCodice volo: %s", elenco.codice_volo);
			printf("\nNome compagnia: %s", elenco.nomecompagnia);
			printf("\nAeroporto di partenza : %s", elenco.tratta_partenza);
			printf("\nAeroporto di arrivo : %s", elenco.tratta_arrivo);
			printf("\nModello aereo: %s", elenco.modello_aereo);
			printf("Data del volo: %2s-%2s-%4s", elenco.datadivolo.giorno, elenco.datadivolo.mese, elenco.datadivolo.anno);
			printf("\nPartenza: %s:%s", elenco.ora_partenza, elenco.minuti_partenza);
			printf("\nArrivo: %s:%s", elenco.ora_arrivo, elenco.minuti_arrivo);
			printf("\nDurata del volo: %s min.", elenco.durata);
			printf("\nCheck-in chiuso: %d\n", elenco.chiusura_checkin);

			fclose(voli);
			break;
		case 6:
			voli = fopen("voli.dat", "rb");
			///Tramite fseek(), mi muovo al volo richiesto dall'utente, con il giusto offset.
			fseek(voli, (id_volo-1)*sizeof(volo), SEEK_SET);
			fread(&elenco, sizeof(volo), 1, voli);

			///Effettuo una stampa dei posti
			printf("\n P P P P P P P P P P P P P  P P P P P P P P P P P P\n O O O O O O O O O O O O O  O O O O O O O O O O O O\n "
					"S S S S S S S S S S S S S  S S S S S S S S S S S S\n T T T T T T T T T"
					" T T T T  T T T T T T T T T T T T\n I I I I I I I I I I I I I  I I I I I I I I I I I"
					" I\n\n 1 7 1 1 2 3 3 4 4 5 6 6 7  7 8 9 9 1 1 1 1 1 1 1 1\n | | 3 9 5 1 7 3 9 5 1 7 3"
					"  9 5 1 7 0 0 1 2 2 3 3 4\n 6 1 | | | | | | | | | | |  | | | | 3 9 5 1 7 3 9 5\n   2 1 2"
					" 3 3 4 4 5 6 6 7 7  8 9 9 1 | | | | | | | |\n     8 4 0 6 2 8 4 0 6 2 8  4 0 6 0 1 1 1 1"
					" 1 1 1 1\n\t\t\t\t  2 0 1 2 2 3 3 4 5\n\t\t\t\t    8 4 0 6 2 8 4 0");
			printf("\n ___________________________________________________");
			for (int i = 0; i < 24; i++) {
				if (i == 0) {
					printf("\n|%d", elenco.posti[0+i]);
				}
				if (i == 11) {
					printf(" ");
				}
				if (i == 23) {
					printf(" %d|", elenco.posti[0+i]);
				}
				else {
				printf(" %d", elenco.posti[0+i]);
				}
			}
			for (int i = 0; i < 24; i++) {
				if (i == 0) {
					printf("\n|%d", elenco.posti[1+i]);
				}
				if (i == 11) {
					printf(" ");
				}
				if (i == 23) {
					printf(" %d|", elenco.posti[1+i]);
				}
				else {
				printf(" %d", elenco.posti[1+i]);
				}
			}
			for (int i = 0; i < 24; i++) {
				if (i == 0) {
					printf("\n|%d", elenco.posti[2+i]);
				}
				if (i == 11) {
					printf(" ");
				}
				if (i == 23) {
					printf(" %d|", elenco.posti[2+i]);
				}
				else {
				printf(" %d", elenco.posti[2+i]);
				}
			}
			printf("\n\t\t\t\t\t\t   |");
			for (int i = 0; i < 24; i++) {
				if (i == 0) {
					printf("\n|%d", elenco.posti[3+i]);
				}
				if (i == 11) {
					printf(" ");
				}
				if (i == 23) {
					printf(" %d|", elenco.posti[3+i]);
				}
				else {
				printf(" %d", elenco.posti[3+i]);
				}
			}
			for (int i = 0; i < 24; i++) {
				if (i == 0) {
					printf("\n|%d", elenco.posti[4+i]);
				}
				if (i == 11) {
					printf(" ");
				}
				if (i == 23) {
					printf(" %d|", elenco.posti[4+i]);
				}
				else {
				printf(" %d", elenco.posti[4+i]);
				}
			}
			for (int i = 0; i < 24; i++) {
				if (i == 0) {
					printf("\n|%d", elenco.posti[5+i]);
				}
				if (i == 11) {
					printf(" ");
				}
				if (i == 23) {
					printf(" %d|", elenco.posti[5+i]);
				}
				else {
				printf(" %d", elenco.posti[5+i]);
				}
			}
			printf("\n|__________________________________________________|\n");

			fclose(voli);
			break;
		case 7:
			///Chiamata alla funzione che mi porta al menu precedente (menu utente).
			mostraMenu();
			break;
		case 8: ///Rendo vero il valore della while e termino il programma con exit(0).
			s = 1;
			exit(0);
			break;
		default: ///Qui ricadranno tutti i valori non corretti. (caratteri e num > 9).
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
			printf("\nValore non corretto.");
			break;
		}
	}
	fclose(voli);
	return 1;
}

/**
 * La funzione chiede un codice volo all'amministratore e verifica se quel codice volo
 * è inserito nel sistema o meno. Se esiste, procede con la stampa dell'volo per quel codice,
 * altrimenti mostra all'amministratore un messaggio di errore.
 * La funzione ha codice F11
 *
 * @pre La funzione richiede che il file dei voli, esista.
 *
 * @post La funzione mostra il volo per quel codice immesso o può mostrare un
 * 		 messaggio di errore se il file o il volo non esiste.
 */
int ricercaVoli (FILE *voli) {

	/**
	 * Struct volo
	 */
	volo elenco;

	/**
	 * Variabile contatore che mi permetterà di uscire
	 * dai cicli se il dato richiesto è giusto.
	 */
	int correct = 0;

	/**
	 * Variabile che mi permette la lettura del file.
	 * Quando read = 0, allora la lettura è finita.
	 */
	int read = 1;

	/**
	 * Variabile che servirà a dire se il codice di prenotazione
	 * esiste.
	 */
	int found = 0;

	/**
	 * Dichiaro un vettore temporaneo per il passaporto
	 */
	char codice_volo_temp[MAX_CODICE_VOLO+1];

	printf("\nLa ricerca di una volo consiste nell'immettere un codice volo");
	printf("\ne l'algoritmo restituira', se esiste, il relativo volo per quel codice.\n");

	///Finchè correct è diverso da 1, ciclo
	while (correct != 1) {

		printf("\n---- Immettere codice prenotazione volo ----\n");
		printf("\nCodice del volo: ");
		scanf("%s", codice_volo_temp);

		/// La funzione ControlloCodiceVolo(), restituisce 1 o 0.
		/// Se è 1 (significa che il codice volo è stato inserito correttamente)
		/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
		correct = ControlloCodiceVolo(codice_volo_temp, MAX_CODICE_VOLO, 0);

		///Le prime due lettere del codice devono essere maiuscole
		/// Es. FR8252
		codice_volo_temp[0] = toupper(codice_volo_temp[0]);
		codice_volo_temp[1] = toupper(codice_volo_temp[1]);
	}

	if( (voli = fopen("voli.dat", "rb") ) == NULL) {
		printf("Errore nell'apertura.");
		return 0; ///Ritorno 0 se il file non esiste.
	}
	else {

		///Leggi il file finchè read non arriva a 0.
		while( read != 0)
		{
			///Quando read è pari a 0, il file è finito
			read = fread(&elenco, sizeof(volo), 1, voli);

			if ( read > 0) {
				///Scorro tutto il vettore delle prenotazioni per ogni utente presente nel sistema.
				/// Se il codice immesso dall'amministratore, coincide con uno presente nel vettore delle
				/// prenotazioni, allora stampo l'utente relativo a quella prenotazione.
				if(!strcmp(codice_volo_temp,elenco.codice_volo)) {
					printf("\n\n---- V O L O    N U M E R O    %d ----\n", elenco.id);
					printf("\nCodice volo: %s", elenco.codice_volo);
					printf("\nNome compagnia: %s", elenco.nomecompagnia);
					printf("\nAeroporto di partenza : %s", elenco.tratta_partenza);
					printf("\nAeroporto di arrivo : %s", elenco.tratta_arrivo);
					printf("\nModello aereo: %s", elenco.modello_aereo);
					printf("\nData del volo: %2s-%2s-%4s", elenco.datadivolo.giorno, elenco.datadivolo.mese, elenco.datadivolo.anno);
					printf("\nPartenza: %s:%s", elenco.ora_partenza, elenco.minuti_partenza);
					printf("\nArrivo: %s:%s", elenco.ora_arrivo, elenco.minuti_arrivo);
					printf("\nDurata del volo: %s min.", elenco.durata);
					printf("\nCheck-in chiuso: %d", elenco.chiusura_checkin);
					found++; ///Aumento il contatore delle prenotazioni trovate
					return 1;
				}
			}
		}

		fclose(voli);
	}

	///Entro nella if solo se non ha trovato nessuna prenotazione
	if (found == 0) {
		return 0;
	}

	return 1;
}

/**
 * La funzione, tramite un algoritmo di ordinamento,
 * ordina per codice volo, tutti i voli registrati
 * nel sistema.
 * La funzione ha codice F15.
 *
 * @param voli File dei voli
 */
int ordinamentoVoli(FILE *voli) {

	///Se il file non esiste, stampa un messaggio di errore.
	if( (voli = fopen("voli.dat", "rb+") ) == NULL) {
		printf("Errore nell'apertura.");
		return 0;
	}
	else {

		/**
		 * Numero di voli presenti nel sistema
		 */
		int numero_voli = 0;

		/**
		 * Struct volo
		 */
		volo elenco;

		///Conto quanti voli ci sono nel file, per poter allocare la memoria giusta.
		voli = fopen("voli.dat", "ab+");

		fseek(voli, (-1)*sizeof(volo), SEEK_END);
		fread(&elenco, sizeof(volo), 1, voli);

		///Salvo l'ultimo ID dell'ultimo volo in una variabile, per poi poter allocare la memoria giusta
		numero_voli = elenco.id;

		fclose(voli);

		///Sorting
		voli = fopen("voli.dat", "rb");

		///Funzione compare2(). Consulta la documentazione.
		int compare2(const void *a, const void *b) {
		    return strncmp((const char *)a, (const char *)b, 20);
		}

		/**
		 * Vettore dinamico dei voli.
		 * E' grande tanto quanti sono i voli
		 */
		volo *listaelenco = malloc(numero_voli * sizeof *listaelenco);

		fread(listaelenco , sizeof *listaelenco , numero_voli, voli);

		///Funzione qsort(). Mi ordina il vettore precedentemente dichiarato
		/// per codice volo, in ordine alfabetico.
		qsort(listaelenco, numero_voli, sizeof(volo), compare2);

		fclose(voli);
		///Fine Sorting

		///Stampa i voli ordinati
		for (int i = 0; i < numero_voli; i++) {
			if (listaelenco[i].codice_volo[0] != '\0') {
			printf("\n\nCODICE VOLO ------> %s", listaelenco[i].codice_volo);
			printf("\n\tNome compagnia: %s", listaelenco[i].nomecompagnia);
			printf("\n\tAeroporto di partenza: %s", listaelenco[i].tratta_partenza);
			printf("\n\tAeroporto di arrivo: %s", listaelenco[i].tratta_arrivo);
			printf("\n\tData del volo: %2s-%2s-%4s", listaelenco[i].datadivolo.giorno, listaelenco[i].datadivolo.mese, listaelenco[i].datadivolo.anno);
			printf("\n\tPartenza -> %s:%s", listaelenco[i].ora_partenza, listaelenco[i].minuti_partenza);
			printf("\n\tArrivo   -> %s:%s", listaelenco[i].ora_arrivo, listaelenco[i].minuti_arrivo);
			}
		}
		return 1;
	}
}

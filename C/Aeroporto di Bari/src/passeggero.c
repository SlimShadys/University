/**
 * @file passeggero.c
 *
 * Questo file contiene le implementazioni dei prototipi
 * dichiarati nel file controlli.h
 * @version 1
 * @date 13/05/2019
 * @authors Gianmarco Scarano
 */

/// Includo le librerie necessarie per il corretto funzionamento del programma
#include "passeggero.h"
#include "controlli.h"
#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Acquisisce l'ultimo numero ID tra tutti gli utenti, posizionandosi all'ultima
 * posizione e immagazzinando in una variabile il suddetto ID.
 *
 * @pre La funzione, per funzionare correttamente, ha bisogno che il file dei
 * 		passeggeri sia correttamente caricato nel sistema.
 * @post L'intero restituito sarà "ID", nel caso in cui il file esista.
 * 		 Verrà restituito 0 se non ci sono utenti, oppure se il file non esiste.
 */
int ID_Utente() {

	/**
	 * Struct per gli utenti, da cui prendere l'ID
	 */
	passeggero utenti;

	/**
	 * Dichiarazione del file da cui pescare l'ultimo utente
	 */
	FILE *passeggeri = NULL;

	///Se il file non esiste, restituisci 0.
	if( (passeggeri = fopen("passeggeri.dat", "rb") ) == NULL) {
		printf("Errore nell'apertura del file.");
		return 0;
	}
	else {

		/**
		 * Variabile che conterrà l'ID
		 */
		int id = 0;

		///Mi posiziono all'ultima riga del file tramite SEEK_END,
		/// ma, volendo l'ultimo utente, lo leggo attraverso l'offset
		/// giusto "(-1)*sizeof(passeggero)"
		fseek(passeggeri, (-1)*sizeof(passeggero), SEEK_END);
		fread(&utenti, sizeof(passeggero), 1, passeggeri);

		///Immagazzino l'ID dell'utente trovato in ultima posizione
		/// nella variabile "id".
		id = utenti.id;

		///Se l'ultimo ID è <= 0 (significa che l'ultimo utente è stato cancellato)
		/// allora, prendo l'ID del penultimo utente.
		if (utenti.id <= 0) {
			passeggeri = fopen("passeggeri.dat", "rb");

			///Mi sposto al penultimo utente
			fseek(passeggeri, (-2)*sizeof(passeggero), SEEK_END);
			fread(&utenti, sizeof(passeggero), 1, passeggeri);

			///Riassegno il penultimo ID nella variabile "id"
			id = utenti.id;

			fclose(passeggeri);
		}

		///Chiudo il file dei passeggeri
		fclose(passeggeri);

		///Ritorno alla funzione l'ID dell'utente trovato.
		return id;
	}
	return 0; ///Ritorno 0 alla funzione se il file non è stato trovato.
}

/**
 * La seguente funzione, permette di resettare la struct passeggero
 * prima di inserire un nuovo utente. In questo modo evito indesiderate
 * memorizzazioni precedenti.
 *
 * @pre La funzione, per funzionare correttamente, ha bisogno che la struct
 * 		passeggero sia correttamente visibile nel file
 * @post Sarà restituita una struct passeggero pari a 0.
 */
void resetUtente(passeggero *utenti1) {
	memset(utenti1, 0, sizeof(*utenti1)); ///Resetto a 0 tutti i membri della struct passeggero.
}

/**
 * La seguente funzione, permette di caricare sul file un nuovo passeggero.
 * Chiede tutti i relativi campi del passeggeri stesso, effettua controlli
 * e alla fine scrive su file.
 * La funzione ha codice F02.
 *
 * @pre La funzione, per funzionare correttamente, ha bisogno che il file dei
 * 		passeggeri sia correttamente caricato nel sistema.
 * @post Le informazioni dell'utente immesso saranno scritte sul file.
 */
int inputUtenti(FILE *input) {

	/**
	 * Variabile che indica la correttezza o no di un campo.
	 */
	int correct = 0;

	/**
	 * All'inizio, l'ID dell'utente sarà 0.
	 * Successivamente verrà preso l'ultimo ID delle utenze
	 * tramite la funzione ID_Utente().
	 */
	int id = 0;

	///Se il file non esiste, stampa un messaggio di errore.
	if( (input = fopen("passeggeri.dat", "rb+") ) == NULL) {
		printf("Errore nell'apertura.");
		fclose(input);
		return 0;
	}
	else {

		input = fopen("passeggeri.dat", "ab+");

		passeggero utenti;

		///Ricavo l'ID dell'ultimo utente tramite la funzione ID_Utente()
		/// e lo immagazzino nella variabile "id", la quale mi servirà
		/// successivamente.
		id = ID_Utente();

		///Mi posiziono all'ultima riga del file, in modo tale da
		/// scrivere su una riga vuota.
		fseek(input, sizeof(passeggero), SEEK_END);

		///Prima di inserire tutte le informazioni del nuovo utente
		/// resetto la struct passeggero.
		resetUtente(&utenti);

		/// Finchè correct non è uguale ad 1, cicla.
		while (correct != 1) {
			fflush(stdin); ///Svuoto eventuale buffer.
			printf("Nome utente %d: ", id+1);

			///Uso la fgets per poter memorizzare al massimo due nomi.
			/// Es. (Francesco Paolo).
			fgets(utenti.nome, MAX_NOME, stdin);

			/// La funzione ControlloNomeUtente(), restituisce 1 o 0.
			/// Se è 1 (significa che il nome è stato inserito correttamente)
			/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
			correct = ControlloNomeUtente(utenti);

			utenti.nome[0] = toupper(utenti.nome[0]); ///Lettera maiuscola all'inizio

			///Faccio diventare minuscole le restanti lettere, a partire dalla posizione 1.
			/// Es. (gIaNmARCO => Gianmarco)
			for (int i = 1; i < MAX_NOME+1; i++) {
				utenti.nome[i] = tolower(utenti.nome[i]);
			}

			///La fgets è conosciuta per inserire un carattere newline alla fine del vettore.
			/// Tramite questo algoritmo, controllo se alla fine del vettore stesso, è stato
			/// inserito un carattere newline (\n). Se sì, lo faccio diventare un
			/// carattere nullo (\0).
			if ((utenti.nome[0] != '\0') && (utenti.nome[strlen(utenti.nome) -1] == '\n')) {
				utenti.nome[strlen(utenti.nome) -1] = '\0';
			}

		}

		///Resetto il contatore "correct" per poter entrare nella prossima while.
		correct = 0;

		/// Finchè correct non è uguale ad 1, cicla.
		while (correct != 1) {
			printf("Cognome utente %d: ", id+1);
			scanf("%s", utenti.cognome);

			/// La funzione ControlloCognomeUtente(), restituisce 1 o 0.
			/// Se è 1 (significa che il cognome è stato inserito correttamente)
			/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
			correct = ControlloCognomeUtente(utenti);

			utenti.cognome[0] = toupper(utenti.cognome[0]); ///Lettera maiuscola all'inizio

			///Faccio diventare minuscole le restanti lettere, a partire dalla posizione 1.
			/// Es. (sCarANo => Scarano)
			for (int i = 1; i < MAX_COGNOME+1; i++) {
				utenti.cognome[i] = tolower(utenti.cognome[i]);
			}

		}

		///Resetto il contatore "correct" per poter entrare nella prossima while.
		correct = 0;

		/// Finchè correct non è uguale ad 1, cicla.
		while (correct != 1) {
			printf("Mese di nascita dell'utente %d: ", id+1);
			scanf("%s", utenti.datadinascita.mese);

			/// La funzione ControlloMeseUtente(), restituisce 1 o 0.
			/// Se è 1 (significa che il mese è stato inserito correttamente)
			/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
			correct = ControlloMeseUtente(utenti);
		}

		///Resetto il contatore "correct" per poter entrare nella prossima while.
		correct = 0;

		/// Finchè correct non è uguale ad 1, cicla.
		while (correct != 1) {
			printf("Giorno di nascita dell'utente %d: ", id+1);
			scanf("%s", utenti.datadinascita.giorno);

			/// La funzione ControlloGiornoUtente(), restituisce 1 o 0.
			/// Se è 1 (significa che il giorno è stato inserito correttamente)
			/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
			correct = ControlloGiornoUtente(utenti);
		}

		///Resetto il contatore "correct" per poter entrare nella prossima while.
		correct = 0;

		/// Finchè correct non è uguale ad 1, cicla.
		while (correct != 1) {
			printf("Anno di nascita dell'utente %d: ", id+1);
			scanf("%s", utenti.datadinascita.anno);

			/// La funzione ControlloAnnoUtente(), restituisce 1 o 0.
			/// Se è 1 (significa che l'anno è stato inserito correttamente)
			/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
			correct = ControlloAnnoUtente(utenti);
		}

		///Resetto il contatore "correct" per poter entrare nella prossima while.
		correct = 0;

		/// Finchè correct non è uguale ad 1, cicla.
		while (correct != 1) {
			printf("Comune di nascita dell'utente %d: ", id+1);
			scanf("%s", utenti.luogodinascita);

			/// La funzione ControlloLuogoDiNascita(), restituisce 1 o 0.
			/// Se è 1 (significa che il luogo di nascita è stato inserito correttamente)
			/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
			correct = ControlloLuogoDiNascita(utenti);

			utenti.luogodinascita[0] = toupper(utenti.luogodinascita[0]); ///Lettera maiuscola all'inizio

			///Faccio diventare minuscole le restanti lettere, a partire dalla posizione 1.
			/// Es. (aLtAmURA => Altamura)
			for (int i = 1; i < MAX_LUOGO_DI_NASCITA+1; i++) {
				utenti.luogodinascita[i] = tolower(utenti.luogodinascita[i]);
			}

		}

		///Resetto il contatore "correct" per poter entrare nella prossima while.
		correct = 0;

		/// Finchè correct non è uguale ad 1, cicla.
		while (correct != 1) {

			/**
			 * Dichiaro un vettore temporaneo per il passaporto
			 */
			char passaporto_temp[MAX_PASSAPORTO+1];

			printf("Numero di passaporto/carta d'identita' dell'utente %d: ", id+1);
			scanf("%s", passaporto_temp);

			/// La funzione ControlloNumeroPassaporto(), restituisce 1 o 0.
			/// Se è 1 (significa che il numero passaporto oppure
			/// il numero della carta d'identità è stato inserito correttamente)
			/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
			correct = ControlloNumeroPassaporto(passaporto_temp, MAX_PASSAPORTO);

			///Le prime due lettere devono essere maiuscole. (Es. AA1234567)
			passaporto_temp[0] = toupper(passaporto_temp[0]);
			passaporto_temp[1] = toupper(passaporto_temp[1]);

			///Copio il numero passaporto dal vettore temporaneo alla struct
			strcpy(utenti.numeropassaporto, passaporto_temp);
		}

		/// La variabile "id" conteneva l'ID dell'ultimo utente.
		/// Lo aumento di 1, e lo assegno all'utente
		/// appena registrato.
		utenti.id = id+1;

		///Scrivo tutta la struct precedentemente popolata, nel file dei passeggeri.
		fwrite(&utenti, sizeof(passeggero), 1, input);

		///Chiusura file
		fclose(input); ///Chiudo prima la prima apertura del file
		fclose(input); ///Chiudo la seconda apertura del file
		printf("\nUtente inserito correttamente!");
		printf("\nRICORDATI IL TUO NUMERO UTENTE -----> |%d|", id+1);


		return 1;
	}
}

/**
 * La seguente funzione, permette di leggere da file l'elenco dei passeggeri
 * Effettua un algoritmo di ricerca per:
 * - Nome
 * - Cognome
 * - Nome e Cognome
 * - Data di nascita
 * - Comune di nascita
 * Chiede tutti i relativi campi del passeggero stesso, effettua controlli
 * e alla fine scrive su file.
 * La funzione ha codice F10
 *
 * @pre La funzione, per funzionare correttamente, ha bisogno che il file dei
 * 		passeggeri sia correttamente caricato nel sistema.
 * @post Le informazione dell'utente immesso saranno scritte sul file.
 */
int letturaUtenti(FILE *input) {

	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

	if( (input = fopen("passeggeri.dat", "rb") ) == NULL) {
		printf("Errore nell'apertura.");
		return 0;
	}
	else {

		/**
		 * Inizializzo il file dei passeggeri
		 */
		input = NULL;

		/**
		 * Contatore che mi permetterà di uscire dal ciclo while.
		 */
		unsigned short int s = 0;

		/**
		 * Immagazzino cosa l'utente ha scelto in questa variabile
		 */
		unsigned short int sceltautente = 0;

		/// Serie di variabili contatori che mi serviranno
		/// per uscire dai cicli se il dato richiesto è giusto.
		int correct = 0;
		int correct2 = 0;

		/**
		 * Variabile per trovare la giusta posizione nel
		 * vettore "prenotazione" dentro la struct passeggero.
		 */
		int num = 0;

		/**
		 * Variabile che mi permette la lettura del file.
		 * Quando read = 0, allora la lettura è finita.
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
		 * Vettore su cui memorizzare il nome da cercare.
		 */
		char nome_temporaneo[MAX_NOME+1];

		/**
		 * Vettore su cui memorizzare il cognome da cercare.
		 */
		char cognome_temporaneo[MAX_COGNOME+1];

		/**
		 * Vettore su cui memorizzare il mese da cercare.
		 */
		char mese_temporaneo[MAX_MESE+1];

		/**
		 * Vettore su cui memorizzare il giorno da cercare.
		 */
		char giorno_temporaneo[MAX_GIORNO+1];

		/**
		 * Vettore su cui memorizzare l'anno da cercare.
		 */
		char anno_temporaneo[MAX_ANNO+1];

		/**
		 * Vettore su cui memorizzare il comune da cercare.
		 */
		char comune_temporaneo[MAX_LUOGO_DI_NASCITA+1];

		/**
		 * Variabile che userò per verificare se l'utente
		 * ha già una prenotazione o meno.
		 */
		int ora_arrivo = 0;

		/**
		 * Variabile che userò per verificare se l'utente
		 * ha già una prenotazione o meno.
		 */
		int ora_partenza = 0;

		passeggero utenti;

		while (s != 1) {	///Finchè s è diverso da 1, continua a ciclare.
			printf("\nChe metodo di ricerca vorresti utilizzare?\n");
			printf("\n1) Nome");
			printf("\n2) Cognome");
			printf("\n3) Nome e cognome");
			printf("\n4) Data di nascita");				///Stampo le possibili ricerche
			printf("\n5) Comune");
			printf("\n6) Mostra quanti utenti sono inseriti nel sistema");
			printf("\n7) Mostra quante prenotazioni sono inserite nel sistema");
			printf("\n8) Torna al menu' amministratore");
			printf("\n-------------------------------------");
			printf("\nLA TUA SCELTA: ");
			scanf("%hu", &sceltautente); ///Immagazzino la scelta dell'amministratore nella variabile sceltautente.

			///Programmazione difensiva che cattura i caratteri, nel caso in cui l'amministratore
			/// abbia immesso dei caratteri invece dei numeri.
			/// Converto i caratteri in numeri e li faccio ricadere nel "default" della switch,
			/// stampando un messaggio d'errore.
			if (s != getchar()) {
			}

			switch (sceltautente) { ///Switch per controllare cosa l'amministratore ha immesso
			case 1:
				/// Finchè correct non è uguale ad 1, cicla.
				while (correct != 1) {
					printf("Immetti il nome: ");
					scanf("%s", nome_temporaneo);

					/// La funzione ControlloNomeTemporaneo(), restituisce 1 o 0.
					/// Se è 1 (significa che il nome è stato inserito correttamente)
					/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
					correct = ControlloNomeTemporaneo(nome_temporaneo, MAX_NOME);

					nome_temporaneo[0] = toupper(nome_temporaneo[0]); ///Faccio diventare maiuscola la prima lettera

					///Faccio diventare minuscole le restanti lettere, a partire dalla posizione 1.
					/// Es. (gIaNmARCO => Gianmarco)
					for (int i = 1; i < MAX_NOME+1; i++) {
						nome_temporaneo[i] = tolower(nome_temporaneo[i]);
					}
				}

				///Apro il file in sola lettura.
				input = fopen("passeggeri.dat", "rb");

				///Leggi il file finchè read non arriva a 0.
				while( read != 0)
				{
					/// Quando read arriva a 0, significa che il file è finito.
					read = fread(&utenti, sizeof(passeggero), 1, input);

					if ( read > 0) {

						///Se il nome da cercare immesso dall'utente e il nome presente del file coincidono, allora stampalo.
						if(!strcmp(nome_temporaneo,utenti.nome)) {
							printf("\nUTENTE %d ------> %s %s - Nato il %s-%s-%s a %s | NUMERO PASSAPORTO: %s\n",utenti.id, utenti.nome,
									utenti.cognome, utenti.datadinascita.giorno, utenti.datadinascita.mese, utenti.datadinascita.anno,
									utenti.luogodinascita, utenti.numeropassaporto);

							///Finchè correct2 non è uguale a 1, cicla.
							while (correct2 != 1) {

								///Trasformo in interi l'orario di arrivo e l'orario di partenza della prenotazione[num]
								/// contenuta nella struct passeggero.
								ora_arrivo = atoi(utenti.p[num].elenco.ora_arrivo);
								ora_partenza = atoi(utenti.p[num].elenco.ora_partenza);

								///Per verificare se un utente ha una prenotazione disponibile, controllo se
								/// l'orario di arrivo (Es. 18), precedentemente convertito in intero,
								/// è minore di MAX_ORA_VOLO (23). Verifico la stessa cosa per l'orario di partenza.
								/// Se le due condizioni combaciano, allora significa che nel vettore p[num], esiste una prenotazione,
								/// quindi la stampo.
								if ((ora_arrivo < MAX_ORA_VOLO) && (ora_partenza > MIN_ORA_VOLO)) {
									printf("\nHai un volo disponibile:\n");
									printf("Volerai da %s a %s il %2s-%2s-%4s.", utenti.p[num].elenco.tratta_partenza, utenti.p[num].elenco.tratta_arrivo, utenti.p[num].elenco.datadivolo.giorno,
											utenti.p[num].elenco.datadivolo.mese, utenti.p[num].elenco.datadivolo.anno);
									printf("\nPartenza ore: %2s:%2s", utenti.p[num].elenco.ora_partenza, utenti.p[num].elenco.minuti_partenza);
									printf("\nArrivo ore: %2s:%2s", utenti.p[num].elenco.ora_arrivo, utenti.p[num].elenco.minuti_arrivo);
									printf("\nDurata del volo: %s min.", utenti.p[num].elenco.durata);
									printf("\nCodice prenotazione: %s", utenti.p[num].codice_prenotazione);
									///Controllo se l'utente ha effettuato il check-in per questa prenotazione
									/// tramite un flag che sarà uguale ad 1 solo nel caso in cui l'utente
									/// effettua il check-in.
									if (utenti.p[num].controllo_checkin == 1) {
										printf("\nCHECK-IN EFFETTUATO PER QUESTO VOLO.");
										printf("\nPosto: %d", utenti.p[num].posto);
									}
									else {
										printf("\nCHECK-IN NON EFFETTUATO PER QUESTO VOLO.");
									}
									printf("\n--------------------------------------------------------------");
									///Passo alla prossima prenotazione. Se prima p[num], era p[0], ora sarà p[1].
									/// In questo caso ricontrollo se l'utente ha un'altra prenotazione.
									num++;
								}
								else {
									/// Esco subito dal ciclo non appena l'algoritmo non trova una prenotazione disponibile.
									correct2 = 1;
								}
							}
							printf("\n");
							notfound++; ///Appena trova una occorrenza (Es. Cerco "Paolo" e trova 5 occorrenze. notfound = 5)
							 	 	 	/// aumento il contatore.
						}
					}
				}

				///Se notfound è minore di 1 (quindi 0), significa che nessun utente è stato trovato con quella occorrenza,
				/// quindi stampo un messaggio di avviso.
				if (notfound < 1) {
					printf("\nNessun risultato trovato!\n");
				}

				///Chiudo il file
				fclose(input);

				///Inizializzo il vettore usato per la ricerca e tutte le altre variabili
				/// per una eventuale nuova ricerca.
				nome_temporaneo[0] = '\0';
				correct = 0;
				correct2 = 0;
				ora_arrivo = 0;
				ora_partenza = 0;
				num = 0;
				read = 1;
				notfound = 0;
				break;
			case 2:
				/// Finchè correct non è uguale ad 1, cicla.
				while (correct != 1) {
					printf("Immetti il cognome: ");
					scanf("%s", cognome_temporaneo);

					/// La funzione ControlloCognomeTemporaneo(), restituisce 1 o 0.
					/// Se è 1 (significa che il cognome è stato inserito correttamente)
					/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
					correct = ControlloCognomeTemporaneo(cognome_temporaneo, MAX_COGNOME);
					cognome_temporaneo[0] = toupper(cognome_temporaneo[0]);

					///Faccio diventare minuscole le restanti lettere, a partire dalla posizione 1.
					/// Es. (sCarANo => Scarano)
					for (int i = 1; i < MAX_COGNOME+1; i++) {
						cognome_temporaneo[i] = tolower(cognome_temporaneo[i]);
					}
				}

				///Apro il file in sola lettura.
				input = fopen("passeggeri.dat", "rb");

				///Leggi il file finchè read non arriva a 0.
				while( read != 0)
				{
					/// Quando read arriva a 0, significa che il file è finito.
					read = fread(&utenti, sizeof(passeggero), 1, input);

					if ( read > 0) {

						///Se il cognome da cercare immesso dall'utente e il cognome presente del file coincidono, allora stampalo.
						if(!strcmp(cognome_temporaneo,utenti.cognome)) {
							printf("\nUTENTE %d ------> %s %s - Nato il %s-%s-%s a %s | NUMERO PASSAPORTO: %s\n",utenti.id, utenti.nome,
									utenti.cognome, utenti.datadinascita.giorno, utenti.datadinascita.mese, utenti.datadinascita.anno,
									utenti.luogodinascita, utenti.numeropassaporto);

							///Finchè correct2 non è uguale a 1, cicla.
							while (correct2 != 1) {

								///Trasformo in interi l'orario di arrivo e l'orario di partenza della prenotazione[num]
								/// contenuta nella struct passeggero.
								ora_arrivo = atoi(utenti.p[num].elenco.ora_arrivo);
								ora_partenza = atoi(utenti.p[num].elenco.ora_partenza);

								///Per verificare se un utente ha una prenotazione disponibile, controllo se
								/// l'orario di arrivo (Es. 18), precedentemente convertito in intero,
								/// è minore di MAX_ORA_VOLO (23). Verifico la stessa cosa per l'orario di partenza.
								/// Se le due condizioni combaciano, allora significa che nel vettore p[num], esiste una prenotazione,
								/// quindi la stampo.
								if ((ora_arrivo < MAX_ORA_VOLO) && (ora_partenza > MIN_ORA_VOLO)) {
									printf("\nHai un volo disponibile:\n");
									printf("Volerai da %s a %s il %2s-%2s-%4s.", utenti.p[num].elenco.tratta_partenza, utenti.p[num].elenco.tratta_arrivo, utenti.p[num].elenco.datadivolo.giorno,
											utenti.p[num].elenco.datadivolo.mese, utenti.p[num].elenco.datadivolo.anno);
									printf("\nPartenza ore: %2s:%2s", utenti.p[num].elenco.ora_partenza, utenti.p[num].elenco.minuti_partenza);
									printf("\nArrivo ore: %2s:%2s", utenti.p[num].elenco.ora_arrivo, utenti.p[num].elenco.minuti_arrivo);
									printf("\nDurata del volo: %s min.", utenti.p[num].elenco.durata);
									printf("\nCodice prenotazione: %s", utenti.p[num].codice_prenotazione);
									///Controllo se l'utente ha effettuato il check-in per questa prenotazione
									/// tramite un flag che sarà uguale ad 1 solo nel caso in cui l'utente
									/// effettua il check-in.
									if (utenti.p[num].controllo_checkin == 1) {
										printf("\nCHECK-IN EFFETTUATO PER QUESTO VOLO.");
										printf("\nPosto: %d", utenti.p[num].posto);
									}
									else {
										printf("\nCHECK-IN NON EFFETTUATO PER QUESTO VOLO.");
									}
									printf("\n--------------------------------------------------------------");
									///Passo alla prossima prenotazione. Se prima p[num], era p[0], ora sarà p[1].
									/// In questo caso ricontrollo se l'utente ha un'altra prenotazione.
									num++;
								}
								else {
									/// Esco subito dal ciclo non appena l'algoritmo non trova una prenotazione disponibile.
									correct2 = 1;
								}
							}
							printf("\n");
							notfound++; ///Appena trova una occorrenza (Es. Cerco "Scarano" e trova 5 occorrenze. notfound = 5)
							 	 	 	/// aumento il contatore.
						}
					}
				}

				///Se notfound è minore di 1 (quindi 0), significa che nessun utente è stato trovato con quella occorrenza,
				/// quindi stampo un messaggio di avviso.
				if (notfound < 1) {
					printf("\nNessun risultato trovato!\n");
				}

				///Chiudo il file
				fclose(input);

				///Inizializzo il vettore usato per la ricerca e tutte le altre variabili
				/// per una eventuale nuova ricerca.
				cognome_temporaneo[0] = '\0';
				correct = 0;
				correct2 = 0;
				ora_arrivo = 0;
				ora_partenza = 0;
				num = 0;
				read = 1;
				notfound = 0;
				break;
			case 3:
				/// Finchè correct non è uguale ad 1, cicla.
				while (correct != 1) {
					printf("Immetti il nome: ");
					scanf("%s", nome_temporaneo);

					/// La funzione ControlloNomeTemporaneo(), restituisce 1 o 0.
					/// Se è 1 (significa che il nome è stato inserito correttamente)
					/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
					correct = ControlloNomeTemporaneo(nome_temporaneo, MAX_NOME);

					nome_temporaneo[0] = toupper(nome_temporaneo[0]); ///Faccio diventare maiuscola la prima lettera

					///Faccio diventare minuscole le restanti lettere, a partire dalla posizione 1.
					/// Es. (gIaNmARCO => Gianmarco)
					for (int i = 1; i < MAX_NOME+1; i++) {
						nome_temporaneo[i] = tolower(nome_temporaneo[i]);
					}
				}

				correct = 0;

				/// Finchè correct non è uguale ad 1, cicla.
				while (correct != 1) {
					printf("Immetti il cognome: ");
					scanf("%s", cognome_temporaneo);

					/// La funzione ControlloCognomeTemporaneo(), restituisce 1 o 0.
					/// Se è 1 (significa che il cognome è stato inserito correttamente)
					/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
					correct = ControlloCognomeTemporaneo(cognome_temporaneo, MAX_COGNOME);
					cognome_temporaneo[0] = toupper(cognome_temporaneo[0]);

					///Faccio diventare minuscole le restanti lettere, a partire dalla posizione 1.
					/// Es. (sCarANo => Scarano)
					for (int i = 1; i < MAX_COGNOME+1; i++) {
						cognome_temporaneo[i] = tolower(cognome_temporaneo[i]);
					}
				}

				///Apro il file in sola lettura.
				input = fopen("passeggeri.dat", "rb");

				///Leggi il file finchè read non arriva a 0.
				while( read != 0)
				{
					/// Quando read arriva a 0, significa che il file è finito.
					read = fread(&utenti, sizeof(passeggero), 1, input);

					if ( read > 0) {

						///Se il nome ed il cognome da cercare immesso dall'utente coincide con il nome e cognome
						/// presente sul file, allora stampalo.
						if(!strcmp(nome_temporaneo,utenti.nome) && !strcmp(cognome_temporaneo,utenti.cognome)) {
							printf("\nUTENTE %d ------> %s %s - Nato il %s-%s-%s a %s | NUMERO PASSAPORTO: %s\n",utenti.id, utenti.nome,
									utenti.cognome, utenti.datadinascita.giorno, utenti.datadinascita.mese, utenti.datadinascita.anno,
									utenti.luogodinascita, utenti.numeropassaporto);

							///Finchè correct2 non è uguale a 1, cicla.
							while (correct2 != 1) {

								///Trasformo in interi l'orario di arrivo e l'orario di partenza della prenotazione[num]
								/// contenuta nella struct passeggero.
								ora_arrivo = atoi(utenti.p[num].elenco.ora_arrivo);
								ora_partenza = atoi(utenti.p[num].elenco.ora_partenza);

								///Per verificare se un utente ha una prenotazione disponibile, controllo se
								/// l'orario di arrivo (Es. 18), precedentemente convertito in intero,
								/// è minore di MAX_ORA_VOLO (23). Verifico la stessa cosa per l'orario di partenza.
								/// Se le due condizioni combaciano, allora significa che nel vettore p[num], esiste una prenotazione,
								/// quindi la stampo.
								if ((ora_arrivo < MAX_ORA_VOLO) && (ora_partenza > MIN_ORA_VOLO)) {
									printf("\nHai un volo disponibile:\n");
									printf("Volerai da %s a %s il %2s-%2s-%4s.", utenti.p[num].elenco.tratta_partenza, utenti.p[num].elenco.tratta_arrivo, utenti.p[num].elenco.datadivolo.giorno,
											utenti.p[num].elenco.datadivolo.mese, utenti.p[num].elenco.datadivolo.anno);
									printf("\nPartenza ore: %2s:%2s", utenti.p[num].elenco.ora_partenza, utenti.p[num].elenco.minuti_partenza);
									printf("\nArrivo ore: %2s:%2s", utenti.p[num].elenco.ora_arrivo, utenti.p[num].elenco.minuti_arrivo);
									printf("\nDurata del volo: %s min.", utenti.p[num].elenco.durata);
									printf("\nCodice prenotazione: %s", utenti.p[num].codice_prenotazione);
									///Controllo se l'utente ha effettuato il check-in per questa prenotazione
									/// tramite un flag che sarà uguale ad 1 solo nel caso in cui l'utente
									/// effettua il check-in.
									if (utenti.p[num].controllo_checkin == 1) {
										printf("\nCHECK-IN EFFETTUATO PER QUESTO VOLO.");
										printf("\nPosto: %d", utenti.p[num].posto);
									}
									else {
										printf("\nCHECK-IN NON EFFETTUATO PER QUESTO VOLO.");
									}
									printf("\n--------------------------------------------------------------");
									///Passo alla prossima prenotazione. Se prima p[num], era p[0], ora sarà p[1].
									/// In questo caso ricontrollo se l'utente ha un'altra prenotazione.
									num++;
								}
								else {
									/// Esco subito dal ciclo non appena l'algoritmo non trova una prenotazione disponibile.
									correct2 = 1;
								}
							}
							printf("\n");
							notfound++; ///Appena trova una occorrenza (Es. Cerco "Scarano" e trova 5 occorrenze. notfound = 5)
							 	 	 	/// aumento il contatore.
						}
					}
				}

				///Se notfound è minore di 1 (quindi 0), significa che nessun utente è stato trovato con quella occorrenza,
				/// quindi stampo un messaggio di avviso.
				if (notfound < 1) {
					printf("\nNessun risultato trovato!\n");
				}

				///Chiudo il file
				fclose(input);

				///Inizializzo il vettore usato per la ricerca e tutte le altre variabili
				/// per una eventuale nuova ricerca.
				nome_temporaneo[0] = '\0';
				cognome_temporaneo[0] = '\0';
				correct = 0;
				correct2 = 0;
				ora_arrivo = 0;
				ora_partenza = 0;
				num = 0;
				read = 1;
				notfound = 0;
				break;
			case 4:
				/// Finchè correct non è uguale ad 1, cicla.
				while (correct != 1) {
					printf("Immetti il mese: ");
					scanf("%s", mese_temporaneo);

					/// La funzione ControlloMeseTemporaneo(), restituisce 1 o 0.
					/// Se è 1 (significa che il mese è stato inserito correttamente)
					/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
					correct = ControlloMeseTemporaneo(mese_temporaneo, MAX_MESE);
				}
				correct = 0;

				/// Finchè correct non è uguale ad 1, cicla.
				while (correct != 1) {
					printf("Immetti il giorno: ");
					scanf("%s", giorno_temporaneo);

					/// La funzione ControlloGiornoTemporaneo(), restituisce 1 o 0.
					/// Se è 1 (significa che il giorno è stato inserito correttamente)
					/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
					correct = ControlloGiornoTemporaneo(giorno_temporaneo, mese_temporaneo, MAX_GIORNO);
				}
				correct = 0;
				while (correct != 1) {
					printf("Immetti l'anno: ");
					scanf("%s", anno_temporaneo);

					/// La funzione ControlloAnnoTemporaneo(), restituisce 1 o 0.
					/// Se è 1 (significa che l'anno è stato inserito correttamente)
					/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
					correct = ControlloAnnoTemporaneo(anno_temporaneo, MAX_ANNO);
				}

				///Apro il file in sola lettura.
				input = fopen("passeggeri.dat", "rb");

				///Leggi il file finchè read non arriva a 0.
				while( read != 0)
				{
					/// Quando read arriva a 0, significa che il file è finito.
					read = fread(&utenti, sizeof(passeggero), 1, input);

					if ( read > 0) {
						///Se la data da cercare corrisponde con la data trovata nel file, allora stampo.
						if(!strcmp(mese_temporaneo,utenti.datadinascita.mese) && !strcmp(giorno_temporaneo,utenti.datadinascita.giorno) && !strcmp(anno_temporaneo,utenti.datadinascita.anno)) {
							printf("\nUTENTE %d ------> %s %s - Nato il %s-%s-%s a %s | NUMERO PASSAPORTO: %s\n",utenti.id, utenti.nome,
									utenti.cognome, utenti.datadinascita.giorno, utenti.datadinascita.mese, utenti.datadinascita.anno,
									utenti.luogodinascita, utenti.numeropassaporto);

							///Finchè correct2 non è uguale a 1, cicla.
							while (correct2 != 1) {

								///Trasformo in interi l'orario di arrivo e l'orario di partenza della prenotazione[num]
								/// contenuta nella struct passeggero.
								ora_arrivo = atoi(utenti.p[num].elenco.ora_arrivo);
								ora_partenza = atoi(utenti.p[num].elenco.ora_partenza);

								///Per verificare se un utente ha una prenotazione disponibile, controllo se
								/// l'orario di arrivo (Es. 18), precedentemente convertito in intero,
								/// è minore di MAX_ORA_VOLO (23). Verifico la stessa cosa per l'orario di partenza.
								/// Se le due condizioni combaciano, allora significa che nel vettore p[num], esiste una prenotazione,
								/// quindi la stampo.
								if ((ora_arrivo < MAX_ORA_VOLO) && (ora_partenza > MIN_ORA_VOLO)) {
									printf("\nHai un volo disponibile:\n");
									printf("Volerai da %s a %s il %2s-%2s-%4s.", utenti.p[num].elenco.tratta_partenza, utenti.p[num].elenco.tratta_arrivo, utenti.p[num].elenco.datadivolo.giorno,
											utenti.p[num].elenco.datadivolo.mese, utenti.p[num].elenco.datadivolo.anno);
									printf("\nPartenza ore: %2s:%2s", utenti.p[num].elenco.ora_partenza, utenti.p[num].elenco.minuti_partenza);
									printf("\nArrivo ore: %2s:%2s", utenti.p[num].elenco.ora_arrivo, utenti.p[num].elenco.minuti_arrivo);
									printf("\nDurata del volo: %s min.", utenti.p[num].elenco.durata);
									printf("\nCodice prenotazione: %s", utenti.p[num].codice_prenotazione);
									///Controllo se l'utente ha effettuato il check-in per questa prenotazione
									/// tramite un flag che sarà uguale ad 1 solo nel caso in cui l'utente
									/// effettua il check-in.
									if (utenti.p[num].controllo_checkin == 1) {
										printf("\nCHECK-IN EFFETTUATO PER QUESTO VOLO.");
										printf("\nPosto: %d", utenti.p[num].posto);
									}
									else {
										printf("\nCHECK-IN NON EFFETTUATO PER QUESTO VOLO.");
									}
									printf("\n--------------------------------------------------------------");
									///Passo alla prossima prenotazione. Se prima p[num], era p[0], ora sarà p[1].
									/// In questo caso ricontrollo se l'utente ha un'altra prenotazione.
									num++;
								}
								else {
									/// Esco subito dal ciclo non appena l'algoritmo non trova una prenotazione disponibile.
									correct2 = 1;
								}
							}
							printf("\n");
							notfound++; ///Appena trova una occorrenza (Es. Cerco "Scarano" e trova 5 occorrenze. notfound = 5)
							 	 	 	/// aumento il contatore.
						}
					}
				}

				///Se notfound è minore di 1 (quindi 0), significa che nessun utente è stato trovato con quella occorrenza,
				/// quindi stampo un messaggio di avviso.
				if (notfound < 1) {
					printf("\nNessun risultato trovato!\n");
				}

				///Chiudo il file
				fclose(input);

				///Inizializzo i vettori usati per la ricerca e tutte le altre variabili
				/// per una eventuale nuova ricerca.
				mese_temporaneo[0] = '\0';
				giorno_temporaneo[0] = '\0';
				anno_temporaneo[0] = '\0';
				correct = 0;
				correct2 = 0;
				ora_arrivo = 0;
				ora_partenza = 0;
				num = 0;
				read = 1;
				notfound = 0;
				break;
			case 5:
				///Finchè correct non è uguale a 1, cicla.
				while (correct != 1) {
					printf("Immetti il comune di nascita: ");
					scanf("%s", comune_temporaneo);

					/// La funzione ControlloComuneTemporaneo(), restituisce 1 o 0.
					/// Se è 1 (significa che il comune è stato inserito correttamente)
					/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
					correct = ControlloComuneTemporaneo(comune_temporaneo, MAX_LUOGO_DI_NASCITA);
					comune_temporaneo[0] = toupper(comune_temporaneo[0]); ///Maiuscola all'inizio

					///Faccio diventare minuscole le restanti lettere, a partire dalla posizione 1.
					/// Es. (aLtAMUra => Altamura)
					for (int i = 1; i < MAX_LUOGO_DI_NASCITA+1; i++) {
						comune_temporaneo[i] = tolower(comune_temporaneo[i]);
					}

				}

				///Apro il file in sola lettura.
				input = fopen("passeggeri.dat", "rb");

				///Leggi il file finchè read non arriva a 0.
				while( read != 0)
				{
					/// Quando read arriva a 0, significa che il file è finito.
					read = fread(&utenti, sizeof(passeggero), 1, input);

					if ( read > 0) {

						///Se il comune da cercare corrisponde con il comune trovato nel file, allora stampa.
						if(!strcmp(comune_temporaneo,utenti.luogodinascita)) {
							printf("\nUTENTE %d ------> %s %s - Nato il %s-%s-%s a %s | NUMERO PASSAPORTO: %s\n",utenti.id, utenti.nome,
									utenti.cognome, utenti.datadinascita.giorno, utenti.datadinascita.mese, utenti.datadinascita.anno,
									utenti.luogodinascita, utenti.numeropassaporto);

							///Finchè correct2 non è uguale a 1, cicla.
							while (correct2 != 1) {

								///Trasformo in interi l'orario di arrivo e l'orario di partenza della prenotazione[num]
								/// contenuta nella struct passeggero.
								ora_arrivo = atoi(utenti.p[num].elenco.ora_arrivo);
								ora_partenza = atoi(utenti.p[num].elenco.ora_partenza);

								///Per verificare se un utente ha una prenotazione disponibile, controllo se
								/// l'orario di arrivo (Es. 18), precedentemente convertito in intero,
								/// è minore di MAX_ORA_VOLO (23). Verifico la stessa cosa per l'orario di partenza.
								/// Se le due condizioni combaciano, allora significa che nel vettore p[num], esiste una prenotazione,
								/// quindi la stampo.
								if ((ora_arrivo < MAX_ORA_VOLO) && (ora_partenza > MIN_ORA_VOLO)) {
									printf("\nHai un volo disponibile:\n");
									printf("Volerai da %s a %s il %2s-%2s-%4s.", utenti.p[num].elenco.tratta_partenza, utenti.p[num].elenco.tratta_arrivo, utenti.p[num].elenco.datadivolo.giorno,
											utenti.p[num].elenco.datadivolo.mese, utenti.p[num].elenco.datadivolo.anno);
									printf("\nPartenza ore: %2s:%2s", utenti.p[num].elenco.ora_partenza, utenti.p[num].elenco.minuti_partenza);
									printf("\nArrivo ore: %2s:%2s", utenti.p[num].elenco.ora_arrivo, utenti.p[num].elenco.minuti_arrivo);
									printf("\nDurata del volo: %s min.", utenti.p[num].elenco.durata);
									printf("\nCodice prenotazione: %s", utenti.p[num].codice_prenotazione);
									///Controllo se l'utente ha effettuato il check-in per questa prenotazione
									/// tramite un flag che sarà uguale ad 1 solo nel caso in cui l'utente
									/// effettua il check-in.
									if (utenti.p[num].controllo_checkin == 1) {
										printf("\nCHECK-IN EFFETTUATO PER QUESTO VOLO.");
										printf("\nPosto: %d", utenti.p[num].posto);
									}
									else {
										printf("\nCHECK-IN NON EFFETTUATO PER QUESTO VOLO.");
									}
									printf("\n--------------------------------------------------------------");
									///Passo alla prossima prenotazione. Se prima p[num], era p[0], ora sarà p[1].
									/// In questo caso ricontrollo se l'utente ha un'altra prenotazione.
									num++;
								}
								else {
									/// Esco subito dal ciclo non appena l'algoritmo non trova una prenotazione disponibile.
									correct2 = 1;
								}
							}
							printf("\n");
							notfound++; ///Appena trova una occorrenza (Es. Cerco "Scarano" e trova 5 occorrenze. notfound = 5)
							 	 	 	/// aumento il contatore.
						}
					}
				}

				///Se notfound è minore di 1 (quindi 0), significa che nessun utente è stato trovato con quella occorrenza,
				/// quindi stampo un messaggio di avviso.
				if (notfound < 1) {
					printf("\nNessun risultato trovato!\n");
				}

				///Chiudo il file
				fclose(input);

				///Inizializzo i vettori usati per la ricerca e tutte le altre variabili
				/// per una eventuale nuova ricerca.
				comune_temporaneo[0] = '\0';
				correct = 0;
				correct2 = 0;
				ora_arrivo = 0;
				ora_partenza = 0;
				num = 0;
				read = 1;
				notfound = 0;
				break;
			case 6:
				input = fopen("passeggeri.dat", "ab+");

				///Tramite la fseek impostata a SEEK_END, mi sposto all'ultima riga.
				/// Per leggere l'ultimo utente, muovo l'offset a (-1).
				fseek(input, (-1)*sizeof(passeggero), SEEK_END);

				///Leggo l'utente e stampo il suo ID.
				/// Quell'ID mi dirà quanti utenti sono registrati nel sistema.
				fread(&utenti, sizeof(passeggero), 1, input);
				printf("Gli utenti presenti nel sistema sono %d.\n", utenti.id);

				fclose(input);
				break;
			case 7:
				///Apro il file in sola lettura.
				input = fopen("passeggeri.dat", "rb");

				///Leggi il file finchè read non arriva a 0.
				while( read != 0)
				{
					/// Quando read arriva a 0, significa che il file è finito.
					read = fread(&utenti, sizeof(passeggero), 1, input);

					if ( read > 0) {
						///Finchè correct2 non è uguale a 1, cicla.
						while (correct2 != 1) {

							///Trasformo in interi l'orario di arrivo e l'orario di partenza della prenotazione[num]
							/// contenuta nella struct passeggero.
							ora_arrivo = atoi(utenti.p[num].elenco.ora_arrivo);
							ora_partenza = atoi(utenti.p[num].elenco.ora_partenza);

							///Per verificare se un utente ha una prenotazione disponibile, controllo se
							/// l'orario di arrivo (Es. 18), precedentemente convertito in intero,
							/// è minore di MAX_ORA_VOLO (23). Verifico la stessa cosa per l'orario di partenza.
							/// Se le due condizioni combaciano, allora significa che nel vettore p[num], esiste una prenotazione,
							/// quindi la stampo.
							if ((ora_arrivo < MAX_ORA_VOLO) && (ora_partenza > MIN_ORA_VOLO)) {
								///Aumento il contatore delle prenotazioni
								found++;
								///Passo alla prossima prenotazione. Se prima p[num], era p[0], ora sarà p[1].
								/// In questo caso ricontrollo se l'utente ha un'altra prenotazione.
								num++;
							}
							else {
								/// Esco subito dal ciclo non appena l'algoritmo non trova una prenotazione disponibile.
								correct2 = 1;
							}
						}
						///Resetto le variabili per passare al prossimo utente
						ora_arrivo = 0;
						ora_partenza = 0;
						num = 0;
						correct2 = 0;
					}
				}
				///Chiudo il file
				fclose(input);

				printf("\nCi sono %d prenotazioni inserite nel sistema.\n", found);

				///Inizializzo i vettori usati per la ricerca e tutte le altre variabili
				/// per una eventuale nuova ricerca.
				correct2 = 0;
				ora_arrivo = 0;
				ora_partenza = 0;
				num = 0;
				read = 1;
				found = 0;
				break;
			case 8:
				s = 1; ///Rendo vero il valore della while ed torno al menu amministratore.
				break;
			default:
				///Qui ricadranno tutti i valori non corretti. (caratteri e num > 7).
				printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
				printf("\nValore non corretto.");
				break;
			}
		}
	}
	fclose(input);

	return 1;
}

/**
 * La seguente funzione, permette di modificare le informazione del passeggero.
 * Effettua un algoritmo di modifica per:
 * - Nome
 * - Cognome
 * - Nome e Cognome
 * - Data di nascita
 * - Comune di nascita
 * - Passaporto
 * Chiede tutti i relativi campi del passeggero stesso, effettua controlli
 * e alla fine scrive su file.
 * La funzione ha codice F03
 *
 * @pre La funzione, per funzionare correttamente, ha bisogno che il file dei
 * 		passeggeri sia correttamente caricato nel sistema.
 * @post Le modifiche dell'utente immesso saranno scritte sul file.
 */
int modificaUtente(FILE *passeggeri) {

	/**
	 * Struct passeggero
	 */
	passeggero utenti;

	/**
	 * File dei passeggeri inizializzato
	 */
	passeggeri = NULL;

	/**
	 * Variabile contatore che mi serve per uscire
	 * dai cicli se il dato richiesto è giusto.
	 */
	int correct = 0;

	/**
	 * Variabile contatore che mi serve per uscire
	 * dai cicli se il dato richiesto è giusto.
	 */
	int correct2 = 0;

	/**
	 * Variabile contatore che mi serve per uscire
	 * dai cicli se il dato richiesto è giusto.
	 */
	int correct3 = 0;

	/**
	 * Variabile contatore che mi serve per uscire
	 * dai cicli se il dato richiesto è giusto.
	 */
	int correct4 = 0;

	/**
	 * Contatore che mi permette di ritornare al menu
	 * una volta arrivato a 0.
	 */
	int wrong = 3;

	/**
	 * Variabile per trovare la giusta posizione nel
	 * vettore "prenotazione" dentro la struct passeggero.
	 */
	int num = 0;

	/**
	 * Variabile che userò per verificare se l'utente
	 * ha già una prenotazione o meno.
	 */
	int ora_arrivo = 0;

	/**
	 * Variabile che userò per verificare se l'utente
	 * ha già una prenotazione o meno.
	 */
	int ora_partenza = 0;

	/**
	 * Variabile che userò per immagazzinare l'ID
	 * dell'utente da eliminare.
	 */
	int id_utente_eliminato = 0;

	/**
	 * Variabile che userò per immagazzinare l'ID
	 * dell'utente da modificare.
	 */
	char numeroutente[3] = "\0";

	/**
	 * Variabile che userò per convertire l'ID dell'utente
	 * da char a int.
	 */
	int numero_utente = 0;

	/**
	 * Contatore che mi permetterà di uscire dal ciclo while.
	 */
	unsigned short int s = 0;

	/**
	 * Immagazzino cosa l'utente ha scelto in questa variabile
	 */
	unsigned short int scelta_utente = 0;

	/**
	 * Vettore su cui memorizzare il nome da modificare.
	 */
	char nome_temporaneo[MAX_NOME+1];

	/**
	 * Vettore su cui memorizzare il cognome da modificare.
	 */
	char cognome_temporaneo[MAX_COGNOME+1];

	/**
	 * Vettore su cui memorizzare il mese da modificare.
	 */
	char mese_temporaneo[MAX_MESE+1];

	/**
	 * Vettore su cui memorizzare il giorno da modificare.
	 */
	char giorno_temporaneo[MAX_GIORNO+1];

	/**
	 * Vettore su cui memorizzare l'anno da modificare.
	 */
	char anno_temporaneo[MAX_ANNO+1];

	/**
	 * Vettore su cui memorizzare il comune da modificare.
	 */
	char comune_temporaneo[MAX_LUOGO_DI_NASCITA+1];

	/**
	 * Vettore su cui memorizzare il passaporto da modificare.
	 */
	char passaporto_temp[MAX_PASSAPORTO+1];

	///Apro il file. Se non esiste, stampo un messaggio di errore.
	while (correct != 1) {
		if( (passeggeri = fopen("passeggeri.dat", "rb+") ) == NULL) {
			printf("Errore nell'apertura.");
			return 0;
			correct = 1;
		}
		else
		{
			///Finchè correct4 non è uguale a 1, cicla.
			while (correct4 != 1) {
				printf("\nQuale e' il tuo numero utente?");
				printf("\nNUMERO UTENTE: ");
				scanf("%s", numeroutente);

				///Trasformo in intero l'ID immesso precedentemente
				numero_utente = atoi(numeroutente);

				///Tramite la funzione fseek(), mi sposto all'utente desiderato.
				fseek(passeggeri, (numero_utente-1)*sizeof(passeggero), SEEK_SET);
				fread(&utenti, sizeof(passeggero), 1, passeggeri);

				///Se l'utente ha immesso un ID diverso da 0 e il nome relativo
				/// a quell'ID è nullo, allora stampa un errore.
				if (utenti.nome[0] != '\0' && numero_utente != 0)
				{
					printf("\n---- Benvenuto %s %s! ----", utenti.nome, utenti.cognome);
					while (correct2 != 1) {
						printf("\n---- Si prega di confermare l'identita' ----\n");
						printf("\nNUMERO PASSAPORTO: ");
						passaporto_temp[0] = '\0';
						scanf("%s", passaporto_temp);

						/// La funzione ControlloPassaportoTemporaneo(), restituisce 1 o 0.
						/// Se è 1 (significa che il passaporto è stato inserito correttamente)
						/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
						correct2 = ControlloPassaportoTemporaneo(passaporto_temp, MAX_PASSAPORTO, 0);

						///Le prime due lettere devono essere maiuscole. (Es. AA1234567)
						passaporto_temp[0] = toupper(passaporto_temp[0]);
						passaporto_temp[1] = toupper(passaporto_temp[1]);
					}
					if (correct2 == 1) {
						///Confronto il passaporto precedentemente immesso con
						/// il passaporto dell'utente pescato con la fseek(),
						/// sempre precedentemente.
						if(!strcmp(passaporto_temp,utenti.numeropassaporto)) {
							printf("\nPassaporto inserito correttamente!\n\n");
							correct = 1; ///Esco dal ciclo principale.
							correct4 = 1; ///Esco dal ciclo di login.
						}
						///Resetto il vettore del passaporto temporaneo e
						/// riporto correct2 a 0, altrimenti non entrerà
						/// nella while del correct2.
						else {
							printf ("\nPassaporto errato. Riprovare.\n\n");
							passaporto_temp[0] = '\0';
							correct2 = 0;
						}
					}
				}
				///Enterò in questo else solamente quando l'utente ha messo un ID non valido.
				else {
					printf("\nNessun utente trovato con questo ID!");
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

	fflush(stdin);

	correct = 0;

	while (s != 1) {	///Finchè s è uguale a 1, eseguo il loop.
		printf("\n1) Modifica nome");
		printf("\n2) Modifica cognome");
		printf("\n3) Modifica luogo di nascita");
		printf("\n4) Modifica data di nascita");			///Stampo le scelte per l'utente.
		printf("\n5) Modifica passaporto");
		printf("\n6) Modifica prenotazione");
		printf("\n7) Elimina utente");
		printf("\n8) Leggi le tue informazioni");
		printf("\n9) Ritorna al menu precedente (menu utente)");
		printf("\n10) Esci dal programma");
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
			///Tramite fseek(), mostro all'utente il nome che intende modificare.
			passeggeri = fopen("passeggeri.dat", "rb");
			fseek(passeggeri, (numero_utente-1)*sizeof(passeggero), SEEK_SET);
			fread(&utenti, sizeof(passeggero), 1, passeggeri);
			printf("Vecchio nome: %s\n", utenti.nome);
			fclose(passeggeri);

			///Finchè correct è uguale a 1, ciclo.
			while (correct != 1) {
				fflush(stdin);
				printf("Immetti il nuovo nome: ");

				///Uso la fgets per poter memorizzare al massimo due nomi.
				/// Es. (Francesco Paolo).
				fgets(nome_temporaneo, MAX_NOME, stdin);

				/// La funzione ControlloNomeTemporaneo(), restituisce 1 o 0.
				/// Se è 1 (significa che il nome è stato inserito correttamente)
				/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
				correct = ControlloNomeTemporaneo(nome_temporaneo, MAX_NOME);

				nome_temporaneo[0] = toupper(nome_temporaneo[0]); ///La prima lettera diventerà maiuscola.

				///Faccio diventare minuscole le restanti lettere, a partire dalla posizione 1.
				/// Es. (gIaNmARCO => Gianmarco)
				for (int i = 1; i < MAX_NOME+1; i++) {
					nome_temporaneo[i] = tolower(nome_temporaneo[i]);
				}

				///La fgets è conosciuta per inserire un carattere newline alla fine del vettore.
				/// Tramite questo algoritmo, controllo se alla fine del vettore stesso, è stato
				/// inserito un carattere newline (\n). Se sì, lo faccio diventare un
				/// carattere nullo (\0).
				if ((nome_temporaneo[0] != '\0') && (nome_temporaneo[strlen(nome_temporaneo) -1] == '\n')) {
					nome_temporaneo[strlen(nome_temporaneo) -1] = '\0';
				}

			}

			passeggeri = fopen("passeggeri.dat", "rb+");

			///Tramite fseek(), mi posiziono all'utente giusto tramite "numeroutente", dopo di che mi muovo nel
			/// giusto membro (utenti.nome).
			fseek(passeggeri, (numero_utente-1)*sizeof(passeggero) + (((char *) &utenti.nome) - ((char *) &utenti)), SEEK_SET);

			///Copio il nome immesso in nome_temporaneo nel membro .nome della struct.
			strcpy(utenti.nome, nome_temporaneo);

			///Aggiorno il file e lo chiudo.
			fwrite(&utenti.nome, sizeof(utenti.nome), 1, passeggeri);
			fclose(passeggeri);

			correct = 0;
			break;
		case 2:
			///Tramite fseek(), mostro all'utente il cognome che intende modificare.
			passeggeri = fopen("passeggeri.dat", "rb");
			fseek(passeggeri, (numero_utente-1)*sizeof(passeggero), SEEK_SET);
			fread(&utenti, sizeof(passeggero), 1, passeggeri);
			printf("Vecchio cognome: %s\n", utenti.cognome);
			fclose(passeggeri);

			///Finchè correct è uguale a 1, ciclo.
			while (correct != 1) {
				printf("Immetti il nuovo cognome: ");
				scanf("%s", cognome_temporaneo);

				/// La funzione ControlloCognomeTemporaneo(), restituisce 1 o 0.
				/// Se è 1 (significa che il cognome è stato inserito correttamente)
				/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
				correct = ControlloCognomeTemporaneo(cognome_temporaneo, MAX_COGNOME);

				cognome_temporaneo[0] = toupper(cognome_temporaneo[0]); ///La prima lettera diventerà maiuscola.

				///Faccio diventare minuscole le restanti lettere, a partire dalla posizione 1.
				/// Es. (ScArANo => Scarano)
				for (int i = 1; i < MAX_COGNOME+1; i++) {
					cognome_temporaneo[i] = tolower(cognome_temporaneo[i]);
				}
			}

			passeggeri = fopen("passeggeri.dat", "rb+");

			///Tramite fseek(), mi posiziono all'utente giusto tramite "numeroutente", dopo di che mi muovo nel
			/// giusto membro (utenti.cognome).
			fseek(passeggeri, (numero_utente-1)*sizeof(passeggero) + (((char *) &utenti.cognome) - ((char *) &utenti)), SEEK_SET);

			///Copio il cognome immesso in cognome_temporaneo nel membro .cognome della struct.
			strcpy(utenti.cognome, cognome_temporaneo);

			///Aggiorno il file e lo chiudo.
			fwrite(&utenti.cognome, sizeof(utenti.cognome), 1, passeggeri);
			fclose(passeggeri);

			correct = 0;
			break;
		case 3:
			///Tramite fseek(), mostro all'utente il luogo di nascita che intende modificare.
			passeggeri = fopen("passeggeri.dat", "rb");
			fseek(passeggeri, (numero_utente-1)*sizeof(passeggero), SEEK_SET);
			fread(&utenti, sizeof(passeggero), 1, passeggeri);
			printf("Vecchio luogo di nascita: %s\n", utenti.luogodinascita);
			fclose(passeggeri);

			///Finchè correct è uguale a 1, ciclo.
			while (correct != 1) {
				printf("Immetti il nuovo luogo di nascita: ");
				scanf("%s", comune_temporaneo);

				/// La funzione ControlloComuneTemporaneo(), restituisce 1 o 0.
				/// Se è 1 (significa che il comune è stato inserito correttamente)
				/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
				correct = ControlloComuneTemporaneo(comune_temporaneo, MAX_LUOGO_DI_NASCITA);

				comune_temporaneo[0] = toupper(comune_temporaneo[0]); ///La prima lettera diventera maiuscola.

				///Faccio diventare minuscole le restanti lettere, a partire dalla posizione 1.
				/// Es. (AlTAMuRA => Altamura)
				for (int i = 1; i < MAX_LUOGO_DI_NASCITA+1; i++) {
					comune_temporaneo[i] = tolower(comune_temporaneo[i]);
				}
			}

			passeggeri = fopen("passeggeri.dat", "rb+");
			///Tramite fseek(), mi posiziono all'utente giusto tramite "numeroutente", dopo di che mi muovo nel
			/// giusto membro (utenti.luogodinascita).
			fseek(passeggeri, (numero_utente-1)*sizeof(passeggero) + (((char *) &utenti.luogodinascita) - ((char *) &utenti)), SEEK_SET);

			///Copio il luogo di nascita immesso in comune_temporaneo nel membro .luogodinascita della struct.
			strcpy(utenti.luogodinascita, comune_temporaneo);

			///Aggiorno il file e lo chiudo.
			fwrite(&utenti.luogodinascita, sizeof(utenti.luogodinascita), 1, passeggeri);
			fclose(passeggeri);

			correct = 0;
			break;
		case 4:
			///Tramite fseek(), mostro all'utente la data di nascita che intende modificare.
			passeggeri = fopen("passeggeri.dat", "rb");
			fseek(passeggeri, (numero_utente-1)*sizeof(passeggero), SEEK_SET);
			fread(&utenti, sizeof(passeggero), 1, passeggeri);
			printf("Vecchia data di nascita: %s-%s-%s\n", utenti.datadinascita.giorno,utenti.datadinascita.mese,utenti.datadinascita.anno);
			fclose(passeggeri);

			///Finchè correct è uguale a 1, ciclo.
			while (correct != 1) {
				printf("Immetti il nuovo mese: ");
				scanf("%s", mese_temporaneo);

				/// La funzione ControlloMeseTemporaneo(), restituisce 1 o 0.
				/// Se è 1 (significa che il mese è stato inserito correttamente)
				/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
				correct = ControlloMeseTemporaneo(mese_temporaneo, MAX_MESE);
			}
			correct = 0;

			///Finchè correct è uguale a 1, ciclo.
			while (correct != 1) {
				printf("Immetti il nuovo giorno: ");
				scanf("%s", giorno_temporaneo);

				/// La funzione ControlloGiornoTemporaneo(), restituisce 1 o 0.
				/// Se è 1 (significa che il giorno è stato inserito correttamente)
				/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
				correct = ControlloGiornoTemporaneo(giorno_temporaneo, mese_temporaneo, MAX_GIORNO);
			}
			correct = 0;

			///Finchè correct è uguale a 1, ciclo.
			while (correct != 1) {
				printf("Immetti il nuovo anno: ");
				scanf("%s", anno_temporaneo);

				/// La funzione ControlloAnnoUtente(), restituisce 1 o 0.
				/// Se è 1 (significa che l'anno è stato inserito correttamente)
				/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
				correct = ControlloAnnoTemporaneo(anno_temporaneo, MAX_ANNO);
			}

			///Tramite fseek(), mi posiziono all'utente giusto tramite "numeroutente", dopo di che mi muovo nel
			/// giusto membro (utenti.datadinascita.giorno).
			/// Copio il giorno di nascita immesso in giorno_temporaneo nel membro .datadinascita.giorno della struct.
			/// Infine, scrivo sul file e lo chiudo.
			passeggeri = fopen("passeggeri.dat", "rb+");
			fseek(passeggeri, (numero_utente-1)*sizeof(passeggero) + (((char *) &utenti.datadinascita.giorno) - ((char *) &utenti)), SEEK_SET);
			strcpy(utenti.datadinascita.giorno, giorno_temporaneo);
			fwrite(&utenti.datadinascita.giorno, sizeof(utenti.datadinascita.giorno), 1, passeggeri);
			fclose(passeggeri);

			///Tramite fseek(), mi posiziono all'utente giusto tramite "numeroutente", dopo di che mi muovo nel
			/// giusto membro (utenti.datadinascita.mese).
			/// Copio il mese di nascita immesso in mese_temporaneo nel membro .datadinascita.mese della struct.
			/// Infine, scrivo sul file e lo chiudo.
			passeggeri = fopen("passeggeri.dat", "rb+");
			fseek(passeggeri, (numero_utente-1)*sizeof(passeggero) + (((char *) &utenti.datadinascita.mese) - ((char *) &utenti)), SEEK_SET);
			strcpy(utenti.datadinascita.mese, mese_temporaneo);
			fwrite(&utenti.datadinascita.mese, sizeof(utenti.datadinascita.mese), 1, passeggeri);
			fclose(passeggeri);

			///Tramite fseek(), mi posiziono all'utente giusto tramite "numeroutente", dopo di che mi muovo nel
			/// giusto membro (utenti.datadinascita.anno).
			/// Copio l'anno di nascita immesso in anno_temporaneo nel membro .datadinascita.anno della struct.
			/// Infine, scrivo sul file e lo chiudo.
			passeggeri = fopen("passeggeri.dat", "rb+");
			fseek(passeggeri, (numero_utente-1)*sizeof(passeggero) + (((char *) &utenti.datadinascita.anno) - ((char *) &utenti)), SEEK_SET);
			strcpy(utenti.datadinascita.anno, anno_temporaneo);
			fwrite(&utenti.datadinascita.anno, sizeof(utenti.datadinascita.anno), 1, passeggeri);
			fclose(passeggeri);

			correct = 0;
			break;
		case 5:
			///Tramite fseek(), mostro all'utente il passaporto che intende modificare.
			passeggeri = fopen("passeggeri.dat", "rb");
			fseek(passeggeri, (numero_utente-1)*sizeof(passeggero), SEEK_SET);
			fread(&utenti, sizeof(passeggero), 1, passeggeri);
			printf("Vecchio numero passaporto/carta d'identita': %s\n", utenti.numeropassaporto);
			fclose(passeggeri);

			///Finche correct è diverso da 1, ciclo.
			while (correct != 1) {
				printf("Immetti il nuovo passaporto modificato: ");
				scanf("%s", passaporto_temp);

				/// La funzione ControlloPassaportoTemporaneo(), restituisce 1 o 0.
				/// Se è 1 (significa che il passaporto è stato inserito correttamente)
				/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
				correct = ControlloPassaportoTemporaneo(passaporto_temp, MAX_PASSAPORTO, 1);
			}

			passeggeri = fopen("passeggeri.dat", "rb+");

			///Tramite fseek(), mi posiziono all'utente giusto tramite "numeroutente", dopo di che mi muovo nel
			/// giusto membro (utenti.numeropassaporto).
			fseek(passeggeri, (numero_utente-1)*sizeof(passeggero) + (((char *) &utenti.numeropassaporto) - ((char *) &utenti)), SEEK_SET);

			///Copio il passaporto immesso in passaporto_temp nel membro .numeropassaporto della struct.
			strcpy(utenti.numeropassaporto, passaporto_temp);

			/// Infine, scrivo sul file e lo chiudo.
			fwrite(&utenti.numeropassaporto, sizeof(utenti.numeropassaporto), 1, passeggeri);
			fclose(passeggeri);

			correct = 0;
			break;
		case 6:
			printf("\n\nTramite la modifica di una prenotazione, puoi al massimo modificare il tuo posto per un determinato volo");
			printf("\noppure puoi cancellare una prenotazione gia' effettuata.\n");
			printf("\nSe desideri modificare una prenotazione (ovvero cambiare volo per una prenotazione x)");
			printf("\npuoi semplicemente cancellarla e prenotare nuovamente un volo.\n");
			correct = modificaPrenotazione(passeggeri, numero_utente);
			break;
		case 7:

			///Funzione F03a
			passeggeri = fopen("passeggeri.dat", "rb+");

			///Tramite fseek(), mi posiziono all'utente che ha effettuato il login.
			fseek(passeggeri, (numero_utente-1)*sizeof(passeggero), SEEK_SET);
			fread(&utenti, sizeof(passeggero), 1, passeggeri);

			///Leggendo i suoi dati tramite fread(), copio il suo ID nella variabile
			/// "id_utente_eliminato", che stamperò successivamente.
			id_utente_eliminato = utenti.id;
			fclose(passeggeri);

			///Tramite fseek(), mi posiziono all'utente che ha effettuato il login.
			passeggeri = fopen("passeggeri.dat", "rb+");
			fseek(passeggeri, (numero_utente-1)*sizeof(passeggero), SEEK_SET);

			///Resetto a 0 tutti i membri della struct passeggero.
			memset(&utenti, 0, sizeof(utenti));
			utenti.id = 0;
			printf("\nL'utente %d e' stato cancellato con successo!\n", id_utente_eliminato);

			/// Infine, scrivo sul file e lo chiudo.
			fwrite(&utenti, sizeof(passeggero), 1, passeggeri);
			fclose(passeggeri);
			break;
		case 8:
			///Apro il file in sola lettura.
			passeggeri = fopen("passeggeri.dat", "rb");

			///Mi posizione tramite fseek(), all'utente che ha effettuato il login.
			fseek(passeggeri, (numero_utente-1)*sizeof(passeggero), SEEK_SET);
			fread(&utenti, sizeof(passeggero), 1, passeggeri);

			///Controllo che l'utente non sia stato eliminato, verificando se l'ID è diverso da 0
			/// e verificando che all'interno del vettore nome, ci sia qualcosa di diverso dal
			/// carattere nullo
			if (utenti.id != 0 && utenti.nome[0] != '\0') {
				///Stampa dell'utente
				printf("\nUTENTE %d ------> %s %s - Nato il %s-%s-%s a %s | NUMERO PASSAPORTO: %s\n",utenti.id, utenti.nome,
						utenti.cognome, utenti.datadinascita.giorno, utenti.datadinascita.mese, utenti.datadinascita.anno,
						utenti.luogodinascita, utenti.numeropassaporto);

				///Finche correct3 è diverso da 1, ciclo.
				while (correct3 != 1) {

					///Trasformo in interi l'orario di arrivo e l'orario di partenza della prenotazione[num]
					/// contenuta nella struct passeggero.
					ora_arrivo = atoi(utenti.p[num].elenco.ora_arrivo);
					ora_partenza = atoi(utenti.p[num].elenco.ora_partenza);

					///Per verificare se un utente ha una prenotazione disponibile, controllo se
					/// l'orario di arrivo (Es. 18), precedentemente convertito in intero,
					/// è minore di MAX_ORA_VOLO (23). Verifico la stessa cosa per l'orario di partenza.
					/// Se le due condizioni combaciano, allora significa che nel vettore p[num], esiste una prenotazione,
					/// quindi la stampo.
					if ((ora_arrivo < MAX_ORA_VOLO) && (ora_partenza > MIN_ORA_VOLO)) {
						printf("\nHai un volo disponibile:\n");
						printf("Volerai da %s a %s il %2s-%2s-%4s.", utenti.p[num].elenco.tratta_partenza, utenti.p[num].elenco.tratta_arrivo, utenti.p[num].elenco.datadivolo.giorno,
								utenti.p[num].elenco.datadivolo.mese, utenti.p[num].elenco.datadivolo.anno);
						printf("\nPartenza ore: %2s:%2s", utenti.p[num].elenco.ora_partenza, utenti.p[num].elenco.minuti_partenza);
						printf("\nArrivo ore: %2s:%2s", utenti.p[num].elenco.ora_arrivo, utenti.p[num].elenco.minuti_arrivo);
						printf("\nDurata del volo: %s min.", utenti.p[num].elenco.durata);
						printf("\nCodice prenotazione: %s", utenti.p[num].codice_prenotazione);

						///Controllo se l'utente ha effettuato il check-in per questa prenotazione
						/// tramite un flag che sarà uguale ad 1 solo nel caso in cui l'utente
						/// effettua il check-in.
						if (utenti.p[num].controllo_checkin == 1) {
							printf("\nCHECK-IN EFFETTUATO PER QUESTO VOLO.");
							printf("\nPosto: %d", utenti.p[num].posto);
						}
						else {
							printf("\nCHECK-IN NON EFFETTUATO PER QUESTO VOLO.");
						}
						printf("\n--------------------------------------------------------------");
						///Passo alla prossima prenotazione. Se prima p[num], era p[0], ora sarà p[1].
						/// In questo caso ricontrollo se l'utente ha un'altra prenotazione.
						num++;
					}
					else {
						/// Esco subito dal ciclo non appena l'algoritmo non trova una prenotazione disponibile.
						correct3 = 1;
					}
				}
			}
			else {
				printf("\nL'utente e' stato eliminato, quindi non posso leggere le sue informazioni!\n");
			}
		fclose(passeggeri);

		///Inizializzo il vettore usato per la ricerca e tutte le altre variabili
		/// per una eventuale nuova ricerca.
		correct3 = 0;
		ora_arrivo = 0;
		ora_partenza = 0;
		num = 0;
		break;
		case 9:
			///Chiamata alla funzione che mi porta al menu precedente (menu utente).
			mostraMenu();
			break;
		case 10: ///Rendo vero il valore della while e termino il programma con exit(0).
			s = 1;
			exit(0);
			break;
		default: ///Qui ricadranno tutti i valori non corretti. (caratteri e num > 9).
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
			printf("\nValore non corretto.");
			break;
		}
	}
	fclose(passeggeri);
	return 1;
}

/**
 * La funzione, tramite un algoritmo di ordinamento,
 * ordina per nome tutti i passeggeri registrati
 * nel sistema.
 * La funzione ha codice F13.
 *
 * @param passeggeri File dei passeggeri
 */
int ordinamentoUtenti(FILE *passeggeri) {

	///Se il file non esiste, stampa un messaggio di errore.
	if( (passeggeri = fopen("passeggeri.dat", "rb+") ) == NULL) {
		printf("Errore nell'apertura.");
		return 0;
	}
	else {

		/**
		 * Numero di utenti presenti nel sistema
		 */
		int numero_utenti = 0;

		/**
		 * Struct passeggero
		 */
		passeggero utenti;

		///Conto quanti utenti ci sono nel file, per poter allocare la memoria giusta.
		passeggeri = fopen("passeggeri.dat", "ab+");

		fseek(passeggeri, (-1)*sizeof(passeggero), SEEK_END);
		fread(&utenti, sizeof(passeggero), 1, passeggeri);

		///Salvo l'ultimo ID dell'utente in una variabile, per poi poter allocare la memoria giusta
		numero_utenti = utenti.id;

		fclose(passeggeri);

		///Sorting
		passeggeri = fopen("passeggeri.dat", "rb");

		///Funzione compare2(). Consulta la documentazione.
		int compare2(const void *a, const void *b) {
		    return strncmp((const char *)a, (const char *)b, 20);
		}

		/**
		 * Vettore dinamico degli utenti.
		 * E' grande tanto quanti sono gli utenti
		 */
		passeggero *listautenti = malloc(numero_utenti * sizeof *listautenti);

		fread(listautenti, sizeof *listautenti, numero_utenti, passeggeri);

		///Funzione qsort(). Mi ordina il vettore precedentemente dichiarato
		/// per nome utenti, in ordine alfabetico.
		qsort(listautenti, numero_utenti, sizeof(passeggero), compare2);

		fclose(passeggeri);
		///Fine Sorting

		///Stampa gli utenti ordinati
		for (int i = 0; i < numero_utenti; i++) {
			if (listautenti[i].nome[0] != '\0') {
			printf("\nUTENTE %d ------> %s %s - Nato il %s-%s-%s a %s | NUMERO PASSAPORTO: %s\n",listautenti[i].id, listautenti[i].nome,
					listautenti[i].cognome, listautenti[i].datadinascita.giorno, listautenti[i].datadinascita.mese, listautenti[i].datadinascita.anno,
					listautenti[i].luogodinascita, listautenti[i].numeropassaporto);
			}
		}

		return 1;
	}
}

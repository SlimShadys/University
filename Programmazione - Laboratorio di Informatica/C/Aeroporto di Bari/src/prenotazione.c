/**
 * @file prenotazione.c
 *
 * Questo file contiene le implementazioni dei prototipi
 * dichiarati nel file prenotazione.h
 * @version 1
 * @date 13/05/2019
 * @authors Gianmarco Scarano
 */

/// Librerie necessarie per il corretto funzionamento del programma.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "prenotazione.h"
#include "passeggero.h"
#include "volo.h"
#include "menu.h"
#include "controlli.h"

/**
 * La funzione, chiede il login all'utente. Successivamente
 * chiede quale volo prenotare e lo assegna all'utente,
 * fornendogli un codice prenotazione.
 * La funzione ha codice F06
 *
 * @pre La funzione richiede che il file dei voli e passeggeri, esistano.
 *
 * @post La funzione può far ritornare l'utente al menù, dopo aver sbagliato
 * 		 tre volte la prenotazione del volo (l'utente sbaglia se immette
 * 		 un volo già prenotato). Se l'utente sceglie un volo non prenotato,
 * 		 allora la funzione procede con la prenotazione.
 */
int prenotaVolo (FILE *voli, FILE *passeggeri) {

	/**
	 * Struct dei voli
	 */
	volo elenco;

	/**
	 * Struct dei passeggeri
	 */
	passeggero utenti;

	voli = NULL;
	passeggeri = NULL;

	/**
	 * Variabile che userò per immagazzinare l'ID
	 * dell'utente da modificare.
	 */
	char numeroutente[3] = "\0";

	/**
	 * Variabile che userò per immagazzinare l'ID
	 * dell'utente da modificare.
	 */
	char numerovolo[2] = "\0";

	/// Serie di variabili contatori che mi serviranno
	/// per uscire dai cicli se il dato richiesto è giusto.
	int correct = 0;
	int correct2 = 0;
	int correct3 = 0;
	int correct4 = 0;
	int correct5 = 0;

	/**
	 * Valore che indica se una prenotazione è già stata
	 * effettuata o meno.
	 */
	int pren_busy = 0;

	/**
	 * Contatore che mi permette di ritornare al menu
	 * una volta arrivato a 0.
	 */
	int wrong = 3;

	/**
	 * Contatore che, nel caso arrivi a 10, significa
	 * che l'utente ha tutte le prenotazioni piene
	 */
	int max_pren_raggiunte = 0;

	/**
	 * Variabile per trovare la giusta posizione nel
	 * vettore "prenotazione" dentro la struct passeggero.
	 */
	int num = 0;

	/**
	 * Variabile che immagazzinerà la scelta del volo.
	 */
	int id_volo = 0;

	/**
	 * Variabile che userò per convertire l'ID dell'utente
	 * da char a int.
	 */
	int numero_utente = 0;

	///Ricavo l'ID dell'ultimo utente tramite la funzione ID_Utente()
	/// e lo immagazzino nella variabile "id", la quale mi servirà
	/// successivamente.
	int id = ID_Utente();

	/**
	 * Vettore su cui memorizzare il passaporto da confrontare
	 * con quello dell'utente, al momento del login.
	 */
	char passaporto_temp[MAX_PASSAPORTO+1];

	/**
	 * Variabile che userò per convertire l'ID del volo
	 * da char a int.
	 */
	int scelta = 0;

	///Finchè correct è diverso da 1, cicla.
	while (correct != 1) {
		if( (passeggeri = fopen("passeggeri.dat", "rb+") ) == NULL) {
			printf("Errore nell'apertura.");
			return 0;
			correct = 1;
		}
		else
		{
			///Finchè correct5 è diverso da 1, cicla.
			while (correct5 != 1) {
				printf("\nQuale e' il tuo numero utente?");
				printf("\nNUMERO UTENTE: ");
				scanf("%s", numeroutente);

				///Trasformo in intero l'ID immesso precedentemente
				numero_utente = atoi(numeroutente);

				///Se l'utente ha immesso un ID uguale a 0 oppure se il
				/// "numero_utente" > della variabile "id" (Che contiene l'ID
				/// dell'ultimo utente), allora stampa un errore.
				if (numero_utente > id || numero_utente == 0) {
					printf("\nHai immesso un numero utente inesistente. L'ultimo utente ha ID %d\n", id);
					strcpy (numeroutente, "\0"); ///Resetto il vettore dell'ID immesso dall'utente.

				///Tramite isalpha() controllo se sono stati inseriti due caratteri alfabetici.
				} else if (isalpha(numeroutente[0]) || isalpha(numeroutente[1])) {
					printf("\nHai immesso un carattere.");
				} else {
					correct5 = 1; ///Esco dal ciclo, se l'input è corretto.
				}
			}

			///Attraverso la fseek(), mi sposto all'utente scelto tramite numero_utente
			fseek(passeggeri, (numero_utente-1)*sizeof(passeggero), SEEK_SET);
			fread(&utenti, sizeof(passeggero), 1, passeggeri);
			printf("\n---- Benvenuto %s %s! ----", utenti.nome, utenti.cognome);
			correct = 1;

			///Finchè correct2 è diverso da 1, cicla.
			while (correct2 != 1) {
				printf("\n---- Si prega di confermare l'identità ----\n");
				printf("\nNUMERO PASSAPORTO: ");

				scanf("%s", passaporto_temp);

				/// La funzione ControlloPassaportoTemporaneo(), restituisce 1 o 0.
				/// Se è 1 (significa che il passaporto è stato inserito correttamente)
				/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
				correct2 = ControlloPassaportoTemporaneo(passaporto_temp, MAX_PASSAPORTO, 0);

				///Le prime due lettere del passaporto devono essere maiuscole
				/// Es. AA1234567
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
				}
				///Resetto il vettore del passaporto temporaneo e
				/// riporto correct2 a 0, altrimenti non entrerà
				/// nella while del correct2.
				else {
					printf ("\nPassaporto errato. Riprovare.\n\n");
					correct2 = 0;
					passaporto_temp[0] = '\0';
				}
			}
		}
	}

	///Scorro tutto il vettore delle prenotazioni e controllo se il codice volo
	/// per la prenotazione [i], sia diverso dal carattere nullo.
	/// Nel caso in cui sia diverso dal carattere nullo (ovvero che il codice
	/// volo esiste), allora aumento il contatore delle prenotazioni.
	for (int i = 0; i < MAX_PRENOTAZIONI; i++) {
		///Confronto tra codice volo e carattere nullo
		if (utenti.p[i].elenco.codice_volo[0] != '\0') {
			max_pren_raggiunte++;
		}
	}

	///Nella if ci entrerò solamente quando le prenotazioni sono uguali a 10.
	/// Se la if è verificata significa che l'utente ha tutte le prenotazioni
	/// già occupate, quindi esco con return 0.
	if (max_pren_raggiunte == 10) {
		printf("\nHai raggiunto il limite delle prenotazioni disponibili!\n");
		return 0;
	}

	if( (voli = fopen("voli.dat", "rb") ) == NULL) {
		printf("Errore nell'apertura.");
	}
	else {
		///Leggo fino alla fine del file
		while( !(feof(voli)))
		{
			/// Quando read arriva a 0, significa che il file è finito.
			int read = fread(&elenco, sizeof(volo), 1, voli);

			if ( read > 0) {
				///Stampo i voli solamente se il codice_volo è diverso da 0 e
				/// il nome della compagnia non ha un nome pari a NULL.
				if (elenco.codice_volo[0] != '\0' && elenco.nomecompagnia[0] != '\0') {
					printf("---- V O L O    N U M E R O    %d ----\n", elenco.id);
					printf("Codice volo: %s\nNome compagnia: %s\nPARTENZA DA: %s\nARRIVO A: %s\nCodice aereo: %s\nData del volo: %2s-%2s-%4s\n"
							"Orario partenza: %2s:%2s\nOrario arrivo: %2s:%2s\nDurata del volo: %3s min.\n\n",
							elenco.codice_volo, elenco.nomecompagnia, elenco.tratta_partenza,
							elenco.tratta_arrivo, elenco.modello_aereo, elenco.datadivolo.giorno,
							elenco.datadivolo.mese, elenco.datadivolo.anno, elenco.ora_partenza,
							elenco.minuti_partenza,elenco.ora_arrivo,elenco.minuti_arrivo, elenco.durata);
					id_volo = elenco.id;
				}
			}
		}

		printf("Questi sono i voli disponibili.\n");

		///Finchè correct4 è diverso da 1, ciclo.
		while (correct4 != 1) {
			pren_busy = 0;
			printf("Quale volo vuoi scegliere?\n");
			printf("LA TUA SCELTA: ");
			scanf("%s", numerovolo);

			///Trasformo in intero l'ID volo immesso precedentemente
			scelta = atoi(numerovolo);

			///Tramite fseek(), mi posiziono al volo giusto.
			fseek(voli, (scelta-1)*sizeof(volo), SEEK_SET);
			fread(&elenco, sizeof(volo), 1, voli);

			///Controllo che la scelta dell'utente sia giusta
			/// Es. - Ci sono 6 voli, l'utente sceglie il volo numero 7
			/// In quel caso, stampo errore.
			if (scelta <= id_volo) {
				if (elenco.codice_volo[0] != '\0') {
				printf("\nHAI SCELTO QUESTO VOLO:\n");
				printf("VOLO %d : ", scelta);
				printf("\nCodice volo: %s\nNome compagnia: %s\nPARTENZA DA: %s\nARRIVO A: %s\nCodice aereo: %s\nGiorno del volo: %2s\nMese del volo: %2s\n"
						"Anno del volo: %4s\nOrario partenza: %2s:%2s\nOrario arrivo: %2s:%2s\nDurata del volo: %3s min.\n\n",
						elenco.codice_volo, elenco.nomecompagnia, elenco.tratta_partenza,
						elenco.tratta_arrivo, elenco.modello_aereo, elenco.datadivolo.giorno,
						elenco.datadivolo.mese, elenco.datadivolo.anno, elenco.ora_partenza,
						elenco.minuti_partenza,elenco.ora_arrivo,elenco.minuti_arrivo, elenco.durata);
				}
			}

			fclose(passeggeri);

			passeggeri = fopen("passeggeri.dat", "rb+");

			///Se l'utente sceglie un volo che non esiste oppure digita 0, stampa errore e ripeti il processo.
			if (scelta > id_volo || scelta == 0) {
				printf("\n\nHai immesso una scelta non valida! I voli sono al massimo %d!\n\n", id_volo);
				numerovolo[0] = '\0';
			}
			if (elenco.codice_volo[0] == '\0') {
				printf("\nHai scelto un volo cancellato!\n\n");
				numerovolo[0] = '\0';
			}
			else {
				///Scorro il vettore delle prenotazioni dell'utente.
				/// Se trovo che il codice_volo del volo scelto precedentemente, coincide
				/// con un codice volo presente nelle 15 prenotazioni dell'utente,
				/// allora stampo un messaggio di errore
				for (int i = 0; i < MAX_PRENOTAZIONI; i++) {
					if (!strcmp(elenco.codice_volo,utenti.p[i].elenco.codice_volo)) {
						printf("Hai gia' una prenotazione per questo volo!\n");
						pren_busy++; ///Aumento il contatore delle prenotazioni già effettuate.
						wrong--; ///All'inizio wrong sarà uguale a 3.
						///Quando wrong raggiungerà 0, allora mostrerò il menu.
					}
				}

				///Stampo le rimanenti possibilità dell'utente
				if ((wrong < 3) && (wrong > 0) && pren_busy > 0) {
					printf("\nHai ancora %d possibilità, poi sarai rimandato al menu'.\n\n", wrong);
				}
				///Quando wrong raggiunge 0, rimando l'utente al menù.
				if (wrong == 0) {
					mostraMenu();
				}

				///Se nel caso non c'è nessuna prenotazione già effettuata per un volo x, allora procedo
				/// nel trovare un indice di prenotazione (p.[num]) disponibile su cui scrivere la prenotazione stessa.
				if (pren_busy == 0) {

					///Finchè correct3 è diverso da 1, cicla.
					while (correct3 != 1) {

						///Trasformo in interi l'orario di arrivo e l'orario di partenza della prenotazione[num]
						/// contenuta nella struct passeggero.
						int ora_arrivo = atoi(utenti.p[num].elenco.ora_arrivo);
						int ora_partenza = atoi(utenti.p[num].elenco.ora_partenza);

						///Per verificare se un utente ha una prenotazione disponibile, controllo se
						/// l'orario di arrivo (Es. 18), precedentemente convertito in intero,
						/// è minore di MAX_ORA_VOLO (23). Verifico la stessa cosa per l'orario di partenza.
						/// Se le due condizioni combaciano, allora significa che nel vettore p[num], esiste una prenotazione,
						/// quindi aumento la variabile "num" e ripeto il processo.
						if ((ora_arrivo < MAX_ORA_VOLO) && (ora_partenza > MIN_ORA_VOLO)) {
							num++;
						}
						else {
							///Alla fine troverò un "num" disponibile, e uscirò dai 2 cicli,
							correct3 = 1;
							correct4 = 1;
						}
					}
				}
			}
		}
	}

	///Mi sposto, tramite fseek(), all'utente giusto e tramite l'offset, anche al membro giusto (in questo caso "elenco",
	/// poichè devo scrivere l'intero volo nel vettore di prenotazioni). Poi lo scrivo su file.
	fseek(passeggeri, (numero_utente-1)*sizeof(passeggero) + (((char *) &utenti.p[num].elenco) - ((char *) &utenti)), SEEK_SET);
	fwrite(&elenco, sizeof(elenco), 1, passeggeri);

	///Chiudo entrambi i file
	fclose(passeggeri);
	fclose(voli);

	passeggeri = fopen("passeggeri.dat", "rb+");
	///Mi sposto, tramite fseek(), all'utente giusto e tramite l'offset, anche al membro giusto (in questo caso "codice_prenotazione").
	fseek(passeggeri, (numero_utente-1)*sizeof(passeggero) + (((char *) &utenti.p[num].codice_prenotazione) - ((char *) &utenti)), SEEK_SET);

	///Genero un codice prenotazione e lo copio nel membro codice_prenotazione.
	strcpy(utenti.p[num].codice_prenotazione, GeneraCodicePrenotazione());
	printf("Questo e' il tuo codice prenotazione per questo volo: %s\n", utenti.p[num].codice_prenotazione);

	///Scrivo solamente il vettore delle prenotazioni, precisamente solo il membro "codice_prenotazione".
	fwrite(&utenti.p[num].codice_prenotazione, sizeof(utenti.p[num].codice_prenotazione), 1, passeggeri);

	///Chiudo tutti i file aperti.
	fclose(passeggeri);
	fclose(passeggeri);

	return 1;
}

/**
 * La funzione, dopo un login valido da parte dell'utente,
 * chiede un codice prenotazione. Essa è capace di verificare se quel
 * codice prenotazione esiste o meno. Se esiste, procede con l'assegnazione
 * di un posto per quel volo. Se non esiste, richiede un nuovo codice.
 * La funzione ha codice F09
 *
 * @pre La funzione richiede che il file dei voli e passeggeri, esistano.
 *
 * @post La funzione può far ritornare l'utente al menù, dopo aver sbagliato
 * 		 tre volte il codice prenotazione. Se l'utente inserisce un codice
 * 		 prenotazione valido, allora procede con l'assegnazione di un posto.
 */
int checkin(FILE *voli, FILE *passeggeri) {

	/**
	 * Struct volo
	 */
	volo elenco;

	/**
	 * Struct passeggero
	 */
	passeggero utenti;

	/**
	 * Variabile che userò per immagazzinare l'ID
	 * dell'utente da modificare.
	 */
	char numeroutente[3] = "\0";

	/// Serie di variabili contatori che mi serviranno
	/// per uscire dai cicli se il dato richiesto è giusto.
	int correct = 0;
	int correct1 = 0;
	int correct2 = 0;
	int correct3 = 0;
	int correct4 = 0;
	int correct5 = 0;

	/**
	 * Variabile che userò per convertire l'ID dell'utente
	 * da char a int.
	 */
	int numero_utente = 0;

	///Ricavo l'ID dell'ultimo utente tramite la funzione ID_Utente()
	/// e lo immagazzino nella variabile "id", la quale mi servirà
	/// successivamente.
	int id = ID_Utente();

	/**
	 * Variabile che servirà a dire se il codice di prenotazione
	 * esiste.
	 */
	int found = 0;

	/**
	 * Variabile che servirà a dire se il codice di prenotazione
	 * non esiste.
	 */
	int notfound = 0;

	/**
	 * Variabile che mi servirà a contenere il posto per l'utente
	 */
	int randomposto = 0;

	/**
	 * Variabile per trovare la giusta posizione nel
	 * vettore "prenotazione" dentro la struct passeggero.
	 */
	int num = 0;

	/**
	 * Variabile che conterrà la giusta posizione nel
	 * vettore "prenotazione" dentro la struct passeggero.
	 */
	int codice = 0;

	/**
	 * Contatore che mi conta quanti posti sono stati
	 * occupati. Se il contatore arriva a 150, significa
	 * che tutti gli utenti si sono imbarcati.
	 */
	int contatore_posti = 0;

	/**
	 * Vettore su cui memorizzare il passaporto immesso
	 * dall'utente al momento del login.
	 */
	char passaporto_temp[MAX_PASSAPORTO+1];

	/**
	 * Vettore su cui memorizzare il codice prenotazione immesso
	 * dall'utente al momento del login.
	 */
	char codice_prenotazione_temp[MAX_CODICE_PRENOTAZIONE+1];

	while (correct != 1) {
		if( (passeggeri = fopen("passeggeri.dat", "rb+") ) == NULL) {
			printf("Errore nell'apertura.");
			correct = 1;
			return 0;
		}
		else
		{
			///Finchè correct1 non è uguale a 1, ciclo.
			while (correct1 != 1) {
				printf("\nQuale e' il tuo numero utente?");
				printf("\nNUMERO UTENTE: ");
				scanf("%s", numeroutente);

				///Trasformo in intero l'ID immesso precedentemente
				numero_utente = atoi(numeroutente);

				///Se l'utente ha immesso un ID uguale a 0 oppure se il
				/// "numero_utente" > della variabile "id" (Che contiene l'ID
				/// dell'ultimo utente), allora stampa un errore.
				if (numero_utente > id || numero_utente == 0) {
					printf("\nHai immesso un numero utente inesistente. L'ultimo utente ha ID %d\n", id);
					strcpy (numeroutente, "\0"); ///Resetto il vettore dell'ID immesso dall'utente.

				///Tramite isalpha() controllo se sono stati inseriti due caratteri alfabetici.
				} else if (isalpha(numeroutente[0]) || isalpha(numeroutente[1])) {
					printf("\nHai immesso un carattere.");
				} else {

					fseek(passeggeri, (numero_utente-1)*sizeof(passeggero), SEEK_SET);
					fread(&utenti, sizeof(passeggero), 1, passeggeri);
					printf("\n---- Benvenuto %s %s! ----", utenti.nome, utenti.cognome);

					///Finchè correct2 è diverso da 1, ciclo
					while (correct2 != 1) {
						printf("\n---- Si prega di confermare l'identità ----\n");
						printf("\nNUMERO PASSAPORTO: ");

						scanf("%s", passaporto_temp);

						/// La funzione ControlloPassaportoTemporaneo(), restituisce 1 o 0.
						/// Se è 1 (significa che il passaporto è stato inserito correttamente)
						/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
						correct2 = ControlloPassaportoTemporaneo(passaporto_temp, MAX_PASSAPORTO, 0);

						///Le prime due lettere del passaporto devono essere maiuscole
						/// Es. AA1234567
						passaporto_temp[0] = toupper(passaporto_temp[0]);
						passaporto_temp[1] = toupper(passaporto_temp[1]);
					}

					if (correct2 == 1) {
						///Confronto il passaporto precedentemente immesso con
						/// il passaporto dell'utente pescato con la fseek(),
						/// sempre precedentemente.
						if(!strcmp(passaporto_temp,utenti.numeropassaporto)) {
							printf("\nPassaporto inserito correttamente!\n\n");
							correct3 = 1; ///Necessario per una if successiva.
						}
						else {
							///Se entro nell'else, il passaporto non coincide.
							printf ("\nPassaporto errato. Riprovare.\n\n");
							correct2 = 0; ///Resetto correct2, altrimenti non entro
							 	 	 	 /// nel ciclo di input del passaporto.
						}
					}

					///Se il passaporto coincide, allora vado avanti con il codice prenotazione.
					if (correct3 == 1) {
						correct4 = 0;
						while (correct4 != 1) {
							printf("\n---- Immettere codice prenotazione volo ----\n");
							printf("\nCODICE PRENOTAZIONE: ");

							scanf("%s", codice_prenotazione_temp);

							/// La funzione ControlloCodicePrenotazione(), restituisce 1 o 0.
							/// Se è 1 (significa che il codice è stato inserito correttamente)
							/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
							correct5 = ControlloCodicePrenotazione(codice_prenotazione_temp, MAX_CODICE_PRENOTAZIONE);

							///Le prime due lettere del codice prenotazione devono essere maiuscole.
							/// Es. AA123
							codice_prenotazione_temp[0] = toupper(codice_prenotazione_temp[0]);
							codice_prenotazione_temp[1] = toupper(codice_prenotazione_temp[1]);

							///Se il codice è stato correttamente inserito, vado avanti.
							if (correct5 == 1) {

								///Scorro tutto il vettore delle prenotazione dell'utente
								for (num = 0; num < MAX_PRENOTAZIONI; num++) {

									///Controllo se il codice inserito precedentemente coincide con almeno
									/// uno presente nel vettore di prenotazioni dell'utente.
									if(!strcmp(codice_prenotazione_temp,utenti.p[num].codice_prenotazione)) {
										printf("\nCodice prenotazione inserito correttamente!\n\n");
										codice = num; ///Se coincide, copio la giusta posizione del vettore prenotazione
										 	 	 	  ///in una variabile chiamata "codice", che userò successivamente.
										found++; ///Aumento il contatore dei "trovati".
									}
									else {
										notfound++; ///Se al primo for non trovo il codice prenotazione richiesto,
										 	 	 	/// aumento il contatore dei "non trovati". Ciclo così per tutto
										 	 	 	/// il for.
									}
								}

								///Se ha trovato almeno una corrispondenza, allora procedo a vedere se l'utente ha
								/// già effettuato questo check-in tramite un flag che diventa 1 al momento della
								/// prenotazione.
								/// Uso "codice" come indice del vettore, perchè quando trovo l'occorrenza, copio "num" in "codice".
								if (found > 0) {
									if (utenti.p[codice].controllo_checkin == 1) {
										printf("\nHai già effettuato il check-in per questa prenotazione!");
										printf("\nImmettere nuovamente i dati.\n");
										///Resetto tutte le variabili dei vari cicli e resetto
										/// i vettori temporanei.
										correct2 = 0;
										correct3 = 0;
										correct4 = 1;
										correct5 = 0;
										notfound = 0;
										found = 0;
										passaporto_temp[0] = '\0';
										codice_prenotazione_temp[0] = '\0';
									}
									else {
										///Il check-in è andato a buon fine, quindi esco da tutti i cicli
										/// e proseguo con l'assegnamento del posto.
										correct = 1;
										correct4 = 1;
										correct1 = 1;
									}
								}

								///Qui ci entrerò solamente se il contatore dei "non trovati" è uguale al
								/// massimo di prenotazioni disponibili. Significa che non esiste un
								/// codice prenotazione tale.
								if (notfound >= MAX_PRENOTAZIONI) {
									printf ("\nCodice prenotazione non trovato. Riprovare.\n\n");
									///Resetto tutte le variabili dei vari cicli e resetto
									/// i vettori temporanei.
									correct2 = 0;
									correct3 = 0;
									correct4 = 1;
									correct5 = 0;
									notfound = 0;
									found = 0;
									passaporto_temp[0] = '\0';
									codice_prenotazione_temp[0] = '\0';
								}
							}
						}
					}
				}
			}
		}

		///Tramite fseek(), mi sposto al giusto utente e sempre tramite offset, mi sposto al membro giusto (in questo
		/// caso è p[codice].elenco.posti) per poter scrivere il posto e l'effettiva riuscita del check-in.
		passeggeri = fopen("passeggeri.dat", "rb+");
		fseek(passeggeri, (numero_utente-1)*sizeof(passeggero) + (((char *) &utenti.p[codice].elenco.posti) - ((char *) &utenti)), SEEK_SET);

		correct4 = 0;

		voli = fopen("voli.dat", "rb+");

		///Finchè correct4 è diverso da 1, ciclo.
		while (correct4 != 1) {

			/**
			 * Variabile per leggere tutto il file
			 */
			int read = 1;

			while( read != 0 )
			{
				/// Quando read arriva a 0, significa che il file è finito.
				read = fread(&elenco, sizeof(volo), 1, voli);

				if ( read > 0) {

					///Confronto il codice volo della prenotazione, con il codice volo di tutti i voli presenti nel sistema.
					/// Dato che il codice volo è unico, una volta trovata la coincidenza, andrò ad inserire un posto
					/// random per quel volo e lo occuperò tramite funzione booleana.
					if(!strcmp(utenti.p[codice].elenco.codice_volo, elenco.codice_volo)) {

						if (elenco.chiusura_checkin == 1) {
							printf("\nIl check-in per questo volo e' stato già chiuso!\n");
							return 0;
						}

						///Genere un numero random da 0 a 150.
						randomposto = rand() % MAX_POSTI;

						///Finchè quel posto è uguale ad 1 (significa che è stato già preso), cicla.
						while (elenco.posti[randomposto] == 1) {
							randomposto = rand() % MAX_POSTI;
						}

						///Occupo il posto per questo utente ed esco dal ciclo.
							utenti.p[codice].elenco.posti[randomposto] = 1;

							elenco.posti[randomposto] = 1;

							///Tramite fseek(), mi posiziono al volo giusto tramite "elenco.id", dopo di che mi muovo nel
							/// giusto membro (elenco.posti).
							fseek(voli, (elenco.id-1)*sizeof(volo) + (((char *) &elenco.posti) - ((char *) &elenco)), SEEK_SET);

							fwrite(&elenco.posti, sizeof(elenco.posti), 1, voli);

							///Controllo, scorrendo il vettore, se tutti i posti sono stati presi
							for (int i = 0; i < MAX_POSTI; i++) {
								if (elenco.posti[i] == 1) {
									contatore_posti++;
								}
							}

							/// Se contatore_posti arriva a 150 (MAX_POSTI), allora
							/// tutti gli utenti per quel volo, hanno effettuato il check-in.
							if (contatore_posti == 150) {
								printf("\nL'imbarco per il volo %s e' concluso. Tutti i passeggeri hanno effettuato il check-in.\n", elenco.codice_volo);
							}

							///Una volta aggiornato il file, lo chiudo
							fclose(voli);
							correct4 = 1; ///Esco dal ciclo
						}
					}
				}
			}

		printf("Questo e' il tuo posto per questo volo: %d\n", randomposto);

		///Scrivo il posto dell'utente su file
		fwrite(&utenti.p[codice].elenco.posti, sizeof(utenti.p[codice].elenco.posti), 1, passeggeri);
		fclose(passeggeri);

		passeggeri = fopen("passeggeri.dat", "rb+");

		///Tramite fseek(), mi sposto al giusto utente e sempre tramite offset, mi sposto al membro giusto (in questo
		/// caso è p[codice].posto) per poter scrivere il posto assegnato all'utente.
		fseek(passeggeri, (numero_utente-1)*sizeof(passeggero) + (((char *) &utenti.p[codice].posto) - ((char *) &utenti)), SEEK_SET);

		utenti.p[codice].posto = randomposto; ///Copio il posto generato nella variabile posto, all'interno del vettore prenotazione.
		///Scrivo su file e chiudo.
		fwrite(&utenti.p[codice].posto, sizeof(utenti.p[codice].posto), 1, passeggeri);
		fclose(passeggeri);

		passeggeri = fopen("passeggeri.dat", "rb+");

		///Tramite fseek(), mi sposto al giusto utente e sempre tramite offset, mi sposto al membro giusto (in questo
		/// caso è p[codice].controllo_checkin) per poter constatare l'effettivo check-in.
		fseek(passeggeri, (numero_utente-1)*sizeof(passeggero) + (((char *) &utenti.p[codice].controllo_checkin) - ((char *) &utenti)), SEEK_SET);

		///Gli assegno 1, in modo tale che nel caso in cui l'utente dovesse
		/// rifare il check-in, non gli sarà permesso dato che il controllo
		/// del check-in per questa prenotazione è impostato ad 1.
		utenti.p[codice].controllo_checkin = 1;
		fwrite(&utenti.p[codice].controllo_checkin, sizeof(utenti.p[codice].controllo_checkin), 1, passeggeri);
		fclose(passeggeri);

	}

	return 1;
}

/**
 * La funzione, la quale non ha bisogno di un login (dato che ha come
 * parametro di input l'ID dell'utente), chiede un codice prenotazione.
 * Essa è capace di verificare se quel codice prenotazione esiste o meno.
 * Se esiste, procede con la modifica del posto (qui, ulteriori controlli
 * su un posto già assegnato sono implementati) per quella prenotazione
 * o può addirittura cancellare la prenotazione stessa.
 * La funzione ha codice F07
 *
 * @pre La funzione richiede che il file dei passeggeri, esista.
 *
 * @post La funzione può modificare/cancellare una prenotazione con successo
 * 		 se il codice prenotazione esiste. Se l'utente inserisce un codice
 * 		 prenotazione non valido, l'algoritmo lo segnalerà.
 */
int modificaPrenotazione(FILE *passeggeri, int id_utente) {

	/**
	 * Struct passeggero
	 */
	passeggero utenti;

	/**
	 * Struct volo
	 */
	volo elenco;

	/**
	 * Dichiaro una variabile di tipo file, che mi servirà
	 * per i voli.
	 */
	FILE *voli = NULL;

	/**
	 * Contatore che mi permetterà di uscire dal ciclo while.
	 */
	unsigned short int s = 0;

	/**
	 * Variabile equivalente ad una carattere "barra spaziatrice".
	 */
	char *barra_spaziatrice = " ";

	/**
	 * Variabile equivalente al carattere "new line", ovvero "invio".
	 */
	char *new_line = "\n";

	/**
	 * Variabile dove memorizzare quanti "spazi" ci sono in una stringa.
	 */
	int spazio = 0;

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
	 * Immagazzino cosa l'utente ha scelto in questa variabile
	 */
	unsigned short int scelta_utente = 0;

	/// Serie di variabili contatori che mi serviranno
	/// per uscire dai cicli se il dato richiesto è giusto.
	int correct = 0;
	int correct2 = 0;
	int correct3 = 0;
	int correct4 = 0;

	/**
	 * Vettore su cui memorizzare il codice prenotazione immesso
	 * dall'utente al momento del login.
	 */
	char codice_prenotazione_temp[MAX_CODICE_PRENOTAZIONE+1];

	/**
	 * Vettore su cui memorizzare il posto che l'utente
	 * desidera immettere al momento della modifica
	 * della prenotazione.
	 */
	char posto_scelto[4];

	/**
	 * Variabile che servirà a dire se il codice di prenotazione
	 * non esiste.
	 */
	int notfound = 0;

	/**
	 * Variabile che servirà a dire se il codice di prenotazione
	 * esiste.
	 */
	int found = 0;

	/**
	 * Variabile per trovare la giusta posizione nel
	 * vettore "prenotazione" dentro la struct passeggero.
	 */
	int num = 0;

	/**
	 * Variabile che conterrà la giusta posizione nel
	 * vettore "prenotazione" dentro la struct passeggero.
	 */
	int codice = 0;

	///Se il file non esiste, stampa un messaggio di errore.
	if( (passeggeri = fopen("passeggeri.dat", "rb+") ) == NULL) {
		printf("Errore nell'apertura.");
		fclose(passeggeri);
		return 0;
	}
	else {

		while (s != 1) {	///Finchè s è uguale a 1, eseguo il loop.
			printf("\n1) Modifica posto");
			printf("\n2) Cancella prenotazione");
			printf("\n3) Leggi le tue informazioni");
			printf("\n4) Ritorna al menu precedente (menu utente)");
			printf("\n5) Esci dal programma");
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
				passeggeri = fopen("passeggeri.dat", "rb+");

				fseek(passeggeri, (id_utente-1)*sizeof(passeggero), SEEK_SET);
				fread(&utenti, sizeof(passeggero), 1, passeggeri);

				correct = 0;

				while (correct != 1) {
					printf("\n---- Immettere codice prenotazione volo ----\n");
					printf("\nCODICE PRENOTAZIONE: ");

					scanf("%s", codice_prenotazione_temp);

					/// La funzione ControlloCodicePrenotazione(), restituisce 1 o 0.
					/// Se è 1 (significa che il codice è stato inserito correttamente)
					/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
					correct2 = ControlloCodicePrenotazione(codice_prenotazione_temp, MAX_CODICE_PRENOTAZIONE);

					///Le prime due lettere del codice prenotazione devono essere maiuscole.
					/// Es. AA123
					codice_prenotazione_temp[0] = toupper(codice_prenotazione_temp[0]);
					codice_prenotazione_temp[1] = toupper(codice_prenotazione_temp[1]);

					///Se il codice è stato correttamente inserito, vado avanti.
					if (correct2 == 1) {

						///Scorro tutto il vettore delle prenotazione dell'utente
						for (num = 0; num < MAX_PRENOTAZIONI; num++) {

							///Controllo se il codice inserito precedentemente coincide con almeno
							/// uno presente nel vettore di prenotazioni dell'utente.
							if(!strcmp(codice_prenotazione_temp,utenti.p[num].codice_prenotazione)) {
								printf("\nCodice prenotazione inserito correttamente!\n\n");
								codice = num; ///Se coincide, copio la giusta posizione del vettore prenotazione
								///in una variabile chiamata "codice", che userò successivamente.
								found++; ///Aumento il contatore dei "trovati".
							}
							else {
								notfound++; ///Se al primo for non trovo il codice prenotazione richiesto,
								/// aumento il contatore dei "non trovati". Ciclo così per tutto
								/// il for.
							}
						}

						///Se ha trovato almeno una corrispondenza, allora procedo a vedere se l'utente ha
						/// già effettuato questo check-in tramite un flag che diventa 1 al momento della
						/// prenotazione.
						/// Uso "codice" come indice del vettore, perchè quando trovo l'occorrenza, copio "num" in "codice".
						if (found > 0) {

							///Tramite fseek(), mi posiziono all'utente giusto tramite "numeroutente", dopo di che mi muovo nel
							/// giusto membro (utenti.numeropassaporto).
							fseek(passeggeri, (id_utente-1)*sizeof(passeggero) + (((char *) &utenti.p[codice].elenco.posti) - ((char *) &utenti)), SEEK_SET);

							while (correct4 != 1) {
								printf("\nChe posto vuoi scegliere?\n");
								printf("\nImmetti il tuo posto (Max. 150) --> ");
								scanf("%s", posto_scelto);

								///Converto più semplicemente in intero, il posto scelto dall'utente
								int val = atoi(posto_scelto);

								///Controllo se l'utente ha inserito un posto non valido.
								/// Max. 150, min 0.
								if (val > 150 || val < 0) {
									printf("\nHai inserito un posto non esistente. Sono massimo 150 posti!\n");
								}
								else {

									/// Controllo se alla posizione [0]-[1]-[2] del vettore, c'è un carattere alfabetico.
									if (isalpha(posto_scelto[0]) || isalpha(posto_scelto[1]) || isalpha(posto_scelto[2]))
									{
										printf("Hai inserito un carattere. Riprova.\n");
									}

									for (int i = 0; i < 3; i++) {
										if (posto_scelto[i] == *barra_spaziatrice) { ///Scorrimento e controllo vettore
											spazio++; ///Se trova uno spazio, aumenta la variabile "spazio" di 1.
										}
									}

									/// Per poter verificare se ci sono due spazi, la variabile "spazio" deve essere almeno pari a 2.
									if (spazio >= 1) {
										printf("Hai immesso uno o piu' spazi.\n");
										return 0;
									}

									/// Controllo se alla posizione [0] del vettore, c'è uno spazio. Il che significa che l'utente ha
									/// inserito la barra spaziatrice come primo carattere.
									if (posto_scelto[0] == *barra_spaziatrice) {
										///Se la if è verificata, stampo a video un messaggio d'errore
										/// ed esco dalla funzione con correct = 0, e ripeto tutta la funzione.
										printf("Hai inserito uno spazio all'inizio!!\n");
										return 0;
									}

									///Stampa un messaggio di errore se all'inizio è stato immesso un carattere new line.
									/// Controllo solo la prima posizione del vettore con il carattere "\n".
									if (posto_scelto[0] == *new_line) {
										printf("Hai inserito un carattere new line all'inizio!!\n");
										return 0; ///Se la if è verificata, esco dalla funzione con correct = 0 e ripeto il tutto.
									}

									voli = fopen("voli.dat", "rb+");

									/**
									 * Variabile per leggere tutto il file
									 */
									int read = 1;

									while( read != 0 )
									{
										/// Quando read arriva a 0, significa che il file è finito.
										read = fread(&elenco, sizeof(volo), 1, voli);

										if ( read > 0) {

											///Confronto il codice volo della prenotazione, con il codice volo di tutti i voli presenti nel sistema.
											/// Dato che il codice volo è unico, una volta trovata la coincidenza, andrò ad inserire un posto
											/// random per quel volo e lo occuperò tramite funzione booleana.
											if(!strcmp(utenti.p[codice].elenco.codice_volo, elenco.codice_volo)) {

												///Se il valore di quell'indice del vettore è pari ad 1,
												/// significa che il posto è già stato preso.
												if (elenco.posti[val] == 1) {
													printf("\nPosto gia' preso!\n");
													return 0;
												}

												///Occupo il posto per questo utente ed esco dal ciclo.
												utenti.p[codice].elenco.posti[val] = 1;

												elenco.posti[val] = 1;

												///Tramite fseek(), mi posiziono al volo giusto tramite "elenco.id", dopo di che mi muovo nel
												/// giusto membro (elenco.posti).
												fseek(voli, (elenco.id-1)*sizeof(volo) + (((char *) &elenco.posti) - ((char *) &elenco)), SEEK_SET);

												fwrite(&elenco.posti, sizeof(elenco.posti), 1, voli);

												///Una volta aggiornato il file, lo chiudo
												fclose(voli);

												passeggeri = fopen("passeggeri.dat", "rb+");

												///Tramite fseek(), mi sposto al giusto utente e sempre tramite offset, mi sposto al membro giusto (in questo
												/// caso è p[codice].posto) per poter scrivere il posto assegnato all'utente.
												fseek(passeggeri, (id_utente-1)*sizeof(passeggero) + (((char *) &utenti.p[codice].posto) - ((char *) &utenti)), SEEK_SET);

												utenti.p[codice].posto = val; ///Copio il posto scelto dall'utente nella variabile val, all'interno del vettore prenotazione.
												///Scrivo su file e chiudo.
												fwrite(&utenti.p[codice].posto, sizeof(utenti.p[codice].posto), 1, passeggeri);
												fclose(passeggeri);
												return 1;
											}
										}
									}
								}
							}
						}
					}

					///Qui ci entrerò solamente se il contatore dei "non trovati" è uguale al
					/// massimo di prenotazioni disponibili. Significa che non esiste un
					/// codice prenotazione tale.
					if (notfound >= MAX_PRENOTAZIONI) {
						printf ("\nCodice prenotazione non trovato. Riprovare.\n\n");
						///Resetto tutte le variabili dei vari cicli e resetto
						/// i vettori temporanei.
						correct = 0;
						correct2 = 0;
						notfound = 0;
						found = 0;
						codice_prenotazione_temp[0] = '\0';
					}
				}
				fclose(passeggeri);
				return 1;
				break;
			case 2:

				///La funzione ha codice F07a

				passeggeri = fopen("passeggeri.dat", "rb+");
				fseek(passeggeri, (id_utente-1)*sizeof(passeggero), SEEK_SET);
				fread(&utenti, sizeof(passeggero), 1, passeggeri);

				correct = 0;

				while (correct != 1) {
					printf("\n---- Immettere codice prenotazione volo ----\n");
					printf("\nCODICE PRENOTAZIONE: ");

					scanf("%s", codice_prenotazione_temp);

					/// La funzione ControlloCodicePrenotazione(), restituisce 1 o 0.
					/// Se è 1 (significa che il codice è stato inserito correttamente)
					/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
					correct2 = ControlloCodicePrenotazione(codice_prenotazione_temp, MAX_CODICE_PRENOTAZIONE);

					///Le prime due lettere del codice prenotazione devono essere maiuscole.
					/// Es. AA123
					codice_prenotazione_temp[0] = toupper(codice_prenotazione_temp[0]);
					codice_prenotazione_temp[1] = toupper(codice_prenotazione_temp[1]);

					///Se il codice è stato correttamente inserito, vado avanti.
					if (correct2 == 1) {

						///Scorro tutto il vettore delle prenotazione dell'utente
						for (num = 0; num < MAX_PRENOTAZIONI; num++) {

							///Controllo se il codice inserito precedentemente coincide con almeno
							/// uno presente nel vettore di prenotazioni dell'utente.
							if(!strcmp(codice_prenotazione_temp,utenti.p[num].codice_prenotazione)) {
								printf("\nCodice prenotazione inserito correttamente!\n\n");
								codice = num; ///Se coincide, copio la giusta posizione del vettore prenotazione
								///in una variabile chiamata "codice", che userò successivamente.
								found++; ///Aumento il contatore dei "trovati".
							}
							else {
								notfound++; ///Se al primo for non trovo il codice prenotazione richiesto,
								/// aumento il contatore dei "non trovati". Ciclo così per tutto
								/// il for.
							}
						}

						///Se ha trovato almeno una corrispondenza, allora procedo a vedere se l'utente ha
						/// già effettuato questo check-in tramite un flag che diventa 1 al momento della
						/// prenotazione.
						/// Uso "codice" come indice del vettore, perchè quando trovo l'occorrenza, copio "num" in "codice".
						if (found > 0) {

							///Tramite fseek(), mi posiziono all'utente giusto tramite "numeroutente", dopo di che mi muovo nel
							/// giusto membro (utenti.numeropassaporto).
							fseek(passeggeri, (id_utente-1)*sizeof(passeggero) + (((char *) &utenti.p[codice]) - ((char *) &utenti)), SEEK_SET);
							memset(&utenti.p[codice], 0, sizeof(utenti.p[codice]));
							fwrite(&utenti.p[codice], sizeof(utenti.p[codice]), 1, passeggeri);
							///La cancellazione è andata a buon fine, quindi esco da tutti i cicli.
							correct = 1;
						}
					}

					///Qui ci entrerò solamente se il contatore dei "non trovati" è uguale al
					/// massimo di prenotazioni disponibili. Significa che non esiste un
					/// codice prenotazione tale.
					if (notfound >= MAX_PRENOTAZIONI) {
						printf ("\nCodice prenotazione non trovato. Riprovare.\n\n");
						///Resetto tutte le variabili dei vari cicli e resetto
						/// i vettori temporanei.
						correct = 0;
						correct2 = 0;
						notfound = 0;
						found = 0;
						codice_prenotazione_temp[0] = '\0';
					}
				}
				fclose(passeggeri);
				return 1;
				break;
			case 3:
				///Apro il file in sola lettura.
				passeggeri = fopen("passeggeri.dat", "rb");

				///Mi posizione tramite fseek(), all'utente che ha effettuato il login.
				fseek(passeggeri, (id_utente-1)*sizeof(passeggero), SEEK_SET);
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
				return 1;
				break;
			case 4:
				///Chiamata alla funzione che mi porta al menu precedente (menu utente).
				mostraMenu();
				break;
			case 5: ///Rendo vero il valore della while e termino il programma con exit(0).
				s = 1;
				exit(0);
				break;
			default: ///Qui ricadranno tutti i valori non corretti. (caratteri e num > 9).
				printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
				printf("\nValore non corretto.");
				break;
			}
		}
	}
	return 1;
}

/**
 * La funzione, la quale non ha bisogno di un login (dato che ricerca un
 * codice prenotazione tra tutti quelli esistenti), chiede un codice prenotazione
 * all'utente e verifica se quel codice prenotazione è inserito nel sistema o meno.
 * Se esiste, procede con la stampa dell'utente per quella prenotazione altrimenti
 * mostra all'utente un messaggio di errore.
 * La funzione ha codice F12
 *
 * @pre La funzione richiede che il file dei passeggeri, esista.
 *
 * @post La funzione mostra l'utente per quella prenotazione o può mostrare un
 * 		 messaggio di errore se il file o la prenotazione non esiste.
 */
int ricercaPrenotazione (FILE *passeggeri) {

	/**
	 * Struct passeggero
	 */
	passeggero utenti;

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
	 * Vettore su cui memorizzare il codice prenotazione immesso
	 * dall'utente al momento del login.
	 */
	char codice_prenotazione_temp[MAX_CODICE_PRENOTAZIONE+1];

	printf("\nLa ricerca di una prenotazione consiste nell'immettere un codice prenotazione");
	printf("\ne l'algoritmo restituira', se esiste, il relativo passeggero per quella prenotazione.\n");

	while (correct != 1) {
		printf("\n---- Immettere codice prenotazione volo ----\n");
		printf("\nCODICE PRENOTAZIONE: ");

		scanf("%s", codice_prenotazione_temp);

		/// La funzione ControlloCodicePrenotazione(), restituisce 1 o 0.
		/// Se è 1 (significa che il codice è stato inserito correttamente)
		/// posso uscire dalla funzione, altrimenti farò ripetere il tutto.
		correct = ControlloCodicePrenotazione(codice_prenotazione_temp, MAX_CODICE_PRENOTAZIONE);

		///Le prime due lettere del codice prenotazione devono essere maiuscole.
		/// Es. AA123
		codice_prenotazione_temp[0] = toupper(codice_prenotazione_temp[0]);
		codice_prenotazione_temp[1] = toupper(codice_prenotazione_temp[1]);
	}

	if( (passeggeri = fopen("passeggeri.dat", "rb") ) == NULL) {
		printf("Errore nell'apertura.");
		return 0; ///Ritorno 0 se il file non esiste.
	}
	else {

		///Leggi il file finchè read non arriva a 0.
		while( read != 0)
		{
			/// Quando read arriva a 0, significa che il file è finito.
			read = fread(&utenti, sizeof(passeggero), 1, passeggeri);

			if ( read > 0) {

				///Scorro tutto il vettore delle prenotazioni per ogni utente presente nel sistema.
				/// Se il codice immesso dall'amministratore, coincide con uno presente nel vettore delle
				/// prenotazioni, allora stampo l'utente relativo a quella prenotazione.
				for (int i = 0; i < MAX_PRENOTAZIONI; i++) {
					if(!strcmp(codice_prenotazione_temp,utenti.p[i].codice_prenotazione)) {
						printf("\nIl codice prenotazione immesso appartiene a:\n%s %s, nato il %s-%s-%s a %s | NUMERO PASSAPORTO: %s | UTENTE N.%d", utenti.nome,
								utenti.cognome, utenti.datadinascita.giorno, utenti.datadinascita.mese, utenti.datadinascita.anno,
								utenti.luogodinascita, utenti.numeropassaporto, utenti.id);
						found++; ///Aumento il contatore delle prenotazioni trovate
					}
				}
			}
		}

		fclose(passeggeri);
	}

	///Entro nella if solo se ha trovato almeno 1 prenotazione
	if (found > 0) {
		return 1;
	}

	///Entro nella if solo se non ha trovato nessuna prenotazione
	if (found == 0) {
		return 0;
	}

	return 1;
}

/**
 * La funzione, tramite un algoritmo di ordinamento,
 * ordina in ordine alfabetico tutte le prenotazioni
 * registrate nel sistema.
 * La funzione ha codice F14.
 *
 * @param passeggeri File dei passeggeri
 */
int ordinamentoPrenotazioni(FILE *passeggeri) {

	///Se il file non esiste, stampa un messaggio di errore.
	if( (passeggeri = fopen("passeggeri.dat", "rb+") ) == NULL) {
		printf("Errore nell'apertura.");
		return 0;
	}
	else {

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
		 * Variabile che mi permetterà di uscire dal ciclo
		 */
		int correct2 = 0;

		/**
		 * Struct passeggero
		 */
		passeggero utenti;

		///Apro il file in sola lettura.
		passeggeri = fopen("passeggeri.dat", "rb");

		///Leggi il file finchè read non arriva a 0.
		while( read != 0)
		{
			/// Quando read arriva a 0, significa che il file è finito.
			read = fread(&utenti, sizeof(passeggero), 1, passeggeri);

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
					/// Se le due condizioni combaciano, allora significa che nel vettore p[num], esiste una prenotazione.
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
				///Resetto le variabili
				ora_arrivo = 0;
				ora_partenza = 0;
				num = 0;
				correct2 = 0;
			}
		}
		///Chiudo il file
		fclose(passeggeri);

		///Sorting
		passeggeri = fopen("passeggeri.dat", "rb");

		/**
		 * Vettore dinamico delle prenotazioni.
		 * E' grande tanto quanti sono le prenotazioni
		 */
		passeggero *listautenti = malloc(found * sizeof *listautenti);

		fread(listautenti, sizeof *listautenti, found, passeggeri);

		int SortFunc(const void* a, const void* b) {
		    passeggero *utenti1 = (passeggero*)a;
		    passeggero *utenti2 = (passeggero*)b;

		    return strcmp(utenti1->p->codice_prenotazione,utenti2->p->codice_prenotazione);
		}

		///Funzione qsort(). Mi ordina il vettore precedentemente dichiarato
		/// per prenotazioni, in ordine alfabetico. Riferirsi alla documentazione.
 		qsort(listautenti, found, sizeof(passeggero), SortFunc);

		fclose(passeggeri);
		///Fine Sorting

		///Stampa le prenotazioni ordinate
		for (int i = 0; i < found; i++) {
			///Non stampare utenti cancellati.
			if (listautenti[i].nome[0] != '\0') {
			printf("\n\nCODICE PRENOTAZIONE ---> %s - %s %s - Nato il %s-%s-%s a %s | NUMERO PASSAPORTO: %s\n", listautenti[i].p->codice_prenotazione, listautenti[i].nome,
					listautenti[i].cognome, listautenti[i].datadinascita.giorno, listautenti[i].datadinascita.mese, listautenti[i].datadinascita.anno,
					listautenti[i].luogodinascita, listautenti[i].numeropassaporto);
			}
		}
		return 1;
	}
}

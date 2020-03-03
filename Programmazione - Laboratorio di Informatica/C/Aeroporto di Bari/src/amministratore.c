/**
 * @file amministratore.c
 *
 * Questo file contiene le implementazioni dei prototipi
 * dichiarati nel file amministratore.h
 * @version 1
 * @date 13/05/2019
 * @authors Gianmarco Scarano
 */

/// Librerie necessarie per il corretto funzionamento del programma.

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "define.h"
#include "menu.h"
#include "volo.h"
#include "passeggero.h"
#include "controlli.h"

/**
 * La funzione chiede all'amministratore un codice volo
 * identificativo per quel volo e ne chiuderà il check-in
 * cambiando il flag "elenco.chiusura_checkin" da 0 a 1.
 * Poi stampa l'avvenuta chiusura.
 *
 * La funzione non ha nessun valore di ritorno.
 *
 */
int chiudi_checkin() {

	/**
	 * Sarà il valore di ritorno. (0 o 1).
	 */
	int correct = 0;

	/**
	 * Codice volo temporaneo
	 */
	char codice_volo_temporaneo[MAX_CODICE_VOLO+1];

	/**
	 * Dichiaro una variabile di tipo FILE
	 * che mi servirà a leggere tutti i codice volo
	 */
	FILE *input = NULL;

	printf("\nImmetti il codice volo: ");
	scanf("%s", codice_volo_temporaneo);

	while (correct != 1) {

		/**
		 * Lunghezza della stringa "codice_volo" inserita dall'amministratore.
		 */
		int lunghezza = strlen(codice_volo_temporaneo);

		///Se la lunghezza del codice è maggiore di 6, mostra un errore.
		if (lunghezza < MAX_CODICE_VOLO+1 && lunghezza > MAX_CODICE_VOLO-1 ) {

			///Scorro la posizione [0]-[1] del vettore durata e controllo se sono stati inseriti dei
			/// caratteri alfabetici tramite la funzione isalpha(). Se la if non è verificata, stampo un errore
			/// ed esco dalla funzione con correct = 0.
			for (int i = 0; i < MAX_CODICE_VOLO-4; i++) {
				if (isalpha(codice_volo_temporaneo[i])) {
					correct = 0;
				}
				else {
					printf("\nI primi due caratteri immessi non sono alfabetici. Il codice volo deve essere composto in questo modo: AA0123!\n");
					correct = 1;
				}
			}

			if (correct == 0) {
				///Scorro la posizione [2]-[3]-[4]-[5] del vettore durata e controllo se sono stati inseriti dei
				/// caratteri numerici tramite la funzione isdigit(). Se la if non è verificata, stampo un errore
				/// ed esco dalla funzione con correct = 0.
				for (int p = 2; p < MAX_CODICE_VOLO; p++) {
					if (isdigit(codice_volo_temporaneo[p])) {
						correct = 0;
					}
					else {
						printf("\nHai immesso dei caratteri errati. Il codice volo deve essere composto in questo modo: AA0123!\n");
						correct = 1;
					}
				}

				codice_volo_temporaneo[0] = toupper(codice_volo_temporaneo[0]);
				codice_volo_temporaneo[1] = toupper(codice_volo_temporaneo[1]);
			}

			if (correct == 0) {

				///Apro il file.
				input = fopen("voli.dat", "rb+");

				/**
				 * Struct del volo
				 */
				volo elenco;

				///Leggi il file finchè read non arriva a 0.
				int read = 1;

				while( read != 0)
				{
					/// Quando read arriva a 0, significa che il file è finito.
					read = fread(&elenco, sizeof(volo), 1, input);

					if ( read > 0) {

						///Se il codice volo che l'utente ha immesso coincide con almeno un codice volo già presente nel sistema,
						/// stampa un errore e ripeti il tutto.
						if(!strcmp(codice_volo_temporaneo,elenco.codice_volo)) {
							printf("\nHo trovato un codice volo valido!\n");
							elenco.chiusura_checkin = 1;

							///Tramite fseek(), mi posiziono al volo giusto tramite "elenco.id", dopo di che mi muovo nel
							/// giusto membro (elenco.chiusura_checkin).
							fseek(input, (elenco.id-1)*sizeof(volo) + (((char *) &elenco.chiusura_checkin) - ((char *) &elenco)), SEEK_SET);

							fwrite(&elenco.chiusura_checkin, sizeof(elenco.chiusura_checkin), 1, input);

							printf("\nHo chiuso il check-in per questo volo --> %s\n", elenco.codice_volo);
							///Una volta aggiornato il file, lo chiudo
							fclose(input);
							correct = 1;
						}
					}
				}
			}
		}

		else {
			///Stampa un errore non appena la prima if (relativa alla lunghezza) è falsa.
			printf("\nHai immesso un codice volo composto da 7 o piu' cifre. Il codice deve essere composto in questo modo: AA0123!\n");
		}

		if (correct == 0) {
			return 0;
		}

		if (correct == 1) {
			return 1;
		}
	}

	return correct;
}

/**
 * La funzione, molto semplicemente, mostra un menù dedicato
 * interamente all'amministratore. Attraverso una switch,
 * chiede all'amministratore un compito da svolgere.
 * Sono implementati gli opportuni controlli.
 *
 * La funzione non ha nessun valore di ritorno.
 *
 */
void login_amministratore() {

	/**
	 * Dichiaro una variabile di tipo file, che passerò
	 * all'interno di varie funzioni presenti nella switch.
	 */
	FILE *file = NULL;

	/**
	 * Valore di ritorno per la funzione
	 * "chiudi_checkin"
	 */
	int chiudicheckin = 0;

	/**
	 * Valore di ritorno per la funzione
	 * "inputUtenti"
	 */
	int input_Utente = 0;

	/**
	 * Valore di ritorno per la funzione
	 * "inputVoli"
	 */
	int input_Voli = 0;

	/**
	 * Valore di ritorno per la funzione
	 * "modificaVoli"
	 */
	int modifica_Voli = 0;

	/**
	 * Valore di ritorno per la funzione
	 * "modificaUtenti"
	 */
	int modifica_Utente = 0;

	/**
	 * Valore di ritorno per la funzione
	 * "letturaUtenti"
	 */
	int leggi_Utenti = 0;

	/**
	 * Valore di ritorno per la funzione
	 * "letturaVoli"
	 */
	int leggi_Voli = 0;

	/**
	 * Valore di ritorno per la funzione
	 * "ricercaPrenotazione"
	 */
	int prenotazione = 0;

	/**
	 * Valore di ritorno per la funzione
	 * "ordinamentoUtenti"
	 */
	int ordina_Utenti = 0;

	/**
	 * Valore di ritorno per la funzione
	 * "ordinamentoVoli"
	 */
	int ordina_Voli = 0;

	/**
	 * Valore di ritorno per la funzione
	 * "ordinamentoPrenotazioni"
	 */
	int ordina_Prenotazioni = 0;

	/**
	 * Valore di ritorno per la funzione
	 * "ricercaVoli"
	 */
	int ricerca_Voli = 0;

	/**
	 * Variabile per la condizione iniziale del login
	 */
	unsigned short int correct = 0;

	/**
	 * Variabile che controlla l'esito
	 * del controllo menu
	 */
	int scelta = 0;

	/**
	 * Sarà la scelta dell'utente
	 * trasformata in intero
	 */
	int opzione = 0;

	/**
	 * Variabile per immagazzinare la scelta da eseguire.
	 */
	char scelta_amministratore[2] = "\0";

	/**
	 * Variabile che mi permetterà di uscire dal secondo while loop.
	 */
	unsigned short int s = 0;

	/**
	 * Dichiaro un vettore di tipo char nella quale sarà presente il
	 * nome utente temporaneo immesso dall'utente stesso
	 */
	char nomeutente[MAX_NOME_UTENTE];

	/**
	 * Dichiaro un vettore di tipo char nella quale sarà presente la
	 * la password utente temporanea immessa dall'utente stesso
	 */
	char passwordutente[MAX_PASSWORD_UTENTE];

	///Dichiaro due vettori, sempre di tipo char, nella quale sono
	/// presenti le effettive credenziali di accesso per l'amministratore.

	/**
	 * Dichiaro un vettore, sempre di tipo char, nella quale sarà
	 * presente l'effettivo nomeadmin, necessario per l'accesso amministratore.
	 */
	char nomeadmin[MAX_NOME_UTENTE] = "adminaeroporto";

	/**
	 * Dichiaro un vettore, sempre di tipo char, nella quale sarà
	 * presente l'effettiva passwordadmin, necessario per l'accesso amministratore.
	 */
	char passwordadmin[MAX_PASSWORD_UTENTE] = "bariaeroporto2019";

	while ( correct == 0 ) { ///Finchè correct è uguale a 0, esegui il loop.
		printf("\n-------------- L O G I N --------------");
		printf("\nNome admin: ");
		scanf("%19s", nomeutente); ///Prendo in input un massimo di 19 caratteri. Il 20 è il terminatore.
		printf("\nPassword admin: ");
		scanf("%19s", passwordutente); ///Prendo in input un massimo di 19 caratteri. Il 20 è il terminatore.

		///Tramite la funzione strcmp(), presente in "string.h", confronto i due vettori temporanei
		/// (che ora avranno le credenziali immesse dall'utente) con le effettive credenziali d'accesso
		/// presenti nei vettori dichiarati precedentemente. Se entrambi i vettori combaciano, allora
		/// la variabile "correct" diventerà 1, ed uscirò dal ciclo. Altrimenti, stampo un messaggio d'errore
		/// e faccio ripetere la procedura di login, azzerando i vettori temporanei.
		if((!strcmp(nomeutente,nomeadmin)) && (!strcmp(passwordutente,passwordadmin))) {
			printf("\nLogin effettuato!\n");
			correct++;
		}
		else {
			printf ("\nLogin errato. Riprovare.\n");
			nomeutente[0] = '\0';
			passwordutente[0] = '\0';
		}
	}

	while (s != 1) {	///Finchè s è uguale a 1, eseguo il loop.
		printf("\n-------------- M E N U --------------");
		printf("\n----- A M M I N I S T R A T O R E-----");
		printf("\n1) Chiudi check-in");
		printf("\n2) Inserisci voli");
		printf("\n3) Inserisci utenti");
		printf("\n4) Modifica voli");			///Stampo le varie funzionalità dell'amministratore.
		printf("\n5) Modifica utenti");
		printf("\n6) Leggi tutti voli");
		printf("\n7) Ricerca utenti");
		printf("\n8) Ricerca prenotazione");
		printf("\n9) Ricerca voli");
		printf("\n10) Ordina utenti");
		printf("\n11) Ordina voli");
		printf("\n12) Ordina prenotazioni");
		printf("\n13) Ritorna al menu precedente (menu utente)");
		printf("\n14) Esci dal programma");
		printf("\n-------------------------------------");
		printf("\nLA TUA SCELTA: ");
		scanf("%s", scelta_amministratore); ///Immagazzino la scelta dell'utente nella variabile sceltautente.

		///Controllo se l'amministratore ha inserito una scelta corretta
		scelta = ControlloMenu(scelta_amministratore, 1);

		///Se il controllo non è andato a buon fine, ri-mostro il menu dopo un messaggio di errore.
		if (scelta == 0) {
			login_amministratore();
		}
		else {
			///Altrimenti trasformo la scelta dell'amministratore, da carattere ad intero e proseguo
			opzione = atoi(scelta_amministratore);
		}

		///Programmazione difensiva che cattura i caratteri, nel caso in cui l'amministratore
		/// abbia immesso dei caratteri invece dei numeri.
		/// Converto i caratteri in numeri e li faccio ricadere nel "default" della switch,
		/// stampando un messaggio d'errore.
		if (s != getchar()) {
		}
		switch (opzione) { ///Switch per controllare cosa l'amministratore ha immesso
		case 1:
			///Chiamata alla funzione che permettere di chiudere
			/// il check-in, dato un volo.
			chiudicheckin = chiudi_checkin();

			if (chiudicheckin == 1) {
				printf("\nHai chiuso un check-in con successo!\n");
			}
			else {
				printf("\nIl check-in non e' stato chiuso con successo. Sei sicuro che esista il file\no che"
						"tu abbia inserito un codice volo valido?");
			}

			break;
		case 2:
			///Chiamata alla funzione che permette l'aggiunta di voli.
			input_Voli = inputVoli(file);

			if (input_Voli == 1) {
				printf("\nHai inserito un volo con successo!\n");
			}
			else {
				printf("\nIl volo non e' stato inserito. Sei sicuro che esista il file?\n");
			}

			break;
		case 3:
			///Chiamata alla funzione che permette l'aggiunta di utenti.
			input_Utente = inputUtenti(file);

			if (input_Utente == 1) {
				printf("\nHai inserito un utente con successo!\n");
			}
			else {
				printf("\nL'utente non e' stato inserito. Sei sicuro che esista il file?\n");
			}

			break;
		case 4:
			///Chiamata alla funzione che permette la modifica di voli.
			modifica_Voli = modificaVoli(file);

			if (modifica_Voli == 1) {
				printf("\nHai modificato un volo con successo!\n");
			}
			else {
				printf("\nIl volo non e' stato modificato. Sei sicuro che esista il file?\n");
			}

			break;
		case 5:
			///Chiamata alla funzione che permette la modifica di utenti.
			modifica_Utente = modificaUtente(file);

			if (modifica_Utente == 1) {
				printf("\nHai modificato un utente con successo!\n");
			}
			else {
				printf("\nL'utente non e' stato modificato. Sei sicuro che esista il file?\n");
			}

			break;
		case 6:
			///Chiamata alla funzione che permette la lettura di voli.
			leggi_Voli = letturaVoli(file);

			if (leggi_Voli == 1) {
				printf("\nLa lettura e' andata a buon fine!\n");
			}
			else {
				printf("\nLa lettura non e' andata a buon fine. Sei sicuro che esista il file?\n");
			}

			break;
		case 7:
			///Chiamata alla funzione che permette la lettura di utenti.
			leggi_Utenti = letturaUtenti(file);

			if (leggi_Utenti == 1) {
				printf("\nLa lettura e' andata a buon fine!\n");
			}
			else {
				printf("\nLa lettura non e' andata a buon fine. Sei sicuro che esista il file?\n");
			}

			break;
		case 8:
			///Chiamata alla funzione che permette la ricerca di prenotazioni.
			prenotazione = ricercaPrenotazione(file);

			if (prenotazione == 1) {
				printf("\n\nLa ricerca e' andata a buon fine!\n");
			}
			else {
				printf("\n\nLa ricerca non e' andata a buon fine. Sei sicuro che esista la prenotazione o il file?\n");
			}

			break;
		case 9:
			///Chiamata alla funzione che permette l'ordinamento di utenti
			ricerca_Voli = ricercaVoli(file);

			if (ricerca_Voli == 1) {
				printf("\n\nLa ricerca e' andata a buon fine!\n");
			}
			else {
				printf("\n\nLa ricerca non e' andata a buon fine. Sei sicuro che esista il codice volo o il file?\n");
			}
			break;
		case 10:
			///Chiamata alla funzione che permette l'ordinamento di utenti
			ordina_Utenti = ordinamentoUtenti(file);

			if (ordina_Utenti == 1) {
				printf("\nL'ordinamento e' andato a buon fine!\n");
			}
			else {
				printf("\nL'ordinamento non e' andato a buon fine. Sei sicuro che esista il file?\n");
			}
			break;
		case 11:
			///Chiamata alla funzione che permette l'ordinamento di utenti
			ordina_Voli = ordinamentoVoli(file);

			if (ordina_Voli == 1) {
				printf("\nL'ordinamento e' andato a buon fine!\n");
			}
			else {
				printf("\nL'ordinamento non e' andato a buon fine. Sei sicuro che esista il file?\n");
			}
			break;
		case 12:
			///Chiamata alla funzione che permette l'ordinamento di utenti
			ordina_Prenotazioni = ordinamentoPrenotazioni(file);

			if (ordina_Prenotazioni == 1) {
				printf("\nL'ordinamento e' andato a buon fine!\n");
			}
			else {
				printf("\nL'ordinamento non e' andato a buon fine. Sei sicuro che esista il file?\n");
			}
			break;
		case 13:
			///Chiamata alla funzione che mi porta al menu precedente (menu utente).
			mostraMenu();
			break;
		case 14: ///Rendo vero il valore della while e termino il programma con exit(0).
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

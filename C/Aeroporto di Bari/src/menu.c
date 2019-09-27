/**
 * @file menu.c
 *
 * Questo file contiene le implementazioni dei prototipi
 * dichiarati nel file menu.c
 * @version 1
 * @date 13/05/2019
 * @authors Gianmarco Scarano
 */

/// Includo le librerie necessarie per il corretto funzionamento del programma
#include <stdio.h>
#include <stdlib.h>
#include "passeggero.h"
#include "amministratore.h"
#include "controlli.h"

void mostraMenu() {

	/**
	 * Valore di ritorno per la funzione
	 * "prenotaVolo"
	 */
	int prenotazione = 0;

	/**
	 * Valore di ritorno per la funzione
	 * "checkin"
	 */
	int check = 0;

	/**
	 * Valore di ritorno per la funzione
	 * "modificaUtente"
	 */
	int modifica_Utente = 0;

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
	 * Dichiaro una variabile di tipo file, che passerò
	 * all'interno di varie funzioni presenti nella switch.
	 */
	FILE *file = NULL;

	/**
	 * Dichiaro un'altra variabile di tipo file, che passerò
	 * all'interno di varie funzioni presenti nella switch.
	 */
	FILE *file1 = NULL;

	/**
	 * Valore di ritorno per la funzione
	 * "inputUtente"
	 */
	int input = 0;

	/**
	 * Variabile per immagazzinare la scelta da eseguire.
	 */
	char sceltautente[2] = "\0";

	unsigned short int s = 0; ///Condizione utile per rendere falso il ciclo while.

	while (s != 1) {	///Finchè s è diverso da 1, continua a ciclare.
		printf("\n-------------- M E N U --------------");
		printf("\n1) Registrati");
		printf("\n2) Prenota un volo");
		printf("\n3) Completa check-in");				///Stampo le varie funzionalità dell'utente
		printf("\n4) Modifica le tue informazioni");
		printf("\n5) Login come amministratore");
		printf("\n6) Esci dal programma");
		printf("\n-------------------------------------");
		printf("\nLA TUA SCELTA: ");
		scanf("%s", sceltautente); ///Immagazzino la scelta dell'utente nella variabile sceltautente.

		///Controllo se l'utente ha inserito una scelta corretta
		scelta = ControlloMenu(sceltautente, 0);

		///Se il controllo non è andato a buon fine, ri-mostro il menu dopo un messaggio di errore.
		if (scelta == 0) {
			mostraMenu();
		}
		///Altrimenti trasformo la scelta dell'utente, da carattere ad intero e proseguo
		else {
			opzione = atoi(sceltautente);
		}

		///Programmazione difensiva che cattura i caratteri, nel caso in cui l'utente
		/// abbia immesso dei caratteri invece dei numeri.
		/// Converto i caratteri in numeri e li faccio ricadere nel "default" della switch,
		/// stampando un messaggio d'errore.
		if (s != getchar()) {
		}

		switch (opzione) { ///Switch per controllare cosa l'utente ha immesso
		case 1:
			///Chiamata alla funzione che permette di aggiungere
			/// nuovi utenti.
			input = inputUtenti(file);

			if (input == 1) {
				printf("\nHai inserito un utente con successo!\n");
			}
			else {
				printf("\nL'utente non e' stato inserito. Sei sicuro che esista il file?\n");
			}

			continue;
		case 2:
			///Chiamata alla funzione che permette di prenotare
			/// un volo.
			prenotazione = prenotaVolo(file, file1);

			if (prenotazione == 1) {
				printf("\nHai inserito una prenotazione con successo!\n");
			}
			else {
				printf("\nLa prenotazione non e' andata a buon fine.\n");
			}

			break;
		case 3:
			///Chiamata alla funzione che permette di effettuare
			/// il check-in, dato un numero prenotazione.
			check = checkin(file, file1);

			if (check == 1) {
				printf("\nHai effettuato un check-in con successo!\n");
			}
			else {
				printf("\nIl check-in non e' andato a buon fine.\n");
			}

			break;
		case 4:
			///Chiamata alla funzione che permettere di modificare
			/// un utente, dato un certo ID.
			modifica_Utente = modificaUtente(file);

			if (modifica_Utente == 1) {
				printf("\nHai effettuato la modifica delle tue informazioni con successo!\n");
			}
			else {
				printf("\nLa modifica delle tue informazioni non e' andata a buon fine.\n");
			}

			break;
		case 5:
			///Chiamata alla funzione che mostra le funzionalità dell'amministratore.
			login_amministratore();
			break;
		case 6: ///Rendo vero il valore della while ed esco dal programma.
			s = 1;
			exit(0);
			break;
		default:
			///Qui ricadranno tutti i valori non corretti. (caratteri e num > 6).
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
			printf("\nValore non corretto.");
			break;
		}
	}

}

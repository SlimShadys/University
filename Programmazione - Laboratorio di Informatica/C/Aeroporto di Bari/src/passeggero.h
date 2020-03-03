/**
 * @file passeggero.h
 * Prototipi di funzioni per le informazioni relative al passeggero.
 *
 * Questa libreria contiene essenzialmente l'aggiunta/modifica/cancellazione dell'utente
 * @version 1
 * @date 13/05/2019
 * @authors Gianmarco Scarano
 */

#ifndef PASSEGGERO_H_
#define PASSEGGERO_H_

#include <stdio.h>
#include "define.h"
#include "data.h"
#include "prenotazione.h"

/**
 * Struct per il passeggero. Contiene i campi relativi ad esso.
 */
typedef struct {
	/**
	 * Nome utente
	 */
	char nome[MAX_NOME+1];

	/**
	 * Cognome utente
	 */
	char cognome[MAX_COGNOME+1];

	/**
	 * Data di nascita dell' utente
	 */
	data datadinascita;

	/**
	 * Luogo di nascita utente
	 */
	char luogodinascita[MAX_LUOGO_DI_NASCITA+1];

	/**
	 * Numero passaporto utente
	 */
	char numeropassaporto[MAX_PASSAPORTO+1];

	/**
	 * ID dell'utente
	 */
	int id;

	/**
	 * Vettore di prenotazioni dell'utente
	 */
	prenotazione p[MAX_PRENOTAZIONI];
} passeggero;

/**
 * Questa procedura apre il file degli utenti e
 * registra un nuovo passeggero nel sistema.
 * Ulteriori funzioni saranno implementate all'interno.
 *
 * @param input Il file dei passeggeri
 *
 * @return La funzione, essendo procedura, non ha nessun parametro
 * 		  di return.
 */
int inputUtenti(FILE *input);

/**
 * Questa procedura apre il file degli utenti e
 * ne legge il contenuto. L'amministratore ha varie
 * possibilità di lettura. Sono implementati algoritmi
 * di ricerca al suo interno.
 *
 * @param input Il file dei passeggeri
 *
 * @return La funzione ritorna 1, se la lettura è stata effettuata con successo,
 * 		   ritorna 0 se la lettura non è stata effettuata, data la mancanza
 * 		   del file dei passeggeri.
 */
int letturaUtenti(FILE *input);

/**
 * Acquisice l'ID dell'ultimo utente.
 *
 * @return "ID" se acquisice correttamente l'ID dell'ultimo utente,
 * 			altrimenti restituisce 0.
 */
int ID_Utente ();

/**
 * Questa procedura apre il file degli utenti e
 * ne può modificare il contenuto. L'amministratore ha varie
 * possibilità di modifica. Sono implementati algoritmi
 * di ricerca al suo interno.
 *
 * @param passeggeri Il file dei passeggeri
 *
 * @return La funzione ritorna 1, se la modifica è stata effettuata con successo,
 * 		   ritorna 0 se la modifica non è stata effettuata, data la mancanza
 * 		   del file dei passeggeri.
 */
int modificaUtente(FILE *passeggeri);

/**
 * Questa procedura resetta a 0 tutti i membri
 * della struct passeggero, prima di inserire
 * un nuovo utente nel sistema.
 *
 * @param utenti1 La struct del passeggero da resettare
 *
 * @return La funzione, essendo procedura, non ha nessun parametro
 * 		  di return.
 */
void resetUtente(passeggero *utenti1);

/**
 * Questa procedura apre il file degli utenti e
 * ordina in base al nome tutti gli utenti.
 *
 * @param passeggeri Il file dei passeggeri
 *
 * @return La funzione ritorna 1, se l'ordinamento è stato effettuato con successo,
 * 		   ritorna 0 se l'ordinamento non è stato effettuato, data la mancanza
 * 		   del file dei passeggeri.
 */
int ordinamentoUtenti(FILE *passeggeri);

#endif /* PASSEGGERO_H_ */

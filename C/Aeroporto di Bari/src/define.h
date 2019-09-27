/**
 * @file define.h
 *
 * Questa libreria contiene tutte le necessarie costanti simboliche
 * richiamate all'interno di indici di vettori, per facilitarne
 * la portabilità.
 *
 * @version 1
 * @date 13/05/2019
 * @authors Gianmarco Scarano
 */

#ifndef DEFINE_H_
#define DEFINE_H_

/**
 * Massima lunghezza per un nome
 */
#define MAX_NOME 20

/**
 * Massima lunghezza per un cognome
 */
#define MAX_COGNOME 20

/**
 * Anno minimo di nascita per un utente
 */
#define MIN_ANNO_NASCITA 1940

/**
 * Anno massimo di nascita per un utente
 */
#define MAX_ANNO_NASCITA 2001

/**
 * Lunghezza massima di un passaporto
 */
#define MAX_PASSAPORTO 9

/**
 * Lunghezza massima di un comune di nascita
 */
#define MAX_LUOGO_DI_NASCITA 15

/**
 * Limite massimo di prenotazioni per un utente
 */
#define MAX_PRENOTAZIONI 10

// ------------------------------------------------------------- //

/**
 * Lunghezza massima di un codice volo
 */
#define MAX_CODICE_VOLO 6

/**
 * Lunghezza massima del nome di una compagnia aerea
 */
#define MAX_NOME_COMPAGNIA 20

/**
 * Lunghezza massima del nome della città di partenza
 */
#define MAX_TRATTA_PARTENZA 20

/**
 * Lunghezza massima del nome della città di arrivo
 */
#define MAX_TRATTA_ARRIVO 20

/**
 * Lunghezza massima del modello di un aereo
 */
#define MAX_MODELLO_AEREO 15

/**
 * Limite massimo di posti su un aereo
 */
#define MAX_POSTI 150

/**
 * Lunghezza massima del codice di prenotazione
 */
#define MAX_CODICE_PRENOTAZIONE 5

/**
 * Ora massima per un volo
 */
#define MAX_ORA_VOLO 23

/**
 * Ora minima per un volo
 */
#define MIN_ORA_VOLO 00

/**
 * Cifre massime della durata di un volo (espressa in minuti)
 */
#define MAX_DURATA 3

// ------------------------------------------------------------- //

/**
 * Lunghezza massima del vettore relativo alle ore
 */
#define MAX_ORA 2

/**
 * Lunghezza massima del vettore relativo ai minuti
 */
#define MAX_MINUTI 2

// ------------------------------------------------------------- //

/**
 * Lunghezza massima del vettore relativo al giorno
 */
#define MAX_GIORNO 2

/**
 * Lunghezza massima del vettore relativo al mese
 */
#define MAX_MESE 2

/**
 * Lunghezza massima del vettore relativo all'anno
 */
#define MAX_ANNO 4

// ------------------------------------------------------------- //

/**
 * Massimo input del nome immesso dall'utente al momento dell'autenticazione amministratore
 */
#define MAX_NOME_UTENTE 20

/**
 * Massimo input della password immesso dall'utente al momento dell'autenticazione amministratore
 */
#define MAX_PASSWORD_UTENTE 20

#define MAX_SCELTA 2

#endif /* DEFINE_H_ */

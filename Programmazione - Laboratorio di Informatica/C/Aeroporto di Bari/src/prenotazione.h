/**
 * @file prenotazione.h
 * Prototipi di funzioni per le informazioni relative alla prenotazione.
 *
 * Questa libreria contiene essenzialmente la struct per la prenotazione
 * e varie funzioni riguardanti essa (prenotazione del volo e check-in)
 * @version 1
 * @date 13/05/2019
 * @authors Gianmarco Scarano
 */

#ifndef PRENOTAZIONE_H_
#define PRENOTAZIONE_H_

#include "volo.h"

/**
 * Struct per la prenotazione. Contiene i campi relativi ad essa.
 */
typedef struct {
	/**
	 * Struct del volo integrata nell'utente
	 */
	volo elenco;

	/**
	 * Questo sarà il codice prenotazione
	 * formato in questo modo: AA123
	 */
	char codice_prenotazione[MAX_CODICE_PRENOTAZIONE+1];

	/**
	 * Posto dell'utente per questa prenotazione
	 */
	int posto;

	/**
	 * Variabile che mi permette di controllare se
	 * il check-in è stato già fatto o meno
	 * per questa prenotazione.
	 */
	int controllo_checkin;

} prenotazione;

/**
 * Questa procedura apre l'interfaccia per la prenotazione del volo.
 * Ulteriori funzioni/controlli saranno implementati all'interno.
 *
 * @param voli File dei voli
 * @param passeggeri File dei passeggeri
 *
 * @return La funzione ritorna 1, se la prenotazione è stata effettuata con successo,
 * 		   ritorna 0 se la prenotazione non è stata effettuata, data la mancanza
 * 		   del file dei passeggeri.
 */
int prenotaVolo (FILE *voli, FILE *passeggeri);

/**
 * Questa procedura apre l'interfaccia per la modifica di una prenotazione.
 * Ulteriori funzioni/controlli saranno implementati all'interno.
 *
 * @param passeggeri File dei passeggeri
 * @param id_utente E' l'ID dell'utente che intende modificare la prenotazione
 *
 * @return La funzione ritorna 1, se la modifica della prenotazione è stata effettuata
		   con successo, ritorna 0 se la modifica non è stata effettuata, data la mancanza
 * 		   del file dei passeggeri.
 */
int modificaPrenotazione(FILE *passeggeri, int id_utente);

/**
 * Questa procedura apre l'interfaccia per il check-in del volo.
 * Ulteriori funzioni/controlli saranno implementati all'interno.
 *
 * @param voli File dei voli
 * @param passeggeri File dei passeggeri
 *
 * @return La funzione ritorna 1, se il check-in è stato effettuato con successo,
 * 		   ritorna 0 se il check-in non è stato effettuato, data la mancanza
 * 		   del file dei passeggeri.
 */
int checkin(FILE *voli, FILE *passeggeri);

/**
 * Questa procedura apre l'interfaccia per la ricerca di una prenotazione.
 * Ulteriori funzioni/controlli saranno implementati all'interno.
 *
 * @param passeggeri File dei passeggeri
 *
 * @return La funzione ritorna 1, se la ricerca della prenotazione è stata effettuata
		   con successo, ritorna 0 se la prenotazione non esiste, oppure il file
		   dei passeggeri non è presente.
 */
int ricercaPrenotazione (FILE *passeggeri);

/**
 * Questa procedura apre il file degli utenti e
 * ordina in base al nome tutti le prenotazioni.
 *
 * @param passeggeri Il file dei passeggeri
 *
 * @return La funzione ritorna 1, se l'ordinamento è stato effettuato con successo,
 * 		   ritorna 0 se l'ordinamento non è stato effettuato, data la mancanza
 * 		   del file dei passeggeri.
 */
int ordinamentoPrenotazioni(FILE *passeggeri);

#endif /* PRENOTAZIONE_H_ */

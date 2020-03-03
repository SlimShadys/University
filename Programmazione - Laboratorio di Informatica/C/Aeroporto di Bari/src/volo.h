/**
 * @file volo.h
 * Prototipi di funzioni per le informazioni relative ai voli.
 *
 * Questa libreria contiene essenzialmente la struct per i voli
 * e varie funzioni riguardanti essi (input-lettura-modifica ecc.)
 * @version 1
 * @date 13/05/2019
 * @authors Gianmarco Scarano
 */

#ifndef VOLO_H_
#define VOLO_H_

#include <stdio.h>
#include "volo.h"
#include "define.h"
#include "data.h"

/**
 * Struct per il volo. Contiene i campi relativi ad esso.
 */
typedef struct {
	/**
	 * Codice indentificativo del volo
	 */
	char codice_volo[MAX_CODICE_VOLO+1];

	/**
	 * Nome compagnia del volo
	 */
	char nomecompagnia[MAX_NOME_COMPAGNIA+1];

	/**
	 * Nome dell'aeroporto di partenza
	 */
	char tratta_partenza[MAX_TRATTA_PARTENZA+1];

	/**
	 * Nome dell'aeroporto di arrivo
	 */
	char tratta_arrivo[MAX_TRATTA_ARRIVO+1];

	/**
	 * Nome o codice del modello aereo
	 */
	char modello_aereo[MAX_MODELLO_AEREO+1];

	/**
	 * Vettore di posti nell'aereo
	 */
	int posti[MAX_POSTI];

	/**
	 * Rimanda alla struct data. Contiene
	 * le informazioni riguardanti
	 * giorno / mese / anno del volo
	 */
	data datadivolo;

	/**
	 * Ora di partenza del volo
	 */
	char ora_partenza[MAX_ORA+1];

	/**
	 * Minuti di partenza del volo
	 */
	char minuti_partenza[MAX_MINUTI+1];

	/**
	 * Ora di arrivo del volo
	 */
	char ora_arrivo[MAX_ORA+1];

	/**
	 * Minuti di arrivo del volo
	 */
	char minuti_arrivo[MAX_MINUTI+1];

	/**
	 * Durata del volo espressa in minuti
	 */
	char durata[MAX_DURATA+1];

	/**
	 * ID identificativo del volo
	 */
	int id;

	/**
	 * Flag che controlla la chiusura
	 * di un check-in
	 */
	int chiusura_checkin;
} volo;

/**
 * Questa procedura apre il file dei voli e
 * registra un nuovo volo nel sistema.
 * Ulteriori funzioni saranno implementate all'interno.
 *
 * @param voli Il file dei voli
 *
 * @return La funzione ritorna 1, se l'aggiunta del volo è stata effettuata con successo,
 * 		   ritorna 0 se l'aggiunta non è stata effettuata, data la mancanza
 * 		   del file dei voli.
 */
int inputVoli(FILE *voli);

/**
 * La funzione apre il file dei voli e ne legge il contenuto.
 *
 * @param voli Il file dei voli
 *
 * @return La funzione ritorna 1, se la lettura dei voli è stata effettuata con successo,
 * 		   ritorna 0 se la lettura non è stata effettuata, data la mancanza
 * 		   del file dei voli.
 */
int letturaVoli(FILE *voli);

/**
 * Questa procedura apre il file dei voli e
 * chiede all'utente quali campi del volo vuole modificare.
 * Ulteriori funzioni saranno implementate all'interno.
 *
 * @param voli Il file dei voli
 *
 * @return La funzione ritorna 1, se la modifica del volo è stata effettuata con successo,
 * 		   ritorna 0 se la modifica non è stata effettuata, data la mancanza
 * 		   del file dei voli.
 */
int modificaVoli(FILE *voli);

/**
 * Questa procedura apre l'interfaccia per la ricerca di un volo.
 * Ulteriori funzioni/controlli saranno implementati all'interno.
 *
 * @param voli File dei voli
 *
 * @return La funzione ritorna 1, se la ricerca del volo è stata effettuata
		   con successo, ritorna 0 se il volo non esiste, oppure se il file
		   dei voli non è presente.
 */
int ricercaVoli (FILE *voli);

/**
 * Questa procedura apre il file dei voli e
 * ordina in base al codice volo, tutti i voli.
 *
 * @param voli Il file dei voli
 *
 * @return La funzione ritorna 1, se l'ordinamento è stato effettuato con successo,
 * 		   ritorna 0 se l'ordinamento non è stato effettuato, data la mancanza
 * 		   del file dei passeggeri.
 */
int ordinamentoVoli(FILE *voli);

/**
 * Questa procedura resetta a 0 tutti i membri
 * della struct volo, prima di inserire
 * un nuovo volo nel sistema.
 *
 * @param elenco1 La struct del volo da resettare
 *
 * @return La funzione, essendo procedura, non ha nessun parametro
 * 		  di return.
 */
void resetVolo(volo *elenco1);

/**
 * Acquisice l'ID dell'ultimo volo.
 *
 * @return "ID" se acquisice correttamente l'ID dell'ultimo volo,
 * 			altrimenti restituisce 0.
 */
int ID_Volo();

#endif /* VOLO_H_ */

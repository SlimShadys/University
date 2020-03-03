/**
 * @file data.h
 * Prototipi di funzione per la struct delle data.
 *
 * Questo header file contiene la struct data (contenente
 * giorno-mese-anno) che sarà ripresa da altre struct,
 * ovvero da "volo" e "passeggero".
 *
 * @version 1
 * @date 17/05/2018
 * @authors Gianmarco Scarano
 */

#ifndef DATA_H_
#define DATA_H_

/**
 * Struct data avente vettori di char
 * per giorno-mese-anno. La loro lunghezza
 * dipende dalle costanti simboliche dichiarate
 * nel "define.h".
 */
typedef struct {
	/**
	 * Vettore per il giorno
	 */
	char giorno[MAX_GIORNO+1];

	/**
	 * Vettore per il mese
	 */
	char mese[MAX_MESE+1];

	/**
	 * Vettore per l'anno
	 */
	char anno[MAX_ANNO+1];
} data;

#endif /* DATA_H_ */

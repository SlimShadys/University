/**
 * @file amministratore.h
 * Prototipi di funzioni per i task dell'amministratore.
 *
 * Questa libreria contiene essenzialmente due funzioni relative all'amministratore
 * nonchè, il suo login e la chiusura del check-in.
 * @version 1
 * @date 13/05/2019
 * @authors Gianmarco Scarano
 */

#ifndef AMMINISTRATORE_H_
#define AMMINISTRATORE_H_

/**
 * Questa procedura apre l'interfaccia per il login amministratore.
 * Ulteriori funzioni saranno implementate all'interno.
 * La funzione ha codice F01a
 *
 * @return La funzione, essendo procedura, non ha nessun parametro
 * 		  di return.
 */
void login_amministratore();

/**
 * Questa funzione chiude il check-in.
 * Per poter funzionare non ha bisogno di parametri in entrata.
 *
 * @return La funzione ritorna 1, se la chiusura è stata effettuata con successo,
 * 		   ritorna 0 se la chiusura non è stata effettuata.
 */
int chiudi_checkin();

#endif /* AMMINISTRATORE_H_ */

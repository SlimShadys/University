/**
 * @file controlli.c
 *
 * Questo file contiene le implementazioni dei prototipi
 * dichiarati nel file controlli.h
 * @version 1
 * @date 13/05/2019
 * @authors Gianmarco Scarano
 */

/// Includo le librerie necessarie al corretto funzionamento del programma.
#include "controlli.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/**
 * Controlla se il nome compagnia è composto da caratteri validi,
 * ovvero solo caratteri alfabetici.
 * La funzione ha codice F04a
 *
 * @pre Qualsiasi input immesso dall'amministratore, sarà elaborato a dovere
 * 		secondi gli opportuni controlli.
 * @post L'intero restituito sarà 1, nel caso in cui la stringa inserita sia
 * 		 formata da soli caratteri alfabetici. Sarà restituito 0 nel caso in cui
 * 		 ci sia almeno 1 numero oppure la lunghezza della stringa stessa superi
 * 		 la lunghezza massima (20).
 */
int ControlloNomeCompagnia (volo elenco1) {

	/**
	 * Sarà il valore di ritorno. (0 o 1).
	 */
	int correct = 0;

	/**
	 * Variabile che conterrà la lunghezza della stringa inserita dall'amministratore
	 */
	int lunghezza = strlen(elenco1.nomecompagnia);

	///Se la lunghezza è maggiore di 20, allora restituisci un errore.
	if (lunghezza < MAX_NOME_COMPAGNIA+1) {

		///Scorro tutto il vettore e controllo se è tutti i caratteri inseriti
		/// siano alfabetici. Nel caso contrario, stampa a video un errore
		/// ed esci subito dalla funzione con un valore di ritorno pari a 0.
		for (int i = 0; i < lunghezza; i++) {
			if (isalpha(elenco1.nomecompagnia[i])) { ///Scorrimento e controllo vettore
			}
			else {
				printf("Hai immesso un numero. Il nome della compagnia e' formato da soli caratteri!\n");
				return correct; ///Appena trova un numero, esce dalla funzione con correct = 0.
			}
		}
		correct = 1; ///Se nessun valore numerico è stato trovato nel vettore, la stringa è giusta e correct diventa 1.
	}
	else {
		///Stampa un errore non appena la prima if (relativa alla lunghezza) è falsa.
		printf("Hai immesso un nome compagnia piu' lungo di 20 caratteri.\n");
	}

	return correct;
}

/**
 * Controlla se la tratta di partenza è composta da caratteri validi,
 * ovvero solo caratteri alfabetici.
 *
 * @pre Qualsiasi input immesso dall'amministratore, sarà elaborato a dovere
 * 		secondi gli opportuni controlli.
 * @post L'intero restituito sarà 1, nel caso in cui la stringa inserita sia
 * 		 formata da soli caratteri alfabetici. Sarà restituito 0 nel caso in cui
 * 		 ci sia almeno 1 numero oppure la lunghezza della stringa stessa superi
 * 		 la lunghezza massima (20).
 */
int ControlloTrattaPartenza (volo elenco1) {

	/**
	 * Sarà il valore di ritorno. (0 o 1).
	 */
	int correct = 0;

	/**
	 * Variabile che conterrà la lunghezza della stringa inserita dall'amministratore
	 */
	int lunghezza = strlen(elenco1.tratta_partenza);

	///Se la lunghezza è maggiore di 20, allora restituisci un errore.
	if (lunghezza < MAX_TRATTA_PARTENZA+1) {

		///Scorro tutto il vettore e controllo se è tutti i caratteri inseriti
		/// siano alfabetici. Nel caso contrario, stampa a video un errore
		/// ed esci subito dalla funzione con un valore di ritorno pari a 0.
		for (int i = 0; i < lunghezza; i++) {
			if (isalpha(elenco1.tratta_partenza[i])) { ///Scorrimento e controllo vettore
			}
			else {
				printf("Hai immesso un numero. La tratta e' formata da soli caratteri!\n");
				return correct; ///Appena trova un numero, esce dalla funzione con correct = 0.
			}
		}
		correct = 1; ///Se nessun valore numerico è stato trovato nel vettore, la stringa è giusta e correct diventa 1.
	}
	else {
		///Stampa un errore non appena la prima if (relativa alla lunghezza) è falsa.
		printf("Hai immesso una tratta piu' lunga di 20 caratteri.\n");
	}
	return correct;
}

/**
 * Controlla se la tratta d'arrivo è composta da caratteri validi,
 * ovvero solo caratteri alfabetici.
 *
 * @pre Qualsiasi input immesso dall'amministratore, sarà elaborato a dovere
 * 		secondi gli opportuni controlli.
 * @post L'intero restituito sarà 1, nel caso in cui la stringa inserita sia
 * 		 formata da soli caratteri alfabetici. Sarà restituito 0 nel caso in cui
 * 		 ci sia almeno 1 numero oppure la lunghezza della stringa stessa superi
 * 		 la lunghezza massima (20).
 */
int ControlloTrattaArrivo (volo elenco1) {

	/**
	 * Sarà il valore di ritorno. (0 o 1).
	 */
	int correct = 0;

	/**
	 * Variabile che conterrà la lunghezza della stringa inserita dall'amministratore
	 */
	int lunghezza = strlen(elenco1.tratta_arrivo);

	///Se la lunghezza è maggiore di 20, allora restituisci un errore.
	if (lunghezza < MAX_TRATTA_ARRIVO+1) {

		///Scorro tutto il vettore e controllo se è tutti i caratteri inseriti
		/// siano alfabetici. Nel caso contrario, stampa a video un errore
		/// ed esci subito dalla funzione con un valore di ritorno pari a 0.
		for (int i = 0; i < lunghezza; i++) {
			if (isalpha(elenco1.tratta_arrivo[i])) { ///Scorrimento e controllo vettore
			}
			else {
				printf("Hai immesso un numero. La tratta e' formata da soli caratteri!\n");
				return correct; ///Appena trova un numero, esce dalla funzione con correct = 0.
			}
		}
		correct = 1; ///Se nessun valore numerico è stato trovato nel vettore, la stringa è giusta e correct diventa 1.
	}
	else {
		///Stampa un errore non appena la prima if (relativa alla lunghezza) è falsa.
		printf("Hai immesso una tratta piu' lunga di 20 caratteri.\n");
	}
	return correct;
}

/**
 * Controlla se il modello dell'aereo è composto da caratteri validi,
 * ovvero da caratteri alfanumerici e solo uno spazio.
 *
 * @pre Qualsiasi input immesso dall'amministratore, sarà elaborato a dovere
 * 		secondi gli opportuni controlli.
 * @post L'intero restituito sarà 1, nel caso in cui la stringa inserita sia
 * 		 formata da caratteri alfanumerici e da al massimo uno spazio.
 * 		 Sarà restituito 0 nel caso in cui ci siano almeno 2 spazi oppure
 * 		 quando la lunghezza della stringa stessa superi la lunghezza massima (15).
 */
int ControlloModelloAereo (volo elenco1) {

	/**
	 * Sarà il valore di ritorno. (0 o 1).
	 */
	int correct = 0;

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
	 * Variabile che conterrà la lunghezza della stringa inserita dall'amministratore
	 */
	int lunghezza = strlen(elenco1.modello_aereo);

	///Se la lunghezza è maggiore di 15, allora restituisci un errore.
	if (lunghezza < MAX_MODELLO_AEREO+1) {

		///Scorro tutto il vettore e controllo se tra i caratteri inseriti
		/// ci sono degli spazi. In questo caso, è ammesso solamente uno spazio.
		/// Se trova più di uno spazio, esce dalla funzione con un valore di ritorno pari a 0.
		for (int i = 0; i < MAX_MODELLO_AEREO+1; i++) {
			if (elenco1.modello_aereo[i] == *barra_spaziatrice) { ///Scorrimento e controllo vettore
				spazio++; ///Se trova uno spazio, aumenta la variabile "spazio" di 1.
			}
		}

		/// Per poter verificare se ci sono due spazi, la variabile "spazio" deve essere almeno pari a 2.
		if (spazio > 1) {
			printf("Hai immesso due spazi. Ne e' ammesso solamente uno. (Es. Boeing 747)\n");
			return correct;
		}

		/// Controllo se alla posizione [0] del vettore, c'è uno spazio. Il che significa che l'utente ha
		/// inserito la barra spaziatrice come primo carattere.
		if (elenco1.modello_aereo[0] == *barra_spaziatrice) {
			///Se la if è verificata, stampo a video un messaggio d'errore
			/// ed esco dalla funzione con correct = 0, e ripeto tutta la funzione.
			printf("Hai inserito uno spazio all'inizio. Un modello di un aereo non inizia con uno spazio.\n");
			correct = 0;
			return correct;
		}

		///Stampa un messaggio di errore se all'inizio è stato immesso un carattere new line.
		/// Controllo solo la prima posizione del vettore con il carattere "\n".
		if (elenco1.modello_aereo[0] == *new_line) {
			printf("Hai inserito un carattere new line all'inizio. Un modello di un aereo non inizia con un carattere new line.\n");
			correct = 0;
			return correct; ///Se la if è verificata, esco dalla funzione con correct = 0 e ripeto il tutto.
		}
		correct = 1; /// Correct sarà uguale a 1 quando l'input è corretto.
	}
	else {
		///Stampa un errore non appena la prima if (relativa alla lunghezza) è falsa.
		printf("Hai immesso un modello piu' lungo di 20 caratteri.\n");
	}
	return correct;
}

/**
 * Controlla se l'orario di partenza (ore e minuti) è composto da caratteri validi,
 * ovvero da caratteri numerici.
 *
 * @pre Qualsiasi input immesso dall'amministratore, sarà elaborato a dovere
 * 		secondi gli opportuni controlli.
 * @post L'intero restituito sarà 1, nel caso in cui la stringa inserita sia
 * 		 formata da caratteri numerici e siano stati inseriti meno di 3 caratteri.
 * 		 Sarà restituito 0 nel caso in cui ci siano più di 2 caratteri, oppure
 * 		 quando l'ora è maggiore di 23 o minore di 00, oppure quando i minuti
 * 		 sono maggiori di 59 e minori di 00.
 */
int ControlloOrarioPartenza (volo elenco1) {

	/**
	 * Sarà il valore di ritorno. (0 o 1).
	 */
	int correct = 0;

	/**
	 * Lunghezza della stringa "ore" inserita dall'amministratore.
	 */
	int lunghezza = strlen(elenco1.ora_partenza);

	/**
	 * Lunghezza della stringa "minuti" inserita dall'amministratore.
	 */
	int lunghezza1 = strlen(elenco1.minuti_partenza);

	///Se la lunghezza dell'ora o dei minuti è maggiore di 2, mostra un errore.
	if ((lunghezza < MAX_ORA+1) && (lunghezza1 < MAX_MINUTI+1)) {

		///Scorro le prime due posizioni di entrambi i vettori e controllo se in posizione [0] e [1] ci siano dei caratteri alfabetici.
		/// Se la condizione è verificata, allora stampa a video un errore.
		if (isalpha(elenco1.ora_partenza[0]) || isalpha(elenco1.ora_partenza[1]) || isalpha(elenco1.minuti_partenza[0]) || isalpha(elenco1.minuti_partenza[0]))
		{
			printf("Hai inserito un carattere. Riprova.\n");
		}
		///Confronto la stringa "ora_partenza" in modo tale che debba contenere un valore minore di 23 e maggiore di 00.
		/// Se la condizione non è verificata, stampo a video un errore.
		else if ((strcmp(elenco1.ora_partenza, "23") > 0 ) || (strcmp(elenco1.ora_partenza, "00") < 0)) {
			printf("Hai inserito un'ora non valida. Deve essere compreso tra 00 e 23.\n");
		}
		///Confronto la stringa "minuti_partenza" in modo tale che debba contenere un valore minore di 59 e maggiore di 00.
		/// Se la condizione non è verificata, stampo a video un errore.
		else if ((strcmp(elenco1.minuti_partenza, "59") > 0 ) || (strcmp(elenco1.minuti_partenza, "00") < 0)) {
			printf("Hai inserito un valore in minuti non valido. Deve essere compreso tra 00 e 59.\n");
		}
		else {
			correct = 1; /// Correct sarà uguale a 1 quando l'input delle ore e dei minuti è corretto.
		}
	}
	else {
		///Stampa un errore non appena la prima if (relativa alla lunghezza) è falsa.
		printf("Hai immesso un'ora di partenza composta da piu' di 2 cifre. Deve essere formata da 2 cifre!\n");
	}
	return correct;
}

/**
 * Controlla se l'orario di arrivo (ore e minuti) è composto da caratteri validi,
 * ovvero da caratteri numerici.
 *
 * @pre Qualsiasi input immesso dall'amministratore, sarà elaborato a dovere
 * 		secondi gli opportuni controlli.
 * @post L'intero restituito sarà 1, nel caso in cui la stringa inserita sia
 * 		 formata da caratteri numerici e siano stati inseriti meno di 3 caratteri.
 * 		 Sarà restituito 0 nel caso in cui ci siano più di 2 caratteri, oppure
 * 		 quando l'ora è maggiore di 23 o minore di 00, oppure quando i minuti
 * 		 sono maggiori di 59 e minori di 00.
 */
int ControlloOrarioArrivo (volo elenco1) {

	/**
	 * Sarà il valore di ritorno. (0 o 1).
	 */
	int correct = 0;

	/**
	 * Trasformo in intero l'ora di partenza.
	 * Necessario per un controllo successivo.
	 */
	int ora_partenza = atoi(elenco1.ora_partenza);

	/**
	 * Trasformo in intero i minuti della partenza.
	 * Necessario per un controllo successivo.
	 */
	int minuti_partenza = atoi(elenco1.minuti_partenza);

	/**
	 * Trasformo in intero l'ora di arrivo.
	 * Necessario per un controllo successivo.
	 */
	int ora_arrivo = atoi(elenco1.ora_arrivo);

	/**
	 * Trasformo in intero i minuti ddell'arrivo.
	 * Necessario per un controllo successivo.
	 */
	int minuti_arrivo = atoi(elenco1.minuti_arrivo);

	/**
	 * Lunghezza della stringa "ore" inserita dall'amministratore.
	 */
	int lunghezza = strlen(elenco1.ora_arrivo);

	/**
	 * Lunghezza della stringa "minuti" inserita dall'amministratore.
	 */
	int lunghezza1 = strlen(elenco1.minuti_arrivo);

	///Se la lunghezza dell'ora o dei minuti è maggiore di 2, mostra un errore.
	if ((lunghezza < MAX_ORA+1) && (lunghezza1 < MAX_MINUTI+1)) {

		///Scorro le prime due posizioni di entrambi i vettori e controllo se in posizione [0] e [1] ci siano dei caratteri alfabetici.
		/// Se la condizione è verificata, allora stampa a video un errore.
		if (isalpha(elenco1.ora_arrivo[0]) || isalpha(elenco1.ora_arrivo[1]) || isalpha(elenco1.minuti_arrivo[0]) || isalpha(elenco1.minuti_arrivo[0]))
		{
			printf("Hai inserito un carattere. Riprova.\n");
		}
		///Confronto la stringa "ora_arrivo" in modo tale che debba contenere un valore minore di 23 e maggiore di 00.
		/// Se la condizione non è verificata, stampo a video un errore.
		else if ((strcmp(elenco1.ora_arrivo, "23") > 0 ) || (strcmp(elenco1.ora_arrivo, "00") < 0)) {
			printf("Hai inserito un'ora non valida. Deve essere compreso tra 00 e 23.\n");
		}
		///Confronto la stringa "minuti_arrivo" in modo tale che debba contenere un valore minore di 59 e maggiore di 00.
		/// Se la condizione non è verificata, stampo a video un errore.
		else if ((strcmp(elenco1.minuti_arrivo, "59") > 0 ) || (strcmp(elenco1.minuti_arrivo, "00") < 0)) {
			printf("Hai inserito un valore in minuti non valido. Deve essere compreso tra 00 e 59.\n");
		}
		///Confronto l'ora di arrivo con quella di partenza. Se l'ora di arrivo è minore di quella
		/// di partenza, allora stampo un errore. Es. (Partenza 16:00, Arrivo 15:00)
		else if (ora_arrivo < ora_partenza) {
			printf("\nL'orario di arrivo non può essere minore di quello di partenza!");
			printf("\nRitorno al futuro?\n");
			printf("-----------------------------------------------------------------\n");
		}
		///Confronto l'ora di arrivo con quella di partenza. Se l'ora di arrivo è uguale a quella
		/// di partenza e i minuti dell'arrivo sono minori di quelli di partenza. allora stampo un errore.
		/// Es. (Partenza 16:30, Arrivo 16:20)
		else if ((ora_arrivo == ora_partenza) && (minuti_arrivo < minuti_partenza)) {
			printf("\nI minuti dell'arrivo non possono essere minori di quelli di partenza!");
			printf("\nRitorno al futuro?\n");
			printf("-----------------------------------------------------------------\n");
		}
		///Confronto l'ora di arrivo con quella di partenza. Se l'ora di arrivo è esattamente uguale a quella
		/// di partenza e i minuti dell'arrivo sono esattamente uguali a quelli di partenza, allora stampo un errore.
		/// Es. (Partenza 16:30, Arrivo 16:30)
		else if ((ora_arrivo == ora_partenza) && (minuti_arrivo == minuti_partenza)) {
			printf("\nL'orario della partenza e dell'arrivo non possono coincidere!");
			printf("\n-----------------------------------------------------------------\n");
		}
		else {
			correct = 1; /// Correct sarà uguale a 1 quando l'input delle ore e dei minuti è corretto.
		}
	}
	else {
		///Stampa un errore non appena la prima if (relativa alla lunghezza) è falsa.
		printf("Hai immesso un'ora di arrivo composta da piu' di 2 cifre. Deve essere formata da 2 cifre!\n");
	}
	return correct;
}

/**
 * Controlla se il mese del volo è composto da caratteri validi,
 * ovvero da caratteri numerici.
 *
 * @pre Qualsiasi input immesso dall'amministratore, sarà elaborato a dovere
 * 		secondi gli opportuni controlli.
 * @post L'intero restituito sarà 1, nel caso in cui la stringa inserita sia
 * 		 formata da caratteri numerici e siano stati inseriti meno di 3 caratteri.
 * 		 Sarà restituito 0 nel caso in cui ci siano più di 2 caratteri, oppure
 * 		 quando il mese è maggiore di 12 (Dicembre) o minore di 01 (Gennaio).
 */
int ControlloMese (volo elenco1) {

	/**
	 * Sarà il valore di ritorno. (0 o 1).
	 */
	int correct = 0;

	/**
	 * Lunghezza della stringa inserita dall'amministratore.
	 */
	int lunghezza = strlen(elenco1.datadivolo.mese);

	///Se la lunghezza del mese è maggiore di 2, mostra un errore.
	if (lunghezza < MAX_MESE+1) {
		///Scorrendo la posizione [0] e [1] del vettore, controllo se è stato immesso un carattere.
		/// Se la condizione è vera, stampo a video un errore.
		if (isalpha(elenco1.datadivolo.mese[0]) || isalpha(elenco1.datadivolo.mese[1]))
		{
			printf("Hai inserito un carattere. Riprova.\n");
		}
		///Se la condizione precedente non è verificata, allora procedo nel controllare se il numero inserito
		/// sia maggiore di 01 (Gennaio) o minore di 12 (Dicembre). Se il valore è errato, stampo a video un errore.
		else if ((strcmp(elenco1.datadivolo.mese, "12") > 0 ) || (strcmp(elenco1.datadivolo.mese, "01") < 0))  {
			printf("Hai immesso un mese errato. Deve essere compreso tra 01 (Gennaio) e 12 (Dicembre).\n");
		}
		else
		{
			correct = 1; /// Correct sarà uguale a 1 quando l'input del mese è corretto.
		}
	}
	else {
		///Stampa un errore non appena la prima if (relativa alla lunghezza) è falsa.
		printf("Hai immesso un mese composto da piu' di 3 cifre. Deve essere formato da 2 cifre!\n");
	}
	return correct;
}

/**
 * Controlla se il giorno del volo è composto da caratteri validi,
 * ovvero da caratteri numerici.
 *
 * @pre Qualsiasi input immesso dall'amministratore, sarà elaborato a dovere
 * 		secondi gli opportuni controlli.
 * @post L'intero restituito sarà 1, nel caso in cui la stringa inserita sia
 * 		 formata da caratteri numerici e siano stati inseriti meno di 3 caratteri.
 * 		 Sarà restituito 0 nel caso in cui ci siano più di 2 caratteri, oppure
 * 		 quando il massimo/minimo giorno di un determinato mese non coincide.
 */
int ControlloGiorno (volo elenco1) {

	/**
	 * Sarà il valore di ritorno. (0 o 1).
	 */
	int correct = 0;

	/**
	 * Variabile che conterrà la stringa stringa "mese" inserita
	 * precedentemente dall'amministratore, convertita in intero
	 */
	int mese = atoi(elenco1.datadivolo.mese);

	/**
	 * Lunghezza della stringa "giorno" inserita dall'amministratore.
	 */
	int lunghezza = strlen(elenco1.datadivolo.giorno);

	///Se la lunghezza del giorno è maggiore di 2, mostra un errore.
	if (lunghezza < MAX_GIORNO+1) {
		///Tramite una switch, assegno un determinato controllo a determinati mesi dell'anno.
		/// La switch esamina il mese, convertito in numero precedentemente e sceglie il "case" corrispondente.
		switch(mese)
		{
		case 4:
		case 6:	///Aprile - Giugno - Settembre - Novembre.
		case 9:
		case 11:
			///Scorro la posizione [0] e [1] dei due vettori e controllo se sono stati inseriti dei
			/// caratteri alfabetici tramite la funzione isalpha(). Se la if è verificata, stampo un errore
			/// ed esco dalla funzione con correct = 0.
			if (isalpha(elenco1.datadivolo.giorno[0]) || isalpha(elenco1.datadivolo.giorno[1]))
			{
				printf("Hai inserito un carattere. Riprova.\n");
			}
			///Se la condizione precedente non è verificata, allora passo al controllo del giorno, il quale deve
			/// essere compreso tra 30 e 01.
			else if ((strcmp(elenco1.datadivolo.giorno, "30") > 0 ) || (strcmp(elenco1.datadivolo.giorno, "01") < 0))  {
				printf("Hai immesso un giorno del mese errato. Deve essere compreso tra 01 e 30.\n");
			}
			else
			{
				correct = 1; ///Correct sarà 1 solamente quando l'utente ha inserito un input giusto. (es. 30 Aprile).
			}
			return correct;
			break;
		case 2: ///Febbraio
			///Scorro la posizione [0] e [1] dei due vettori e controllo se sono stati inseriti dei
			/// caratteri alfabetici tramite la funzione isalpha(). Se la if è verificata, stampo un errore
			/// ed esco dalla funzione con correct = 0.
			if (isalpha(elenco1.datadivolo.giorno[0]) || isalpha(elenco1.datadivolo.giorno[1]))
			{
				printf("Hai inserito un carattere. Riprova.\n");
			}
			///Se la condizione precedente non è verificata, allora passo al controllo del giorno, il quale deve
			/// essere compreso tra 29 e 01.
			else if ((strcmp(elenco1.datadivolo.giorno, "29") > 0 ) || (strcmp(elenco1.datadivolo.giorno, "01") < 0))  {
				printf("Hai immesso un giorno del mese errato. Deve essere compreso tra 01 e 29.\n");
			}
			else
			{
				correct = 1; ///Correct sarà 1 solamente quando l'utente ha inserito un input giusto. (es. 25 Febbraio).
			}
			return correct;
			break;
		default: /// Gennaio - Marzo - Maggio - Luglio - Agosto - Ottobre - Dicembre
			///Scorro la posizione [0] e [1] dei due vettori e controllo se sono stati inseriti dei
			/// caratteri alfabetici tramite la funzione isalpha(). Se la if è verificata, stampo un errore
			/// ed esco dalla funzione con correct = 0.
			if (isalpha(elenco1.datadivolo.giorno[0]) || isalpha(elenco1.datadivolo.giorno[1]))
			{
				printf("Hai inserito un carattere. Riprova.\n");
			}
			///Se la condizione precedente non è verificata, allora passo al controllo del giorno, il quale deve
			/// essere compreso tra 31 e 01.
			else if ((strcmp(elenco1.datadivolo.giorno, "31") > 0 ) || (strcmp(elenco1.datadivolo.giorno, "01") < 0))  {
				printf("Hai immesso un giorno del mese errato. Deve essere compreso tra 01 e 31.\n");
			}
			else
			{
				correct = 1; ///Correct sarà 1 solamente quando l'utente ha inserito un input giusto. (es. 27 Marzo).
			}
			return correct;
			break;
		}
	}
	else {
		///Stampa un errore non appena la prima if (relativa alla lunghezza) è falsa.
		printf("Hai immesso un giorno composto da piu' di 3 cifre. Deve essere formato da 2 cifre!\n");
	}
	return correct;

}

/**
 * Controlla se l'anno del volo è composto da caratteri validi,
 * ovvero da caratteri numerici.
 *
 * @pre Qualsiasi input immesso dall'amministratore, sarà elaborato a dovere
 * 		secondi gli opportuni controlli.
 * @post L'intero restituito sarà 1, nel caso in cui la stringa inserita sia
 * 		 formata da caratteri numerici e siano stati inseriti meno di 3 caratteri.
 * 		 Sarà restituito 0 nel caso in cui ci siano più di 4 caratteri, meno di 4 caratteri
 * 		 oppure quando l'utente immette un anno maggiore di 2020 o minore di 2019.
 */
int ControlloAnno (volo elenco1) {

	/**
	 * Sarà il valore di ritorno. (0 o 1).
	 */
	int correct = 0;

	/**
	 * Lunghezza della stringa "anno" inserita dall'amministratore.
	 */
	int lunghezza = strlen(elenco1.datadivolo.anno);

	///Se la lunghezza dell'anno non è esattamente di 4 caratteri, mostra un errore.
	if ((lunghezza < MAX_ANNO+1) && (lunghezza > MAX_ANNO-1)) {

		///Scorro la posizione [0]-[1]-[2]-[3] del vettore anno e controllo se sono stati inseriti dei
		/// caratteri alfabetici tramite la funzione isalpha(). Se la if è verificata, stampo un errore
		/// ed esco dalla funzione con correct = 0.
		if (isalpha(elenco1.datadivolo.anno[0]) || isalpha(elenco1.datadivolo.anno[1]) || isalpha(elenco1.datadivolo.anno[2]) ||  isalpha(elenco1.datadivolo.anno[3]))
		{
			printf("Hai inserito un carattere. Riprova.\n");
			return correct;
		}
		///Se la condizione precedente non è verificata, allora passo al controllo dell'anno, il quale deve
		/// essere compreso tra 2020 e 2019.
		else if ((strcmp(elenco1.datadivolo.anno, "2020") > 0 ) || (strcmp(elenco1.datadivolo.anno, "2019") < 0))  {
			printf("Hai immesso un anno errato. Deve essere compreso tra 2019 e 2020.\n");
		}
		else
		{
			correct = 1; ///Correct sarà 1 solamente quando l'utente ha inserito un input giusto. (es. 2020).
		}
	}
	else {
		///Stampa un errore non appena la prima if (relativa alla lunghezza) è falsa.
		printf("Hai immesso un anno composto da piu' di 4 cifre, oppure da meno di 4 cifre. Deve essere formato da esattamente 4 cifre!\n");
	}
	return correct;
}

/**
 * Controlla se la durata del volo è composta da caratteri validi,
 * ovvero da caratteri numerici.
 *
 * @pre Qualsiasi input immesso dall'amministratore, sarà elaborato a dovere
 * 		secondi gli opportuni controlli.
 * @post L'intero restituito sarà 1, nel caso in cui la stringa inserita sia
 * 		 formata da caratteri numerici e siano stati inseriti meno di 4 caratteri.
 * 		 Sarà restituito 0 nel caso in cui ci siano più di 3 caratteri, oppure
 * 		 quando l'amministratore immette una durata (in min.) maggiore di 240
 * 		 o minore di 40.
 */
int ControlloDurata (volo elenco1) {

	/**
	 * Sarà il valore di ritorno. (0 o 1).
	 */
	int correct = 0;

	/**
	 * Variabile che conterrà, più semplicemente, il vettore della durata
	 * in un intero per poi fare gli opportuni controlli sui casi limite.
	 */
	int val = atoi(elenco1.durata);

	/**
	 * Lunghezza della stringa "durata" inserita dall'amministratore.
	 */
	int lunghezza = strlen(elenco1.durata);

	///Se la lunghezza della durata è maggiore di 3, mostra un errore.
	if (lunghezza < MAX_DURATA+1) {

		///Scorro la posizione [0]-[1]-[2] del vettore durata e controllo se sono stati inseriti dei
		/// caratteri alfabetici tramite la funzione isalpha(). Se la if è verificata, stampo un errore
		/// ed esco dalla funzione con correct = 0.
		if (isalpha(elenco1.durata[0]) || isalpha(elenco1.durata[1]) || isalpha(elenco1.durata[2]))
		{
			printf("Hai inserito un carattere. Riprova.\n");
		}
		///Se la condizione precedente non è verificata, allora passo al controllo della durata (tramite
		/// la variabile "val", la quale deve essere compresa tra 240 e 40.
		else if ((val > 240 ) || (val < 40))  {
			printf("Hai immesso una durata errata. Un volo può durare dai 40 minuti fino ai 240 minuti (4 ore).\n");
		}
		else
		{
			correct = 1; ///Correct sarà 1 solamente quando l'utente ha inserito un input giusto. (es. 130).
		}
	}
	else {
		///Stampa un errore non appena la prima if (relativa alla lunghezza) è falsa.
		printf("Hai immesso una durata composta da 4 o piu' cifre. Deve essere formata da almeno 2 cifre!\n");
	}
	return correct;
}

/**
 * Controlla se il codice del volo è composto da caratteri validi,
 * ovvero dai primi 2 caratteri alfabetici e i restanti 4 numerici.
 * La funzione ha codice F04b
 *
 * @pre Qualsiasi input immesso dall'amministratore, sarà elaborato a dovere
 * 		secondi gli opportuni controlli.
 * @post L'intero restituito sarà 1, nel caso in cui la stringa inserita sia
 * 		 formata dai primi 2 caratteri alfabetici e i restanti 4 numerici.
 * 		 La stringa sarà formata da 6 caratteri.
 * 		 Sarà restituito 0 nel caso in cui ci siano più di 6 caratteri, oppure
 * 		 quando l'amministratore immette prima numeri e poi lettere, o meglio ancora
 * 		 quando immette più di 2 caratteri alfabetici o meno di 3 caratteri numerici.
 */
int ControlloCodiceVolo (char *codice_volo_temp, int MAX_CODICE_VOLO_TEMP, int immesso) {

	/**
	 * Sarà il valore di ritorno. (0 o 1).
	 */
	int correct = 0;

	/**
	 * Lunghezza della stringa "codice_volo" inserita dall'amministratore.
	 */
	int lunghezza = strlen(codice_volo_temp);

	///Se la lunghezza del codice è maggiore di 6, mostra un errore.
	if (lunghezza < MAX_CODICE_VOLO_TEMP+1) {

		///Scorro la posizione [0]-[1] del vettore durata e controllo se sono stati inseriti dei
		/// caratteri alfabetici tramite la funzione isalpha(). Se la if non è verificata, stampo un errore
		/// ed esco dalla funzione con correct = 0.
		for (int i = 0; i < MAX_CODICE_VOLO_TEMP-4; i++) {
			if (isalpha(codice_volo_temp[i])) {
			}
			else {
				printf("I primi due caratteri immessi non sono alfabetici. Il codice volo deve essere composto in questo modo: AA0123!");
				return correct;
			}
		}

		///Scorro la posizione [2]-[3]-[4]-[5] del vettore durata e controllo se sono stati inseriti dei
		/// caratteri numerici tramite la funzione isdigit(). Se la if non è verificata, stampo un errore
		/// ed esco dalla funzione con correct = 0.
		for (int p = 2; p < MAX_CODICE_VOLO_TEMP; p++) {
			if (isdigit(codice_volo_temp[p])) {
			}
			else {
				printf("Hai immesso dei caratteri errati. Il codice volo deve essere composto in questo modo: AA0123!");
				return correct;
			}
		}

		if (immesso == 1) {

			/**
			 * Dichiaro una variabile di tipo FILE
			 * che mi servirà a leggere tutti i codice volo
			 */
			FILE *input = NULL;

			///Apro il file in sola lettura.
			input = fopen("voli.dat", "rb");

			/**
			 * Struct del passeggero
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
					if(!strcmp(codice_volo_temp,elenco.codice_volo)) {
						printf("\nHai immesso un codice volo gia' esistente!\n");
						return correct;
					}
				}
			}
			///Chiudo il file
			fclose(input);

		}

		correct = 1; ///Correct sarà 1 solamente quando l'utente ha inserito un input giusto. (es. FR8252).
	}

	else {
		///Stampa un errore non appena la prima if (relativa alla lunghezza) è falsa.
		printf("Hai immesso un codice volo composto da 7 o piu' cifre. Il codice deve essere composto in questo modo: AA0123!\n");
	}
	return correct;

}

/**
 * Controlla se il nome inserito dall'utente è composto da caratteri validi,
 * ovvero da caratteri alfabetici aventi al massimo uno spazio.
 * La funzione ha codice F02a
 *
 * @pre Qualsiasi input immesso dall'utente, sarà elaborato a dovere
 * 		secondi gli opportuni controlli.
 * @post L'intero restituito sarà 1, nel caso in cui la stringa inserita sia
 * 		 formata da caratteri alfabetici.
 * 		 Sarà restituito 0 nel caso in cui ci siano più di 20 caratteri, oppure
 * 		 quando l'utente immette numeri.
 */
int ControlloNomeUtente (passeggero utenti1) {

	/**
	 * Sarà il valore di ritorno. (0 o 1).
	 */
	int correct = 0;

	/**
	 * Variabile equivalente al carattere "barra spaziatrice", ovvero a " ".
	 */
	char *barra_spaziatrice = " ";

	/**
	 * Variabile equivalente al carattere "new line", ovvero "invio".
	 */
	char *new_line = "\n";

	/**
	 * Contatore per quanti spazi sono stati inseriti.
	 */
	int spazio = 0;

	/**
	 * Lunghezza della stringa "nome" inserita dall'utente.
	 */
	int lunghezza = strlen(utenti1.nome);

	///Se la lunghezza del nome è maggiore di 20, mostra un errore.
	if (lunghezza < MAX_NOME+1) {

		///Scorro tutto il vettore e controllo se sono stati inseriti degli spazi,
		/// confrontando la variabile "char *barra_spaziatrice" precedentemente dichiarata
		/// con ogni singolo elemento del vettore. Se la if è verificata, aumento il contatore.
		for (int i = 0; i < MAX_NOME+1; i++) {
			if (utenti1.nome[i] == *barra_spaziatrice) { ///Confronto
				spazio++; ///Se la if è verificata, aumento il contatore.
			}
		}

		///Stampa un messaggio di errore se ci sono almeno 2 spazi.
		if (spazio > 1) {
			printf("Hai immesso due spazi. Ne e' ammesso solamente uno. (Es. Francesco Paolo)\n");
			return correct; ///Se la if è verificata, esco dalla funzione con correct = 0 e ripeto il tutto.
		}

		///Stampa un messaggio di errore se all'inizio è stato immesso uno spazio.
		/// Controllo solo la prima posizione del vettore con il carattere " ".
		if (utenti1.nome[0] == *barra_spaziatrice) {
			printf("Hai inserito uno spazio all'inizio. Un nome non inizia con uno spazio.\n");
			correct = 0;
			return correct; ///Se la if è verificata, esco dalla funzione con correct = 0 e ripeto il tutto.
		}

		///Stampa un messaggio di errore se all'inizio è stato immesso un carattere new line.
		/// Controllo solo la prima posizione del vettore con il carattere "\n".
		if (utenti1.nome[0] == *new_line) {
			printf("Hai inserito un carattere new line all'inizio. Un nome non inizia con un carattere new line.\n");
			correct = 0;
			return correct; ///Se la if è verificata, esco dalla funzione con correct = 0 e ripeto il tutto.
		}

		///Scorro tutto il vettore e controllo se sono stati inseriti dei numeri,
		/// attraverso la funzione isdigit(). Se la if è vericata, stampo un messaggio
		/// di errore ed esco dalla funzione con correct = 0.
		for (int i = 0; i < lunghezza; i++) {
			if (isdigit(utenti1.nome[i])) {
				printf("Hai immesso un numero. Un nome e' formato da soli caratteri!\n");
				return correct;
			}
		}

		correct = 1; ///Correct sarà 1 solamente quando l'utente ha inserito un input giusto. (es. Gianmarco).
	}
	else {
		///Stampa un errore non appena la prima if (relativa alla lunghezza) è falsa.
		printf("Hai immesso un nome piu' lungo di 20 caratteri.\n");
	}
	return correct;
}

/**
 * Controlla se il cognome inserito dall'utente è composto da caratteri validi,
 * ovvero da caratteri alfabetici aventi al massimo uno spazio.
 *
 * @pre Qualsiasi input immesso dall'utente, sarà elaborato a dovere
 * 		secondi gli opportuni controlli.
 * @post L'intero restituito sarà 1, nel caso in cui la stringa inserita sia
 * 		 formata da caratteri alfabetici.
 * 		 Sarà restituito 0 nel caso in cui ci siano più di 20 caratteri, oppure
 * 		 quando l'utente immette numeri.
 */
int ControlloCognomeUtente (passeggero utenti1) {

	/**
	 * Sarà il valore di ritorno. (0 o 1).
	 */
	int correct = 0;

	/**
	 * Lunghezza della stringa "cognome" inserita dall'utente.
	 */
	int lunghezza = strlen(utenti1.cognome);

	///Se la lunghezza del cognome è maggiore di 20, mostra un errore.
	if (lunghezza < MAX_COGNOME+1) {

		///Scorro tutto il vettore e controllo se sono stati inseriti dei caratteri alfabetici,
		/// attraverso la funzione isalpha(). Se la if non è vericata, stampo un messaggio
		/// di errore ed esco dalla funzione con correct = 0.
		for (int i = 0; i < lunghezza; i++) {
			if (isalpha(utenti1.cognome[i])) {
			}
			else {
				printf("Hai immesso un numero. Un cognome e' formato da soli caratteri!\n");
				return correct;
			}
		}
		correct = 1; ///Correct sarà 1 solamente quando l'utente ha inserito un input giusto. (es. Gianmarco).
	}
	else {
		///Stampa un errore non appena la prima if (relativa alla lunghezza) è falsa.
		printf("Hai immesso un nome piu' lungo di 20 caratteri.\n");
	}
	return correct;
}

/**
 * Controlla se il mese di nascita dell'utente è composto da caratteri validi,
 * ovvero da caratteri numerici.
 * La funzione è identica a ControlloMese(), solo che qui è passata la struct
 * del passeggero e non dei voli, come accadeva precedentemente.
 *
 * @pre Qualsiasi input immesso dall'utente, sarà elaborato a dovere
 * 		secondi gli opportuni controlli.
 * @post L'intero restituito sarà 1, nel caso in cui la stringa inserita sia
 * 		 formata da caratteri numerici e siano stati inseriti meno di 3 caratteri.
 * 		 Sarà restituito 0 nel caso in cui ci siano più di 2 caratteri, oppure
 * 		 quando il mese è maggiore di 12 (Dicembre) o minore di 01 (Gennaio).
 */
int ControlloMeseUtente (passeggero utenti1) {

	/**
	 * Sarà il valore di ritorno. (0 o 1).
	 */
	int correct = 0;

	/**
	 * Lunghezza della stringa "mese" inserita dall'utente.
	 */
	int lunghezza = strlen(utenti1.datadinascita.mese);

	///Se la lunghezza del mese è maggiore di 2, mostra un errore.
	if (lunghezza < MAX_MESE+1) {
		///Scorrendo la posizione [0] e [1] del vettore, controllo se è stato immesso un carattere.
		/// Se la condizione è vera, stampo a video un errore.
		if (isalpha(utenti1.datadinascita.mese[0]) || isalpha(utenti1.datadinascita.mese[1]))
		{
			printf("Hai inserito un carattere. Riprova.\n");
		}
		///Se la condizione precedente non è verificata, allora procedo nel controllare se il numero inserito
		/// sia maggiore di 01 (Gennaio) o minore di 12 (Dicembre). Se il valore è errato, stampo a video un errore.
		else if ((strcmp(utenti1.datadinascita.mese, "12") > 0 ) || (strcmp(utenti1.datadinascita.mese, "01") < 0))  {
			printf("Hai immesso un mese errato. Deve essere compreso tra 01 (Gennaio) e 12 (Dicembre).\n");
		}
		else
		{
			correct = 1; /// Correct sarà uguale a 1 quando l'input del mese è corretto.
		}
	}
	else {
		///Stampa un errore non appena la prima if (relativa alla lunghezza) è falsa.
		printf("Hai immesso un mese composto da piu' di 3 cifre. Deve essere formato da 2 cifre!\n");
	}
	return correct;
}

/**
 * Controlla se il giorno di nascita dell'utente è composto da caratteri validi,
 * ovvero da caratteri numerici.
 * La funzione è identica a ControlloGiorno(), solo che qui è passata la struct
 * del passeggero e non dei voli, come accadeva precedentemente.
 *
 * @pre Qualsiasi input immesso dall'utente, sarà elaborato a dovere
 * 		secondi gli opportuni controlli.
 * @post L'intero restituito sarà 1, nel caso in cui la stringa inserita sia
 * 		 formata da caratteri numerici e siano stati inseriti meno di 3 caratteri.
 * 		 Sarà restituito 0 nel caso in cui ci siano più di 2 caratteri, oppure
 * 		 quando il massimo/minimo giorno di un determinato mese non coincide.
 */
int ControlloGiornoUtente (passeggero utenti1) {

	/**
	 * Sarà il valore di ritorno. (0 o 1).
	 */
	int correct = 0;

	/**
	 * Variabile che contiene il numero la stringa stringa "mese",
	 * inserita precedentemente dall'utente, convertita in intero
	 */
	int mese = atoi(utenti1.datadinascita.mese);

	/**
	 * Lunghezza della stringa "giorno" inserita dall'amministratore.
	 */
	int lunghezza = strlen(utenti1.datadinascita.giorno);

	///Se la lunghezza del giorno è maggiore di 2, mostra un errore.
	if (lunghezza < MAX_GIORNO+1) {
		///Tramite una switch, assegno un determinato controllo a determinati mesi dell'anno.
		/// La switch esamina il mese, convertito in numero precedentemente e sceglie il "case" corrispondente.
		switch(mese)
		{
		case 4:
		case 6: ///Aprile - Giugno - Settembre - Novembre.
		case 9:
		case 11:
			///Scorro la posizione [0] e [1] dei due vettori e controllo se sono stati inseriti dei
			/// caratteri alfabetici tramite la funzione isalpha(). Se la if è verificata, stampo un errore
			/// ed esco dalla funzione con correct = 0.
			if (isalpha(utenti1.datadinascita.giorno[0]) || isalpha(utenti1.datadinascita.giorno[1]))
			{
				printf("Hai inserito un carattere. Riprova.\n");
			}
			///Se la condizione precedente non è verificata, allora passo al controllo del giorno, il quale deve
			/// essere compreso tra 30 e 01.
			else if ((strcmp(utenti1.datadinascita.giorno, "30") > 0 ) || (strcmp(utenti1.datadinascita.giorno, "01") < 0))  {
				printf("Hai immesso un giorno del mese errato. Deve essere compreso tra 01 e 30.\n");
			}
			else
			{
				correct = 1; ///Correct sarà 1 solamente quando l'utente ha inserito un input giusto. (es. 30 Aprile).
			}
			return correct;
			break;
		case 2: ///Febbraio
			///Scorro la posizione [0] e [1] dei due vettori e controllo se sono stati inseriti dei
			/// caratteri alfabetici tramite la funzione isalpha(). Se la if è verificata, stampo un errore
			/// ed esco dalla funzione con correct = 0.
			if (isalpha(utenti1.datadinascita.giorno[0]) || isalpha(utenti1.datadinascita.giorno[1]))
			{
				printf("Hai inserito un carattere. Riprova.\n");
			}
			///Se la condizione precedente non è verificata, allora passo al controllo del giorno, il quale deve
			/// essere compreso tra 29 e 01.
			else if ((strcmp(utenti1.datadinascita.giorno, "29") > 0 ) || (strcmp(utenti1.datadinascita.giorno, "01") < 0))  {
				printf("Hai immesso un giorno del mese errato. Deve essere compreso tra 01 e 29.\n");
			}
			else
			{
				correct = 1; ///Correct sarà 1 solamente quando l'utente ha inserito un input giusto. (es. 25 Febbraio).
			}
			return correct;
			break;
		default: /// Gennaio - Marzo - Maggio - Luglio - Agosto - Ottobre - Dicembre
			///Scorro la posizione [0] e [1] dei due vettori e controllo se sono stati inseriti dei
			/// caratteri alfabetici tramite la funzione isalpha(). Se la if è verificata, stampo un errore
			/// ed esco dalla funzione con correct = 0.
			if (isalpha(utenti1.datadinascita.giorno[0]) || isalpha(utenti1.datadinascita.giorno[1]))
			{
				printf("Hai inserito un carattere. Riprova.\n");
			}
			///Se la condizione precedente non è verificata, allora passo al controllo del giorno, il quale deve
			/// essere compreso tra 31 e 01.
			else if ((strcmp(utenti1.datadinascita.giorno, "31") > 0 ) || (strcmp(utenti1.datadinascita.giorno, "01") < 0))  {
				printf("Hai immesso un giorno del mese errato. Deve essere compreso tra 01 e 31.\n");
			}
			else
			{
				correct = 1; ///Correct sarà 1 solamente quando l'utente ha inserito un input giusto. (es. 27 Marzo).
			}
			return correct;
			break;
		}
	}
	else {
		///Stampa un errore non appena la prima if (relativa alla lunghezza) è falsa.
		printf("Hai immesso un giorno composto da piu' di 3 cifre. Deve essere formato da 2 cifre!\n");
	}
	return correct;
}

/**
 * Controlla se l'anno di nascita dell'utente è composto da caratteri validi,
 * ovvero da caratteri numerici.
 * La funzione è identica a ControlloAnno(), solo che qui è passata la struct
 * del passeggero e non dei voli, come accadeva precedentemente.
 *
 * @pre Qualsiasi input immesso dall'utente, sarà elaborato a dovere
 * 		secondi gli opportuni controlli.
 * @post L'intero restituito sarà 1, nel caso in cui la stringa inserita sia
 * 		 formata da caratteri numerici e siano stati inseriti meno di 3 caratteri.
 * 		 Sarà restituito 0 nel caso in cui ci siano più di 4 caratteri, meno di 4 caratteri
 * 		 oppure quando l'utente immette un anno maggiore di 2002 o minore di 1945.
 */
int ControlloAnnoUtente (passeggero utenti1) {

	/**
	 * Sarà il valore di ritorno. (0 o 1).
	 */
	int correct = 0;

	/**
	 * Lunghezza della stringa "anno" inserita dall'utente.
	 */
	int lunghezza = strlen(utenti1.datadinascita.anno);

	///Se la lunghezza dell'anno non è esattamente di 4 caratteri, mostra un errore.
	if ((lunghezza < MAX_ANNO+1) && (lunghezza > MAX_ANNO-1)) {

		///Scorro la posizione [0]-[1]-[2]-[3] del vettore anno e controllo se sono stati inseriti dei
		/// caratteri alfabetici tramite la funzione isalpha(). Se la if è verificata, stampo un errore
		/// ed esco dalla funzione con correct = 0.
		if (isalpha(utenti1.datadinascita.anno[0]) || isalpha(utenti1.datadinascita.anno[1]) || isalpha(utenti1.datadinascita.anno[2]) ||  isalpha(utenti1.datadinascita.anno[3]))
		{
			printf("Hai inserito un carattere. Riprova.\n");
		}
		///Se la condizione precedente non è verificata, allora passo al controllo dell'anno, il quale deve
		/// essere compreso tra 1945 e 2002.
		else if ((strcmp(utenti1.datadinascita.anno, "2001") > 0 ) || (strcmp(utenti1.datadinascita.anno, "1945") < 0))  {
			printf("Hai immesso un anno errato. Deve essere compreso tra 1945 e 2001.\n");
		}
		else
		{
			correct = 1; ///Correct sarà 1 solamente quando l'utente ha inserito un input giusto. (es. 1999).
		}
	}
	else {
		///Stampa un errore non appena la prima if (relativa alla lunghezza) è falsa.
		printf("Hai immesso un anno composto da piu' di 4 cifre, oppure da meno di 4 cifre. Deve essere formato da esattamente 4 cifre!\n");
	}
	return correct;
}

/**
 * Controlla se il luogo di nascita dell'utente è composto da caratteri validi,
 * ovvero da caratteri alfabetici.
 *
 * @pre Qualsiasi input immesso dall'utente, sarà elaborato a dovere
 * 		secondi gli opportuni controlli.
 * @post L'intero restituito sarà 1, nel caso in cui la stringa inserita sia
 * 		 formata da caratteri alfabetici e siano stati inseriti meno di 15 caratteri.
 * 		 Sarà restituito 0 nel caso in cui ci siano più di 15 caratteri, oppure
 * 		 quando l'utente immette dei caratteri numerici.
 */
int ControlloLuogoDiNascita (passeggero utenti1) {

	/**
	 * Sarà il valore di ritorno. (0 o 1).
	 */
	int correct = 0;

	/**
	 * Lunghezza della stringa "luogodinascita" inserita dall'utente.
	 */
	int lunghezza = strlen(utenti1.luogodinascita);

	///Se la lunghezza della stringa è maggiore a 15, mostra un errore.
	if (lunghezza < MAX_LUOGO_DI_NASCITA+1) {

		///Scorro tutto il vettore e controllo se sono stati inseriti dei
		/// caratteri alfabetici tramite la funzione isalpha(). Se la if non è verificata
		/// stampo un errore ed esco dalla funzione con correct = 0.
		for (int i = 0; i < lunghezza; i++) {
			if (isalpha(utenti1.luogodinascita[i])) {
			}
			else {
				printf("Hai immesso un numero. Un comune e' formato da soli caratteri!\n");
				return correct;
			}
		}
		correct = 1; ///Correct sarà 1 solamente quando l'utente ha inserito un input giusto. (es. Bari).
	}
	else {
		///Stampa un errore non appena la prima if (relativa alla lunghezza) è falsa.
		printf("Hai immesso un comune piu' lungo di 15 caratteri.\n");
	}
	return correct;
}

/**
 * Controlla se il passaporto/carta d'identità inserito dall'utente
 * è composto da caratteri validi, ovvero dai primi 2 caratteri alfabetici
 * e i restanti 7 da caratteri numerici. La stringa deve essere formata da
 * 9 caratteri.
 * La funzione ha codice F02b
 *
 * @pre Qualsiasi input immesso dall'utente, sarà elaborato a dovere
 * 		secondi gli opportuni controlli.
 * @post L'intero restituito sarà 1, nel caso in cui la stringa inserita sia
 * 		 formata dai primi 2 caratteri alfabetici e i restanti 7, caratteri numerici.
 * 		 Sarà restituito 0 in tutti gli altri casi, ovvero quando non è composto esattamente
 * 		 da 9 caratteri oppure quando si sbagliano le posizioni dei numeri/lettere.
 */
int ControlloNumeroPassaporto (char *passaporto_temp, int MAX_PASSAPORTO_TEMP) {

	/**
	 * Sarà il valore di ritorno. (0 o 1).
	 */
	int correct = 0;

	/**
	 * Lunghezza della stringa "passaporto_temp" inserita dall'utente.
	 */
	int lunghezza = strlen(passaporto_temp);

	///Se la lunghezza della stringa non è esattamente di 9 caratteri, mostra un errore.
	if ((lunghezza < MAX_PASSAPORTO_TEMP+1) && (lunghezza == MAX_PASSAPORTO_TEMP)) {

		///Scorro le posizioni [0]-[1] del vettore e controllo se sono stati inseriti dei
		/// caratteri alfabetici tramite la funzione isalpha(). Se la if non è verificata
		/// stampo un errore ed esco dalla funzione con correct = 0.
		for (int i = 0; i < MAX_PASSAPORTO_TEMP-8; i++) {
			if (isalpha(passaporto_temp[i])) {
			}
			else {
				printf("I primi due caratteri immessi non sono alfabetici. Il numero del passaporto deve essere composto in questo modo: AA0123456!\n");
				return correct;
			}
		}

		///Scorro la posizione [2]-[3]-[4]-[5]-[6]-[7] del vettore durata e controllo se sono stati inseriti dei
		/// caratteri numerici tramite la funzione isdigit(). Se la if non è verificata, stampo un errore
		/// ed esco dalla funzione con correct = 0.
		for (int p = 2; p < MAX_PASSAPORTO_TEMP; p++) {
			if (isdigit(passaporto_temp[p])) {
			}
			else {
				printf("Hai immesso dei caratteri errati. Il numero del passaporto deve essere composto in questo modo: AA0123456!\n");
				return correct;
			}
		}

		/**
		 * Dichiaro una variabile di tipo FILE
		 * che mi servirà a leggere tutti i passaporti
		 */
		FILE *input = NULL;

		///Apro il file in sola lettura.
		input = fopen("passeggeri.dat", "rb");

		/**
		 * Struct del passeggero
		 */
		passeggero utenti;

		///Leggi il file finchè read non arriva a 0.
		int read = 1;

		while( read != 0)
		{
			/// Quando read arriva a 0, significa che il file è finito.
			read = fread(&utenti, sizeof(passeggero), 1, input);

			if ( read > 0) {

				///Se il passaporto che l'utente ha immesso coincide con almeno un passaporto già presente nel sistema,
				/// stampa un errore e ripeti il tutto.
				if(!strcmp(passaporto_temp,utenti.numeropassaporto)) {
					printf("\nHai immesso un passaporto gia' esistente!\n");
					return correct;
				}
			}
		}
		///Chiudo il file
		fclose(input);

		correct = 1; ///Correct sarà 1 solamente quando l'utente ha inserito un input giusto. (es. AA1234567).
	}
	else {
		///Stampa un errore non appena la prima if (relativa alla lunghezza) è falsa.
		printf("Hai immesso un numero passaporto da 8 o piu' cifre, oppure un numero di passaporto troppo corto.\nIl numero del passaporto deve essere composto in questo modo: AA0123456!\n");
	}
	return correct;
}

/**
 * Controlla se il passaporto/carta d'identità inserito dall'utente
 * è composto da caratteri validi, ovvero dai primi 2 caratteri alfabetici
 * e i restanti 7 da caratteri numerici. La stringa deve essere formata da
 * 9 caratteri.
 * Ha le medesime funzionalità di ControlloNumeroPassaporto(), solo che in questo
 * caso, la funzione è dedicata per l'identificazione dell'utente.
 * La funzione ha codice F06a
 *
 * @pre Qualsiasi input immesso dall'utente, sarà elaborato a dovere
 * 		secondi gli opportuni controlli.
 * @post L'intero restituito sarà 1, nel caso in cui la stringa inserita sia
 * 		 formata dai primi 2 caratteri alfabetici e i restanti 7 caratteri numerici.
 * 		 Sarà restituito 0 in tutti gli altri casi, ovvero quando non è composto esattamente
 * 		 da 9 caratteri oppure quando si sbagliano le posizioni dei/delle numeri/lettere.
 */
int ControlloPassaportoTemporaneo (char *passaporto_temporaneo, int MAX_PASS, int modifica_pass) {

	/**
	 * Sarà il valore di ritorno. (0 o 1).
	 */
	int correct = 0;

	/**
	 * Lunghezza della stringa "numeropassaporto" inserita dall'utente.
	 */
	int lunghezza = strlen(passaporto_temporaneo);

	///Se la lunghezza della stringa è inferiore a 9 caratteri, mostra un errore.
	if (lunghezza < MAX_PASS+1) {

		///Scorro le posizioni [0]-[1] del vettore e controllo se sono stati inseriti dei
		/// caratteri alfabetici tramite la funzione isalpha(). Se la if non è verificata
		/// stampo un errore ed esco dalla funzione con correct = 0.
		for (int i = 0; i < MAX_PASS-8; i++) {
			if (isalpha(passaporto_temporaneo[i])) {
			}
			else {
				printf("I primi due caratteri immessi non sono alfabetici. Il numero del passaporto deve essere composto in questo modo: AA0123456!\n");
				return correct;
			}
		}

		///Scorro la posizione [2]-[3]-[4]-[5]-[6]-[7] del vettore durata e controllo se sono stati inseriti dei
		/// caratteri numerici tramite la funzione isdigit(). Se la if non è verificata, stampo un errore
		/// ed esco dalla funzione con correct = 0.
		for (int p = 2; p < MAX_PASS; p++) {
			if (isdigit(passaporto_temporaneo[p])) {
			}
			else {
				printf("Hai immesso dei caratteri errati. Il numero del passaporto deve essere composto in questo modo: AA0123456!\n");
				return correct;
			}
		}

		if (modifica_pass == 1) {
		/**
		 * Dichiaro una variabile di tipo FILE
		 * che mi servirà a leggere tutti i passaporti
		 */
		FILE *input = NULL;

		///Apro il file in sola lettura.
		input = fopen("passeggeri.dat", "rb");

		/**
		 * Struct del passeggero
		 */
		passeggero utenti;

		///Leggi il file finchè read non arriva a 0.
		int read = 1;

		while( read != 0)
		{
			/// Quando read arriva a 0, significa che il file è finito.
			read = fread(&utenti, sizeof(passeggero), 1, input);

			if ( read > 0) {

				///Se il passaporto che l'utente ha immesso coincide con almeno un passaporto già presente nel sistema,
				/// stampa un errore e ripeti il tutto.
				if(!strcmp(passaporto_temporaneo,utenti.numeropassaporto)) {
					printf("\nHai immesso un passaporto gia' esistente!\n");
					return correct;
				}
			}
		}
		///Chiudo il file
		fclose(input);

		}

		correct = 1; ///Correct sarà 1 solamente quando l'utente ha inserito un input giusto. (es. AA1234567).
	}
	else {
		///Stampa un errore non appena la prima if (relativa alla lunghezza) è falsa.
		printf("Hai immesso un numero passaporto da 8 o piu' cifre, oppure un numero di passaporto troppo corto.\nIl numero del passaporto deve essere composto in questo modo: AA0123456!\n");
	}
	return correct;
}

/**
 * Controlla se il codice prenotazione inserito dall'utente al momento
 * del check-in è composto da caratteri validi, ovvero dai primi 2 caratteri alfabetici
 * e i restanti 3 da caratteri numerici. La stringa deve essere formata da
 * 5 caratteri.
 *
 * @pre Qualsiasi input immesso dall'utente, sarà elaborato a dovere
 * 		secondi gli opportuni controlli.
 * @post L'intero restituito sarà 1, nel caso in cui la stringa inserita sia
 * 		 formata dai primi 2 caratteri alfabetici e i restanti 3, caratteri numerici.
 * 		 Sarà restituito 0 in tutti gli altri casi, ovvero quando non è composto esattamente
 * 		 da 5 caratteri oppure quando si sbagliano le posizioni dei numeri/lettere.
 */
int ControlloCodicePrenotazione (char *codice_prenotazione_temporaneo, int MAX_PREN) {

	/**
	 * Sarà il valore di ritorno. (0 o 1).
	 */
	int correct2 = 0;

	/**
	 * Lunghezza della stringa "codice_prenotazione_temporaneo" inserita dall'utente.
	 */
	int lunghezza = strlen(codice_prenotazione_temporaneo);

	///Se la lunghezza della stringa è inferiore a 5 caratteri, mostra un errore.
	if (lunghezza < MAX_PREN+1) {

		///Scorro le posizioni [0]-[1] del vettore e controllo se sono stati inseriti dei
		/// caratteri alfabetici tramite la funzione isalpha(). Se la if non è verificata
		/// stampo un errore ed esco dalla funzione con correct = 0.
		for (int i = 0; i < MAX_PREN-4; i++) {
			if (isalpha(codice_prenotazione_temporaneo[i])) {
			}
			else {
				printf("I primi due caratteri immessi non sono alfabetici. Il codice prenotazione deve essere composto in questo modo: AA123!\n");
				return correct2;
			}
		}

		///Scorro la posizione [2]-[3]-[4]-[5] del vettore codice_prenotazione_temporaneo e controllo se sono stati inseriti dei
		/// caratteri numerici tramite la funzione isdigit(). Se la if non è verificata, stampo un errore
		/// ed esco dalla funzione con correct = 0.
		for (int p = 2; p < MAX_PREN; p++) {
			if (isdigit(codice_prenotazione_temporaneo[p])) {
			}
			else {
				printf("Hai immesso dei caratteri errati. Il codice prenotazione deve essere composto in questo modo: AA123!\n");
				return correct2;
			}
		}
		correct2 = 1; ///Correct sarà 1 solamente quando l'utente ha inserito un input giusto. (es. AA123).
	}
	else {
		///Stampa un errore non appena la prima if (relativa alla lunghezza) è falsa.
		printf("Hai immesso un codice prenotazione composto da 6 o piu' cifre. Il codice prenotazione deve essere composto in questo modo: AA123!\n");
	}
	return correct2;
}

/**
 * La funzione, dati due vettori di numeri e caratteri, genera una stringa
 * formata da esattamente 2 caratteri iniziali e 3 numerici.
 * La stringa sarà quindi formata da 5 caratteri in tutto.
 *
 * @pre La funzione non ha bisogno di rispettare alcun pre-condizione
 * 		dato che funziona in ogni caso.
 * @post La stringa restituita sarà formata dai primi 2 caratteri alfabetici
 * 		 e i dai restanti 3 caratteri numerici.
 */
char* GeneraCodicePrenotazione() {

	/**
	 * Contatore
	 */
	int i = 0;

	/**
	 * Vettore di char nella quale immagazzino numeri da 0 a 9.
	 */
	char numeri_random[] = "0123456789";

	/**
	 * Vettore di char nella quale immagazzino tutte le lettere dell'alfabeto.
	 */
	char caratteri_random[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	/**
	 * Sarà la stringa restituita. E' una static char dato che la "return"
	 * deve restituire l'indirizzo della variabile, che viene distrutto nel passaggio
	 * nel caso in cui non la dichiaro "static".
	 */
	static char prenotazione[MAX_CODICE_PRENOTAZIONE+1]; ///


	///Scorro la posizione [0]-[1] del vettore e gli assegno a ciascuna posizione
	/// un carattere alfabetico estratto random dal vettore caratteri_random[]
	for (i = 0; i < 2; i++) {
		prenotazione[i] = caratteri_random[rand() % (sizeof(caratteri_random) - 1)];
	}

	///Scorro la posizione [2]-[3]-[4] del vettore e gli assegno a ciascuna posizione
	/// un carattere numerico estratto random dal vettore numeri_random[]
	for (i = 2; i < 5; i++) {
		prenotazione[i] = numeri_random[rand() % (sizeof(numeri_random) - 1)];
	}

	///Per evitare problemi o output indesiderati, l'ultima posizione [5]
	/// avrà il carattere nullo.
	prenotazione[5] = '\0';

	return prenotazione;
}

/**
 * La funzione, dato un vettore e un intero, controlla (a seconda dell'intero)
 * se il vettore è stata scritta nella maniera appropriata. In questo caso
 * se l'intero è 0, allora la stringa deve essere composta solo da numeri e deve
 * essere composta da meno di 2 cifre. Nel caso contrario, se l'intero è 1,
 * allora la stringa deve essere composta da meno di 3 cifre.
 *
 * @pre La funzione ha bisogno che l'utente inserisca una stringa e che
 * 		l'opzione sia scritta all'intero della chiamata di funzione.
 * @post L'intero restituito sarà 1 se la stringa è scritta correttamente,
 * 		 sarà 0 se non è stata scritta correttamente.
 */
int ControlloMenu(char *array, int opzione) {

	/**
	 * Lunghezza della stringa inserita dall'utente.
	 */
	int lunghezza = strlen(array);

	///Se opzione è uno, significa che sono nel menu amministratore (che comprende cifre > 9)
	if (opzione == 1) {

		///Se la lunghezza della stringa è superiore a 2 caratteri, mostra un errore.
		if (lunghezza < MAX_SCELTA+1) {

			///Scorro le posizioni [0]-[1] del vettore e controllo se sono stati inseriti dei
			/// caratteri alfabetici tramite la funzione isalpha(). Se la if è verificata
			/// stampo un errore ed esco dalla funzione con return = 0.
			for (int i = 0; i < MAX_SCELTA; i++) {
				if (isalpha(array[i])) {
					printf("\nHai immesso dei caratteri errati!\n");
					return 0;
				}
			}
		}
		else {
			///Stampa un errore non appena la prima if (relativa alla lunghezza) è falsa.
			printf("Hai immesso una scelta troppo lunga! Deve contenere al massimo 1 carattere, non %d!", lunghezza);
			return 0;
		}

	}

	///Se opzione è uno, significa che sono nel menu utente (che comprende cifre < 10)
	if (opzione == 0) {

		///Se la lunghezza della stringa è superiore ad 1 carattere, mostra un errore.
		if (lunghezza < MAX_SCELTA) {

			///Scorro le posizioni [0]-[1] del vettore e controllo se sono stati inseriti dei
			/// caratteri alfabetici tramite la funzione isalpha(). Se la if è verificata
			/// stampo un errore ed esco dalla funzione con return = 0.
			for (int i = 0; i < MAX_SCELTA; i++) {
				if (isalpha(array[i])) {
					printf("\nHai immesso dei caratteri errati!\n");
					return 0;
				}
			}
		}
		else {
			///Stampa un errore non appena la prima if (relativa alla lunghezza) è falsa.
			printf("Hai immesso una scelta troppo lunga! Deve contenere al massimo 1 carattere, non %d!", lunghezza);
			return 0;
		}

	}

	///Ritorno 1, solo se la stringa inserita è giusta
	return 1;
}

/**
 * Controlla se il nome inserito dall'amministratore al momento della ricerca
 * tramite "nome" è composto da caratteri validi, ovvero da caratteri
 * alfabetici aventi al massimo uno spazio.
 * Ha la stessa funzionalità di ControlloNomeUtente(), solo che in
 * questo caso, viene usata per poter poi successivamente cercare
 * il nome richiesto nel file dei passeggeri.
 *
 * @pre Qualsiasi input immesso dall'amministratore, sarà elaborato a dovere
 * 		secondi gli opportuni controlli.
 * @post L'intero restituito sarà 1, nel caso in cui la stringa inserita sia
 * 		 formata da caratteri alfabetici.
 * 		 Sarà restituito 0 nel caso in cui ci siano più di 20 caratteri, oppure
 * 		 quando l'utente immette numeri.
 */
int ControlloNomeTemporaneo (char *temp, int MAX_NOME_TEMP) {

	/**
	 * Sarà il valore di ritorno. (0 o 1).
	 */
	int correct = 0;

	/**
	 * Variabile equivalente al carattere "barra spaziatrice", ovvero a " ".
	 */
	char *barra_spaziatrice = " ";

	/**
	 * Variabile equivalente al carattere "new line", ovvero "invio".
	 */
	char *new_line = "\n";

	/**
	 * Contatore per quanti spazi sono stati inseriti.
	 */
	int spazio = 0;

	/**
	 * Lunghezza della stringa "nome" inserita dall'amministratore.
	 */
	int lunghezza = strlen(temp);

	///Se la lunghezza del nome è maggiore di 20, mostra un errore.
	if (lunghezza < MAX_NOME_TEMP+1) {

		///Scorro tutto il vettore e controllo se sono stati inseriti degli spazi,
		/// confrontando la variabile "char *barra_spaziatrice" precedentemente dichiarata
		/// con ogni singolo elemento del vettore. Se la if è vericata, aumento il contatore.
		for (int i = 0; i < MAX_NOME_TEMP+1; i++) {
			if (temp[i] == *barra_spaziatrice) { ///Confronto
				spazio++; ///Se la if è verificata, aumento il contatore.
			}
		}

		///Stampa un messaggio di errore se ci sono almeno 2 spazi.
		if (spazio > 1) {
			printf("Hai immesso due spazi. Ne e' ammesso solamente uno. (Es. Francesco Paolo)\n");
			return correct; ///Se la if è verificata, esco dalla funzione con correct = 0 e ripeto il tutto.
		}

		///Stampa un messaggio di errore se all'inizio è stato immesso uno spazio.
		/// Controllo solo la prima posizione del vettore con il carattere " ".
		if (temp[0] == *barra_spaziatrice) {
			printf("Hai inserito uno spazio all'inizio. Un nome non inizia con uno spazio.\n");
			correct = 0;
			return correct; ///Se la if è verificata, esco dalla funzione con correct = 0 e ripeto il tutto.
		}

		///Stampa un messaggio di errore se all'inizio è stato immesso un carattere new line.
		/// Controllo solo la prima posizione del vettore con il carattere "\n".
		if (temp[0] == *new_line) {
			printf("Hai inserito un carattere new line all'inizio. Un nome non inizia con un carattere new line.\n");
			correct = 0;
			return correct; ///Se la if è verificata, esco dalla funzione con correct = 0 e ripeto il tutto.
		}

		///Scorro tutto il vettore e controllo se sono stati inseriti dei numeri,
		/// attraverso la funzione isdigit(). Se la if è verificata, stampo un messaggio
		/// di errore ed esco dalla funzione con correct = 0.
		for (int i = 0; i < lunghezza; i++) {
			if (isdigit(temp[i])) {
				printf("Hai immesso un numero. Un nome e' formato da soli caratteri!\n");
				return correct;
			}
		}

		correct = 1; ///Correct sarà 1 solamente quando l'utente ha inserito un input giusto. (es. Gianmarco).
	}
	else {
		///Stampa un errore non appena la prima if (relativa alla lunghezza) è falsa.
		printf("Hai immesso un nome piu' lungo di 20 caratteri.\n");
	}
	return correct;
}

/**
 * Controlla se il cognome inserito dall'amministratore al momento della ricerca
 * tramite "cognome" è composto da caratteri validi, ovvero da caratteri
 * alfabetici aventi al massimo uno spazio.
 * Ha la stessa funzionalità di ControlloCognomeUtente(), solo che in
 * questo caso, viene usata per poter poi successivamente cercare
 * il cognome richiesto nel file dei passeggeri.
 *
 * @pre Qualsiasi input immesso dall'amministratore, sarà elaborato a dovere
 * 		secondi gli opportuni controlli.
 * @post L'intero restituito sarà 1, nel caso in cui la stringa inserita sia
 * 		 formata da caratteri alfabetici.
 * 		 Sarà restituito 0 nel caso in cui ci siano più di 20 caratteri, oppure
 * 		 quando l'utente immette numeri.
 */
int ControlloCognomeTemporaneo (char *temp, int MAX_COGNOME_TEMP) {

	/**
	 * Sarà il valore di ritorno. (0 o 1).
	 */
	int correct = 0;

	/**
	 * Lunghezza della stringa "cognome" inserita dall'amministratore.
	 */
	int lunghezza = strlen(temp);

	///Se la lunghezza del cognome è maggiore di 20, mostra un errore.
	if (lunghezza < MAX_COGNOME_TEMP+1) {

		///Scorro tutto il vettore e controllo se sono stati inseriti dei caratteri alfabetici,
		/// attraverso la funzione isalpha(). Se la if non è vericata, stampo un messaggio
		/// di errore ed esco dalla funzione con correct = 0.
		for (int i = 0; i < lunghezza; i++) {
			if (isalpha(temp[i])) {
			}
			else {
				printf("Hai immesso un numero. Un cognome e' formato da soli caratteri!\n");
				return correct;
			}
		}
		correct = 1; ///Correct sarà 1 solamente quando l'amministratore ha inserito un input giusto. (es. Gianmarco).
	}
	else {
		///Stampa un errore non appena la prima if (relativa alla lunghezza) è falsa.
		printf("Hai immesso un nome piu' lungo di 20 caratteri.\n");
	}
	return correct;
}

/**
 * Controlla se il mese di nascita inserito dall'amministratore al momento della
 * ricerca di utenti tramite "Data di nascita" è composto da caratteri validi,
 * ovvero da caratteri numerici.
 * Ha la stessa funzionalità di ControlloMeseUtente(), solo che in
 * questo caso, viene usata per poter poi successivamente cercare
 * la data di nascita richiesta nel file dei passeggeri.
 *
 * @pre Qualsiasi input immesso dall'amministratore, sarà elaborato a dovere
 * 		secondi gli opportuni controlli.
 * @post L'intero restituito sarà 1, nel caso in cui la stringa inserita sia
 * 		 formata da caratteri numerici e siano stati inseriti meno di 3 caratteri.
 * 		 Sarà restituito 0 nel caso in cui ci siano più di 2 caratteri, oppure
 * 		 quando il mese è maggiore di 12 (Dicembre) o minore di 01 (Gennaio).
 */
int ControlloMeseTemporaneo (char *temp, int MAX_MESE_TEMP) {

	/**
	 * Sarà il valore di ritorno. (0 o 1).
	 */
	int correct = 0;

	/**
	 * Lunghezza della stringa "mese" inserita dall'utente.
	 */
	int lunghezza = strlen(temp);

	///Se la lunghezza del mese è maggiore di 2, mostra un errore.
	if (lunghezza < MAX_MESE_TEMP+1) {
		///Scorrendo la posizione [0] e [1] del vettore, controllo se è stato immesso un carattere.
		/// Se la condizione è vera, stampo a video un errore.
		if (isalpha(temp[0]) || isalpha(temp[1]))
		{
			printf("Hai inserito un carattere. Riprova.\n");
		}
		///Se la condizione precedente non è verificata, allora procedo nel controllare se il numero inserito
		/// sia maggiore di 01 (Gennaio) o minore di 12 (Dicembre). Se il valore è errato, stampo a video un errore.
		else if ((strcmp(temp, "12") > 0 ) || (strcmp(temp, "01") < 0))  {
			printf("Hai immesso un mese errato. Deve essere compreso tra 01 (Gennaio) e 12 (Dicembre).\n");
		}
		else
		{
			correct = 1; /// Correct sarà uguale a 1 quando l'input del mese è corretto.
		}
	}
	else {
		///Stampa un errore non appena la prima if (relativa alla lunghezza) è falsa.
		printf("Hai immesso un mese composto da piu' di 3 cifre. Deve essere formato da 2 cifre!\n");
	}
	return correct;
}

/**
 * Controlla se il giorno di nascita inserito dall'amministratore al momento della
 * ricerca di utenti tramite "Data di nascita" è composto da caratteri validi,
 * ovvero da caratteri numerici.
 * Ha la stessa funzionalità di ControlloGiornoUtente(), solo che in
 * questo caso, viene usata per poter poi successivamente cercare
 * la data di nascita richiesta nel file dei passeggeri.
 *
 * @pre Qualsiasi input immesso dall'utente, sarà elaborato a dovere
 * 		secondi gli opportuni controlli.
 * @post L'intero restituito sarà 1, nel caso in cui la stringa inserita sia
 * 		 formata da caratteri numerici e siano stati inseriti meno di 3 caratteri.
 * 		 Sarà restituito 0 nel caso in cui ci siano più di 2 caratteri, oppure
 * 		 quando il massimo/minimo giorno di un determinato mese non coincide.
 */
int ControlloGiornoTemporaneo (char *temp, char *temp_mese, int MAX_GIORNO_TEMP) {

	/**
	 * Sarà il valore di ritorno. (0 o 1).
	 */
	int correct = 0;

	/**
	 * Variabile che contiene il numero la stringa stringa "mese",
	 * inserita precedentemente dall'utente, convertita in intero
	 */
	int mese = atoi(temp_mese);

	/**
	 * Lunghezza della stringa "giorno" inserita dall'amministratore.
	 */
	int lunghezza = strlen(temp);

	///Se la lunghezza del giorno è maggiore di 2, mostra un errore.
	if (lunghezza < MAX_GIORNO_TEMP+1) {
		///Tramite una switch, assegno un determinato controllo a determinati mesi dell'anno.
		/// La switch esamina il mese, convertito in numero precedentemente e sceglie il "case" corrispondente.
		switch(mese)
		{
		case 4:
		case 6: ///Aprile - Giugno - Settembre - Novembre.
		case 9:
		case 11:
			///Scorro la posizione [0] e [1] dei due vettori e controllo se sono stati inseriti dei
			/// caratteri alfabetici tramite la funzione isalpha(). Se la if è verificata, stampo un errore
			/// ed esco dalla funzione con correct = 0.
			if (isalpha(temp[0]) || isalpha(temp[1]))
			{
				printf("Hai inserito un carattere. Riprova.\n");
			}
			///Se la condizione precedente non è verificata, allora passo al controllo del giorno, il quale deve
			/// essere compreso tra 30 e 01.
			else if ((strcmp(temp, "30") > 0 ) || (strcmp(temp, "01") < 0))  {
				printf("Hai immesso un giorno del mese errato. Deve essere compreso tra 01 e 30.\n");
			}
			else
			{
				correct = 1; ///Correct sarà 1 solamente quando l'utente ha inserito un input giusto. (es. 30 Aprile).
			}
			return correct;
			break;
		case 2: ///Febbraio
			///Scorro la posizione [0] e [1] dei due vettori e controllo se sono stati inseriti dei
			/// caratteri alfabetici tramite la funzione isalpha(). Se la if è verificata, stampo un errore
			/// ed esco dalla funzione con correct = 0.
			if (isalpha(temp[0]) || isalpha(temp[1]))
			{
				printf("Hai inserito un carattere. Riprova.\n");
			}
			///Se la condizione precedente non è verificata, allora passo al controllo del giorno, il quale deve
			/// essere compreso tra 29 e 01.
			else if ((strcmp(temp, "29") > 0 ) || (strcmp(temp, "01") < 0))  {
				printf("Hai immesso un giorno del mese errato. Deve essere compreso tra 01 e 29.\n");
			}
			else
			{
				correct = 1; ///Correct sarà 1 solamente quando l'utente ha inserito un input giusto. (es. 25 Febbraio).
			}
			return correct;
			break;
		default: /// Gennaio - Marzo - Maggio - Luglio - Agosto - Ottobre - Dicembre
			///Scorro la posizione [0] e [1] dei due vettori e controllo se sono stati inseriti dei
			/// caratteri alfabetici tramite la funzione isalpha(). Se la if è verificata, stampo un errore
			/// ed esco dalla funzione con correct = 0.
			if (isalpha(temp[0]) || isalpha(temp[1]))
			{
				printf("Hai inserito un carattere. Riprova.\n");
			}
			///Se la condizione precedente non è verificata, allora passo al controllo del giorno, il quale deve
			/// essere compreso tra 31 e 01.
			else if ((strcmp(temp, "31") > 0 ) || (strcmp(temp, "01") < 0))  {
				printf("Hai immesso un giorno del mese errato. Deve essere compreso tra 01 e 31.\n");
			}
			else
			{
				correct = 1; ///Correct sarà 1 solamente quando l'utente ha inserito un input giusto. (es. 27 Marzo).
			}
			return correct;
			break;
		}
	}
	else {
		///Stampa un errore non appena la prima if (relativa alla lunghezza) è falsa.
		printf("Hai immesso un giorno composto da piu' di 3 cifre. Deve essere formato da 2 cifre!\n");
	}
	return correct;
}

/**
 * Controlla se l'anno di nascita inserito dall'amministratore al momento della
 * ricerca di utenti tramite "Data di nascita" è composto da caratteri validi,
 * ovvero da caratteri numerici.
 * Ha la stessa funzionalità di ControlloAnnoUtente(), solo che in
 * questo caso, viene usata per poter poi successivamente cercare
 * la data di nascita richiesta nel file dei passeggeri.
 *
 * @pre Qualsiasi input immesso dall'utente, sarà elaborato a dovere
 * 		secondi gli opportuni controlli.
 * @post L'intero restituito sarà 1, nel caso in cui la stringa inserita sia
 * 		 formata da caratteri numerici e siano stati inseriti meno di 3 caratteri.
 * 		 Sarà restituito 0 nel caso in cui ci siano più di 4 caratteri, meno di 4 caratteri
 * 		 oppure quando l'utente immette un anno maggiore di 2002 o minore di 1945.
 */
int ControlloAnnoTemporaneo (char *temp, int MAX_ANNO_TEMP) {

	/**
	 * Sarà il valore di ritorno. (0 o 1).
	 */
	int correct = 0;

	/**
	 * Lunghezza della stringa "anno" inserita dall'utente.
	 */
	int lunghezza = strlen(temp);

	///Se la lunghezza dell'anno non è esattamente di 4 caratteri, mostra un errore.
	if (lunghezza < MAX_ANNO_TEMP+1 && lunghezza > MAX_ANNO-1) {

		///Scorro la posizione [0]-[1]-[2]-[3] del vettore anno e controllo se sono stati inseriti dei
		/// caratteri alfabetici tramite la funzione isalpha(). Se la if è verificata, stampo un errore
		/// ed esco dalla funzione con correct = 0.
		if (isalpha(temp[0]) || isalpha(temp[1]) || isalpha(temp[2]) ||  isalpha(temp[3]))
		{
			printf("Hai inserito un carattere. Riprova.\n");
		}
		///Se la condizione precedente non è verificata, allora passo al controllo dell'anno, il quale deve
		/// essere compreso tra 1935 e 2001.
		else if ((strcmp(temp, "2002") > 0 ) || (strcmp(temp, "1945") < 0))  {
			printf("Hai immesso un anno errato. Deve essere compreso tra 1945 e 2002.\n");
		}
		else
		{
			correct = 1; ///Correct sarà 1 solamente quando l'utente ha inserito un input giusto. (es. 1999).
		}
	}
	else {
		///Stampa un errore non appena la prima if (relativa alla lunghezza) è falsa.
		printf("Hai immesso un anno composto da piu' di 4 cifre, oppure da meno di 4 cifre. Deve essere formato da esattamente 4 cifre!\n");
	}
	return correct;
}

/**
 * Controlla se il comune di nascita inserito dall'utente al momento della
 * modifica dello stesso è composto da caratteri validi, ovvero da caratteri alfabetici.
 * Ha la stessa funzionalità di ControlloLuogoDiNascita(), solo che in
 * questo caso, viene usata per poter poi successivamente cercare
 * la data di nascita richiesta nel file dei passeggeri.
 *
 * @pre Qualsiasi input immesso dall'utente, sarà elaborato a dovere
 * 		secondi gli opportuni controlli.
 * @post L'intero restituito sarà 1, nel caso in cui la stringa inserita sia
 * 		 formata da caratteri alfabetici e siano stati inseriti meno di 15 caratteri.
 * 		 Sarà restituito 0 nel caso in cui ci siano più di 15 caratteri, oppure
 * 		 quando l'utente immette dei caratteri numerici.
 */
int ControlloComuneTemporaneo (char *temp, int MAX_COMUNE_TEMP) {

	/**
	 * Sarà il valore di ritorno. (0 o 1).
	 */
	int correct = 0;

	/**
	 * Lunghezza della stringa "luogodinascita" inserita dall'utente.
	 */
	int lunghezza = strlen(temp);

	///Se la lunghezza della stringa è maggiore a 15, mostra un errore.
	if (lunghezza < MAX_COMUNE_TEMP+1) {

		///Scorro tutto il vettore e controllo se sono stati inseriti dei
		/// caratteri alfabetici tramite la funzione isalpha(). Se la if non è verificata
		/// stampo un errore ed esco dalla funzione con correct = 0.
		for (int i = 0; i < lunghezza; i++) {
			if (isalpha(temp[i])) {
			}
			else {
				printf("Hai immesso un numero. Un comune e' formato da soli caratteri!\n");
				return correct;
			}
		}
		correct = 1; ///Correct sarà 1 solamente quando l'utente ha inserito un input giusto. (es. Bari).
	}
	else {
		///Stampa un errore non appena la prima if (relativa alla lunghezza) è falsa.
		printf("Hai immesso un comune piu' lungo di 15 caratteri.\n");
	}
	return correct;
}

/**
 * Controlla se la tratta di partenza inserita dall'amministratore al momento della
 * modifica di un volo è composta da caratteri validi, ovvero da caratteri alfabetici.
 *
 * @pre Qualsiasi input immesso dall'amministratore, sarà elaborato a dovere
 * 		secondi gli opportuni controlli.
 * @post L'intero restituito sarà 1, nel caso in cui la stringa inserita sia
 * 		 formata da soli caratteri alfabetici. Sarà restituito 0 nel caso in cui
 * 		 ci sia almeno 1 numero oppure la lunghezza della stringa stessa superi
 * 		 la lunghezza massima (20).
 */
int ControlloTrattaPartenzaTemporaneo (char* temp, int MAX_TRATTA_PARTENZA_TEMP) {

	/**
	 * Sarà il valore di ritorno. (0 o 1).
	 */
	int correct = 0;

	/**
	 * Lunghezza della stringa inserita dall'amministratore.
	 */
	int lunghezza = strlen(temp);

	///Se la lunghezza è maggiore di 20, allora restituisci un errore.
	if (lunghezza < MAX_TRATTA_PARTENZA_TEMP+1) {

		///Scorro tutto il vettore e controllo se è tutti i caratteri inseriti
		/// siano alfabetici. Nel caso contrario, stampa a video un errore
		/// ed esci subito dalla funzione con un valore di ritorno pari a 0.
		for (int i = 0; i < lunghezza; i++) {
			if (isalpha(temp[i])) { ///Scorrimento e controllo vettore
			}
			else {
				printf("Hai immesso un numero. La tratta e' formata da soli caratteri!\n");
				return correct; ///Appena trova un numero, esce dalla funzione con correct = 0.
			}
		}
		correct = 1; ///Se nessun valore numerico è stato trovato nel vettore, la stringa è giusta e correct diventa 1.
	}
	else {
		///Stampa un errore non appena la prima if (relativa alla lunghezza) è falsa.
		printf("Hai immesso una tratta piu' lunga di 20 caratteri.\n");
	}
	return correct;
}

/**
 * Controlla se la tratta di arrivo inserita dall'amministratore al momento della
 * modifica di un volo è composta da caratteri validi, ovvero da caratteri alfabetici.
 *
 * @pre Qualsiasi input immesso dall'amministratore, sarà elaborato a dovere
 * 		secondi gli opportuni controlli.
 * @post L'intero restituito sarà 1, nel caso in cui la stringa inserita sia
 * 		 formata da soli caratteri alfabetici. Sarà restituito 0 nel caso in cui
 * 		 ci sia almeno 1 numero oppure la lunghezza della stringa stessa superi
 * 		 la lunghezza massima (20).
 */
int ControlloTrattaArrivoTemporaneo (char* temp, int MAX_TRATTA_ARRIVO_TEMP) {

	/**
	 * Sarà il valore di ritorno. (0 o 1).
	 */
	int correct = 0;

	/**
	 * Lunghezza della stringa inserita dall'amministratore.
	 */
	int lunghezza = strlen(temp);

	///Se la lunghezza è maggiore di 20, allora restituisci un errore.
	if (lunghezza < MAX_TRATTA_ARRIVO_TEMP+1) {

		///Scorro tutto il vettore e controllo se è tutti i caratteri inseriti
		/// siano alfabetici. Nel caso contrario, stampa a video un errore
		/// ed esci subito dalla funzione con un valore di ritorno pari a 0.
		for (int i = 0; i < lunghezza; i++) {
			if (isalpha(temp[i])) { ///Scorrimento e controllo vettore
			}
			else {
				printf("Hai immesso un numero. La tratta e' formata da soli caratteri!\n");
				return correct; ///Appena trova un numero, esce dalla funzione con correct = 0.
			}
		}
		correct = 1; ///Se nessun valore numerico è stato trovato nel vettore, la stringa è giusta e correct diventa 1.
	}
	else {
		///Stampa un errore non appena la prima if (relativa alla lunghezza) è falsa.
		printf("Hai immesso una tratta piu' lunga di 20 caratteri.\n");
	}
	return correct;
}

/**
 * Controlla se il nome della compagnia inserito dall'amministratore al momento della
 * modifica di un volo è composto da caratteri validi, ovvero da caratteri alfabetici.
 *
 * @pre Qualsiasi input immesso dall'amministratore, sarà elaborato a dovere
 * 		secondi gli opportuni controlli.
 * @post L'intero restituito sarà 1, nel caso in cui la stringa inserita sia
 * 		 formata da soli caratteri alfabetici. Sarà restituito 0 nel caso in cui
 * 		 ci sia almeno 1 numero oppure la lunghezza della stringa stessa superi
 * 		 la lunghezza massima (20).
 */
int ControlloNomeCompagniaTemporaneo (char* temp, int MAX_NOME_COMPAGNIA_TEMP) {

	/**
	 * Sarà il valore di ritorno. (0 o 1).
	 */
	int correct = 0;

	/**
	 * Lunghezza della stringa inserita dall'amministratore.
	 */
	int lunghezza = strlen(temp);

	///Se la lunghezza è maggiore di 20, allora restituisci un errore.
	if (lunghezza < MAX_NOME_COMPAGNIA_TEMP+1) {

		///Scorro tutto il vettore e controllo se è tutti i caratteri inseriti
		/// siano alfabetici. Nel caso contrario, stampa a video un errore
		/// ed esci subito dalla funzione con un valore di ritorno pari a 0.
		for (int i = 0; i < lunghezza; i++) {
			if (isalpha(temp[i])) { ///Scorrimento e controllo vettore
			}
			else {
				printf("Hai immesso un numero. Il nome della compagnia e' formato da soli caratteri!\n");
				return correct; ///Appena trova un numero, esce dalla funzione con correct = 0.
			}
		}
		correct = 1; ///Se nessun valore numerico è stato trovato nel vettore, la stringa è giusta e correct diventa 1.
	}
	else {
		///Stampa un errore non appena la prima if (relativa alla lunghezza) è falsa.
		printf("Hai immesso un nome compagnia piu' lungo di 20 caratteri.\n");
	}

	return correct;
}

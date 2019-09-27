/**
 ============================================================================
 Name        : Aeroporto di Bari.c
 Author      : Gianmarco Scarano
 Version     : 1.0
 Copyright   : Gianmarco Scarano - Informatica ITPS Corso B / 2018-2019
 Description : Gestione Aeroporto di Bari
 ============================================================================
 */

/// Includo le librerie necessarie al corretto funzionamento del programma.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "define.h"
#include "data.h"
#include "volo.h"
#include "passeggero.h"
#include "prenotazione.h"
#include "menu.h"

int main() {

	setbuf(stdout, NULL); ///Funzione necessaria per il corretto funzionamento della scanf().
	srand(time(NULL)); ///La funzione time() (con argomento NULL) restituisce il tempo attuale in secondi
	/// trascorsi dal 1 Gennaio 1970 fino ad oggi.
	/// Source: http://didawiki.di.unipi.it/lib/exe/fetch.php/fisica/inf/2012-numeripseudocasuali.pdf (pagina 6).

	mostraMenu(); ///Mostro il menu all'utente, per poter interagire con il programma.

	return EXIT_SUCCESS;

}

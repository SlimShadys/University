public class Lab {

	public static void main(String[] args) {

		// 1. Inserimento dati studente (PROVA BASE)
		Studente studente = new Studente();
		Studente.inserimento();
		System.out.println("Fine inserimento.\n");

		// 2. Stampa studente (PROVA BASE)
		
		/*
		 * All'interno si trova anche la stampa dei voti tramite thread (Bonus)
		 */
		studente.print();
		System.out.println("\nFine programma.");

	}

}

//Esempio che mostra il funzionamento del classloader.

class Test {
	static { //Clausola statica
		System.out.println("Inizializzo Test");
	}	
}

public class Main {

	public static void main(String [] args) throws Exception {

		System.out.println("Eseguo forName() sulla classe Test");
		
		/*
		 * Quando eseguo forName("classe-x"), essa eseguirà tutto ciò
		 * che è contenuto in "static" (Riga 5).
		 * 
		 * 
		 • E' un metodo statico di Class.
		 • Serve per ottenere un riferimento a un oggetto Class.
		 • Prende un oggetto di tipo String ("Test") contenente il nome testuale della
		   classe di cui si vuole il riferimento e restituisce un riferimento all'oggetto Class di Test.
		 * 
		 * 
		 */
		Class.forName("Test");

		System.out.println("Fatto!");
	}
}
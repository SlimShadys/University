public class Main {

	public static void main(String[] args) {
		
		/*
		 * Creo un oggetto di tipo Thread.
		 * Scrivo new Programma1, poichè
		 * Programma1 extends Thread
		 */
		Thread t1 = new Programma1(); // come se scrivessi new Thread();
		
		/*
		 * Creo un altro oggetto di tipo Thread.
		 * Passo nel costruttore new Programma2()
		 * poichè, al contrario di Programma1,
		 * non estende la classe Thread, ma Runnable.
		 */
		Thread t2 = new Thread(new Programma2());

		//Eseguo il thread numero 1
		t1.start();
		
		//Eseguo il thread numero 2
		t2.start();
		
	}

}

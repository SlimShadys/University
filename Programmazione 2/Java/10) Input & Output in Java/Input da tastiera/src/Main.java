import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {

	public static void main(String[] args) {

		//Stringa a null
		String s = null;
		
		/*
		 * Creo un oggetto di tipo InputStreamReader
		 * Legge byte e li converte in "char"
		 * System.in = Tastiera dell'utente
		 */
		InputStreamReader ISR = new InputStreamReader(System.in);
		
		/*
		 * Legge il testo da uno stream (flusso)
		 * In questo caso, leggerà il flusso da ISR.
		 */
		BufferedReader BR = new BufferedReader(ISR);
		
		try { //Blocco try, poichè readLine() ne ha bisogno.
			
			s = BR.readLine(); //Leggi l'input dell'utente e mettilo in "s"

			
			while(s != null) {	//Finchè l'input non è nullo, continua

				
				if (s.equals("exit")) { //Se scriviamo "exit", esci dal programma.
					break;
				}
				else {
					System.out.println("Hai scritto: " + s); //Stampa
					s = BR.readLine(); //Prendi nuovamente l'input
				}
			}
		}
		catch (IOException ex) { //Crea un oggetto IOException, il quale indica
								 //che c'è stato un errore I/O.
			ex.printStackTrace(); //Eccezione per readLine()
		} finally {
			try {
				BR.close(); //Una volta che abbiamo terminato il programma
							//chiudiamo l'input della tastiera.
			}
			catch (IOException ex) {
				ex.printStackTrace();
			}
		}
		
	}

}

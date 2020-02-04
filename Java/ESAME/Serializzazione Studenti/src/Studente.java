import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.Scanner;

public class Studente implements Serializable { //IMPLEMENTS SERIALIZABLE ALTRIMENTI NON FUNZIONA

	/**
	 * Eclipse dà warning se non metti questa variabile
	 */
	private static final long serialVersionUID = 1L;
	
	private int matricola;
	private String cognome;
	private String nome;

	public Studente (int ma, String co, String no) {
		matricola = ma;
		cognome = co;
		nome = no;
	}

	public static void inserimento() {

		ArrayList<Studente> studenti_array = new ArrayList<Studente>();

		Scanner input = new Scanner(System.in);
		Scanner input2 = new Scanner(System.in);
		Scanner input3 = new Scanner(System.in);

		int m = 1;
		String n;
		String c;

		while (m != 0) {

			System.out.printf("\nImmetti matricola: ");	
			m = input.nextInt();

			if (m == 0) {
				break;
			}

			else {

				System.out.printf("\nImmetti nome: ");			
				n = input2.nextLine();

				System.out.printf("\nImmetti cognome: ");
				c = input3.nextLine();

				studenti_array.add(new Studente(m, c, n));

			}
		}

		input.close();
		input2.close();
		input3.close();

		//Scrittura su file
		try {

			/*
			 * Istanza dell'oggetto fileOutput.
			 * Crea il file "Persona.dat".
			 */
			FileOutputStream fileOutput = new FileOutputStream("Persona.dat");

			/*
			 * Crea un oggetto di tipo ObjectOutputStream
			 * alla quale passiamo "fileOutput" nonchè "Persona.dat"
			 */
			ObjectOutputStream StreamOutput = new ObjectOutputStream(fileOutput);

			/*
			 * Scriviamo sul file l'oggetto studenti_array di classe ArrayList<Studente>.
			 */
			StreamOutput.writeObject(studenti_array);

			/*
			 * Chiudo il file
			 */
			StreamOutput.close();

			System.out.println("Oggetto serializzato con successo.\n");

		} catch (IOException ex) {
			ex.printStackTrace(); //Eccezione, nel caso in cui interrompiamo l'operazione
		}


	}

	public static void print() throws ClassNotFoundException {

		//Lettura da file
		try {

			/*
			 * Istanza dell'oggetto fileInput.
			 * Legge il file "Persona.dat".
			 */
			FileInputStream fileInput = new FileInputStream("Persona.dat");

			/*
			 * Crea un oggetto di tipo ObjectInputStream
			 * alla quale passiamo "fileInput" nonchè "Persona.dat"
			 */
			ObjectInputStream StreamInput = new ObjectInputStream(fileInput);

			/*
			 * Creo un oggetto di tipo ArrayList<Studente>.
			 * Questo oggetto restituirà conterrà gli oggetti restituiti
			 * da readObject(), ovvero i singoli studenti presenti in "Persona.dat"
			 * Metto (ArrayList<Studente>), per fare un cast, dato che dovrà leggere
			 * dati di tipo "(ArrayList<Studente>)"
			 */

			/*
			 * Finchè ci sono dati da leggere, tu stampa.
			 * fileInput.available() ritorna un numero, se è > 0, allora ci sono ancora dati
			 * se è <= 0 allora il file è terminato.
			 */

			while (fileInput.available() > 0) {

				ArrayList<Studente> e = (ArrayList<Studente>) StreamInput.readObject();

				System.out.println(e); //Andrà a richiamare il toString()

			}

			/*
			 * Chiudo il file
			 */
			StreamInput.close();

		} catch (IOException ex) {
			ex.printStackTrace(); //Eccezione, nel caso in cui interrompiamo l'operazione
		}

	}

	@Override
	public String toString() {
		return "\nNome: " + nome + "\t-- Cognome: " + cognome + "\t-- Matricola: " + matricola ;
	}

}

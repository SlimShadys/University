import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

public class Main {

	public static void main(String[] args) throws ClassNotFoundException {

		/*
		 * Costruttore della classe persona
		 */
		Persona p = new Persona("Gianmarco", "Scarano", 20, "GS20");
		
		/*
		 * Classe per poter scrivere su un file
		 */
		FileOutputStream fileOutput;
		
		/*
		 * Classe per poter leggere da un file
		 */
		FileInputStream fileInput;
		
		/*
		 * Classe che aggiunge il metodo writeObject()
		 * per poter scrivere su file
		 */
		ObjectOutputStream StreamOutput;
		
		/*
		 * Classe che aggiunge il metodo readObject()
		 * per poter leggere su file
		 */
		ObjectInputStream StreamInput;
		
		//Scrittura su file
		try {
			
			/*
			 * Istanza dell'oggetto fileOutput.
			 * Crea il file "Persona.txt".
			 */
			fileOutput = new FileOutputStream("Persona.txt");
			
			/*
			 * Crea un oggetto di tipo ObjectOutputStream
			 * alla quale passiamo "fileOutput" nonchè "Persona.txt"
			 */
			StreamOutput = new ObjectOutputStream(fileOutput);
			
			/*
			 * Scriviamo sul file l'oggetto p di classe Persona.
			 */
			StreamOutput.writeObject(p);
			
			/*
			 * Chiudo il file
			 */
			StreamOutput.close();
			System.out.println("Oggetto serializzato con successo.");
			
		} catch (IOException ex) {
			ex.printStackTrace(); //Eccezione, nel caso in cui interrompiamo l'operazione
		}
		
		//Lettura da file
		try {
			
			/*
			 * Istanza dell'oggetto fileInput.
			 * Legge il file "Persona.txt".
			 */
			fileInput = new FileInputStream("Persona.txt");
			
			/*
			 * Crea un oggetto di tipo ObjectInputStream
			 * alla quale passiamo "fileInput" nonchè "Persona.txt"
			 */
			StreamInput = new ObjectInputStream(fileInput);

			/*
			 * Creo un oggetto di tipo persona.
			 * Questo oggetto restituirà l'oggetto restituito
			 * da readObject(), ovvero "Persona.txt"
			 * Metto (Persona), per fare un cast, dato che dovrà leggere
			 * dati ti tipo "Persona"
			 */
			Persona p1 = (Persona) StreamInput.readObject();
			
			System.out.println("Oggetto deserializzato con successo:\n" + p1);
			
		} catch (IOException ex) {
			ex.printStackTrace(); //Eccezione, nel caso in cui interrompiamo l'operazione
		}
		
	}

}

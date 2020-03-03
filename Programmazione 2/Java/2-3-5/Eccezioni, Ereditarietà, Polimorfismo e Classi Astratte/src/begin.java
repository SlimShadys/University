/*
 * Qui è presente:
 * 1. Ereditarietà (con Classi Astratte)
 * 2. Eccezioni
 * 3. Polimorfismo
 *
 */

public class begin {

	public static void main(String[] args) {

		//Creo gli oggetti piano e guitar, facente parte della superclasse Instruments.
		instruments InPiano = new piano();
		instruments InGuitar = new guitar();

		InPiano.name = "Yamaha C 3 X PE";
		InGuitar.name = "TS Ideen 5336";

		//Eseguo il metodo play() all'interno di piano.java
		InPiano.play();
		System.out.printf("\n");

		//Eseguo il metodo play() all'interno di guitar.java
		InGuitar.play();

		System.out.println("\nAggiungo un piano all'array dei pianoforti. . .");

		//Creo un oggetto di tipo PianoList
		pianoList pn = new pianoList();

		//Eseguo il metodo di aggiunta di un piano all'array.
		//Il piano aggiunto è il piano indicato alla riga 6.
		//Si poteva anche passare un nuovo oggetto piano.
		pn.addPiano(InPiano);
		System.out.printf("\n");

		//Aggiungo oggetti diversi in uno stesso array di oggetti "Instruments" generici.
		instrumentsList genericInstrument = new instrumentsList();
		genericInstrument.addGenericInstrument(InPiano);
		genericInstrument.addGenericInstrument(InGuitar);

		//Assegno alla variabile color contenuta in "InPiano", il valore green.
		//ATTENZIONE: Non c'è una variabile vera e propria in "InPiano", ma
		//viene presa da instruments.java, dato che abbiamo creato la classe
		//piano con "extends instruments" -> Ereditarietà
		InPiano.color = "green";
		InGuitar.color = "wood";

		System.out.printf("\n\nThe color of the piano is %s, while the color of the guitar is %s.", InPiano.color, InGuitar.color);


	}

}
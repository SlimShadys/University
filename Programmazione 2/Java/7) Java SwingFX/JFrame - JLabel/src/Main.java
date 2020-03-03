import javax.swing.*;

public class Main{

	public static void main(String[] args) {

		//Creo un oggetto di tipo Window
		Window finestra = new Window();
		
		//Chiude il programma non appena si preme la X
		finestra.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		//Dimensioni della finestra
		finestra.setSize(400, 200);
		
		//IMPORTANTE -> "finestra" deve essere visibile.
		//Quindi tramite il metodo setVisible(true)
		//in poche parole mostro la finestra.
		finestra.setVisible(true);
		
	}

}

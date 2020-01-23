import javax.swing.*;

public class Main {

	public static void main(String[] args) {

		/*
		 * Creo una classe GUI che estende (extends) JFrame
		 * ecco perchè posso acecdere ai metodi g.x in 14-15-16
		 */
		GUI g = new GUI();
		
		//Chiude il programma non appena si preme la X
		g.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		//Dimensioni della finestra
		g.setSize(400,200);
		
		//IMPORTANTE -> "g" deve essere visibile.
		//Quindi tramite il metodo setVisible(true)
		//in poche parole mostro la finestra.
		g.setVisible(true);
	}

}

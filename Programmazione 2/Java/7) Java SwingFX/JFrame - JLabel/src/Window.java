import java.awt.*;
import javax.swing.*;

public class Window extends JFrame {

	/**
	 * Richiesto da Java / Eclipse per un Warning
	 */
	private static final long serialVersionUID = 1L;
	
	//Creo un oggetto di tipo JLabel
	private JLabel elemento1;
	
	public Window() {
		
		//"super" ci permette l'accesso alla superclasse
		//in questo caso JFrame.
		//In altre parole è il titolo in alto a sinistra della finestra
		super("JLabel");
		
		/*
		 * Questo ci da un layout di default, quindi non dobbiamo
		 * codificarlo noi stessi.
		 */
		setLayout(new FlowLayout());
		
		//Assegno al JLabel elemento1, la frase sottostante.
		elemento1 = new JLabel("Questa è una frase");

		/*
		 * Aggiungo il JLabel alla finestra.
		 * Se non mettessi questo, il JLabel (e quindi la stringa)
		 * non verrebbe visualizzato.
		 */
		add(elemento1); 
		
	}
}

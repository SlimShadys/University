import javax.swing.*;
import java.awt.*;

public class GUI extends JFrame {

	/**
	 * Richiesto da Java / Eclipse per un Warning
	 */
	private static final long serialVersionUID = 1L;

	//Creo un oggetto di tipo JButton
	private JButton standard;

	/*
	 * Costruttore di GUI
	 */
	public GUI() {

		//"super" ci permette l'accesso alla superclasse
		//in questo caso JFrame.
		//In altre parole è il titolo in alto a sinistra della finestra
		super("JButton");

		/*
		 * Questo ci da un layout di default, quindi non dobbiamo
		 * codificarlo noi stessi.
		 */
		setLayout(new FlowLayout());

		//Il nostro pulsante conterrà la stringa "Pulsante Standard"
		standard = new JButton("Pulsante Standard");

		/*
		 * Opzionale - Posso mettere una immagine di fianco al bottone
		 * Specificare il proprio percorso come parametro
		 */
		ImageIcon icon = new ImageIcon("C:\\Users\\Gianmarco\\eclipse-workspace\\JButton\\src\\download.png");

		standard.setIcon(icon); //Collego l'icona superiore al bottone

		/*
		 * Aggiungo il bottone alla finestra.
		 * Se non mettessi questo, il pulsante non verrebbe visualizzato
		 */
		add(standard);

	}

}

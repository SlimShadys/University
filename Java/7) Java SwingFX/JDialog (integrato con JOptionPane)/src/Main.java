
import javax.swing.*;

public class Main {

	public static void main(String[] args) {
		
		/*
		 * Creo 2 stringhe che conterranno il messaggio da chiedere
		 * all'utente.
		 * Per far ciò, creo 2 istanze di JOptionPane contenenti "showInputDialog".
		 * 
		 * showInputDialog = "Chiede all'utente un input"
		 * 
		 */
		String n1 = JOptionPane.showInputDialog("Immetti il primo numero");
		String n2 = JOptionPane.showInputDialog("Immetti il secondo numero");

		/*
		 * Trasformo le due stringhe in interi
		 * attraverso parseInt
		 */
		int number1 = Integer.parseInt(n1);
		int number2 = Integer.parseInt(n2);
		
		int sum = number1 + number2;
		
		/*
		 * Questo JOptionPane è uguale a quelli della riga 16-17
		 * tranne che per il fatto che questa volta, mostra un messaggio
		 * invece di chiederlo: "showMessageDialog"
		 * 
		 * 1° parametro = null: Specifica il frame da utilizzare.
		 * 						se è posto a null, allora utilizza
		 * 						un nuovo frame.
		 * 
		 * 2° parametro = sum: Mostra la stringa sottostante + la somma.
		 */
		JOptionPane.showMessageDialog(null, "La somma è: " + sum);
		
		// --------------------------- //
		
		/*
		 * Creo un nuovo JOptionPane, questa volta chiedendo all'utente
		 * o SI oppure NO.
		 * Si utilizza il metodo di default QUESTION_MESSAGE
		 * seguito da YES_NO_OPTION.
		 */
		JOptionPane option = new JOptionPane ("Hai capito?",
				JOptionPane.QUESTION_MESSAGE,
				JOptionPane.YES_NO_OPTION); 
		
		/*
		 * Questa istanza in poche parole, ci scrive il titolo della finestra.
		 * createDialog ci crea una finestra di dialogo.
		 * Gli passiamo il JOptionPane precedente e un titolo.
		 */
		JDialog dialog = option.createDialog(option,"Una domanda..."); 
		
		//IMPORTANTE -> "dialog" deve essere visibile.
		//Quindi tramite il metodo setVisible(true)
		//in poche parole mostro la finestra.
		dialog.setVisible(true);
		
		//Mette in attesa il programma non appena si preme la X
		dialog.setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);

	}

}

import javax.swing.*;

public class Main {

	public static void main(String[] args) {
		
		String n1 = JOptionPane.showInputDialog("Immetti il primo numero");
		String n2 = JOptionPane.showInputDialog("Immetti il secondo numero");

		int number1 = Integer.parseInt(n1);
		int number2 = Integer.parseInt(n2);
		
		int sum = number1 + number2;
		
		JOptionPane.showMessageDialog(null, "La somma è: " + sum);
		
		JOptionPane option = new JOptionPane ("Hai capito?",
				JOptionPane.QUESTION_MESSAGE,
				JOptionPane.YES_NO_OPTION); 
		
		JDialog dialog = option.createDialog(option,"Una domanda..."); 
		
		dialog.setSize(400,200);
		dialog.setVisible(true);
		dialog.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

	}

}

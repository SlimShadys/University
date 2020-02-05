import java.awt.*;
import java.awt.event.ActionEvent;
import java.util.*;
import javax.swing.*;

public class JavaSwingForm extends JFrame {
	/**
	 * Da Warning Eclipse se non lo metti
	 */
	private static final long serialVersionUID = 1L;

	private JFrame frame = new JFrame("Prova");
	public JTextField matr;
	public JTextField cogn;
	public JTextField nom;


	ArrayList<Studente> studenti = new ArrayList<Studente>();

	public static void main(String[] args) {
		try {
			JavaSwingForm window=new JavaSwingForm();
			window.frame.setVisible(true);
		}catch (Exception e){
			e.printStackTrace();
		}
	}


	public JavaSwingForm()
	{
		initialize();
	}

	public void initialize()
	{
		/*
		 * Aggiungo un Listener al frame appena creato tramite
		 * il metodo addWindowListener, e gli passo il costruttore
		 * di una classe creata da noi -> GenericWindowListener.
		 *
		 * Servirà per far terminare il programma quando premiamo la X
		 * Nel caso in cui si voglia togliere questa opzione, eliminare
		 * questa linea di codice sottostante e la classe GenericWindowListener.java
		 */
		frame.addWindowListener(new GenericWindowListener());

		frame.setSize(600,500);

		Container c = frame.getContentPane();
		c.setLayout(new BorderLayout());

		/*
		 * Matricola
		 */
		JPanel pannellomatricola=new JPanel();
		pannellomatricola.setLayout(new FlowLayout());
		JLabel etichettaMatricola = new JLabel("Matricola");
		pannellomatricola.add(etichettaMatricola);
		matr=new JTextField(20);

		pannellomatricola.add(matr);
		c.add(pannellomatricola,BorderLayout.NORTH); //Posizione del pulsante

		/*
		 * Cognome
		 */
		JPanel pannellocognome=new JPanel();
		pannellocognome.setLayout(new FlowLayout());
		JLabel etichettacognome = new JLabel("Cognome");
		pannellocognome.add(etichettacognome);
		cogn=new JTextField(20);

		pannellocognome.add(cogn);
		c.add(pannellocognome,BorderLayout.CENTER); //Posizione del pulsante

		/*
		 * Nome
		 */
		JPanel pannellonome=new JPanel();
		pannellonome.setLayout(new FlowLayout());
		JLabel etichettanome = new JLabel("Nome");
		pannellonome.add(etichettanome);
		nom=new JTextField(20);

		pannellonome.add(nom);
		c.add(pannellonome,BorderLayout.WEST); //Posizione del pulsante

		/*
		 * Pulsanti
		 */
		JPanel pannellopulsanti=new JPanel();
		pannellopulsanti.setLayout(new FlowLayout());

		JButton inseriscistudente=new JButton("Inserisci Studente");
		inseriscistudente.addActionListener(new ActionListener());
		pannellopulsanti.add(inseriscistudente);

		JButton inseriscidocente=new JButton("Inserisci Docente");
		inseriscidocente.addActionListener(new ActionListener());
		pannellopulsanti.add(inseriscidocente);

		JButton stampa=new JButton("Stampa");
		stampa.addActionListener(new ActionListener());
		pannellopulsanti.add(stampa);
		c.add(pannellopulsanti,BorderLayout.PAGE_END); //Posizione del pulsante


	}

	public class ActionListener implements java.awt.event.ActionListener {

		public void actionPerformed(ActionEvent e) {
			if(e.getActionCommand().contentEquals("Inserisci Studente")) {
				//PER LEGGERE DALLA CASELLA DI TESTO NOME
				int matricola=Integer.parseInt(matr.getText());
				String nome = nom.getText();
				String cognome = cogn.getText();
				studenti.add(new Studente(matricola,cognome, nome));
			}
			else if(e.getActionCommand().contentEquals("Inserisci Docente")) {
				//PER LEGGERE DALLA CASELLA DI TESTO NOME
				int matricola=Integer.parseInt(matr.getText());
				String nome = nom.getText();
				String cognome = cogn.getText();
				studenti.add(new Docente(matricola,cognome, nome));
			}

			else {
				Iterator<Studente> i1 = studenti.iterator();

				while(i1.hasNext())
				{
					((Studente)i1.next()).chiSono();
				}
			}
		}
	}
}
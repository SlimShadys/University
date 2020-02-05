
public class Docente extends Studente {

	public Docente(int matricola, String cognome, String nome) {
		super(matricola, cognome, nome);

	}

	/*
	 * Override del metodo chiSono. Con questo riesco a far
	 * stampare la qualifica del DOCENTE, quando verrà invocato
	 * un oggetto di tipo docente all'interno dell'iteratore
	 */
	public void chiSono()
	{
		System.out.println("Cognome:" + cognome);
		System.out.println("Nome: " + nome);
		System.out.println("Qualifica: DOCENTE");
		System.out.println("Matricola: " + matricola);
	}

}

//LA CLASSE DEVE SEMPRE IMPLEMENTARE CLONEABLE, COSI' POTRA' ESSERE CLONATA
public class Movie implements Cloneable {

	private String nome;
	private String data;

	/*
	 * Costruttore
	 */
	public Movie(String nome, String data)
	{
		super();
		this.nome = nome;
		this.data = data;
	}

	/*
	 * Metodo per ritornare il nome
	 */
	public String getName()
	{
		return nome;
	}

	/*
	 * Metodo per impostare un nuovo titolo.
	 * Gli passiamo una stringa
	 */
	public void setName(String nome)
	{
		this.nome = nome;
	}

	/*
	 * Metodo per ritornare la data
	 */
	public String getDate()
	{
		return data;
	}

	/*
	 * Metodo per impostare una nuova data.
	 * Gli passiamo una stringa
	 */
	public void setDate(String data)
	{
		this.data = data;
	}

	/*
	 * Tramite questo metodo, riesco a clonare questa classe.
	 * Il Throws è necessario poichè non siamo sicuri questa
	 * classe sia clonabile.
	 */
	@Override
	public Object clone() throws CloneNotSupportedException
	{
		return super.clone();
	}

}
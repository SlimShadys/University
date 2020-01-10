public class Main
{

	public static void main(String[] args)

	//Questo è di default, poichè tutte le classi non possono essere clonate
			throws CloneNotSupportedException
	{

		/*
		 * Creo un oggetto di tipo Movie con questi parametri.
		 */
		Movie film = new Movie("8 Mile", "2002");

		//Stampo
		System.out.println("Film originale:");
		System.out.println("Nome          = "
				+ film.getName());

		System.out.println("Data di uscita = "
				+ film.getDate());

		System.out.println("----------------------------");

		/*
		 * Creo un oggetto di tipo Movie che è un CLONE di "film"
		 */
		Movie filmClonato = (Movie) film.clone();

		/*
		 * Tramite diversi metodi, cambio il nome e la data.
		 */
		filmClonato.setName("Batman");
		filmClonato.setDate("2010");

		//Stampo
		System.out.println("Film clonato:");
		System.out.println("Nome          = "
				+ filmClonato.getName());

		System.out.println("Data di uscita = "
				+ filmClonato.getDate());

	}

}

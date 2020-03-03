/*

Prova di Laboratorio di PROGETTAZIONE DI BASI DI DATI
C.d.S. in Informatica e Tecnologie per la Produzione del Software (3 anni)
Docente: dott.ssa Francesca A. Lisi

26 Febbraio 2015

-------------------------------------
Cognome e Nome	: Lamparelli Ivan
Matricola	: 
-------------------------------------

 */

import java.sql.*;

public class ProvaDB20150226 {

	public static void main(String[] args) {


		// sezione dichiarazione variabili locali
		int ok, num;

		String titolo_libro;
		String nome_editore;

		String nro_autore;
		String nome_autore;
		String cognome_autore;

		int num_libri;
		double prezzo_libri;

		Connection connessione = null;

		// es. 1: creazione stringa contenente comando SQL
		String stringa1 = "ALTER TABLE Libri ADD FOREIGN KEY (Codice_editore) REFERENCES Editori(Codice_editore)";

		// es. 2: creazione stringa contenente comando SQL
		String stringa2 = "DELETE FROM Editori WHERE Nome_Editore = 'Arcade Publishing'";

		// es. 3: creazione stringa contenente comando SQL
		String stringa3 = "CREATE VIEW LibriPubblicati_MA(Titolo_libro, Nome_editore) AS "
				+ "SELECT Titolo_libro, Nome_editore FROM Libri NATURAL JOIN Editori "
				+ "WHERE Stato_editore = 'MA'";

		// es. 4: creazione stringa contenente comando SQL		
		String stringa4 = "SELECT * FROM LibriPubblicati_MA;";

		// es. 5: creazione stringa contenente comando SQL
		String stringa5 = "SELECT DISTINCT Nro_autore, Cognome_autore, Nome_autore "
				+ "FROM Autori NATURAL JOIN LibriAutori NATURAL JOIN Libri NATURAL JOIN LibriPubblicati_MA "
				+ "ORDER BY Cognome_autore, Nome_autore";

		// es. 6: creazione stringa contenente comando SQL		
		String stringa6 = "SELECT Cognome_autore, Nome_autore, Titolo_libro, Nome_editore "
				+ "FROM Autori NATURAL LEFT JOIN LibriAutori NATURAL LEFT JOIN Libri "
				+ "NATURAL LEFT JOIN Editori ORDER BY Cognome_autore";

		// es. 7: creazione stringa contenente comando SQL
		String stringa7 = "SELECT Nome_editore, count(*) AS Num_libri, avg(Prezzo_libro) AS Prezzo_medio "
				+ "FROM Editori NATURAL JOIN Libri GROUP BY Codice_editore";

		try {

			/*
			 * QUI dava errore perché non avevo inserito JDBC fra le librerie
			 */

			// caricamento del driver
			new com.mysql.jdbc.Driver();

			/*
			 * Qui NON dà la stringa da mettere all'interno di getConnection
			 * Bisogna ricordarsi la sintassi
			 */

			//creazione di una connessione al database con credenziali di accesso appropriate
			connessione = DriverManager.getConnection("jdbc:mysql://localhost/HenrysBooksDB20150226", "root", "password");

			// es. 1: esecuzione comando SQL

			Statement istruzione1 = connessione.createStatement();

			ok = istruzione1.executeUpdate(stringa1);

			System.out.println("Es1: Ho aggiunto il vincolo dalla tabella Libri verso Editori. Ho modificato " + ok + " tuple");

			// es. 2: esecuzione comando SQL
			Statement istruzione2 = connessione.createStatement();
			num = istruzione2.executeUpdate(stringa2);

			System.out.println("\nEs2: Il numero di tuple eliminate dalla tabella Editori è: " + num + " ");


			// es. 3: esecuzione comando SQL
			Statement istruzione3 = connessione.createStatement();
			istruzione3.execute(stringa3);

			System.out.println("\nEs3: Ho creato una view sui libri con editori del Massachusetts.");


			// es. 4: esecuzione comando SQL
			Statement istruzione4 = connessione.createStatement();
			ResultSet risultato4 = istruzione4.executeQuery(stringa4);

			System.out.println("\nEs4: Il contenuto della vista LibriPubblicati_MA è:");
			while (risultato4.next()) {

				titolo_libro = risultato4.getString("Titolo_libro");
				nome_editore = risultato4.getString("Nome_editore");

				System.out.println("Titolo libro: " + titolo_libro);
				System.out.println("Nome editore: " + nome_editore);
				System.out.println("-----------------------------");

			}

			System.out.println("\n\\-----------------------------//");

			// es. 5: esecuzione comando SQL
			Statement istruzione5 = connessione.createStatement();
			ResultSet risultato5 = istruzione5.executeQuery(stringa5);

			System.out.println("\nEs5: Gli autori di libri pubblicati da editori dello stato del Massachusetts sono:");

			while (risultato5.next()) {

				nro_autore = risultato5.getString("Nro_autore");
				cognome_autore = risultato5.getString("Cognome_autore");
				nome_autore = risultato5.getString("Nome_autore");

				System.out.println("Numero autore: " + nro_autore);
				System.out.println("Cognome autore: " + cognome_autore);
				System.out.println("Nome autore: " + nome_autore);
				System.out.println("-----------------------------");

			}

			System.out.println("\n\\-----------------------------//");

			// es. 6: esecuzione comando SQL
			Statement istruzione6 = connessione.createStatement();
			ResultSet risultato6 = istruzione6.executeQuery(stringa6);

			System.out.println("\nEs6: Gli autori in ordine alfabetico per cognome, anche senza libri, sono:");

			while (risultato6.next()) {

				titolo_libro = risultato6.getString("Titolo_libro");
				nome_editore = risultato6.getString("Nome_editore");
				cognome_autore = risultato6.getString("Cognome_autore");
				nome_autore = risultato6.getString("Nome_autore");

				System.out.println("Cognome autore: " + cognome_autore);
				System.out.println("Nome autore   : " + nome_autore);
				System.out.println("Titolo libro  : " + titolo_libro);
				System.out.println("Nome editore  : " + nome_editore);
				System.out.println("-----------------------------");

			}

			System.out.println("\n\\-----------------------------//");

			// es. 7: esecuzione comando SQL
			Statement istruzione7 = connessione.createStatement();
			ResultSet risultato7 = istruzione7.executeQuery(stringa7);

			System.out.println("\nEs7: Il numero ed il prezzo medio dei libri pubblicati da ciascun editore:");

			while (risultato7.next()) {

				nome_editore = risultato7.getString("Nome_editore");
				num_libri = risultato7.getInt("Num_libri");
				prezzo_libri = risultato7.getDouble("Prezzo_medio");

				System.out.println("Nome editore  : " + nome_editore);
				System.out.println("Numero libri  : " + num_libri);
				System.out.println("Prezzo medio  : " + prezzo_libri);
				System.out.println("-----------------------------");
			}
		} 
		catch (SQLException e) {
			e.printStackTrace();

		}

	}

}

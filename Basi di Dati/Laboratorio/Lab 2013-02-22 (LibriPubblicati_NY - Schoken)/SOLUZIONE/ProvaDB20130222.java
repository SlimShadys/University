/*

Prova di Laboratorio di PROGETTAZIONE DI BASI DI DATI
C.d.S. in Informatica e Tecnologie per la Produzione del Software (3 anni)
Docente: dott.ssa Francesca A. Lisi

22 Febbraio 2013

-------------------------------------
Cognome e Nome	:
Matricola	:
-------------------------------------

 */


package application;

import java.sql.*;

public class ProvaDB20130222 {

	public static void main(String[] args) {
		// sezione dichiarazione variabili locali

		Connection connessione = null;

		int ok, num;

		String titolo_libro;
		String nome_editore;

		String nome_autore;
		String cognome_autore;
		String nro_autore;

		int nro_autori;
		String citta_editore;

		int num_libri;
		double prezzo_medio;

		// es. 1: creazione stringa contenente comando SQL
		String stringa1 = "ALTER TABLE Libri ADD FOREIGN KEY (Codice_editore) REFERENCES Editori (Codice_editore)";

		// es. 2: creazione stringa contenente comando SQL
		String stringa2 = "DELETE FROM Editori WHERE Nome_editore = 'Schoken Books'";

		// es. 3: creazione stringa contenente comando SQL
		String stringa3 = "CREATE VIEW LibriPubblicati_NY(Titolo_libro, Nome_editore) AS "
				+ "SELECT Titolo_libro, Nome_editore FROM Libri NATURAL JOIN Editori "
				+ "WHERE Citta_editore = 'New York'";

		// es. 4: creazione stringa contenente comando SQL
		String stringa4 = "SELECT * FROM LibriPubblicati_NY";

		// es. 5: creazione stringa contenente comando SQL
		String stringa5 = "SELECT Nro_autore, Nome_autore, Cognome_autore "
				+ "FROM Autori NATURAL JOIN LibriAutori NATURAL JOIN Libri NATURAL JOIN LibriPubblicati_NY "
				+ "GROUP BY Nro_autore "
				+ "ORDER BY Cognome_autore, Nome_autore";

		// es. 6: creazione stringa contenente comando SQL
		String stringa6 = "SELECT Titolo_libro, COUNT(Nro_autore) AS NroAutori, Nome_editore, Citta_editore "
				+ "FROM LibriAutori NATURAL JOIN Libri NATURAL JOIN Editori "
				+ "GROUP BY Titolo_libro "
				+ "ORDER BY Titolo_libro";

		// es. 7: creazione stringa contenente comando SQL
		String stringa7 = "SELECT Nome_editore, COUNT(Codice_libro) AS NumLibri, AVG(Prezzo_libro) AS PrezzoMedio "
				+ "FROM Editori NATURAL JOIN Libri "
				+ "GROUP BY Codice_editore";

		try {
			// caricamento del driver
			new com.mysql.jdbc.Driver();
			/*
			  creazione di una connessione al database HenrysBooksDB20140120
			  con credenziali di accesso appropriate
			 */
			connessione = DriverManager.getConnection("jdbc:mysql://localhost/henrysbooksdb20130222", "root", "password");

			// es. 1: esecuzione comando SQL
			Statement istruzione1 = connessione.createStatement();
			ok = istruzione1.executeUpdate(stringa1);

			System.out.println();

			// es. 2: esecuzione comando SQL
			Statement istruzione2 = connessione.createStatement();
			num = istruzione2.executeUpdate(stringa2);

			System.out.println("\n2) Il numero di tuple eliminate dalla tabella Editori è: " + num + " ");


			// es. 3: esecuzione comando SQL
			Statement istruzione3 = connessione.createStatement();
			istruzione3.execute(stringa3);

			System.out.println();


			// es. 4: esecuzione comando SQL
			Statement istruzione4 = connessione.createStatement();
			ResultSet risultato4 = istruzione4.executeQuery(stringa4);

			System.out.println("\n4) Il contenuto della vista LibriPubblicati_NY è:");
			while (risultato4.next()) {

				titolo_libro = risultato4.getString("Titolo_libro");
				nome_editore = risultato4.getString("Nome_editore");

				System.out.println("Titolo libro: " + titolo_libro);
				System.out.println("Nome editore: " + nome_editore);
				System.out.println("-------------");
			}

			// es. 5: esecuzione comando SQL
			Statement istruzione5 = connessione.createStatement();
			ResultSet risultato5 = istruzione5.executeQuery(stringa5);

			System.out.println("\n\\-----------------------------//");

			System.out.println("\n5) Gli autori che hanno pubblicato almeno un libro con editori di New York sono:");
			while (risultato5.next()) {

				nro_autore = risultato5.getString("Nro_autore");
				nome_autore = risultato5.getString("Nome_autore");
				cognome_autore = risultato5.getString("Cognome_autore");

				System.out.println("Codice autore   : " + nro_autore);
				System.out.println("Nome autore     : " + nome_autore);
				System.out.println("Cognome autore  : " + cognome_autore);
				System.out.println("-------------");

			}

			// es. 6: esecuzione comando SQL
			Statement istruzione6 = connessione.createStatement();
			ResultSet risultato6 = istruzione6.executeQuery(stringa6);

			System.out.println("\n\\-----------------------------//");

			System.out.println("\n6) I titoli dei libri con numero di autori, e il nome e la città dell’editore:");
			while (risultato6.next()) {

				titolo_libro = risultato6.getString("Titolo_libro");
				nro_autori = risultato6.getInt("NroAutori");
				nome_editore = risultato6.getString("Nome_editore");
				citta_editore = risultato6.getString("Citta_editore");

				System.out.println("Titolo libro   : " + titolo_libro);
				System.out.println("Numero autori  : " + nro_autori);
				System.out.println("Nome editore   : " + nome_editore);
				System.out.println("Città editore  : " + citta_editore);
				System.out.println("-------------");

			}

			// es. 7: esecuzione comando SQL
			Statement istruzione7 = connessione.createStatement();
			ResultSet risultato7 = istruzione7.executeQuery(stringa7);

			System.out.println("\n\\-----------------------------//");

			System.out.println("\n7) Il numero ed il prezzo medio dei libri pubblicati da ciascun editore:");
			while (risultato7.next()) {

				nome_editore = risultato7.getString("Nome_editore");
				num_libri = risultato7.getInt("NumLibri");
				prezzo_medio = risultato7.getDouble("PrezzoMedio");

				System.out.println("Nome editore   : " + nome_editore);
				System.out.println("Numero libri   : " + num_libri);
				System.out.println("Prezzo medio   : " + prezzo_medio);
				System.out.println("-------------");

			}
		} 
		catch (SQLException e) {
			e.printStackTrace();

		}

	}
}

/*

Prova di Laboratorio di PROGETTAZIONE DI BASI DI DATI
C.d.S. in Informatica e Tecnologie per la Produzione del Software (3 anni)
Docente: dott.ssa Francesca A. Lisi

4 Febbraio 2015

-------------------------------------
Cognome e Nome	:
Matricola	:
-------------------------------------

 */


package application;

import java.sql.*;

public class ProvaDB20150204 {

	public static void main(String[] args) {
		// sezione dichiarazione variabili locali

		Connection connessione = null;

		int ok;
		int num;		

		String titolo_libro;

		String nome_filiale;
		int copie_disponibili;

		double prezzo_libro;

		String nome_editore;


		// es. 1: creazione stringa contenente comando SQL
		String stringa1 = "ALTER TABLE Scorte ADD FOREIGN KEY (Nro_filiale) REFERENCES Filiali (Nro_filiale);";

		// es. 2: creazione stringa contenente comando SQL
		String stringa2 = "INSERT INTO Filiali(Nro_filiale, Nome_filiale, Sede_filiale) VALUES ('5', 'Henrys Manhattan', 'Broadway');";

		// es. 3: creazione stringa contenente comando SQL
		String stringa3 = "CREATE VIEW LibriDisponibili_HD(Titolo_libro) AS "
				+ "SELECT Titolo_libro FROM Libri NATURAL JOIN Filiali NATURAL JOIN Scorte "
				+ "WHERE Nome_filiale = 'Henrys Downtown' AND Nro_copie_disponibili >= 1;";

		// es. 4: creazione stringa contenente comando SQL
		String stringa4 = "SELECT * FROM LibriDisponibili_HD;";

		// es. 5: creazione stringa contenente comando SQL
		String stringa5 = "SELECT Nome_filiale, Titolo_libro, Nro_copie_disponibili AS CopieDisponibili "
				+ "FROM Filiali NATURAL JOIN Libri NATURAL JOIN Scorte "
				+ "ORDER BY Nome_filiale, Titolo_libro;";

		// es. 6: creazione stringa contenente comando SQL
		String stringa6 = " SELECT Titolo_libro, Prezzo_libro AS PrezzoLibro "
				+ "FROM Libri NATURAL JOIN LibriDisponibili_HD "
				+ "WHERE Prezzo_libro = (SELECT min(prezzo_libro) FROM LibriDisponibili_HD NATURAL JOIN Libri);";

		// es. 7: creazione stringa contenente comando SQL
		String stringa7 = "SELECT Titolo_libro, Nome_editore, Prezzo_libro FROM Libri tutti NATURAL JOIN Editori "
				+ "WHERE Titolo_libro NOT IN (SELECT * FROM LibriDisponibili_HD hd WHERE tutti.Titolo_libro = hd.Titolo_libro) "
				+ "ORDER BY Titolo_libro;";

		try {
			// caricamento del driver
			new com.mysql.jdbc.Driver();
			/*
			  creazione di una connessione al database HenrysBooksDB20140204
			  con credenziali di accesso appropriate
			 */
			connessione = DriverManager.getConnection("jdbc:mysql://localhost/henrysbooksdb20150204", "root", "password");

			// es. 1: esecuzione comando SQL
			Statement istruzione1 = connessione.createStatement();
			ok = istruzione1.executeUpdate(stringa1);

			System.out.println();

			// es. 2: esecuzione comando SQL
			Statement istruzione2 = connessione.createStatement();
			num = istruzione2.executeUpdate(stringa2);

			System.out.println("\n2) Il numero di inserimenti fatti nella tabella Filiali è: " + num + " ");


			// es. 3: esecuzione comando SQL
			Statement istruzione3 = connessione.createStatement();
			istruzione3.execute(stringa3);

			System.out.println();


			// es. 4: esecuzione comando SQL
			Statement istruzione4 = connessione.createStatement();
			ResultSet risultato4 = istruzione4.executeQuery(stringa4);

			System.out.println("\n4) Il contenuto della vista LibriDisponibili_HD è:");
			while (risultato4.next()) {

				titolo_libro = risultato4.getString("Titolo_libro");

				System.out.println("Titolo libro: " + titolo_libro);

			}
			
			System.out.println("\n\\-----------------------------//");

			// es. 5: esecuzione comando SQL
			Statement istruzione5 = connessione.createStatement();
			ResultSet risultato5 = istruzione5.executeQuery(stringa5);

			System.out.println("\n5) I titoli ed il numero di copie disponibili dei libri in vendita presso ciascuna filiale sono:");
			while (risultato5.next()) {

				nome_filiale = risultato5.getString("Nome_filiale");
				titolo_libro = risultato5.getString("Titolo_libro");
				copie_disponibili = risultato5.getInt("CopieDisponibili");

				System.out.println("Nome filiale: " + nome_filiale);
				System.out.println("Titolo libro: " + titolo_libro);
				System.out.println("Copie disponibili: " + copie_disponibili);
				System.out.println("---------------------------------------");

			}

			// es. 6: esecuzione comando SQL
			Statement istruzione6 = connessione.createStatement();
			ResultSet risultato6 = istruzione6.executeQuery(stringa6);
			
			System.out.println("\n\\-----------------------------//");

			System.out.println("\n6) Il titolo del libro meno costoso fra quelli disponibili presso la filiale 'Henrys Downtown' è:");
			while (risultato6.next()) {

				titolo_libro = risultato6.getString("Titolo_libro");
				prezzo_libro = risultato6.getDouble("PrezzoLibro");

				System.out.println("Titolo libro: " + titolo_libro);
				System.out.println("Prezzo libro: " + prezzo_libro);

			}

			// es. 7: esecuzione comando SQL
			Statement istruzione7 = connessione.createStatement();
			ResultSet risultato7 = istruzione7.executeQuery(stringa7);
			
			System.out.println("\n\\-----------------------------//");

			System.out.println("\n7) I libri che non sono disponibili presso la filiale 'Henrys Downtown' sono:");
			while (risultato7.next()) {

				titolo_libro = risultato7.getString("Titolo_libro");
				nome_editore = risultato7.getString("Nome_editore");
				prezzo_libro = risultato7.getDouble("Prezzo_libro");

				System.out.println("Titolo libro: " + titolo_libro);
				System.out.println("Nome editore: " + nome_editore);
				System.out.println("Prezzo libro: " + prezzo_libro);
				System.out.println("------------------------------");

			}
		} 
		catch (SQLException e) {
			e.printStackTrace();

		}

	}
}

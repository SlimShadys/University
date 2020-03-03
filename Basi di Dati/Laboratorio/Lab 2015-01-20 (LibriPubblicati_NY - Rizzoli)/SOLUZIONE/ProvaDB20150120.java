/*

Prova di Laboratorio di PROGETTAZIONE DI BASI DI DATI
C.d.S. in Informatica e Tecnologie per la Produzione del Software (3 anni)
Docente: dott.ssa Francesca A. Lisi

20 Gennaio 2015

-------------------------------------
Cognome e Nome	: Scarano Gianmarco
Matricola	: 705627
-------------------------------------

*/


import java.sql.*;

public class ProvaDB20150120 {

	public static void main(String[] args) {
		// sezione dichiarazione variabili locali
		
		Connection connessione = null;
		
		boolean ok;
		int num;
		
		String titolo_libro;
		String nome_editore;
		String codice_editore;
		String citta_editore;
		
		String cognome_autore;
		String nome_autore;

		int num_autori;
		int num_libri;
		double prezzo_libro;		

		// es. 1: creazione stringa contenente comando SQL
		String stringa1 = "ALTER TABLE Libri ADD FOREIGN KEY (Codice_editore) REFERENCES Editori (Codice_editore)";

		// es. 2: creazione stringa contenente comando SQL
		String stringa2 = "DELETE FROM Editori WHERE Nome_editore = 'Rizzoli'";

		// es. 3: creazione stringa contenente comando SQL
		String stringa3 = "CREATE VIEW LibriPubblicati_NY(Titolo_libro, Nome_editore) AS "
				+ "SELECT Titolo_libro, Nome_editore FROM Libri NATURAL JOIN Editori "
				+ "WHERE Stato_editore = 'NY'";

		// es. 4: creazione stringa contenente comando SQL
		String stringa4 = "SELECT * FROM LibriPubblicati_NY";

		// es. 5: creazione stringa contenente comando SQL
		String stringa5 = "SELECT Nro_autore, Cognome_autore,Nome_autore,Titolo_libro,Nome_editore "
				        + "FROM Autori NATURAL JOIN LibriAutori NATURAL JOIN Libri NATURAL JOIN Editori "
				        + "WHERE Titolo_libro IN (SELECT(Titolo_libro) FROM LibriPubblicati_NY) "
				        + "ORDER BY Cognome_autore,Nome_autore ";

		// es. 6: creazione stringa contenente comando SQL
		String stringa6 = "SELECT Codice_libro,Titolo_libro,Count(Nro_autore) AS Nro_autori,Codice_editore,Nome_editore,Citta_editore "
                + "FROM Autori NATURAL JOIN LibriAutori NATURAL JOIN Libri NATURAL JOIN Editori "
                + "GROUP BY Codice_libro "
                + "ORDER BY Titolo_libro ";

		// es. 7: creazione stringa contenente comando SQL
		String stringa7 = "SELECT Nome_editore,Codice_editore,Count(Codice_libro) AS NumLibri,Avg(Prezzo_libro) AS PrezzoMedio "
		                + "FROM Editori NATURAL JOIN Libri "
		                + "GROUP BY Codice_editore ";
			
		try {
			// caricamento del driver
			new com.mysql.jdbc.Driver();
			/*
			  creazione di una connessione al database HenrysBooksDB20140120
			  con credenziali di accesso appropriate
			 */
			connessione = DriverManager.getConnection("jdbc:mysql://localhost/henrysbooksdb20150120", "root", "password");

			// es. 1: esecuzione comando SQL
			Statement istruzione1 = connessione.createStatement();
			ok = istruzione1.execute(stringa1);
			
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
				System.out.println("----------");

			}
			
			System.out.println("\n\\-----------------------------//");
			
			// es. 5: esecuzione comando SQL
			Statement istruzione5 = connessione.createStatement();
			ResultSet risultato5 = istruzione5.executeQuery(stringa5);
			
			System.out.println("\n5) Gli autori di libri pubblicati da editori dello stato di New York sono:");
			while (risultato5.next()) {
				
				cognome_autore = risultato5.getString("Cognome_autore");
				nome_autore = risultato5.getString("Nome_autore");
				
				System.out.println("Nome autore: " + nome_autore + "\tCognome autore: " + cognome_autore);

			}
			
			System.out.println("\n\\-----------------------------//");
			
			// es. 6: esecuzione comando SQL
			Statement istruzione6 = connessione.createStatement();
			ResultSet risultato6 = istruzione6.executeQuery(stringa6);
			
			System.out.println("\n6) I libri in ordine alfabetico di titolo sono:");
			while (risultato6.next()) {
				
				titolo_libro = risultato6.getString("Titolo_libro");
				num_autori = risultato6.getInt("Nro_autori");
				nome_editore = risultato6.getString("Nome_editore");
				citta_editore = risultato6.getString("Citta_editore");
				
				System.out.println("Titolo libro : " + titolo_libro);
				System.out.println("Numero autori: " + num_autori);
				System.out.println("Nome editore : " + nome_editore);
				System.out.println("Città editore: " + citta_editore);

			}
			
			System.out.println("\n\\-----------------------------//");
			
			// es. 7: esecuzione comando SQL
			Statement istruzione7 = connessione.createStatement();
			ResultSet risultato7 = istruzione7.executeQuery(stringa7);
			
			System.out.println("\n7) Il numero ed il prezzo medio dei libri pubblicati da ciascun editore:");
			
			while (risultato7.next()) {
				
				nome_editore = risultato7.getString("Nome_editore");
				codice_editore = risultato7.getString("Codice_editore");
				num_libri = risultato7.getInt("NumLibri");
				prezzo_libro = risultato7.getDouble("PrezzoMedio");
				
				System.out.println("Nome editore: " + nome_editore);
				System.out.println("Codice editore: " + codice_editore);
				System.out.println("Numero di libri: " + num_libri);
				System.out.println("Prezzo medio di libri: " + prezzo_libro);
				System.out.println("--------------------------------------");

			}
		} 
		catch (SQLException e) {
			e.printStackTrace();

		}

	}
}

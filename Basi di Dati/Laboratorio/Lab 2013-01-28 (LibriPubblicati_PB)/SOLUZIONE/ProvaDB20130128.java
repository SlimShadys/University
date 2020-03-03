/*

Prova di Laboratorio di PROGETTAZIONE DI BASI DI DATI
C.d.S. in Informatica e Tecnologie per la Produzione del Software (3 anni)
Docente: dott.ssa Francesca A. Lisi

28 Gennaio 2013

-------------------------------------
Cognome e Nome	:
Matricola	:
-------------------------------------

 */

import java.sql.*;

public class ProvaDB20130128 {

	public static void main(String[] args) {
		// sezione dichiarazione variabili locali

		int ok, num;

		int codice;
		int numero;
		
		String nome;
		String cognome;
		String titolo;
		String tipo;

		Connection connessione = null;

		// es. 1: creazione stringa contenente comando SQL
		String stringa1 = "ALTER TABLE LibriAutori ADD FOREIGN KEY (Nro_Autore) REFERENCES Autori(Nro_autore)";

		// es. 2: creazione stringa contenente comando SQL
		String stringa2 = "INSERT INTO Autori(Nro_autore, Cognome_autore, Nome_autore) VALUES ('24', '', 'Liala')";

		// es. 3: creazione stringa contenente comando SQL
		String stringa3 = "CREATE VIEW LibriPubblicati_PB(Codice_libro, Titolo_libro, Tipo_libro) AS "
				+ "SELECT Codice_libro, Titolo_libro, Tipo_libro FROM Libri NATURAL JOIN Editori "
				+ "WHERE Nome_editore = 'Pocket Books'";

		// es. 4: creazione stringa contenente comando SQL
		String stringa4 = "SELECT * FROM LibriPubblicati_PB";

		// es. 5: creazione stringa contenente comando SQL
		String stringa5 = "SELECT Nro_autore, Cognome_autore, Nome_autore FROM Autori NATURAL JOIN LibriAutori "
				+ "WHERE Codice_libro NOT IN (SELECT Codice_libro FROM LibriPubblicati_PB) "
				+ "ORDER BY Cognome_autore, Nome_autore";

		// es. 6: creazione stringa contenente comando SQL
		String stringa6 = "SELECT Titolo_libro, Tipo_libro, Prezzo_libro "
				+ "FROM Libri NATURAL JOIN LibriPubblicati_PB "
				+ "WHERE Prezzo_libro = (SELECT MAX(Prezzo_libro) FROM LibriPubblicati_PB NATURAL JOIN Libri)";

		// es. 7: creazione stringa contenente comando SQL
		String stringa7 = "SELECT Cognome_autore, Nome_autore, Nro_copie_disponibili "
				+ "FROM LibriPubblicati_PB NATURAL JOIN LibriAutori NATURAL JOIN Autori NATURAL JOIN Scorte NATURAL JOIN Filiali "
				+ "WHERE Nro_Seq = 1 AND Nome_Filiale = 'Henrys Books'";

		try {
			// caricamento del driver
			new com.mysql.jdbc.Driver();
			/*
			  creazione di una connessione al database ProdottiPremiereDB
			  con credenziali di accesso appropriate
			 */
			connessione = DriverManager.getConnection("jdbc:mysql://localhost/henrysbooksdb20130128", "root", "password");

			// es. 1: esecuzione comando SQL
			Statement istruzione1 = connessione.createStatement();
			ok = istruzione1.executeUpdate(stringa1);

			System.out.println("Es1: Aggiunto vincolo referenziale fra l'attributo Codice_libro della relazione LibriAutori e la relazione Libri");

			// es. 2: esecuzione comando SQL
			Statement istruzione2 = connessione.createStatement();
			num = istruzione2.executeUpdate(stringa2);

			System.out.println("\n2) Il numero di inserimenti fatti nella tabella Autori è: " + num);

			// es. 3: esecuzione comando SQL
			Statement istruzione3 = connessione.createStatement();
			istruzione3.execute(stringa3);

			System.out.println("\nEs3: Creata vista LibriPubblicati_PB.");

			// es. 4: esecuzione comando SQL
			Statement istruzione4 = connessione.createStatement();
			ResultSet risultato4 = istruzione4.executeQuery(stringa4);

			System.out.println("\n4) Il contenuto della vista LibriPubblicati_PB è:");
			while (risultato4.next()) {

				codice = risultato4.getInt("Codice_libro");
				titolo = risultato4.getString("Titolo_libro");
				tipo = risultato4.getString("Tipo_libro");

				System.out.println("Codice libro: " + codice);
				System.out.println("Titolo libro: " + titolo);
				System.out.println("Tipo libro  : " + tipo);
				System.out.println("---------------");				

			}

			// es. 5: esecuzione comando SQL
			Statement istruzione5 = connessione.createStatement();
			ResultSet risultato5 = istruzione5.executeQuery(stringa5);
			
			System.out.println("\n\\-----------------------------//");

			System.out.println("\n5) Gli autori che non pubblicano libri con l’editore di nome 'Pocket Books' sono:");
			while (risultato5.next()) {

				numero = risultato5.getInt("Nro_autore");
				cognome = risultato5.getString("Cognome_autore");
				nome = risultato5.getString("Nome_autore");

				System.out.println("Numero autore : " + numero);
				System.out.println("Cognome autore: " + cognome);
				System.out.println("Nome autore   : " + nome);
				System.out.println("---------------");		

			}

			// es. 6: esecuzione comando SQL
			Statement istruzione6 = connessione.createStatement();
			ResultSet risultato6 = istruzione6.executeQuery(stringa6);
			
			System.out.println("\n\\-----------------------------//");

			System.out.println("\n6) Il titolo e tipo del libro più costoso fra quelli pubblicati dall’editore di nome 'Pocket Books' è:");

			while (risultato6.next()) {

				titolo = risultato6.getString("Titolo_libro");
				tipo = risultato6.getString("Tipo_libro");

				System.out.println("Titolo libro: " + titolo);
				System.out.println("Tipo libro  : " + tipo);	

			}

			// es. 7: esecuzione comando SQL
			Statement istruzione7 = connessione.createStatement();
			ResultSet risultato7 = istruzione7.executeQuery(stringa7);
			
			System.out.println("\n\\-----------------------------//");

			System.out.println("\n7) Per ciascun libro pubblicato dall’editore di nome 'Pocket Books', il cognome e nome del primo autore ed il numero totale di copie disponibili presso le filiali Henrys Books è:");
			while (risultato7.next()) {

				cognome = risultato7.getString("Cognome_autore");
				nome = risultato7.getString("Nome_autore");
				numero = risultato7.getInt("Nro_copie_disponibili");

				System.out.println("Cognome autore  : " + cognome);
				System.out.println("Nome autore     : " + nome);
				System.out.println("Copie disonibili: " + numero);
				System.out.println("---------------");		

			}
		} 
		catch (SQLException e) {
			e.printStackTrace();

		}

	}
}

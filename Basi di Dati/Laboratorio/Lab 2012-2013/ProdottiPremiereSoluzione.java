/*

Prova di Laboratorio di PROGETTAZIONE DI BASI DI DATI
C.d.S. in Informatica e Tecnologie per la Produzione del Software (3 anni)
Docente: dott.ssa Francesca A. Lisi

21 Dicembre 2012

-------------------------------------
Cognome e Nome	:
Matricola	:
-------------------------------------

*/

import java.sql.*;

public class ProdottiPremiere {

	public static void main(String[] args) {
		// sezione dichiarazione variabili locali
		
		Connection connessione = null;

		boolean ok;

		double fido;
		int num;
		int count;
		
		String codCliente;
		String nomeCliente;
		String cognomeCliente;
		
		String codRappresentante;
		String nomeRappresentante;
		String cognomeRappresentante;
			
		// es. 1: creazione stringa contenente comando SQL
		String stringa1 = "CREATE TABLE DettOrdini("
				+ "NroOrdine CHAR(6),"
				+ "NroArt CHAR(4),"
				+ "QtaOrd DECIMAL(3,0),"
				+ "PrezzoRichiesto DECIMAL(6,2),"
				+ "PRIMARY KEY (NroOrdine, NroArt),"
				+ "FOREIGN KEY (NroOrdine) REFERENCES Ordini(NroOrdine),"
				+ "FOREIGN KEY (NroArt) REFERENCES Articoli(NroArt))";

		// es. 2: creazione stringa contenente comando SQL
		String stringa2 = "INSERT INTO DettOrdini(NroOrdine,NroArt,QtaOrd,PrezzoRichiesto) VALUES ('12489','AX12','11','21.95')";

		// es. 3: creazione stringa contenente comando SQL
		String stringa3 = "CREATE VIEW PiccoliClienti AS SELECT * FROM Clienti WHERE Saldo < 1000";

		// es. 4: creazione stringa contenente comando SQL
		String stringa4 = "SELECT DISTINCT CodCliente, Cognome, Nome FROM Clienti NATURAL JOIN Ordini "
				+ "WHERE Data = '2002-09-05'";

		// es. 5: creazione stringa contenente comando SQL
		String stringa5 = "SELECT DISTINCT r.CodRappr, r.Cognome, r.Nome "
				+ "FROM Rappresentanti r JOIN Clienti c "
				+ "WHERE r.CodRappr = c.CodRappr AND c.Fido = 1000";

		// es. 6: creazione stringa contenente comando SQL
		String stringa6 = "SELECT Fido, COUNT(*) "
				+ "FROM Clienti "
				+ "WHERE CodRappr = '03' "
				+ "GROUP BY Fido "
				+ "HAVING COUNT(*) > 1";

		// es. 7: creazione stringa contenente comando SQL
		String stringa7 = "SELECT CodCliente, Cognome, Nome FROM PiccoliClienti "
				+ "WHERE Saldo < 1000 AND Fido > Saldo";
			
		try {
			// caricamento del driver
			new com.mysql.jdbc.Driver();
			/*
			  creazione di una connessione al database ProdottiPremiereDB
			  con credenziali di accesso appropriate
			 */
			connessione = DriverManager.getConnection("jdbc:mysql://localhost/ProdottiPremiereDB", "root", "root");

			// es. 1: esecuzione comando SQL
			Statement istruzione1 = connessione.createStatement();
			ok = istruzione1.execute(stringa1);
			
			num = (ok)?1:0;
			System.out.println("1) Il numero di righe coinvolte dal comando di creazione della tabella DettOrdini è: " + num + " ");

			// es. 2: esecuzione comando SQL
			Statement istruzione2 = connessione.createStatement();
			num = istruzione2.executeUpdate(stringa2);
			
			System.out.println("\n2) Il numero di inserimenti fatti nella tabella DettOrdini è: " + num + " ");
			
			
			// es. 3: esecuzione comando SQL
			Statement istruzione3 = connessione.createStatement();
			istruzione3.execute(stringa3);

			System.out.println("\n3) Vista PiccoliClienti creata");

			
			// es. 4: esecuzione comando SQL
			Statement istruzione4 = connessione.createStatement();
			ResultSet risultato4 = istruzione4.executeQuery(stringa4);
			
			System.out.println("\n4) I clienti che hanno emesso un ordine il 5 settembre 2002 sono:");
			
			while (risultato4.next()) {
				codCliente = risultato4.getString("CodCliente");
				nomeCliente = risultato4.getString("Nome");
				cognomeCliente = risultato4.getString("Cognome");
				
				System.out.println("---------------------------------");
				System.out.println("Codice cliente : " + codCliente);
				System.out.println("Nome cliente   : " + nomeCliente);
				System.out.println("Cognome cliente: " + cognomeCliente);
				

			}
			
			// es. 5: esecuzione comando SQL
			Statement istruzione5 = connessione.createStatement();
			ResultSet risultato5 = istruzione5.executeQuery(stringa5);
			
			System.out.println("\n5) I rappresentanti che hanno almeno un cliente con fido di 1000 euro sono:");
			while (risultato5.next()) {
				codRappresentante = risultato5.getString("r.CodRappr");
				nomeRappresentante = risultato5.getString("r.Nome");
				cognomeRappresentante = risultato5.getString("r.Cognome");
				
				System.out.println("---------------------------------");
				System.out.println("Codice rappresentante  : " + codRappresentante);
				System.out.println("Nome rappresentante    : " + nomeRappresentante);
				System.out.println("Cognome rappresentante : " + cognomeRappresentante);

			}
			
			// es. 6: esecuzione comando SQL
			Statement istruzione6 = connessione.createStatement();
			ResultSet risultato6 = istruzione6.executeQuery(stringa6);
			
			System.out.println("\n6) Il numero dei clienti del rappresentante con codice 03 aventi un certo fido è:");
			while (risultato6.next()) {
				fido = risultato6.getDouble("Fido");
				count = risultato6.getInt("COUNT(*)");
				
				System.out.println("---------------------------------");
				System.out.println("Fido  : " + fido);
				System.out.println("Count : " + count);

			}
			
			// es. 7: esecuzione comando SQL
			Statement istruzione7 = connessione.createStatement();
			ResultSet risultato7 = istruzione7.executeQuery(stringa7);
			
			System.out.println("\n7) I clienti con saldo inferiore a 1000 e fido superiore al saldo sono:");
			while (risultato7.next()) {
				codCliente = risultato7.getString("CodCliente");
				cognomeCliente = risultato7.getString("Cognome");
				nomeCliente = risultato7.getString("Nome");
				
				System.out.println("---------------------------------");
				System.out.println("Codice cliente : " + codCliente);
				System.out.println("Nome cliente   : " + nomeCliente);
				System.out.println("Cognome cliente: " + cognomeCliente);

			}
		} 
		catch (SQLException e) {
			e.printStackTrace();

		}

	}
}

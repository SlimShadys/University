import java.util.Iterator;
import java.util.Scanner;
import java.util.Set;
import java.util.TreeSet;

public class Studente implements Comparable<Studente>{

	private static int matricola;
	private static String cognome;
	private static String nome;
	private static Set<Esame> esami = new TreeSet<Esame>();

	public static void inserimento() {

		Scanner input  = new Scanner(System.in);
		Scanner input1 = new Scanner(System.in);
		Scanner input2 = new Scanner(System.in);
		Scanner input3 = new Scanner(System.in);
		Scanner input4 = new Scanner(System.in);
		Scanner input5 = new Scanner(System.in);

		System.out.println("Nome studente: ");
		nome = input.nextLine();

		System.out.println("Cognome studente: ");
		cognome = input1.nextLine();

		System.out.println("Matricola studente: ");
		matricola = input2.nextInt();

		int codice_esame = 1;
		String nome_esame;
		int voto_esame;

		System.out.println("--- INSERIMENTO ESAMI ---");

		while (codice_esame != 0) {

			System.out.println("Codice esame: ");
			codice_esame = input3.nextInt();

			if (codice_esame == 0) {
				break;
			}

			else {

				System.out.println("Nome esame: ");
				nome_esame = input4.nextLine();

				System.out.println("Voto esame: ");
				voto_esame = input5.nextInt();

				esami.add(new Esame(codice_esame, nome_esame, voto_esame));

			}

		}

		input.close();
		input1.close();
		input2.close();
		input3.close();
		input4.close();
		input5.close();

	}

	public void print() {

		System.out.println("Matricola: " + matricola);
		System.out.println("Nome: " + nome);
		System.out.println("Cognome: " + cognome);

		System.out.println("\nEsami sostenuti:");
		
		Iterator<Esame> es = esami.iterator();

		Multithreading t1 = new Multithreading();

		t1.run(es);

	}

	@Override
	public int compareTo(Studente o) {
		// TODO Auto-generated method stub
		return 0;
	}

}

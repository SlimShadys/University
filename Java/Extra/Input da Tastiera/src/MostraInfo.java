import java.util.Scanner;

public class MostraInfo {

	private static Scanner input;
	private static Scanner input2;
	private static Scanner input3;

	public static void main(String[] args) {


		input = new Scanner(System.in);
		input2 = new Scanner(System.in);
		input3 = new Scanner(System.in);

		//RICHIESTA NOME
		System.out.print("Qual è il tuo nome? : ");

		//Definisco una variabile stringa e invece di inizializzarlo con una stringa attraverso le virgolette
		//la inizializzo tramite "input.nextLine()" -> Acquisisci tutto finchè non si preme il tasto Invio (Enter).
		String Nome = input.nextLine();

		//RICHIESTA ETA'
		System.out.print("Quanti anni hai? : ");
		//Definisco una variabile integer e invece di inizializzarla con un valore,
		//la inizializzo tramite "input.nextInt()" -> Acquisisci tutto finchè non si preme il tasto Invio (Enter).
		int eta = input2.nextInt();

		//RICHIESTA GENERE
		System.out.printf("Sei maschio? (True / False) : ");

		//Definisco una variabile boolean e invece di inizializzarla con un valore TRUE / FALSE
		//la inizializzo tramite "input.nextBoolean()" -> Acquisisci solo True o False
		Boolean myGender = input3.nextBoolean();

		//Stampo
		System.out.printf("\nBenvenuto, %s :)", Nome);
		System.out.printf("\n\nLE TUE INFORMAZIONI:");
		System.out.printf("\nNome -> %s", Nome);
		System.out.printf("\nAnni -> %d", eta);
		if (myGender == true) {
			System.out.printf("\nSesso -> Maschile");	
		}
		else
		{
			System.out.printf("\nSesso -> Femminile");				
		}

	}

}

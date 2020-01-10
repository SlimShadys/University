class Lettera {

	char c;

}

public class Main {

	/*
	 * Metodo che cambia la variabile c da "x (inteso come qualsiasi valore)" a "z"
	 */
	static void cambiaInZ(Lettera letter) {
		letter.c = 'z';
	}

	public static void main(String[] args) {

		//Creo l'oggetto lettera
		Lettera l = new Lettera();

		//Gli assegno la lettera a e lo stampo
		l.c = 'a';
		System.out.printf("1 - l.c = %c" , l.c);

		//Chiamo la funzione e cambio la a in z
		cambiaInZ(l);
		
		//Stampo
		System.out.printf("\n2 - l.c = %c" , l.c);


	}
}

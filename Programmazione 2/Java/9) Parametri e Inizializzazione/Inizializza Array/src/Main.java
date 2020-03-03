import java.util.Arrays;

public class Main {

	public static void main(String[] args) {

		System.out.println("/----- Inizializzazione di array -----/\n");

		Integer[] a = {
				new Integer(1),
				new Integer(2),
				new Integer(3),
		};

		Integer[] b = new Integer[] {
				new Integer(4),
				new Integer(5),
				new Integer(6),
		};
		
		System.out.println("PRIMO ARRAY:");
		for (int i = 0; i < a.length; i++) {
			System.out.printf("All'indice %d c'è il numero %d\n", i, a[i]);
		}
		
		System.out.println("\nSECONDO ARRAY:");
		for (int i = 0; i < b.length; i++) {
			System.out.printf("All'indice %d c'è il numero %d\n", i, b[i]);
		}
		
		System.out.println("\n/----- Inizializzazione di array multidimensionale-----/\n");

		int[][] multidimensionale = {
				{ 1, 2, 3},
				{ 4, 5, 6}
		};
		
		@SuppressWarnings("unused")
		int[][][] multidimensionale1 = new int[2][2][4];
		
		
		System.out.println("PRIMO ARRAY MULTIDIMENSIONALE:");
		System.out.println(Arrays.deepToString(multidimensionale));

		/*
		 * Multidimensionale1 un po' complicato da stampare.
		 */


	}

}
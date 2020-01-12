import java.lang.reflect.Constructor;
import java.lang.reflect.Method;

public class Main {
	
	public static void main(String[] args) {
		
		// GetDeclaredMethods
		
		/*
		 * Creo oggetto per la classe Metodi
		 */
		Metodi m1 = new Metodi();
		
		/*
		 * Creo un array del tipo predefinito "Method"
		 * e tramite m1.getClass ricavo la classe di m1 = Metodi
		 * tramite getDeclaredMethods() ricavo i metodi da me dichiarati
		 * all'interno di quella classe -> "add" e "mult"
		 */
		Method[] m = m1.getClass().getDeclaredMethods();
		
		System.out.println("----- ESEMPIO GetDeclaredMethods -----\n");
		
		/*
		 * Creo una variabile y e eseguo il metodo add()
		 */
		int y = m1.add(1, 5);
		System.out.println("Addizione: " + y); //Stampa
		
		/*
		 * Creo una variabile x e eseguo il metodo mult()
		 */
		int x = m1.mult(5, 6);
		System.out.println("Moltiplicazione: " + x + "\n");
		
		//Stampo l'array m
		System.out.println("Metodi della classe \"Metodi\":");
		for (int i = 0; i < m.length; i++) {
			System.out.println("" + i + ". " + m[i]);
		}
		
		/*------------------------------------------------*/
		
		// GetConstructors
		
		System.out.println("\n----- ESEMPIO GetConstructors -----\n");
		
		/*
		 * Creo oggetto per la classe Construtt e
		 * lo inizializzo con "Fatto" attraverso il
		 * costruttore
		 */
		Costrutt c1 = new Costrutt("Fatto");
		
		/*
		 * Creo un array del tipo predefinito "Constructor"
		 * e tramite c1.getClass ricavo la classe di c1 = Construtt
		 * tramite getConstructors() ricavo i costruttori da me dichiarati
		 * all'interno di quella classe -> "Construtt(String name)"
		 */
		Constructor[] ctor = c1.getClass().getConstructors();
		
		//Stampo l'array ctor
		System.out.println("\nCostruttori classe \"Construtt\":");
		for (int i = 0; i < ctor.length; i++) {
			System.out.println("" + i + ". " + ctor[i]);
		}
		
	}
	
}
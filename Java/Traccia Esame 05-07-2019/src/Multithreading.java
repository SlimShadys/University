import java.util.Iterator;

public class Multithreading extends Thread {
	
	public void run(Iterator<Esame> es) {
		
		System.out.println("\n--- / Stampa in multithreading \\ ---");
	    while (es.hasNext()) {
	        System.out.println(es.next());
	    }
		
	}

}

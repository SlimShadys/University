
public class Main {

	public static void main(String[] args) {
		
		Simple c1 = new Simple("c1");
		
		Complex c2 = new Complex("c2");
				
		/*
		 * Se c1 è istanza di Simple, continua
		 */
		if ( c1 instanceof Simple ) {
			
			System.out.println(c1.getName() + " fa parte di Simple");

		}
		
		/*
		 * c1.getClass() = Simple
		 * isInstance(c2) = c2 (che fa parte della classe Complex)
		 * 
		 * c2 è istanza di Simple? Falso.
		 */
		System.out.println("c1.getClass().isInstance(c2): " + c1.getClass().isInstance(c2));

	}

}

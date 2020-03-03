public class Immutable1 {

	private int data;

	public Immutable1(int initVal) {
		data = initVal;
	}

	public int read() {
		return data; 
	}

	public Immutable1 quadruple() {
		return new Immutable1(data * 4);
	}

	static void f(Immutable1 i1) {
		Immutable1 quad = i1.quadruple();
		
		System.out.println("i1 = " + i1.read());
		System.out.println("quad = " + quad.read());
	}

} 


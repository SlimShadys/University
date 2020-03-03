public class Main {

	public static void main(String[] args) {
		
		Immutable1 x = new Immutable1(47);
		
		System.out.println("x = " + x.read());
		
		Immutable1.f(x);
		
		System.out.println("x = " + x.read());

	}

}

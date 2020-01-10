public abstract class instruments {

	public abstract void play();

	public void hasStrings(int i) {
		if (i >= 1) {
			System.out.printf("This instrument has %d strings!\n", i);
		}
		else {
			System.out.println("This instrument does not have strings! It has keys!");
		}
	}

	public String color;
	public String name;
}

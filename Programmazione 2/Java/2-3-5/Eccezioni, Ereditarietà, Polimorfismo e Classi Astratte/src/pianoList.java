public class pianoList {

	instruments array[] = new piano [5];

	private int i = 0;

	public void addPiano(instruments p) {

		try {
			array[i] = p;
			System.out.printf("Ho aggiunto un nuovo piano all'indice %d del tuo array.", i);
			i++;

			if (i > array.length) {
				throw new Exception();
			}
		}

		catch (Exception e) {
			System.out.println("\nHai raggiunto il limite massimo dell'array.");
			System.out.println("Non puoi più aggiungere oggetti.");
		}

	}
}

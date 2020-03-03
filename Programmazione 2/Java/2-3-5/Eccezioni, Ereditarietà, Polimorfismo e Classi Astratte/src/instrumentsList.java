public class instrumentsList {

	private instruments genericInstrumentsArray[] = new instruments [5];

	private int i = 0;

	public void addGenericInstrument (instruments in) {

		try {
			genericInstrumentsArray[i] = in;
			System.out.printf("\nHo aggiunto un nuovo strumento all'indice %d dell'array genericInstrumentsArray", i);
			System.out.printf("\nLo strumento aggiunto all'indice %d è %s -> ", i, in.name);
			i++;

			if (i > genericInstrumentsArray.length) {
				throw new Exception();
			}
		}

		catch (Exception e) {
			System.out.println("\nHai raggiunto il limite massimo dell'array.");
			System.out.println("Non puoi più aggiungere oggetti.");
		}

	}

}

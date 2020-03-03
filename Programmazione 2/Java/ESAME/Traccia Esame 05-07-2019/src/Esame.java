
public class Esame implements Comparable<Esame>{

	public int codice;
	private String nome;
	private int voto;

	public Esame(int code, String name, int grade) {

		codice = code;
		nome = name;
		voto = grade;

	}

	@Override
	public String toString() {
		String s = "- Nome esame = " + nome;
		s = s + "\n- Codice esame = " + codice;
		s = s + "\n- Voto esame = " + voto;
		s = s + "\n----------------";
		return s;
	}

	@Override
	public int compareTo(Esame o) {

		if (codice - (o.codice) == 0) {
			return 0;
		}

		else {
			if ((o.voto - voto) == 0) {
				return 1;
			}
			else {
				return o.voto - voto; //Iteratore - Costruttore = Descrescente
									  //Costruttore - Iteratore = Crescente
			}
		}

	}
}

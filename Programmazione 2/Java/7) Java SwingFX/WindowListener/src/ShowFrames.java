//**********************************************************
//  ShowFrames.java       
//
//  Dimostra l'uso dei frame.
//**********************************************************

import mypack.FrameDemo;
import mypack.GenericWindowListener;

public class ShowFrames
{
	//-------------------------------------------------------
	//  Crea e visualizza un frame vuoto.
	//-------------------------------------------------------
	public static void main (String[] args)
	{
		//Creo un oggetto di tipo FrameDemo
		FrameDemo frame = new FrameDemo();

		//Aggiungo un Listener al frame appena creato tramite
		//il metodo addWindowListener, e gli passo il costruttore
		//di una classe creata da noi -> GenericWindowListener.
		frame.addWindowListener(new GenericWindowListener());

		//IMPORTANTE -> "frame" deve essere visibile.
		//Quindi tramite il metodo setVisible(true)
		//in poche parole mostro la finestra.
		frame.setVisible(true);
	}
}

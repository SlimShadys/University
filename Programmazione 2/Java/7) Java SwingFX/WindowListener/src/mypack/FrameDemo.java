//**********************************************************
//  FrameDemo.java       
//
//  Dimostra l'uso dei frame.
//**********************************************************

package mypack;

import javax.swing.JFrame;

public class FrameDemo extends JFrame
{
	/**
	 * Richiesto da Java / Eclipse per un Warning
	 */
	private static final long serialVersionUID = 1L;

	//-------------------------------------------------------
	//  Definisce il titolo e la dimensione di un frame vuoto.
	//-------------------------------------------------------
	public FrameDemo ()
	{
		//Titolo del costruttore
		super ("Frame Demonstration");

		// Dimensione di un frame vuoto.
		// n.b. Dimensione del frame del costruttore
		// Tutti gli oggetti di tipo FrameDemo, avranno
		// dimensioni 300x200.
		setSize (300, 200);
	}
}


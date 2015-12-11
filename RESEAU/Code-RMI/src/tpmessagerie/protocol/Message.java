package tpmessagerie.protocol;

public class Message implements java.io.Serializable {
	
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 3321069725607296632L;
	
	public String utilisateur;
	public String contenu;
	
	public Message(String u, String c)
	{
		utilisateur = u;
		contenu = c;
	}
	
	public String toString()
	{
		return utilisateur + " : " + contenu;
	}
}

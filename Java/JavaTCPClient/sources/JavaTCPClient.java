/* ****************************** */
/* *** JAVA TCP CLIENT        *** */
/* ****************************** */
/* *** This client sends TLVs *** */
/* ***   Type: 1 byte         *** */
/* ***   Length: 1 byte       *** */
/* ***   Value: N bytes       *** */
/* ****************************** */
import java.io.*;
import java.net.*;

/* ************ */
/* *** MAIN *** */
/* ************ */
class JavaTCPClient {
    public static void main(String argv[]) throws Exception {

	// Variables
	String sentence;
	String modifiedSentence;
	BufferedReader inFromUser = new BufferedReader(new InputStreamReader(System.in));
	Socket clientSocket = new Socket("localhost", 6789);
	DataOutputStream outToServer = new DataOutputStream(clientSocket.getOutputStream());
	BufferedReader inFromServer = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));

	// Get the data to send
	sentence = inFromUser.readLine();
	System.out.println("Preparing to send: " + sentence);

	// Get the sentence and chop it into bytes
	byte[] b = sentence.getBytes("UTF8");
	System.out.println("LENGTH: " + b.length);
	for (int i = 0; i<b.length; i++)
	    {
		System.out.println("\tBYTE[" + i + "]: " + b[i]);
	    }

	// Send the type field
	outToServer.writeByte((byte)1);
	// Send the length field
	outToServer.writeByte((byte)b.length);
	// Send the data
	outToServer.write(b,0,b.length);

	
	
	//modifiedSentence = inFromServer.readLine();
	//System.out.println("FROM SERVER: " + modifiedSentence);
	clientSocket.close();
    }
}

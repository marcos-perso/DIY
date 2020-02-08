/* *********************** */
/* *** JAVA TCP CLIENT *** */
/* *********************** */
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
	sentence = inFromUser.readLine();
	System.out.println("Sending: " + sentence);
	outToServer.writeBytes(sentence + '\n');
	modifiedSentence = inFromServer.readLine();
	System.out.println("FROM SERVER: " + modifiedSentence);
	clientSocket.close();
    }
}

/* *********************** */
/* *** JAVA TCP SERVER *** */
/* *********************** */
import java.io.*;
import java.net.*;

/* ************ */
/* *** MAIN *** */
/* ************ */
class JavaTCPServer {
 public static void main(String argv[]) throws Exception {

     // Variables
     String clientSentence;
     String capitalizedSentence;
     ServerSocket welcomeSocket = new ServerSocket(6789);

     // Main loop
     while (true) {

	 // Accept the socket
	 Socket connectionSocket = welcomeSocket.accept();
	 // Show the incoming connection
	 System.out.println(" THE CLIENT" + " " + connectionSocket.getInetAddress()
			    + ":" + connectionSocket.getPort() + " IS CONNECTED ");
	 // read the data
	 BufferedReader inFromClient = new BufferedReader(new InputStreamReader(connectionSocket.getInputStream()));
	 clientSentence = inFromClient.readLine();
	 System.out.println("Received: " + clientSentence);

	 DataOutputStream outToClient = new DataOutputStream(connectionSocket.getOutputStream());
	 capitalizedSentence = clientSentence.toUpperCase() + '\n';
	 outToClient.writeBytes(capitalizedSentence);
     }
 }
}

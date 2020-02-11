/* ****************************** */
/* *** JAVA TCP SERVER        *** */
/* ****************************** */
/* *** This server reads TLVs *** */
/* ***   Type: 1 byte         *** */
/* ***   Length: 1 byte       *** */
/* ***   Value: N bytes       *** */
/* ****************************** */
import java.io.*;
import java.net.*;

enum FSM_State {TYPE,LENGTH,VALUE};

/* ************ */
/* *** MAIN *** */
/* ************ */
class JavaTCPServer {
 public static void main(String argv[]) throws Exception {

     // Variables
     int TLVType = 0;
     int TLVLength = 0;
     boolean end = false;
     
     String clientSentence;
     String capitalizedSentence;
     ServerSocket welcomeSocket = new ServerSocket(6789);
     int count;

     // Main loop
     while (true) {

	 // Create a value field
	 byte[] bytes = new byte[1024];
	 FSM_State FSM = FSM_State.TYPE;

	 // Accept the socket
	 Socket connectionSocket = welcomeSocket.accept();
	 // Show the incoming connection
	 System.out.println(" THE CLIENT" + " " + connectionSocket.getInetAddress()
			    + ":" + connectionSocket.getPort() + " IS CONNECTED ");
	 // read the data
	 DataInputStream in = new DataInputStream(new BufferedInputStream(connectionSocket.getInputStream()));
	 //BufferedReader inFromClient = new BufferedReader(new InputStreamReader(connectionSocket.getInputStream()));
	 //while ((count = inFromClient.read()) >0);
	 //{
	 //clientSentence = inFromClient.readLine();
	 //clientSentence = inFromClient.readChar();
	 //System.out.println("Received: " + clientSentence);
        // and on the main thread we read from the socket and write
        // the contents to the console.
	 byte[] TLV;
	 while (!end)
	     {
		 switch(FSM)
		     {
		     case TYPE:
			 TLVType = (int)in.readByte();
			 FSM = FSM_State.LENGTH;
			 System.out.println("TYPE: " + TLVType);
			 break;
		     case LENGTH:
			 TLVLength = in.readByte();
			 FSM = FSM_State.VALUE;
			 System.out.println("LENGTH: " + (int)TLVLength);
			 break;
		     case VALUE:
			 int BytesRead = 0;
			 TLV = new byte[TLVLength];
			 while( BytesRead < TLVLength) {
         
			     // read one single byte
			     TLV[BytesRead]= in.readByte();
			     //String A = Byte.toString(in.readByte());
			     System.out.println("b[" + BytesRead + "]: " + TLV[BytesRead]);
			     BytesRead++;
			 }
			 FSM = FSM_State.TYPE;
			 break;
		     }
	     }
	 

	 //byte[] bytes = new byte[1024];
	 // int len;
        	 //while((len = in.read(bytes)) > 0) {
        	 //    String echoStr = new String(bytes, 0, len);
        	 //    System.out.println("From Client:" + echoStr);
        	 //}
	 //}	     

	 // DataOutputStream outToClient = new DataOutputStream(connectionSocket.getOutputStream());
	 	 //capitalizedSentence = clientSentence.toUpperCase() + '\n';
	 	 //outToClient.writeBytes(capitalizedSentence);
     }
 }
}

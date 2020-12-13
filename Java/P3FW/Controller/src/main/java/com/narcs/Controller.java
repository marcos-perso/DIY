package com.narcs;
import org.apache.commons.cli.CommandLine;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.persist.MemoryPersistence;
import javax.swing.*;
import java.awt.*;
import javax.swing.table.DefaultTableModel;

/**
 * Hello world!
 *
 */

public class Controller {


    /* *************** */
    /* *** MEMBERS *** */
    /* *************** */
    String topic        = "Plantuino III Data";
    String broker       = "tcp://node02.myqtthub.com:1883";
    String clientId     = "PIII-Controller";
    String loginId      = "PIII-Controller";
    String password     = "pw-PIII-Controller";
    //String clientId     = "PlantuinoIII";
    //String loginId      = "PlantuinoIII";
    //String password     = "pw-PlantuinoIII";
    MemoryPersistence persistence = null;
    MqttClient client   = null;
	
    /* *************** */
    /* *** METHODS *** */
    /* *************** */
    public void ConnectToBroker()
    {

	try {

	    // --> Create the client
	    this.persistence = new MemoryPersistence();
	    this.client = new MqttClient(this.broker, this.clientId, this.persistence);

	    MqttConnectOptions connOpts = new MqttConnectOptions();
	    connOpts.setCleanSession(true);
	    connOpts.setPassword(password.toCharArray());
	    connOpts.setUserName(loginId);

	    // --> Set the callback
	    client.setCallback(new MqttCallback() {
                    public void connectionLost(Throwable cause) {
                    }
		    
                    public void messageArrived(String topic, MqttMessage message) throws Exception {
                        System.out.println(String.format("Receiver: received '%s'", new String(message.getPayload())));
                    }
		    
                    public void deliveryComplete(IMqttDeliveryToken token) {
                    }
                });


	    // --> Connect the client to the broker
	    this.client.connect(connOpts);
	    System.out.println("Connecting to broker: "+this.broker);
	    System.out.println(String.format("Successfully connected to %s", this.client.getServerURI()));

	    // --> Subscribe to the relevant topic
	    client.subscribe(this.topic);

	} catch(MqttException me) {

	    // --> Check possible errors
	    System.out.println("reason "+me.getReasonCode());
	    System.out.println("msg "+me.getMessage());
	    System.out.println("loc "+me.getLocalizedMessage());
	    System.out.println("cause "+me.getCause());
	    System.out.println("excep "+me);
	    me.printStackTrace();
	}
    }

    /* ************ */
    /* *** MAIN *** */
    /* ************ */
    
    public static void main(String args[]) 
    {
	
	
	// ===== VARIABLE DEFINITION =====


	// ===== CREATING THE GUI =====

	// --> Creating the frame
	JFrame frame = new JFrame("My First GUI");
	frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	frame.setSize(100,500);

	// --> Creating the table
	JPanel PanelTable = new JPanel(); // the panel is not visible in output
	String[] TableHeader = {"MAC","Alias","Temperature","Humidity","Last report","Edit"}; // Table Header
	Object[][] TableData = null;
	
	DefaultTableModel model = new DefaultTableModel() ;
	model.addColumn("Identity");
	model.addColumn("Temperature");
	model.addColumn("Humidity");
	model.addColumn("Last Report");
	model.addColumn("Edit Report");

        JTable Table = new JTable(model);

        //table.setPreferredScrollableViewportSize(new Dimension(500, 70));
        //table.setFillsViewportHeight(true);
	JScrollPane js = new JScrollPane(Table);
	js.setPreferredSize(new Dimension(400,150));
	PanelTable.add(js);

	// --> Build the whole
	frame.getContentPane().add(BorderLayout.NORTH, PanelTable);
	frame.setVisible(true);

	
	// === Main FSM ===
	Controller MyController = new Controller();
	MyController.ConnectToBroker();

	
    }
    
}


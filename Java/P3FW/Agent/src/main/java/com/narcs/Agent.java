package com.narcs;
import org.apache.commons.cli.CommandLine;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.eclipse.paho.client.mqttv3.persist.MemoryPersistence;
import java.net.*;
import java.util.*;
import java.lang.*;
import org.json.simple.*;
import java.time.format.*;  
import java.time.Duration;  
import java.time.LocalDateTime;    
import java.time.format.DateTimeFormatter;  


public class Agent {


    /* *************** */
    /* *** MEMBERS *** */
    /* *************** */
    public enum t_fsmState {e_Init, e_WaitState, e_SendData};
    public t_fsmState fsmState; 

    // PlantuinoIII SAP
    String Identity         = null;
    int Temperature         = 0;
    int Humidity            = 0;
    MqttClient sampleClient = null;
    String broker           = "tcp://node02.myqtthub.com:1883";
    String clientId         = "PIII-Agent";
    String loginId          = "PIII-Agent";
    String password         = "pw-PIII-Agent";
    String topic            = "Plantuino III Data";
    MemoryPersistence persistence = null;
    LocalDateTime CurrentTime, PastTime;
    int SendDataInterval;
    Duration MyInterval;
    
    /* *************** */
    /* *** METHODS *** */
    /* *************** */
    public String GetIdentity()
    {
	
	// creating an object of Random class   
	Random random = new Random();   
	// Generates random integers 0 to 49  
	Integer i = new Integer(random.nextInt(100000));
	return i.toString();   

    };

    public int GetTemperature()
    {
	Random random = new Random();   
	Integer i = new Integer(random.nextInt(100));
	return i; // TBD
    }

    public int GetHumidity()
    {
	return 10; // TBD
    }

    public void reset()
    {
	this.fsmState         = t_fsmState.e_Init;
	this.CurrentTime      = LocalDateTime.now();
	this.PastTime         = LocalDateTime.now();
	this.SendDataInterval = 5;
	this.Identity         = GetIdentity(); // Get an identity. In teh future it can be get from a file
    }

    public void sendData()
    {

	this.Temperature = GetTemperature();
	this.Humidity    = GetHumidity();

	// Get the data necessary for the announcement
	System.out.println("Identity :"    + this.Identity);
	System.out.println("Temperature :" + this.Temperature);
	System.out.println("Humidity :"    + this.Humidity);

	// Create the message
	JSONObject msg = new JSONObject();
	JSONObject Metrics = new JSONObject();
	JSONObject Configuration = new JSONObject();
	Configuration.put("SendDataInterval",SendDataInterval);
	msg.put("Configuration",Configuration);

	Metrics.put("Temperature",this.Temperature);
	Metrics.put("Humidity",this.Humidity);
	msg.put("Metrics",Metrics);

	
	this.Send(msg);

    }

    public void ConnectToBroker()
    {


	// --> PAHO definitions
	this.persistence = new MemoryPersistence();

	    // --> Create the client

	try {

	    this.sampleClient = new MqttClient(this.broker, this.clientId, this.persistence);
	    MqttConnectOptions connOpts = new MqttConnectOptions();

	    JSONObject obj = new JSONObject();
	    
	    connOpts.setCleanSession(true);
	    connOpts.setPassword(password.toCharArray());
	    connOpts.setUserName(this.loginId);
	    
	    // --> Connect the client to the broker
	    System.out.println("Connecting to broker: " + this.broker);
	    this.sampleClient.connect(connOpts);
	    System.out.println("Connected");
	    
	} catch(MqttException me) {
	    System.out.println("reason "+me.getReasonCode());
	    System.out.println("msg "+me.getMessage());
	    System.out.println("loc "+me.getLocalizedMessage());
	    System.out.println("cause "+me.getCause());
	    System.out.println("excep "+me);
	    me.printStackTrace();
	    
	} catch (Throwable t) {
	    t.printStackTrace();
	}     
    }
    

    public void Send(JSONObject msg)
    {

	String content      = "Message from MqttPublishSample";
	int qos             = 2;

	try {

	    
	    
	    // --> Publishing message
	    content = msg.toJSONString();
	    System.out.println("Publishing message: "+content);

	    
	    MqttMessage message = new MqttMessage(content.getBytes());
	    message.setQos(qos);
	    this.sampleClient.publish(this.topic, message);
	    System.out.println("Message published");
	    //sampleClient.disconnect();
	    //System.out.println("Disconnected");
	    //System.exit(0);
	    
	} catch(MqttException me) {
	    System.out.println("reason "+me.getReasonCode());
	    System.out.println("msg "+me.getMessage());
	    System.out.println("loc "+me.getLocalizedMessage());
	    System.out.println("cause "+me.getCause());
	    System.out.println("excep "+me);
	    me.printStackTrace();
	    
	} catch (Throwable t) {
	    t.printStackTrace();
	}     
    }

    /* ************ */
    /* *** MAIN *** */
    /* ************ */

    public static void main(String args[]) 
    {


	// Create the agent
	Agent MyAgent = new Agent();

	// Reset the state of the agent
	MyAgent.reset();


	//  === RUN the state machine
	while (true)
	    {

		switch(MyAgent.fsmState)
		    {
		    case e_Init:

			// Initialize the variables
			// Move to the next state
			System.out.println("INIT State");
			MyAgent.fsmState = t_fsmState.e_WaitState;
			MyAgent.ConnectToBroker();
			break;

		    case e_WaitState:
			DateTimeFormatter dtf = DateTimeFormatter.ofPattern("HH:mm:ss");
			MyAgent.CurrentTime = LocalDateTime.now();

			MyAgent.MyInterval = Duration.between(MyAgent.PastTime, MyAgent.CurrentTime);

			if (MyAgent.MyInterval.getSeconds() > MyAgent.SendDataInterval)
			    {
				MyAgent.fsmState = t_fsmState.e_SendData;
				MyAgent.PastTime = MyAgent.CurrentTime;
			    }
			
			break;
		    case e_SendData:
			System.out.println("Sending data");
			System.out.println("");
			MyAgent.sendData();
			MyAgent.fsmState = t_fsmState.e_WaitState;
			break;
			
		    }
		
		
	    }
	
	
	
    }
    
}

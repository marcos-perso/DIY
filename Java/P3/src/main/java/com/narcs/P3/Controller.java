package com.narcs.P3;
import org.apache.commons.cli.CommandLine;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.eclipse.paho.client.mqttv3.persist.MemoryPersistence;

/**
 * Hello world!
 *
 */

public class Controller {

public static void main(String args[]) 
    {
        System.out.println(" Hello world ");       

	String topic        = "MQTT Examples";
	String content      = "Message from MqttPublishSample";
	int qos             = 2;
	//String broker       = "tcp://mqtt.eclipse.org:1883";
	String broker       = "tcp://node02.myqtthub.com:1883";
	String clientId     = "PlantuinoII";
	String loginId      = "PlantuinoII";
	String password      = "pw-PlantuinoII";

	MemoryPersistence persistence = new MemoryPersistence();
	
	try {
	    MqttClient sampleClient = new MqttClient(broker, clientId, persistence);
	    MqttConnectOptions connOpts = new MqttConnectOptions();
	    connOpts.setCleanSession(true);
	    connOpts.setPassword(password.toCharArray());
	    connOpts.setUserName(loginId);

	    
	    System.out.println("Connecting to broker: "+broker);
	    sampleClient.connect(connOpts);
	    System.out.println("Connected");
	    System.out.println("Publishing message: "+content);
	    MqttMessage message = new MqttMessage(content.getBytes());
	    message.setQos(qos);
	    sampleClient.publish(topic, message);
	    System.out.println("Message published");
	    sampleClient.disconnect();
	    System.out.println("Disconnected");
	    System.exit(0);
	    
	} catch(MqttException me) {
	    System.out.println("reason "+me.getReasonCode());
	    System.out.println("msg "+me.getMessage());
	    System.out.println("loc "+me.getLocalizedMessage());
	    System.out.println("cause "+me.getCause());
	    System.out.println("excep "+me);
	    me.printStackTrace();
	}

	
	
    }
	
	
}


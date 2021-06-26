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
import java.awt.event.*;
import org.json.simple.*;
import javax.swing.table.DefaultTableModel;
import javax.swing.border.Border;

/**
 * Hello world!
 *
 */

class IrrigationButtonListener implements ActionListener {


    Controller i_controller;
    
    public IrrigationButtonListener(Controller c) {
	i_controller = c;
    }
    
    public void actionPerformed(ActionEvent e) {
	i_controller.numClicks++;
	System.out.println("Button Clicked " + i_controller.numClicks + " times");
    }
}

class LEDButtonListener implements ActionListener {


    Controller i_controller;
    
    public LEDButtonListener(Controller c) {
	i_controller = c;
    }
    
    public void actionPerformed(ActionEvent e) {
	i_controller.numClicks++;
	System.out.println("Button Clicked. Updating the LEDS");
	i_controller.sendData();
    }
}

class CheckboxListener implements ItemListener {

    Controller i_controller;
    
    public CheckboxListener(Controller c) {
	i_controller = c;
    }

    public void itemStateChanged(ItemEvent e)
    {

	// Find the checkbox that has been triggered
	JCheckBox chk = (JCheckBox)e.getItem();
	System.out.println(chk.getText() + " Checkbox: " + (e.getStateChange()==1?"checked":"unchecked"));
	if (chk.getText() == "LED0")
	    {
		System.out.println("Updating LED0 "); if (e.getStateChange()==1) { i_controller.LED0 = 1;} else { i_controller.LED0 = 0;}
	    }
	if (chk.getText() == "LED1")
	    {
		System.out.println("Updating LED1 "); if (e.getStateChange()==1) { i_controller.LED1 = 1;} else { i_controller.LED1 = 0;}
	    }
	if (chk.getText() == "LED2")
	    {
		System.out.println("Updating LED2 "); if (e.getStateChange()==1) { i_controller.LED2 = 1;} else { i_controller.LED2 = 0;}
	    }
	if (chk.getText() == "LED3")
	    {
		System.out.println("Updating LED3 "); if (e.getStateChange()==1) { i_controller.LED3 = 1;} else { i_controller.LED3 = 0;}
	    }
    }

}

public class Controller {


    /* *************** */
    /* *** MEMBERS *** */
    /* *************** */
    String topic        = "Plantuino III Data";
    String topic_control= "Plantuino III Control";
    String broker       = "tcp://node02.myqtthub.com:1883";
    String clientId     = "PIII-Controller";
    String loginId      = "PIII-Controller";
    String password     = "pw-PIII-Controller";
    //String clientId     = "PlantuinoIII";
    //String loginId      = "PlantuinoIII";
    //String password     = "pw-PlantuinoIII";
    MqttClient sampleClient = null;
    MemoryPersistence persistence = null;
    MqttClient client   = null;

    //LEDs
    int LED0;
    int LED1;
    int LED2;
    int LED3;


    int numClicks = 0;
    
	
    /* *************** */
    /* *** METHODS *** */
    /* *************** */

    
    public void ConnectToBroker()
    {

	// --> PAHO definitions
	this.persistence = new MemoryPersistence();

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

    public void sendData()
    {

	// Create the message
	JSONObject msg = new JSONObject();
	JSONObject contents = new JSONObject();

	contents.put("content","3");
	msg.put("contents",contents);
	
	this.Send(msg);

    }

    public void Send(JSONObject msg)
    {

	String content      = "Message from Controller";
	int qos             = 2;

	try {

	    
	    
	    // --> Publishing message
	    content = msg.toJSONString();
	    System.out.println("Publishing message: "+content);

	    
	    MqttMessage message = new MqttMessage(content.getBytes());
	    message.setQos(qos);
	    this.client.publish(this.topic_control, message);
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
	
	
	// ===== VARIABLE DEFINITION =====
	Controller MyController = new Controller();

	// Listeners
	IrrigationButtonListener MyIrrigationButtonListener = new IrrigationButtonListener(MyController);
	LEDButtonListener MyLEDButtonListener = new LEDButtonListener(MyController);
	CheckboxListener MyCheckboxListener = new CheckboxListener(MyController);

	
	// === Main FSM ===
	MyController.ConnectToBroker();

	// ===== CREATING THE GUI =====

	// --> Creating the frame
	JFrame frame = new JFrame("My First GUI");
	frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	frame.setSize(675,300);

	 //Creating the MenuBar and adding components
        JMenuBar mb = new JMenuBar();
        JMenu m1 = new JMenu("FILE");
        JMenu m2 = new JMenu("Help");
        mb.add(m1);
        mb.add(m2);
        JMenuItem m11 = new JMenuItem("Open");
        JMenuItem m22 = new JMenuItem("Save as");
        m1.add(m11);
        m1.add(m22);

	// Create components that we will need later
	Border blackline = BorderFactory.createLineBorder(Color.black);
	BorderLayout Blayout = new BorderLayout();
	FlowLayout   Flayout = new FlowLayout();
	GridLayout   Glayout = new GridLayout(2,2);
	GridLayout   Glayout_p4 = new GridLayout(2,4);
	Blayout.setHgap(10);
	Blayout.setVgap(10);
	Flayout.setHgap(10);
	Flayout.setVgap(10);
	Flayout.setAlignment(FlowLayout.LEFT);
	Glayout.setHgap(10);
	Glayout.setVgap(10);
	Glayout_p4.setHgap(10);
	Glayout_p4.setVgap(10);

	//Creating the P1 panel (main)
        JPanel p1 = new JPanel(); // the panel is not visible in output
	p1.setBorder(blackline);
	p1.setLayout(Blayout);

	// Create the different panels
        JPanel p2 = new JPanel(); // the panel is not visible in output
	p2.setBorder(blackline);
	p2.setLayout(Flayout);
        JPanel p3 = new JPanel(); // the panel is not visible in output
	p3.setBorder(blackline);
	p3.setLayout(Glayout);
        JPanel p4 = new JPanel(); // the panel is not visible in output
	p4.setBorder(blackline);
	p4.setLayout(Glayout_p4);
        JPanel p5 = new JPanel(); // the panel is not visible in output
	p5.setBorder(blackline);
	p5.setLayout(Flayout);
        JPanel p6 = new JPanel(); // the panel is not visible in output
	p6.setBorder(blackline);
	p6.setLayout(Flayout);
        JPanel p7 = new JPanel(); // the panel is not visible in output
	p7.setBorder(blackline);
	p7.setLayout(Flayout);
        JPanel p8 = new JPanel(); // the panel is not visible in output
	p8.setBorder(blackline);
	p8.setLayout(Flayout);

	// Creating P7
        JLabel AliasLabel = new JLabel("Alias");
	JFormattedTextField AliasTextField = new JFormattedTextField();
	AliasTextField.setName("AliasTextField");
	AliasTextField.setColumns(10);
	JButton UpdateAlias = new JButton("Update");
	p7.add(AliasLabel);
	p7.add(AliasTextField);
	p7.add(UpdateAlias);

	// Creating P8
        JLabel MACLabel = new JLabel("MAC");
	JFormattedTextField MACTextField = new JFormattedTextField();
	MACTextField.setName("MACTextField");
	MACTextField.setColumns(10);
	p8.add(MACLabel);
	p8.add(MACTextField);


	// Creating P5
        JLabel LastReportLabel = new JLabel("Last Report");
	JFormattedTextField LastReportTextField = new JFormattedTextField();
	LastReportTextField.setName("LastReportTextField");
	LastReportTextField.setColumns(10);
	p5.add(LastReportLabel);
	p5.add(LastReportTextField);

	// Creating P3
        JLabel TemperatureLabel = new JLabel("TemperatureLabel");
	JFormattedTextField TemperatureTextField = new JFormattedTextField();
	TemperatureTextField.setName("TemperatureTextField");
	TemperatureTextField.setColumns(10);
        JLabel HumidityLabel = new JLabel("Humidity");
	JFormattedTextField HumidityTextField = new JFormattedTextField();
	HumidityTextField.setName("HumidityTextField");
	HumidityTextField.setColumns(10);
	p3.add(TemperatureLabel);
	p3.add(TemperatureTextField);
	p3.add(HumidityLabel);
	p3.add(HumidityTextField);

	// Creating P4
	JCheckBox chkLED0 = new JCheckBox("LED0");
	JCheckBox chkLED1 = new JCheckBox("LED1");
	JCheckBox chkLED2 = new JCheckBox("LED2");
	JCheckBox chkLED3 = new JCheckBox("LED3");
	JButton UpdateLEDButton = new JButton("Update LED");
	JButton IrrigateButton = new JButton("Irrigate");
	p4.add(chkLED0);
	p4.add(chkLED1);
	p4.add(chkLED2);
	p4.add(chkLED3);
	p4.add(UpdateLEDButton);
	p4.add(IrrigateButton);

	IrrigateButton.addActionListener(MyIrrigationButtonListener); 
	UpdateLEDButton.addActionListener(MyLEDButtonListener); 
	chkLED0.addItemListener(MyCheckboxListener);
	chkLED1.addItemListener(MyCheckboxListener);
	chkLED2.addItemListener(MyCheckboxListener);
	chkLED3.addItemListener(MyCheckboxListener);
	

	// Creating p2
	p2.add(p7);
	p2.add(p8);
	


	p6.add(p3);
	p6.add(p4);
	    
	p1.add(BorderLayout.NORTH,p2);
	p1.add(BorderLayout.CENTER,p6);
	p1.add(BorderLayout.SOUTH,p5);
        //JTextField tf = new JTextField(10); // accepts upto 10 characters
        //JButton send = new JButton("Send");
        //JButton reset = new JButton("Reset");
        //panel.add(label); // Components Added using Flow Layout
        //panel.add(tf);
        //panel.add(send);
        //panel.add(reset);


	//	model.addColumn("Identity");
	//	model.addColumn("Temperature");
	//	model.addColumn("Humidity");
	//	model.addColumn("Last Report");
	//	model.addColumn("Edit Report");

	//	JScrollPane js = new JScrollPane(Table);
	//	js.setPreferredSize(new Dimension(400,150));
	//	PanelTable.add(js);

	// --> Build the whole
	frame.getContentPane().add(BorderLayout.NORTH, mb);
	frame.getContentPane().add(BorderLayout.CENTER, p1);
	frame.setVisible(true);


	// === Send a starting control message ===
	System.out.println("Controller started");
	System.out.println("");
	MyController.sendData();

	
    }
    
}


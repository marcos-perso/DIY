#PLANTUINO III GENERAL STRUCTURE


##DIRECTORY TREE
<pre>
PlantuinoIII
   |
   |-----RPI-Agent   ==> Raspberry PI Plantuino III agent (1)
   |    |
   |    |--- rpi-service
   |	|
   |	|--- python_source
   |
   |--JavaController  ==> JAVA controller to be run in a PC (2)

</pre>


##(1) RPI AGENT
Controls the behaviour of the RPI Plantuino III agent:
    - GPIOs to control the LEDs

The service is run automatically once deployed in the raspberry
hhhh


![Imageddd](./Diagrams/PlantuinoIII.png "Text to show on mouseover")

The RPI Agent is implemented in Python

##(2) Controller
Controls the behaviour of the different agents.
The controller is written in Java.
A Java agent is also built for testing purposes. It is not maintained
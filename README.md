# DIY

DIY projects using Raspberry, Arduino (PlatformIO) and Raspberry Pi


# General behaviour

The whole system is composed of at least one controller and several agents that perform teh actions.
An MQTT broker (myqtthub)

The broker contains two topics:
  * **Plantuino III Data**: Allows the exchange <of data from Agents to controllers
  * **Plantuino III Control**: Allows the transfer of management and control from Controllers to Agents

# Controller:


# Agent
Each agent has a Unique IDentifier (UID)

# Links
  * Myqtthub: ([https://myqtthub.com/](URL))

# Acronyms

  * **UID** Unique IDentifier


********************* AGENT 1 **********************
sudo apt-get install python-rpi.gpio python3-rpi.gpio
sudo adduser <user> gpio
sudo chmod og+rwx /dev/gpio*

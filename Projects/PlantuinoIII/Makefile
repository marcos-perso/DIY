#################
## DESCRIPTION ##
#################

# Makefile to generate the different components of the Plantuino III
# platform
# --> Plantuino III RPI Agent


#####################
## PROJECT INCLUDE ##
#####################

########################
## COMPILATION TARGET ##
########################
# Target to compile this module. 
# It can be:
# --> UBUNTU-MATE-RPI: Ubuntu Mate RPI variant
TARGET = UBUNTU-MATE-RPI

RPI_USER = narcs
RPI_HOST = 10.10.1.17


##################
## PROJECT INFO ##
##################

PRJ_DIR = .
PRJ_NAME = plantuinoIII
MVN_PRJ_NAME = JavaController
MVN_ORG_NAME = com.narcs
VERSION = 1.0
CONTROLLER_JAR_FILE = Controller-$(VERSION)-SNAPSHOT.jar
AGENT_JAR_FILE = Agent-$(VERSION)-SNAPSHOT.jar

#####################
### COMPILER INFO ###
#####################

ifeq ($(TARGET),UBUNTU-MATE-RPI)
	target_arch = -linux
endif

###########
## TOOLS ##
###########
PYTHON = python3

##############
## INCLUDES ##
##############

##########
## LIBS ##
##########

####################
### SOURCE FILES ###
####################
RPI_AGENT_PYTHON_SRC = ./RPI-Agent/python_source
RPI_AGENT_SERVICE    = ./RPI-Agent/rpi-service


##################
### OTHER INFO ###
##################

#############
## DEFAULT ##
#############

##############
## COMMANDS ##
##############

commands:
	@echo ""
	@echo "$(HEAD) Available commands: $(TAIL)"
	@echo
	@echo " -------------- RPI Agent (PYTHON) ------------------"
	@echo ""
	@echo "DEPLOY_TEST:        Deploying TEST into the RPI"
	@echo "REBOOT_RPI :        Reboot Raspberry pi"
	@echo "SSH_RPI    :        SSH into the RPI agent"
	@echo " "
	@echo " -------------- PC Controller Agent (JAVA) ------------------"
	@echo " "
	@echo "  CLEAN_MVN       : Clean project"
	@echo "  COMPILE_MVN_PRJ : Compile Maven project"
	@echo "  CREATE_PACKAGE  : Create package"
	@echo "  RUN_CONTROLLER   : Run the controller in the PC"
	@echo "  RUN_AGENT        : Run an agent (DEBUG ONLY)"
	@echo ""
	@echo " ---------------- DEBUG --------------------"
	@echo ""
	@echo "  CREATE_DOC       : Create the Documentation"
	@echo "  SHOW_DOC         : Show documentation"
	@echo ""
	@echo " ---------------- DEBUG --------------------"

#############
## ACTIONS ##
#############
CREATE_DOC:
	java -jar plantuml.jar doc/sequence.txt
	java -jar plantuml.jar doc/json.txt
SHOW_DOC:
	feh doc/sequence.png &
	feh doc/json.png &

RUN_CONTROLLER:
	java -jar $(MVN_PRJ_NAME)/Controller/target/$(CONTROLLER_JAR_FILE)
RUN_AGENT:
	java -jar $(MVN_PRJ_NAME)/Agent/target/$(AGENT_JAR_FILE)

CLEAN_MVN:
	@cd $(MVN_PRJ_NAME); mvn clean

COMPILE_MVN_PRJ:
	 @echo " --- Compiling project ---"
	cd $(MVN_PRJ_NAME); mvn -e compile

CREATE_PACKAGE:
	@cd $(MVN_PRJ_NAME); mvn -e package


DEPLOY_TEST:
	@echo "======================================="
	@echo "=== Depolying Plantuino III service ==="
	@echo "======================================="
	@echo "Copying service units into RPI"
	rcp $(RPI_AGENT_SERVICE)/plantuinoIII.service $(RPI_USER)@$(RPI_HOST):/home/$(RPI_USER)/.
	-ssh -t $(RPI_USER)@$(RPI_HOST) sudo mv /home/$(RPI_USER)/plantuinoIII.service /usr/lib/systemd/system/.
	@echo "Copying plantuino III executables"
	rcp $(RPI_AGENT_PYTHON_SRC)/agent.py $(RPI_USER)@$(RPI_HOST):/home/$(RPI_USER)/.
	@echo "Enabling service..."
	-ssh -t $(RPI_USER)@$(RPI_HOST) systemctl enable $(PRJ_NAME)
	@echo "Rebooting..."
	-ssh -t $(RPI_USER)@$(RPI_HOST) sudo shutdown -r now

REBOOT_RPI:
	@echo "Rebooting..."
	-ssh -t $(RPI_USER)@$(RPI_HOST) sudo shutdown -r now

SSH_RPI:
	@echo "SSH into the RPI"
	ssh $(RPI_USER)@$(RPI_HOST)


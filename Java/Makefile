#################
## DESCRIPTION ##
#################

# Makefile to generate JAVA Plantuino III project (built with maven)
# Plantuino III project has 2 programs running in JAVA
#    --> P3Controller: Plantuino III controller
#    --> P3Client: Plantuino III client


#####################
## PROJECT INCLUDE ##
#####################

########################
## COMPILATION TARGET ##
########################
# Target to compile this module. 
# It can be:
# --> UBUNTU-PC: Linux over x386 architecture
# --> UBUNTU-RPI: Linux over RPI
TARGET = UBUNTU-PC

RPI_USER = pi
RPI_SERVER = 10.10.1.3


##################
## PROJECT INFO ##
##################

PRJ_DIR = .

MVN_PRJ_NAME = P3FW
MVN_ORG_NAME = com.narcs
VERSION = 1.0
CONTROLLER_JAR_FILE = Controller-$(VERSION)-SNAPSHOT.jar
AGENT_JAR_FILE = Agent-$(VERSION)-SNAPSHOT.jar

#####################
### COMPILER INFO ###
#####################

ifeq ($(TARGET),UBUNTU-PC)
	target_arch = -linux
endif
ifeq ($(TARGET),UBUNTU-RPI)
	target_arch = -linux
endif

###########
## TOOLS ##
###########
JAVAC = javac
JAVA = java

##############
## INCLUDES ##
##############

##########
## LIBS ##
##########

##################
### OTHER INFO ###
##################

#############
## DEFAULT ##
#############

all: LINK

##############
## COMMANDS ##
##############

commands:
	@echo ""
	@echo "$(HEAD) Available commands: $(TAIL)"
	@echo
	@echo "  CREATE_MVN_PRJ  : Create Maven project"
	@echo
	@echo "  CLEAN_MVN       : Clean project"
	@echo "  COMPILE_MVN_PRJ : Compile Maven project"
	@echo "  CREATE_PACKAGE  : Create package"
	@echo
	@echo "  RUN_CONTROLLER   : Run the controller"
	@echo "  RUN_AGENT        : Run an agent"
	@echo "  INSTALL_TO_RPI   : Install teh agent"
	@echo ""
	@echo " ---------------- DEBUG --------------------"
	@echo "  SHOW_MANIFEST    : Show the manifest of tar file"

#############
## ACTIONS ##
#############

SHOW_MANIFEST:
	cd P3; unzip -p target/P3-1.0-SNAPSHOT.jar META-INF/MANIFEST.MF

RUN_CONTROLLER:
	java -jar $(MVN_PRJ_NAME)/Controller/target/$(CONTROLLER_JAR_FILE)
RUN_AGENT:
	java -jar $(MVN_PRJ_NAME)/Agent/target/$(AGENT_JAR_FILE)

CLEAN_MVN:
	@cd $(MVN_PRJ_NAME); mvn clean

CREATE_MVN_PRJ:
	@echo " --- Creating Maven project. Run only once! ---"
	@echo "mvn -U -B archetype:generate -DgroupId=$(MVN_ORG_NAME) -DartifactId=$(MVN_PRJ_NAME)" 
	@echo "cd $(MVN_PRJ_NAME). -- Change packaging type from jar to pm --"
	@echo "cd $(MVN_PRJ_NAME); mvn -e -U -B archetype:generate -DgroupId=$(MVN_ORG_NAME) -DartifactId=Controller"
	@echo "cd $(MVN_PRJ_NAME); mvn -e -U -B archetype:generate -DgroupId=$(MVN_ORG_NAME) -DartifactId=Agent"

COMPILE_MVN_PRJ:
	 @echo " --- Compiling project ---"
	cd $(MVN_PRJ_NAME); mvn -e compile

CREATE_PACKAGE:
	@cd $(MVN_PRJ_NAME); mvn -e package

INSTALL_TO_RPI: CREATE_PACKAGE
	 @echo "Sending to the RPI"
	scp $(MVN_PRJ_NAME)/Agent/target/$(AGENT_JAR_FILE) $(RPI_USER)@$(RPI_SERVER):/home/$(RPI_USER)/plantuino3/.

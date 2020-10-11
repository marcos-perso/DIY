#################
## DESCRIPTION ##
#################

# Makefile to generate javipse PAHO libraries


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


##################
## PROJECT INFO ##
##################

PRJ_DIR = .

################################
## SOURCES & ENVIRONMENT INFO ##
################################
PAHO_SRC = https://github.com/eclipse/paho.mqtt.java.git
PAHO_JAR_FILE = org.eclipse.paho.client.mqttv3-1.2.5.jar 
PAHO_DIR = paho.mqtt.java
PAHO_EXAMPLE_DIR = example_paho_java
EXAMPLE_SOURCES = $(PAHO_EXAMPLE_DIR)/example_paho_java.java
CLASS_EXAMPLE = example_paho_java.class
PAHO_CLASS_DIR = /home/marcos/Projects/DIY/JavaLibs/paho.mqtt.java/org.eclipse.paho.client.mqttv3/target

#####################
### COMPILER INFO ###
#####################

ifeq ($(TARGET),UBUNTU-PC)
	target_arch = -linux
endif
ifeq ($(TARGET),UBUNTU-RPI)
	target_arch = -linux
endif

#########################
### COMPILER COMMANDS ###
#########################

# Compilation flags
J_FLAGS = 

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

#####################
## DERIVED SOURCES ##
#####################

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
	@echo "  DOWNLOAD        : Download Eclipse libraries"
	@echo "  COMPILE_LIB     : Compile the libraries"
	@echo "  COMPILE_EXAMPLE : Compile the libraries"
	@echo "  RUN_EXAMPLE     : Running library example"
	@echo ""

#############
## ACTIONS ##
#############

INFO:
	@echo " --- Compiler ---"
	@echo $(JAVAC)
	@echo $(JAVA)
	@echo " --- Java classes (CLASS) ---"
	@echo $(CLASS)

DOWNLOAD:
	@echo "Downloading from github..."
	git clone $(PAHO_SRC)

COMPILE_LIB: $(CLASS)
	cd $(PAHO_DIR) ; mvn package -DskipTests

COMPILE_EXAMPLE: $(CLASS_EXAMPLE)
	@echo "Compiling example..."

$(CLASS_EXAMPLE): $(EXAMPLE_SOURCES)
	@echo "Compiling $<..."
	$(JAVAC) -cp $(PAHO_CLASS_DIR)/$(PAHO_JAR_FILE) -d $(PAHO_EXAMPLE_DIR) $<

TEST:
	@echo $(EXAMPLE_SOURCES) 


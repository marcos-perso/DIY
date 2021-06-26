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
	@echo ""
	@echo " ---------------- DEBUG --------------------"
	@echo "  SHOW_MANIFEST    : Show the manifest of tar file"

#############
## ACTIONS ##
#############

SHOW_MANIFEST:
	cd P3; unzip -p target/P3-1.0-SNAPSHOT.jar META-INF/MANIFEST.MF

CREATE_MVN_PRJ:
	@echo " --- Creating Maven project. Run only once! ---"
	@echo "mvn -U -B archetype:generate -DgroupId=$(MVN_ORG_NAME) -DartifactId=$(MVN_PRJ_NAME)" 
	@echo "cd $(MVN_PRJ_NAME). -- Change packaging type from jar to pm --"
	@echo "cd $(MVN_PRJ_NAME); mvn -e -U -B archetype:generate -DgroupId=$(MVN_ORG_NAME) -DartifactId=Controller"
	@echo "cd $(MVN_PRJ_NAME); mvn -e -U -B archetype:generate -DgroupId=$(MVN_ORG_NAME) -DartifactId=Agent"

no
INSTALL_TO_RPI: CREATE_PACKAGE:w

	 @echo "Sending to the RPI"
	scp $(MVN_PRJ_NAME)/Agent/target/$(AGENT_JAR_FILE) $(RPI_USER)@$(RPI_SERVER):/home/$(RPI_USER)/plantuino3/.

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


##################
## PROJECT INFO ##
##################

PRJ_DIR = .

MVN_PRJ_NAME = P3
MVN_ORG_NAME = com.narcs.$(MVN_PRJ_NAME)
VERSION = 1.0
JAR_FILE = $(MVN_PRJ_NAME)-$(VERSION)-SNAPSHOT.jar

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
	@echo "  RUN_CONTROLLER   : Run the project"
	@echo ""
	@echo " ---------------- DEBUG --------------------"
	@echo "  SHOW_MANIFEST    : Show the manifest of tar file"

#############
## ACTIONS ##
#############

SHOW_MANIFEST:
	cd P3; unzip -p target/P3-1.0-SNAPSHOT.jar META-INF/MANIFEST.MF

RUN_CONTROLLER:
	cd $(MVN_PRJ_NAME); java -jar target/$(JAR_FILE)

CLEAN_MVN:
	@cd $(MVN_PRJ_NAME); mvn clean

CREATE_MVN_PRJ:
	@echo " --- Creating Maven project. Run only once! ---"
	mvn -U -B archetype:generate -DgroupId=$(MVN_ORG_NAME) -DartifactId=$(MVN_PRJ_NAME) -DarchetypeGroupId=org.apache.maven.archetypes -DarchetypeArtifactId=maven-archetype-quickstart

COMPILE_MVN_PRJ:
	 @echo " --- Compiling project ---"
	cd $(MVN_PRJ_NAME); mvn -e compile package

CREATE_PACKAGE:
	@cd $(MVN_PRJ_NAME); mvn package



#################
## DESCRIPTION ##
#################

# Makefile to generate java compilation


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
TOP = JavaTCPServer
RUN_FILE = $(TOP).class

######################
## ENVIRONMENT INFO ##
######################

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

#############
## SOURCES ##
#############

SOURCE_DIR = ./sources
SOURCES := $(shell find $(SOURCE_DIR) -name '*.java')

##############
## INCLUDES ##
##############

##########
## LIBS ##
##########

#####################
## DERIVED SOURCES ##
#####################

CLASS = $(notdir $(SOURCES:$.java=$.class))

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
	@echo "  INFO            : Shows compiling information"
	@echo "  CLEAN           : Clean the database"
	@echo "  COMPILE         : Compile the program"
	@echo "  RUN             : Run the program"
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

CLEAN:
	@echo "Cleaning..."
	@-\rm $(RUN_FILE)

RUN: $(TOP).class
	@echo "Running..."
	$(JAVA) $(TOP)

COMPILE: $(CLASS)
	@echo "Compiling java classes"

$(CLASS): $(SOURCES)
	echo "Compiling $<..."
	#$(JAVAC) $<  $@
	$(JAVAC) -d . $<

.PHONY: DEPEND

## Include dependencies file
ifeq ($(DEP_FILE), $(wildcard $(DEP_FILE)))
include $(DEP_FILE)
endif

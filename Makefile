# Target specific macros
TARGET = MOMIMOMI

NXTOSEK_ROOT = /cygdrive/c/cygwin/nxtOSEK

# nxtway_gs_balancer library desiged for NXTway-GS two wheeled self-balancing robot
USER_INC_PATH= $(NXTOSEK_ROOT)/ecrobot/nxtway_gs_balancer
USER_LIB = nxtway_gs_balancer

# using NXT standard tires (not Motorcycle tires)
#USER_DEF = NXT_STD_TIRE
DRIVENPART_SOURCES := 
# User application source
TARGET_SOURCES := \
	Main.c \
	balancer_param.c

TOPPERS_OSEK_OIL_SOURCE := ./prog.oil


O_PATH ?= build

include $(NXTOSEK_ROOT)/ecrobot/lejos_osek.tmf



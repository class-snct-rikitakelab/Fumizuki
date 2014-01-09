# Target specific macros
TARGET = TORITSU_NOMI

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
	balancer_param.c \
<<<<<<< HEAD
	Balancer_running.c
=======
	Balance.c
>>>>>>> 9b3817fe6a16ca223e7edbf1f76593e2934c7bf5

TOPPERS_OSEK_OIL_SOURCE := ./prog.oil


O_PATH ?= build

include $(NXTOSEK_ROOT)/ecrobot/lejos_osek.tmf



#example
#CGT_DIR    = D:/Program\ Files/TI-7
#empty:=
#space:= $(empty) $(empty)
#VDSP_INTERMEDIATE=$(subst \,/,$(ADI_DSP))
#VDSP=$(subst $(space),\$(space),$(VDSP_INTERMEDIATE))
#ifeq ($(TPENA),1)
#CCFLAG += -DTP
#endif

#-pdel=count            Set error limit to <count>
#-mv=id                 Target processor version (Default:6200) 
#-pdsw=id               Treat diagnostic <id> as warning
#-pdsr=id               Treat diagnostic <id> as remark
#-c                     Disable linking (overrides -z)
#-fr=dir                Object file directory (default is .)
#-pden                  Displays a diagnostic's identifiers along with its text
#$<                     第一个依赖文件的名称
#$@                     目标的完整名称



CGT_DIR = D:/C6000_CGTOOLS_7.4.8
TOOL_DIR    = ./exe


#    compliler tools
CC          = $(CGT_DIR)/bin/cl6x
HEX6X       = $(CGT_DIR)/bin/hex6x
AR          = $(CGT_DIR)/bin/ar6x
ADDCRC      = $(TOOL_DIR)/addcrc


#System and Local DIR
SYS_DIR			    = ../../release
APP_DIR		        = .
OBJ_DIR		        = ./obj
COMMOM_DIR          = ../../../APP_COMPONENT/MU
COMMOM_DIR1          = ../../../APP_COMPONENT/ST
DSP_DIR             = $(SYS_DIR)/arch/hz6101/dsp
PROCESS_DIR         = $(SYS_DIR)/arch/hz6101_process
REL_DIR      	    = ./hex


#systme include
CGT_INC             = $(CGT_DIR)/include
SYS_INC			    = $(SYS_DIR)/ucmp-inc
DSP_INC		        = $(DSP_DIR)/inc
PROCESS_INC         = $(PROCESS_DIR)/inc4


#local include
COMMON_INC	        = $(COMMOM_DIR)/inc
COMMON_INC1	        = $(COMMOM_DIR1)/inc



#system lib and link
CGT_LIB             = $(CGT_DIR)/lib
DSP_LIB             = $(DSP_DIR)/lib/HZ6101.lib
LOGIC_LIB           = $(DSP_DIR)/lib/ToolBox.dlb
PROCESS_LIB         = $(PROCESS_DIR)/lib/libProcess.lib
LNK_FILE		        = ./link/linker.cmd


#local source code
APP_SRC		        = $(APP_DIR)/src
APP_INC		        = $(APP_DIR)/src
COMMOM_SRC	        = $(COMMOM_DIR)/src
COMMOM_SRC1	        = $(COMMOM_DIR1)/src



####################################################################################
## notes:
## add "-pdsr232" to CFLAG, to suppress warning message "warning: nonstandard type for a bit field"
####################################################################################

CC_INC      = -I $(CGT_INC) -I $(SYS_INC) -I $(DSP_INC) -I $(PROCESS_INC) -I $(COMMON_INC) -I $(COMMON_INC1) -I $(APP_INC)
CC_LIB      = -I $(CGT_LIB) -l $(DSP_LIB) -l $(LOGIC_LIB) -l $(PROCESS_LIB) 
CCFLAG      = -c -pdsw225 -mv6740 --abi=eabi -pdel1 -pdsr232 -pden -pdsr179 -D CHIP_6713 -D OMAP_DSP -D MAIN_DSP -fr $(OBJ_DIR) -O3 
#LINK_FLAG   = --abi=eabi -z -c -w -x $(CC_LIB) $(LNK_FILE) 
LINK_FLAG   = -z -c -w -x $(CC_LIB) $(LNK_FILE) 



DSP_OUT     = $(OBJ_DIR)/dsp.out

DSP_MAP     = $(OBJ_DIR)/dsp.map
DSP_HEX     = $(OBJ_DIR)/dsp.hex
DSP_APP     = $(REL_DIR)/OMAPDSP

OBJS = $(OBJ_DIR)/usr_app.obj \
       $(OBJ_DIR)/Subroutine.obj \
       $(OBJ_DIR)/QD.obj \
       $(OBJ_DIR)/CommFun.obj	\
       $(OBJ_DIR)/DevAlarm.obj	\
       $(OBJ_DIR)/SENSOR.obj	\
       $(OBJ_DIR)/DEBUGU.obj \
       $(OBJ_DIR)/GLOBAL_VAR.obj \
       $(OBJ_DIR)/sfp.obj \
	   $(OBJ_DIR)/CableInput.obj \
	   $(OBJ_DIR)/Simulate.obj \
	   $(OBJ_DIR)/DualSysPos.obj \
	   $(OBJ_DIR)/BreakInfoDeal.obj \
	   $(OBJ_DIR)/DZCmdMerge.obj \
	   $(OBJ_DIR)/ElecLock.obj \
	   $(OBJ_DIR)/SwPos.obj \
	   $(OBJ_DIR)/BIOGs16.obj \
	   $(OBJ_DIR)/AIOGs16.obj \
	   $(OBJ_DIR)/SysSwapDeal.obj \
	   $(OBJ_DIR)/uart.obj \
	   $(OBJ_DIR)/LoRaUnpack.obj \
	   $(OBJ_DIR)/WirelessRecv.obj
	   
	   
###########################################################
# Begin "lib" test
###########################################################
ifeq ($(MAKECMDGOALS),lib)

BCU_LIB     =  $(OBJ_DIR)/ccc.lib
lib: $(BCU_LIB)

$(BCU_LIB): $(OBJS)
	$(AR) -r $@ $^ 

endif


###########################################################
# Begin "all" configuration
###########################################################
all : app


###########################################################
# Begin "make" configuration
###########################################################
#1. doj  2. out and map     3. TMP  4. hex

app: $(DSP_APP)
hex: $(DSP_HEX)
out: $(DSP_OUT)

$(DSP_APP):  $(DSP_HEX)
	$(ADDCRC) $(DSP_HEX) $(DSP_APP)
	
$(DSP_HEX):  $(DSP_OUT)
	$(HEX6X) $< -a -byte -memwidth 8 -romwidth 8 -order l -o $@

$(DSP_OUT):  $(OBJS) $(DSP_LIB) $(LOGIC_LIB) $(PROCESS_LIB)
	$(CC) $(LINK_FLAG)  $^ -m $(DSP_MAP) -o $@

###########################################################
# Begin all OBJs
###########################################################


$(OBJ_DIR)/%.obj :$(APP_SRC)/%.c
	@echo "-----------------------------------------------------"
	@echo "Compiling $<"
	$(CC) $(CC_INC) $(CCFLAG) $<
	@echo "-----------------------------------------------------"

$(OBJ_DIR)/%.obj :$(COMMOM_SRC)/%.c
	@echo "-----------------------------------------------------"
	@echo "Compiling $<"
	$(CC) $(CC_INC) $(CCFLAG) $<
	@echo "-----------------------------------------------------"

$(OBJ_DIR)/%.obj :$(COMMOM_SRC1)/%.c
	@echo "-----------------------------------------------------"
	@echo "Compiling $<"
	$(CC) $(CC_INC) $(CCFLAG) $<
	@echo "-----------------------------------------------------"

#(CC) $(CC_INC) $(CCFLAG) $< -o $@



###########################################################
# Begin "clean" configuration
###########################################################

clean:
	del /F /Q  "./obj\*.*"
	@echo "clean all objects...ok!"

#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/part_d1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/part_d1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=part_d1.c uart.c D:/G1/5190/Lab/lab2/part_d1.X/LCD_GFX.c D:/G1/5190/Lab/lab2/part_d1.X/ST7735.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/part_d1.o ${OBJECTDIR}/uart.o ${OBJECTDIR}/_ext/1894741347/LCD_GFX.o ${OBJECTDIR}/_ext/1894741347/ST7735.o
POSSIBLE_DEPFILES=${OBJECTDIR}/part_d1.o.d ${OBJECTDIR}/uart.o.d ${OBJECTDIR}/_ext/1894741347/LCD_GFX.o.d ${OBJECTDIR}/_ext/1894741347/ST7735.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/part_d1.o ${OBJECTDIR}/uart.o ${OBJECTDIR}/_ext/1894741347/LCD_GFX.o ${OBJECTDIR}/_ext/1894741347/ST7735.o

# Source Files
SOURCEFILES=part_d1.c uart.c D:/G1/5190/Lab/lab2/part_d1.X/LCD_GFX.c D:/G1/5190/Lab/lab2/part_d1.X/ST7735.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/part_d1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=ATmega328PB
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/part_d1.o: part_d1.c  .generated_files/flags/default/5e866c8e1ea7c05e5c10b1ef8698ea97b88ef868 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/part_d1.o.d 
	@${RM} ${OBJECTDIR}/part_d1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/part_d1.o.d" -MT "${OBJECTDIR}/part_d1.o.d" -MT ${OBJECTDIR}/part_d1.o -o ${OBJECTDIR}/part_d1.o part_d1.c 
	
${OBJECTDIR}/uart.o: uart.c  .generated_files/flags/default/84041ea0c5d1a045e1de27d02a6d6ccd52685dd4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/uart.o.d 
	@${RM} ${OBJECTDIR}/uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/uart.o.d" -MT "${OBJECTDIR}/uart.o.d" -MT ${OBJECTDIR}/uart.o -o ${OBJECTDIR}/uart.o uart.c 
	
${OBJECTDIR}/_ext/1894741347/LCD_GFX.o: D:/G1/5190/Lab/lab2/part_d1.X/LCD_GFX.c  .generated_files/flags/default/539005364c97d7a357205e6db754cc37eac52e79 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1894741347" 
	@${RM} ${OBJECTDIR}/_ext/1894741347/LCD_GFX.o.d 
	@${RM} ${OBJECTDIR}/_ext/1894741347/LCD_GFX.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/1894741347/LCD_GFX.o.d" -MT "${OBJECTDIR}/_ext/1894741347/LCD_GFX.o.d" -MT ${OBJECTDIR}/_ext/1894741347/LCD_GFX.o -o ${OBJECTDIR}/_ext/1894741347/LCD_GFX.o D:/G1/5190/Lab/lab2/part_d1.X/LCD_GFX.c 
	
${OBJECTDIR}/_ext/1894741347/ST7735.o: D:/G1/5190/Lab/lab2/part_d1.X/ST7735.c  .generated_files/flags/default/8611e4a5fa681c05e0b811c5bccb6410f91145ba .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1894741347" 
	@${RM} ${OBJECTDIR}/_ext/1894741347/ST7735.o.d 
	@${RM} ${OBJECTDIR}/_ext/1894741347/ST7735.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/1894741347/ST7735.o.d" -MT "${OBJECTDIR}/_ext/1894741347/ST7735.o.d" -MT ${OBJECTDIR}/_ext/1894741347/ST7735.o -o ${OBJECTDIR}/_ext/1894741347/ST7735.o D:/G1/5190/Lab/lab2/part_d1.X/ST7735.c 
	
else
${OBJECTDIR}/part_d1.o: part_d1.c  .generated_files/flags/default/f394695e1d9e670348adc3aea10afd3f64540537 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/part_d1.o.d 
	@${RM} ${OBJECTDIR}/part_d1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/part_d1.o.d" -MT "${OBJECTDIR}/part_d1.o.d" -MT ${OBJECTDIR}/part_d1.o -o ${OBJECTDIR}/part_d1.o part_d1.c 
	
${OBJECTDIR}/uart.o: uart.c  .generated_files/flags/default/450ee78b23d1b98c80ea186b8bc444fa39eeba4f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/uart.o.d 
	@${RM} ${OBJECTDIR}/uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/uart.o.d" -MT "${OBJECTDIR}/uart.o.d" -MT ${OBJECTDIR}/uart.o -o ${OBJECTDIR}/uart.o uart.c 
	
${OBJECTDIR}/_ext/1894741347/LCD_GFX.o: D:/G1/5190/Lab/lab2/part_d1.X/LCD_GFX.c  .generated_files/flags/default/439f08d44492a5e9e94e649c0de6154785c917b2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1894741347" 
	@${RM} ${OBJECTDIR}/_ext/1894741347/LCD_GFX.o.d 
	@${RM} ${OBJECTDIR}/_ext/1894741347/LCD_GFX.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/1894741347/LCD_GFX.o.d" -MT "${OBJECTDIR}/_ext/1894741347/LCD_GFX.o.d" -MT ${OBJECTDIR}/_ext/1894741347/LCD_GFX.o -o ${OBJECTDIR}/_ext/1894741347/LCD_GFX.o D:/G1/5190/Lab/lab2/part_d1.X/LCD_GFX.c 
	
${OBJECTDIR}/_ext/1894741347/ST7735.o: D:/G1/5190/Lab/lab2/part_d1.X/ST7735.c  .generated_files/flags/default/69e484f716918b95b04acb47236da025b1af9565 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1894741347" 
	@${RM} ${OBJECTDIR}/_ext/1894741347/ST7735.o.d 
	@${RM} ${OBJECTDIR}/_ext/1894741347/ST7735.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/_ext/1894741347/ST7735.o.d" -MT "${OBJECTDIR}/_ext/1894741347/ST7735.o.d" -MT ${OBJECTDIR}/_ext/1894741347/ST7735.o -o ${OBJECTDIR}/_ext/1894741347/ST7735.o D:/G1/5190/Lab/lab2/part_d1.X/ST7735.c 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/part_d1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/part_d1.X.${IMAGE_TYPE}.map  -D__DEBUG=1  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"   -gdwarf-2 -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -gdwarf-3 -mno-const-data-in-progmem     $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/part_d1.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  -o ${DISTDIR}/part_d1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -Wl,--start-group  -Wl,--end-group  -Wl,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1
	@${RM} ${DISTDIR}/part_d1.X.${IMAGE_TYPE}.hex 
	
	
else
${DISTDIR}/part_d1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/part_d1.X.${IMAGE_TYPE}.map  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -gdwarf-3 -mno-const-data-in-progmem     $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/part_d1.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  -o ${DISTDIR}/part_d1.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -Wl,--start-group  -Wl,--end-group 
	${MP_CC_DIR}\\avr-objcopy -O ihex "${DISTDIR}/part_d1.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "${DISTDIR}/part_d1.X.${IMAGE_TYPE}.hex"
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif

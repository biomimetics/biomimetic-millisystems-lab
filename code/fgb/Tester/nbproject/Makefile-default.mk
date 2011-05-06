#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
include Makefile

# Environment
MKDIR=mkdir -p
RM=rm -f 
CP=cp 
# Macros
CND_CONF=default

ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Tester.${IMAGE_TYPE}.elf
else
IMAGE_TYPE=production
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Tester.${IMAGE_TYPE}.elf
endif
# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}
# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/877975035/xl.o ${OBJECTDIR}/_ext/877975035/dfmem.o ${OBJECTDIR}/_ext/877975035/init_default.o ${OBJECTDIR}/_ext/1360930230/interrupts.o ${OBJECTDIR}/_ext/877975035/gyro.o ${OBJECTDIR}/_ext/877975035/ovcamHS.o ${OBJECTDIR}/_ext/1360930230/init.o ${OBJECTDIR}/_ext/877975035/stopwatch.o ${OBJECTDIR}/_ext/877975035/ovcam.o ${OBJECTDIR}/_ext/877975035/delay.o ${OBJECTDIR}/main.o


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

# Path to java used to run MPLAB X when this makefile was created
MP_JAVA_PATH=/System/Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Home/bin/
OS_ORIGINAL="Darwin"
OS_CURRENT="$(shell uname -s)"
############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
MP_CC=/Applications/Microchip/mplabc30/v3.24/bin/pic30-gcc
# MP_BC is not defined
MP_AS=/Applications/Microchip/mplabc30/v3.24/bin/pic30-as
MP_LD=/Applications/Microchip/mplabc30/v3.24/bin/pic30-ld
MP_AR=/Applications/Microchip/mplabc30/v3.24/bin/pic30-ar
# MP_BC is not defined
MP_CC_DIR=/Applications/Microchip/mplabc30/v3.24/bin
# MP_BC_DIR is not defined
MP_AS_DIR=/Applications/Microchip/mplabc30/v3.24/bin
MP_LD_DIR=/Applications/Microchip/mplabc30/v3.24/bin
MP_AR_DIR=/Applications/Microchip/mplabc30/v3.24/bin
# MP_BC_DIR is not defined
.build-conf: ${BUILD_SUBPROJECTS}
ifneq ($(OS_CURRENT),$(OS_ORIGINAL))
	@echo "***** WARNING: This make file contains OS dependent code. The OS this makefile is being run is different from the OS it was created in."
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Tester.${IMAGE_TYPE}.elf

MP_PROCESSOR_OPTION=33FJ128MC706A
MP_LINKER_FILE_OPTION=,-Tp33FJ128MC706A.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
.PHONY: ${OBJECTDIR}/_ext/877975035/ovcamHS.o
${OBJECTDIR}/_ext/877975035/ovcamHS.o: ../../shared/ovcamHS.s  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/877975035 
	${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -c -mcpu=$(MP_PROCESSOR_OPTION)  -o ${OBJECTDIR}/_ext/877975035/ovcamHS.o ../../shared/ovcamHS.s  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,-g,-I".."
.PHONY: ${OBJECTDIR}/_ext/877975035/delay.o
${OBJECTDIR}/_ext/877975035/delay.o: ../../shared/delay.s  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/877975035 
	${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -c -mcpu=$(MP_PROCESSOR_OPTION)  -o ${OBJECTDIR}/_ext/877975035/delay.o ../../shared/delay.s  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,-g,-I".."
else
.PHONY: ${OBJECTDIR}/_ext/877975035/ovcamHS.o
${OBJECTDIR}/_ext/877975035/ovcamHS.o: ../../shared/ovcamHS.s  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/877975035 
	${MP_CC} $(MP_EXTRA_AS_PRE)  -omf=elf -c -mcpu=$(MP_PROCESSOR_OPTION)  -o ${OBJECTDIR}/_ext/877975035/ovcamHS.o ../../shared/ovcamHS.s  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-I".."
.PHONY: ${OBJECTDIR}/_ext/877975035/delay.o
${OBJECTDIR}/_ext/877975035/delay.o: ../../shared/delay.s  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/877975035 
	${MP_CC} $(MP_EXTRA_AS_PRE)  -omf=elf -c -mcpu=$(MP_PROCESSOR_OPTION)  -o ${OBJECTDIR}/_ext/877975035/delay.o ../../shared/delay.s  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-I".."
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/877975035/xl.o: ../../shared/xl.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/877975035 
	${RM} ${OBJECTDIR}/_ext/877975035/xl.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -fno-short-double -Wall -D__IMAGEPROC2 -I"../lib" -I"../../shared" -MMD -MF ${OBJECTDIR}/_ext/877975035/xl.o.d -o ${OBJECTDIR}/_ext/877975035/xl.o ../../shared/xl.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/877975035/xl.o.d > ${OBJECTDIR}/_ext/877975035/xl.o.tmp
	${RM} ${OBJECTDIR}/_ext/877975035/xl.o.d 
	${CP} ${OBJECTDIR}/_ext/877975035/xl.o.tmp ${OBJECTDIR}/_ext/877975035/xl.o.d 
	${RM} ${OBJECTDIR}/_ext/877975035/xl.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/877975035/xl.o.d > ${OBJECTDIR}/_ext/877975035/xl.o.tmp
	${RM} ${OBJECTDIR}/_ext/877975035/xl.o.d 
	${CP} ${OBJECTDIR}/_ext/877975035/xl.o.tmp ${OBJECTDIR}/_ext/877975035/xl.o.d 
	${RM} ${OBJECTDIR}/_ext/877975035/xl.o.tmp
endif
${OBJECTDIR}/_ext/877975035/dfmem.o: ../../shared/dfmem.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/877975035 
	${RM} ${OBJECTDIR}/_ext/877975035/dfmem.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -fno-short-double -Wall -D__IMAGEPROC2 -I"../lib" -I"../../shared" -MMD -MF ${OBJECTDIR}/_ext/877975035/dfmem.o.d -o ${OBJECTDIR}/_ext/877975035/dfmem.o ../../shared/dfmem.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/877975035/dfmem.o.d > ${OBJECTDIR}/_ext/877975035/dfmem.o.tmp
	${RM} ${OBJECTDIR}/_ext/877975035/dfmem.o.d 
	${CP} ${OBJECTDIR}/_ext/877975035/dfmem.o.tmp ${OBJECTDIR}/_ext/877975035/dfmem.o.d 
	${RM} ${OBJECTDIR}/_ext/877975035/dfmem.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/877975035/dfmem.o.d > ${OBJECTDIR}/_ext/877975035/dfmem.o.tmp
	${RM} ${OBJECTDIR}/_ext/877975035/dfmem.o.d 
	${CP} ${OBJECTDIR}/_ext/877975035/dfmem.o.tmp ${OBJECTDIR}/_ext/877975035/dfmem.o.d 
	${RM} ${OBJECTDIR}/_ext/877975035/dfmem.o.tmp
endif
${OBJECTDIR}/_ext/877975035/init_default.o: ../../shared/init_default.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/877975035 
	${RM} ${OBJECTDIR}/_ext/877975035/init_default.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -fno-short-double -Wall -D__IMAGEPROC2 -I"../lib" -I"../../shared" -MMD -MF ${OBJECTDIR}/_ext/877975035/init_default.o.d -o ${OBJECTDIR}/_ext/877975035/init_default.o ../../shared/init_default.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/877975035/init_default.o.d > ${OBJECTDIR}/_ext/877975035/init_default.o.tmp
	${RM} ${OBJECTDIR}/_ext/877975035/init_default.o.d 
	${CP} ${OBJECTDIR}/_ext/877975035/init_default.o.tmp ${OBJECTDIR}/_ext/877975035/init_default.o.d 
	${RM} ${OBJECTDIR}/_ext/877975035/init_default.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/877975035/init_default.o.d > ${OBJECTDIR}/_ext/877975035/init_default.o.tmp
	${RM} ${OBJECTDIR}/_ext/877975035/init_default.o.d 
	${CP} ${OBJECTDIR}/_ext/877975035/init_default.o.tmp ${OBJECTDIR}/_ext/877975035/init_default.o.d 
	${RM} ${OBJECTDIR}/_ext/877975035/init_default.o.tmp
endif
${OBJECTDIR}/_ext/1360930230/interrupts.o: ../lib/interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1360930230 
	${RM} ${OBJECTDIR}/_ext/1360930230/interrupts.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -fno-short-double -Wall -D__IMAGEPROC2 -I"../lib" -I"../../shared" -MMD -MF ${OBJECTDIR}/_ext/1360930230/interrupts.o.d -o ${OBJECTDIR}/_ext/1360930230/interrupts.o ../lib/interrupts.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1360930230/interrupts.o.d > ${OBJECTDIR}/_ext/1360930230/interrupts.o.tmp
	${RM} ${OBJECTDIR}/_ext/1360930230/interrupts.o.d 
	${CP} ${OBJECTDIR}/_ext/1360930230/interrupts.o.tmp ${OBJECTDIR}/_ext/1360930230/interrupts.o.d 
	${RM} ${OBJECTDIR}/_ext/1360930230/interrupts.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1360930230/interrupts.o.d > ${OBJECTDIR}/_ext/1360930230/interrupts.o.tmp
	${RM} ${OBJECTDIR}/_ext/1360930230/interrupts.o.d 
	${CP} ${OBJECTDIR}/_ext/1360930230/interrupts.o.tmp ${OBJECTDIR}/_ext/1360930230/interrupts.o.d 
	${RM} ${OBJECTDIR}/_ext/1360930230/interrupts.o.tmp
endif
${OBJECTDIR}/_ext/877975035/gyro.o: ../../shared/gyro.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/877975035 
	${RM} ${OBJECTDIR}/_ext/877975035/gyro.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -fno-short-double -Wall -D__IMAGEPROC2 -I"../lib" -I"../../shared" -MMD -MF ${OBJECTDIR}/_ext/877975035/gyro.o.d -o ${OBJECTDIR}/_ext/877975035/gyro.o ../../shared/gyro.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/877975035/gyro.o.d > ${OBJECTDIR}/_ext/877975035/gyro.o.tmp
	${RM} ${OBJECTDIR}/_ext/877975035/gyro.o.d 
	${CP} ${OBJECTDIR}/_ext/877975035/gyro.o.tmp ${OBJECTDIR}/_ext/877975035/gyro.o.d 
	${RM} ${OBJECTDIR}/_ext/877975035/gyro.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/877975035/gyro.o.d > ${OBJECTDIR}/_ext/877975035/gyro.o.tmp
	${RM} ${OBJECTDIR}/_ext/877975035/gyro.o.d 
	${CP} ${OBJECTDIR}/_ext/877975035/gyro.o.tmp ${OBJECTDIR}/_ext/877975035/gyro.o.d 
	${RM} ${OBJECTDIR}/_ext/877975035/gyro.o.tmp
endif
${OBJECTDIR}/_ext/1360930230/init.o: ../lib/init.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1360930230 
	${RM} ${OBJECTDIR}/_ext/1360930230/init.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -fno-short-double -Wall -D__IMAGEPROC2 -I"../lib" -I"../../shared" -MMD -MF ${OBJECTDIR}/_ext/1360930230/init.o.d -o ${OBJECTDIR}/_ext/1360930230/init.o ../lib/init.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1360930230/init.o.d > ${OBJECTDIR}/_ext/1360930230/init.o.tmp
	${RM} ${OBJECTDIR}/_ext/1360930230/init.o.d 
	${CP} ${OBJECTDIR}/_ext/1360930230/init.o.tmp ${OBJECTDIR}/_ext/1360930230/init.o.d 
	${RM} ${OBJECTDIR}/_ext/1360930230/init.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1360930230/init.o.d > ${OBJECTDIR}/_ext/1360930230/init.o.tmp
	${RM} ${OBJECTDIR}/_ext/1360930230/init.o.d 
	${CP} ${OBJECTDIR}/_ext/1360930230/init.o.tmp ${OBJECTDIR}/_ext/1360930230/init.o.d 
	${RM} ${OBJECTDIR}/_ext/1360930230/init.o.tmp
endif
${OBJECTDIR}/_ext/877975035/stopwatch.o: ../../shared/stopwatch.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/877975035 
	${RM} ${OBJECTDIR}/_ext/877975035/stopwatch.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -fno-short-double -Wall -D__IMAGEPROC2 -I"../lib" -I"../../shared" -MMD -MF ${OBJECTDIR}/_ext/877975035/stopwatch.o.d -o ${OBJECTDIR}/_ext/877975035/stopwatch.o ../../shared/stopwatch.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/877975035/stopwatch.o.d > ${OBJECTDIR}/_ext/877975035/stopwatch.o.tmp
	${RM} ${OBJECTDIR}/_ext/877975035/stopwatch.o.d 
	${CP} ${OBJECTDIR}/_ext/877975035/stopwatch.o.tmp ${OBJECTDIR}/_ext/877975035/stopwatch.o.d 
	${RM} ${OBJECTDIR}/_ext/877975035/stopwatch.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/877975035/stopwatch.o.d > ${OBJECTDIR}/_ext/877975035/stopwatch.o.tmp
	${RM} ${OBJECTDIR}/_ext/877975035/stopwatch.o.d 
	${CP} ${OBJECTDIR}/_ext/877975035/stopwatch.o.tmp ${OBJECTDIR}/_ext/877975035/stopwatch.o.d 
	${RM} ${OBJECTDIR}/_ext/877975035/stopwatch.o.tmp
endif
${OBJECTDIR}/_ext/877975035/ovcam.o: ../../shared/ovcam.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/877975035 
	${RM} ${OBJECTDIR}/_ext/877975035/ovcam.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -fno-short-double -Wall -D__IMAGEPROC2 -I"../lib" -I"../../shared" -MMD -MF ${OBJECTDIR}/_ext/877975035/ovcam.o.d -o ${OBJECTDIR}/_ext/877975035/ovcam.o ../../shared/ovcam.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/877975035/ovcam.o.d > ${OBJECTDIR}/_ext/877975035/ovcam.o.tmp
	${RM} ${OBJECTDIR}/_ext/877975035/ovcam.o.d 
	${CP} ${OBJECTDIR}/_ext/877975035/ovcam.o.tmp ${OBJECTDIR}/_ext/877975035/ovcam.o.d 
	${RM} ${OBJECTDIR}/_ext/877975035/ovcam.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/877975035/ovcam.o.d > ${OBJECTDIR}/_ext/877975035/ovcam.o.tmp
	${RM} ${OBJECTDIR}/_ext/877975035/ovcam.o.d 
	${CP} ${OBJECTDIR}/_ext/877975035/ovcam.o.tmp ${OBJECTDIR}/_ext/877975035/ovcam.o.d 
	${RM} ${OBJECTDIR}/_ext/877975035/ovcam.o.tmp
endif
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR} 
	${RM} ${OBJECTDIR}/main.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -fno-short-double -Wall -D__IMAGEPROC2 -I"../lib" -I"../../shared" -MMD -MF ${OBJECTDIR}/main.o.d -o ${OBJECTDIR}/main.o main.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/main.o.d > ${OBJECTDIR}/main.o.tmp
	${RM} ${OBJECTDIR}/main.o.d 
	${CP} ${OBJECTDIR}/main.o.tmp ${OBJECTDIR}/main.o.d 
	${RM} ${OBJECTDIR}/main.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/main.o.d > ${OBJECTDIR}/main.o.tmp
	${RM} ${OBJECTDIR}/main.o.d 
	${CP} ${OBJECTDIR}/main.o.tmp ${OBJECTDIR}/main.o.d 
	${RM} ${OBJECTDIR}/main.o.tmp
endif
else
${OBJECTDIR}/_ext/877975035/xl.o: ../../shared/xl.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/877975035 
	${RM} ${OBJECTDIR}/_ext/877975035/xl.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -fno-short-double -Wall -D__IMAGEPROC2 -I"../lib" -I"../../shared" -MMD -MF ${OBJECTDIR}/_ext/877975035/xl.o.d -o ${OBJECTDIR}/_ext/877975035/xl.o ../../shared/xl.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/877975035/xl.o.d > ${OBJECTDIR}/_ext/877975035/xl.o.tmp
	${RM} ${OBJECTDIR}/_ext/877975035/xl.o.d 
	${CP} ${OBJECTDIR}/_ext/877975035/xl.o.tmp ${OBJECTDIR}/_ext/877975035/xl.o.d 
	${RM} ${OBJECTDIR}/_ext/877975035/xl.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/877975035/xl.o.d > ${OBJECTDIR}/_ext/877975035/xl.o.tmp
	${RM} ${OBJECTDIR}/_ext/877975035/xl.o.d 
	${CP} ${OBJECTDIR}/_ext/877975035/xl.o.tmp ${OBJECTDIR}/_ext/877975035/xl.o.d 
	${RM} ${OBJECTDIR}/_ext/877975035/xl.o.tmp
endif
${OBJECTDIR}/_ext/877975035/dfmem.o: ../../shared/dfmem.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/877975035 
	${RM} ${OBJECTDIR}/_ext/877975035/dfmem.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -fno-short-double -Wall -D__IMAGEPROC2 -I"../lib" -I"../../shared" -MMD -MF ${OBJECTDIR}/_ext/877975035/dfmem.o.d -o ${OBJECTDIR}/_ext/877975035/dfmem.o ../../shared/dfmem.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/877975035/dfmem.o.d > ${OBJECTDIR}/_ext/877975035/dfmem.o.tmp
	${RM} ${OBJECTDIR}/_ext/877975035/dfmem.o.d 
	${CP} ${OBJECTDIR}/_ext/877975035/dfmem.o.tmp ${OBJECTDIR}/_ext/877975035/dfmem.o.d 
	${RM} ${OBJECTDIR}/_ext/877975035/dfmem.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/877975035/dfmem.o.d > ${OBJECTDIR}/_ext/877975035/dfmem.o.tmp
	${RM} ${OBJECTDIR}/_ext/877975035/dfmem.o.d 
	${CP} ${OBJECTDIR}/_ext/877975035/dfmem.o.tmp ${OBJECTDIR}/_ext/877975035/dfmem.o.d 
	${RM} ${OBJECTDIR}/_ext/877975035/dfmem.o.tmp
endif
${OBJECTDIR}/_ext/877975035/init_default.o: ../../shared/init_default.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/877975035 
	${RM} ${OBJECTDIR}/_ext/877975035/init_default.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -fno-short-double -Wall -D__IMAGEPROC2 -I"../lib" -I"../../shared" -MMD -MF ${OBJECTDIR}/_ext/877975035/init_default.o.d -o ${OBJECTDIR}/_ext/877975035/init_default.o ../../shared/init_default.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/877975035/init_default.o.d > ${OBJECTDIR}/_ext/877975035/init_default.o.tmp
	${RM} ${OBJECTDIR}/_ext/877975035/init_default.o.d 
	${CP} ${OBJECTDIR}/_ext/877975035/init_default.o.tmp ${OBJECTDIR}/_ext/877975035/init_default.o.d 
	${RM} ${OBJECTDIR}/_ext/877975035/init_default.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/877975035/init_default.o.d > ${OBJECTDIR}/_ext/877975035/init_default.o.tmp
	${RM} ${OBJECTDIR}/_ext/877975035/init_default.o.d 
	${CP} ${OBJECTDIR}/_ext/877975035/init_default.o.tmp ${OBJECTDIR}/_ext/877975035/init_default.o.d 
	${RM} ${OBJECTDIR}/_ext/877975035/init_default.o.tmp
endif
${OBJECTDIR}/_ext/1360930230/interrupts.o: ../lib/interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1360930230 
	${RM} ${OBJECTDIR}/_ext/1360930230/interrupts.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -fno-short-double -Wall -D__IMAGEPROC2 -I"../lib" -I"../../shared" -MMD -MF ${OBJECTDIR}/_ext/1360930230/interrupts.o.d -o ${OBJECTDIR}/_ext/1360930230/interrupts.o ../lib/interrupts.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1360930230/interrupts.o.d > ${OBJECTDIR}/_ext/1360930230/interrupts.o.tmp
	${RM} ${OBJECTDIR}/_ext/1360930230/interrupts.o.d 
	${CP} ${OBJECTDIR}/_ext/1360930230/interrupts.o.tmp ${OBJECTDIR}/_ext/1360930230/interrupts.o.d 
	${RM} ${OBJECTDIR}/_ext/1360930230/interrupts.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1360930230/interrupts.o.d > ${OBJECTDIR}/_ext/1360930230/interrupts.o.tmp
	${RM} ${OBJECTDIR}/_ext/1360930230/interrupts.o.d 
	${CP} ${OBJECTDIR}/_ext/1360930230/interrupts.o.tmp ${OBJECTDIR}/_ext/1360930230/interrupts.o.d 
	${RM} ${OBJECTDIR}/_ext/1360930230/interrupts.o.tmp
endif
${OBJECTDIR}/_ext/877975035/gyro.o: ../../shared/gyro.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/877975035 
	${RM} ${OBJECTDIR}/_ext/877975035/gyro.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -fno-short-double -Wall -D__IMAGEPROC2 -I"../lib" -I"../../shared" -MMD -MF ${OBJECTDIR}/_ext/877975035/gyro.o.d -o ${OBJECTDIR}/_ext/877975035/gyro.o ../../shared/gyro.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/877975035/gyro.o.d > ${OBJECTDIR}/_ext/877975035/gyro.o.tmp
	${RM} ${OBJECTDIR}/_ext/877975035/gyro.o.d 
	${CP} ${OBJECTDIR}/_ext/877975035/gyro.o.tmp ${OBJECTDIR}/_ext/877975035/gyro.o.d 
	${RM} ${OBJECTDIR}/_ext/877975035/gyro.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/877975035/gyro.o.d > ${OBJECTDIR}/_ext/877975035/gyro.o.tmp
	${RM} ${OBJECTDIR}/_ext/877975035/gyro.o.d 
	${CP} ${OBJECTDIR}/_ext/877975035/gyro.o.tmp ${OBJECTDIR}/_ext/877975035/gyro.o.d 
	${RM} ${OBJECTDIR}/_ext/877975035/gyro.o.tmp
endif
${OBJECTDIR}/_ext/1360930230/init.o: ../lib/init.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1360930230 
	${RM} ${OBJECTDIR}/_ext/1360930230/init.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -fno-short-double -Wall -D__IMAGEPROC2 -I"../lib" -I"../../shared" -MMD -MF ${OBJECTDIR}/_ext/1360930230/init.o.d -o ${OBJECTDIR}/_ext/1360930230/init.o ../lib/init.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1360930230/init.o.d > ${OBJECTDIR}/_ext/1360930230/init.o.tmp
	${RM} ${OBJECTDIR}/_ext/1360930230/init.o.d 
	${CP} ${OBJECTDIR}/_ext/1360930230/init.o.tmp ${OBJECTDIR}/_ext/1360930230/init.o.d 
	${RM} ${OBJECTDIR}/_ext/1360930230/init.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1360930230/init.o.d > ${OBJECTDIR}/_ext/1360930230/init.o.tmp
	${RM} ${OBJECTDIR}/_ext/1360930230/init.o.d 
	${CP} ${OBJECTDIR}/_ext/1360930230/init.o.tmp ${OBJECTDIR}/_ext/1360930230/init.o.d 
	${RM} ${OBJECTDIR}/_ext/1360930230/init.o.tmp
endif
${OBJECTDIR}/_ext/877975035/stopwatch.o: ../../shared/stopwatch.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/877975035 
	${RM} ${OBJECTDIR}/_ext/877975035/stopwatch.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -fno-short-double -Wall -D__IMAGEPROC2 -I"../lib" -I"../../shared" -MMD -MF ${OBJECTDIR}/_ext/877975035/stopwatch.o.d -o ${OBJECTDIR}/_ext/877975035/stopwatch.o ../../shared/stopwatch.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/877975035/stopwatch.o.d > ${OBJECTDIR}/_ext/877975035/stopwatch.o.tmp
	${RM} ${OBJECTDIR}/_ext/877975035/stopwatch.o.d 
	${CP} ${OBJECTDIR}/_ext/877975035/stopwatch.o.tmp ${OBJECTDIR}/_ext/877975035/stopwatch.o.d 
	${RM} ${OBJECTDIR}/_ext/877975035/stopwatch.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/877975035/stopwatch.o.d > ${OBJECTDIR}/_ext/877975035/stopwatch.o.tmp
	${RM} ${OBJECTDIR}/_ext/877975035/stopwatch.o.d 
	${CP} ${OBJECTDIR}/_ext/877975035/stopwatch.o.tmp ${OBJECTDIR}/_ext/877975035/stopwatch.o.d 
	${RM} ${OBJECTDIR}/_ext/877975035/stopwatch.o.tmp
endif
${OBJECTDIR}/_ext/877975035/ovcam.o: ../../shared/ovcam.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/877975035 
	${RM} ${OBJECTDIR}/_ext/877975035/ovcam.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -fno-short-double -Wall -D__IMAGEPROC2 -I"../lib" -I"../../shared" -MMD -MF ${OBJECTDIR}/_ext/877975035/ovcam.o.d -o ${OBJECTDIR}/_ext/877975035/ovcam.o ../../shared/ovcam.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/877975035/ovcam.o.d > ${OBJECTDIR}/_ext/877975035/ovcam.o.tmp
	${RM} ${OBJECTDIR}/_ext/877975035/ovcam.o.d 
	${CP} ${OBJECTDIR}/_ext/877975035/ovcam.o.tmp ${OBJECTDIR}/_ext/877975035/ovcam.o.d 
	${RM} ${OBJECTDIR}/_ext/877975035/ovcam.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/877975035/ovcam.o.d > ${OBJECTDIR}/_ext/877975035/ovcam.o.tmp
	${RM} ${OBJECTDIR}/_ext/877975035/ovcam.o.d 
	${CP} ${OBJECTDIR}/_ext/877975035/ovcam.o.tmp ${OBJECTDIR}/_ext/877975035/ovcam.o.d 
	${RM} ${OBJECTDIR}/_ext/877975035/ovcam.o.tmp
endif
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR} 
	${RM} ${OBJECTDIR}/main.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -fno-short-double -Wall -D__IMAGEPROC2 -I"../lib" -I"../../shared" -MMD -MF ${OBJECTDIR}/main.o.d -o ${OBJECTDIR}/main.o main.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/main.o.d > ${OBJECTDIR}/main.o.tmp
	${RM} ${OBJECTDIR}/main.o.d 
	${CP} ${OBJECTDIR}/main.o.tmp ${OBJECTDIR}/main.o.d 
	${RM} ${OBJECTDIR}/main.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/main.o.d > ${OBJECTDIR}/main.o.tmp
	${RM} ${OBJECTDIR}/main.o.d 
	${CP} ${OBJECTDIR}/main.o.tmp ${OBJECTDIR}/main.o.d 
	${RM} ${OBJECTDIR}/main.o.tmp
endif
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Tester.${IMAGE_TYPE}.elf: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf  -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -o dist/${CND_CONF}/${IMAGE_TYPE}/Tester.${IMAGE_TYPE}.elf ${OBJECTFILES}        -Wl,--defsym=__MPLAB_BUILD=1,-L"/opt/microchip/mplabc30/v3.24/lib",-Map="$(BINDIR_)$(TARGETBASE).map",--report-mem,--report-mem$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1
else
dist/${CND_CONF}/${IMAGE_TYPE}/Tester.${IMAGE_TYPE}.elf: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf  -mcpu=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Tester.${IMAGE_TYPE}.elf ${OBJECTFILES}        -Wl,--defsym=__MPLAB_BUILD=1,-L"/opt/microchip/mplabc30/v3.24/lib",-Map="$(BINDIR_)$(TARGETBASE).map",--report-mem,--report-mem$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION)
	${MP_CC_DIR}/pic30-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Tester.${IMAGE_TYPE}.elf -omf=elf
endif


# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/CABO.o \
	${OBJECTDIR}/CCartwright.o \
	${OBJECTDIR}/CColton.o \
	${OBJECTDIR}/CCromer.o \
	${OBJECTDIR}/CDiegoWright.o \
	${OBJECTDIR}/CDombrock.o \
	${OBJECTDIR}/CDuffy.o \
	${OBJECTDIR}/CIndian.o \
	${OBJECTDIR}/CJR.o \
	${OBJECTDIR}/CKEL.o \
	${OBJECTDIR}/CKidd.o \
	${OBJECTDIR}/CKnoops.o \
	${OBJECTDIR}/CLU.o \
	${OBJECTDIR}/CLan.o \
	${OBJECTDIR}/CLandsteiner.o \
	${OBJECTDIR}/CMNS.o \
	${OBJECTDIR}/CRBCsnps.o \
	${OBJECTDIR}/CRHCE.o \
	${OBJECTDIR}/CRHD.o \
	${OBJECTDIR}/CSNP.o \
	${OBJECTDIR}/CSNPNameLookupMixin.o \
	${OBJECTDIR}/CScianna.o \
	${OBJECTDIR}/CSubstitutions.o \
	${OBJECTDIR}/CVel.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L../MyTools/dist/Debug/GNU-Linux -Wl,-rpath,'../MyTools/dist/Debug/GNU-Linux'

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/bloodarray

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/bloodarray: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/bloodarray ${OBJECTFILES} ${LDLIBSOPTIONS} -lMyTools

${OBJECTDIR}/CABO.o: CABO.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../MyTools -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CABO.o CABO.cpp

${OBJECTDIR}/CCartwright.o: CCartwright.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../MyTools -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CCartwright.o CCartwright.cpp

${OBJECTDIR}/CColton.o: CColton.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../MyTools -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CColton.o CColton.cpp

${OBJECTDIR}/CCromer.o: CCromer.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../MyTools -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CCromer.o CCromer.cpp

${OBJECTDIR}/CDiegoWright.o: CDiegoWright.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../MyTools -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CDiegoWright.o CDiegoWright.cpp

${OBJECTDIR}/CDombrock.o: CDombrock.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../MyTools -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CDombrock.o CDombrock.cpp

${OBJECTDIR}/CDuffy.o: CDuffy.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../MyTools -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CDuffy.o CDuffy.cpp

${OBJECTDIR}/CIndian.o: CIndian.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../MyTools -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CIndian.o CIndian.cpp

${OBJECTDIR}/CJR.o: CJR.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../MyTools -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CJR.o CJR.cpp

${OBJECTDIR}/CKEL.o: CKEL.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../MyTools -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CKEL.o CKEL.cpp

${OBJECTDIR}/CKidd.o: CKidd.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../MyTools -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CKidd.o CKidd.cpp

${OBJECTDIR}/CKnoops.o: CKnoops.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../MyTools -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CKnoops.o CKnoops.cpp

${OBJECTDIR}/CLU.o: CLU.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../MyTools -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CLU.o CLU.cpp

${OBJECTDIR}/CLan.o: CLan.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../MyTools -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CLan.o CLan.cpp

${OBJECTDIR}/CLandsteiner.o: CLandsteiner.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../MyTools -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CLandsteiner.o CLandsteiner.cpp

${OBJECTDIR}/CMNS.o: CMNS.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../MyTools -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CMNS.o CMNS.cpp

${OBJECTDIR}/CRBCsnps.o: CRBCsnps.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../MyTools -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CRBCsnps.o CRBCsnps.cpp

${OBJECTDIR}/CRHCE.o: CRHCE.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../MyTools -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CRHCE.o CRHCE.cpp

${OBJECTDIR}/CRHD.o: CRHD.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../MyTools -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CRHD.o CRHD.cpp

${OBJECTDIR}/CSNP.o: CSNP.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../MyTools -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CSNP.o CSNP.cpp

${OBJECTDIR}/CSNPNameLookupMixin.o: CSNPNameLookupMixin.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../MyTools -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CSNPNameLookupMixin.o CSNPNameLookupMixin.cpp

${OBJECTDIR}/CScianna.o: CScianna.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../MyTools -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CScianna.o CScianna.cpp

${OBJECTDIR}/CSubstitutions.o: CSubstitutions.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../MyTools -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CSubstitutions.o CSubstitutions.cpp

${OBJECTDIR}/CVel.o: CVel.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../MyTools -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CVel.o CVel.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../MyTools -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/queueProg.o


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
LDLIBSOPTIONS=-L../../Downloads/mysql-connector-c++-1.1.8-linux-ubuntu16.10-x86-64bit/lib -L../../Desktop/PCAN_Basic_Linux-4.1.1/pcanbasic/examples/c++/src ../../Downloads/mysql-connector-c++-1.1.8-linux-ubuntu16.10-x86-64bit/lib/libmysqlcppconn.so /opt/lampp/lib/libmysqlclient.a -lpcanbasic

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pcanprojectcombined

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pcanprojectcombined: ../../Downloads/mysql-connector-c++-1.1.8-linux-ubuntu16.10-x86-64bit/lib/libmysqlcppconn.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pcanprojectcombined: /opt/lampp/lib/libmysqlclient.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pcanprojectcombined: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pcanprojectcombined ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/queueProg.o: queueProg.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I../../Downloads/mysql-connector-c++-1.1.8-linux-ubuntu16.10-x86-64bit/include -I../../Downloads/mysql-connector-c++-1.1.8-linux-ubuntu16.10-x86-64bit/include/cppconn -I../../Downloads/boost_1_64_0 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/queueProg.o queueProg.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} -r ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libmysqlcppconn.so
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pcanprojectcombined

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

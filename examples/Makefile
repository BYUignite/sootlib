CHEMISTRY   = CANTERARR
PARALLEL    = NO
options      =  -O3
linkoptions  +=  -framework Accelerate
cppoptions   = -std=c++11
CC_COMPILER_NAME = g++
C_COMPILER_NAME  = gcc
CANT_LIB = /usr/local/cantera24/lib       # Homebrew-installed path
CANT_INC = /usr/local/cantera24/include   # Homebrew-installed path

####################   DIRECTORIES   ##########################################

SRCDIR       = ./
CVODE_SRCDIR = cvode/
PROG         = test.x

####################   COMPILATION   ##########################################

includes += -I$(SRCDIR)

####################   Cantera flags   ########################################

ext_libs += -lcantera -lsootlib
includes += -I$(CANT_INC)
libs     += -L$(CANT_LIB) -L../lib

####################   other flags   ##########################################

ifneq ($(CHEMISTRY), CANTERARR)
    D1        = -DPROBLEMSPECIFICRR
endif

DIRECTIVES = $(D1) $(D2) $(D3) -D_USESTDVECTOR_

COMPCC   = $(CC_COMPILER_NAME) $(includes) $(options) $(cppoptions) $(DIRECTIVES) -c
COMPC    = $(C_COMPILER_NAME)  $(includes) $(options) $(DIRECTIVES) -c

COMPDEP  = $(CC_COMPILER_NAME) $(includes) $(options) $(cppoptions) $(DIRECTIVES)  -MM -MT
COMPDEPC = $(C_COMPILER_NAME)  $(includes) $(options) $(DIRECTIVES)  -MM -MT

LINK     = $(CC_COMPILER_NAME) $(options) $(linkoptions) $(libs)

######################## SOURCE FILES ##########################

SRC   = $(SRCDIR)main.cc


CVSRC = $(CVODE_SRCDIR)sundials_smalldense.c     \
        $(CVODE_SRCDIR)sundials_nvector.c        \
        $(CVODE_SRCDIR)sundials_math.c           \
        $(CVODE_SRCDIR)sundials_dense.c          \
        $(CVODE_SRCDIR)nvector_serial.c          \
        $(CVODE_SRCDIR)cvode_io.c                \
        $(CVODE_SRCDIR)cvode_dense.c             \
        $(CVODE_SRCDIR)cvode.c

#-------Add your rxn rate file here: make another ifeq block

ifeq ($(CHEMISTRY), ONESTEPC2H4)
    SRC += $(SRCDIR)user_chemical_mechanisms/onestep_c2h4.cc
endif
ifeq ($(CHEMISTRY), ONESTEPCH4)
    SRC += $(SRCDIR)user_chemical_mechanisms/onestep_ch4.cc
endif
ifeq ($(CHEMISTRY), C2H4RED)
    SRC += $(SRCDIR)user_chemical_mechanisms/c2h4red.cc
endif
ifeq ($(CHEMISTRY), CH4RED)
    SRC += $(SRCDIR)user_chemical_mechanisms/ch4red.cc
endif
ifeq ($(CHEMISTRY), HEPTRED)
    SRC += $(SRCDIR)user_chemical_mechanisms/nHept_LiuHewsonPitsch_red.cc
endif
ifeq ($(CHEMISTRY), SIMPLEDLR)
    SRC += $(SRCDIR)user_chemical_mechanisms/simple_dlr.cc
endif
ifeq ($(CHEMISTRY), ABFRED)
    SRC += $(SRCDIR)user_chemical_mechanisms/abf_red62.cc
endif
ifeq ($(CHEMISTRY), ARAMCORED)
    SRC += $(SRCDIR)user_chemical_mechanisms/aramco_red86_nonstiff.cc
endif
ifeq ($(CHEMISTRY), ARAMCORED_STIFF)
    SRC += $(SRCDIR)user_chemical_mechanisms/aramco_red86_stiff.cc
endif

######################## OBJECT FILES ##########################

OBJS   = $(SRC:.cc=.o)
CVOBJS = $(CVSRC:.c=.o)

######################## BUILD TARGETS ##########################

default : $(PROG)

$(PROG) : $(OBJS) $(CVOBJS)
	$(LINK) $(OBJS) $(CVOBJS) -o $@ $(ext_libs)

%.o: %.cc
	$(COMPCC) $< -o $@
%.o: %.c
	$(COMPC)  $< -o $@

clean :
	rm -f $(OBJS) $(CVOBJS)
	rm -f ./test.x


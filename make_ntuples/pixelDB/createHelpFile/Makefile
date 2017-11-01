include $(ROOTSYS)/etc/Makefile.arch
UNDEFOPT      = dynamic_lookup

ROOTCFLAGS    = $(shell $(ROOTSYS)/bin/root-config --cflags)
#ROOTLIBS     += $(shell $(ROOTSYS)/bin/root-config --ldflags)$(shell $(ROOTSYS)/bin/root-config --libs)
ROOTLIBS      = $(shell $(ROOTSYS)/bin/root-config --libs)
ROOTGLIBS     = $(shell $(ROOTSYS)/bin/root-config --glibs)
ROOTLDFLAGS   += $(shell $(ROOTSYS)/bin/root-config --ldflags)$(shell $(ROOTSYS)/bin/root-config --libs)

RFCFLAGS = $(shell restframes-config --cxxflags)
RFLIBS   = $(shell restframes-config --libs)

CXX           = g++ -m64
CXXFLAGS      = -g -fPIC -Wno-deprecated -O -ansi -D_GNU_SOURCE -g -O2 -m64
LD            = g++ -m64
#LDFLAGS       = -g -m64
SOFLAGS       = -shared -m64

#PG da qui per macosx
#PG -----------------

ARCH         := $(shell $(ROOTSYS)/bin/root-config --arch)
PLATFORM     := $(shell $(ROOTSYS)/bin/root-config --platform)

NGLIBS         = $(ROOTGLIBS) 
NGLIBS        += -lMinuit -lEG -lg2c
gGLIBS          = $(filter-out -LNew, $(NGLIBS))

CXXFLAGS      += $(ROOTCFLAGS)
CXXFLAGS      += $(RFCLFAGS)
LIBS           = $(ROOTLIBS)

NGLIBS         = $(ROOTGLIBS)
NGLIBS        += $(RFLIBS)
NGLIBS        += -lMinuit -lEG 
#GLIBS          = $(filter-out -LNew, $(NGLIBS))
GLIBS           = $(filter-out -lfreetype, $(NGLIBS))
#ROOTLIBS  += $(shell echo ${GoodRunsListLib})

INCLUDEDIR       = ./include
SRCDIR           = ./src/
CXX	         += -I$(INCLUDEDIR) -I.
OUTLIB	         = ./lib/

.SUFFIXES: .cc,.C,.hh,.h
.PREFIXES: ./lib

all:  lib run_createHelpFile

run_createHelpFile: $(SRCDIR)loadFiles.C $(OUTLIB)Analysis.o
	$(CXX) $(CXXFLAGS) -o run_createHelpFile $(OUTLIB)*.o $(GLIBS) $ $<

lib:	$(OUTLIB)Analysis.o \
	$(OUTLIB)BranchAddress.o \

# analysis functions


$(OUTLIB)BranchAddress.o: $(SRCDIR)BranchAddress.C 
	$(CXX) $(CXXFLAGS) -c -I$(INCLUDEDIR) -o $(OUTLIB)BranchAddress.o $<


$(OUTLIB)Analysis.o: $(SRCDIR)Analysis.C $(OUTLIB)BranchAddress.o 
	$(CXX) $(CXXFLAGS) -c -I$(INCLUDEDIR) -o $(OUTLIB)Analysis.o $<

run_createHelpFile.clean:
	rm -f run_createHelpFile

clean:
	rm -f $(OUTLIB)*.o 
	rm -f run_createHelpFile


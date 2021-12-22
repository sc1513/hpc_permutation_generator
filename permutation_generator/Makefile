COMMON  = ../common

DBG      ?=
CXX      ?= g++
OMPFLAGS ?= -fopenmp
CXXFLAGS  = -O3 -I. -std=c++11 -I$(COMMON) $(DBG)

ifeq ($(CXX),icpc)
  CXXFLAGS += -xHost #-no-vec
  CXXFLAGS += -qopt-report=5
  CXXFLAGS += -Wunknown-pragmas -fopenmp # Disable warning about OpenMP pragma no defined.
endif

ifeq ($(CXX),g++)
  CXXFLAGS += -mtune=native -march=native
endif

EXEC = permutation_gen3

all: $(EXEC)

# Load common make options
include $(COMMON)/Makefile.common
LDFLAGS   = $(COMMON_LIBS)

permutation_gen3.o: permutation_gen3.cpp
	$(CXX) $(CXXFLAGS) $(OMPFLAGS) -c permutation_gen3.cpp

permutation_gen3: permutation_gen3.o $(COMMON_OBJS)
	$(CXX) $(CXXFLAGS) $(OMPFLAGS) -o permutation_gen3 permutation_gen3.o $(COMMON_OBJS) $(LDFLAGS)

clean: clean_common
	/bin/rm -fv $(EXEC) *.o *.optrpt *.d                                                 

COMMON	= ../common

#CXX	= icpc
CXX    ?= g++
CXXFLAGS= -O3 -I. -I$(COMMON)
LDFLAGS	= -lrt

ifeq ($(CXX),icpc)
CXXFLAGS += -xHost #-no-vec
CXXFLAGS += -qopt-report=5
CXXFLAGS += -D__ALIGNMENT=32
endif

ifeq ($(CXX),g++)
CXXFLAGS += -mtune=native
CXXFLAGS += -march=skylake-avx512
endif

ifneq ($(restrict),)
ifneq ($(restrict),0)
CXXFLAGS += -D__RESTRICT=restrict -restrict
endif
endif

ifneq ($(align),)
ifneq ($(align),0)
CXXFLAGS += -D__ALIGNMENT=$(align)
endif
endif

ifneq ($(dtype),)
ifneq ($(dtype),0)
CXXFLAGS += -D__DTYPE=$(dtype)
endif
endif

EXEC = permutation_gen

all: $(EXEC)

include $(COMMON)/Makefile.common

-include *.d

permutation_gen: permutation_gen.o $(COMMON_OBJS)
	$(CXX) $(CXXFLAGS) -o permutation_gen $^ $(LDFLAGS)

clean:
	/bin/rm -fv $(EXEC) *.o *.optrpt *.d

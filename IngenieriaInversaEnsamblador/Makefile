###############################################################################
# Makefile
###############################################################################

SHELL = /bin/bash # for ubuntu

###############################################################################

SRC = $(wildcard *.s *.c *.cc *.cpp)
EXE = $(basename $(SRC))
ATT = $(EXE:=.att)
LOG = $(EXE:=.log)

###############################################################################

ASFLAGS = -fno-omit-frame-pointer -g0 -m32 -nostartfiles
CFLAGS = -fno-omit-frame-pointer -g0 -m32 -O2 -pthread -Wall -Wl,--no-as-needed
CXXFLAGS = $(CFLAGS) -D _GLIBCXX_USE_SCHED_YIELD -std=c++0x

###############################################################################

default: $(EXE)

all: default $(ATT)

clean:
	$(RM) -rfv $(ATT) $(EXE) $(LOG) $(OBJ) core.* callgrind.out.* *~

strip: $(EXE)
	for i in $(EXE); do strip $$i; done

###############################################################################

%.att: %
	objdump -C -d $< > $@

%.log: %
	valgrind --callgrind-out-file=./$<.log --collect-jumps=yes --demangle=yes --dump-instr=yes --tool=callgrind --trace-jump=yes ./$<

k%: %.log
	kcachegrind $< &

###############################################################################

.PHONY: all clean default strip
.PRECIOUS: $(LOG)

###############################################################################


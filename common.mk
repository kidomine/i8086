APP=i8086
TST=tst86

LIBRARY=lib$(APP).a

CC=gcc
RM=rm
AR=ar

CCOPTS=-Wall -pedantic
RMOPTS=-fr
AROPTS=q
LNOPTS=-B static

H_INC_DIR=-I./include -I/usr/include -I/opt/local/include/
L_INC_DIR=-L./ -L/usr/lib/ -L/opt/local/lib/

ifndef DEBUG
    DEBUG=1
endif

ifndef PROFILE
    PROFILE=0
endif

ifndef COVERAGE
    COVERAGE=0
endif

ifeq ($(DEBUG), 1)
    CCOPTS+=-g -O0
    ifeq ($(PROFILE), 1)
        CCOPTS+=-fprofile-arcs -ftest-coverage
    endif
    
    ifeq ($(COVERAGE), 1)
        S_LIB_DEPS=-lgcov
    endif
else
    CCOPTS+=-O2
    ifeq ($(PROFILE), 1)
        $(warning "Ignoring PROFILE flag since we are not building for DEBUG...")
    endif
    
    ifeq ($(COVERAGE), 1)
        $(warning "Ignoring COVERAGE flag since we are not building for DEBUG...")
    endif
endif

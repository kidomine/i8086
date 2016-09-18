include common.mk
include cpu/module.mk
include ins/module.mk
include tests/module.mk

S_LIB_DEPS+=-l$(APP)
D_LIB_DEPS=-lcunit

CPU_OBJS=$(patsubst %.c,%.o,$(CPU_SRCS))
INS_OBJS=$(patsubst %.c,%.o,$(INS_SRCS))
MEM_OBJS=$(patsubst %.c,%.o,$(MEM_SRCS))
DEV_OBJS=$(patsubst %.c,%.o,$(DEV_SRCS))
TST_OBJS=$(patsubst %.c,%.o,$(TST_SRCS))

_GTMP=$(CPU_SRCS) $(INS_SRCS) $(MEM_SRCS) $(DEV_SRCS)
_GCDA=$(patsubst %.c, %.gcda, $(_GTMP))
_GCNO=$(patsubst %.c, %.gcno, $(_GTMP))

%.o: %.c
	$(CC) $(CCOPTS) $(H_INC_DIR) -c -o $@ $<

check:
	@echo "**** Program Info   ****"
	@echo "Application name: $(APP)"
	@echo "Test application: $(TST)"
	@echo "Library name    : $(LIBRARY)"
	@echo ""
	@echo "**** Build options  ****"
	@echo "DEBUG  : $(DEBUG)"
	@echo "PROFILE: $(PROFILE)"
	@echo "CCOPTS : $(CCOPTS)"
	@echo ""
	@echo "****  Core modules  ****"
	@echo "CPU SRCS: $(CPU_SRCS)"
	@echo "    OBJS: $(CPU_OBJS)"
	@echo "INS SRCS: $(INS_SRCS)"
	@echo "    OBJS: $(INS_OBJS)"
	@echo "DEV SRCS: $(DEV_SRCS)"
	@echo "    OBJS: $(DEV_OBJS)"
	@echo "MEM SRCS: $(MEM_SRCS)"
	@echo "    OBJS: $(MEM_OBJS)"
	@echo ""
	@echo "****  Test modules  ****"
	@echo "TST SRCS: $(TST_SRCS)"
	@echo "    OBJS: $(TST_OBJS)"


all: $(LIBRARY)

test: $(LIBRARY) $(TST_OBJS)
	$(CC) $(L_INC_DIR) $(D_LIB_DEPS) -o $(TST) $(TST_OBJS) \
	$(LIBRARY) -B static $(S_LIB_DEPS)
	
$(LIBRARY): $(CPU_OBJS) $(INS_OBJS) $(DEV_OBJS) $(MEM_OBJS)
	@echo "Creating core library..."
	$(AR) $(AROPTS) $@ $(CPU_OBJS) $(INS_OBJS) $(DEV_OBJS) $(MEM_OBJS)

clean:
	@echo "Cleaning coverage files..."
	$(RM) $(RMOPTS) $(_GCDA)
	$(RM) $(RMOPTS) $(_GCNO)

	@echo "Cleaning object files..."
	$(RM) $(RMOPTS) $(CPU_OBJS)
	$(RM) $(RMOPTS) $(INS_OBJS)
	$(RM) $(RMOPTS) $(DEV_OBJS)
	$(RM) $(RMOPTS) $(MEM_OBJS)
	$(RM) $(RMOPTS) $(TST_OBJS)
	
	@echo "Cleaning executable files..."
	$(RM) $(RMOPTS) $(LIBRARY)
	$(RM) $(RMOPTS) $(APP)
	$(RM) $(RMOPTS) $(TST)
	
	@echo "Cleanin miscellaneous files..."
	$(RM) $(RMOPTS) *.xml

.PHONY: all test clean

# Environs we need

HERE ?= $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
MPY ?= $(HERE)/micropython
SRC := $(HERE)/src
include $(MPY)/py/mkenv.mk

# Include py core make definitions.
include $(TOP)/py/py.mk
include $(TOP)/extmod/extmod.mk

# Set CFLAGS and libraries.
CFLAGS += -I$(HERE) -I$(BUILD) -I$(TOP) -I$(SRC)
LIBS += -lm

SRC_C = \
	$(SRC)/main.c \
	$(SRC)/mphalport.c \
	shared/readline/readline.c \
	shared/runtime/gchelper_generic.c \
	shared/runtime/pyexec.c \
	shared/runtime/stdout_helpers.c

# Define source files containung qstrs.
SRC_QSTR += shared/readline/readline.c shared/runtime/pyexec.c
# Define the required object files.
OBJ = $(PY_CORE_O) $(addprefix $(BUILD)/, $(SRC_C:.c=.o))

PROG ?= micropython
TARGET = $(BUILD)/$(PROG)

# Define the top-level target, the main firmware.
all: $(TARGET)

# build target
$TARGET: $(OBJ)
	$(ECHO) "LINK $@"
	$(Q)$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)
	$(Q)$(SIZE) $@

# Include remaining core make rules.
include $(TOP)/py/mkrules.mk


repl: $(TARGET)
	@stty raw opost -echo
	@$(BUILD)/micropython
	@stty -raw opost echo

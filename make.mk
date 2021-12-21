# compile gcc flags
CFLAGS += -Wextra
CFLAGS += -Wpedantic
CFLAGS += -Wundef
CFLAGS += -Wunused
CFLAGS += -Wshadow
CFLAGS += -Winline
CFLAGS += -Wpacked
# CFLAGS += -Wpadded
CFLAGS += -Wcast-qual
CFLAGS += -Wcast-align
CFLAGS += -Wattributes
CFLAGS += -Wconversion
CFLAGS += -Wfloat-equal
CFLAGS += -Wswitch-enum
CFLAGS += -Wswitch-default
CFLAGS += -Wdouble-promotion
# C defines
C_DEFS +=
# C includes
C_INCLUDES +=
# C sources
C_SOURCES += $(wildcard *.c)
# AS defines
AS_DEFS +=
# ASM sources
ASM_SOURCES +=
# link flags
LDFLAGS += -u_printf_float

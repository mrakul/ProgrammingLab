# Example Building

PROG_SUFFIX := my-code

SRC_DIR   := src
BUILD_DIR := build
BIN_DIR   := bin
LIB_DIR   := lib
INCLUDE_DIR  := /usr/local/include
LINK_LIB_DIR := /usr/local/lib
EXAMPLE_DIR := example

EXAMPLE_SRC := $(EXAMPLE_DIR)/my-code-example.c
EXAMPLE_OBJ := $(EXAMPLE_DIR)/my-code-example.o
EXAMPLE_BIN := $(BIN_DIR)/my-code-example

LIB_NAME := libmycode.a
LIB      := $(LIB_DIR)/$(LIB_NAME)

# Compiler features
CC     ?= gcc
CFLAGS ?= -Wall -Wextra -fPIC -O0 -std=c11 -MMD -MP -mavx2
CFLAGS += -I$(SRC_DIR)
CFLAGS += -I$(INCLUDE_DIR)/anotherproject/

# Additional CFLAGS from the command line
# Example: make EXTRA_CFLAGS=-DTLS_PROXY_DEBUG, etc.
CFLAGS += $(EXTRA_CFLAGS)

# Archiver
AR      	?= ar
ARFLAGS 	:= rcs

# All DPDK libraries (not used)
PKGCONF  ?= pkg-config
DPDKLIBS += $(shell $(PKGCONF) --static --libs libdpdk)

# Linker features: use only local include not to mix with global
LDFLAGS = -L$(shell pwd)/$(LIB_DIR)/
# LDFLAGS = -L$(LINK_LIB_DIR)

LDLIBS   += -lmycode
# DPDK flags
LDLIBS   += -lrte_eal -lrte_ring -lrte_mbuf -lrte_mempool
# LDLIBS   += -lrte_pmd_bond -lnuma -lrte_ethdev -lrte_hash -lrte_mbuf -lrte_mempool -lrte_ring -lrte_eal -lpcap

# Possible flags
# CFLAGS   -g -O2 -fPIC -DOS_LINUX -mavx2 -std=c11 -march=native -I/usr/local/include -include rte_config.h -march=native -I/usr/include/libnl3  -I${srcdir}/../rust/gen -I${srcdir}/../rust/dist -I../rust/gen
# CPPFLAGS -O2 -mavx2 -I/usr/include/dbus-1.0 -I/usr/lib/x86_64-linux-gnu/dbus-1.0/include -I/usr/include/libnl3  -fPIC 

# Objects lists
SRCS := $(wildcard $(SRC_DIR)/*.c)
HDRS := $(wildcard $(SRC_DIR)/*.h)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
DEPS := $(OBJS:.o=.d)

# all: $(LIB)
all: example $(LIB)

# Compile object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Build static library
library: $(LIB)

$(LIB): $(OBJS)
	@mkdir -p $(LIB_DIR)
	$(AR) $(ARFLAGS) $@ $^

# Build example
example: $(EXAMPLE_BIN) $(LIB)

$(EXAMPLE_OBJ): $(EXAMPLE_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

# Linking: use built static library in local /lib directory and global DPDK 
$(EXAMPLE_BIN): $(LIB) $(EXAMPLE_OBJ)
	mkdir -p $(BIN_DIR)
	$(CC) $(EXAMPLE_OBJ) $(LDFLAGS) $(LDLIBS) -o $@

# Installation 
install: install-headers install-library

# Install only external API
install-headers: $(HDRS)
	mkdir -p $(INCLUDE_DIR)/$(PROG_SUFFIX)
	cp $(SRC_DIR)/my-code.h $(INCLUDE_DIR)/$(PROG_SUFFIX)

install-library: $(LIB)
	mkdir -p $(LINK_LIB_DIR)
	cp $(LIB) $(LINK_LIB_DIR)

# Clean
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR) $(LIB_DIR) $(EXAMPLE_DIR)/*.o $(EXAMPLE_DIR)/*.d

clean-install:
	rm -rf $(INCLUDE_DIR)/$(PROG_SUFFIX)
	rm -rf $(LINK_LIB_DIR)/$(LIB_NAME)


# Dependendcies include
-include $(DEPS)

# .PHONY section
.PHONY: all clean install library install-headers install-library
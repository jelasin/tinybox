# Makefile for tinybox
export CC := gcc

debug := false
ifeq ($(debug), true)
export CFLAGS := -I$(PWD)/include -DDEBUG -g -Wall
else
export CFLAGS := -I$(PWD)/include -O2 -Wall
endif

static := false
ifeq ($(static), true)
export LDFLAGS := -static
else
export LDFLAGS :=
endif

export BUILD_DIR := $(PWD)/build
export SRC_DIR := $(PWD)/src

export TARGET := $(BUILD_DIR)/tinybox

.PHONY: all clean

all: $(TARGET)

$(TARGET):
	$(MAKE) -C $(SRC_DIR)

debug:
	$(MAKE) debug=true
	$(MAKE) all

static:
	$(MAKE) static=true
	$(MAKE) all

clean:
	$(foreach dir, $(SRC_DIR), $(MAKE) -C $(dir) clean;)

distclean: clean
	rm -rf $(BUILD_DIR)/*

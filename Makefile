CC ?= cc
CFLAGS ?= -O2 -march=native -pipe
COMMONFLAGS := -std=gnu11 $\
							 -Wall -Wextra -Wpedantic $\
							 -I. -Iinclude -Ideps/termbox2

# uncomment/comment to enable/disable
# PROCESS_HEADER_FILES := yes
PROCESSED_HEADER_FILES := $(if ${PROCESS_HEADER_FILES},$\
														$(subst .h,$\
														$(if $(findstring clang,${CC}),$\
															.h.pch,$\
															.h.gch),$\
														$(shell find include -name '*.h' -type f)))

define GET_OBJECT_FILES
$(patsubst src/%.c,$\
	build/%.o,$\
	$(shell find $(1) -name '*.c' -type f))
endef
COMMON_OBJECT_FILES := $(call GET_OBJECT_FILES,src/common src/deps)
TERMENU_OBJECT_FILES := $(call GET_OBJECT_FILES,src/termenu)
TERMENU_PATH_OBJECT_FILES := $(call GET_OBJECT_FILES,src/termenu_path)

TERMENU_REQUIREMENTS := ${COMMON_OBJECT_FILES} ${TERMENU_OBJECT_FILES}
TERMENU_PATH_REQUIREMENTS := ${COMMON_OBJECT_FILES} ${TERMENU_PATH_OBJECT_FILES}

OUTPUT_EXECUTABLES := termenu termenu_path

define COMPILE
${CC} -c $(1) ${CFLAGS} ${COMMONFLAGS} -o $(2)

endef
define LINK
${CC} $(1) ${CFLAGS} ${COMMONFLAGS} -o $(2)

endef
define REMOVE
$(if $(wildcard $(1)),$\
	$(info rm $(1))
	$(shell rm $(1)))

endef
define REMOVE_LIST
$(foreach ITEM,$\
	$(1),$\
	$(call REMOVE,${ITEM}))
endef

all: ${PROCESSED_HEADER_FILES} ${OUTPUT_EXECUTABLES} termenu_run

termenu: ${TERMENU_REQUIREMENTS}
	$(call LINK,${TERMENU_REQUIREMENTS},$@)

termenu_path: ${TERMENU_PATH_REQUIREMENTS}
	$(call LINK,${TERMENU_PATH_REQUIREMENTS},$@)

build/%.o: src/%.c
	$(call COMPILE,$<,$@)

%.gch: %
	$(call COMPILE,$<,$@)
%.pch: %
	$(call COMPILE,$<,$@)

clean:
	$(call REMOVE_LIST,${PROCESSED_HEADER_FILES})
	$(call REMOVE_LIST,${TERMENU_REQUIREMENTS})
	$(call REMOVE_LIST,${TERMENU_PATH_REQUIREMENTS})
	$(call REMOVE_LIST,${OUTPUT_EXECUTABLES})

.PHONY: all clean

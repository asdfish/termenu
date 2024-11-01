CC ?= gcc
C_FLAGS := -std=gnu11 $\
					 -Wall -Wextra -Wpedantic $\
					 -O2 -march=native -pipe $\
					 -Ideps/termbox2 -Iinclude

TERMENU_OBJECT_FILES := build/string_utils.o build/termbox_utils.o build/termenu.o $\
												build/termbox2.o
TERMENU_PATH_OBJECT_FILES := build/string_utils.o build/termenu_path.o

EXECUTABLES := termenu termenu_path termenu_run

INSTALL_DIRECTORY := /usr/local/bin

define REMOVE_LIST
	$(foreach ITEM,$\
		${1},$\
		$(if $(wildcard ${ITEM}),$\
			$(shell rm ${ITEM})))

endef

all: termenu termenu_path

build/%.o: src/%.c
	${CC} -c $< ${C_FLAGS} -o $@

termenu: ${TERMENU_OBJECT_FILES}
	${CC} ${TERMENU_OBJECT_FILES} -o termenu
	
termenu_path: ${TERMENU_PATH_OBJECT_FILES}
	${CC} ${TERMENU_PATH_OBJECT_FILES} -o termenu_path

clean:
	$(call REMOVE_LIST,$\
		${TERMENU_OBJECT_FILES})
	$(call REMOVE_LIST,$\
		${TERMENU_PATH_OBJECT_FILES})
ifneq (,$(wildcard termenu))
	rm termenu
endif
ifneq (,$(wildcard termenu_path))
	rm termenu_path
endif

install: all ${INSTALL_DIRECTORY}
	$(foreach EXECUTABLE,$\
		${EXECUTABLES},$\
		$(shell chmod +x ${EXECUTABLE} && cp ${EXECUTABLE} ${INSTALL_DIRECTORY}))

uninstall:
	$(foreach EXECUTABLE,$\
		${EXECUTABLES},$\
		$(if $(wildcard ${INSTALL_DIRECTORY}/${EXECUTABLE}),$\
			$(shell rm ${INSTALL_DIRECTORY}/${EXECUTABLE})))

.PHONY: all clean install uninstall

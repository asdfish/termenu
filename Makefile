CC ?= gcc
C_FLAGS := -std=gnu11 $\
					 -Wall -Wextra -Wpedantic $\
					 -O2 -march=native -pipe $\
					 -Ideps/termbox2 -Iinclude

DIRECTORIES := build deps
DEPENDENCIES := deps/termbox2

TERMENU_OBJECT_FILES := build/string_utils.o build/termbox_utils.o build/termenu.o $\
												build/termbox2.o
TERMENU_PATH_OBJECT_FILES := build/string_utils.o build/termenu_path.o

INSTALL_DIRECTORY := /usr/local/bin

all: ${DIRECTORIES} ${DEPENDENCIES} termenu termenu_path

${DIRECTORIES}:
	-mkdir ${DIRECTORIES}

deps/termbox2: deps
	git -C deps clone https://github.com/termbox/termbox2 --depth=1

${TERMENU_OBJECT_FILES} ${TERMENU_PATH_OBJECT_FILES}: build/%.o :src/%.c
	${CC} -c $< ${C_FLAGS} -o $@

termenu: ${TERMENU_OBJECT_FILES}
	${CC} ${TERMENU_OBJECT_FILES} -o termenu
	
termenu_path: ${TERMENU_PATH_OBJECT_FILES}
	${CC} ${TERMENU_PATH_OBJECT_FILES} -o termenu_path

clean:
	-rm -rf ${DIRECTORIES}
	-rm -f termenu
	-rm -f termenu_path

install: all ${INSTALL_DIRECTORY}
	-chmod +x ./termenu_run
	-cp -f termenu* ${INSTALL_DIRECTORY}

uninstall:
	-rm ${INSTALL_DIRECTORY}/termenu
	-rm ${INSTALL_DIRECTORY}/termenu_path
	-rm ${INSTALL_DIRECTORY}/termenu_run

.PHONY: all clean install uninstall

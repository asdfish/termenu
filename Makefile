CC ?= gcc

STANDARD := -std=gnu11

INCLUDE_FLAGS := -Ideps/termbox2 -Iinclude

OPTIMIZATION_FLAGS := -O2 -march=native -pipe

TERMENU_LINK_FLAGS := -Ldeps/termbox2 -ltermbox
TERMENU_OBJECT_FILES := build/string_utils.c.o build/termbox_utils.c.o build/termenu.c.o

TERMENU_PATH_OBJECT_FILES := build/string_utils.c.o build/termenu_path.c.o

INSTALL_DIRECTORY := /usr/local/bin

define COMPILE_FILE
	${CC} -c ${STANDARD} $(1) ${INCLUDE_FLAGS} ${OPTIMIZATION_FLAGS} -o build/$(notdir $(1)).o

endef

all: termenu termenu_path

build:
	mkdir build

build/string_utils.c.o: include/string_utils.h src/string_utils.c
	$(call COMPILE_FILE,src/string_utils.c)

build/termbox_utils.c.o: include/termbox_utils.h src/termbox_utils.c
	$(call COMPILE_FILE,src/termbox_utils.c)

build/termenu.c.o: config.h include/string_utils.h include/termbox_utils.h src/termenu.c
	$(call COMPILE_FILE,src/termenu.c)

build/termenu_path.c.o: src/termenu_path.c
	$(call COMPILE_FILE,src/termenu_path.c)

deps:
	mkdir deps

deps/termbox2: deps
	git -C deps clone https://github.com/termbox/termbox2 --depth=1 --branch=v2.0.0
	make -C deps/termbox2 lib
	rm deps/termbox2/*.so deps/termbox2/*.o

termenu: deps/termbox2 build ${TERMENU_OBJECT_FILES}
	${CC} ${TERMENU_OBJECT_FILES} ${TERMENU_LINK_FLAGS} -o termenu

termenu_path: build ${TERMENU_PATH_OBJECT_FILES}
	${CC} ${TERMENU_PATH_OBJECT_FILES} -o termenu_path

install: all ${INSTALL_DIRECTORY}
	chmod +x termenu_run
	cp -f termenu ${INSTALL_DIRECTORY}
	cp -f termenu_path ${INSTALL_DIRECTORY}
	cp -f termenu_run ${INSTALL_DIRECTORY}

uninstall:
ifneq (, $(wildcard ${INSTALL_DIRECTORY}/termenu))
	rm -f ${INSTALL_DIRECTORY}/termenu
endif
ifneq (, $(wildcard ${INSTALL_DIRECTORY}/termenu_path))
	rm -f ${INSTALL_DIRECTORY}/termenu_path
endif
ifneq (, $(wildcard ${INSTALL_DIRECTORY}/termenu_run))
	rm -f ${INSTALL_DIRECTORY}/termenu_run
endif

termbox2: dependencies_prep
ifeq (, $(wildcard deps/termbox2))
	git -C deps clone https://github.com/termbox/termbox2 --depth=1 --branch=v2.0.0
	make -C deps/termbox2
	rm deps/termbox2/*.o deps/termbox2/*.so
endif

clean:
ifneq (, $(wildcard termenu))
	rm -f termenu
endif
ifneq (, $(wildcard build))
	rm -rf build
endif
ifneq (, $(wildcard deps))
	rm -rf deps
endif

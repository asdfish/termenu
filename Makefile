CC ?= gcc

C_STANDARD := -std=gnu11

TERMENU_SOURCE_FILES :=
TERMENU_HEADER_FILES :=
TERMENU_LINK_FLAGS :=
TERMENU_INCLUDE_FLAGS :=
TERMENU_OBJECT_FILES :=

TERMENU_PATH_SOURCE_FILES :=
TERMENU_PATH_OBJECT_FILES :=

DEBUG_FLAGS := -Wall -Wextra -Wpedantic
OPTIMIZATION_FLAGS := -Og

# ${1} source file
# ${2} extra flags
define COMPILE_FILE
	${CC} -c ${C_STANDARD} ${1} ${2} ${DEBUG_FLAGS} ${OPTIMIZATION_FLAGS} -o build/$(notdir ${1}).o 

endef

all: termbox2 termenu termenu_path

termenu: build_prep ${TERMENU_SOURCE_FILES} ${TERMENU_HEADER_FILES}
	$(foreach SOURCE_FILE,$\
		${TERMENU_SOURCE_FILES},$\
		$(call COMPILE_FILE,${SOURCE_FILE},${TERMENU_LINK_FLAGS},${TERMENU_INCLUDE_FLAGS})$\
	)

termenu_path: build_prep ${TERMENU_PATH_SOURCE_FILES}
	$(foreach SOURCE_FILE,$\
		${TERMENU_PATH_SOURCE_FILES},$\
		$(call COMPILE_FILE,${SOURCE_FILE},)$\
	)

build_prep:
ifeq (, $(wildcard build))
	mkdir build
endif

dependencies_prep:
ifeq (, $(wildcard deps))
	mkdir deps
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

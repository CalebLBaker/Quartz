CC := g++

SOURCES := $(shell find src -name '*.cpp')
OBJECTS := $(patsubst src/%.cpp, build/%.o, $(SOURCES))
DBGOBJECTS := $(patsubst src/%.cpp, build/debug/%.o, $(SOURCES))
INCLUDEPATH := -Isrc

all: blc

build:
	mkdir build
	mkdir build/scan
	mkdir build/ast
	mkdir build/codeGen

build/debug: build
	mkdir build/debug
	mkdir build/debug/scan
	mkdir build/debug/ast
	mkdir build/debug/codeGen

build/debug/scan/%.o: src/scan/%.cpp build/debug
	${CC} -g -Isrc -Isrc/scan -c $< -o $@

build/debug/ast/%.o: src/ast/%.cpp build/debug
	${CC} -g -Isrc -Isrc/ast -c $< -o $@

build/debug/codeGen/%.o: src/codeGen/%.cpp build/debug
	${CC} -g -Isrc -Isrc/codeGen -c $< -o $@

build/debug/%.o: src/%.cpp build/debug
	${CC} -g -Isrc -c $< -o $@

blc.dbg: $(DBGOBJECTS)
	${CC} -g $^ -o $@

build/scan/%.o: src/scan/%.cpp build
	${CC} -Isrc -Isrc/scan -O3 -c $< -o $@

build/ast/%.o: src/ast/%.cpp build
	${CC} -Isrc -Isrc/ast -O3 -c $< -o $@

build/codeGen/%.o: src/codeGen/%.cpp build
	${CC} -Isrc -Isrc/codeGen -O3 -c $< -o $@

build/%.o: src/%.cpp build
	${CC} -Isrc -O3 -c $< -o $@

blc: $(OBJECTS)
	${CC} $^ -o $@

clean:
	rm -rf build
	rm -f blc
	rm -f blc.dbg
	rm -f out.s
	rm -f out.elf


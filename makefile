CC = gcc
TARGET = build/dist/main

ifeq ($(OS),Windows_NT)
	MAKE_GENERATOR = "MinGW Makefiles"
else
	MAKE_GENERATOR = "Unix Makefiles"
endif

all: clean $(TARGET) run

$(TARGET): main.c
	cmake -B build -S . -G $(MAKE_GENERATOR)
	cmake --build build

run:
	./$(TARGET)

clean:
	-@cmake -E remove_directory build

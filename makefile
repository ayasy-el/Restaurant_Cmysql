CC = gcc
RESTO = build/dist/restoran # restoran target
KARYAWAN = build/dist/karyawan   # karyawan target

ifeq ($(OS),Windows_NT)
	MAKE_GENERATOR = "MinGW Makefiles"
else
	MAKE_GENERATOR = "Unix Makefiles"
endif

all: clean r k

r: clean src/restoran/main.c
	cmake -B build -DBUILD_RESTORAN=ON -DBUILD_KARYAWAN=OFF
	cmake --build build --target restoran

k: clean src/karyawan/main.c
	cmake -B build -DBUILD_RESTORAN=OFF -DBUILD_KARYAWAN=ON
	cmake --build build --target karyawan

run-r:
	./$(RESTO)

run-k:
	./$(KARYAWAN)

clean:
	-@cmake -E remove_directory build

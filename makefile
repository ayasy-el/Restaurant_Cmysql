CC = gcc
BUILD_DIR = build
DIST_DIR = $(BUILD_DIR)/dist
TARGET = $(DIST_DIR)/main

ifeq ($(OS),Windows_NT)
    CFLAGS = -I./include/ -L./lib/ -lmariadb
    RM = rmdir /s /q 
    MKDIR = if not exist $(subst /,\,$1) mkdir $(subst /,\,$1)
else
    CFLAGS = -I/usr/include/mysql -L/usr/lib/mysql -lmysqlclient
    RM = rm -rf
    MKDIR = mkdir -p
endif

all: $(TARGET) run

$(TARGET): $(BUILD_DIR)/main.o $(BUILD_DIR)/tambah_pelanggan.o $(BUILD_DIR)/tambah_pesanan.o $(BUILD_DIR)/lihat_riwayat.o $(BUILD_DIR)/database.o | $(DIST_DIR)
	$(CC) -o $(TARGET) $(BUILD_DIR)/main.o $(BUILD_DIR)/tambah_pelanggan.o $(BUILD_DIR)/tambah_pesanan.o $(BUILD_DIR)/lihat_riwayat.o $(BUILD_DIR)/database.o $(CFLAGS)
ifeq ($(OS),Windows_NT)
	copy .\lib\libmariadb.dll .\build\dist\libmariadb.dll
endif

run:
	./$(TARGET)

$(BUILD_DIR):
ifeq ($(OS),Windows_NT)
	$(call MKDIR,$(DIST_DIR))
else
	$(MKDIR) $(DIST_DIR)
endif

$(BUILD_DIR)/main.o: main.c | $(BUILD_DIR)
	$(CC) -c main.c $(CFLAGS) -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/tambah_pelanggan.o: tambah_pelanggan.c | $(BUILD_DIR)
	$(CC) -c tambah_pelanggan.c $(CFLAGS) -o $(BUILD_DIR)/tambah_pelanggan.o

$(BUILD_DIR)/tambah_pesanan.o: tambah_pesanan.c | $(BUILD_DIR)
	$(CC) -c tambah_pesanan.c $(CFLAGS) -o $(BUILD_DIR)/tambah_pesanan.o

$(BUILD_DIR)/lihat_riwayat.o: lihat_riwayat.c | $(BUILD_DIR)
	$(CC) -c lihat_riwayat.c $(CFLAGS) -o $(BUILD_DIR)/lihat_riwayat.o

$(BUILD_DIR)/database.o: database.c | $(BUILD_DIR)
	$(CC) -c database.c $(CFLAGS) -o $(BUILD_DIR)/database.o

clean:
	-@$(RM) $(BUILD_DIR)

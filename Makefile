.PHONY: all clean

CC=g++

SRC=src

TARGET=build
TARGET_NAME=task

all: build test
	@echo 'Done build & test. Put executable in $(TARGET)/$(TARGET_NAME)'

build: $(SRC)
	mkdir -p $(TARGET)
	$(CC) $(SRC)/*.cpp -o $(TARGET)/$(TARGET_NAME)

test: build
	$(TARGET)/$(TARGET_NAME) test/test.txt > $(TARGET)/o_test.txt
	test "`diff test/o_test.txt build/o_test.txt`" = ""

clean:
	rm -rf $(TARGET)

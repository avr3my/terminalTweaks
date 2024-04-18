CC=g++
CFLAGS=-std=c++11 -Wall
TARGET=a.out
SOURCES=*.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	@echo Compiling $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)
	@echo Done

clean:
	@if [ -e $(TARGET) ]; then \
		rm -f $(TARGET); \
		echo Removed $(TARGET); \
	fi


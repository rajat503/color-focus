CC = g++
CFLAGS  = -g
TARGET = focus

 all: $(TARGET).cpp
	 			$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp `pkg-config opencv --cflags --libs`

C=g++
TARGET=P1
OBJS=P1.o scanner.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

P1.o:
	$(CC) -c P1.cpp

scanner.o:
	$(CC) -c scanner.cpp


clean:
	rm -f *.o $(TARGET)

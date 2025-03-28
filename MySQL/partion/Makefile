CC = gcc
TARGET = program
OBJS = DBmain.o DBselect.o

all: $(TARGET)

DBselect.o: DBselect.c
	$(CC) -c $^ `mysql_config --include`

DBmain.o: DBmain.c
	$(CC) -c $^ `mysql_config --include`

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ `mysql_config --libs`

clean:
	rm -rf *.o *.gch $(TARGET)

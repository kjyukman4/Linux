CC = gcc

TARGET = connect1
OBJS = connect1.o

INC = `mysql_config --include` 
LIBS = `mysql_config --libs`

$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(LIBS)

$(OBJS): connect1.c
	$(CC) -c  $(INC) connect1.c

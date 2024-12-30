CC = gcc
TARGET = RentCar
OBJS =	DBfunction.o Customer.o Car.o Rent.o RentCar.o

all: $(TARGET)

DBfunction.o: DBfunction.c
	$(CC) -c $^ `mysql_config --include`

Customer.o: Customer.c
	$(CC) -c $^ `mysql_config --include`

Car.o: Car.c
	$(CC) -c $^ `mysql_config --include`

Rent.o: Rent.c
	$(CC) -c $^ `mysql_config --include`

RentCar.o: RentCar.c
	$(CC) -c $^ `mysql_config --include`

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ `mysql_config --libs`

clean:
	rm -rf *.o *.gch $(TARGET)

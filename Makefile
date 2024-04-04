CC = gcc
OBJS = Pharmacy.o Stock.o Medicine.o Product.o LinkedList.o main.o Address.o \
  Employee.o Person.o Customer.o Order.o Prescription.o Date.o general.o
EXEC = demo
DEBUG = -g
CFLAGS = -Wall -Werror $(DEBUG)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@

Address.o: Address.c Address.h general.h
Customer.o: Customer.c Customer.h general.h Person.h
Date.o: Date.c Date.h
Employee.o: Employee.c Employee.h general.h Person.h
LinkedList.o: LinkedList.c LinkedList.h general.h
Medicine.o: Medicine.c Medicine.h Product.h general.h Date.h
Order.o: Order.c Order.h Product.h general.h Medicine.h Date.h Stock.h \
  LinkedList.h Prescription.h Customer.h Person.h Employee.h
Person.o: Person.c Person.h general.h
Pharmacy.o: Pharmacy.c Pharmacy.h Address.h general.h Stock.h Product.h \
  Medicine.h Date.h LinkedList.h Employee.h Person.h Customer.h Order.h \
  Prescription.h
Prescription.o: Prescription.c Prescription.h general.h Date.h Medicine.h \
  Product.h Customer.h Person.h Stock.h LinkedList.h
Product.o: Product.c Product.h general.h
Stock.o: Stock.c Stock.h Product.h general.h Medicine.h Date.h \
  LinkedList.h
general.o: general.c general.h
main.o: main.c Pharmacy.h Address.h general.h Stock.h Product.h \
  Medicine.h Date.h LinkedList.h Employee.h Person.h Customer.h Order.h \
  Prescription.h



clean:
	rm -f $(OBJS) $(EXEC)
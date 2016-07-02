OBJS := client.o send_message.o

default: $(OBJS)
	gcc $(OBJS) -o run -lpthread

client.o: client.c client.h
	gcc -c client.c -o client.o

send_message.o: send_message.c send_message.h
	gcc -c send_message.c -o send_message.o

clean:
	-rm *.o run

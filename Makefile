CC=gcc
CFLAGS=-Wall -std=c99 -O3

wrdmttns: wrdmttns.o dic.o stats.o auxiliar.o grafo.o queue.o dijkstra.o
	$(CC) $(CFLAGS) -o wrdmttns wrdmttns.o dic.o stats.o auxiliar.o grafo.o queue.o dijkstra.o

wrdmttns.o: wrdmttns.c wrdmttns.h
	$(CC) -c $(CFLAGS) wrdmttns.c

dic.o: dic.c wrdmttns.h
	$(CC) -c $(CFLAGS) dic.c

stats.o: stats.c wrdmttns.h
	$(CC) -c $(CFLAGS) stats.c

auxiliar.o: auxiliar.c wrdmttns.h
	$(CC) -c $(CFLAGS) auxiliar.c

grafo.o: grafo.c wrdmttns.h
	$(CC) -c $(CFLAGS) grafo.c

queue.o: queue.c wrdmttns.h
	$(CC) -c $(CFLAGS) queue.c

dijkstra.o: dijkstra.c wrdmttns.h
	$(CC) -c $(CFLAGS) dijkstra.c


clean::
	rm -f *.o core a.out wrdmttns *~


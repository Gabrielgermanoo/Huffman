huff:

test: queue/queue.c huffman/huffman.c
	gcc util/util.c queue/queue.c huffman/huffman.c test/test.c   -lcunit -o teste

clean:

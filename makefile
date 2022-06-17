huff: util/util.c queue/queue.c huffman/huffman.c decompress/decompress.c compress/compress.c main.c
	gcc util/util.c queue/queue.c huffman/huffman.c decompress/decompress.c compress/compress.c main.c -o main

test: queue/queue.c huffman/huffman.c
	gcc util/util.c queue/queue.c huffman/huffman.c test/test.c -lcunit -o teste

clean:
	rm main

clean_test:
	rm teste
huff: util/util.c queue/queue.c huffman/huffman.c decompress/decompress.c compress/compress.c main.c
	gcc util/util.c queue/queue.c huffman/huffman.c decompress/decompress.c compress/compress.c main.c -o main

test: util/util.c queue/queue.c huffman/huffman.c 
	gcc util/util.c test/test.c queue/queue.c huffman/huffman.c -lcunit -o testar

clean:
	rm main

clean_test:
	rm testar
huff: util/util.c queue/queue.c huffman/huffman.c decompress/decompress.c compress/compress.c main.c
	gcc util/util.c queue/queue.c huffman/huffman.c decompress/decompress.c compress/compress.c main.c -o main

tests: tad_test/tad_test.c
	gcc test/test.c tad_test/tad_test.c -lcunit -o teste

clean:
	rm main

clean_test:
	rm teste
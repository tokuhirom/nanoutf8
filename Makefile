test:
	$(CC) -g -std=c99 t/test_nanoutf8.c -o t/test_nanoutf8.t
	prove -v ./t/test_nanoutf8.t

clean:
	rm -rf t/test_nanoutf8.t

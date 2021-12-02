CC=g++

main:
	$(CC) *.cpp -o  main

clean:
	rm **.o

wipe:
	rm main
raid: source.c
	gcc -o raid source.c

test: raid
	./raid < test1.txt

clean:
	rm -f raid

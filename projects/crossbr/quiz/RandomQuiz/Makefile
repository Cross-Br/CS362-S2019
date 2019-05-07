compile: testme.c
	gcc -o quiz2 testme.c -coverage -fpic -lm
	./quiz2

test: quiz2
	gcov testme.c -b
	
clean:
	rm -f quiz2 testme.c.gcov testme.gcda testme.gcno
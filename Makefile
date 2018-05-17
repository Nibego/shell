
shellnb: shellnb.a
	gcc -L. -o shellOS mainShell.c -lshellnb
shellnb.a: shellnb.o
	ar -cvr libshellnb.a mainShell.o
shellnb.o: 
	gcc -c mainShell.c
clean:
	rm -f shellOS lib*.a *.o
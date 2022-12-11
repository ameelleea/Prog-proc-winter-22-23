#Makefile del programma per verificare le congetture di Beal, Collatz e Cramer.

verifica_congetture: verifica_congetture.c Makefile
	gcc -ansi -Wall -O verifica_congetture.c -o verifica_congetture

pulisci:
	rm -f verifica_congetture.o

pulisci_tutto: 
	rm -f verifica_congetture.o verifica_congetture

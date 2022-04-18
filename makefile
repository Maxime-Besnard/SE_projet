all: acquisition validation terminal

acquisition:		acquisition.o lectureEcriture.o message.o
	gcc -Wall acquisition.c lectureEcriture.o message.o -o acquisition

validation: 		validation.o lectureEcriture.o message.o
	gcc -Wall validation.c lectureEcriture.o message.o -o validation

terminal: 			terminal.o lectureEcriture.o message.o
	gcc -Wall terminal.c lectureEcriture.o message.o -o terminal

lectureEcriture.o:	lectureEcriture.c
	gcc -Wall lectureEcriture.c -c

message.o:			message.c
	gcc -Wall message.c -c

clean:
	rm *.o 
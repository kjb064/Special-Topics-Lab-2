# Make file to create Generate Report application

generateReport: generateReport.o calculateGross.o calculateFica.o newPage.o
	gcc -o generateReport src/generateReport.o src/calculateGross.o src/calculateFica.o src/newPage.o

# chain rules

generateReport.o: src/generateReport.c
	gcc -c -o src/generateReport.o src/generateReport.c

calculateGross.o: src/calculateGross.c
	gcc -c -o src/calculateGross.o src/calculateGross.c

calculateFica.o: src/calculateFica.c
	gcc -c -o src/calculateFica.o src/calculateFica.c

newPage.o: src/newPage.c
	gcc -c -o src/newPage.o src/newPage.c 

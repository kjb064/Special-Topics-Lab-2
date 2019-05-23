/*
Lab 2: Control Breaks
Author: Kevin Barry
Last Updated: 3/19/18
   -- Processed the correct data
   -- Removed unnecessary code  
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>	
#define size 10

float calculateGross(float hoursWld, float payrate);
void newPage(FILE *outFile, float *Pgross, float *Pfica, float *Pnet, int *pageKt, float *Rgross, float *Rfica, float *Rnet, int *lineKt);
float calculateFica(int Flimit, float Frate, float ytd, float gross);
int compareDept(char dept[size], char deptSave[size]);

int main(){
    setlocale(LC_NUMERIC, "");

    int Flimit;			// Obtain FICA limit and rate from text file
    float Frate;
    FILE *ficaFile = fopen("fica.txt", "r");
    if(ficaFile == NULL){
        printf("File containing FICA limit and FICA rate not found. Program terminating.");
        exit(1);
    }
    fscanf(ficaFile, "%d%f", &Flimit, &Frate); 
    fclose(ficaFile);

    FILE *inFile;
    char inFileName[20];

    FILE *outFile;
    char outFileName[20];

    printf("Enter the name of the input file: ");
    scanf("%s", inFileName);
    inFile = fopen(inFileName, "r");
    if(inFile == NULL){
        printf("Input file does not exist. Program terminating.");
        exit(1);
    }

    printf("Enter the name of the output file: ");
    scanf("%s", outFileName);
    
    char choice;
    if((outFile = fopen(outFileName, "r")) != NULL){
        printf("Output file already exists. Overwrite? (Y/N): ");
        scanf(" %c", &choice);
        if(choice == 'n' || choice == 'N'){
          printf("Terminating to prevent overwrite.");
          exit(1);
      }
    }  
    outFile = fopen(outFileName, "w");
    printf("\n");

    int EmpNum;
    char givenName[size];
    char surname[size];
    char dept[size], deptSave[size]; 			
    float ytd, payrate, hoursWkd, gross, ficaTax, net, newYtd;

    // Print cover page
    fprintf(outFile,"\n\n\n\n\n\n\n\n\n\t\t\t\t\tACME Sports Inc.\n\t\t\t\"We are the best, you use the best!\"" );

    int lineKt = 0;
    int pageKt = 1;
    fprintf(outFile, "\f\n\n\t\t\t\t\tACME\n\n");	
    fprintf(outFile, "Emp#\t   Name\t\tDept.\t New YTD\tGross\t     FICA\t    Net\n\n");

    int MaxLines = 4; 
    int numProcessed = 0;    

    // Set page totals
    float Pgross, Pfica, Pnet;		
    Pgross = Pfica = Pnet = 0.0;  

    // Set report totals
    float Rgross, Rfica, Rnet;
    Rgross = Rfica = Rnet = 0.0;

    // Set dept. totals
    float Dgross, Dfica, Dnet;
    Dgross = Dfica = Dnet = 0.0;

    while((fscanf(inFile, "%d%s%s%s%f%f%f", &EmpNum, givenName, surname, dept, &ytd, &payrate, &hoursWkd)) != EOF){
	
	if(numProcessed == 0){
	    for(int i = 0; i < size; i++)
		deptSave[i] = dept[i];	  // Read first record, save dept.
	}

	if((compareDept(dept, deptSave)) == 0){
	    fprintf(outFile, "\t\tDepartment Totals:\t\t%'10.2f%'10.2f%'10.2f\n\n", Dgross, Dfica, Dnet);
            for(int i = 0; i < size; i++)
	        deptSave[i] = dept[i];    // Save next dept.

	    Dgross = Dfica = Dnet = 0.0;
        }

	if(lineKt == MaxLines)
           newPage(outFile, &Pgross, &Pfica, &Pnet, &pageKt, &Rgross, &Rfica, &Rnet, &lineKt);
        
        gross = calculateGross(hoursWkd, payrate);
        ficaTax = calculateFica(Flimit, Frate, ytd, gross);
        net = gross - ficaTax;
        newYtd = ytd + gross;
        fprintf(outFile, "%d%10s%10s%6s\t%'10.2f%'10.2f%'10.2f%'10.2f\n", EmpNum, givenName, surname, dept, newYtd, gross, ficaTax, net);       

        lineKt++;
        Pgross += gross;
        Pfica += ficaTax;
        Pnet += net;

	Dgross += gross;
	Dfica += ficaTax;
        Dnet += net;

        numProcessed++;
    } // end while

    fprintf(outFile, "\t\tDepartment Totals:\t\t%'10.2f%'10.2f%'10.2f", Dgross, Dfica, Dnet);
 
    fprintf(outFile, "\n\nPage Totals:\t\t\t\t\t$%'8.2f  $%'8.2f  $%'8.2f", Pgross, Pfica, Pnet);
    fprintf(outFile, "\n\n\t\t\t\t\t\t\t\t\t\tPage %d", pageKt); 
    Rgross += Pgross;
    Rnet += Pnet;
    Rfica += Pfica;
    pageKt++;

    // Report Summary
    fprintf(outFile, "\f\t\t\t\t\tReport Summary\n\n");
    fprintf(outFile, "Records processed: %d\n", numProcessed);
    fprintf(outFile, "Total Gross: $%'8.2f\n", Rgross);
    fprintf(outFile, "Total Net:   $%'8.2f\n", Rnet);
    fprintf(outFile, "Total FICA:  $ %'8.2f\n", Rfica);
    fprintf(outFile, "\n\n\t\t\t\t\t\t\t\t\tPage %d", pageKt);    
  
    printf("\nResults printed to %s.\n", outFileName);       

    // Close files
    fclose(inFile);
    fclose(outFile);

}

int compareDept(char dept[size], char deptSave[size]){
    int i = 0; 
    while(deptSave[i] == dept[i] && deptSave != '\0'){
 	if(deptSave[i] != dept[i])
	    return 0;
	i++;
    }
    return i;
}



// File newPage.c

#include <stdio.h>
#include <locale.h>

void newPage(FILE *outFile, float *Pgross, float *Pfica, float *Pnet, int *pageKt, float *Rgross, float *Rfica, float *Rnet, int *lineKt){
   setlocale(LC_NUMERIC, "");

// Finish current page
    fprintf(outFile, "\n\nPage Totals:\t\t\t\t\t$%'8.2f  $%'8.2f  $%'8.2f", *Pgross, *Pfica, *Pnet);
    fprintf(outFile, "\n\n\t\t\t\t\t\t\t\t\t\tPage %d", *pageKt);

    *Rgross += *Pgross;
    *Rfica += *Pfica;
    *Rnet += *Pnet;

// Start next page
    (*pageKt)++;
    fprintf(outFile, "\f\n\n\t\t\t\t\tACME\n\n");
    fprintf(outFile, "Emp#\t   Name\t\tDept.\t New YTD\tGross\t     FICA\t    Net\n\n");
    *lineKt = 0;
    *Pgross = *Pfica = *Pnet = 0.0;
}

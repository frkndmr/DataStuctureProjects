
#include "circuit.h"
#include <stdio.h>
#include <stdlib.h>

using namespace std;




int main(int argc, char *argv[]){
    circuit Circuit;
    Circuit.create();

    char grp;
    double val;

    FILE *fptr;
	fptr = fopen(argv[1],"r");
	fscanf(fptr,"%c",&grp);
    fgetc(fptr);
    fscanf(fptr,"%lf",&val);

    if(val>0)
        Circuit.add_resistor(grp,val);
    
    else if(val<0)
        Circuit.remove_resistor(grp,val);
    while (!feof (fptr)){
    	
    	if(fgetc(fptr)=='\n'){
    		fscanf(fptr,"%c",&grp);
    		fgetc(fptr);
    		fscanf(fptr,"%lf",&val);
            if(val>0)
                Circuit.add_resistor(grp,val);
            else if(val<0)
                Circuit.remove_resistor(grp,val);
            else if(val == 0)
                Circuit.circuit_info();

		}
    }
    fclose(fptr);
    Circuit.clear();



    return 0;
}

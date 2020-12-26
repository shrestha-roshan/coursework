
#include <stdio.h>

void main(){
	int A =2;
	int D = 4;
	int C = 5;
	
	int B=A+C;
	int Btemp = B;
	
	Btemp=C+D;
	
	int Ctemp = C;
	C=Btemp + D;
	
	printf("B => %d \n", B );
	printf("C => %d\n", C);
	
}

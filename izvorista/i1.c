#include <stdio.h>
#include <stdlib.h>

void generiraj_niz(int nmin)
{
	int i;
	for (i = 0; i < nmin; ++i)
		printf("y");
}

int main()
{
	generiraj_niz(1000000);
	return 0;
}

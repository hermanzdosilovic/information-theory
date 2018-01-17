#include <stdio.h>
#include <stdlib.h>

void generiraj_niz(int nmin)
{
	int i;
	for (i = 0; i < nmin; ++i)
	{
		if (i % 2 == 0)
		{
			printf("x");
		}
		else
		{
			printf("y");
		}
	}
}

int main()
{
	generiraj_niz(100000);
	return 0;
}

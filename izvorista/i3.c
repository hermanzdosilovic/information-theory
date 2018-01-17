#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void generiraj_niz(int nmin)
{
	int i;

	srand(clock());
	for (i = 0; i < nmin; ++i)
	{
		/*
			randomness, random stuff ... where everything suddenly dissolves into arbitrariness ...
			http://www.youtube.com/watch?v=T1Ogwa76yQo
		*/
		if (rand() % 2 == 0)
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
	generiraj_niz(10000000);
	return 0;
}

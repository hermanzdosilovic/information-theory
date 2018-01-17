#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void generiraj_niz(int nmin)
{
	int i, stanje;

	srand(clock());

	stanje = 0;
	i = 0;
	while (i < nmin)
	{
		if (stanje == 0)
		{
			printf("xyxy");
			i = i + 4;

			if (rand() % 3 == 0)
			{
				stanje = 1;
			}
			else
			{
				stanje = 2;
			}
		}
		else if (stanje == 1)
		{
			printf("xxxxyyyy");
			i = i + 8;

			stanje = rand() % 3;
		}
		else
		{
			printf("yyyyxxxx");
			i = i + 8;

			if (rand() % 3 == 0)
			{
				stanje = 1;
			}
			else
			{
				stanje = 0;
			}
		}
	}
}

int main()
{
	generiraj_niz(1000000);
	return 0;
}

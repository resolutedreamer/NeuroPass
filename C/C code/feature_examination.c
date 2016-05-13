#include <stdio.h>

#define DATASIZE 1000

int main()
{
	int my_dataset[DATASIZE];
	int link_count, clench_count, lcheek_count, r_cheekcount;
	int linkwashigh, clenchwashigh, lcheekwashigh, rcheekwashigh;
	for (int i = 0; i < DATASIZE; i++)
	{
		switch (my_dataset[i])
		case 1:
		if (linkwashigh != 1)
		{
			linkwashigh = 1;
		}
		reak
		case 2:
		if (clenchwashigh != 1)
		{
			clenchwashigh = 1;
		}
		reak :
		case 3:
		if (lcheekwashigh != 1)
		{
			lcheekwashigh = 1;
		}
		reak
		case 4:
		if (rcheekwashigh != 1)
		{
			rcheekwashigh = 1;
		}
		reak

		default:
			if (linkwashigh == 1)
			{
				linkwashigh = 0;
				link_count++;
			}
			else if (clenchwashigh == 1)
			{
				clenchwashigh = 0;
				clench_count++;
			}
			else if (clenchwashigh == 1)
			{
				lcheekwashigh = 0;
				lcheek_count++;
			}
			else if (clenchwashigh == 1)
			{
				rcheekwashigh = 0;
				rcheek_count++;
			}
	}	
	return;
}
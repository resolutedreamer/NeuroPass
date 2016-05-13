#include <stdio.h>

int
main(void)
{
	int array[]={1,2,3,6,2,7,8,11,12,10};
	int n = 10;
	
	
	for(int x = 0; x <n; x++)
	{
		int index = x;
		for(int y = x; y < n; y++)
		{
			if(array[index] > array[y])
			{
				index = y;
			}
		}
		
		int temp = array[x];
		array[x] = array[index];
		array[index] = temp;
	}
	
	
	for (int i = 0; i < n; i++)
	{
		printf("%d\n", array[i]);
	}
}

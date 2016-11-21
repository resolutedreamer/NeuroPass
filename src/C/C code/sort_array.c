void sort_array(char* array)
{
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
}
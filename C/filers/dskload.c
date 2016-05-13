float AC_EEG_data[14][10000] = {{0}};
int x, y;


void loaddata(char* input)
{
	// for(x = 0; x < 100; x ++) {
		// for(y = 0; y < 100; y ++)
			// AC_EEG_data[x][y] = 0;
	// }
	
	// get the input file, which at this point is a text file containing AC_EEG_data
	printf('Importing AC_EEG_data.csv.')
	FILE* fp = fopen(input,'r');
	if (fp == NULL)
	{
		printf('Error. File open failed.')
		return;
	}
	fscanf(fp, "%f", AC_EEG_data);
	for(x = 0; x < 100; x ++) {
		for(y = 0; y < 100; y ++)
			printf("%f", AC_EEG_data[x][y]);
	}
	
	fclose(fp);
	printf('AC_EEG_data.csv successfully imported into AC_EEG_data array.')
}
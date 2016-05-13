#include <stdio.h>

float AC_EEG_data[14][1000] = {{0}};
int x, y;


void loaddata(char * input)
{
	// get the input file, which at this point is a text file containing AC_EEG_data
	FILE* fp = fopen(input,"r");
	printf("Importing AC_EEG_data.csv.\n");
	if (fp == NULL)
	{
		printf("Error. File open failed.\n");
		return;
	}
	fscanf(fp, "%f", AC_EEG_data);
	for(x = 0; x < 100; x ++) {
		for(y = 0; y < 100; y ++)
			printf("%f\n", AC_EEG_data[x][y]);
	}
	
	fclose(fp);
	printf("AC_EEG_data.csv successfully imported into AC_EEG_data array.\n");
}

int main()
{
	printf("Hello World.\n");
	loaddata("C:/CCStudio_v3.1/MyProjects/filers/anthony.csv");
	return;
}

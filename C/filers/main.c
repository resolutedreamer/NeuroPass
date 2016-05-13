#include <stdio.h>
#define LENGTH 10000

// initialize 2D float array
float temp[16];
float data[LENGTH][14];

void loaddata(char * input)
{
	//initialize all variables
	char c;
	int i = 0, j = 0;
	
	//#pragma data(buffer,".EXT_RAM")

	//open the file
	FILE* csv = fopen(input, "r");

	// check if file was opened
	if (!csv)
		printf("File could not be opened.\n");

	// skip over first line	
	do
	c = fgetc(csv);
	while (c != '\n');

	//store one row, for LENGTH number of rows
	for (i = 0; i < LENGTH; i++)
	{

		// get first 16 columns
		for (j = 0; j < 16; j++)
		{
			// add double to array
			fscanf(csv, "%f", &temp[j]);

			// skip comma
			fgetc(csv);
		}

		// copy correct columns to new array
 		for (j = 0; j < 14; j++)
		{
			data[i][j] = temp[j + 2];
		}

		// skip rest of line
		do
		c = fgetc(csv);
		while (c != '\n');
	}

	for (i = 0; i < LENGTH; i++)
	{
		for (j = 0; j < 14; j++)
		{
			printf("%f, ", data[i][j]);
			if (j == 13)
				printf("\n");
		}
	}
	printf("Data successfully imported into data array.\n");
}



int main()
{
	printf("Hello World.\n");
	loaddata("C:/CCStudio_v3.1/MyProjects/filers/s1-24eyeslrl-27.11.13.01.57.01.CSV");
	printf("Done.\n");
	return 0;
}

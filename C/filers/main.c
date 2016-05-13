#include <stdio.h>
#include <stdlib.h>

float** loaddata(char* filename, int numof_lines)
{
	int i = 0, j = 0;
	char c;

	// temp array for fscanf
	float temp[16];

	float** data;
	float* ptemp;

	// counters the number of line loop events. Should be same a lines variable
	int counter = 0;

	FILE* csv = fopen(filename, "r");

	// check if file was opened
	if (!csv)
		printf("File could not be opened.\n");
	else
		printf("File opened succesfully.\n");


	// skip over first line
	do
	c = fgetc(csv);
	while (c != '\n');	

	// 1st dimension of final data array. Return this pointer to access the array!
	data = (float**)malloc(14 * sizeof(float*));
	if (data == NULL)
		printf("Malloc Failed! temp = %f .\n",data);
	else
		printf("Data is located at: %f .\n",data);
	// create 2nd dimension of final float array on heap	
	for (i = 0; i < 14; i++)
	{	
		ptemp = NULL;
		ptemp = (float *)malloc(numof_lines * sizeof(float));
		if (ptemp == NULL)
			printf("Malloc Failed! ptemp = %f .\n", ptemp);
		else
			printf("ptemp = %d. \n",ptemp);
		data[i] = ptemp;
	}


	// not really necessay
	ptemp = NULL;

	// iterate by line
	for (i = 0; i < numof_lines; i++)
	{

		// get first 16 columns
		for (j = 0; j < 16; j++)
		{
			// add float to temp array
			fscanf(csv, "%f", &temp[j]);

			// skip comma
			fgetc(csv);
		}

		// copy correct temp to final array
		for (j = 0; j < 14; j++)
		{
			data[j][i] = temp[j + 2];
		}

		counter++;

		// skip rest of line
		do
		{
			c = fgetc(csv);

			// check if EOF
			if (feof(csv))
				break;

		} while (c != '\n');

		printf("Line %d is completed.\n", counter);
	}

	// print out final 2D array
	for (i = 0; i < 14; i++)
	{
		for (j = 0; j < 6; j++)
		{
			printf("%f, ", data[i][j]);
			if (j == (6 -1) )
				printf("\n");
		}
	}
	printf("import complete!\n");
	fclose(csv);
	return data;
}

int countlines(char* filename)
{
	char c;
	int numof_lines = 0;
	FILE* csv = fopen(filename, "r");

	// check if file was opened
	if (!csv)
		printf("File could not be opened.\n");
	else
		printf("File opened succesfully.\n");
	printf("Counting lines.\n");

	// counter number of lines in file
	do
	{
		c = fgetc(csv);
		if (c == '\n')
		{
			++numof_lines;
		}
	} while (c != EOF);

	printf("Done counting %d lines.\n", numof_lines);
	fclose(csv);
	return numof_lines;
}

int main(void)
{
	float** rawdata = NULL;
	int rows;
	char* filename = "C:/CCStudio_v3.1/MyProjects/s1-24eyesshort.CSV";

	rows = countlines(filename);
	rawdata = loaddata(filename,rows);
	if (rawdata == NULL)
		printf("rawdata is still null!\n",rawdata);
	else
		printf("rawdata is located at: %f .\n",rawdata);
	printf("import complete!\n");

	return 0;

}








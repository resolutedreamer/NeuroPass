//loop_intr.c loop program using interrupts
#include "DSK6416_AIC23.h"	        //codec support
Uint32 fs=DSK6416_AIC23_FREQ_8KHZ;	//set sampling rate
#define DSK6416_AIC23_INPUT_MIC 0x0015
#define DSK6416_AIC23_INPUT_LINE 0x0011
Uint16 inputsource=DSK6416_AIC23_INPUT_LINE; // select input
#include <stdio.h>
#define LENGTH 5000

// initialize 2D float array
float temp[16];
#pragma DATA_SECTION(temp,".EXT_RAM")
float data[LENGTH][14];
#pragma DATA_SECTION(data,".EXT_RAM")


interrupt void c_int11()         //interrupt service routine
{
   output_sample(0);   //output data
   return;
}

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

void main()
{
	printf("Hello World.\n");
	loaddata("C:/CCStudio_v3.1/MyProjects/filers/s1-24eyeslrl-27.11.13.01.57.01.CSV");
	printf("Done.\n");
}
 

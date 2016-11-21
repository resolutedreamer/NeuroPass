// csv_importer.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <stdio.h>
#define LENGTH 100

int _tmain(int argc, _TCHAR* argv[])
{
	FILE* csv = fopen("C:/Data/AC_EEG_data.CSV", "r");

	// check if file was opened
	if (!csv)
		printf("File could not be opened.\n");

	// skip over first line
	char c;
	do
	c = fgetc(csv);
	while (c != '\n');

	// initialize 2D float array
	double temp[16];
	double data[LENGTH][14];

	for (int i = 0; i < LENGTH; i++)
	{

		// get first 16 columns
		for (int j = 0; j < 16; j++)
		{
			// add double to array
			fscanf(csv, "%lf", &temp[j]);

			// skip comma
			fgetc(csv);
		}

		// copy correct columns to new array
		for (int j = 0; j < 14; j++)
		{
			data[i][j] = temp[j + 2];
		}

		// skip rest of line
		do
		c = fgetc(csv);
		while (c != '\n');
	}

	for (int i = 0; i < LENGTH; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			printf("%f, ", data[i][j]);
			if (j == 13)
				printf("\n");
		}
	}

	return 0;
}


// csv_importer.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


using namespace std;

double raw_import[1050000], less_raw_import[1050000], AC_EEG_data[14][75000];
int x, y;

void loaddata(char * input)
{
	int most_digits = 20, bigcounter = 0, doneflag = 0;
	char hold;
	char temp[20];
	//char *idx = (char*)malloc(2);
	int i = 0;
	double current_number = 0;

	// get the input file, which at this point is a text file containing AC_EEG_data
	FILE* fp = fopen(input, "r");


	printf("Importing AC_EEG_data.csv.\n");
	if (fp == NULL)
	{
		printf("Error. File open failed.\n");
		return;
	}
	//fscanf(fp, "%f", AC_EEG_data);
	//fscanf(fp, "%d,%c", &x, &c);

	//stores characters into temp char array until you try to store a comma
	while (1)
	{
		for (i = 0; i < most_digits; i++)
		{
			hold = fgetc(fp);			
			if (hold == '\n')
			{
				temp[i] = '\0';
				break;
			}
			else if (isspace(hold))
				continue;
			else if (hold == ',')
			{
				temp[i] = '\0';
				break;
			}
			else if (hold == EOF)
			{
				doneflag = 1;
				break;
			}
			//is not a space, a new line, or a comma
			temp[i] = hold;
		}
		if (doneflag == 1)
		{
			break;
		}
		else
		{
			current_number = atof(temp); ///////////// From TA: The pointer idx is used to store the first two values of temp
			raw_import[bigcounter] = current_number;
			//printf("%f\n", current_number);
			bigcounter++;
		}
	}

	printf("done reading in raw_import, now beginning to take the giant row and making it into a 36 by %d matrix.\n", bigcounter);

	for (int i = 2; i < bigcounter; (i=i+22))
	{
		for (y = i; y < (y + 14); y++)
		{
			less_raw_import[y] = raw_import[y];
			//printf("%d\n", y);
		}
		printf("%d\n", i);
	}

	printf("taking 36 by %d matrix, turning it into 14 by %d matrix.\n", bigcounter, bigcounter);

	for (i = 0; i < (bigcounter/36*14); i++)
	{
		AC_EEG_data[i/14][i%14] = less_raw_import[i];
	}


	fclose(fp);
	printf("AC_EEG_data.csv successfully imported into AC_EEG_data array.\n");
}


int _tmain(int argc, _TCHAR* argv[])
{
	printf("We Begin Now.\n");
	loaddata("C:/Data/AC_EEG_data.CSV");
	printf("Done.\n");
	return 0;
}


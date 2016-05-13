#include <stdio.h>
#define LENGTH 500
#define PI 3.14159265359

// initialize 2D float array
float importeddata[14][LENGTH];

void loaddata(char * input)
{
	//initialize all variables
	char c;
	int i = 0, j = 0;
	float temp[16];
	//#pragma data(buffer,".EXT_RAM")

	//open the file
	FILE* csv = fopen(input, "r");

	// check if file was opened
	if (!csv)
		printf("File could not be opened.\n");
	else
		printf("File opened succesfully.\n");

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
			importeddata[j][i] = temp[j + 2];
		}

		// skip rest of line
		do
		c = fgetc(csv);
		while (c != '\n');
		printf("Stored row %d.\n",i);
	}

	printf("Data imported into data array.\n");
}

// iirsos.c generic iir filter using cascaded second order sections
void IIRSOS(float* filterthis,float* temp,int Fs, int cutoff,int highorlowpass)	 //low is 0 high is 1
{	
	#define NUM_SECTIONS 1
	float b[NUM_SECTIONS][3]={ {0.0, 0.0, 0.0} };
	float a[NUM_SECTIONS][2]={ {0.0, 0.0} };
	float w[NUM_SECTIONS][2] = {0};
	float RC;
	float T;
	int i = 0;

	RC = 1/(2*PI*cutoff);
	T = 1/Fs;
	if (highorlowpass == 0)
	{
		b[NUM_SECTIONS][0] = 1 / (1 + (2*RC)/T) ;
		b[NUM_SECTIONS][1] = 1 / (1 + (2*RC)/T) ;
		a[NUM_SECTIONS][1] = (1 - (2*RC)/T ) / (1 + (2*RC)/T ) ;
	}
	else if (highorlowpass == 1)
	{
		b[NUM_SECTIONS][0] = 1* ( 1 / (1 + T/(2*RC)) ) ;
		b[NUM_SECTIONS][1] = -1* ( 1 / (1 + T/(2*RC)) ) ;
		a[NUM_SECTIONS][1] = -1*(1 - (2*RC)/T ) / (1 + (2*RC)/T ) ;
	}

	for(i = 0; i < LENGTH ; i++)
	{	
		int section;   // index for section number
		float input;   // input to each section
		float wn,yn;   // intermediate and output values in each stage
		input = filterthis[i];
		for (section=0 ; section< NUM_SECTIONS ; section++)
		{
			wn = input - a[section][0]*w[section][0] - a[section][1]*w[section][1];
			yn = b[section][0]*wn + b[section][1]*w[section][0] + b[section][2]*w[section][1];
			//printf("%f,%f\n",wn,yn);
			w[section][1] = w[section][0];
			w[section][0] = wn;
			input = yn;              // output of current section will be input to next
		}
		temp[i] = yn;
	}
	
}



float* filterdata(float * filterthis)
{
	float* temp = (float*)malloc(sizeof(float)*LENGTH);
	IIRSOS(filterthis,temp,128,1000,1);	
	return temp;
}



int main()
{
	float* filteredchannel;
	//float* filteredchannel2;
	printf("Hello World.\n");
	loaddata("C:/CCStudio_v3.1/MyProjects/filers/s1-24eyeslrl-27.11.13.01.57.01.CSV");
	filteredchannel = filterdata(importeddata[0]);
	//filteredchannel2 = filterdata(importeddata[1]);
	printf("Filtered Channel is stored starting at address: %d\n",filteredchannel);
	printf("Done.\n");
	return 0;
}


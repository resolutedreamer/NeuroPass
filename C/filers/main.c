#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159265359
#define NUM_SECTIONS 1

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
	printf("Import completed! Returning address of imported data back to main.\n");
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

// iirsos.c generic iir filter using cascaded second order sections
void IIRSOS(float* filterthis,int sig_length, float* temp,int Fs, int cutoff,int highorlowpass)	 //low is 0 high is 1
{
	float b[3]={0.0, 0.0, 0.0};
	float a[2]={0.0, 0.0};
	float w[2]={0.0};
	float RC;
	float T;
	int i = 0;

	RC = 1.0/(2*PI*cutoff);
	T = 1.0/Fs;
	if (highorlowpass == 0)
	{
		printf("Running Yu Yu's LPF!\n");
		b[0] = 1.0/(1.0+(2.0*RC)/T) ;
		b[1] = 1.0/(1.0+(2.0*RC)/T) ;
		a[1] = (1.0-(2.0*RC)/T)/(1.0+(2*RC)/T);
	}
	else if (highorlowpass == 1)
	{
		printf("Running Yu Yu's HPF!\n");
		b[0] = 1.0*(1.0/(1.0+T/(2.0*RC)));
		b[1] = -1.0*(1.0/(1.0+T/(2.0*RC)));
		a[1] = -1.0*(1.0-(2.0*RC)/T )/(1.0+(2.0*RC)/T);
	}

	for(i = 0; i < sig_length ; i++)
	{	
		float input;   // input to each section
		float wn,yn;   // intermediate and output values in each stage
		input = filterthis[i];

		wn = input - a[0]*w[0] - a[1]*w[1];
		yn = b[0]*wn + b[1]*w[0] + b[2]*w[1];
		//printf("%f,%f\n",wn,yn);
		w[1] = w[0];
		w[0] = wn;
		input = yn;              // output of current section will be input to next

		temp[i] = yn;
	}
	printf("");
}



float* filterdata(float * signal, int sig_length)
{
	float* temp = (float*)malloc(sizeof(float)*sig_length);
	IIRSOS(signal, sig_length, temp,128.0,1000.0,1);	
	return temp;
}


float** dcoffsetbegone(float* datamatrix[], int numof_rows)
{	
	int i, r;
	float back[14];
	int	IIR_TC = 256;
	printf("Running the Emotiv HPF!\n");
	//copy the first row of data into 'back'
	for (i = 0; i < 14; i++)
		back[i] = datamatrix[i][0];


	for (i = 0; i < 14; i++)
		datamatrix[i][0] = 0;


	for (r = 1; r < numof_rows; r++)
	{
		float tempback[14];
		for (i = 0; i < 14; i++)
			tempback[i] = back[i] * (IIR_TC - 1);
		for (i = 0; i < 14; i++)
			back[i] = (tempback[i] + datamatrix[i][r]) / IIR_TC;
		for (i = 0; i < 14; i++)
			datamatrix[i][r] = datamatrix[i][r] - back[i];

	}
	printf("Emotiv HPF Filter Completed!\n");
	return datamatrix;
}






float findmean(float* signal, int signal_length)
{
	int i = 0;
	float sum = 0, mean = 0;

	for(i = 0; i < signal_length; i++)
		sum = sum + signal[i];
	mean = sum / (float)signal_length;

	printf ("The mean is %f!\n", mean);
	return mean;
}









float findstd(float* signal, int signal_length)
{
	int i = 0, j = 0;
	float * array = (float*)malloc(sizeof(float) * signal_length);
	float sum = 0, mean = 0, variance = 0, std = 0;
	mean = findmean(signal, signal_length);

	for (j = 0; j < signal_length; j++)
	{
		// the array named 'array' stores the value of (signal - mean)^2
	    array[i] = (float)pow((signal[i] - mean),2);
	    sum += array[i];
	    i++;
	}	 
	
	//variance is the mean of the array named 'array'
	variance = sum / signal_length;

	// lastly, std is the sqrt of the variance
	std = (float)sqrt(variance);
	printf ("The standard deviation is %f!\n", std);
	return std;
}

float calcthreshold(float* signal, int rows)
{
	float mean,std,threshold;
	//find the mean of the signal
	mean = findmean(signal, rows);
	//find the std of the signal
	std = findstd(signal, rows);
	//return the sum of the mean and the std
	threshold = (mean + std);
	printf ("The thresholding value is %f!\n", threshold);
	return threshold;
}

void fpeaks(float* signal, int signal_length, float threshold, float** usefulpks, int ** usefullocs, int * usefulpkcnt)
//returns the number of useful peaks
{
	int i = 0, k = 0;
	float * peaks = NULL;
	int pksfound = 0;
	int * locs = NULL;

	float * thresholdedpeaks = NULL;
	int thresholdedpksfound = 0;
	int * thresholdedlocs = NULL;

	float * finalpeaks = NULL;
	int finalpksfound = 0;
	int * finallocs = NULL;

	// allocate enough room for signal/3 peaks
	peaks = (float*) malloc(sizeof(float) * (int)signal_length/3);
	// allocate enough room for signal/3 peak locations
	locs = (int*) malloc(sizeof(int) * (int)signal_length/3);

	
	// this loop finds bad peaks
	for (i = 0; i < signal_length - 1 ; i++)
	{
		if (i == 0)
			continue;
		if (signal[i] > signal[i - 1] && signal[i] > signal[i + 1])
		{
			// good canidate
			peaks[k] = signal[i];
			locs[k] = i;
			k = k + 1;
		}
	}
	pksfound = k;

	// allocate enough room for pksfound peaks
	thresholdedpeaks = (float*) malloc(sizeof(float) * pksfound);
	// allocate enough room for pksfound peak locations
	thresholdedlocs = (int*) malloc(sizeof(int) * pksfound);

	// this loop gets rid of the peaks that are under the threshold
	k = 0;
	for (i = 0; i < pksfound; i++)
	{
		if (peaks[i] < threshold)
			continue;
		else
		{
			thresholdedpeaks[k] = peaks[i];
			thresholdedlocs[k] = locs[i];
			k = k + 1;
		}
	}
	thresholdedpksfound = k;

	free(peaks);
	free(locs);

	finalpeaks = (float*)malloc(sizeof(float) * thresholdedpksfound);
	finallocs = (int*)malloc(sizeof(int) * thresholdedpksfound);
	finalpksfound = thresholdedpksfound;

	for (i = 0; i < finalpksfound; i++)
	{
		finalpeaks[i] = thresholdedpeaks[i];
		finallocs[i] = thresholdedlocs[i];
	}

	free(thresholdedpeaks);
	free(thresholdedlocs);

	*usefulpks = finalpeaks;
	*usefullocs = finallocs;
	*usefulpkcnt = finalpksfound;
}

int main(void)
{
	//pointers for importing data
	float** rawdata = NULL;
	float* F7 = NULL;
	int sig_length = 0;
	
	//pointers for intermediary storage
	int* realpklocs = NULL;
	float* realpkheights = NULL;
	int realpkcnt = 0;
	float threshold = 0;

	//location of data file to be imported
	char* filename = "C:/CCStudio_v3.1/MyProjects/s1-24eyes.CSV";
	printf("Welcome to NeuroPass!\n\n");
	//calculate the rows in the csv file
	sig_length = countlines(filename) - 1;

	//import the csv file
	rawdata = loaddata(filename,sig_length);

	//verify succesful import of csv file
	if (rawdata == NULL)
		printf("Import Failed. rawdata is still null!\n");
	else
		printf("Import Successful! rawdata is located at: %x .\n",rawdata);

	//remove the raw data's dc offset
	dcoffsetbegone(rawdata,sig_length);
	
	//run desired channel through yuyu's highpass filter
	F7 = filterdata(rawdata[1],sig_length);
	
	//calculate the threhold
	threshold = calcthreshold(F7,sig_length);

	//find the peaks of the channel of choice
	fpeaks(F7, sig_length, threshold, &realpkheights, &realpklocs, &realpkcnt);
	
	//knowing the set of thresholded peaks, quantize
	//the positive and negative peaks into a sequence
	

	//using the sequence, identify the lrl


	//remainder is blinks???


	//return the final password sequence

	printf("wheeeeeee");
	return 0;

}








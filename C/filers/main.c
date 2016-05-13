#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159265359
#define NUM_SECTIONS 1
#define POS_VAL 2	// POS peaks have value 2
#define NEG_VAL 3	// NEG peaks have value 3

typedef struct Events
{
	int loc;
	int logical_value;
} Events;


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

void fpeaks(float* signal, int signal_length, float threshold, float** usefulpks, int ** usefullocs, int * usefulpkcnt, int posorneg)
//returns the number of useful peaks
{
	int i = 0, k = 0;
	float* temp;
	
	float * peaks = NULL;
	int * locs = NULL;
	int pksfound = 0;

	float * thresholdedpeaks = NULL;
	int * thresholdedlocs = NULL;
	int thresholdedpksfound = 0;

	float * finalpeaks = NULL;
	int * finallocs = NULL;
	int finalpksfound = 0;
	
	//copy either +signal or -signal into temp depending on user input
	temp = (float*)malloc(sizeof(float)*signal_length);
	if (posorneg == 0)
	{
		for(i = 0; i < signal_length; i++)
		{
			temp[i] = signal[i];
		}
	}
	else if (posorneg == 1)
	{
		for(i = 0; i < signal_length; i++)
		{
			temp[i] = -1.0*signal[i];
		}
	}

	// allocate enough room for signal/3 peaks
	peaks = (float*) malloc(sizeof(float) * (int)signal_length/3);
	// allocate enough room for signal/3 peak locations
	locs = (int*) malloc(sizeof(int) * (int)signal_length/3);

	
	// this loop finds bad peaks
	for (i = 0; i < signal_length - 1 ; i++)
	{
		if (i == 0)
			continue;
		if (temp[i] > temp[i - 1] && temp[i] > temp[i + 1])
		{
			// good candidate
			peaks[k] = temp[i];
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
	
	free(temp);
}

void sort_and_combine(Events* positive_events, int positivepkcnt,Events* negative_events, int negativepkcnt, Events* total_events)
{	
	int i = 0, j = 0, temp = 0, tempval = 0;
	//pos = 3 neg = 2
	for (i = 0; i < positivepkcnt + negativepkcnt; i++)
	{
		if (i < positivepkcnt)
		{
			total_events[i].loc = positive_events[i].loc;
			total_events[i].logical_value = positive_events[i].logical_value;
		}
		else if (i >= positivepkcnt)
		{
			total_events[i].loc = negative_events[i-positivepkcnt].loc;
			total_events[i].logical_value = negative_events[i-positivepkcnt].logical_value;
		}
	}
	
	for(i = 0; i < positivepkcnt + negativepkcnt; i++)
	{
		for(j = i; j < positivepkcnt + negativepkcnt; j++)
		{
			if(total_events[i].loc > total_events[j].loc)
			{
				temp = total_events[i].loc;
				tempval = total_events[i].logical_value;
				
				total_events[i].loc = total_events[j].loc;
				total_events[i].logical_value = total_events[j].logical_value;
				
				total_events[j].loc = temp;
				total_events[j].logical_value = tempval;
			}
		}
	}
	
	
	
	//total_events = sortrows(total_events,1);
	// now we have all the peaks that were thresholded (sorted in time), STORED IN all_peaks
}

Events* get_total_events(int* positivepklocs, int* negativepklocs, int positivepkcnt, int negativepkcnt)
{
	int i
	;
	Events* positive_events = (Events*)malloc(positivepkcnt*sizeof(Events));
	Events* negative_events = (Events*)malloc(negativepkcnt*sizeof(Events));	
	Events* total_events = (Events*)malloc((positivepkcnt+negativepkcnt)*sizeof(Events));	
	
	for (i = 0; i < positivepkcnt; i++)
	{
		positive_events[i].loc = positivepklocs[i];
		positive_events[i].logical_value = POS_VAL;
	}

	for (i = 0; i < negativepkcnt; i++)
	{
		negative_events[i].loc = negativepklocs[i];
		negative_events[i].logical_value = NEG_VAL;
	}
	sort_and_combine(positive_events,positivepkcnt, negative_events,negativepkcnt, total_events);
	free(positive_events);
	free(negative_events);
	return total_events;
}

Events* remove_excess_peaks(Events* total_events, int total_events_cnt)
{
	// now we have peaks, where same type of peak (e.g. ++)
	//must be separated by min_peak_distance, STORED IN masked_peaks

	Events* masked_peaks = (Events*)malloc(sizeof(Events)*total_events_cnt);
	Events* masked_peaks_to_be_returned;
	int min_peak_distance = 200;
	int i = 0, k = 0;
	for (i = 0; i < total_events_cnt; i++)
	{
		if (i == 0)
		{
			masked_peaks[k].loc = total_events[i].loc;
			masked_peaks[k].logical_value = total_events[i].logical_value;
			k = k+1;
			continue;
		}
		
		if (total_events[i].logical_value == masked_peaks[k-1].logical_value && total_events[i].loc < masked_peaks[k-1].loc+min_peak_distance)
			continue;
		else
		{
			masked_peaks[k].loc = total_events[i].loc;
			masked_peaks[k].logical_value = total_events[i].logical_value;
			k = k+1;
		}
	}
	
	masked_peaks_to_be_returned = (Events*)malloc(sizeof(Events)*k);
	//masked_peaks_to_be_returned = masked_peaks;
	for (i = 0; i < total_events_cnt; i++)
	{
		masked_peaks_to_be_returned[i].loc = masked_peaks[i].loc;
		masked_peaks_to_be_returned[i].logical_value = masked_peaks[i].logical_value;
	}
	free(masked_peaks);
	return masked_peaks_to_be_returned;
}



int main(void)
{
	//pointers for importing data
	float** rawdata = NULL;
	float* F7 = NULL;
	int sig_length = 0;
	
	//pointers for intermediary storage	
	float* positivepkheights = NULL;
	int* positivepklocs = NULL;
	int positivepkcnt = 0;	
	
	float* negativepkheights = NULL;
	int* negativepklocs = NULL;
	int negativepkcnt = 0;
	
	float threshold = 0;

	Events* total_events;
	Events* masked_peaks;
	int totalpkcnt = 0;

	//location of data file to be imported
	char* filename = "C:/CCStudio_v3.1/MyProjects/s1-24eyes.CSV";
	printf("Welcome to NeuroPass!\n\n");
	//calculate the rows in the csv file
	sig_length = countlines(filename) - 1;

	//import the csv file
	rawdata = loaddata(filename,sig_length);

	//verify successful import of csv file
	if (rawdata == NULL)
		printf("Import Failed. rawdata is still null!\n");
	else
		printf("Import Successful! rawdata is located at: %x .\n",rawdata);

	//remove the raw data's dc offset
	dcoffsetbegone(rawdata,sig_length);
	
	//run desired channel through yuyu's highpass filter
	F7 = filterdata(rawdata[1],sig_length);
	
	//calculate the threshold
	threshold = calcthreshold(F7,sig_length);

	//find the positive peaks of the channel of choice
	fpeaks(F7, sig_length, threshold, &positivepkheights, &positivepklocs, &positivepkcnt,0);
	//find the negative peaks of the channel of choice
	fpeaks(F7, sig_length, threshold, &negativepkheights, &negativepklocs, &negativepkcnt,1);
	totalpkcnt = positivepkcnt + negativepkcnt;
	
	//knowing the set of threshold-ed peaks, quantize
	//the positive and negative peaks into a sequence
	total_events = get_total_events(positivepklocs, negativepklocs, positivepkcnt, negativepkcnt);
	masked_peaks = remove_excess_peaks(total_events, totalpkcnt);

	//using the sequence, identify the lrl


	//remainder is blinks???


	//return the final password sequence
	

	printf("wheeeeeeee!\n");
	free(rawdata);
	free(F7);
	free(positivepkheights);
	free(positivepklocs);
	free(negativepkheights);
	free(negativepklocs);
	free(total_events);
	return 0;

}








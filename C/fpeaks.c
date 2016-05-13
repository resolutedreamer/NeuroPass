#include <stdio.h>
#include <cstdlib>

void fpeaks(float* signal, int signal_length, int threshold, int min_distance, float* usefulpks, int * usefullocs, int *usefulpkcnt)
//returns the number of useful peaks
{
	int i = 0, k = 0;
	float * peaks;
	// allocate enough room for 30 peaks
	peaks = (float*) malloc(sizeof(float) * 30);
	int * locs;
	// allocate enough room for 30 peak locations
	locs = (int*) malloc(sizeof(int) * 30);

	int pksfound = 0;
	// this loop finds peaks
	for (i = 0; i < signal_length -1; i++)
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

	// this loop gets rid of the peaks that are under the threshold
	k = 0;
	for (i = 0; i < pksfound; i++)
	{
		if (peaks[i] < threshold)
			continue;
		else
		{
			usefulpks[k] = peaks[i];
			usefullocs[k] = locs[i];
			k = k + 1;
		}
	}
	*usefulpkcnt = k;
}

int main ()
{
	float signal[10] = {1, 3, 2, 4, 2, 5, 6, 9 ,7 , 6};
	int signal_length = 10;
	int threshold = 2;
	int min_distance = 0;
	int usefulpkcnt = 0;
	//float* usefulpks = (float*)malloc(3*sizeof(float));
	float usefulpks[3];
	//int* usefullocs = (int*) malloc(3*sizeof(int));
	int usefullocs[3];
	fpeaks(signal, signal_length, threshold, min_distance, usefulpks, usefullocs, &usefulpkcnt);
	return 0;
}
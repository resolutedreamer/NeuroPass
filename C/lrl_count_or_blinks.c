int* lrl_count_or_blinks(int* masked_peaks,int masked_peaks_length)
{
	int lrl_count = 0;
	int i = 0, j = 0, k = 0, blinks = 0, z = 0,blinking = 0;
	int outputsequence_counter = 0;
	int temp[4];
	int* outputsequence;
	int code1[4] = {POS_VAL, NEG_VAL, POS_VAL, NEG_VAL};
	int code2[4] = {POS_VAL, POS_VAL, POS_VAL, POS_VAL};
	
	outputsequence = (int*)malloc(10*sizeof(int));
	
	while ( i < masked_peaks_length)
	{
		if (i < 4)
		{
			i = i + 1;
			continue;
		}
		temp[0] = masked_peaks[i-3];
		temp[1] = masked_peaks[i-2];
		temp[2] = masked_peaks[i-1];
		temp[3] = masked_peaks[i];
		
		if (temp[0] == code1[0] && temp[1] == code1[1] && temp[2] == code1[2] && temp[3] == code1[3] )
		{
			outputsequence_counter++;
			outputsequence[outputsequence_counter] = 0;
			i = i + 4;
		}
		else if (temp[0] == code2[0] && temp[1] == code2[1] && temp[2] == code2[2] && temp[3] == code2[3] )
		{
			outputsequence_counter++;
			outputsequence[outputsequence_counter] = 1;
			i = i + 4;
		}
		else
		{
			i=i+1;
			continue;
		}
	}
	return outputsequence;
}

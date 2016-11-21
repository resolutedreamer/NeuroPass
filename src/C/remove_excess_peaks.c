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
}

#define POS_VAL 2	// POS peaks have value 2
#define NEG_VAL 3	// NEG peaks have value 3

typedef struct Events
{
	int loc;
	int logical_value;
} Events;

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

Events* get_total_events (int* positivepklocs, int* negativepklocs, int positivepkcnt, int negativepkcnt)
{
	int i;
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
	
	sort_and_combine(positive_events,positivepkcnt, negative_events,negativepkcnt, &total_events);
	
	return total_events;
}


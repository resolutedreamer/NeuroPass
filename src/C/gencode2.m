
while (i < totalpkcnt)
{
	limit = i + window;
	number = 0;
	for (j = 0; j < totalpkcnt; j++)
	{
		if (total_events[j].loc < limit && total_events[j].loc > i)
			number = number+1;
	}
	i = i + window;
	period[k] = number;
	k=k+1;
}
thismany = k;

k=0;
for (i=1; i < thismany; i++)
{
	if (period[i] > 5)
	{
		printf("3");
		k=k+1;
	}
	else if (period[i] > 0)
	{
		printf("2");
		k=k+1;
	}
}

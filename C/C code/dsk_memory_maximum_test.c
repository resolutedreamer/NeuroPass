int main()
{
	int i;
	double * test;
	printf("malloc-ing.\n");
	test = (double*)malloc(2000*sizeof(double));
	if (test == NULL)
		printf("mem allocation failure.\n");
	else
		printf("mem allocation success.\n");
	printf("done.\n");
	return 0;

}


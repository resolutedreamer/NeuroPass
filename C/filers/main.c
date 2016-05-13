#include <stdio.h>

float AC_EEG_data[28];

int x, y;


void loaddata(char * input)
{
	int most_digits = 20, bigcounter=0, doneflag=0;
	char temp[20];
	char *idx;

	int i = 0;
	double current_number = 0;

	//int a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14;
	//double d;

	// get the input file, which at this point is a text file containing AC_EEG_data
	FILE* fp = fopen(input,"r");


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
 		for( i = 0; i < most_digits; i++)	
		{
			temp[i] = fgetc(fp);
			if (temp[i] == ',')
				break;
			else if (temp[i] == EOF)
				doneflag=1;
		}
		if(doneflag==1)
		{
			break;
		}
		else
		{
			//instead of storing a comma, mark the end of the string
			temp[i] = '\0';
			//i = 0;
			//printf("%s\n",strcpy(idx,temp,2));
			current_number = atoi(strcpy(idx,temp,2)); ///////////// From TA: The pointer idx is used to store the first two values of temp
			AC_EEG_data[bigcounter] = current_number;
			printf("%f\n", current_number);
			bigcounter++;
		}
	}


	
	//for(x = 0; x < 70; x ++) {
	//		printf("%f\n", AC_EEG_data[x]);
	//}

	//DOUBLE POINTERS
	//FGET
	
	fclose(fp);
	printf("AC_EEG_data.csv successfully imported into AC_EEG_data array.\n");
}





int main()
{
	printf("Hello World.\n");
	loaddata("C:/CCStudio_v3.1/MyProjects/filers/AC_EEG_data.CSV");
	printf("Done.\n");
	return 0;
}

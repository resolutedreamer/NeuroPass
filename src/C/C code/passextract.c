inputdata[100];
currentpass[20];

for(int i = 0; i < 100;)
{
	for (int k = 0; k < 5; k++)
	{
		if (inputpassword[k] == 1)
		{
			currentpass[i]=1;
		}
		else if (inputpassword[k] == 2)
		{
			currentpass[i]=2;	
		}
		else if (k == 4 && currentpass[i] != 1 || currentpass[i] != 2)
		{
			currentpass[i]=0;
		}
	}
	i = i+20;
}

//FILE* newfilepointer = fopen("qq.txt", w);
//for (i = 0; i <20; i++) fout to filepointer currentpass[i]
//fclosefile
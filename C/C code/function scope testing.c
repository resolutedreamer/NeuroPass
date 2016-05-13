int foo (int a, int **a1)
{
	a = 1;
	int * temp = (int*)malloc(sizeof(int));
	*a1 = temp;
	return a;
}

int main
{
	int a;
	int *a1 = NULL;
	int b;
	b = foo(a, &a1);
	
}
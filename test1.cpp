#include <stdio.h>
#include <stdlib.h>
void test(int &x)
{
	x=1024;
	printf("test函数内部 x=%d\n",x);
}

int main()
{

   printf("Hello, World! \n");
   int x=1;
	printf("调用test前 x=%d\n",x);
	test(x);
	printf("调用test后 x=%d\n",x);
	system("pause");
   return 0;
   
}


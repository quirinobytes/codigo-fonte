#include <stdio.h>


int fib(int num){

if (num ==0)
	return 1;
else
	return num*fib(num-1);
}




int main (){

int pid,c,a=5;
int valor;

fork();

pid = getpid();
printf("%d",pid);

if (pid==0){
	printf( "PID: %d \n",pid);
	for (c=0;c<4;c++){
		pid = fork();
	}
}

if (pid!=0){
//	printf( "PID: %d \n",pid);

	if (pid%2==0){
		printf("é par: digite o fib:\n");
		scanf("%d",valor);
		printf("FIB(%d)=%f",fib(5.0));
		for (;a<10;a++){
		printf("%d: %d\n",pid,a);
		}
	}

	if (pid%2!=0){
		printf("é impar:");
		for (;a>0;a--)
		printf ("%d: %d\n",pid,a);
	}

}





return 0;

}

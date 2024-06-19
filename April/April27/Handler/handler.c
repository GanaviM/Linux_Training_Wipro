// CPP program to illustrate 
// User-defined Signal Handler 
#include<stdio.h> 
#include<signal.h>
 
// Handler for SIGINT, caused by 
// Ctrl-C at keyboard 
void handle_sigint(int sig) 
{ 
	printf("Caught signal %d\n", sig); 
}
 
int main() 
{ 
	signal(SIGINT, handle_sigint); 
	while (1) ; 
	return 0; 
} 


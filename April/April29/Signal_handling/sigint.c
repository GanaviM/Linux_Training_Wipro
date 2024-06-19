#include<stdio.h>
#include<stdlib.h>
#include<signal.h>

//Signal handler function
void sigint_handler(int signum)
{
	printf("Caught SIGINT (%d)\n", signum);
	//Custom handling for SIGINT
	//For example, cleanup or graceful shutdown
	exit(signum);
}
int main()
{
	//Define the struct for the signal action
	//Signal(SIGINT, sigint_handler);
	struct sigaction sa; 
	sa.sa_handler = sigint_handler; //Set the signal handler function
	sigemptyset(&sa.sa_mask);//Clear the special mask
	sa.sa_flags = 0; //Nospecial flags

	//Register teh signal handler for SIGINT
	if(sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("Sigaction");
		exit(EXIT_FAILURE);
	
	}
	printf("Signal handler registered for SIGINT Press Ctrl+c to trigger\n");

	//loop indefinitely
	while(1)
	{
		//Do something
	}
	return 0;

}

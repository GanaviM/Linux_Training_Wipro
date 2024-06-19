#include<stdio.h> 
#include<stdlib.h>
 
// entry point function 
int nomain();
 
void _start(){
 
	// calling entry point 
	nomain(); 
	exit(0); 
}
 
int nomain() 
{ 
	puts("Geeksforgeeks"); 
	return 0; 
} 

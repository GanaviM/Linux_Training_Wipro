#include <stdio.h>
#include <pthread.h>

#define MAX_SIZE 5

pthread_mutex_t bufLock;
int count;

void producer(char* buf)
{
       	for(;;) 
	{
	       	while(count == MAX_SIZE);
	       	pthread_mutex_lock(&bufLock);
	        buf[count] = getchar();
		count++; 
		pthread_mutex_unlock(&bufLock);
       	}
}

void useChar(char ch)
{
	printf("Used character: %c\n", ch);
}

void consumer(char* buf)
{
	char ch;
	int newlineCount = 0;

	for(;;)
	{
		while(count == 0);
		pthread_mutex_lock(&bufLock);
		
		ch = buf[count - 1];
		count--;
		pthread_mutex_unlock(&bufLock);
		
		if (ch == '\n')
		{
			newlineCount++;
			if(newlineCount >=2)
			{
				break;
			}
			else{
				newlineCount = 0;
				useChar(ch);
			}
		}
	}
}

int main()
{
	char buffer[MAX_SIZE];
	pthread_t p;
	count = 0;
	pthread_mutex_init(&bufLock, NULL);
	pthread_create(&p, NULL, (void*)producer, &buffer);
	printf("Enter characters: \n");

	consumer(buffer);
	return 0;
}

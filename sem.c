#include <stdio.h> 
#include <stdlib.h>
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
#include <sys/types.h>

#define MAX_THREAD 20
pthread_t tid[MAX_THREAD]; 
pthread_mutex_t mutex;
int count = 0;
  
void* thread(void* arg) 
{ 
    pthread_mutex_lock(&mutex);
    printf("\nEntered..\n"); 
  
    //critical section 
    count++;
    sleep(2); 
      
    //signal 
    printf("\nJust Exiting...\n"); 
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
} 
  
  
int main() 
{ 
    pthread_mutex_init(&mutex, NULL);
    int i;
    int p = 0;
    int l = 0;
    for (i = 0 ; i < MAX_THREAD ; i++)
    {
        p = pthread_create(&(tid[i]), NULL, thread, NULL);
		if (p != 0)
		{
			printf("Thread [%d] created error\n", i);
		}
    }

    for(i = 0; i < MAX_THREAD; i++)
    {   
        l = pthread_join(tid[i], NULL);
        if(l != 0)
        {
            printf("Thread [%d] created error\n", i);
        }
    }
    pthread_mutex_destroy(&mutex);
    printf("Count value: %d\n", count);
    return 0; 
}

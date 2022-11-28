#include <stdio.h> 
#include <stdlib.h>
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
#include <sys/types.h>
#include <time.h>
#include <sys/resource.h>
#define MAX_THREAD 20
pthread_t tid[MAX_THREAD]; 
pthread_mutex_t mutex;

int count = 0;
  
void* thread(void* arg) 
{ 
    // get time per thread
    clock_t t;
    t = clock();

    pthread_mutex_lock(&mutex);
    // Get RAM
    struct rusage r_usage;
    getrusage(RUSAGE_SELF,&r_usage);
    // Print the maximum resident set size used (in kilobytes).
    printf("Memory usage: %ld kilobytes\n",r_usage.ru_maxrss);
    printf("\nEntered..\n"); 
  
    //critical section 
    count++;
    sleep(1); 
      
    //signal 
    printf("\nJust Exiting...\n"); 
    // t = clock() - t;

    // save in file
    FILE *fptr;
    fptr = fopen("/home/bai8/data_mutex.txt","a");
    fprintf(fptr,"%f %ld",(double)t/CLOCKS_PER_SEC, r_usage.ru_maxrss);
    fputs("\r\n", fptr);
    fclose(fptr);

    pthread_mutex_unlock(&mutex);

   
    pthread_exit(NULL);

    // write in file txt
} 
  
  
int main() 
{ 
    clock_t t;
    t = clock();
    pthread_mutex_init(&mutex, NULL);
    int i;
    int p = 0;
    int l = 0;
    for (i = 0 ; i < MAX_THREAD ; i++)
    {
        p = pthread_create(&(tid[i]), NULL, &thread, NULL);
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

    t = clock() - t;

    // save total time
    
    FILE *fptr;
    fptr = fopen("/home/bai8/data_mutex.txt","a");
    fprintf(fptr,"Total time/RAM: %f",(double)t/CLOCKS_PER_SEC);
    fputs("\r\n", fptr);
    fclose(fptr);
    printf("Count value: %d\n", count);
    return 0; 
}

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h> 

/* source: https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html */

/* This sample code explains how two independent threads are created 
 * pthread_create creates a thread whose starting function is print_message_function
 * pthread_join is a 'blocking call' that waits until the pthread_create terminates
 */

void *print_message_function( void *ptr );
int print_time();

int print_time()
{
    time_t timer;
    char buffer[26];
    struct tm* tm_info;
    timer = time(NULL);
    tm_info = localtime(&timer);
    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
    printf ("%s:", buffer);
    return 0;
}


void main(void)
{
     pthread_t thread1, thread2;
     char *message1 = "Thread 1";
     char *message2 = "Thread 2";
     int  iret1, iret2;

    /* Create independent threads each of which will execute function */


     iret1 = pthread_create( &thread1, NULL, print_message_function, (void*) message1);
     iret2 = pthread_create( &thread2, NULL, print_message_function, (void*) message2);

     /* Wait till threads are complete before main continues. Unless we  */
     /* wait we run the risk of executing an exit which will terminate   */
     /* the process and all threads before the threads have completed.   */
     printf ("Waiting for Thread 1 to join\n");
     pthread_join( thread1, NULL);
     printf ("Waiting for Thread 2 to join\n");
     pthread_join( thread2, NULL); 

     print_time();
     printf("Thread 1 returns: %d\n",iret1);
     print_time();
     printf("Thread 2 returns: %d\n",iret2);
     exit(0);
}

void *print_message_function( void *ptr )
{
     char *message;
     message = (char *) ptr;
     print_time();
     printf("processing %s \n", message);
     sleep (2);
     print_time();
     printf("finished processing %s \n", message);
}

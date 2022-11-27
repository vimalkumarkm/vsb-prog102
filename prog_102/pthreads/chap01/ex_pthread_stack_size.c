#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* altered from source: https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html */

/* This sample code explains how two independent threads are created 
 * pthread_create creates a thread whose starting function is print_message_function
 * pthread_join is a 'blocking call' that waits until the pthread_create terminates
 */

void *print_message_function( void *ptr );

void main(void)
{
     pthread_t thread1;
     char *message1 = "Thread 1";
     pthread_attr_t attr;
     int iret1;
     unsigned long int stacksize = 0;

     pthread_attr_init(&attr);
     pthread_attr_getstacksize(&attr, &stacksize);
     printf("Thread stack size = %lu bytes \n", stacksize);


     stacksize = 1000000;
     pthread_attr_init(&attr);
     pthread_attr_setstacksize(&attr, stacksize);


     pthread_attr_init(&attr);
     pthread_attr_getstacksize(&attr, &stacksize);
     printf("Thread stack size = %lu bytes \n", stacksize);

    /* Create independent threads each of which will execute function */
     iret1 = pthread_create( &thread1, NULL, print_message_function, (void*) message1);

     /* Wait till threads are complete before main continues. Unless we  */
     /* wait we run the risk of executing an exit which will terminate   */
     /* the process and all threads before the threads have completed.   */

     pthread_join( thread1, NULL);

     printf("Thread 1 returns: %d\n",iret1);
     exit(0);
}

void *print_message_function( void *ptr )
{
     char *message;
     message = (char *) ptr;
     printf("%s \n", message);
}

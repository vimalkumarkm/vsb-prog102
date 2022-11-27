#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h> 

int g_myvar = 0;
int debug = 0;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;


/* source: https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html */

/* This sample code explains how two independent threads are created 
 * pthread_create creates a thread whose starting function is print_message_function
 * pthread_join is a 'blocking call' that waits until the pthread_create terminates
 */

void *print_message_function1( void *ptr );
void *print_message_function2( void *ptr );
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


     iret1 = pthread_create( &thread1, NULL, print_message_function1, (void*) message1);
     iret2 = pthread_create( &thread2, NULL, print_message_function2, (void*) message2);

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


void *print_message_function1( void *ptr )
{
     char *message;
     int  i = 0;
     int  l_myvar = 0;
     static int s_myvar = 0;
     message = (char *) ptr;
     int ret;
     printf("processing %s \n", message);

     for (i = 0; i < 1000000; i ++)
     {
	     if (debug) printf ("thread 1 to acquire mutex1\n");
	     pthread_mutex_lock (&mutex1);
	     if (debug) printf ("thread 1 acquired mutex1\n");
	     while ((ret = pthread_mutex_trylock (&mutex2)))
	     {
	             printf ("$thread 1 couldnt acquire mutex2 %d\n", ret);
		     pthread_mutex_unlock (&mutex1);
	             printf ("$thread 1 unlock mutex1\n");
		     printf ("$thread 1 sleeping ..");
		     sleep (1);
		     pthread_mutex_lock (&mutex1);
	             printf ("$thread 1 acquired mutex1\n");
	     }
	     if (debug) printf ("thread 1 acquired mutex2\n");
	     l_myvar ++;
	     g_myvar ++;
	     s_myvar ++;
	     if (debug)
	     {
		     printf ("%s ",message);
		     print_time();
		     printf ("l_myvar: %d  g_myvar: %d s_myvar:%d\n", l_myvar, g_myvar, s_myvar);
	     }
	     pthread_mutex_unlock (&mutex1);
	     if (debug) printf ("thread 1 unlock mutex1\n");
	     pthread_mutex_unlock (&mutex2);
	     if (debug) printf ("thread 1 unlock mutex2\n");
	     //sleep (1);
     }

}


void *print_message_function2( void *ptr )
{
     char *message;
     int  i = 0;
     int  l_myvar = 0;
     static int s_myvar = 0;
     message = (char *) ptr;
     printf("processing %s \n", message);


     for (i = 0; i < 1000000; i ++)
     {
	     if (debug) printf ("thread 2 to acquire mutex2\n");
	     pthread_mutex_lock (&mutex2);
	     if (debug) printf ("thread 2 acquired mutex2\n");
	     while (pthread_mutex_trylock (&mutex1))
	     {
	     	     printf ("#thread 2 couldnt acquire mutex1\n");
		     pthread_mutex_unlock (&mutex2);
	     	     printf ("#thread 2 released mutex2\n");
		     printf ("#thread 2 sleeping ..\n");
		     sleep (1);
		     pthread_mutex_lock (&mutex2);
	     	     printf ("#thread 2 acquired mutex2\n");
	     }
	     if (debug) printf ("thread 2 acquired mutex1\n");
	     //pthread_mutex_lock (&mutex1);
	     l_myvar ++;
	     g_myvar ++;
	     s_myvar ++;
	     if (debug)
	     {
		     printf ("%s ",message);
		     print_time();
		     printf ("l_myvar: %d  g_myvar: %d s_myvar:%d\n", l_myvar, g_myvar, s_myvar);
	     }
	     pthread_mutex_unlock (&mutex2);
	     if (debug) printf ("thread 2 unlock mutex2\n");
	     pthread_mutex_unlock (&mutex1);
	     if (debug) printf ("thread 2 unlock mutex1\n");
	     //sleep (1);
     }

}

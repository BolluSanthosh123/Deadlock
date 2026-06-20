#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
pthread_mutex_t mutex;
pthread_mutex_t mutex1;

void *thread1(void *arg)
{ 
    pthread_mutex_lock(&mutex);
    printf("thread1 acquire the mutex1\n");
    sleep(5);
    printf("thread1 waiting for mutex2\n");
    pthread_mutex_lock(&mutex1);
    printf("thread1 acquired mutex2\n");

    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex);
    
    return NULL;
}
void *thread2(void *arg)
{
    pthread_mutex_lock(&mutex1);
    printf("Thread2 acquired mutex2\n");
    sleep(5);
    printf("thread2 waiting for mutex1\n");
    pthread_mutex_lock(&mutex);
    printf("tread2 aqcuired mutex1\n");

    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex);
    return NULL;
}
int main()
{
	pthread_t t1,t2;
	pthread_mutex_init(&mutex,NULL);
	pthread_mutex_init(&mutex1,NULL);

	pthread_create(&t1,NULL,thread1,NULL);
	pthread_create(&t2,NULL,thread2,NULL);

	pthread_join(t1,NULL);
	pthread_join(t2,NULL);

	pthread_mutex_destroy(&mutex);
	pthread_mutex_destroy(&mutex1);
	return 0;
}

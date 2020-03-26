#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

#define COUNT 10
static  int   i = 1;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  even  = PTHREAD_COND_INITIALIZER;
pthread_cond_t  uneven = PTHREAD_COND_INITIALIZER;

//1 3 5 7 9

//2 4 6 8 10
void* funB(void *arg)
{
    while(i <= COUNT)
    {
        pthread_mutex_lock(&mutex);
        if(i % 2 == 0)
        {
            printf("pthread_B : %d\n",i);
            ++i;
            pthread_cond_signal(&even);
        }
        else
            pthread_cond_wait(&uneven, &mutex);
        pthread_mutex_unlock(&mutex);
    }
}

int main()
{
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, funA, NULL);
    pthread_create(&tid2, NULL, funB, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    return 0;
}
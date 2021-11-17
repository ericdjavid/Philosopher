#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

typedef enum s_bool
{
    FALSE,
    TRUE
} t_bool;

typedef struct s_lolcat
{
    int a;
    int b;
    t_bool IS_FINISHED;
    pthread_mutex_t mymutex;
    pthread_mutex_t END;
} t_lolcat;

t_bool check_end(t_lolcat *clone)
{
    pthread_mutex_lock(&clone->END);
    if (clone->IS_FINISHED == TRUE)
    {
        pthread_mutex_unlock(&clone->END);
        return TRUE;
    }
    pthread_mutex_unlock(&clone->END);
    return (FALSE);
}

void *loop(void *numbz)
{
    t_lolcat *clone = (t_lolcat *)numbz;
    printf("Started execution\n");
    while (check_end(clone) == FALSE)
    {
        pthread_mutex_lock(&clone->mymutex);
        printf("%d%d", clone->a, clone->b);
        // if (clone->a == 5)
        //     break;
        pthread_mutex_unlock(&clone->mymutex);
        sleep(0.2);
    }
    printf("\nFinished execution\n");
    pthread_exit(NULL);
}

void *the_hell(void *numbz)
{
    t_lolcat *clone = (t_lolcat *)numbz;

    int i = 0;

    while (clone->a < 5)
    {
        pthread_mutex_lock(&clone->mymutex);
        clone->a += 1;
        clone->b += 1;
        pthread_mutex_unlock(&clone->mymutex);
        sleep(1);
    }
    pthread_mutex_lock(&clone->END);
    clone->IS_FINISHED = TRUE;
    pthread_mutex_unlock(&clone->END);
}

int main(int argc, char *argv[])
{
    t_lolcat *numbz = malloc(sizeof(*numbz));
    numbz->a = 1;
    numbz->b = 2;
    numbz->IS_FINISHED = FALSE;

    pthread_t th1;
    pthread_t th2;

    pthread_mutex_init(&numbz->mymutex, NULL);
    pthread_mutex_init(&numbz->END, NULL);
    int ret = pthread_create(&th1, NULL, loop, (void *)numbz);
    if (ret)
        return 1;
    int ret2 = pthread_create(&th2, NULL, the_hell, (void *)numbz);
    if (ret2)
        return 1;

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    free(numbz);
    return 0;
}
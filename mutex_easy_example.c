#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//equivalent a pthread init
//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef	struct              s_p
{
    pthread_mutex_t         mutex;
    int                     thread1;
    int                     thread2;
}                           t_p;

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

void    *go1(void *mutex)
{
    //t_p *ppp;
    //ppp = (t_p *)mutex;
   // pthread_mutex_lock(&ppp->mutex); // si on enleve ici
   sleep(3);
    for (int i = 0; i < 100; i++)
    {
        fprintf(stderr, "\033[95mthread 1: %d\033[0m\n", i);
    }
  //  pthread_mutex_unlock(&ppp->mutex); // si on enleve ici
    pthread_exit (0); //ne pas oublier d'exit du thread pr free les 
}

void    *go2(void *mutex)
{
    //t_p *ppp;
    //ppp = (t_p *)mutex;
   // pthread_mutex_lock(&ppp->mutex); // si on enleve ici
    for (int i = 0; i < 100; i++)
    {
        fprintf(stderr, "\033[90mthread 2: %d\033[0m\n", i);
    }
  //  pthread_mutex_unlock(&ppp->mutex); // si on enleve ici
    pthread_exit (0); //ne pas oublier d'exit du thread pr free les 
}

int main()
{
    pthread_t               thread_id1;
    pthread_t               thread_id2;
    t_p                     mutex;    // structure mutex
//    t_p                     *pp; // pointeur du mutex p
    void *ret;

  //  pp = &p;
  //  pp->i = 3;

    pthread_mutex_init(&mutex.mutex, NULL);	// obligatoire de init le mutex

    // creer les 2 threads et appeler la fonction go1 avec le pointeur sur mutex en param
    pthread_create(&thread_id1, NULL, go1, (void *)&mutex);
    pthread_create(&thread_id2, NULL, go2, (void *)&mutex);

    //permet d'attendre que tous les threads soient finis avec de end le process main
    (void)pthread_join (thread_id1, &ret);
    (void)pthread_join (thread_id2, &ret);
    sleep(1);
    return 0;
}

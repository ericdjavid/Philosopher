#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef	struct              s_p
{
    pthread_mutex_t         mutex;
    int                     i;
}                           t_p;

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

void    *go1(void *pp)
{
    char *str;
    static int i = 0;
    t_p *ppp;

    ppp = (t_p *)pp;
i++;
    pthread_mutex_lock(&ppp->mutex); // si on enleve ici
 
	printf("variable utilisee is %d", ppp->i);
	printf("increment is %d\n", i);
    pthread_mutex_unlock(&ppp->mutex); // si on enleve ici
    pthread_exit (0); //ne pas oublier d'exit du thread pr free les 
}

int main()
{
    pthread_t               thread_id1;
    pthread_t               thread_id2;
    t_p                     p;
    t_p                     *pp; // tu crees un pointeur du mutex p
    void *ret;

    pp = &p;
    pp->i = 3;

    pthread_mutex_init(&p.mutex, NULL);			// obligatoire de init le mutex
    //sinon ca fait des conditional jumps
    pthread_create(&thread_id1, NULL, go1, (void *)pp);
    pthread_create(&thread_id2, NULL, go1, (void *)pp);

    
    (void)pthread_join (thread_id1, &ret);
    (void)pthread_join (thread_id2, &ret);
    sleep(1);
    return 0;
}

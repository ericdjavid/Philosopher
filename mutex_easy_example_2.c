#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

static pthread_mutex_t my_mutex;
static int tab[5];

void *read_tab_process(void *arg)
{
    int i;

    pthread_mutex_lock(&my_mutex);
    for (i = 0; i != 5; i++)
        printf("read_process, tab[%d] vaut %d\n", i, tab[i]);
    pthread_mutex_unlock(&my_mutex);
    pthread_exit(0);
}

void *write_tab_process(void *arg)
{
    int i;

    pthread_mutex_lock(&my_mutex);
    for (i = 0; i != 5; i++)
    {
        tab[i] = 2 * i;
        printf("write_process, tab[%d] vaut %d\n", i, tab[i]);
        sleep(1); /* Relentit le thread d'ecriture... */
    }
    pthread_mutex_unlock(&my_mutex);
    pthread_exit(0);
}

main(int ac, char **av)
{
    pthread_t th1, th2;
    void *ret;

    pthread_mutex_init(&my_mutex, NULL);

    if (pthread_create(&th1, NULL, write_tab_process, NULL) < 0)
    {
        fprintf(stderr, "pthread_create error for thread 1\n");
        exit(1);
    }

    if (pthread_create(&th2, NULL, read_tab_process, NULL) < 0)
    {
        fprintf(stderr, "pthread_create error for thread 2\n");
        exit(1);
    }

    (void)pthread_join(th1, &ret);
    (void)pthread_join(th2, &ret);
}

/*

La fonction pthread_mutex_lock verrouille le MUTEX pendant la durée du remplissage du tableau. Le thread de lecture est contraint d'attendre l'appel à pthread_mutex_unlock pour verrouiller à son tour le MUTEX et lire le tableau correct. A l'exécution on obtient:
pierre@mmxpf % ./thread2
write_process, tab[0] vaut 0
write_process, tab[1] vaut 2
write_process, tab[2] vaut 4
write_process, tab[3] vaut 6
write_process, tab[4] vaut 8
read_process, tab[0] vaut 0
read_process, tab[1] vaut 2
read_process, tab[2] vaut 4
read_process, tab[3] vaut 6
read_process, tab[4] vaut 8

Si par malheur on n'utilisait par le MUTEX, on obtiendrait par contre:
pierre@mmxpf % ./thread2
write_process, tab[0] vaut 0
read_process, tab[0] vaut 0
read_process, tab[1] vaut 0
read_process, tab[2] vaut 0
read_process, tab[3] vaut 0
read_process, tab[4] vaut 0
write_process, tab[1] vaut 2
write_process, tab[2] vaut 4
write_process, tab[3] vaut 6
write_process, tab[4] vaut 8

*/
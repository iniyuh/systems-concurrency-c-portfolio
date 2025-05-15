// from the Cilk manual: http://supertech.csail.mit.edu/cilk/manual-5.4.6.pdf
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

int safe(char * config, int i, int j)
{
    int r, s;

    for (r = 0; r < i; r++)
    {
        s = config[r];
        if (j == s || i-r==j-s || i-r==s-j)
            return 0;
    }
    return 1;
}

struct args {
    char * config;
    int n;
    // int startPoint;
    // int i;
};

int count = 0;
sem_t sem;

void nqueens(char *config, int n, int i) {
    char *new_config;
    int j;

    if (i==n)
    {
        sem_wait(&sem);
        count++;
        sem_post(&sem);
    }
    
    /* try each possible position for queen <i> */
    for (j=0; j<n; j++)
    {
        /* allocate a temporary array and copy the config into it */
        new_config = malloc((i+1)*sizeof(char));
        memcpy(new_config, config, i*sizeof(char));
        if (safe(new_config, i, j))
        {
            new_config[i] = j;
	        nqueens(new_config, n, i+1);
        }
        free(new_config);
    }

    return;
}

void * runner (void * param) {
    struct args * struct_ptr = (struct args *) param;

    nqueens(struct_ptr->config, struct_ptr->n, 1);

    return NULL;
}

int main(int argc, char *argv[])
{
    int n;
    // char *config;

    if (argc < 2)
    {
        printf("%s: number of queens required\n", argv[0]);
        return 1;
    }

    n = atoi(argv[1]);
    // config = malloc(n * sizeof(char));
    // count = malloc(n * sizeof(int));
    pthread_t tid[n];

    printf("running queens %d\n", n);

    struct args * set = malloc(n * sizeof(struct args));
    sem_init(&sem, 0, 1);
    for (int i = 0; i < n; i++) {
        // count[i] = 0;
        // config[0] = i;

        set[i].config = malloc(n * sizeof(char));
        set[i].config[0] = i;
        set[i].n = n;
        // set[i].startPoint = 1;
        // set[i].i = i;

        // nqueens(set[i].config, set[i].n, set[i].startPoint, set[i].i);

        pthread_create(&tid[i], NULL, runner, &set[i]);
    }

    for (int i = 0; i < n; i++) {
        pthread_join(tid[i], NULL);
    }
    sem_destroy(&sem);

    // int sum = 0;
    // for (int i = 0; i < n; i++) {
    //     // printf("%d\n", count[i]);
    //     sum += *(set[i].count);
    // }

    printf("# solutions: %d\n", count);

    for (int i = 0; i < n; i++) {
        free(set[i].config);
    }
    free(set);

    return 0;
}

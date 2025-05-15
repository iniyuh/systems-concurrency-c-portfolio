#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>

#include <sys/ipc.h>
#include <sys/msg.h>

#define CITIES_LENGTH 7
#define NUM_CITIES (CITIES_LENGTH - 1)

static const char* cities[] = { "Central City", "Starling City", "Gotham City", "Metropolis", "Coast City", "National City" };

const int distances[CITIES_LENGTH - 1][ CITIES_LENGTH - 1] = {
    {0, 793, 802, 254, 616, 918},
    {793, 0, 197, 313, 802, 500},
    {802, 197, 0, 496, 227, 198},
    {254, 313, 496, 0, 121, 110},
    {616, 802, 227, 121, 0, 127},
    {918, 500, 198, 110, 127, 0}
};

int initial_vector[CITIES_LENGTH] = { 0, 1, 2, 3, 4, 5, 0 };

typedef struct {
    int cities[CITIES_LENGTH];
    int total_dist; 
} route;

typedef struct {
    long mtype;
    int distance;
} msg;

void print_route ( route* r ) {
    printf ("Route: ");
    for ( int i = 0; i < CITIES_LENGTH; i++ ) {
        if ( i == CITIES_LENGTH - 1 ) {
            printf( "%s\n", cities[r->cities[i]] );
        } else {
            printf( "%s - ", cities[r->cities[i]] );
        }
    }
}

void calculate_distance( route* r ) {
    if ( r->cities[0] != 0 ) {
        printf( "Route must start with %s (but was %s)!\n", cities[0], cities[r->cities[0]]);
        exit( -1 );
    } 
    if ( r->cities[6] != 0 ) {
        printf( "Route must end with %s (but was %s)!\n", cities[0], cities[r->cities[6]]);
        exit ( -2 );
    }
    int distance = 0;
    for ( int i = 1; i < CITIES_LENGTH; i++ ) {
        int to_add = distances[r->cities[i-1]][r->cities[i]];
        if ( to_add == 0 ) {
            printf( "Route cannot have a zero distance segment.\n");
            exit ( -3 );
        }
        distance += to_add;
    }
    r->total_dist = distance;
}

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void permute(route* r, int left, int right, route* best) {
    if (left == right) {
        int msgqid = msgget(IPC_PRIVATE, 0666 | IPC_CREAT);

        int pid = fork();

        if (pid < 0) {
            printf("Error %d occured.", pid);
            exit(-1);
        }
        else if (pid == 0) {
            msg m;
            m.mtype = 1;

            calculate_distance(r);
            m.distance = r->total_dist;

            msgsnd(msgqid, &m, sizeof(msg), 0);
            free(r);
            free(best);
            exit(0);
        }
        else {
            msg m2;
            msgrcv(msgqid, &m2, sizeof(msg), 1, 0);

            r->total_dist = m2.distance;

            if (m2.distance < best->total_dist) {
                memcpy(best, r, sizeof(route));
            }

            msgctl(msgqid, IPC_RMID, NULL);
        }        

        return;
    }

    for (int i = left; i <= right; i++) {
        swap(&r->cities[left], &r->cities[i]);
        permute(r, left + 1, right, best);
        swap(&r->cities[left], &r->cities[i]);
    }
}   

void assign_best(route** best, route* candidate) {
    if (*best == NULL) {
        *best = candidate;
        return;
    }

    int a = candidate->total_dist;
    int b = (*best)->total_dist;

    if (a < b) {
        free(*best);
        *best = candidate;
    } else {
        free(candidate);
    }
}

route* find_best_route( ) {
    route* candidate = malloc( sizeof(route) );
    memcpy (candidate->cities, initial_vector, CITIES_LENGTH * sizeof( int ));
    candidate->total_dist = 0;

    route* best = malloc( sizeof(route) );
    memset( best, 0, sizeof(route) );
    best->total_dist = 999999;

    permute( candidate, 1, 5, best );

    free( candidate );
    return best;
}

int main( int argc, char** argv ) {
    route * best = find_best_route( );
    print_route( best );
    printf( "Distance: %d\n", best->total_dist ); 
    free( best );
    return 0;
}
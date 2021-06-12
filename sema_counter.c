#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include <time.h>

union semun{
	int val;
	struct semid_ds *buf;
	ushort *array;
};

#define PATH "/home/june/key"

typedef struct __counter_t {
    union semun sem_arg;
    int semid;
    int value;
    key_t key;  
} counter_t;

unsigned int loop_cnt;
counter_t counter;

void init(counter_t *c) {
    c->value = 0;
    c->key = ftok(PATH, 'z');
    c->semid = semget(c-> key, 1, 0600 | IPC_CREAT);
    c->sem_arg.val=1;
    semctl(c->semid, 0, SETVAL, c->sem_arg);

    if (c->key<0){
	    perror("Key generate Error!!!\n");
	    exit(1);
    }
    
    if (c->semid<0){
	    perror("semaphore set Error!!!\n");
	    exit(1);
    }
    
}

void increment(counter_t *c) {
    struct sembuf s;  
    /* Lock */
    s.sem_num = 0;
    s.sem_op = -1; 
    s.sem_flg = 0;
    semop(c->semid, &s, 1);
    
    c->value++;
    
    /* Unlock */
    s.sem_num = 0;
    s.sem_op = 1;
    s.sem_flg = 0;
    semop(c->semid, &s, 1);
}


void decrement(counter_t *c) {
    struct sembuf s;   
     /* Lock */
    s.sem_num = 0;
    s.sem_op = -1; 
    s.sem_flg = 0;
    semop(c->semid, &s, 1);	
    
    c->value--;    
    
    /* Unlock */
    s.sem_num = 0;
    s.sem_op = 1;
    s.sem_flg = 0;
    semop(c->semid, &s, 1);
}


int get(counter_t *c) { 
    struct sembuf s; 
     /* Lock */
    s.sem_num = 0;
    s.sem_op = -1; 
    s.sem_flg = 0;
    semop(c->semid, &s, 1);
    
    int rc = c->value;
    
    /* Unlock */
    s.sem_num = 0;
    s.sem_op = 1;
    s.sem_flg = 0;
    semop(c->semid, &s, 1);
    return rc;
}

void *mythread(void *sem_arg)
{
    char *letter = sem_arg;
    int i;

    printf("%s: begin\n", letter);
    for (i = 0; i < loop_cnt; i++) {
        increment(&counter);
    }
    printf("%s: done\n", letter);
    return NULL;
}
    


int main(int argc, char *argv[])
{   
    loop_cnt = atoi(argv[1]);

    init(&counter);

    pthread_t p1, p2;
    printf("main: begin [counter = %d]\n", get(&counter));
    pthread_create(&p1, NULL, mythread, "A"); 
    pthread_create(&p2, NULL, mythread, "B");
    // join waits for the threads to finish
    pthread_join(p1, NULL); 
    pthread_join(p2, NULL); 
    printf("main: done [counter: %d] [should be: %d]\n", get(&counter), loop_cnt * 2);
    return 0;
}
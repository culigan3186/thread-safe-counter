#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun {
    int val;
    struct semid_ds *buf;
    ushort *array;
};

#define PATH "/home/june/key"

int main(int argc, char *argv[])
{
    key_t key;
    int semid;
    struct sembuf s;
    union semun arg;

    key = ftok(PATH, 'z');
    if (key < 0) {
        perror(argv[0]);
        exit(1);
    }
    semid = semget(key, 1, 0600 | IPC_CREAT);   
    //semid :세마포어 식별하는 집합번호
    
    if (semid < 0) {
        perror(argv[0]);
        exit(1);
    }

    printf("semid = %d\n", semid);

    arg.val = 1;
    semctl(semid, 0, SETVAL, arg); // semaphore를 컨트롤 하는 함수
    //int semctl ( int semid, int semnum, int cmd, union semun arg)
    
    /* Lock */
    s.sem_num = 0;
    s.sem_op = -1; 
    s.sem_flg = 0;
    semop(semid, &s, 1);

    /* Critical Section Starts */
    printf("getting sem\n");
    for (int i = 0; i < 10; i++) {
        printf("%s in critical section\n", argv[0]);
        sleep(1);
    }
    printf("releasing sem\n");
    /* Critical Section Ends */

    /* Unlock */
    s.sem_num = 0;
    s.sem_op = 1;
    s.sem_flg = 0;
    semop(semid, &s, 1);
    // semop는 세마포어의 값을 변경. 증가 or 감소
    /*
    semctl(semid, 0, IPC_RMID, NULL);      
    */
    return 0;
}

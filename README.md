## Second Assignments:thread safe counter
## Environments
- **Ubuntu 18.04**

## Execution time of Semaphore and Mutex 
I compared the performance of semaphore and mutex using Liuux's time command.
```
time ./mutex_count 1000000
```
```
time ./sema_count 1000000
```
### Mutex excution time 
-time average : real: 0.1085s , user: 0.1602s , sys: 0.053s 

<img src = "https://user-images.githubusercontent.com/67793181/121784608-cd7bd880-cbef-11eb-8a4a-87726d9e7aac.png" height="450px" width="400px">  

### Semaphore execution time
-time average : real: 3.466s , user: 1.414s, sys: 3.871s

<img src = "https://user-images.githubusercontent.com/67793181/121784622-e4bac600-cbef-11eb-816d-78acba524ff5.png" height="450px" width="400px">


## Why is there a difference in performance?
As a result of the execution of mutex and semaphore, mutex had a shorter execution time.In other words, Mutex was faster than Semaphore.

Semaphores can access shared resources by as many processes (or threads) as the semaphores' variables. On the other hand,  Mutex or Mutual Exclusion Object is used to give access to a resource to only one process at a time. The mutex object allows all the processes to use the same resource but at a time, only one process is allowed to use the resource. Mutex uses the lock-based technique to handle the critical section problem.

semaphore can be changed by any process acquiring or releasing the resource.
mutex is released only by the process that has acquired the lock on it.

Semaphore provides features to create queues for synchronization, and mutex has ownership to implement exclusive rights. Mutex is faster than semaphores because it does not require sophisticated implementation of counters and queues.

As mentioned earlier, semaphores need to wait while changing the count, but mutex does not need to, so mutex takes less time.

## Reference

## About Me
- **Name : Kim Wonjune**
- **School : Kookmin University**
- **major : Automobile and IT convergence**
- **Student ID : 20173392**

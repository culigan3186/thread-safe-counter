## Second Assignments:thread safe counter
## Environments
- **Ubuntu 18.04**

## What is Mutex and Semaphore respectively?

- **Semaphore**  : 
- **Mutex** :



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


## Reference

## About Me
- **Name : Kim Wonjune**
- **School : Kookmin University**
- **major : Automobile and IT convergence**
- **Student ID : 20173392**

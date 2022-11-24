#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>

// Define constants
#define NUM_OF_PROCESSING_THREADS 10
#define NUM_OF_TASKS 10

pthread_mutex_t mutexQueue;
pthread_cond_t condQueue;

typedef struct TaskToDo {
    int numOne;
    int numTwo;
    void (*taskFunction)(int, int);
} TaskToDo;

TaskToDo tasksQueue[NUM_OF_TASKS];
int queueSize = 0;

// Create several different functions to assign it to a task and make it by threads as required
void sum(int a, int b)
{
    printf("Sum of % d and %d is %d\n", a, b, (a + b));
}

void multiplication(int a, int b)
{
    printf("Multiplication of % d and %d is %d\n", a, b, (a * b));
}

void *processTask(TaskToDo *task)
{
    task->taskFunction(task->numOne, task->numTwo);                      // Use two numbers and the function to do of the task assigned
    // int result = task->numOne + task->numTwo;
    // printf("The sum of %d and %d is: %d\n", task->numOne, task->numTwo, result);

    return NULL;
}

void submitTask(TaskToDo taskToSubmit)                                  // Main thread is adding tasks to the array and signaling one thread to process a task
{
    pthread_mutex_lock(&mutexQueue);
    tasksQueue[queueSize] = taskToSubmit;
    queueSize++;
    pthread_mutex_unlock(&mutexQueue);
    pthread_cond_signal(&condQueue);                                    // Signal only one task, since we are adding only one task
}

void *processingThread(void *args)                                  // Processing tasks are waiting here for a job
{
    while (1){
        TaskToDo taskToAssign;

        pthread_mutex_lock(&mutexQueue);
        while (queueSize == 0)
            pthread_cond_wait(&condQueue, &mutexQueue);             // Wait on the condition variable (again, lock the current thread and unlock the mutex atomically, so the others may come or a new task submitted)
        // Initially, this example used checking of whether the work is found with no sleeping tasks
        taskToAssign = tasksQueue[0];                               // Take the first element
        for (int i = 0; i < queueSize - 1; i++)                     // Move the rest to the beginning, just a simple simulation
            tasksQueue[i] = tasksQueue[i + 1];
        queueSize--;
        pthread_mutex_unlock(&mutexQueue);

        processTask(&taskToAssign);
    }
    return NULL;
}

int main(int argc, char **argv)
{
    // TaskToDo t1 = {5, 10};
    pthread_mutex_init(&mutexQueue, NULL);
    pthread_cond_init(&condQueue, NULL);

    pthread_t myThreads[NUM_OF_PROCESSING_THREADS];

    // 1. Create threads sequentially
    for (int i = 0; i < NUM_OF_PROCESSING_THREADS; i++){
        pthread_create(&myThreads[i], NULL, processingThread, NULL);
    }

    // 2. Submitting new tasks passing function to do and two arguments to be processed
    for (int i = 0; i < NUM_OF_TASKS; i++)
        // submitTask((TaskToDo) { .numOne = i, .numTwo = i });
        submitTask((TaskToDo){.taskFunction = ((i & 1) ? sum : multiplication),
                              .numOne = rand() % 100,
                              .numTwo = rand() % 100 });

    // 2. Wait for the threads to finish
            for (int i = 0; i < NUM_OF_PROCESSING_THREADS; i++)
                if (pthread_join(myThreads[i], NULL) != 0)
                    printf("Failed to join a thread %d\n", i);

        pthread_mutex_destroy(&mutexQueue);
        pthread_cond_destroy(&condQueue);

        return 0;
    }
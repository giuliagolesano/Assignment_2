#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "Task.h"

#define MAX_TASKS 10  // Numero massimo di task gestibili

class Scheduler : public Task{
  private:
    Task* tasks[MAX_TASKS]; // Array di puntatori alle task
    int nTasks;             // Numero di task registrate

  public:
    Scheduler();
    void init();
    void addTask(Task* task);
    void schedule();
};

#endif

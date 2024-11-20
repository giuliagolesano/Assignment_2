#include "Scheduler.h"

Scheduler::Scheduler() {
  nTasks = 0; // Nessuna task registrata inizialmente
}

void Scheduler::init() {
  nTasks = 0; // Reinizializza il numero di task
}

void Scheduler::addTask(Task* task) {
  if (nTasks < MAX_TASKS) {
    tasks[nTasks++] = task; // Aggiunge una nuova task
  }
}

void Scheduler::schedule() {
  for (int i = 0; i < nTasks; i++) {
    tasks[i]->tick(); // Esegue il metodo tick() di ogni task
  }
}

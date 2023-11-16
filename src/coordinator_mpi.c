#include <mpi.h>

#include "coordinator.h"

#define READY 0
#define NEW_TASK 1
#define TERMINATE -1

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Error: not enough arguments\n");
    printf("Usage: %s [path_to_task_list]\n", argv[0]);
    return -1;
  }

  // TODO: implement Open MPI coordinator
  MPI_Init(&argc, &argv);

  int procID, totalProcs;
  MPI_Comm_size(MPI_COMM_WORLD, &totalProcs);
  MPI_Comm_rank(MPI_COMM_WORLD, &procID);

  int num_tasks;
  task_t **tasks;
  if (read_tasks(argv[1], &num_tasks, &tasks)) {
    printf("Error reading task list from %s\n", argv[1]);
    MPI_Abort(MPI_COMM_WORLD, 1);
  }

  if (procID == 0) {
    // Manager process

    MPI_Status status;
    int nextTask = 0;
    int32_t message;

    while (nextTask < num_tasks) {
      MPI_Recv(&message, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
      int source = status.MPI_SOURCE;
      MPI_Send(&nextTask, 1, MPI_INT, source, 0, MPI_COMM_WORLD);
      nextTask++;
    }

    // Wait for all workers to finish
    for (int i = 1; i < totalProcs; i++) {
      MPI_Recv(&message, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
      int source = status.MPI_SOURCE;
      message = TERMINATE;
      MPI_Send(&message, 1, MPI_INT, source, 0, MPI_COMM_WORLD);
    }

  } else {

    // Worker node
    int32_t message;

    while (true) {
      message = READY;
      MPI_Send(&message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
      MPI_Recv(&message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

      if (message == TERMINATE) {
        break;
      }

      if (execute_task(tasks[message])) {
        printf("Task %d failed\n", message);
        return -1;
      }
    }
  }

  for (int i = 0; i < num_tasks; i++) {
    free(tasks[i]->path);
    free(tasks[i]);
  }
  free(tasks);

  MPI_Finalize();
  return 0;
}

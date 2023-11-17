#include <mpi.h>

#include "coordinator.h"

#define READY 0
#define NEW_TASK 1
#define TERMINATE -1

#include "coordinator.h"

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
  task_t **output_tasks;

  if (procID == 0) {

      int nextTask = 0;
      MPI_Status status;
      if (read_tasks(argv[1], &num_tasks, &output_tasks)) {
          return -1;
      }

      int32_t message;

      while (nextTask < num_tasks) {
          MPI_Recv(&message, 1, MPI_INT32_T, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
          int sourceProc = status.MPI_SOURCE;
          message = nextTask;
          MPI_Send(&message, 1, MPI_INT32_T, sourceProc, 0, MPI_COMM_WORLD);
          nextTask++;
  }

      for (int i = 0; i < totalProcs - 1; i++) {
          MPI_Recv(&message, 1, MPI_INT32_T, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
          int sourceProc = status.MPI_SOURCE;
          message = TERMINATE;
          MPI_Send(&message, 1, MPI_INT32_T, sourceProc, 0, MPI_COMM_WORLD);
      }

  } else {

      int32_t message;

      if (read_tasks(argv[1], &num_tasks, &output_tasks)) {
        return -1;
      }

      while (true) {
          message = READY;
          MPI_Send(&message, 1, MPI_INT32_T, 0, 0, MPI_COMM_WORLD);
          MPI_Recv(&message, 1, MPI_INT32_T, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
          if (message == TERMINATE) break;
          execute_task(output_tasks[message]);
      }
  }

  MPI_Finalize();
  return 0;
}

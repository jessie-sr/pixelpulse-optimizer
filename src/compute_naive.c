#include "compute.h"

// Function to flip a matrix in both dimensions
matrix_t* flip_matrix(matrix_t *original_matrix) {
    int rows = original_matrix->rows;
    int cols = original_matrix->cols;
    int *original_data = original_matrix->data;

    // Allocate memory for the flipped matrix
    matrix_t *flipped_matrix = malloc(sizeof(matrix_t));
    if (!flipped_matrix) {
        // handle memory allocation failure
        return NULL;
    }
    flipped_matrix->data = malloc(sizeof(int) * rows * cols);
    if (!flipped_matrix->data) {
        // handle memory allocation failure
        free(flipped_matrix);
        return NULL;
    }

    flipped_matrix->rows = rows;
    flipped_matrix->cols = cols;

    // Copy and flip elements
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int flipped_r = rows - 1 - r;
            int flipped_c = cols - 1 - c;
            flipped_matrix->data[flipped_r * cols + flipped_c] = original_data[r * cols + c];
        }
    }

    return flipped_matrix;
}


// Computes the convolution of two matrices
int convolve(matrix_t *a_matrix, matrix_t *b_matrix, matrix_t **output_matrix) {
  // TODO: convolve matrix a and matrix b, and store the resulting matrix in
  // output_matrix
  b_matrix = flip_matrix(b_matrix);

  int a_cols = a_matrix->cols;
  int b_cols = b_matrix->cols;
  int a_rows = a_matrix->rows;
  int b_rows = b_matrix->rows;
  int *a_data = a_matrix->data;
  int *b_data = b_matrix->data;

  int c_cols = a_cols - b_cols + 1;
  int c_rows = a_rows - b_rows + 1;

  // Allocate memory for output matrix data
  int c_num_data = c_cols * c_rows;
  int *c_data = malloc(sizeof(int) * c_num_data);

  if (c_data == NULL) {
    // handle memory allocation failure
    return -1;
  }

  for (int cr = 0; cr < c_rows; cr++) {
    for (int cc = 0; cc < c_cols; cc++) {
      int sum = 0;
      for (int br = 0; br < b_rows; br++) {
        for (int bc = 0; bc < b_cols; bc++) {
          int ar = cr + br;
          int ac = cc + bc;
          sum += a_data[ar * a_cols + ac] * b_data[br * b_cols + bc];
        }
      }
      c_data[cr * c_cols + cc] = sum;
    }
  }
  
  // Allocate memory for the output matrix struct
  *output_matrix = malloc(sizeof(matrix_t));
  if (*output_matrix == NULL) {
      // handle memory allocation failure
      free(c_data);
      return -1;
  }

  // Set the fields of the output matrix
  (*output_matrix)->rows = c_rows;
  (*output_matrix)->cols = c_cols;
  (*output_matrix)->data = c_data;

  return 0; // success

}

// Executes a task
int execute_task(task_t *task) {
  matrix_t *a_matrix, *b_matrix, *output_matrix;

  char *a_matrix_path = get_a_matrix_path(task);
  if (read_matrix(a_matrix_path, &a_matrix)) {
    printf("Error reading matrix from %s\n", a_matrix_path);
    return -1;
  }
  free(a_matrix_path);

  char *b_matrix_path = get_b_matrix_path(task);
  if (read_matrix(b_matrix_path, &b_matrix)) {
    printf("Error reading matrix from %s\n", b_matrix_path);
    return -1;
  }
  free(b_matrix_path);

  if (convolve(a_matrix, b_matrix, &output_matrix)) {
    printf("convolve returned a non-zero integer\n");
    return -1;
  }

  char *output_matrix_path = get_output_matrix_path(task);
  if (write_matrix(output_matrix_path, output_matrix)) {
    printf("Error writing matrix to %s\n", output_matrix_path);
    return -1;
  }
  free(output_matrix_path);

  free(a_matrix->data);
  free(b_matrix->data);
  free(output_matrix->data);
  free(a_matrix);
  free(b_matrix);
  free(output_matrix);
  return 0;
}

# PixelPulse Optimizer

## Overview
This project focuses on speeding up convolution operations, which are central to many applications like video processing. We specifically tackle the challenge of optimizing convolutions for video processing, using grayscale videos as our primary dataset.

### Application: Video Processing
- Grayscale videos are used, simplifying the problem to single-value pixels.
- Convolutions are applied to video frames for effects like blurring or sharpening.
- Techniques like Gaussian Blur are employed to process frames.

### Vectors and Matrices
- **Vector Representation:** Array of `int32_t`s.
- **Matrix Representation (`matrix_t`):**
  - `uint32_t rows`: Number of rows.
  - `uint32_t cols`: Number of columns.
  - `int32_t *data`: 1D array of matrix data in row-major format.

### .bin Files
- Matrices are stored in `.bin` files as a sequence of 4-byte integers.
- The first two integers indicate rows and columns, followed by the matrix elements.

### Task Structure (`task_t`)
- Represents a convolution operation.
- Identified by `path` to the folder containing the task.

## Testing
- Tests located in the `tests` directory.
- Custom tests can be added to `tools/custom_tests.py`.
- Use `make` commands to generate and run tests. e.g. use`make task_1 TEST=tests/my_custom_test` to run tests for task 1.

## Debugging
- Use `cgdb` or `valgrind` with the commands printed by `make` for debugging.

## Implementation Overview

1. **Basic Convolution Algorithm:**
   - Developed an initial implementation of 2D convolutions in `compute_naive.c`without optimization enhancements, which serves as a comparative benchmark for subsequent optimization techniques.

2. **Advanced Optimization Techniques:**
   - **SIMD Integration:** Enhanced `compute_naive.c` with SIMD instructions in `compute_optimized.c` to accelerate data processing, leveraging parallel data handling capabilities for increased computational efficiency.
   - **Parallel Processing with OpenMP:** Incorporated OpenMP directives to facilitate parallel execution of code segments, significantly reducing computation time by distributing workload across multiple processors.
   - **Algorithmic Refinement:** Conducted thorough analysis and refinement of the convolution algorithm to optimize performance, focusing on improving computational complexity and resource utilization.
   - **Open MPI Implementation:** Implemented parallelization using Open MPI in `coordinator_mpi.c`, extending optimization to a distributed computing environment for handling large-scale data processing with enhanced scalability and efficiency.

## Viewing Output
- Outputs are GIFs which can be viewed by transferring them to a local machine.
- Use `scp` to copy GIFs from the server to a local machine for viewing.
![Sample Output GIF](https://media.giphy.com/media/v1.Y2lkPTc5MGI3NjExZjV5dmh0cXY1eHdiMDZ6bzcxazJ1N3Z3bXB6cWN5ZGR4Nnl3eTZibSZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/RivH477vCCYiMNlUZJ/giphy-downsized-large.gif)

## Acknowledgements
This project is based on the content of project4 of CS61C Great Ideas of Computer Architecture (Machine Structures) at UC Berkeley. Thanks to all contributors and testers who helped in developing and refining this project!

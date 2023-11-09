import math

from framework import Test, TestSpec, Task, Matrix, randint
import filters


# This file will be updated with more tests when the autograder is released
@Test()
def test_small(test: TestSpec):
    for _ in range(10):
        rows_a = randint(15, 25)
        cols_a = randint(15, 25)
        rows_b = randint(5, 15)
        cols_b = randint(5, 15)
        test.add_task(
            Task(Matrix.random(rows_a, cols_a), Matrix.random(rows_b, cols_b))
        )


@Test()
def test_large(test: TestSpec):
    for _ in range(50):
        rows_a = randint(100, 100)
        cols_a = randint(100, 100)
        rows_b = randint(20, 40)
        cols_b = randint(20, 40)
        test.add_task(
            Task(Matrix.random(rows_a, cols_a), Matrix.random(rows_b, cols_b))
        )


@Test()
def test_gif_kachow_blur(test: TestSpec):
    test.add_gif("/home/ff/cs61c/fa23/proj4/gifs/kachow.gif",
                 filters.BlurFilter.create(size=17, sigma=7))


@Test()
def test_gif_kachow_sharpen(test: TestSpec):
    test.add_gif("/home/ff/cs61c/fa23/proj4/gifs/kachow.gif",
                 filters.SharpenFilter.create(size=3, sigma=1))

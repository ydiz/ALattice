## Basics

https://helloacm.com/simple-tutorial-with-openmp-how-to-use-parallel-block-in-cc-using-openmp/

`#pragma omp parallel` creates several threads to execute the block below it. Without braces, executed the next statement with multiple threads.

---
## compilation:

1. include `<omp.h>`
2. add `-fopenmp` gcc hello_openmp.c -fopenmp

---

## schedule
For loops where each iteration takes roughly equal time, **static schedules** work best, as they have little overhead.

For loops where each iteration can take very different amounts of time, **dynamic schedules**, work best as the work will be split more evenly across threads.

* Schedule clause  schedule(type[, chunk_size]). Chunks are groups of iterations (in contiguous order) that are assigned to threads
* Static schedule - each thread is assigned a fixed number of chunks (default)
* Dynamic schedule - each thread grabs "chunk" iterations until all iterations are done
    * Faster threads are assigned more iterations

----

## `_Pragma`

`_Pragma("argument")` is equivalent to`#pragma argument`  except **it can be used in macros**

`#pragma` is a preprocessor directive in its own right; it can't be used within a `#define` directive.

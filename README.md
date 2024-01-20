# How to Use the TBO Library

To incorporate the TBO Library into your own projects, follow the steps below:

## 1. Clone the Repository

Users can clone the repository to obtain the library files.

```bash
git clone https://github.com/your-username/tbo_lib.git
```

## 2. Navigate to the library directory:

Go to the newly cloned directory using the following command:

```bash
cd tbo_lib
```

## 3. Check the files:

Ensure that the files tbo_lib.h and tbo_lib.c are present in the directory. These are the main files of the library.


## 4. Integrate the library into your project:

Copy the tbo_lib.h and tbo_lib.c files to your project directory. Make sure they are in the same folder as your source code.


## 5.1. Include headers in your code:

At the beginning of your source code, include the tbo_lib.h header using the #include directive:

```bash
#include "tbo_lib.h"
```
## 5.2. Including library functions in your code

* Declare a variable of type BlockSizes. This will store the values of thread_x and thread_y to be passed to the kernel during execution.
* Inside the loop where the kernel is executed, before the kernel call, assign the previously created variable the function "before_kernel," passing the loop iterator and the declared variable of type BlockSizes as parameters in sequence.
* Next, insert the kernel call, passing to it the values "variable_name.bsize_x" and "variable_name.bsize_y" as parameters for the number of threads per block in the x and y dimensions, respectively. Measure the kernel execution time and store it in a variable of type double.
* After the kernel execution, assign the declared variable of type BlockSizes the return value of the "genetic_exec" function, passing the loop iterator and the variable storing the kernel execution time as parameters in sequence. 
* It is important to note the initialization value of the iterator so that when passed for the first time as a parameter to the functions, its value is equal to zero. If it is necessary to start the iterator with a different value than zero, such as 1, pass the value (iterator-1) as a parameter to the functions.

Example of inserting library functions into the code:

```bash
#include "tbo_lib.h"

int main()
{
    BlockSizes bsizes;
    double kernel_time;

    for (int it = 0; it <= 1000; it++)
    {
        bsizes = before_kernel(it, bsizes);

        kernel_time = kernel_execution(bsizes.bsize_x, bsizes.bsize_y);
  
        bsizes = genetic_exec(it, kernel_time);
    }

    return 0;
}

```
## 6. Compile your code:

When compiling your code, make sure to include the implementation file tbolib.c. This can be done by adding the file to the compiler command line. For example:

```bash
gcc your_code.c tbo_lib.c -o your_program
```
Replace your_code.c with the name of your source code file.

## 7. Run your code:

After successful compilation, execute the generated program:

```bash
./your_program
```

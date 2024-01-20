# How to Use the TBO Lib Library

To incorporate the TBO Lib library into your own projects, follow the steps below:

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

Ensure that the files tbo_lib.h and tbolib.c are present in the directory. These are the main files of the library.


## 4. Integrate the library into your project:

Copy the tbo_lib.h and tbolib.c files to your project directory. Make sure they are in the same folder as your source code.


## 5. Include headers in your code:

At the beginning of your source code, include the tbo_lib.h header using the #include directive:

```bash
#include "tbo_lib.h"
```
## 6. Compile your code:

When compiling your code, make sure to include the implementation file tbolib.c. This can be done by adding the file to the compiler command line. For example:

```bash
gcc your_code.c tbolib.c -o your_program
```
Replace your_code.c with the name of your source code file.

## 7. Compile your code:

After successful compilation, execute the generated program:

```bash
./your_program
```

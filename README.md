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
## 5.2. 
Declare uma variável do tipo BlockSizes. Esta armazenará os valores de thread_x e thread_y que serão passados para o kernel enviado à execução. 
Dentro do loop onde o kernel é executado, anterior à chamada do kernel faça a variável que você criou anteriormente receber a função "before_kernel", passando como parâmetros para ela, em sequência, o iterador do loop e a variável declarada do tipo BlockSizes. 
Em seguida insira a chamada do kernel, passando a ele os valores "nome_variavel.bsize_x" e "nome_variavel.bsize_y" como parâmetros de número de threads por bloco nas dimensões x e y respectivamente. Colete o tempo de execução do kernel e armazene-o em uma variável do tipo double. 
Após a execução do kernel, faça a variável declarada do tipo BlockSizes receber o retorno da execução da função "genetic_exec", passando como parâmetros para ela, em sequência, o iterador do loop e a variável que armazena o tempo de execução do kernel. 
É importante observar o valor de inicialização do iterador, de modo que, quando passado pela primeira vez como parâmetro das funções o seu valor seja igual a zero. Se for necessário iniciar o seu iterador com um valor diferente de zero, como por exemplo 1, passe o valor (iterador-1) como parâmetro para as funções. 

Exemplo de inserção das funções da biblioteca no código: 
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

## 7. Compile your code:

After successful compilation, execute the generated program:

```bash
./your_program
```

# Adding the functions to your code

# Programming concepts in scientific computing (MATH-458)
## Final Project: Numerical methods for eigenvalues computation

We implement five methods for eigenvalues computation:
- Power Method
- Inverse Power Method
- Power Method with shift
- Inverse Power Method with shift
- QR Method

and a reader to read matrices, vectors and scalars from file.

## Compilation and documentation
To compile the program, perform the following steps:
1. Open your terminal, and clone the repository on your machine using the command
```
git clone https://github.com/IvanBioli/PCSC_Project.git
```
2. In order to compile the tests you should first install *googletest*. From your terminal run the command
```
git submodule update --init 
```
3. Then you should clone the *eigen* library. From your terminal run the command 
```
git clone https://gitlab.com/libeigen/eigen.git
```
4. To build, from your terminal run the command
```
mkdir build
cd build
cmake ..
make
```
5. One central executable should be present in the `build` folder with name `main`.
6. Two test executable should be present in the `build` folder with names `test_methods` and `test_reader`. The first one
tests the methods for eigevalues computation, the second one tests the `FileReader` class.
7. To generate the documentation, move in the doc folder and lunch doxygen to generate the html webpage.
To do this, from your terminal run the command:
```
cd ../doc
doxygen Doxyfile
```
## Computation of eigenvalues
To compute the eigenvalues of a matrix, use the executable `main`.
Three arguments must be provided, following this order:
- the numerical method the user wants to apply. It can be `power` for the Power Method,
  `invpower` for the Inverse Power Method, `shiftpower` for the Power Method with shift,
  `shiftinvpower` for the Inverse Power Method with shift or `qr` for the QR Method.
- the path to the file in which the parameters of the method are provided. 
See the documentation for the format requirements of the input. Two examples are already 
provided in `input_files/real_input.txt` and `input_files/complex_input.txt`.
- the type of the input, `real` for real matrices and `complex` for complex matrices.

The output of the eigenvalues' computation will be written on standard output, preceded by the matrix and the eventual 
shift applied.

You can test our methods on two predefined inputs. 
For the real case, the following parameters are provided in `input_files/real_input.txt`
```
   [  1  28  48 -52 -8 ]
   [  2 -17 -42  24  2 ]
A =[  0  12  25 -12  0 ]
   [  2   0  -4  11  2 ]
   [ -4  -4  12  16  5 ]
   
x0 = [ 1 1 1 1 1 ]^T

shift = 4.5

tol = 1e-10

maxit = 1000   
```
The matrix `A` has eigenvalues `1`, `3`, `5`, `7`, `9`. 
Therefore, the numerical methods should approximate the following eigenvalues:
- QR Method: all the eigenvalues 
- Power Method: `9`
- Inverse Power Method: `1`
- Power Method with shift: `9` (the eigenvalue farthest from `4.5`)
- Inverse Power Method with shift: `5` (the eigenvalue closest to `4.5`)

This can be verified for the power method running from the `build` folder the command:
```
./main "power" "../input_files/real_input.txt" "real"
```
Similarly, the output of the other numerical methods can be checked.

For the complex case, the following parameters are provided in `input_files/complex_input.txt`
```
    [( -6, -1) ( 4, -4) (-1, -11) ( 8,  -8) (0, 0)]
    [(-10, -4) ( 5, -6) (-8, -18) ( 4, -10) (0, 0)]
A = [(  6,  2) (-4,  4) ( 1,  12) (-8,   8) (0, 0)]
    [(  1, -2) ( 6, -3) (15, -10) (15,  -7) (0, 0)]
    [(  8,  3) (-6,  3) (-6,  11) (-6,   9) (9, 2)]
   
x0 = [ 1 1 1 1 1 ]^T

shift = (4, 1)

tol = 1e-10

maxit = 1000   
```
where `(a, b)` represents the complex number  `a+ib`.
The matrix `A` has eigenvalues `(0, 1)`, `(3, -1)`, `(5, 0)`, `(7, -2)`, `(9, 2)`.
Therefore, the numerical methods should approximate the following eigenvalues:
- Power Method: `(9, 2)`
- Inverse Power Method: `(0, 1)`
- Power Method with shift: `(9, 2)` (the eigenvalue farthest from `(4, 1)`)
- Inverse Power Method with shift: `(5, 0)` (the eigenvalue closest to `(4, 1)`)

The QR method has not been implemented for the complex case.

This can be verified for the Power Method running from the `build` folder the command:
```
./main "power" "../input_files/complex_input.txt" "complex"
```
Similarly, the output of the other numerical methods can be checked.

To execute the tests for our implementation of the numerical methods and the reader, from the `build` folder run the 
commands:
```
./test_methods
./test_reader
``` 

## Report
Our report can be found in PDF format in the folder `report`.

## Authors
Ivan Bioli




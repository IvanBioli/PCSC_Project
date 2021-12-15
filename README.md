# Programming concepts in scientific computing (MATH-458)
## Final Project: Numerical methods for eigenvalues computation

We implement five methods for eigenvalues computation
- Power Method
- Inverse Power Method
- Power Method with shift
- Inverse Power Method with shift
- QR Method

and a reader to read matrices, vectors and scalars from file.

[![Status](https://img.shields.io/badge/status-active-success.svg)]()


## 📝 Table of Contents
- [⛏️ Quick start](#️-quick-start)
- [🔁 Compute Eigenvalues](#️-compute-eigenvalues)
- [✍️ Authors](#️-authors)


## ⛏️ Quick start
To compile the program, perform the following steps:
1. Open your terminal, and clone the repository on your machine using the command
```
git clone https://github.com/IvanBioli/PCSC_Project.git
```
3. In order to compile it you should first install *googletest*. From your terminal run the command
```
git submodule update --init 
```
3. Then you should clone the *eigen* library. From your terminal, run the command 
```
git clone https://gitlab.com/libeigen/eigen.git
```
4. To buid, from your terminal, run the command
```
mkdir build
cd build
cmake ..
make
```
5. One central executable should be present in the `build` folder with name `main.exe`.
6. Two test executable should be present in the `build` folder with names `test_methods.exe`and `test_reader.exe`. The first one tests the methods for eigevalues computation, the second one tests the `FileReader` class.
7. To generate the documentation, move in the doc folder and lunch doxygen to generate the html webpage.
To do this, run the command:
```
cd ../doc
doxygen Doxyfile
```
## 🔁 Compute Eigenvalues
To compute

## ✍️ Authors
Ivan Bioli




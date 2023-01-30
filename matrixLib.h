/*
Author: Merve Öğ 
Mail: merve.og@stu.fsm.edu.tr
Date:10/12/2022
File:Project1.c
Description: Bu projede belirli matris ve vectör işlemlerini yapan fonksiyonları dinamik bellek yönetimi konusundan yararlanarak kodladım.
Assisgnment: 1.proje
*/
#ifndef MYLIB_H
#define MYLIB_H
float *returnVector(int);
float **returnMatrix(int, int);
void freeMatrix(float **, int);
float mean(float *, int);
float correlation(float *, float *, int);
float covariance(float *, float *, int);
float **matrixMultiplication(float **, float **, int, int, int, int);
float **matrixTranspose(float **, int, int);
float *rowMeans(float **, int, int);
float *columnMeans(float **, int, int);
float **covarianceMatrix(float **, int, int);
float determinant(float **, int);
void printVector(float *, int);
void printMatrix(float **, int, int);
void matrixFill(float **, int, int, int);
void vectorFill(float *, int, int);
#endif

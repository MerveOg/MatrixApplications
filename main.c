/*
Author: Merve Öğ 
Mail: merve.og@stu.fsm.edu.tr
Date:11/12/2022
File:Project1.c
Description: Bu projede belirli matris ve vectör işlemlerini yapan fonksiyonları dinamik bellek yönetimi konusundan yararlnarak kodladım.
Assisgnment: 1.proje
*/

#include <stdio.h>
#include <stdlib.h>
#include "matrixLib.h"
#include <time.h>

int main(int argc, char *argv[])
{

    int seed;

    if (argc == 2) //Eğer iki adet argüman varsa
    {
        seed = atoi(argv[1]); //seed'e argümanın 2.değerini integera cast ederek atıyor.
    }
    else
    {
        printf("There are lost or more arguments!"); //Eğer argüman 2 adet değilse eksik ya da fazla argüman girildiyse uyarısı veriliyor.
        exit(1);
    }

    float *arr2;
    arr2 = returnVector(6);
    vectorFill(arr2, 6, seed);

    printf("\n-------------------------------------------------\n");
    printf("Vector1: \n");
    float *arr;
    arr = returnVector(6);
    vectorFill(arr, 6, seed);
    printVector(arr, 6);
    printf("\nMean of this vector is: %f\n", mean(arr, 6));

    printf("\n-------------------------------------------------\n");

    printf("\nVector1:\n");
    printVector(arr, 6);
    printf("\n\nVector2:\n");
    printVector(arr2, 6);
    printf("\n");
    float resultCovarieance = covariance(arr, arr2, 6);
    printf("\nCovariance of Vector1 and Vector2 vector: %f", resultCovarieance);
    float resultCorrelation = correlation(arr, arr2, 6);
    printf("\nCorrelation of Vector1 and Vector2: %f\n", resultCorrelation);

    printf("\n-------------------------------------------------\n");
    printf("\n\n");

    printf("Matrix:\n");
    float **matrix1;
    matrix1 = returnMatrix(3, 4);
    matrixFill(matrix1, 3, 4, seed);
    printMatrix(matrix1, 3, 4);
    printf("\n");

    printf("Row mean array: ");
    printVector(rowMeans(matrix1, 3, 4), 3);

    printf("\nColumn mean array: ");
    printVector(columnMeans(matrix1, 3, 4), 4);

    printf("\n");
    printf("\nTranspoze Matrix: \n");
    printMatrix(matrixTranspose(matrix1, 3, 4), 4, 3);

    printf("\nMatrix Multiplication(Matrix*TranspozeMatrix): \n");
    printMatrix(matrixMultiplication(matrix1, matrixTranspose(matrix1, 3, 4), 3, 4, 4, 3), 3, 3);

    printf("\n");
    printf("\n-------------------------------------------------\n");

    float **matrix2;
    matrix2 = returnMatrix(3, 3);

    printf("\nNew Matrix for calculate determinant: \n");
    matrixFill(matrix2, 3, 3, seed);
    printMatrix(matrix2, 3, 3);

    printf("\nDeterminant of new matrix: %f \n", determinant(matrix2, 3));

    printf("\nCovariance matrix of new matrix: \n");
    printMatrix(covarianceMatrix(matrix2, 3, 3), 3, 3);
    printf("\n-------------------------------------------------\n");

    freeMatrix(matrix1, 3);
    freeMatrix(matrix2, 3);
    free(arr);
    free(arr2);

    return 0;
}

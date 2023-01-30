/*
Author: Merve Öğ 
Mail: merve.og@stu.fsm.edu.tr
Date:11/12/2022
File:Project1.c
Description: Bu projede belirli matris ve vectör işlemlerini yapan fonksiyonları dinamik bellek yönetimi konusundan yararlnarak kodladım.
Assisgnment: 1.proje
*/
#include <stdlib.h>
#include <stdio.h>
#include "matrixLib.h"
#include <math.h>
#include <time.h>

//Bu fonksiyon dinamik olarak bir vektör oluşturuyor.
float *returnVector(int size)
{

  float *arr = (float *)malloc(size * sizeof(float));

  return arr;
}


//Bu fonksiyon vektöre boyutuna göre değerler atıyor.
void vectorFill(float *vec, int N, int seed)
{
  srand(seed);
  for (int i = 0; i < N; i++)
  {
    vec[i] = (float)(rand() % 10 + 1);
  }
}


//Bu fonksiyon vektörü ekrana basıyor.
void printVector(float *vec, int size)
{

  for (int i = 0; i < size; i++)
  {
    printf("%.2f ", vec[i]);
  }
}


//Bu fonksiyon dinamik olarak 2 boyutlu bir matris oluşturuyor.
//Öncelikle satır için yer oluşturdum ardından satırlardan yararlanarak sütunları da oluşturdum.
float **returnMatrix(int row, int col)
{

  float **twoDimensionalArray = (float **)malloc(sizeof(float *) * row);

  for (int i = 0; i < row; i++)
  {
    twoDimensionalArray[i] = (float *)malloc(sizeof(float) * col);
  }

  return twoDimensionalArray;
}


//Bu fonksiyon matris elemanlarına değerler atıyor.
//Matrisler satır ve sütunlardan oluştuğu için iki for kullandım.
void matrixFill(float **mat, int row, int col, int seed)
{
  srand(seed);
  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < col; j++)
    {
      mat[i][j] = (float)(1 + rand() % 10);
    }
  }
}


//Bu fonksiyon matrisi ekrana basıyor.
void printMatrix(float **mat, int row, int col)
{

  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < col; j++)
    {
      printf("%.2f ", mat[i][j]);
    }
    printf("\n");
  }
}


//Bu fonksiyon geriye vektörün ortalamasını döndürüyor.
//Bu hesabı vektördeki değerleri toplayıp toplam eleman sayısına bölerek hesaplıyor.
float mean(float *vec, int size)
{

  float sum = 0, result = 0;

  for (int i = 0; i < size; i++)
  {
    sum += vec[i];
  }

  result += sum / size;
  return result;
}


float covariance(float *vec, float *vec2, int size)
{

  float sum = 0;
  float result = 0;

  for (int i = 0; i < size; i++)
  {
    //Verilen vectörlerdeki her bir elemandan o vektörün ortalamasını çıkardım ve bu değerleri her defasında çarpıp toplama ekledim.
    sum += (vec[i] - mean(vec, size)) * (vec2[i] - mean(vec2, size));
  }
  //Ardından bu değeri (vectör boyutu -1) 'e bölerek hesapladım.
  result += sum / (size - 1);

  return result;
}


float correlation(float *vec, float *vec2, int size)
{

  float sumx = 0, sumy = 0;
  float resultx = 0, resulty = 0;
  float correlationResult = 0;

  for (int i = 0; i < size; i++)
  {
    //Burada elemanlardan vector ortalamasını cıkarıp karesini alıyorum ve değişkene atıyorum.
    sumx += pow((vec[i] - mean(vec, size)), 2);
    sumy += pow((vec2[i] - mean(vec2, size)), 2);
  }

  resultx = sqrt(sumx / (size - 1)); //Sonucu size-1 'e bölüyorum ve karekökünü alıyorum.
  resulty = sqrt(sumy / (size - 1)); //Sonucu size-1'e bölüyorum ve karekökünü alıyorum.
  //Burada iki vectörün covariance değerini bulduğum iki değerin çarpımına bölüp değere atıyorum.
  correlationResult = (covariance(vec, vec2, size)) / (resultx * resulty);

  return correlationResult;
}


//Bu fonksiyon heap'ten matris için alınan alanı geri iade ediyor.
//Bu işlemi gerçekleştirirken önce satırları geri iade ediyoruz.
//Ardından yeniden free işlemini gerçekleştirmemiz gerekiyor.
void freeMatrix(float **mat, int row)
{

  for (int i = 0; i < row; i++)
  {
    free(mat[i]);
  }
  free(mat);
}


//Bu fonksiyon verilen matrisin transpozesini return ediyor.
//Böylelikle yeni oluşturulan matrisin sütunları ilk matrisin satır değerleri olmuş oluyor ve ilk matrisin transpozesi bulunuyor.
float **matrixTranspose(float **mat, int row, int col)
{

  float **result = returnMatrix(col, row);

  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < col; j++)
    {
      result[j][i] = mat[i][j];
    }
  }

  return result;
}


float *rowMeans(float **mat, int row, int col)
{

  float *result = returnVector(row);
  float sum = 0;

  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < col; j++)
    {
      sum += mat[i][j]; //sum değişkenine satır değerlerini ekledim.
    }

    result[i] = sum / col; // sum/col ile satır ortalamasını hesapladım ve vectöre atadım.
    sum = 0;               // Farklı bir satıra geçtiğinde toplamı 0 yaptım ki satırların ayrı ayrı ortalamalarını bulabileyim.
  }

  return result;
}


float *columnMeans(float **mat, int row, int col)
{

  float *result = returnVector(col);

  //verilen matrisin transpozesini aldıktan sonra o matrisin satırlarının satır ortalamasını hesapladım ve değerleri vectörde tuttum.
  //Böylelikle ilk matrisin sütun ortalamasını bulmuş oldum.
  result = rowMeans(matrixTranspose(mat, row, col), col, row);

  return result;
}


float **matrixMultiplication(float **mat1, float **mat2, int row1, int col1, int row2, int col2)
{

  float **multiMatrix = returnMatrix(row1, col2);
  float multiResult = 0;

  if (col1 == row2) //İlk matrisin sütun sayısı ile 2.matrisin satır sayısı aynı ise çarpım hesaplanabilir.
  {
    int i, j;
    //Her satırdaki belli indeksteki değerle diğer matrisin sütunundaki belli indeksteki değeri
    //Çarpmamız gerektiği için 3.bir for daha gerekti.
    int x;

    for (i = 0; i < row1; i++)
    {
      for (j = 0; j < col2; j++)
      {
        multiMatrix[i][j] = 0;

        for (int x = 0; x < row2; x++)
        {
          //Matris çarpımında bir matrisin satırdaki a indeksindeki değer ile diğer matrisin
          //Sütunundaki a indeksindeki değer çarpılır ve bir değere eklenir.(a -> örnek indeks).
          multiMatrix[i][j] += mat1[i][x] * mat2[x][j];
        }
      }
    }
    return multiMatrix;
  }
  else
  {
    exit(1);
  }
}


/*
//Determinant için yazdığım ilk kodum.
float determinant(float **mat, int row)
{
  int col;
  col = row + 2;
  int a = 3;
  float sum1 = 1, sum2 = 1, sum3 = 1;
  float difference1 = 1, difference2 = 1, difference3 = 1;
  int m, k;
  float result = 0;

  //Burada 3*3'lük matrisimi realloc yardımıyla 3*5'lik matrise genişletiyorum.
  for (int i = 0; i < row; i++)
  {
    mat[i] = realloc(mat[i], sizeof(float) * col);
  }

  //Burada eklediğim 2 sütuna matrisin ilk 2 sütun değerlerini ekliyorum.
  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      mat[i][a] = mat[i][j];
      a++;
    }
    a = 3;
  }
  //
  for (k = 0; k < row; k++)
  {
    //Sarros kuralında sola dogru carpımda 3 tane carpımı topluyoruz
    //Ben bunlar arasında aşağıdaki gibi bir örüntü yakaladım.
    sum1 *= mat[k][k];
    sum2 *= mat[k][k + 1];
    sum3 *= mat[k][k + 2];
  }
    //Sarros kuralında sola dogru carpımda 3 tane carpımı topluyoruz. Sonra çıkarıyoruz.
    //Ben bunlar arasında aşağıdaki gibi bir örüntü yakaladım.
  for (int m = 0; m < row; m++)
  {
    difference1 *= mat[m][2 - m];
    difference2 *= mat[m][3 - m];
    difference3 *= mat[m][4 - m];
  }

  result = (sum1 + sum2 + sum3) + (-difference1 - difference2 - difference3);

  return result;
}
*/


float determinant(float **mat, int row)
{
  int col;
  col = row + 2;
  int a = 3;
  float product = 1;
  float product2 = 1;
  float result = 0;
  int x, y;
  float sum = 0, difference = 0;

  //Burada 3*3'lük matrisimi realloc yardımıyla 3*5'lik matrise genişletiyorum.
  for (int i = 0; i < row; i++)
  {
    mat[i] = realloc(mat[i], sizeof(float) * col);
  }

  //Burada eklediğim 2 sütuna matrisin ilk 2 sütun değerlerini ekliyorum.
  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      mat[i][a] = mat[i][j];
      a++;
    }
    a = 3;
  }

  //Burada sarros kuralındaki toplama kısmını hesaplıyorum.
  //Çarpraz bir şekilde matris elemanlarını çarpıp diğer sütuna geçmem gerekiyor.
  //Dış for çarpraz çarpım gerçekleştikten sonra diğer sütuna geçmeyi sağlıyor.
  for (int i = 0; i < row; i++)
  {

    x = i;       //Sarros hesaplarken çarpraz çarpımda örüntü yakaladım ve x'i her seferinde i'ye eşitledim
    product = 1; //Her seferinde bu değeri 1'e eşitlemem gerekir ki önceki değer üzerinden işlem yapmasın.

    for (int j = 0; j < row; j++)
    {
      product *= mat[j][x]; //Burada çarpraz çarpım yapıyor.
      //İç for bitmeden i artmayacak ondan dolayı x'i bir arttırmam gerekiyor(örüntü gereği)
      x++;
    }
    sum += product;
  }

  //Burada sarros kuralındaki toplama kısmını hesaplıyorum.
  for (int i = 0; i < row; i++)
  {
    //Sarros hesaplarken çarpraz çarpımda örüntü yakaladım ve y'yi her seferinde i'ye eşitledim
    y = i;
    product2 = 1; //Her seferinde bu değeri 1'e eşitlemem gerekir ki önceki değer üzerinden işlem yapmasın.

    //Burada çarpraz çarpımı alt kısımdan hesaplamaya başlatacağımız için j = row-1 dedim.
    for (int j = row - 1; j >= 0; j--)
    {
      product2 *= mat[j][y]; //Burada çarpraz çarpım yapıyor.
      y++;
    }
    difference += product2; //Yaptığım çarpraz çarpımı her seferinde bir değişkende topladım.
  }
  result = sum - difference;
  return result;
}


float **covarianceMatrix(float **mat, int row, int col)
{

  if (row == col) //Covariance matrixler simetrik matrix olduğundan kare matrix olmalılar.
  {
    float *vector = returnVector(col);
    vector = columnMeans(mat, row, col);
    float **result = returnMatrix(col, row);
    float **temp = returnMatrix(col, row);
    float **product = returnMatrix(col, row);
    temp = mat;

    for (int i = 0; i < row; i++)
    {
      for (int j = 0; j < col; j++)
      {
        temp[j][i] -= vector[i]; //Elemanlardan bulunduğu sütunun sütun ortalamasını çıkardım.
      }
    }
    //temp matrisinin transpozesini aldım ve mat matrisi ile matrix çarpıımı uyguladım(mat*temp)
    product = matrixMultiplication(mat, matrixTranspose(temp, col, row), row, col, row, col);

    for (int i = 0; i < row; i++)
    {
      for (int j = 0; j < col; j++)
      {
        //product matrisindeki her bir elemanı row değerine böldüm ve yeni bir matrise atadım.
        result[i][j] = product[i][j] / (float)row;
      }
    }
    return result;
  }
  else
  {
    exit(1);
  }
}

// #include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "include/filter.h"

// #include "include/coefficients.h"

// int32_t multiply(int32_t x, int32_t y) {
//     // printf("multiply\n");
//     int64_t x64 = x;
//     int64_t y64 = y;
//     // if (x64 >= 2147483648 || y64 >= 2147483648) {
//     //     printf("Overflow\n");
//     // }
//     int64_t result = MUL(x64, y64);
//     // if (result >= 2147483648) {
//     //     printf("REsult Overflow\n");
//     // }
//     return (int32_t)result;
// }

int32_t multiply(int32_t x, int32_t y) {
    int64_t x64 = x;
    int64_t y64 = y;
    int64_t result = x64 * y64;
    result = result >> (FRACTION_BITS - 1);
    return (int32_t)result;
}

/*
//matrixMultiplication
int32_t * matrixMultiplication(const int32_t (*A)[N], int32_t (*B), int AHeight, int AWidth, int BHeight, int BWidth){
    int32_t *outArray = (int32_t*)malloc(sizeof(int32_t *) * AHeight);
    for(int jj=0; jj<AHeight; jj++)
            outArray[jj] = 0;
    for(int jj=0; jj<AHeight; jj++){
        for(int kk=0; kk<AWidth; kk++){
            outArray[jj] += multiply(A[jj][kk], B[kk]);
            // if (outArray[jj] > 2147483648){
            //     printf("value is to large ");
            // }            
        }
    }
    return outArray;
}

int32_t * MulS(const int32_t (*A)[N], int32_t (*B), int AHeight, int AWidth, int BHeight, int BWidth, int k){
    int32_t *outArray = (int32_t*)malloc(sizeof(int32_t *) * AHeight);
    for(int jj=0; jj<AHeight; jj++)
            outArray[jj] = 0;
    for(int jj=0; jj<AHeight; jj++){
        for(int kk=0; kk<AWidth; kk++){
            if (B[kk] == 1){
                outArray[jj] += A[jj][kk];
            }
            else if (B[kk] == 0){
                outArray[jj] -= A[jj][kk];
            }
            // else {
            //     printf("Error in MulS function at %d\n", k);
            // }
        }
    }
    return outArray;
}



*/



// struct dataMatrix readMatrix(char path[]){

//     // int array[100][100];
//     int height, width, ii, jj;
    
//     FILE *fp;
//     // char buff[255];

//     fp = fopen(path, "r");

//     if(fscanf(fp, "%d%d", &height, &width) != 2)
//         printf("error the first line is wrong\n");

//     // printf("height: %d, width: %d\n", height, width);
//     int32_t **matrix;

//     matrix = malloc(sizeof(int32_t *) * height);
//     for (int i = 0; i < height; i++)
//         matrix[i] = malloc(sizeof(int32_t) * width);

    
//     for(jj=0; jj<height; jj++)
//         for(ii=0; ii<width; ii++)
//             fscanf(fp, "%d", &matrix[jj][ii]);
    
//     fclose(fp);

//     struct dataMatrix output;

//     output.data = matrix;
//     output.Height = height;
//     output.Width = width;

//     // Dette bør legges til, men er feil nå
//     // for (int i = 0; i < batchData.constMatrix[Bf].Height; i++)
//         // free(matrix[i]);
//     // free(matrix);

//     return output;

// }


// void printMatrix(struct dataMatrix input){
//     printf("Matrix = \n");
//     // printf("Height: %d, Width: %d\n", input.Height, input.Width);
//     // printf("input.data[0][0]=%d\n", input.data[0][0]);
//     for(int jj=0; jj<input.Height; jj++){
//       for(int ii=0; ii<input.Width; ii++)
//          printf ("%d ", input.data[jj][ii]);
//       printf("\n");
//    }
// }
// void printMatrixInt(struct dataMatrix input){
//     printf("Matrix = \n");
//     for(int jj=0; jj<input.Height; jj++){
//       for(int ii=0; ii<input.Width; ii++)
//          printf ("%d ", input.data[jj][ii]);
//       printf("\n");
//     }
// }

// int32_t readConstant(char path[]){
//     FILE    *textfile;
//     char    *text;
//     long    numbytes;
     
//     textfile = fopen(path, "r");
//     if(textfile == NULL)
//         return 1;
     
//     fseek(textfile, 0L, SEEK_END);
//     numbytes = ftell(textfile);
//     fseek(textfile, 0L, SEEK_SET);  
 
//     text = (char*)calloc(numbytes, sizeof(char));   
//     if(text == NULL)
//         return 1;
 
//     fread(text, sizeof(char), numbytes, textfile);
//     fclose(textfile);
 

//     int32_t out = atof(text);

//     return out;
// }


// int32_t * FirFiltering(struct batchVariables filterData);

// struct dataMatrix batchEstimator(struct batchVariables filterData){
//     // int32_t *outArray = malloc(sizeof(int32_t *) * size);
    
//     // struct dataMatrix M_arr;
//     // int32_t **M_arr;
//     int32_t M_arr[size+1][N] = {0};
//     // M_arr.Height = size+1;
//     // M_arr.Width = N;
    
//     //Initialize to zero
//     // for(int jj=0; jj<size+1; jj++)
//     //     for(int ii=0; ii<N; ii++)
//     //         M_arr[jj][ii] = 0;

    
//     // int32_t *M_curl;
//     // M_curl = malloc(sizeof(int32_t) * N);
//     int32_t M_curl[N] = {0};

//     for (int k1 = 1; k1 < size; k1++){
//         int32_t *tempAfM = matrixMultiplication(Af, M_arr[k1-1], Af_Height, Af_Width, size+1, N);
//         int32_t *tempBfs = matrixMultiplication(Bf, S[k1-1], Bf_Height, Bf_Width, S_Height, S_Width);
//         for(int jj=0; jj<N; jj++){
//             M_arr[k1][jj] = tempAfM[jj] + tempBfs[jj];
//             // printf("M_arr[%d][%d]: %d ", k1, jj, M_arr[k1][jj]);
//             // printf("tempAfM[%d]: %d ", jj, tempAfM[jj]);
//             // printf("tempBfs[%d]: %d\n", jj, tempBfs[jj]);
//         }
//     }
    

    
//     // int32_t *tempAbM;
//     // tempAbM = malloc(sizeof(int32_t) * Ab_Height);
//     // int32_t *tempBbs;
//     // tempBbs = malloc(sizeof(int32_t) * Bb_Height);
//     int32_t tempMM[N] = {0};
//     // int32_t *tempMM;
//     // tempMM = malloc(sizeof(int32_t) * N);
//     int32_t output[N] = {0};
//     // int32_t *output;
//     // output = malloc(sizeof(int32_t) * size);
//     for (size_t k2 = size; k2 > 1; k2--)
//     {
//         // printMatrix(filterData.constMatrix[Ab]);
//         // printf("Ab[0][0] = %d\n", Ab[0][0]);
//         int32_t *tempAbM = matrixMultiplication(Ab, M_arr[k2], Ab_Height, Ab_Width, size+1, N);
//         int32_t *tempBbs = matrixMultiplication(Bb, S[k2-1], Bb_Height, Bb_Width, S_Height, S_Width);
        
//         for(int jj=0; jj<N; jj++){
//             M_curl[jj] = tempAbM[jj] + tempBbs[jj];
//             // printf("jj = %d, %d\n",jj, tempAbM[jj] + tempBbs[jj]);
//         }

//         for(int jj=0; jj<N; jj++){
//             tempMM[jj] = M_curl[jj] - M_arr[k2-1][jj];
//             // printf("jj = %d, %d\n",jj, tempMM[jj]);
//         }
//         // output.data[k2-1] = WT* tempMM
//         // int32_t *temp;
//         // temp = malloc(sizeof(int32_t) * WT_Height);
//         int32_t *temp = matrixMultiplication(WT, tempMM, WT_Height, WT_Width, N, 1);
        
//         output[k2-1] = temp[0];
//         for(int jj=0; jj<N; jj++)
//             M_arr[k2-1][jj] = M_curl[jj];

        

        

//     }
//     //print m_curl
//     // for(int jj=0; jj<N; jj++)
//     //     printf("jj = %d, %d\n",jj, M_curl[jj]);
//     //print output
    
//     // free(tempAbM);
//     // free(tempBbs);
//     // printMatrix(output);    
    
//     // output = mulMatrix(filterData.constMatrix[Bf], filterData.s);

//     // printf("S = %f\n", S[0][0]);
//     struct dataMatrix outputMatrix;
//     outputMatrix.Height = size;
//     outputMatrix.Width = 1;
//     outputMatrix.data = malloc(sizeof(int32_t *) * outputMatrix.Height);
//     for (int i = 0; i < outputMatrix.Height; i++)
//         outputMatrix.data[i] = malloc(sizeof(int32_t) * outputMatrix.Width);
    
//     // outputMatrix.data = output;
//     for(int jj=0; jj<outputMatrix.Height; jj++)
//         outputMatrix.data[jj][0] = output[jj];
    
//     return outputMatrix;
// }




// struct dataMatrix parallelBatchEstimator(struct batchVariables filterData){
    

// }



// struct dataMatrix mulMatrix(struct dataMatrix A, struct dataMatrix B){
//     struct dataMatrix out;
//     if (A.Width != B.Height){
//         printf("Error Multiplication not possible\n");
//     }
//     out.Height = A.Height;
//     out.Width = B.Width;
//     out.data = malloc(sizeof(int32_t *) * out.Height);
//     for (int i = 0; i < out.Height; i++)
//         out.data[i] = malloc(sizeof(int32_t) * out.Width);

//     for(int i = 0; i < A.Height; i++){
//         for(int j = 0; j < B.Width; j++){
//             out.data[i][j] = 0;
//             for(int k = 0; k < B.Height; k++){
//                 out.data[i][j] += A.data[i][k] * B.data[k][j];
//             }
//         }  
//     }
//     return out;
// }






// int32_t * FirFiltering(struct batchVariables filterData){
//     // Init fir filter variables
//     int samples = S_Height - filterData.constants[K] ;
//     int32_t *outArray = malloc(sizeof(int32_t *) * samples);
//     // Initialize to 0
//     for(int i = 0; i < samples; i++){
//         outArray[i] = 0;
//     }
//     // Fir filter algorithm
//     int k;
//     for (k = 0; k < samples; k++){
//         for (int i = 0; i < filterData.constants[K]; i++){ 
//             for (int j = 0; j < filterData.h.Width; j++)
//             {
//                 if (S[k+i][j] == 1)
//                 {
//                     outArray[k] += filterData.h.data[i][j] * 1;
//                 } else
//                 {
//                     outArray[k] += filterData.h.data[i][j] * -1;
//                 }
//                 // outArray[k] += filterData.h.data[i][j] * S[k+i][j];
//             }
//         }
//     }

//     return outArray;
// }

// int32_t * FirFilteringDownsample(struct batchVariables filterData){
//     // Init fir filter variables
//     int samples = S_Height - filterData.constants[K] ;
//     int32_t *outArray = malloc(sizeof(int32_t *) * samples);
//     // Initialize to 0
//     for(int i = 0; i < samples; i++){
//         outArray[i] = 0;
//     }
//     // Fir filter algorithm
//     int k;
//     // printf("DSR = %d\n", filterData.constants[DSR]);
//     // printf("Samples = %d\n",samples/filterData.constants[DSR]);
//     for (k = 0; k < (samples/filterData.constants[DSR])-10; k++ ){
//         // printf("k = %d k*DSR = %d\n",k,k*filterData.constants[DSR]);
//         for (int i = 0; i < filterData.constants[K]; i++){ 
//             // printf("i = %d\n",i);
//             for (int j = 0; j < filterData.h.Width; j++)
//             {
//                 if (S[(k*filterData.constants[DSR])+i][j] == 1)
//                 {
//                     outArray[k] += filterData.h.data[i][j] * 1;
//                 } else
//                 {
//                     outArray[k] += filterData.h.data[i][j] * -1;
//                 }
//                 // outArray[k] += filterData.h.data[i][j] * S[k+i][j];
//             }
//         }
//     }

//     return outArray;
// }
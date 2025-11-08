#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {//open the 2 files to calculate the error between the matrices
    FILE *f1 = fopen("intensitymatrix.txt", "r");
    FILE *f2 = fopen("matrix.txt", "r");
    if (!f1 || !f2) {
        printf("Cannot open files. \n");
        return 1;
    }

    int rows1, colms1, rows2, colms2;
    fscanf(f1, "%d %d", &rows1, &colms1);
    fscanf(f2, "%d %d", &rows2, &colms2);
    //rows and coloumns of two matrices should be same to calculate the error

    if (rows1 != rows2 || colms1 != colms2) {
        printf("Matrix sizes do not match. \n");
        fclose(f1);
        fclose(f2);
        return 1;
    }

    double entry1, entry2, sum = 0;//entry1 is elements of matrix1 and entry2 is elements of matrix2
    for (int i = 0; i < rows1 * colms1; i++) {
        if (fscanf(f1, "%lf", &entry1) != 1 || fscanf(f2, "%lf", &entry2) != 1) {
            printf("Error reading matrix data. \n");
            fclose(f1);
            fclose(f2);
            return 1;
        } //sum of squares of difference between the entries of two matrices  
        double diff = entry1 - entry2;
        sum += diff * diff;
    }

    fclose(f1);
    fclose(f2);
    printf("Frobenius norm of error: %.6f \n", sqrt(sum));
    return 0;
}


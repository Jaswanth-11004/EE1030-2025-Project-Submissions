#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "functions.h"

int main(){
    srand(42);
    printf("Enter the k value:");
    int m,n,k;
    //enter the value of k
    scanf("%d",&k);
    FILE* f=fopen("intensitymatrix.txt","r");
    if(!f){
    printf("intensitymatrix.txt not found\n");
    return 1;
    }
    //takes the value of number of rows and number of coloumns from the input file 
    fscanf(f,"%d%d",&m,&n);
    //allocate the memory for 2-d matrix
    double** A=alloc(m,n);
    for(int i=0;i<m;i++){
    for(int j=0;j<n;j++){
    fscanf(f,"%lf",&A[i][j]);
    }}
    fclose(f);
    
//creating 
    double** Omega=alloc(n,k);
    for(int i=0;i<n;i++){
    for(int j=0;j<k;j++){
    Omega[i][j]=randn();
}}

    double** Y=alloc(m,k); 
    //multiplication of A and omega
    matmultiply(A,Omega,Y,m,n,k);
    //orthonormalize the matrix Y
    gram_schmidt(Y,m,k);


    double** Qt=alloc(k,m); 
    //taking transpose of Y
    transpose(Y,Qt,m,k);
    double** B=alloc(k,n);
    //multiplication of Qt and B
    matmultiply(Qt,A,B,k,m,n);

    
    double** Bt=alloc(n,k); 
    transpose(B,Bt,k,n);
    double** BBt=alloc(k,k);
    matmultiply(B,Bt,BBt,k,n,k);

    double** U_t=alloc(k,k); 
    double* eval=malloc(k*sizeof(double));
    jacobi(BBt,eval,U_t,k);


    for(int i=0;i<k-1;i++){
    int idx=i;
    for(int j=i+1;j<k;j++)if(eval[j]>eval[idx])idx=j;
        if(idx!=i){
        //exchanging the values of eval[i]=eval[idx]
        double tmp=eval[i];
        eval[i]=eval[idx];eval[idx]=tmp;
        for(int r=0;r<k;r++){
        double t=U_t[r][i];U_t[r][i]=U_t[r][idx];U_t[r][idx]=t;
        }}}

    double* S=malloc(k*sizeof(double));
    for(int i=0;i<k;i++){
    S[i]=sqrt(fmax(eval[i],0));
}
double** tmp=alloc(n,k);
matmultiply(Bt,U_t,tmp,n,k,k);
 double** V=alloc(n,k);
 for(int j=0;j<k;j++){
 double inv;
 if(S[j]>1e-12){
 inv=1.0/S[j];
 }else{//if inv is so small then it can take as zero
 inv=0;
 }
 for(int i=0;i<n;i++){
 V[i][j]=tmp[i][j]*inv;
 }}

    double** U=alloc(m,k); 
    matmultiply(Y,U_t,U,m,k,k);

    double** US=alloc(m,k);
    for(int i=0;i<m;i++)for(int j=0;j<k;j++)US[i][j]=U[i][j]*S[j];
    double** Vt=alloc(k,n); 
    transpose(V,Vt,n,k);
    double** Arec=alloc(m,n);
    matmultiply(US,Vt,Arec,m,k,n);

  //printing  array in output file
    FILE* out=fopen("matrix.txt","w");
    fprintf(out,"%d %d\n",m,n);
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){ fprintf(out,"%.4f ",Arec[i][j]);
}   fprintf(out,"\n");
    }
    fclose(out);
    printf("matrix saved to matrix.txt\n");

    freeMat(A,m);freeMat(Omega,n);freeMat(Y,m);freeMat(Qt,k);freeMat(B,k);
    freeMat(Bt,n);freeMat(BBt,k);freeMat(U_t,k);free(eval);free(S);
    freeMat(tmp,n);freeMat(V,n);freeMat(U,m);freeMat(US,m);freeMat(Vt,k);freeMat(Arec,m);
    return 0;
}


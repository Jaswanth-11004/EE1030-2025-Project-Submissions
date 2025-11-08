double randn() {//to create random matrix
    double u1 = ((double)rand() + 1.0) / ((double)RAND_MAX + 2.0);
    double u2 = ((double)rand() + 1.0) / ((double)RAND_MAX + 2.0);
    return sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
}
//to multiply the two matrices
void matmultiply(double** A, double** B, double** C, int m, int n, int p) {
    for (int i=0;i<m;i++) {
    for (int j=0;j<p;j++) {
        double s=0; for (int k=0;k<n;k++) s+=A[i][k]*B[k][j];
        C[i][j]=s;
    }}
}
//allocate the memory for 2-d pointer with size r*c
double** alloc(int r, int c) {
    double** A = malloc(r * sizeof(double*));
    for (int i = 0; i < r; i++){
    A[i] = calloc(c, sizeof(double));
    }return A;
}

void freeMat(double** A, int r) { 
for (int i = 0; i < r; i++) free(A[i]); free(A);
}
//orthonormalize the coloumn vectors of matrix
void gram_schmidt(double** Q,int m,int k){
    for(int j=0;j<k;j++){
        for(int i=0;i<j;i++){
            double dot=0;for(int r=0;r<m;r++){
            dot+=Q[r][i]*Q[r][j];
            }
            for(int r=0;r<m;r++){
            Q[r][j]-=dot*Q[r][i];
            }}
        double norm=0;for(int r=0;r<m;r++){
        norm+=Q[r][j]*Q[r][j];
        } norm=sqrt(norm);
        for(int r=0;r<m;r++){
        Q[r][j]=Q[r][j]/(norm+1e-12);
        }}
}

//to create the eigen vector matrix and the eigen vaues matrix in a 2-d pointer and 1-d pointer
void jacobi(double** A,double* eval,double** evec,int n){
    for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
    evec[i][j]=(i==j);
    }
    eval[i]=A[i][i];
    }
    for(int it=0;it<500;it++){
        int p=0,q=1;double max=0;
        for(int i=0;i<n;i++)for(int j=i+1;j<n;j++)
            if(fabs(A[i][j])>max){max=fabs(A[i][j]);p=i;q=j;}
        if(max<1e-10)break;
        double phi=0.5*atan2(2*A[p][q],A[q][q]-A[p][p]);
        double c=cos(phi),s=sin(phi);
        double App=c*c*A[p][p]-2*s*c*A[p][q]+s*s*A[q][q];
        double Aqq=s*s*A[p][p]+2*s*c*A[p][q]+c*c*A[q][q];
        A[p][p]=App;A[q][q]=Aqq;A[p][q]=A[q][p]=0;
        for(int i=0;i<n;i++)if(i!=p&&i!=q){
            double aip=A[i][p],aiq=A[i][q];
            A[i][p]=A[p][i]=c*aip-s*aiq;
            A[i][q]=A[q][i]=s*aip+c*aiq;
        }
        for(int i=0;i<n;i++){
            double vip=evec[i][p],viq=evec[i][q];
            evec[i][p]=c*vip-s*viq; evec[i][q]=s*vip+c*viq;
        }
    }
    for(int i=0;i<n;i++){
    eval[i]=A[i][i];
}}
//to find the transpose of matrix A
void transpose(double** A, double** T, int m, int n) {
    for(int i=0;i<m;i++)for(int j=0;j<n;j++)T[j][i]=A[i][j];
}


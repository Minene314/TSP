#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void func(double **,int*,int);
void swap(int*,int*);
void distCal(double**,int*);
double mini(double,double);

double min = 1e9;
int N;

int main(void){
  clock_t start,end;
  int i,j,lp=1;
  int *a;
  FILE *fp;
  char fname[] = "../test.txt";
  int s, t;
  double dist;
  if((fp = fopen(fname,"r"))==NULL){
      printf("errer\n");
      return -1;
  }else{
      printf("%s file opened\n",fname);
  }
  fscanf(fp,"%d",&N);
  double **net;
  a = (int*)malloc(sizeof(int)*N+1);
  net = (double**)malloc(sizeof(double*)*N);
  for(int i = 0; i < N; i++) net[i] = (double*)malloc(sizeof(double)*N);
  //vector<vector<int>> gen(GEN, vector<int>(N));
  while(fscanf(fp,"%d %d %lf",&s, &t, &dist)!=EOF) {
      net[s][t] = net[t][s] = dist;
  }
  fclose(fp);
  for(i=0;i<N;i++) net[i][i] = 0;
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      printf("%f ",net[i][j]);
    }
    printf("\n");
  }
  printf("\n");
  for(i=0;i<N;i++) a[i] = i;
  start = clock();
  for(i=0;i<lp;i++) func(net,a,N);
  end = clock();
  printf("N=%d\nprocessing time=%fs\n",N,(double)(end-start)/CLOCKS_PER_SEC);
  printf("shortest:%f\n",min);

  free(a);
  for(i=0;i<N;i++) free(net[i]);
  free(net);
  return 0;
}

void func(double **g,int *a,int n){
  int i,j;
  if(n<2){
    a[N] = a[0];
    //for(i=0;i<N+1;i++) printf("%d ",a[i]);
    //printf("\n");
    distCal(g,a);
    return;
  }
  j = n-1;
  for(i=n-1;i>-1;i--){
    swap(&a[i],&a[j]);
    func(g,a,j);
    swap(&a[i],&a[j]);
  }
  return;
}

void swap(int *a,int *b){
  int tmp = *a;
  *a = *b;
  *b = tmp;
  return;
}

void distCal(double **g,int *a){
  double dist = 0;
  int i;
  //for(i=0;i<N;i++) printf("%d-->%d\n",a[i],a[i+1]);

  for(i=0;i<N;i++) dist = dist+ g[a[i]][a[i+1]];
  //for(i=0;i<N+1;i++) printf("%d ",a[i]);
  //printf("距離:%d\n",dist);
  min = mini(min,dist);
  return;
}

double mini(double a,double b){
  if(a>b) return b;
  return a;
}
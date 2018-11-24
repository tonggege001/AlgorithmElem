#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    double x;
    double y;
    int x_index;
    int y_index;
}node;
int baoli_Minlen(node * A, int n, int& in_x, int & in_y);
int divide_Minlen(node * A, int n, int& in_x, int & in_y);
void GenerateTest1Data(){
    FILE * fp = fopen("D:\\data.in","w");

    //����100������
    for(int i = 0;i<100;i++){
        srand((unsigned )i);
        int x= rand();
        x = x%10;//���ݹ�ģ���Ϊ100
        if(x==0 || x==1) continue;
        fprintf(fp,"%d ",x);
        for(int j = 0;j<x;j++){
            fprintf(fp,"%d %d ",rand()%100,rand()%100);
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
}
//
//void test(){
//    FILE * fp = fopen("D:\\data.in","r");
//    for(int i = 0;i<100;i++){
//        int n;
//        fscanf(fp,"%d",&n);
//        node * A = (node *)malloc(sizeof(node) * n);
//        for(int j = 0;j<n;j++){
//            fscanf(fp,"%lf%lf",&A[j].x,&A[j].y);
//        }
//        int x1,y1,x2,y2;
//        int a1 = divide_Minlen(A,n,x1,y1);
//        int a2 = baoli_Minlen(A,n,x2,y2);
//        printf("%d.�����㷨���Ϊ��%lf ���Ϊ��%d %d���������ⷨ���Ϊ��%lf�� ���Ϊ%d %d\n",i,
//               a1,x1,y1,a2,x2,y2);
//        free(A);
//    }
//    fclose(fp);
//}
////��10��
//
//
//
///*
//int main() {
//    GenerateTest1Data();
//    test();
//
//}
//
//*/

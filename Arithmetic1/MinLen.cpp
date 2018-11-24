#include <iostream>
#include <cmath>
#include <algorithm>


using namespace std;
typedef struct node{
    int x;
    int y;
    int x_index;
    int y_index;
}node;

int index_1;
int index_2;
int index_3;
int index_4;
int index_5;
int index_6;
bool complare1(node a,node b) {
    return a.x<b.x;
}

bool complare2(node a,node b) {
    return a.y<b.y;
}



int dist(node n1,node n2){
    return (int) sqrt(pow(n1.x-n2.x,2)+pow(n1.y-n2.y,2));
}

int findMinLength(node * a, node * b,int auxl[],int auxr[],int low, int high,int &in_x, int& in_y){
    if(high==low)
        return INT32_MAX;
    if(low+1==high){
        in_x = low;
        in_y = high;
        return dist(a[low],a[high]);
    }
    if(low + 2 == high){
        int a1 = dist(a[low],a[low+1]);
        int a2 = dist(a[low],a[low+2]);
        int a3 = dist(a[low+1],a[low+2]);
        if(a1<=a2 && a1<=a3){
            in_x=low;
            in_y=low+1;
            return a1;
        }
        if(a2<=a1 && a2<=a3){
            in_x=low;
            in_y=low+2;
            return a2;
        }
        if (a3<=a1 && a3<=a2){
            in_x=low+1;
            in_y=low+2;
            return a3;
        }
    }
    int mid = (high+low)/2;  //���м��ҵ�
    int x1,y1,x2,y2,x3,y3;
    int len_left = findMinLength(a,b,auxl,auxr,low,mid,x1,y1);
    int len_right = findMinLength(a,b,auxl,auxr,mid+1,high,x2,y2);
    int del;
    if(len_left<len_right){
        del = len_left;
    }
    else{
        del = len_right;
        x1=x2;
        y1=y2;
    }

    //1.Ѱ��X��������ҽ�
    int left_bound = a[mid].x_index;
    int right_bound = a[mid].x_index+1;
    while(abs(a[left_bound].x-a[mid].x)<del && left_bound >=0){
        left_bound--;
    }
    while(abs(a[right_bound].x-a[mid].x)<del && right_bound >=0){
        right_bound++;
    }
    left_bound++;
    right_bound--;

    //Ѱ�����ݼ���Y��ֵ����ߵ�
    int y_high = INT_MIN;
    for(int i = high;i>=low;i--){
        if(a[i].x_index>=left_bound && a[i].x_index<=right_bound){
            if(a[i].y_index > y_high) y_high = a[i].y_index;
        }
    }



    int min = INT32_MAX;
    for(int i = y_high;i>=0;i--){
        int valid = 0;
        if(b[i].x_index>=left_bound && b[i].x_index<=right_bound ){
            //����͵����Ѱ7����Ч��
            for(int j = i-1;j>=0 && valid<7;j--){
                if(b[j].x_index>=left_bound && b[j].x_index <=right_bound){
                    if(dist(b[j],b[i]) < min){
                        min = dist(b[j],b[i]);
                        x3 = b[j].x_index;
                        y3=b[i].x_index;
                    }
                    valid++;
                }
            }
        }
    }
//
//
//
//    //2.Ѱ��X������ߵ�Ԫ�أ����½磩
//    int len_l = 0;//��¼ѡ���Ԫ�صĳ���
//    int len_r = 0;
//
//    for(int i = a[mid].y_index;abs(b[a[mid].y_index].y-b[i].y)<del;i--){
//        //�����������Χ������뵽��ߵĸ���������
//        if(b[i].x_index >= left_bound && b[i].x_index <= mid){
//            auxl[len_l++] = b[i].x_index;
//        }
//        else if(b[i].x_index>mid && b[i].x_index<=right_bound)
//            auxr[len_r++] =b[i].x_index;
//            //����ֹͣ����
//        else
//            break;
//    }
//    for(int i = a[mid].y_index+1;abs(b[a[mid].y_index].y-b[i].y)<del;i++){
//        //�����������Χ������뵽��ߵĸ���������
//        if(b[i].x_index >= left_bound && b[i].x_index <= mid){
//            auxl[len_l++] = b[i].x_index;
//        }
//        else if(b[i].x_index>mid && b[i].x_index<=right_bound)
//            auxr[len_r++] =b[i].x_index;
//            //����ֹͣ����
//        else
//            break;
//    }
//    //Ѱ���������ߵ���Сֵ
//    double min = del;
//    for(int i = 0;i<len_l;i++){
//        for(int j = 0;j<len_r;j++){
//            double middle_dist = dist(a[auxl[i]],a[auxr[j]]);
//            if(middle_dist<min)
//                min = middle_dist;
//        }
//    }
    if(min < del){
        in_x = x3;
        in_y = y3;
        return min;
    }
    else{
        in_x = x1;
        in_y = y1;
        return del;
    }

}
//���򣬲��������ݽṹ��ʼ��
//��ʼʱ��a1�к������ݣ���a2�в���������

void preprocess(node * a1, node * a2, int n){
    sort(a1,a1+n,&complare1);
    for(int i = 0;i<n;i++){
        a1[i].x_index = i;
    }
    //��a1�е����ݷ��뵽a2
    for (int i = 0; i < n; ++i) {
        a2[i] = a1[i];
    }
    //��a1��a2�е�y����
    sort(a2,a2+n,&complare2);
    for(int i = 0;i<n;i++){
        a2[i].y_index = i;
        a1[a2[i].x_index].y_index = i;
    }
}
/*
 * ���÷����㷨���
 */
int divide_Minlen(node * A, int n,int &in_x, int &in_y){
    node *B = (node * )malloc(sizeof(node)*n);
    int auxl[n+1];
    int auxr[n+1];
    preprocess(A,B,n);
    int x1,y1;
    int minlen = findMinLength(A, B,auxl,auxr,0, n-1,x1,y1);
    in_x = x1;
    in_y = y1;
    free(B);
    return minlen;
}

/**
 * ���ñ�����ⷨ
 * @param A ����A
 * @param n ����Ԫ�ظ���
 * @return
 */
int baoli_Minlen(node * A, int n,int & in_x, int & in_y){
    int min = dist(A[0],A[1]);
    for(int i = 0;i<n;i++){
        for(int j = i+1;j<n;j++){
            if(dist(A[i],A[j])< min){
                min = dist(A[i],A[j]);
                in_x = i;
                in_y = j;
            }
        }
    }
    return min;
}


int main222() {

    int count;//��������������
    FILE * fin, * fout;
    fin = fopen("data.in","r");
    fout = fopen("data.out","w");

    fscanf(fin,"%d", &count);

    for(int w = 0;w<count;w++){
        int n;
        fscanf(fin,"%d", &n);
        node A[n];
        for(int i = 0;i<n;i++){
            fscanf(fin,"%d%d",&(A[i].x),&(A[i].y));
        }
        int x,y;
        int minlen = baoli_Minlen(A,n,x,y);
        fprintf(fout,"%d %d %d %d",A[x].x_index, A[x].y_index,A[y].x_index,A[y].y_index );
        if(w!=count-1)
            fprintf(fout,"\n");

    }



}




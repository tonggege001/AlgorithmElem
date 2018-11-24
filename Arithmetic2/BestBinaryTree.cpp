//
// Created by Administor on 2018/11/10.
//

#include <iostream>
#include <cmath>
#include <queue>

#define N 20

using namespace std;
template <typename T>
class node{

private:
    long __draw(int low, int high);

public:
    T data;
    node<T> *parent;//˫�׽��
    node<T> *lchild;//����
    node<T> *rchild;//�Һ���

    node<T>(T data);
    ~node<T>();

    int getDepth();
    int Draw();
};

template<typename T>
node<T>::node(T data) {
    this->data = data;
    parent = nullptr;
    lchild = nullptr;
    rchild = nullptr;
}
template <typename T>
node<T>::~node() {
    this->parent = nullptr;
    if(this->lchild!= nullptr){
        delete this->lchild;  //����ᴥ���ݹ����
    }
    if(this->rchild!= nullptr){
        delete this->rchild;
    }
}
template <typename T>
int node<T>::getDepth() {
    if (this->lchild == nullptr){
        if(this->rchild== nullptr)
            return 1;
        else{
            return 1+this->rchild->getDepth();
        }
    }
    else if(this->rchild== nullptr){
        return 1+this->lchild->getDepth();
    }
    else
        return std::max(1+this->lchild->getDepth(),1+this->rchild->getDepth());
}
template <typename T>
long node<T>::__draw(int low, int high) {
    int mid = high/2;
    for(int i = low;i<mid;i++){
        printf("    ");
    }
    printf("%4d",this->data);
    for(int i = mid+1;i<=high;i++){
        printf("    ");
    }
}
template <typename T>
int node<T>::Draw() {
    int depth = this->getDepth();
    int maxlen = (int)std::pow(2,depth-1);
    std::queue<node> Q;
    Q.push(this);
    while(!Q.empty()){
        int level_len = (int)Q.size();
        int gap = maxlen/level_len;
        for(int i = 1;i<=maxlen;i+=gap){
            node * n = Q.front();
            Q.pop();
            int low = i;
            int high = i+gap-1;
            for(low;low<high;low++){
                printf("    ");
            }
            if(n!= nullptr)
                printf("%4d",n->data);
            else
                printf("    ");
        }

    }


}



/**
 * �����Ŷ�����������p��q��n�����룬���ؽ�����
 * @param p �����ɹ��Ľ����ۣ���Χ��1~n
 * @param q ����ʧ�ܵ�������ۣ���Χ��0~n
 * @param n ���ݹ�ģn
 * @param w Ȩ�ؾ���
 * @param e i...j��Ϊ����Ȩֵ������� ע�⣬������һ�����ɵ�j=i-1ʱ��������ʧ��
 * @param r ���ڵ���� i...j�У�˭�Ǹ��ڵ㣨�����
 * @return
 */
int BestBinaryTree(double p[], double q[], int n, double w[][N], double e[][N], int root[][N]){
    //��ʼ��e ��j=i-1ʱ��������ʧ�ܵ�����
    for(int i = 1;i<=n+1;i++){
        e[i][i-1] = q[i-1];
    }
    for(int len = 1;len<=n;len++){ //���ڳ���
        for(int i = 1;i<=n-len+1;i++){ //�������
            int j = i+len-1;
            e[i][j] = 99999999;
            for(int r = i;r<=j;r++){ //�Դ�����ÿ�����ѯ��һ�β�����Сֵ
                if(e[i][j] > e[i][r-1]+e[r+1][j] + w[i][j]){
                    e[i][j] = e[i][r-1]+e[r+1][j] + w[i][j];
                    root[i][j] = r;
                }
            }
        }
    }
    return 0;
}

template <typename T>
node<T> * makeTree(int root[][N],int low, int high){
    if(low>high)
        return nullptr;
    int r_index = root[low][high];
    node<T> * R = new node<T>(r_index);
    node<T> * left = makeTree<T>(root, low, r_index-1);
    node<T> * right = makeTree<T>(root, r_index+1, high);
    R->lchild = left;
    R->rchild = right;
    if(left!= nullptr)
        left->parent = R;
    if(right!= nullptr)
        right->parent = R;
    return R;
}

int PRINTWEIGHT(double w[][N], int n){
    cout<<"Ȩֵ����Ϊ��"<<endl;
    for(int j = n;j>=0;j--){
        for(int i = 1;i<=n;i++){
            cout<<w[i][j]<<"            ";
        }
        cout<<endl;
    }
    cout<<endl;
}




int main(){
    int n;
    std::cout<<"��������������"<<std::endl;
    std::cin>>n;
    double p[n+1]; //���еĸ���
    double q[n+1]; //û�����еĸ���
    double w[n+2][N]; //Ȩֵ
    double e[n+2][N]; //����¼
    int root[n+2][N]; //��¼���ڵ㣬����i...j������i...j��˭�Ǹ��ڵ�

    std::cout<<"����������"<<n<<"��p��"<<std::endl;
    for(int i = 1;i<n+1;i++){
        std::cin>>p[i];
    }
    std::cout<<"����������"<<n+1<<"��q��"<<std::endl;
    for(int i = 0;i<n+1;i++){
        std::cin>>q[i];
    }
    //��ʼ����w��w[i...j]��ζ��p[i...j]��q[i-1...j]֮��
    for(int i = 1;i<=n;i++){
        for(int j = i;j<=n;j++){
            double weight = 0;
            for(int k = i;k<=j;k++){ //���ȼ����ڽ��Ȩֵ
                weight += p[k];
            }
            for(int k = i-1;k<=j;k++){ //�ټ���Ҷ�ӽ���Ȩֵ
                weight += q[k];
            }
            w[i][j] = weight;
        }
    }
    PRINTWEIGHT(w,n);  //��ӡ��Ȩֵ����
    BestBinaryTree(p,q,n,w,e,root);
    node<int> *Root = makeTree<int>(root,1,n);

    //��ӡ���ڵ����
    cout<<endl;
    cout<<"���ڵ����Ϊ��"<<endl;
    for(int i = 0;i<=n+1;i++){
        for(int j = 0;j<=n+1;j++){
            std::cout<<root[i][j]<<"    ";
        }
        std::cout<<std::endl;
    }


}



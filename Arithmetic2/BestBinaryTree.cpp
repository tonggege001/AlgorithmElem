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
    node<T> *parent;//双亲结点
    node<T> *lchild;//左孩子
    node<T> *rchild;//右孩子

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
        delete this->lchild;  //这里会触发递归调用
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
 * 求最优二叉树，其中p，q，n是输入，返回结果表格
 * @param p 搜索成功的结点代价，范围是1~n
 * @param q 搜索失败的区间代价，范围是0~n
 * @param n 数据规模n
 * @param w 权重矩阵
 * @param e i...j作为树的权值（输出） 注意，这里有一个技巧当j=i-1时代表搜索失败
 * @param r 根节点矩阵 i...j中，谁是根节点（输出）
 * @return
 */
int BestBinaryTree(double p[], double q[], int n, double w[][N], double e[][N], int root[][N]){
    //初始化e 当j=i-1时代表搜索失败的区间
    for(int i = 1;i<=n+1;i++){
        e[i][i-1] = q[i-1];
    }
    for(int len = 1;len<=n;len++){ //窗口长度
        for(int i = 1;i<=n-len+1;i++){ //窗口起点
            int j = i+len-1;
            e[i][j] = 99999999;
            for(int r = i;r<=j;r++){ //对窗口中每个结点询问一次查找最小值
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
    cout<<"权值矩阵为："<<endl;
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
    std::cout<<"请输入结点数量："<<std::endl;
    std::cin>>n;
    double p[n+1]; //命中的概率
    double q[n+1]; //没有命中的概率
    double w[n+2][N]; //权值
    double e[n+2][N]; //表格记录
    int root[n+2][N]; //记录根节点，其中i...j代表在i...j中谁是根节点

    std::cout<<"请依次输入"<<n<<"个p："<<std::endl;
    for(int i = 1;i<n+1;i++){
        std::cin>>p[i];
    }
    std::cout<<"请依次输入"<<n+1<<"个q："<<std::endl;
    for(int i = 0;i<n+1;i++){
        std::cin>>q[i];
    }
    //初始计算w，w[i...j]意味着p[i...j]和q[i-1...j]之和
    for(int i = 1;i<=n;i++){
        for(int j = i;j<=n;j++){
            double weight = 0;
            for(int k = i;k<=j;k++){ //首先计算内结点权值
                weight += p[k];
            }
            for(int k = i-1;k<=j;k++){ //再计算叶子结点的权值
                weight += q[k];
            }
            w[i][j] = weight;
        }
    }
    PRINTWEIGHT(w,n);  //打印出权值矩阵
    BestBinaryTree(p,q,n,w,e,root);
    node<int> *Root = makeTree<int>(root,1,n);

    //打印根节点矩阵
    cout<<endl;
    cout<<"根节点矩阵为："<<endl;
    for(int i = 0;i<=n+1;i++){
        for(int j = 0;j<=n+1;j++){
            std::cout<<root[i][j]<<"    ";
        }
        std::cout<<std::endl;
    }


}



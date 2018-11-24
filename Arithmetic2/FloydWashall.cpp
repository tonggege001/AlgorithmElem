//
// Created by Administor on 2018/11/13.
//
#include <iostream>
#include <fstream>
#include <stack>

int adj[100][100]; //邻接矩阵
int weight[100][100];//计算当前的矩阵
int pi[100][100];  //前驱矩阵

using namespace std;


void Floyd_Washell(int n){
    //初始化前驱矩阵
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=n;j++){
            if(adj[i][j]!=100){
                pi[i][j] = i;
            }
        }
    }
    for(int k = 1;k<=n;k++){
        for(int i = 1;i<=n;i++){
            for(int j = 1;j<=n;j++){
                if(weight[i][k]>32767) continue;
                if(weight[k][j]>32767) continue;
                if(weight[i][j]>weight[i][k]+weight[k][j]){
                    weight[i][j] = weight[i][k]+weight[k][j];
                    pi[i][j] = pi[k][j];
                }
            }
        }
    }
}


int main2(){
    int num;
    ifstream file;
    file.open("data.in");
    file>>num;

    ofstream file2;
    file2.open("data.out");
    file2<<num<<endl;
    for(int i = 0;i<num;i++){
        int n;
        file>>n;
        //构造邻接矩阵
        for(int j = 1;j<=n;j++){
            for(int k = 1;k<=n;k++){
                file>>adj[j][k];
                pi[i][j] = 0;  //前驱矩阵初始化为0
            }
        }
        //初始化距离矩阵
        for(int j = 1;j<=n;j++){
            for(int k = 1;k<=n;k++){
                if(adj[j][k]==100)
                    weight[j][k] = 10000000;
                else
                    weight[j][k] = adj[j][k];
            }
        }

        Floyd_Washell(n);
        file2<<n<<endl;
        for(int i = 1;i<=n;i++){
            for(int j = 1;j<=n;j++){
                if(weight[i][i]>32767)
                    file2<<32767;
                else
                    file2<<weight[i][j];

                if(j==n) file2<<"\n";else file2<<" ";
            }
        }

        for(int i = 1;i<=n;i++){
            for(int j = 1;j<=n;j++){
                //路径不存在时输出NULL；
                if(weight[i][j]>32767){
                    file2<<"NULL"<<endl;
                    continue;
                }
                //自己到自己时，因为这里不会出现负环，所以肯定是自己的
                if(i==j){
                    file2<<i<<endl;
                    continue;
                }
                //当有直接相连的边时
                if(pi[i][j]==i){
                    file2<<i<<" "<<j<<endl;
                    continue;
                }
                //用栈保存上一个结点
                stack<int> st;
                int pos = j;
                do{
                    st.push(pos);
                    pos = pi[i][pos];
                }while(pos!=i && pos!=0);
                st.push(i);
                //输出路径
                while(!st.empty()){
                    pos = st.top();
                    st.pop();
                    if(st.empty())
                        file2<<pos<<"\n";
                    else
                        file2<<pos<<" ";
                }
            }
        }
        file2<<endl;
    }
    file.close();
    file2.close();
}



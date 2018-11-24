//
// Created by Administor on 2018/11/3.
//
#include <iostream>
//class A{
//    int a;
//protected:
//    int b,c;
//public:
//    int d,e;
//};
//
//class B:protected A{
//    int a;
//protected:
//    int b,f;
//public:
//    int e,g;
//    A::d;
//    long aaa();
//};
//
//long B::aaa() {
//    std::cout<<"this is aaa()"<<std::endl;
//    return 0;
//}
//
//class C:A{
//    int a;
//protected:
//    int b,f;
//public:
//    int e,g;
//    A::d;
//};
//
//struct D:B,C{
//    int a;
//protected:
//    int b,f;
//public:
//    int e,g;
//
//    void eee(){
//    //    this->A::b = 10;
//        this->B::aaa();
//        this->B::b = 11;
//        this->C::b = 12;
//    //    std::cout<<this->A::b<<std::endl;
//        std::cout<<this->B::b<<std::endl;
//        std::cout<<this->C::b<<std::endl;
//    }
//};
/*
int main(){
    D d;
    d.eee();
}
*/
//
//using namespace std;
//struct A{A(){cout<<'A';}};
//struct B{B(){cout<<'B';}};
//struct C:A{C(){cout<<'C';}};
//struct D:A,B{D(){cout<<'D';}};
//struct E:A,B,virtual C{
//    D d;
//    E(){cout<<'E';}
//};
//struct F:A,virtual B, virtual C,D,E{
//    C c,d;
//    E e;
//    F(){cout <<'F';}
//};
//
//int main(){
//    A a;cout<<endl;
//    B b;cout<<endl;
//    C c;cout <<endl;
//    D d;cout<<endl;
//    E e;cout<<endl;
//    F f;cout<<endl;
//}

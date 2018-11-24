//注意:代码模板中的代码将会被复制到任何新创建的文件中，编辑代码模板中的代码，让他帮你自动增加固定代码吧
#include <iostream>
#include<string>
using namespace std;

typedef struct BigInteger{
    string & number;//数字,采用小端方式存放数字
    bool sign;//符号
    int length;//指明大整数的长度，
    BigInteger():number(*new string()){
        this->sign = true;
        this->length = 1;
        this->number.push_back('0');
    }
    //初始化列表
    BigInteger(int num):number(*new string()){
        if(num==0){
            this->sign = true;
            this->length = 1;
            this->number.clear();
            this->number.push_back('0');
            return;
        }
        if(num<0){
            this->sign = false;
            num = -num;
        }
        else
            this->sign = true;
        this->length = 0;
        while(num!=0){
            this->number.push_back((char)(num%10+'0'));
            num = num/10;
            this->length++;
        }
    }
    BigInteger(const BigInteger& b):number(*new string()){
        this->sign = b.sign;
        this->length = b.length;
        for(int i = 0;i<b.length;i++){
            this->number.push_back(b.number[i]);
        }
    }
    BigInteger(string str):number(*new string()){
        if(str.length()==0 && str[0]=='0'){
            this->length = 1;
            this->sign = true;
            this->number.push_back('0');
        }
        else{
            for(int i = (int)str.length()-1;i>=0;i--){
                this->number.push_back(str[i]);
            }
            this->length = (int)str.length();
            this->sign = true;
        }

    }
    ~BigInteger(){
        delete &this->number;
    }
    BigInteger & operator=(const BigInteger &);//实现赋值运算
    BigInteger operator+(BigInteger & b); //实现加法运算
    BigInteger operator-(BigInteger & b);//实现减法运算
    BigInteger  operator-();//取负运算符
    BigInteger operator*(BigInteger &b); //实现乘法运算
    BigInteger operator/(BigInteger &b);//实现除法运算
    bool operator==(const BigInteger & b);//相等
    BigInteger operator<<(int n); //左移n位


    void Divided(BigInteger& a, BigInteger & b, int len)const;//将一个大整数分成左右两个部分
    BigInteger oneBitMultiple(const BigInteger & a, const BigInteger &b);//一位数乘法
    BigInteger unsigned_multiple(const BigInteger & a, const BigInteger & b);

    friend ostream &operator<<(ostream &out,BigInteger&a);
    //判断操作数是否绝对值大于等于b
    bool absBig(BigInteger b){
        if(this->length < b.length) //位长不一定时，可以直接返回
            return false;
        else if(this->length > b.length)
            return true;
            //处理位长相等的情况
        else{
            //从高位开始比较，当相等时，比较下一个，否则返回二者位数的大小。
            for(int i = this->length-1;i>=0;i--){
                if(this->number.at((unsigned )i) == b.number.at((unsigned )i))
                    continue;
                else return this->number.at((unsigned )i) > b.number.at((unsigned )i);

            }
            //如果相等
            return false;
        }
    }

}BigInteger;

//赋值运算符重载
BigInteger& BigInteger::operator=(const BigInteger &b){
    this->sign = b.sign;
    this->length = b.length;
    this->number.clear();
    for(int i = 0;i<b.length;i++){
        this->number.push_back(b.number[i]) ;
    }
    return *this;
}
//取负号运算符重载
BigInteger BigInteger::operator-(){
    this->sign = !this->sign;
    return *this;
}

/**
 * 加法运算符重载
 */
BigInteger BigInteger::operator+(BigInteger &b){
    BigInteger c;//因为初值为0，所以首先需要清空字符串
    c.number.clear();
    //如果符号相同，则直接计算加法
    if(this->sign && b.sign ||  !this->sign && !b.sign){
        //执行无符号整数加法
        int minlen = this->length>b.length?b.length:this->length;
        int bit = 0;//遍历的位长
        int c_in = 0;//进位
        while(bit < minlen){
            int _a = this->number[bit]-'0';
            int _b=b.number[bit]-'0';
            char _c= (char)((_a+_b+c_in) % 10 + '0');
            c_in = (char)((_a+_b + c_in) /10);
            c.number.push_back(_c);
            bit++;
        }
        if(this->length==b.length){
            if(c_in!= 0){
                c.number.push_back('1');
                bit++;
            }
        }
        else{
            BigInteger * p = this->length>b.length?this:&b;
            while(bit<p->length){
                int _a = p->number[bit] - '0';
                char _c = (char)((_a+c_in)%10 +'0');
                c_in = ((_a+c_in)/10);
                c.number.push_back(_c);
                bit++;
            }
            if(c_in!= 0){
                c.number.push_back('1');
                bit++;
            }

        }
        //处理符号情况
        c.sign = this->sign;
        c.length = bit;


    }
        //如果符号相异直接返回减法操作
    else{
        if(this->sign && !b.sign){
            BigInteger temp = b;
            temp.sign = true;
            c = *this - temp;
        }else{
            BigInteger temp = *this;
            temp.sign = true;
            c = b - temp;

        }

    }
    return c;
}
//两个正整数相减a-b
BigInteger unsigned_sub(BigInteger & a, BigInteger & b){
    BigInteger c = 0;
    if(a==b)
        return c;
    c.number.clear();
    c.length = 0;
    int carry = 0;
    int length = a.length < b.length?a.length:b.length;
    int i = 0;
    if(a.absBig(b)){
        for(i = 0;i<length;i++){
            int _a = a.number.at((unsigned )i)-'0';
            int _b = b.number.at((unsigned )i)-'0';
            int _c;
            if(_a-_b-carry>=0 && _a-_b-carry<=9){
                _c = _a-_b-carry;
                carry = 0;
            }
            else{
                _c = _a+10-_b-carry;
                carry = 1;
            }
            c.number.push_back((char)(_c+'0'));
            c.length ++;
        }
        //前提是默认a已经绝对值大于b，这里看位数是否相等，不等的话继续计算
        if(a.length > b.length){
            for(;i<a.length;i++){
                int _a=a.number[(unsigned )i]- '0';
                if(carry!=0 && _a>0){
                    _a = _a-1;
                    carry = 0;
                }
                else if(carry!=0 && _a==0){
                    _a = 9;
                    carry = 1;
                }
                c.number.push_back((char)(_a+'0'));
                if(_a!=0)
                    c.length++;
            }
        }
    }
    else{
        c = unsigned_sub(b,a);
        c.sign = false;
        return c;
    }

}

BigInteger BigInteger::operator-(BigInteger &b){
    BigInteger c;
    //被减数和减数均为正数
    if(this->sign && b.sign){
        c = unsigned_sub(*this,b);
    }
        //a - (-b)
    else if(this->sign&& !b.sign){
        BigInteger d = b;
        d.sign = true;
        c = *this+d;
    }
        //-a - b
    else if(!this->sign && b.sign){
        BigInteger temp1 = *this;
        BigInteger temp2 = b;
        temp2.sign = temp1.sign = true;
        c= temp1+temp2;
        c.sign = false;
    }
        //被减数和减数均为负号-a - (-b)，则执行b-a
    else{
        BigInteger temp1 = *this;
        BigInteger temp2 = b;
        temp2.sign = true;
        temp1.sign=true;
        c = unsigned_sub(temp2,temp1);
    }
    //被减数和减数符号相同则执行无符号相减
    //消除前面无效的0
    int zero = 0;
    for(int i = c.number.length()-1;i>0;i--){
        if(c.number[i]=='0') zero++;
        else
            break;
    }
    c.length = c.length-zero;
    while(zero!=0){
        c.number.pop_back();
        zero--;
    }

    return c;
}

/**
 * 将两个整数分开成左右两个整数
 * @param org 原来的整数
 * @param a 高位整数 a.length>=b.length
 * @param b 低位整数
 */
void BigInteger::Divided( BigInteger &a, BigInteger &b,int len)const {
    int _length = len;
    //分的长度大
    if(_length >= this->length*2){
        a = 0;
        b = *this;
        return;
    }
    b.length = len/2;
    a.length = this->length-b.length;
    a.number.clear();
    b.number.clear();
    for(int i = this->length-a.length;i<this->length;i++){
        a.number.push_back(this->number[i]);
    }
    for(int i = 0;i<b.length;i++){
        b.number.push_back(this->number[i]);
    }
    return;


}
/*
 * 一位乘法
 */
BigInteger BigInteger::oneBitMultiple(const BigInteger &a, const BigInteger &b) {
    BigInteger c;
    c.number.clear();
    c.length = 0;
    if(a.length==1 && b.length==1){
        int _a = a.number[0]-'0';
        int _b = b.number[0]-'0';
        if(_a==0||_b==0){
            c.number.push_back('0');
            c.length++;
            return c;
        }
        int _c = _a*_b;
        while(_c!=0){
            c.number.push_back((char)((_c %10)+'0'));
            c.length++;
            _c = _c/10;
        }
        return c;
    }
    else if(a.length==1 && b.length!=1){
        //当乘以0时直接返回0
        if(a.length==1 && a.number[0]=='0' ||b.length==1 && b.number[0]=='0' ){
            c = 0;
            return c;
        }
        int carry = 0;
        int _a = a.number[0]-'0';
        for(int i = 0;i<b.length;i++){
            int _b = b.number[i]-'0';
            int tmp = _a*_b+carry;
            c.number.push_back((char)((tmp %10)+'0'));
            c.length++;
            carry = tmp /10;
        }
        if(carry!=0){
            c.number.push_back((char)(carry+'0'));
            c.length++;
        }
        return c;
    }
    else if(a.length !=1 && b.length == 1){
        return oneBitMultiple(b,a);
    }
}

BigInteger BigInteger::operator<<(int n) {
    BigInteger c = *this;
    if(this->length==1 && this->number[0]=='0'){
        return *this;
    }

    c.number.insert(0,(unsigned)n,'0');
    c.length+=n;
    return  c;
}

BigInteger BigInteger::unsigned_multiple(const BigInteger &a, const BigInteger &b) {
    if(a.length==1 || b.length==1){
        return oneBitMultiple(a,b);
    }
    int len = a.length>b.length?a.length:b.length;
    BigInteger A,B,C,D;//x为高位，y为低位
    a.Divided(A,B,len);
    b.Divided(C,D,len);

    BigInteger AC = unsigned_multiple(A,C);
    BigInteger BD = unsigned_multiple(B,D);
    BigInteger A_B = A-B;
    BigInteger D_C = D-C;

    BigInteger tmp1,tmp2;
    tmp1 = AC<<(len/2)*2;
    tmp2 = A_B *D_C ;
    tmp2 = tmp2+AC;
//    cout<<"tmp..1:"<<tmp2<<endl;
    tmp2 = tmp2 + BD;
//    cout<<"tmp..2:"<<tmp2<<endl;
    tmp2 = tmp2<<(len/2);
//    cout<<"tmp..3:"<<tmp2<<endl;
//    cout<<"A:"<<A<<"  B:"<<B<<"  C:"<<C<<"  D"<<D<<endl;
//    cout<<"AC:"<<AC<<"  BD:"<<BD<<"  A_B:"<<A_B<<"  D_C:"<<D_C<<endl;
//    cout<<"tmp1:"<<tmp1<<"  tmp2:"<<tmp2<<endl;
    return  tmp1 + tmp2 +BD;

}

BigInteger BigInteger::operator*(BigInteger &b) {
    BigInteger c = unsigned_multiple(*this,b);
    c.sign = (this->sign&&b.sign) || (!this->sign && !b.sign);
    return c;

}

ostream& operator<<(ostream &out, BigInteger & a) {
    out<<(a.sign?"+":"-");
    for(int i = a.length-1;i>=0;i--){
        out<<a.number[i];
    }
    return out;
}

bool BigInteger::operator==(const BigInteger &b) {
    if(this->length==b.length){
        bool flag = true;//默认相等
        for(int i = 0;i<this->length;i++){
            if(this->number[i]!=b.number[i]){
                flag = false;
                break;
            }

        }
        return flag;
    }
    return false;
}

int main(){
    BigInteger a = *new string("15616884651894891351684186464651684684866816");
    BigInteger b = *new string("1561864846168486135146138431681684323131864878931878943513");
    BigInteger c = a*b;
    cout<<c<<endl;
    return 0;

}


int main2(){
//    for(int i = 0;i<20;i++){
//        int n1 = rand();
//        int n2 = rand();
//        BigInteger a1 = n1;
//        BigInteger a2 = n2;
//        BigInteger a3 = a1*a2;
//        long long b1 = n1;
//        long long b2 = n2;
//        cout<<"BigInteger: "<<a3<<"   result: "<<b1*b2<<endl;
//    }
}


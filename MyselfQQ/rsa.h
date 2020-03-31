
#ifndef RSA_H
#define RSA_H
#include <iostream>
#include <cmath>
#include <cstring>
#include <ctime>
#include <cstdlib>

using namespace std;
#include<stdio.h>
#include<QString>
QString a;
char text1[1024];
char text2[1024];
int Plaintext[1024];//明文
__int64 Ciphertext[1024];//密文 qlonglong 在win32下为long long int
int n, e = 0, d;
//int e=3,d=3,n=10;
#include<QDebug>
//二进制转换
int BianaryTransform(int num, int bin_num[])
{

    int i = 0,  mod = 0;

    //转换为二进制，逆向暂存temp[]数组中
    while(num != 0)
    {
        mod = num%2;
        bin_num[i] = mod;
        num = num/2;
        i++;
    }

    //返回二进制数的位数
    return i;
}

//反复平方求幂
__int64 Modular_Exonentiation(__int64 a, int b, int n)
{
    int c = 0, bin_num[1000];
    __int64 d = 1;
    int k = BianaryTransform(b, bin_num)-1;

    for(int i = k; i >= 0; i--)
    {
        c = 2*c;
        d = (d*d)%n;
        if(bin_num[i] == 1)
        {
            c = c + 1;
            d = (d*a)%n;
        }
    }
    return d;
}

//生成1000以内素数
int ProducePrimeNumber(int prime[])
{
    int c = 0, vis[1001];
    memset(vis, 0, sizeof(vis));
    for(int i = 2; i <= 1000; i++)if(!vis[i])
    {
        prime[c++] = i;
        for(int j = i*i; j <= 1000; j+=i)
            vis[j] = 1;
    }

    return c;
}

//辗转相除法求最大公约数
int Exgcd(int m,int n,int &x)
{
    int x1,y1,x0,y0, y;
    x0=1; y0=0;
    x1=0; y1=1;
    x=0; y=1;
    int r=m%n;
    int q=(m-r)/n;
    while(r)
    {
        x=x0-q*x1; y=y0-q*y1;
        x0=x1; y0=y1;
        x1=x; y1=y;
        m=n; n=r; r=m%n;
        q=(m-r)/n;
    }
    return n;
}

//RSA初始化
void RSA_Initialize()
{
    //取出1000内素数保存在prime[]数组中
    int prime[5000];
    int count_Prime = ProducePrimeNumber(prime);

    //随机取两个素数p,q
    srand((unsigned)time(NULL));
    int ranNum1 = rand()%count_Prime;
    int ranNum2 = rand()%count_Prime;
    int p = prime[ranNum1], q = prime[ranNum2];

    n = p*q;

    //求φ(n)
    int On = (p-1)*(q-1);

    //用辗转相除法法求e,d
    for(int j = 3; j < On; j+=1331)
    {
        int gcd = Exgcd(j, On, d);
        if( gcd == 1 && d > 0)
        {
            e = j;
            break;
        }
    }
}

//RSA加密
void RSA_Encrypt()
{
    cout<<"公钥 (e, n) : e = "<<e<<" n = "<<n<<'\n';
    cout<<"私钥 (d, n) : d = "<<d<<" n = "<<n<<'\n'<<'\n';

    int i = 0;
    for(i = 0; i < 1024; i++)
        //求C
        Ciphertext[i] = Modular_Exonentiation(Plaintext[i], e, n);

    //cout<<"用公钥 (e, n) 加密，得到密文:"<<'\n';
    /*for(i = 0; i<1024 && Ciphertext[i]!=0 ; i++)
        printf("%I64d ",Ciphertext[i]);
    cout<<'\n'<<'\n';*/
}

//RSA解密
void RSA_Decrypt()//QQ765715928
{
    int i = 0;
    for(i = 0; i < 1024; i++)
        Ciphertext[i] = Modular_Exonentiation(Ciphertext[i], d, n);

    //cout<<"用私钥 (d, n) 解密，得到明文:"<<'\n';
    for(i = 0; i<1024 && Ciphertext[i]!=0 ; i++)
    {
        //cout<<(char)(Ciphertext[i]);
        text2[i] = (char)(Ciphertext[i]) ;
    }
    text2[i] = 0 ;
    cout<<'\n'<<'\n';
}


//算法初始化
void Initialize(QString aa)
{
    int i;
    srand((unsigned)time(0));

    int omg;
    omg=aa.toInt();

    //cout<<"输入明文:"<<'\n';
        //cin.getline(text1,1024);

    for(i = 0; i < 1024; i++)
    {
        Plaintext[i] = omg%10;
        omg=omg/10;
        qDebug()<<"Plaintext number is"<<Plaintext[i];

    }
    //qDebug()<<aa;

}

/*int main()
{
    //生成1024个随机数字
    Initialize();

    while(!e)
        //RSA初始化
        RSA_Initialize();

    cout<< "MD5 : " << md5(text1) << endl;

    RSA_Encrypt();

    RSA_Decrypt();

    cout<< "MD5 : " << md5(text2) << endl;

    system("pause");

    return 0;
}*/

#endif // RSA_H

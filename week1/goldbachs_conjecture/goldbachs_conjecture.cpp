#include <iostream>
#include <algorithm>
#include <string>
#include <math.h>

#define MAXN 1000000

bool prime[MAXN];

using namespace std;

// fonction naive (mais suffisante), crible d'eratosthene serait plus rapide
bool isPrime(int a)
{
    bool res=true;
    int d=2;
    while(res && d<=sqrt(a))
    {
        res=(a%d!=0);
        d++;
        //cout << d <<" diviseur ?"<< endl;
    }
    /*if(res)
        cout << a <<" premier"<< endl;
    else
        cout << a <<" divisible par "<<d <<endl;*/
    return res;
}

int a, b, n;

void findAB()
{
    if(a<n/2)
    {
        a=-1;
    }
    else if (!(isPrime(a) && isPrime(b)))
    {
        a--;
        b=n-a;
        //cout << n << "=" << a << "+" << b << "\n";
        findAB();
    }
}

int main()
{
    while(1)
    {
        cin >> n;
        //cout << "\n\nn=" <<n <<endl;
        if (n==0)
            return 0;

        a=n-3;
        b=n-a;

        findAB();
        if(a==-1)
            cout << "Goldbach's conjecture is wrong.\n";
        else
            cout << n << " = " << b << " + " << a << "\n";
    }
    return 0;
}

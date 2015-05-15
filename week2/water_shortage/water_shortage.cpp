#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <math.h>

using namespace std;

#define epsilon 0.0001

double baseL[1000];
double area[1000];
double height[1000];
int N, nbcase;
double target;

double V(double ll)
{
    double res=0;
    for(int i=0; i<N; i++)
        res += min(max(0.0, ll - baseL[i]), height[i]) * area[i];
    return res;
}

double recherche(double min, double max)
{
    double mid=(min+max)/2;
    double v=V(mid);

    if(v<= target + epsilon && v >= target - epsilon)
        return mid;
    if(v>target+epsilon)
        recherche(min, mid);
    else
        recherche(mid, max);
}

double lmax()
{
    double res=0;
    for(int i=0; i<N; i++)
        res = max(res, baseL[i] + height[i]);
    return res;
}

int main()
{
    cin >> nbcase;
    while (nbcase--)
    {
        cin >> N;

        double total=0;
        for(int i=0; i<N; i++)
        {
            double b, h, w, d;
            cin >> b >> h >> w >> d;

            baseL[i]=b;
            height[i]=h;
            area[i]=w*d;

            total+=height[i]*area[i];
        }
        cin >> target;

        if(target > total + epsilon)
            cout << "OVERFLOW" << endl;
        else
            printf("%.2f\n",recherche(0, lmax()));

        if(nbcase > 0)
            cout << endl;
    }

    return 0;
}

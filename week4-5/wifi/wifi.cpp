#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <cstdio>
#include <string>
#include <math.h>
#include <list>
#include <cstring>

using namespace std;

#define NMAX 100001
#define epsilon 0.001

int nbcase, n, m;
int houses[NMAX];

//nombre de wifi pour recouvrir les maisons pour un diametre fixe
int needed(double diam)
{
    int first=houses[0];

    int res=1;
    for(int i=1; i<m; i++)
    {
        if(houses[i]>first+diam)
        {
            first=houses[i];
            res++;
        }
    }
    return res;
}

int main()
{
    scanf("%d", &nbcase);
    while(nbcase--)
    {
        scanf("%d%d",&n,&m);
        for(int i=0; i<m; i++)
            scanf("%d", &houses[i]);

        std::sort(houses, houses+m);

        /*for(int i=0; i<m; i++)
            cout << houses[i] << endl;
        */

        double min, max, mid;
        min=0;
        max=2*(houses[m-1] - houses[0] +1);

        while(max-min>epsilon)
        {
            mid=(min+max)/2;

            int wifi=needed(mid);
            //cout << "d="<<mid <<" -> " << wifi << " wifi needed"<< endl;
            if(wifi>n)
                min=mid;
            else
                max=mid;
        }
        printf("%.1f\n", mid/2.0);
    }
    return 0;
}

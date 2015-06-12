#include <iostream>
#include <climits>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

#define NMAX 101
#define DMAX 200

int nbcase, N, a, b;
int g[NMAX][NMAX];
int marked[NMAX];

int main()
{
    int nbcase=0;
    while(true)
    {
        for (int i=0; i<NMAX; ++i)
        {
            for (int j=0; j<NMAX; ++j)
                g[i][j] = DMAX;
            //g[i][i] = 0;
        }

        scanf("%d%d", &a, &b);
        if(a==0 && b==0)
            return 0;
        while(!(a==0 && b==0))
        {
            //cout << a << " " << b<< endl;
            g[a][b]=1;
            scanf("%d%d", &a, &b);
        }

        for (int k=0; k<NMAX; ++k)
            for (int i=0; i<NMAX; ++i)
                for (int j=0; j<NMAX; ++j)
                    g[i][j] = min(g[i][j], g[i][k] + g[k][j]);

        double sum=0;
        int n=0;
        for (int i=0; i<NMAX; ++i)
        {
            for (int j=0; j<NMAX; ++j)
            {
                if(g[i][j]!=DMAX && i!=j)
                {
                    sum+=g[i][j];
                    n++;
                }
            }
        }

        nbcase++;
        printf("Case %d: average length between pages = %.3lf clicks\n", nbcase, (double)sum/n);
	}
	return 0;
}

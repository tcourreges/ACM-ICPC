#include <iostream>
#include <climits>
#include <algorithm>

using namespace std;

unsigned long long g[101][101];
int nbcase, N, E, T, M;

int main()
{
    cin >> nbcase;

    for(int icase=0; icase<nbcase; icase++)
    {
        cin >> N >> E >> T >> M;

        for (int i=0; i<N; ++i)
        {
            for (int j=0; j<N; ++j)
            {
                g[i][j] = INT_MAX;
            }
            g[i][i] = 0;
        }

        for(int i=0; i<M; i++)
        {
            int a, b, c;
            cin >> a >> b >> c;
            g[a-1][b-1] = c;
        }

        for (int k=0; k<N; ++k)
            for (int i=0; i<N; ++i)
                for (int j=0; j<N; ++j)
                    g[i][j] = min(g[i][j], g[i][k] + g[k][j]);

        int res=0;
        E -= 1;
        for (int i=0; i<N; ++i)
        {
            if (g[i][E] <= T)
                res++;
        }

        cout << res << endl;

        if(icase<nbcase-1)
            cout << endl;
    }
    return 0;
}

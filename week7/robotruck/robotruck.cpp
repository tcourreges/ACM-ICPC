#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>
#include <list>

using namespace std;

#define NMAX 100001

int nbcase, C,N;
int x[NMAX], y[NMAX], w[NMAX];
int W[NMAX], D[NMAX]; // poids et distance(sans passage par O) cumulés
int dO[NMAX]; // distance à l'origine

int res[NMAX]; // distance minimale jusqu'à O en livrant 1-i

int main()
{
    scanf("%d",&nbcase);
    while(nbcase--)
    {
        scanf("%d%d",&C,&N);

        for(int i=1;i<N+1; i++)
        {
            scanf("%d%d%d", &x[i], &y[i], &w[i]);

            W[i] = W[i-1] + w[i];
            D[i] = D[i-1] + abs(x[i]-x[i-1]) + abs(y[i]-y[i-1]);
            dO[i]=abs(x[i])+abs(y[i]);
        }

        list<int> q; // liste de priorité : prochain passage par l'origine
        q.push_back(0); // juste pour initialiser (origine)
        for(int i=1; i<N+1; i++)
        {
            //for(list<int>::iterator it = q.begin(); it!=q.end(); it++) cout << *it << ' '; cout << endl;

            // on vire assez de paquets au début pour respecter C
            while(!q.empty() && W[i]-W[q.front()] > C)
                q.pop_front();

            // on livre tous les paquets jusqu'à i d'un coup (ie a-origine-(a+1)-...-i)
            int a=q.front();
            res[i]=  res[a]  +  dO[a+1] + (D[i]-D[a+1]) + dO[i];

            // on vire les arrêts qui ne peuvent plus améliorer le résultat
            // ie: il est plus intéressant de partir de i que de q.back() pour la suite
            while(!q.empty() &&
                  !(res[i] + dO[i+1] - D[i+1] > res[q.back()] + dO[q.back()+1] - D[q.back()+1]))
                q.pop_back();

            q.push_back(i);
        }
        printf("%d\n", res[N]);
        if(nbcase) printf("\n");
    }
    return 0;
}

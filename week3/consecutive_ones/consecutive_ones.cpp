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

#define NMAX 401
#define MMAX 401

bool mat[NMAX][MMAX];
int perm[MMAX];
int nbcase, N, M;

void echange(int a,int b)
{
    for(int i=0; i<N; i++)
        swap(mat[i][a], mat[i][b]);
    swap(perm[a], perm[b]);
}

//la matrice convient jusqu'à j=col-1
bool find(int col)
{
    if(col==M)
        return true;

    for(int j=col; j<M; j++)
    {
        bool swapj=true;

        // est-ce qu'on peut swap j<->col ie est-ce qu'on aurait bien
        // sur chaque ligne 10... =>que des 0
        // (mais 00 ou X0 on peut pas savoir)
        for(int i=0; i<N; i++)
        {
            if(mat[i][col-1] && !mat[i][j]) // 10...
            {
                for(int k=col; k<M; k++)
                {
                    if(mat[i][k]) // 10...1
                    {
                        swapj=false;
                        break;break;
                    }
                }
            }
        }
        if(swapj)
        {
            echange(j,col);
            if(find(col+1))
                return true;
            echange(j,col); //on retablit la matrice pour les appels suivants
        }
    }
    return false;
}

int main()
{
    cin >> nbcase;
    while(nbcase--)
    {
        cin >> N >> M;

        for (int j = 0; j < M; j++)
            perm[j] = j;

        for (int i = 0; i < N; i++)
        {
            string s;
            cin >> s;
            for (int j = 0; j < M; j++)
                mat[i][j] = (s[j] == '1');
        }
        /*
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++)
                cout << mat[i][j];
            cout << endl;
        }*/

        find(1);
        for(int j=0; j<M; j++)
            cout << perm[j] << endl;

        if(nbcase>0)
            cout << endl;
    }
    return 0;
}

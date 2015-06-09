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

#define NMAX 41
#define KMAX 201

char grid[NMAX][NMAX];
bool marked[NMAX][NMAX];
char words[KMAX][23];
int n, m, k;

struct dir
{
    int x, y;
    dir(int _x, int _y): x(_x), y(_y) {}
};

dir directions[8]={
    dir(-1,-1), dir(-1, 0), dir(-1, 1),
    dir( 0,-1),             dir( 0, 1),
    dir( 1,-1), dir( 1, 0), dir( 1, 1)
};

//tente de lire les cmax lettres de word depuis i0,j0 dans la direction d
bool read(char* word, int i0, int j0, dir d, int cmax)
{
    //cout << "read("<< word<< ") at "<< i0<<","<<j0 << " size=" <<cmax <<endl;
    int i=i0, j=j0, c=0;

    //cout << c << "/" << cmax-1 << " " << grid[i][j] << " =? " << word[c] << endl;

    while(i>=0 && i<n && j>=0 && j<m && c<cmax && word[c]==grid[i][j])
    {
        i = i + d.x;
        j = j + d.y;
        c++;
        //cout << c << "/" << cmax-1 << " " << grid[i][j] << " =? " << word[c] << endl;
    }
    return c==cmax;
}

void mark(int i0, int j0, dir d, int cmax)
{
    int i=i0, j=j0, c=0;

    while(i>=0 && i<n && j>=0 && j<m && c<cmax)
    {
        //cout << "marking " << grid[i][j] << " at " << i << j<< endl;
        marked[i][j]=true;
        i = i + d.x;
        j = j + d.y;
        c++;
    }
}

int main()
{
    while (true)
    {
        int sc=scanf("%d%d", &n, &m);
        if(sc!=2)
            return 0;

        scanf("\n%d\n", &k);
        for (int i = 0 ; i < k ; i++)
            scanf("%s\n", words[i]);
        for (int i = 0 ; i < n ; i++)
        {
            for (int j = 0 ; j < m ; j++)
            {
                scanf("%c", &grid[i][j]);
                marked[i][j] = false;
            }
            scanf("\n");
        }
/*
        for (int i = 0 ; i < k ; i++)
            cout << words[i] << endl;
        for (int i = 0 ; i < n ; i++) {
            for (int j = 0 ; j < m ; j++)
                cout << grid[i][j];
            cout << endl;
        }
*/
/*
        cout << read("CB", 1, 1, directions[0], 2) << endl;
        cout << read("WAR", 2, 1, directions[0], 3) << endl;
*/
        for(int iword=0; iword<k; iword++)
        {
            int length=strlen(words[iword]);

            for(int i=0; i<n; i++)
            {
                for(int j=0; j<m; j++)
                {

                    for(int idir=0; idir<8; idir++)
                    {
                        if (read(words[iword], i, j, directions[idir], length))
                        {
                            mark(i, j, directions[idir], length);
                        }
                    }
                }
            }
        }
        for (int i = 0 ; i < n ; i++)
            for (int j = 0 ; j < m ; j++)
                if(!marked[i][j])
                    printf("%c",grid[i][j]);
        printf("\n");

    }
    return 0;
}

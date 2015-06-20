#include <iostream>
#include <climits>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

#define NMAX 100001

int N, M;
int n[2][2];
int subs[2][2][NMAX]; //cas, company, subsidiary

void display(int cas)
{
    cout << "--------------------------"<<endl;
    for(int c=0; c<2; c++)
    {
        for(int i=0; i<n[cas][c]; i++)
            cout << subs[cas][c][i] << " ";
        cout << endl;
    }
}

//takeover => la plus grosse subsidiary
bool takeover(int cas, int c1)
{
    int c2=1-c1;

    int n1=n[cas][c1];
    int n2=n[cas][c2];

    if(subs[cas][c1][n1-1]<subs[cas][c2][n2-1])
        return false;

    n[cas][c2]--;
    return true;
}

//merge => les deux plus grosses
void merge(int cas, int c1)
{
    int n1=n[cas][c1];
    n[cas][c1]--;

    if(n1>1)
        subs[cas][c1][n1-2] += subs[cas][c1][n1-1];
}

//merge->takeover => takeover wins
//takeover->merge

int main()
{
    int nbcase=0;

    while(true)
    {
        int sc = scanf("%d%d", &N, &M);
        if(sc==EOF) return 0;

        n[0][0]=N; n[0][1]=M;
        n[1][0]=N; n[1][1]=M;

        for(int c=0; c<2; c++)
            for(int i=0; i<n[0][c]; i++)
                scanf("%d", &subs[0][c][i]);

        sort(subs[0][0], subs[0][0]+N);
        sort(subs[0][1], subs[0][1]+M);

        for(int i=0; i<N; i++)
            subs[1][0][i]=subs[0][0][i];
        for(int i=0; i<M; i++)
            subs[1][1][i]=subs[0][1][i];

        //display(0); display(1);

        //cout << "###################################"<<endl;
        int res=0;
        for(int cas=0; cas<2; cas++)
        {
            //cout << "-----------CAS "<<cas<<"----------"<<endl;
            //display(cas);

            int c=0;

            if(cas==1 || !takeover(cas, c))
                    merge(cas, c);

            while(n[cas][0]>0 && n[cas][1]>0)
            {
               // display(cas);
                c=1-c;
                if(!takeover(cas, c))
                    merge(cas, c);
            }

            if(n[cas][0]==0)
                res=1;

            //cout << endl<<res <<" won"<<endl;

            if(res==0)
                break;
        }

        nbcase++;

        if(res==0)
            printf("Case %d: Takeover Incorporated\n", nbcase);
        else
            printf("Case %d: Buyout Limited\n", nbcase);
    }

    return 0;
}

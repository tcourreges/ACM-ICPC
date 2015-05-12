#include <stdio.h>
#include <vector>
#include <iostream>
#include <list>

using namespace std;

int nbcase, N, M, k, t, ti;
list<int> queue;
vector<int> dep[101]; //v[ti]={t tq t dep de ti}
int degree[101]; //degree[t]=nb de dependances
bool topush[101];

int main()
{
    cin >> nbcase;

    while(nbcase--)
    {
        cin >> N >> M;

        //reset
        for(int i = 0; i <= N; i++)
            dep[i].clear(), degree[i] = 0;

        //on stocke les transitions+degres
        while(M--)
        {
            cin >> t >> k;
            while(k--)
            {
                cin >> ti;
                dep[ti].push_back(t);
                degree[t]++;
            }
        }

        queue.clear();
        //on queue tous les deg=0 par ordre croissant
        for(int i = 1; i <= N; i++)
        {
            if(degree[i] == 0)
                queue.push_back(i);
        }

        int t;
        bool espace =false;
        while(!queue.empty())
        {
            if(espace)
                putchar(' ');
            espace = true;

            //on affiche t=front et on le vire de la queue
            t = queue.front();
            queue.pop_front();
            cout << t;

            for(int i = 1; i <= N; i++)
                topush[i]=false;

            //on decremente le deg de ses successeurs et on marque les deg=0
            for(vector<int>::iterator it = dep[t].begin(); it != dep[t].end(); it++)
            {
                degree[*it]--;
                if(degree[*it]==0)
                    topush[*it]=true;
            }

            //on queue les nouveaux deg=0 par ordre croissant
            for(int i = 1; i <= N; i++)
            {
                if(topush[i])
                    queue.push_back(i);
            }
        }
        cout << endl;

        if(nbcase>0)
            cout << endl;
    }
    return 0;
}

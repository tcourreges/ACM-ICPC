#include <iostream>
#include <algorithm>
#include <string>
#include <math.h>

using namespace std;

int nbcase, x, k;
int v[6]; //5+1 pour indexer comme dans le sujet

bool find(int vi, int _x, int _k, int imax)
{
    //cas terminal
    if (vi == 0 || _k == 0)
        return false;

    //i=nombre de vi (on part du plus grand possible)
    for(int i=min(_x/vi,imax); i>=0; i--)
    {
        /*
        for(int j=0; j<k-_k; j++)
            cout << " ";
            cout << i << " x " << vi << endl;
        */
        //soit ça tombe juste, soit on regarde si on peut completer avec le vi suivant
        if (i*vi == _x || find( v[  k - _k +2], _x-i*vi, _k-1, i))
            return true;
    }
    return false;
}

int main()
{
    int nbcase;
    cin >> nbcase;

    for(int i=0; i<nbcase; i++)
    {
        cin >> x;
        cin >> k;

        //on remplit v
        for(int j=1; j<=k; j++)
        {
            cin >> v[j];
            //cout << v[j] << " ";
        }
        for(int j=k+1; j<=5; j++)
            v[j]=0;

        //on lance le recursion
        if(find(v[1], x, k, 100000))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;

        if(i<nbcase-1)
            cout << endl;
    }

    return 0;
}

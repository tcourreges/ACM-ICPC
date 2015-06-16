#include <iostream>
#include <climits>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

#define NMAX 100001

int l[NMAX];

int n, length;
int nbcase;
int first, last, res;

int main()
{
    scanf("%d", &nbcase);
    while(nbcase--)
    {
        scanf("%d%d", &n, &length);
        for(int i=0; i<n; i++)
            scanf("%d",&l[i]);

        sort(l, l+n);
        /*for(int i=0; i<n; i++)
            cout << l[i] << endl;
        */

        first=0;
        last=n-1;
        res=0;

        while(first<last+1)
        {
            //cout << first << " "<<last<<endl;
            int left=length-l[last];
            last--;

            if(l[first]<=left)
                first++;

            res++;
        }

        cout << res << endl;

        if(nbcase)
            cout << endl;
    }

    return 0;
}


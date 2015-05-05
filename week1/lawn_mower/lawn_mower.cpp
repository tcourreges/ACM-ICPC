#include <iostream>
#include <algorithm>
#include <string>

float x[1000];
float y[1000];

using namespace std;

int main()
{
    int nx, ny;
    float w;

    while(1)
    {
        cin >> nx;
        cin >> ny;
        cin >> w;

        if (nx==0 && ny==0 && w==0.0)
            return 0;

        //cout << "\n";

        //on remplit les tableaux
        for(int i=0; i<nx; i++)
        {
            cin >> x[i];
            //cout << x[i] << " ";
        }

        for(int i=0; i<ny; i++)
            cin >> y[i];

        bool yes=true;

        //on classe par ordre croissant
        std::sort(x, x + nx);
        std::sort(y, y + ny);

        //cout << "\n" << yes << "\n";

        //on verifie que ca s'enchaine correctement
        for(int i=0; i<nx-1; i++)
        {
            //cout << x[i] << " ";
            if((x[i + 1]-x[i])>w)
                yes=false;
            //cout << " --" << yes << " \n";
        }
        if((x[0]-0)>w/2)
            yes=false;
        if((75-x[nx - 1])>w/2)
            yes=false;

        //cout << "------\n";

        for(int i=0; i<ny-1; i++)
        {
            //cout << y[i] << " ";
            if((y[i + 1]-y[i])>w)
                yes=false;
            //cout << " --" << yes << " \n";
        }

        if((y[0]-0) > w/2)
            yes=false;
        if((100-y[ny - 1])>w/2)
            yes=false;

        if(yes)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}

/* 
 * File:   main.cpp
 * Author: Drackzgull
 *
 * Created on 22 de marzo de 2016, 12:04 PM
 */

#include <cstdlib>
#include <random>
#include <chrono>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv)
{
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine g(seed);
    uniform_int_distribution<unsigned> rd(1, 100);
    unsigned chance = 1,                                        //chance of getting an UR
            jewels = 0,                                         //jewels spent
            get = 0,                                            //event UR copies aquired
            UR = 0;                                             //other UR cards aquired
    int N = -1;
    bool flag = false;
    ofstream F;
    
    //file in which to dump the sim data, it will overwrite itself on each run.
    //data tabulated in rows as: N (sim number) - jewels spent - amount of pulls - target UR copies aquired - other UR cads aquired
    F.open("Last Sim.txt", ofstream::out | ofstream::trunc);
    
    cout << "enter how many runs to simulate:";
    do
    {
        cin >> N;
        if(N < 1)
            cout << "please enter a positive number:" << endl;
    }while(N < 1);
    
    for(int i = 0; i < N; i++)
    {
        while(get < 2)
        {
            jewels += 3000;
            for(int j = 0; j < 11; j++)
            {
                if(rd(g) <= chance)
                {
                    if(rd(g) <= 50)
                        get++;
                    else
                        UR++;
                    flag = true;
                }
            }
            if(flag)
                chance = 1;
            else
                chance += 5;
            flag = false;
        }
        F << i + 1 << "\t" << jewels << "\t" << jewels * 11 / 3000 << "\t" << get << "\t" << UR << endl;
        chance = 1;
        jewels = 0;
        get = 0;
        UR = 0;
    }
    return 0;
}


// ConsoleApplication1.cpp : Defines the entry point for the console application.
//
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

unsigned seed = chrono::system_clock::now().time_since_epoch().count();
default_random_engine g(seed);
uniform_int_distribution<unsigned> rd(1, 100);

//provide F stream reference and number of iterations to run, special summon function.
void special_summon(ofstream& F, int N, int jewel_limit, int success) {
	bool use_jewel_limit;
	if (jewel_limit == 0) use_jewel_limit = false;
	else use_jewel_limit = true;
	unsigned chance = 1,                                        //chance of getting an UR
		jewels = 0,                                         //jewels spent
		get = 0,                                            //event UR copies aquired
		UR = 0;                                             //other UR cards aquired
	bool flag = false;
	bool result = true;
	F << "Count" << "\t" << "jewels" << "\t" << "Cards" << "\t" << "Featured" << "\t" << "Other UR";
	if (use_jewel_limit == true) F << "\t" << "success?";
	F << endl;
	for (int i = 0; i < N; i++)
	{
		//if no jewel limit, run till sucess.  if jewel limit, either run till success OR run till out of jewels.
		while ((get < success && use_jewel_limit == false) || (get < success && use_jewel_limit == true && ((jewels + 3000) <= jewel_limit)))
		{
			jewels += 3000;
			for (int j = 0; j < 11; j++)
			{
				if (rd(g) <= chance)
				{
					if (rd(g) <= 50)
						get++;
					else
						UR++;
					flag = true;
				}
			}
			if (flag)
				chance = 1;
			else
				chance += 5;
			flag = false;
		}
		F << i + 1 << "\t" << jewels << "\t" << jewels * 11 / 3000 << "\t" << get << "\t" << UR;
		if (use_jewel_limit == true) {
			if (get < success) F << "\t" << "no";
			else F << "\t" << "yes";
		}
		F << endl;
		chance = 1;
		jewels = 0;
		get = 0;
		UR = 0;
	}
}


int main(int argc, char** argv)
{
	int N = -1,
		jewel_limit = 0,
		success = 0;
	char summon_type = '0';
	ofstream F;

	//file in which to dump the sim data, it will overwrite itself on each run.
	//data tabulated in rows as: N (sim number) - jewels spent - amount of pulls - target UR copies aquired - other UR cads aquired
	F.open("Last Sim.txt", ofstream::out | ofstream::trunc);

	cout << "enter type of summon:" << endl << "S - Special" << endl;

	//read summon type
	cin >> summon_type;
	
	//if not valid, request summon type again until valid
	while(summon_type != 'S')
	{
		cout << "please enter a valid summon type" << endl;
		cin >> summon_type;
	} 

	cout << endl;
	cout << "enter how many runs to simulate:";
	do
	{
		cin >> N;
		if (N < 1)
			cout << "please enter a positive number:" << endl;
	} while (N < 1);

	cout << endl << "Enter the target number of featured cards" << endl;
	do
	{
		cin >> success;
		if (success < 1)
			cout << "please enter a positive number:" << endl;
	} while (success < 1);

	cout << endl << "Enter a jewel limit (0 for no limit)" << endl;
	do
	{
		cin >> jewel_limit;
		if (jewel_limit < 0)
			cout << "please enter a positive number:" << endl;
	} while (jewel_limit < 0);

	if (summon_type == 'S')
		special_summon(F,N,jewel_limit,success);

	return 0;
}

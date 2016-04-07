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

void box_summon_11(ofstream& F, int N, int jewel_limit, int success)
{
	bool use_jewel_limit;
	if (jewel_limit == 0) use_jewel_limit = false;
	else use_jewel_limit = true;
	unsigned chance = 1,                                        //chance of getting an UR
		jewels = 0,                                         //jewels spent
		get = 0,                                            //event UR copies aquired
		UR = 0;                                             //other UR cards aquired
	F << "Count" << "\t" << "jewels" << "\t" << "Cards" << "\t" << "Featured" << "\t" << "Other UR";
	if (use_jewel_limit == true) F << "\t" << "success?";
	F << endl;
	for (int i = 0; i < N; i++)
	{
		//if no jewel limit, run till sucess.  if jewel limit, either run till success OR run till out of jewels.
		while ((get < success && use_jewel_limit == false) || (get < success && use_jewel_limit == true && ((jewels + 3000) <= jewel_limit)))
		{
			//build box summon 
			bool reset_box = false,
				got_featured = false,
				got_other_UR = false;
			unsigned box_count = 0;
			//while there's no need to reset box...
			while ((reset_box == false && use_jewel_limit == false) || (reset_box == false && use_jewel_limit == true && ((jewels + 3000) <= jewel_limit)))
			{
				//do an 11 summon
				jewels += 3000;
				box_count += 11;
				for (int j = 0; j < 11; j++)
				{
					if (rd(g) <= chance)
					{
						//if you received both URs do nothing.  If you received 1 UR get the other.
						if (got_other_UR == true && got_featured == true) {}
						else if ((rd(g) <= 50 && got_featured == false) || got_other_UR == true) {
							get++;
							reset_box = true;
							got_featured = true;
						}
						else {
							UR++;
							got_other_UR = true;
						}
					}
				}
				//if you drew all the cards...
				if (box_count == 77) 
				{
					//if you didn't already get both URs, get them.  then reset the box stats.
					if (got_featured == false) get++;
					if (got_other_UR == false) UR++;
					reset_box = true;
				}
			}
		}
		F << i + 1 << "\t" << jewels << "\t" << jewels * 11 / 3000 << "\t" << get << "\t" << UR;
		if (use_jewel_limit == true) {
			if (get < success) F << "\t" << "no";
			else F << "\t" << "yes";
		}
		F << endl;
		jewels = 0;
		get = 0;
		UR = 0;
	}
}

void box_summon_1(ofstream& F, int N, int jewel_limit, int success)
{
	{
		bool use_jewel_limit;
		if (jewel_limit == 0) use_jewel_limit = false;
		else use_jewel_limit = true;
		unsigned chance = 1,                                        //chance of getting an UR
			jewels = 0,                                         //jewels spent
			get = 0,                                            //event UR copies aquired
			UR = 0;                                             //other UR cards aquired
		F << "Count" << "\t" << "jewels" << "\t" << "Cards" << "\t" << "Featured" << "\t" << "Other UR";
		if (use_jewel_limit == true) F << "\t" << "success?";
		F << endl;
		for (int i = 0; i < N; i++)
		{
			//if no jewel limit, run till sucess.  if jewel limit, either run till success OR run till out of jewels.
			while ((get < success && use_jewel_limit == false) || (get < success && use_jewel_limit == true && ((jewels + 3000) <= jewel_limit)))
			{
				//build box summon 
				bool reset_box = false,
					got_featured = false,
					got_other_UR = false;
				unsigned box_count = 0;
				//while there's no need to reset box...
				while ((reset_box == false && use_jewel_limit == false) || (reset_box == false && use_jewel_limit == true && ((jewels + 3000) <= jewel_limit)))
				{
					//do an summon
					jewels += 300;
					box_count += 1;
					if (rd(g) <= chance)
						{
							//if you received both URs do nothing.  If you received 1 UR get the other.
							if (got_other_UR == true && got_featured == true) {}
							else if ((rd(g) <= 50 && got_featured == false) || got_other_UR == true) {
								get++;
								reset_box = true;
								got_featured = true;
							}
							else {
								UR++;
								got_other_UR = true;
							}
						}
					//if you drew all all but two, check guarenteed UR.  
					if (box_count == 76)
					{
						//if you haven't gotten either UR yet, get one at random.
						if (got_other_UR == false && got_featured == false)
							if ((rd(g) <= 50)) {
								get++;
								got_featured = true;
								reset_box = true;
							}
							else {
								UR++;
								got_other_UR = true;
							}
					}
					//receive the other UR you haven't gotten yet
					if (box_count == 77)
					{
						if (got_featured == false) get++;
						if (got_other_UR == false) UR++;
						reset_box = true;
					}
				}
			}
			F << i + 1 << "\t" << jewels << "\t" << jewels / 300 << "\t" << get << "\t" << UR;
			if (use_jewel_limit == true) {
				if (get < success) F << "\t" << "no";
				else F << "\t" << "yes";
			}
			F << endl;
			jewels = 0;
			get = 0;
			UR = 0;
		}
	}
}

void step_up_summon(ofstream& F, int N, int jewel_limit, int success) { 
	bool use_jewel_limit;
	if (jewel_limit == 0) use_jewel_limit = false;
	else use_jewel_limit = true;
	unsigned chance = 1,                                        //chance of getting an UR
		jewels = 0,                                         //jewels spent
		get = 0,                                            //event UR copies aquired
		alt = 0,
		UR = 0,												//other UR cards aquired
		steps = 0,
		cards = 0,
		next_step_cost = 0;												
	bool flag = false;
	F << "Count" << "\t" << "jewels" << "\t" << "steps" << "\t" << "Cards" << "\t" << "Featured" << "\t" << "Alt Featured" << "\t" << "Other UR";
	if (use_jewel_limit == true) F << "\t" << "success?";
	F << endl;
	for (int i = 0; i < N; i++)
	{
		//if no jewel limit, run till sucess.  if jewel limit, either run till success OR run till out of jewels.
		while ((get < success && use_jewel_limit == false) || (get < success && use_jewel_limit == true && ((jewels + next_step_cost) <= jewel_limit)))
		{
			jewels += next_step_cost;
			int cards_to_draw = 0;
			if (steps % 4 == 0)
			{
				cards_to_draw = 1;
				chance = 1;
				cards += 1;
				next_step_cost = 600;
			}
			if (steps % 4 == 1)
			{
				cards_to_draw = 3;
				chance = 2;
				cards += 3;
				next_step_cost = 1200;
			}
			if (steps % 4 == 2)
			{
				cards_to_draw = 5;
				chance = 3;
				cards += 5;
				next_step_cost = 3000;
			}
			if (steps % 4 == 3)
			{
				cards_to_draw = 10;
				cards += 11;
				chance = 4;
				next_step_cost = 100;
				if (steps % 8 == 7)
				{
					if (rd(g) <= 50)
						get++;
					else
						alt++;
				}
			}
			for (int j = 0; j < cards_to_draw; j++)
			{
				if (rd(g) <= chance)
				{
					int temp = rd(g);
					if (temp <= 25)
						get++;
					else if (temp <= 50)
						alt++;
					else
						UR++;
				}
			}
			steps++;
		}
		F << i + 1 << "\t" << jewels << "\t" << steps << "\t" << cards << "\t" << get << "\t" << alt << "\t" << UR;
		if (use_jewel_limit == true) {
			if (get < success) F << "\t" << "no";
			else F << "\t" << "yes";
		}
		F << endl;
		steps = 0;
		chance = 1;
		jewels = 0;
		alt = 0;
		cards = 0;
		next_step_cost = 0;
		get = 0;
		UR = 0;
	}
}

void flip_dx_summon(ofstream& F, int N, int jewel_limit, int success)
{
	{
		bool use_jewel_limit;
		if (jewel_limit == 0) use_jewel_limit = false;
		else use_jewel_limit = true;
		unsigned chance = 1,                                        //chance of getting an UR
			jewels = 0,                                         //jewels spent
			get = 0,                                            //event UR copies aquired
			cards = 0,											//total nubmer of cards
			UR = 0;                                             //other UR cards aquired
		F << "Count" << "\t" << "jewels" << "\t" << "Cards" << "\t" << "Featured" << "\t" << "Other UR";
		if (use_jewel_limit == true) F << "\t" << "success?";
		F << endl;
		for (int i = 0; i < N; i++)
		{
			//if no jewel limit, run till sucess.  if jewel limit, either run till success OR run till out of jewels.
			while ((get < success && use_jewel_limit == false) || (get < success && use_jewel_limit == true && ((jewels + 1400) <= jewel_limit)))
			{
				jewels += 300;
				cards += 1;
				for (int j = 0; j < 6; j++)
				{
					if (rd(g) <= chance)
					{
						//ignore non-event URs by default, can add option to grab non-event URs later I guess
						if (rd(g) <= 50) {
							if (j != 0)
							{
								jewels += 1100;
								cards += 5;
							}
							get++;
						}
					}
				}
			}
			F << i + 1 << "\t" << jewels << "\t" << cards << "\t" << get << "\t" << UR;
			if (use_jewel_limit == true) {
				if (get < success) F << "\t" << "no";
				else F << "\t" << "yes";
			}
			F << endl;
			jewels = 0;
			get = 0;
			UR = 0;
		}
	}
}

void premium_hyper_summon(ofstream& F, int N, int jewel_limit, int success)
{
	bool use_jewel_limit;
	if (jewel_limit == 0) use_jewel_limit = false;
	else use_jewel_limit = true;
	unsigned chance = 3,                                        //chance of getting an UR
		jewels = 0,                                         //jewels spent
		get = 0,                                            //event UR copies aquired
		UR = 0;                                             //other UR cards aquired
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
				}
			}
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

void poi_summon(ofstream& F, int N, int rt_limit, int success);

int main(int argc, char** argv)
{
	int N = -1,
		jewel_limit = 0,
		success = 0;
	char summon_type = '0';
	ofstream F;
	bool valid_summon = false;

	//file in which to dump the sim data, it will overwrite itself on each run.
	//data tabulated in rows as: N (sim number) - jewels spent - amount of pulls - target UR copies aquired - other UR cads aquired
	F.open("Last Sim.txt", ofstream::out | ofstream::trunc);

	cout << "enter type of summon:" << endl << "S: Special Summon" << endl << "B: Box summon" << endl << "F: Flip DX summon" << endl << "U: Step Up summon" << endl;

	do {
		cin >> summon_type;
		if (summon_type == 'S' || summon_type == 'B' || summon_type == 'F' || summon_type == 'P' || summon_type == 'U') valid_summon = true;
		else cout << "please enter a valid summon type" << endl;
	} while (valid_summon == false);
	
	cout << endl;
	cout << "enter how many runs to simulate:" << endl;
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
	if (summon_type == 'S')	special_summon(F, N, jewel_limit, success);
	else if (summon_type == 'B')
	{
		
		cout << endl << "Box summon can draw either 1 or 11 at a time, which do you want to do?" << endl;
		int number_of_cards_to_summon;
		do {
			cin >> number_of_cards_to_summon;
			if (!(number_of_cards_to_summon == 1 || number_of_cards_to_summon == 11)) cout << "please use a value of 1 or 11." << endl;
		} while (!(number_of_cards_to_summon == 1 || number_of_cards_to_summon == 11));
		if (number_of_cards_to_summon == 1) box_summon_1(F, N, jewel_limit, success);
		else box_summon_11(F, N, jewel_limit, success);
	}
	else if (summon_type == 'F') flip_dx_summon(F, N, jewel_limit, success);
	else if (summon_type == 'P') premium_hyper_summon(F, N, jewel_limit, success);
	else if (summon_type == 'U') step_up_summon(F, N, jewel_limit, success);
	return 0;
}

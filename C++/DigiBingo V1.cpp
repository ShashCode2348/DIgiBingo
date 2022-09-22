#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
using namespace std;

string join(vector<string> initList, const string& separator = "") {
	string s;
	for (const auto& i : initList) {
		if (s.empty()) {
			s = i;
		}
		else {
			s += separator + i;
		}
	}
	return s;
}

string join(vector<int> initList, const string& separator = "") {
	string s;
	for (const auto& i : initList) {
		if (s.empty()) {
			s = to_string(i);
		}
		else {
			s += separator + to_string(i);
		}
	}
	return s;
}

int choice(vector<int> list) {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(0, size(list)-1);
	int random_num =  int(dist(mt));
	return list[random_num];
}

void m10maker(int n, vector<int>* m10) {
	bool maker = true;
	int qwerty = 0;
	while (maker == true) {
		if (qwerty == int((n - 1) / 10) - 1) {
			maker = false;
		}
		qwerty += 1;
		m10->push_back((qwerty*10) - 1);
	}
}

void getplayersnames(int p, vector<string>* t, int an, vector<string> num) {
	for (int counter = 0; counter < p; counter++, an++) {
		string n = num[an];
		string the; cout << "Who is your " << n << " player? " << flush; cin >> the;
		t->push_back(the);
	}
	string list_of_players = join(*t, ", ");
	string ans1;
	cout << "These are the people playing:\n" << list_of_players << "\nAre these the only people playing(y/n)? " << flush;
	cin >> ans1;
	if (ans1 == "n") {
		string smth;  cout << "How many more players are playing? " << flush; cin >> smth;
		int play = stoi(smth);
		getplayersnames(play, t, an, num);
	}
	else if (ans1 == "y") {
		cout << "Now for the player's cards" << endl;
	}
}

void makecards(int clen, vector<vector<int>>* cnums,int p, int n) {
	for (int a = 0; a < p; a++) {
		vector<int> num90 = {}; for (int i = 1; i < n; i++) { num90.push_back(i); }
		for (int i = 0; i < clen; i++) {
			int cardnum = choice(num90);
			num90.erase(remove(num90.begin(), num90.end(), cardnum), num90.end());
			(* cnums)[a].push_back(cardnum);
		}
	}
}

pair<vector<int>, vector<string>> getnumbers(vector<int> num90, vector<int> finnums, int a, vector<string> names, vector<vector<int>> cards,vector<vector<int>> fincards, int an, vector<string> nums, int an2, vector<string> finnames, int an3, vector<int> multiples_of_10) {
	vector<int> z;
	while (num90.size() > 0) {
		cout << "Retrieving number... " << endl;
		this_thread::sleep_for(chrono::milliseconds(1000));
		int chosen_number = choice(num90);
		cout << "The chosen number is " << chosen_number << endl;
		num90.erase(remove(num90.begin(), num90.end(), chosen_number), num90.end());
		finnums.push_back(chosen_number);
		cout << "Checking for occurence in cards... " << endl;
		this_thread::sleep_for(chrono::milliseconds(1000));
		an = 0;
		an2 = 0;
		int c = names.size() - finnames.size();
		for (int counter = 0; counter < names.size(); counter++) {
			an3 = 0;
			string plural = " numbers";
			if (count(cards[counter].begin(), cards[counter].end(), chosen_number)) {
				an++;
				fincards[counter].push_back(chosen_number);
				cards[counter].erase(remove(cards[counter].begin(), cards[counter].end(), chosen_number), cards[counter].end());
				if (cards[counter].size() == 0) {
					an2++;
					an3++;
					cout << names[counter] << " has finished their numbers and is " << nums[0] << endl;
					finnames.push_back(names[counter]);
				}
				if (an3 != 1) {
					if (cards[counter].size() == 1) {
						plural = " number";
					}
					cout << names[counter] << ", you have " << chosen_number << " in your card, and have " << cards[counter].size() << plural << " left to finish" << endl;
				}
				this_thread::sleep_for(chrono::milliseconds(500));
			}
		}
		if (an < 1) {
			cout << "No one has " << chosen_number << endl;
		}
		if (an2 >= 1) {
			z.push_back(an2);
			nums.erase(nums.begin());
		}
		if (count(multiples_of_10.begin(), multiples_of_10.end(), a)) {
			cout << "The numbers that have been called out so far are: " << join(finnums, ", ") << endl;
		}
		a++;
		string xyz; cout << "Are you ready to continue? " << flush; cin >> xyz;
	}
	return pair<vector<int>, vector<string>> {z, finnames};
}

int main() {
	//Variables
	string winner = "winners are";
	vector<int> finnumbers{};
	vector<int> z{};
	vector<string>the_players{};
	vector<string>finplayers{};
	vector<int>donenums{};
	int any_use = 0;
	int anyuse = 0;
	int anyuses = 0;
	int any_uses = 0;
	vector<string> numbers = { "first", "second", "third", "fourth", "fifth", "sixth", "seventh", "eigth", "ninth", "tenth", "eleventh", "twelfth", "thirteenth", "fourteenth", "fifteenth", "sixteenth", "seventeenth", "eighteenth", "nineteenth", "twentieth"
		"twenty-first", "twenty-second", "twenty-third", "twenty-fourth", "twenty-fifth", "twenty-sixth", "twenty-seventh", "twenty-eigth", "twenty-ninth", "thirtieth" };
	vector<int> multiples_of_10{};

	//Intro
	cout << "Welcome to DigiBingo(2 - 30 players)!" << endl;
	cout << "DigiBingo:\n    1. Asks for details\n    2. Makes each player a card of numbers\n    3. Chooses a random number not chosen already and shows which people have that number\n    4. Displays the winner and the order of players(who came 1st / 2nd / last)" << endl;
	cout << "So..." << endl;
	this_thread::sleep_for(chrono::milliseconds(500));
	cout << "Let\'s get started." << endl;

	//Get players' names and setup
	string player_str;
	cout << "How many players are playing DigiBingo?" << flush; cin >> player_str;
	int player = 0;
	try {
		player = stoi(player_str);
	}
	catch (...) {
		cout << "An integer was not entered" << endl;
	}
	getplayersnames(player, &the_players, any_use, numbers);
	int n = 90; 
	int x = 1; vector<int> numbers_to_n(n); generate(numbers_to_n.begin(), numbers_to_n.end(), [&] {return x++; });
	m10maker(n, &multiples_of_10);

	//Make the cards
	vector<vector<int>> cardnums = {}; for (int i = 0; i < the_players.size(); i++) { cardnums.push_back({}); }
	int cardlen = 15;
	makecards(cardlen, &cardnums, the_players.size(), n);
	for (int a = 0; a < size(the_players); a++) {
		vector<string> str_cardnum; for (int i = 0; i < size(cardnums[a]); i++) { str_cardnum.push_back(to_string(cardnums[a][i])); };
		string l = join(str_cardnum, ", "); cout << the_players[a] << ", your numbers are: " << l << endl;
	}
	string xyzy; cout << "Are you ready to continue? " << flush; cin >> xyzy;

	//Calling the numbers
	vector<vector<int>> fincardnums = {}; for (int i = 0; i < the_players.size(); i++) { fincardnums.push_back({}); }
	pair<vector<int>, vector<string>> y = getnumbers(numbers_to_n, finnumbers, any_use, the_players, cardnums, fincardnums, anyuse, numbers, anyuses, finplayers, any_uses, multiples_of_10);
	z = y.first;
	finplayers = y.second;

	//Who Wins?
	if (z[0] == 1) {
		winner = "winner is";
	}
	cout << "The " << winner << "..." << flush;
	this_thread::sleep_for(chrono::milliseconds(500));
	cout << join(vector<string>{ finplayers.begin(), finplayers.begin()+z[0]}, ", ") << endl;
	numbers = { "1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th", "19th", "20th", "21st", "22nd", "23rd", "24th", "25th", "26th", "27th", "28th", "29th", "30th"};
	for (int counter = 0; counter <= z.size(); counter++) {
		cout << numbers[counter] << ": " << join(vector<string>{ finplayers.begin(), finplayers.begin() + z[0]}, ", ") << endl;
		for (int i = 0; i < z[0]; i++) {
			finplayers.erase(finplayers.begin());
		}
		z.erase(z.begin());
	}
	return 0;
}

#include "Functions.h"

vector<string> numbers = { "first", "second", "third", "fourth", "fifth", "sixth", "seventh", "eigth", "ninth", "tenth", "eleventh", "twelfth", "thirteenth", "fourteenth", "fifteenth", "sixteenth", "seventeenth", "eighteenth", "nineteenth", "twentieth"
		"twenty-first", "twenty-second", "twenty-third", "twenty-fourth", "twenty-fifth", "twenty-sixth", "twenty-seventh", "twenty-eigth", "twenty-ninth", "thirtieth" };

Player::Player(string name):m_name(name) {
	vector<int> num90 = {}; for (int i = 1; i < Game::m_totalnums; i++) { num90.push_back(i); }
	for (int i = 0; i < Game::m_cardlen; i++) {
		int cardnum = choice(num90);
		num90.erase(remove(num90.begin(), num90.end(), cardnum), num90.end());
		m_nums.push_back(cardnum);
	}
}

Game::Game() {
	bool maker = true;
	int qwerty = 0;
	while (maker == true) {
		if (qwerty == int((m_totalnums - 1) / 10) - 1) {
			maker = false;
		}
		qwerty += 1;
		multiples_of_10.push_back(90 - (qwerty * 10) - 1);
	}
}

void Game::playersInit() {
	int numPlayers;
	cout << "How many players are playing DigiBingo? " << flush; cin >> numPlayers;
	if (numPlayers <= 0) {
		cout << "A positive integer was not inputted" << endl;
		exit(1);
	}
	for (int i = 0; i < numPlayers; i++) {
		string name; cout << "What is the name of your " << numbers[i] << " player? " << flush; cin >> name;
		the_players.push_back(Player(name));
	}
	cout << "Now for the player's cards" << endl;
	this_thread::sleep_for(chrono::milliseconds(500));
	for (Player p: the_players) {
		vector<int> nums = *p.getNums();
		cout << p.getName() << ", your numbers are: " << intJoin(nums, ", ", "0") << endl;
	}
}

void Game::getnumbers() {
	vector<int> num90 = {}; for (int i = 1; i < Game::m_totalnums; i++) { num90.push_back(i); }
	vector<int> finNumbers = {};
	int maxPos = 1;
	while (num90.size() > 0) {
		cout << "Retrieving number... " << endl;
		this_thread::sleep_for(chrono::milliseconds(1000));
		int chosen_number = choice(num90);
		cout << "The chosen number is " << chosen_number << endl;
		num90.erase(remove(num90.begin(), num90.end(), chosen_number), num90.end());
		finNumbers.push_back(chosen_number);
		cout << "Checking for occurence in cards... " << endl;
		this_thread::sleep_for(chrono::milliseconds(1000));
		int numPresent = 0;
		int isFin = 0;
		for (Player& p : the_players) {
			if (p.getNums()->size() == 0) {
				continue;
			}
			string plural = " numbers";
			if (find(p.getNums()->begin(), p.getNums()->end(), chosen_number) != p.getNums()->end()) {
				numPresent++;
				p.removeNum(chosen_number);
				if (p.getNums()->size() == 0) {
					isFin++;
					cout << p.getName() << " has finished their numbers and is " << numbers[0] << endl;
					finplayers.push_back(p);
					continue;
				}
				if (p.getNums()->size() == 1) {
					plural = " number";
				}
				cout << p.getName() << ", you have " << chosen_number << " in your card, and have " << p.getNums()->size() << plural << " left to finish. " << endl;
			}
		}
		if (numPresent < 1) {
			cout << "No one has " << chosen_number << " in their cards" << endl;
		}
		if (isFin > 0) {
			numbers.erase(numbers.begin());
			numPerPlace.push_back(isFin);
		}
		if (count(multiples_of_10.begin(), multiples_of_10.end(), num90.size())) {
			cout << "The numbers that have been called out so far are: " << intJoin(finNumbers, ", ") << endl;
		}
		string cont; cout << "Are you ready to continue? " << flush; cin >> cont;
	}
	finplayers.push_back(Player(""));
}

string join(vector<string> initList, const string& separator) {
	string s;
	for (const auto &i : initList) {
		if (s.empty()) {
			s = i;
		}
		else {
			s += separator + i;
		}
	}
	return s;
}

string intJoin(vector<int> initList, const string& separator, const string& fill) {
	string s;
	for (const auto &i : initList) {
		string str = to_string(i);
		if (str.size() < 2) {
			str = fill + str;
		}
		if (s.empty()) {
			s = str;
		}
		else {
			s += separator + str;
		}
	}
	return s;
}

int choice(vector<int> list) {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(0, size(list) - 1);
	int random_num = int(dist(mt));
	return list[random_num];
}
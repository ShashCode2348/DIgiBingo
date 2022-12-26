#include "Functions.h"

vector<string> numbers = { "first", "second", "third", "fourth", "fifth", "sixth", "seventh", "eigth", "ninth", "tenth", "eleventh", "twelfth", "thirteenth", "fourteenth", "fifteenth", "sixteenth", "seventeenth", "eighteenth", "nineteenth", "twentieth"
		"twenty-first", "twenty-second", "twenty-third", "twenty-fourth", "twenty-fifth", "twenty-sixth", "twenty-seventh", "twenty-eigth", "twenty-ninth", "thirtieth" };

Player::Player(string name) :m_name(name) {
	vector<int> num90 = {}; for (int i = 1; i < Game::m_totalnums; i++) { num90.push_back(i); }
	for (int i = 0; i < Game::m_cardlen; i++) {
		int cardnum = choice(num90);
		num90.erase(remove(num90.begin(), num90.end(), cardnum), num90.end());
		m_nums.push_back(cardnum);
	}
}

void Game::playersInit() {
	int numPlayers;
	try {
		numPlayers = stoi(askStr("How many players are playing DigiBingo? "));
		if (numPlayers <= 0) {
			cout << "A positive integer was not inputted" << endl;
			exit(1);
		}
	}
	catch (...) {
		cout << "An integer wasn't entered" << endl;
		exit(1);
	}
	for (int i = 0; i < numPlayers; i++) {
		string name = askStr("What is the name of your " + numbers[i] + " player?");
		the_players.push_back(Player(name));
	}
	askStr("Now for the player's cards. Are you ready to continue?");
	this_thread::sleep_for(chrono::milliseconds(500));
	string cardInfo;
	int a = 0;
	for (Player p : the_players) {
		a++;
		vector<int> nums = *p.getNums();
		cardInfo += (p.getName() + ", your numbers are: " + intJoin(nums, ", ", "0") + "\n");
		if ((a == 5) || (a == the_players.size())) {
			dispText(cardInfo + "Are you ready to continue?");
			cardInfo = "";
		}
	}
}

void Game::getnumbers(Fl_Box* numDisp) {
	vector<int> num90 = {}; for (int i = 1; i < Game::m_totalnums; i++) { num90.push_back(i); }
	vector<int> finNumbers = {};
	int maxPos = 1;
	while (num90.size() > 0) {
		this_thread::sleep_for(chrono::milliseconds(2000));
		int chosen_number = choice(num90);
		numDisp->label(setdp(2, chosen_number).c_str());
		numDisp->redraw();
		num90.erase(remove(num90.begin(), num90.end(), chosen_number), num90.end());
		finNumbers.push_back(chosen_number);
		num_maker(chosen_number);
		int numPresent = 0;
		int isFin = 0;
		string msgTxt = "";
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
					msgTxt += (p.getName() + " has finished their numbers and is " + numbers[0] + "\n");
					finplayers.push_back(p);
					continue;
				}
				if (p.getNums()->size() == 1) {
					plural = " number";
				}
				msgTxt += (p.getName() + ", you have " + to_string(chosen_number) + " in your card, and have " + to_string(p.getNums()->size()) + plural + " left to finish. " + "\n");
			}
		}
		if (numPresent < 1) {
			msgTxt += ("No one has " + to_string(chosen_number) + " in their cards");
		}
		if (isFin > 0) {
			numbers.erase(numbers.begin());
			numPerPlace.push_back(isFin);
		}
		dispText(msgTxt);
	}
	finplayers.push_back(Player(""));
}

string join(vector<string> initList, const string& separator) {
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

string intJoin(vector<int> initList, const string& separator, const string& fill) {
	string s;
	for (const auto& i : initList) {
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

vector<string> split(string initStr, char sep) {
	vector<string> s;
	string e;
	for (char i : initStr) {
		if (i == sep) {
			s.push_back(e);
			e = "";
			continue;
		}
		e.push_back(i);
	}
	return s;
}

int choice(vector<int> list) {
	random_device rd;
	mt19937 mt(rd());
	uniform_real_distribution<double> dist(0, size(list) - 1);
	int random_num = int(dist(mt));
	return list[random_num];
}

string askStr(string qText) {
	auto* i = new Fl_Input(100, 500, 0, 0, qText.c_str());
	i->align(FL_ALIGN_RIGHT_TOP); i->labelfont(FL_HELVETICA); i->labelsize(12);
	i->readonly(false); i->activate();
	string inp;
	while (not (Fl::event() == FL_WHEN_ENTER_KEY)) {
		Fl::wait();
	}
	inp = i->value();
	i->~Fl_Input();
	return inp;
}

void dispText(string qText) {
	vector<string> qList = split(qText, '\n');
	string disp;
	for (int i = 0; i < qList.size(); i++) {
		if (i % 5 == 0) {
			askStr(disp + "\n Are you ready to continue?");
			disp = "";
		}
		disp += (qList[i] + "\n");
	}
	if (qList.size() % 5 != 0) {
		askStr(disp + "\n Are you ready to continue?");
	}
}

string setdp(int dp, int i) {
	string output;
	string I = to_string(i);
	if (I.size() < dp) {
		while (output.size() < dp - 1) { output += "0"; }
	}
	output += I;
	return output;
}

void num_maker(int counter) {
	int xy = counter;
	counter = xy - 1;
	string i = setdp(2, counter);
	int z = atoi(&(i[1]));
	if (z > 312) {
		z += 63;
	}
	int x_pos = z + 625;
	int y_pos = atoi(&(i[0])) * 64 + 62;
	auto* num = new Fl_Box(FL_NO_BOX, x_pos, y_pos, 0, 0, setdp(2, xy).c_str());
	num->align(FL_ALIGN_RIGHT_TOP); num->labelfont(FL_HELVETICA); num->labelsize(25);
	num->show();
}
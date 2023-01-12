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

Game::Game() {
	inpText->align(FL_ALIGN_RIGHT_BOTTOM); inpText->labelfont(FL_HELVETICA); inpText->labelsize(18); inpText->hide();
	inpField->align(FL_ALIGN_RIGHT_TOP); inpField->hide();
	smt->align(FL_ALIGN_RIGHT_TOP); smt->labelfont(FL_HELVETICA); smt->labelsize(20); smt->hide();
	w->align(FL_ALIGN_RIGHT_TOP); w->labelfont(FL_HELVETICA); w->labelsize(20); w->hide();
	for (int i = 1; i < Game::m_totalnums; i++) { num_maker(i); }
}

void Game::playersInit() {
	string dispIn = askStr("Do you want the program to show if players have a number in their card(Y/N)?");
	transform(dispIn.begin(), dispIn.end(), dispIn.begin(), ::tolower);
	if (dispIn == "n") {
		showNum = false;
	}
	int numPlayers;
	try {
		numPlayers = stoi(askStr("How many players are playing DigiBingo?"));
		if (numPlayers <= 0) {
			cout << "A positive integer was not inputted" << endl;
			exit(1);
		}
	}
	catch (...) {
		cout << "An integer wasn't entered" << endl;
		exit(2);
	}
	for (int i = 0; i < numPlayers; i++) {
		string name = askStr("What is the name of your " + numbers[i] + " player?");
		the_players.push_back(Player(name));
	}
	askStr("Now for the player's cards. Are you ready to continue?");
	this_thread::sleep_for(chrono::milliseconds(500));
	string cardInfo;
	for (Player p : the_players) {
		vector<int> nums = *p.getNums();
		cardInfo += (p.getName() + ", your numbers are: " + intJoin(nums, ", ", "0") + "\n");
	}
	dispText(cardInfo + "Are you ready to continue?");
}

void Game::getnumbers(Fl_Box* numDisp) {
	vector<int> num90 = {}; for (int i = 1; i < Game::m_totalnums; i++) { num90.push_back(i); }
	vector<int> finNumbers = {};
	int maxPos = 1;
	while (num90.size() > 0) {
		this_thread::sleep_for(chrono::milliseconds(500));
		int chosen_number = choice(num90);
		numDisp->copy_label(setdp(2, chosen_number).c_str());
		num90.erase(remove(num90.begin(), num90.end(), chosen_number), num90.end());
		finNumbers.push_back(chosen_number);
		numBoard[chosen_number - 1]->show();
		int numPresent = 0;
		int isFin = 0;
		string msgTxt = "";
		for (Player& p : the_players) {
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
		if (isFin > 0) {
			numbers.erase(numbers.begin());
			numPerPlace.push_back(isFin);
		}
		switch (showNum) {
		case true:
			if (numPresent < 1) {
				askStr("No one has " + to_string(chosen_number) + " in their cards\n\nAre you ready to continue?");
			}
			else {
				dispText(msgTxt);
			}
			break;
		default:
			askStr("Are you ready to continue?");
			break;
		}
	}
	finplayers.push_back(Player(""));
}

void Game::num_maker(int counter) {
	int xy = counter;
	counter = xy - 1;
	string i = setdp(2, counter);
	int z = atoi(&(i[1])) * 78;
	if (atoi(&(i[1])) > 4) {
		z += 63;
	}
	int x_pos = z + 630;
	int y_pos = stoi(i.substr(0, 1)) * 64 + 50;
	auto* num = new Fl_Box(FL_NO_BOX, x_pos, y_pos, 0, 0, ""); num->copy_label(setdp(2, xy).c_str());
	num->align(FL_ALIGN_RIGHT_TOP); num->labelfont(FL_HELVETICA); num->labelsize(30);
	num->hide();
	numBoard.push_back(num);
}

string Game::AskStr(string qText) {
	inpText->copy_label(qText.c_str()); inpField->take_focus(); inpText->show(); inpField->show();
	inp = "";
	while (Fl::event_key() != FL_Enter) {
		Fl::wait(0);
	}
	inp = inpField->value(); inpField->value("");
	inpText->hide(); inpField->hide();
	Fl::e_keysym = FL_Left;
	return inp;
}

string Game::askStr(string qText) {
	string inp = AskStr(qText);
	AskStr("");
	return inp;
}

void Game::dispText(string qText) {
	vector<string> qList = split(qText, '\n');
	string disp;
	for (int i = 0; i < qList.size(); i++) {
		disp += (qList[i] + "\n");
		if (i % 5 == 4) {
			askStr(disp + "\nAre you ready to continue?");
			disp = "";
		}
	}
	if (qList.size() % 5 != 0) {
		askStr(disp + "\nAre you ready to continue?");
	}
}

void Game::finGame() {
	string winner = "winners are";
	if (numPerPlace[0] == 1) {
		winner = "winner is";
	}
	string pos = finGameTransform();
	smt->copy_label(("The " + winner + "... " + pos).c_str());
	smt->show();
	this_thread::sleep_for(chrono::milliseconds(500));
	int size = numPerPlace.size();
	string sm;
	numbers = { "1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th", "19th", "20th", "21st", "22nd", "23rd", "24th", "25th", "26th", "27th", "28th", "29th", "30th" };
	for (int counter = 0; counter < size; counter++) {
		pos = finGameTransform();
		sm += (numbers[0] + ": " + pos + "\n");
		for (int i = 0; i < numPerPlace[0]; i++) {
			finplayers.erase(finplayers.begin());
		}
		numPerPlace.erase(numPerPlace.begin()); numbers.erase(numbers.begin());
	}
	w->copy_label(sm.c_str());
	w->show();
}

string Game::finGameTransform() {
	vector<string> pl;
	for (int i = 0; i < numPerPlace[0]; i++) {
		pl.push_back(finplayers[i].getName());
	}
	return join(pl, ", ");
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

string setdp(int dp, int i) {
	string output;
	string I = to_string(i);
	if (I.size() < dp) {
		while (output.size() < dp - 1) { output += "0"; }
	}
	output += I;
	return output;
}

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <thread>
#include <chrono>
#include <functional>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
using namespace std;

string join(vector<string> initList, const string& separator = "");
string intJoin(vector<int> initList, const string& separator = "", const string& fill = "");
vector<string> split(string initStr, char sep);
int choice(vector<int> list);
string setdp(int dp, int i);

extern vector<string> numbers;

class Player {
private:
	string m_name;
	vector<int> m_nums;
public:
	Player(string name);
	vector<int>* getNums() { return &m_nums; }
	void removeNum(int num) { m_nums.erase(find(m_nums.begin(), m_nums.end(), num)); }
	string getName() { return m_name; }
};

class Game {
public:
	static const int m_cardlen = 5;
	static const int m_totalnums = 16;
	vector<Player> the_players;
	vector<Player> finplayers;
	vector<int> numPerPlace{};
	vector<Fl_Box*> numBoard{};
	Fl_Box* inpText = new Fl_Box(FL_NO_BOX, 60, 665, 0, 0, ""); Fl_Input* inpField = new Fl_Input(60, 685, 360, 40, ""); string inp;
	Fl_Box* smt = new Fl_Box(FL_NO_BOX, 30, 30, 0, 0, ""); Fl_Box* w = new Fl_Box(FL_NO_BOX, 30, 60, 0, 0, "");
	Fl_Window* win;
	bool showNum = true;
	//private:
	string AskStr(string qText);
public:
	Game();
	void playersInit();
	void addPlayer(Player player) { the_players.push_back(player); }
	void getnumbers(Fl_Box* numDisp);
	void num_maker(int counter);
	string askStr(string qText);
	void dispText(string qText);
	void finGame();
	string finGameTransform();
};

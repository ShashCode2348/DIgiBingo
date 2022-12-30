#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <thread>
#include <chrono>
#include <functional>
using namespace std;

string join(vector<string> initList, const string& separator = "");
string intJoin(vector<int> initList, const string& separator = "", const string& fill = "");
int choice(vector<int> list);
extern vector<string> numbers;

class Player {
private:
	string m_name;
	vector<int> m_nums;
public:
	Player(string name);
	vector<int>* getNums() { return &m_nums; }
	void removeNum(int num) {m_nums.erase(find(m_nums.begin(),m_nums.end(), num));}
	string getName() { return m_name; }
};

class Game {
public:
	static const int m_cardlen = 15;
	static const int m_totalnums = 91;
	vector<int> multiples_of_10;
	vector<Player> the_players;
	vector<Player> finplayers;
	vector<int> numPerPlace{};
public:
	Game();
	void playersInit();
	void addPlayer(Player player) { the_players.push_back(player); }
	void getnumbers();
};


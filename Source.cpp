#include "Functions.h"

int main() {
	//Intro
	cout << "Welcome to DigiBingo(2 - 30 players)!" << endl;
	cout << "DigiBingo:\n    1. Asks for details\n    2. Makes each player a card of numbers\n    3. Chooses a random number not chosen already and shows which people have that number\n    4. Displays the winner and the order of players(who came 1st / 2nd / last)" << endl;
	cout << "So..." << endl;
	this_thread::sleep_for(chrono::milliseconds(500));
	cout << "Let\'s get started." << endl;

	//Setup
	Game game;
	game.playersInit();

	//Calling the numbers
	game.getnumbers();

	//Who wins?
	string winner = "winners are";
	if (game.numPerPlace[0] == 1) {
		winner = "winner is";
	}
	cout << "The " << winner << "... " << flush;
	this_thread::sleep_for(chrono::milliseconds(500));
	transform(game.finplayers.begin(), game.finplayers.begin() + game.numPerPlace[0] - 1, ostream_iterator<string>(cout, ", "), [](Player p) { return p.getName(); });
	cout << game.finplayers[game.numPerPlace[0] - 1].getName() << endl;
	int size = game.numPerPlace.size();
	numbers = { "1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th", "19th", "20th", "21st", "22nd", "23rd", "24th", "25th", "26th", "27th", "28th", "29th", "30th" };
	for (int counter = 0; counter < size; counter++) {
		cout << numbers[0] << ": " << flush;
		transform(game.finplayers.begin(), game.finplayers.begin() + game.numPerPlace[0] - 1, ostream_iterator<string>(cout, ", "), [](Player p) { return p.getName(); });
		cout << game.finplayers[game.numPerPlace[0] - 1].getName() << endl;
		for (int i = 0; i < game.numPerPlace[0]; i++) {
			game.finplayers.erase(game.finplayers.begin());
		}
		game.numPerPlace.erase(game.numPerPlace.begin()); numbers.erase(numbers.begin());
	}
	return 0;
}
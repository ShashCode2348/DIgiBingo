#include "Functions.h"

int main() {
	//FLTK Setup & Intro
	Fl::scheme("gtk+");
	auto* win = new Fl_Window(40, 10, 1470, 810, "DigiBingo");
	auto* g1 = new Fl_Group(0, 0, 1470, 810, "");
	g1->begin();
	auto* introLabel = new Fl_Box(FL_NO_BOX, 40, 15, 0, 0, "Welcome to DigiBingo(2 - 30 players)! \n"
		"DigiBingo:\n    1. Asks for details\n    2. Makes each player a card of numbers\n    "
		"3. Chooses a random number not chosen already and shows which people have that number\n    "
		"4. Displays the winner and the order of players(who came 1st / 2nd / last)");
	introLabel->align(FL_ALIGN_RIGHT_TOP); introLabel->labelfont(FL_HELVETICA);  introLabel->labelsize(18);
	introLabel->show();
	win->show();

	Game game;
	game.playersInit();
	auto* chosenLabel = new Fl_Box(FL_NO_BOX, 245, 289, 0, 0, "The chosen number is:");
	chosenLabel->align(FL_ALIGN_RIGHT_TOP); chosenLabel->labelfont(FL_HELVETICA); chosenLabel->labelsize(20);
	chosenLabel->show();
	auto* chosenNum = new Fl_Box(FL_NO_BOX, 245, 484, 0, 0, "0");
	chosenNum->align(FL_ALIGN_RIGHT_TOP); chosenNum->labelfont(FL_HELVETICA); chosenNum->labelsize(245);
	chosenNum->show();
	g1->end();

	//Calling the numbers
	game.getnumbers(chosenNum);

	//Who wins?
	g1->clear();
	string winner = "winners are";
	if (game.numPerPlace[0] == 1) {
		winner = "winner is";
	}
	transform(game.finplayers.begin(), game.finplayers.begin() + game.numPerPlace[0] - 1, ostream_iterator<string>(cout, ", "), [](Player p) { return p.getName(); });
	auto* smt = new Fl_Box(FL_NO_BOX, 30, 30, 0, 0, ("The " + winner + "... " + game.finplayers[game.numPerPlace[0] - 1].getName()).c_str());
	smt->align(FL_ALIGN_RIGHT_TOP); smt->labelfont(FL_HELVETICA); smt->labelsize(18);
	smt->show();
	this_thread::sleep_for(chrono::milliseconds(500));
	int size = game.numPerPlace.size();
	string sm;
	numbers = { "1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th", "19th", "20th", "21st", "22nd", "23rd", "24th", "25th", "26th", "27th", "28th", "29th", "30th" };
	for (int counter = 0; counter < size; counter++) {
		cout << numbers[0] << ": " << flush;
		transform(game.finplayers.begin(), game.finplayers.begin() + game.numPerPlace[0] - 1, ostream_iterator<string>(cout, ", "), [](Player p) { return p.getName(); });
		sm += (numbers[0] + ": " + game.finplayers[game.numPerPlace[0] - 1].getName() + "\n");
		for (int i = 0; i < game.numPerPlace[0]; i++) {
			game.finplayers.erase(game.finplayers.begin());
		}
		game.numPerPlace.erase(game.numPerPlace.begin()); numbers.erase(numbers.begin());
	}
	auto* w = new Fl_Box(FL_NO_BOX, 240, 30, 0, 0, sm.c_str());
	w->align(FL_ALIGN_RIGHT_TOP); w->labelfont(FL_HELVETICA); w->labelsize(20);
	w->show();
	return Fl::run();
}
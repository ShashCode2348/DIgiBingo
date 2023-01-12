#include "Functions.h"

int main() {
	//FLTK Setup & Intro
	Fl::scheme("gtk+");
	auto* win = new Fl_Window(40, 10, 1470, 770, "DigiBingo");
	auto* introLabel = new Fl_Box(FL_NO_BOX, 40, 15, 0, 0, "Welcome to DigiBingo(2 - 30 players)! \n"
		"DigiBingo:\n    1. Asks for details\n    2. Makes each player a card of numbers\n    "
		"3. Chooses a random number not chosen already\n    and shows which people have that number\n    "
		"4. Displays the winner and the position of players");
	introLabel->align(FL_ALIGN_RIGHT_TOP); introLabel->labelfont(FL_HELVETICA);  introLabel->labelsize(21);
	introLabel->show();

	Game game;
	auto* chosenLabel = new Fl_Box(FL_NO_BOX, 85, 216, 0, 0, "The chosen number is:");
	chosenLabel->align(FL_ALIGN_RIGHT_TOP); chosenLabel->labelfont(FL_HELVETICA); chosenLabel->labelsize(30);
	chosenLabel->show();
	auto* chosenNum = new Fl_Box(FL_NO_BOX, 85, 261, 0, 0, "");
	chosenNum->align(FL_ALIGN_RIGHT_TOP); chosenNum->labelfont(FL_HELVETICA); chosenNum->labelsize(245);
	chosenNum->show();
	win->show();
	game.playersInit();

	//Calling the numbers
	game.getnumbers(chosenNum);

	//Who wins?
	introLabel->hide(); chosenLabel->hide(); chosenNum->hide();
	game.finGame();
	return Fl::run();
}

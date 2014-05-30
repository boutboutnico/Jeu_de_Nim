//============================================================================
// Name        : Jeu_de_Nim.cpp
// Author      : 
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <iterator>

#include "player.h"
#include "board.h"
#include "ia_minmax.h"

using namespace std;

// 16 Sitcks
// 2 Players
// Remove 1,2 or 3 sticks then next player
// Player who remove the last stick looses.

int waitPlayersMove(const Board& b, const Player& p)
{
	int sticks = 0;

	do
	{
//		cout << p << ">> Enter 1, 2 or 3: ";
		cin >> sticks;

		if (b.isValidMove(sticks) == false) cout << "Invalid move" << endl;
//		else cout << endl;

	} while (b.isValidMove(sticks) == false);

	return sticks;
}

int main()
{
	cout << "-----	Jeu de Nim	-----" << endl;

	IA_MinMax ia_minmax;
	Player p1("Player_1");
	Player p2("Player_2");

	Board board(p1, ia_minmax.getPlayer());
//	Board board(p1, p2);
	cout << board;

	int move = 0;
	const Player* p_c = NULL;

	while (board.isOver() == false)
	{
		p_c = &board.getCurrentPlayer();

		cout << ">> " << *p_c << " " << flush;

		if (*p_c == p1 || *p_c == p2)
		{
			move = waitPlayersMove(board, *p_c);
		}
		else
		{
			move = ia_minmax.compute(board, 2);
			cout << endl;
		}

		cout << "Move>> " << move << endl;

		// Play move and load next player
		board.executeMove(move);

		cout << board;
	}

	cout << "Winner is ";
	if (board.isWinner(p1)) cout << p1 << endl;
	else cout << ia_minmax.getPlayer() << endl;

	cout << "-----	End of Game	-----" << endl;
	return 0;
}

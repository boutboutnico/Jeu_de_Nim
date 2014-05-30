/*
 * board.h
 *
 *  Created on: 30 mai 2014
 *      Author: nboutin
 */

#ifndef BOARD_H_
#define BOARD_H_

#include <iostream>
#include <iomanip>
#include <vector>
#include <iterator>

class Board
{
public:
	static const uint8_t N_DEFAULT_STICKS = 16;
	static const uint8_t N_MIN_MOVE = 1;
	static const uint8_t N_MAX_MOVE = 3;

	Board(Player& p1, Player& p2, const uint8_t n_sticks = N_DEFAULT_STICKS) :
			p1(p1),
			p2(p2),
			p_current(&p1),
			p_winner(false, NULL),
			_n_total_sticks(n_sticks),
			_n_remaining_sticks(n_sticks)
	{
	}

	inline int8_t getRemainingSticks() const
	{
		return _n_remaining_sticks;
	}

	inline int8_t getTotalSticks() const
	{
		return _n_total_sticks;
	}

	inline const Player& getCurrentPlayer()
	{
		return *p_current;
	}

	inline void nextPlayer()
	{
		if (p_current == &p1) p_current = &p2;
		else p_current = &p1;
	}

	inline bool isValidMove(uint8_t n_sticks) const
	{
		return (n_sticks >= N_MIN_MOVE && n_sticks <= N_MAX_MOVE && n_sticks <= _n_remaining_sticks) ?
				true : false;
	}

	inline bool isOver() const
	{
		return (_n_remaining_sticks > 0) ? false : true;
	}

	inline bool isWinner(const Player& p)
	{
		if (p_winner.first == true && p == *p_winner.second) return true;
		else return false;
	}

	bool executeMove(uint8_t move)
	{
//		std::cout << __func__ << " p:" << *p_current << ", m:" << (int) move << std::endl;

		if (isValidMove(move) == true)
		{
			_n_remaining_sticks -= move;

			if (isOver())
			{
				p_winner.first = true;
				if (*p_current == p1) p_winner.second = &p2;
				else p_winner.second = &p1;
			}

			nextPlayer();
			return true;
		}
		else return false;
	}

	void undoMove(uint8_t move)
	{
		_n_remaining_sticks += move;
		nextPlayer();
	}

	friend std::ostream& operator<<(std::ostream&, const Board&);

private:
	const Player& p1;
	const Player& p2;
	const Player* p_current;

	std::pair<bool, const Player*> p_winner;

	uint8_t _n_total_sticks;
	uint8_t _n_remaining_sticks;

};

std::ostream& operator<<(std::ostream& out, const Board& b)
{

	for (uint8_t i = 1; i <= b._n_total_sticks; i++)
	{
		if ((i % 5) == 0 || i == 1)
		{
			out << std::setw(2) << std::left << static_cast<int>(i);
		}
		else
		{
			out << std::setw(2) << std::left << " ";
		}
	}
	out << std::endl;

	for (uint8_t i = 1; i <= b._n_remaining_sticks; i++)
	{
		out << "| ";
	}

	for (uint8_t i = b._n_remaining_sticks + 1; i <= b._n_total_sticks; i++)
	{
		out << ". ";
	}

	out << "[" << (int)b._n_remaining_sticks << "]";

	return out << std::endl;
}

#endif /* BOARD_H_ */

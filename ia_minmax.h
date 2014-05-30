/*
 * ia_minmax.h
 *
 *  Created on: 30 mai 2014
 *      Author: nboutin
 */

#ifndef IA_MINMAX_H_
#define IA_MINMAX_H_

#include <iostream>

#include "board.h"

class IA_MinMax
{
public:
	IA_MinMax() :
			_player("Player_IA")
	{

	}

	inline Player& getPlayer()
	{
		return _player;
	}

	uint8_t compute(Board& b, int level)
	{
		int8_t max_val = -100;
		uint8_t best_move = 0;

		// For all moves
		for (int i = Board::N_MIN_MOVE; i <= Board::N_MAX_MOVE; i++)
		{
//			std::cout << __PRETTY_FUNCTION__ << " i:" << i << ", l:" << level << std::endl;

			// Play current move
			if (b.executeMove(i))
			{
				int8_t val = computeMin(b, level - 1);

				if (val > max_val)
				{
					max_val = val;
					best_move = i;
				}

				b.undoMove(i);
			}
		}

		return best_move;
	}

	int8_t computeMin(Board& b, int level)
	{
//		std::cout << __PRETTY_FUNCTION__ << " l:" << level << std::endl;

		if (level == 0 || b.isOver() == true) return evalBoard(b);

		int8_t min_val = 100;

		// For all moves
		for (int i = Board::N_MIN_MOVE; i <= Board::N_MAX_MOVE; i++)
		{
//			std::cout << __PRETTY_FUNCTION__ << " i:" << i << ", l:" << level << std::endl;

			// Play current move
			if (b.executeMove(i))
			{
				int8_t val = computeMax(b, level - 1);

				if (val < min_val)
				{
					min_val = val;
				}

				b.undoMove(i);
			}
		}

		return min_val;
	}

	int8_t computeMax(Board& b, int level)
	{
//		std::cout << __PRETTY_FUNCTION__ << " l:" << level << std::endl;

		if (level == 0 || b.isOver() == true) return evalBoard(b);

		int8_t max_val = -100;

		// For all moves
		for (int i = Board::N_MIN_MOVE; i <= Board::N_MAX_MOVE; i++)
		{
//			std::cout << __PRETTY_FUNCTION__ << " i:" << i << ", l:" << level << std::endl;

			// Play current move
			if (b.executeMove(i))
			{
				int8_t val = computeMin(b, level - 1);

				if (val > max_val)
				{
					max_val = val;
				}

				b.undoMove(i);
			}
		}

		return max_val;
	}

	int8_t evalBoard(Board& b)
	{
		int8_t result = 0;

		// Game is not over, it is a draw
		if (b.isOver() != true)
		{
			result = 0;
		}
		else if (b.isWinner(_player))
		{
			result = b.getTotalSticks();
		}
		else
		{
			result = -b.getTotalSticks();
		}

//		std::cout << __PRETTY_FUNCTION__ << " r:" << (int) result << std::endl;

		return result;
	}

private:
	Player _player;

};

#endif /* IA_MINMAX_H_ */

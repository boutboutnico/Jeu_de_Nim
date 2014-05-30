/*
 * player.h
 *
 *  Created on: 30 mai 2014
 *      Author: nboutin
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>

class Player
{
	friend std::ostream& operator<<(std::ostream& out, const Player p);

public:
	Player(const std::string& name) :
			_name(name)
	{
	}

	bool operator ==(const Player &p) const
	{
		return (_name == p._name) ? true : false;
	}

private:
	std::string _name;
};

std::ostream& operator<<(std::ostream& out, const Player p)
{
	return out << p._name;
}

#endif /* PLAYER_H_ */

#include <algorithm>
#include <iterator>
#include <iostream>
#include <fstream>

#include "maze_turner.h"

MazeTurner::MazeTurner(std::string fileName) : mMyMap(fileName)
{
	GetMap();
}

void MazeTurner::GetMap()
{
    std::ifstream mapFile(mMyMap.c_str());

    // new lines will be skipped unless we stop it from happening:    
    mapFile.unsetf(std::ios_base::skipws);

    char firstLine[256];
    mapFile.getline(firstLine, 256);

    std::string firstLineStr(firstLine);
    mMapSize.x = firstLineStr.length();

    // count the newlines with an algorithm specialized for counting:
    mMapSize.y = std::count(
        std::istream_iterator<char>(mapFile),
        std::istream_iterator<char>(), 
        '\n');
    mMapSize.y += 2; // To counteract the getline, and to count the last line

    // std::cout << "The map is " << mMapSize.x << ":" << mMapSize.y << " in size\n";

    mapFile.clear(); // Files this works with, may not end with just \n
    mapFile.seekg(0, mapFile.beg);

	mMap = new char*[mMapSize.x];
	for (int i = 0; i < mMapSize.x; ++i)
		mMap[i] = new char[mMapSize.y];

	for (int i = 0; i < mMapSize.y; ++i)
	{
	    char mapLine[mMapSize.x];
	    mapFile.getline(mapLine, mMapSize.x+1);
	    for (int j = 0; j < mMapSize.x; ++j)
	    {
	    	mMap[j][i] = mapLine[j];
	    	if (mStartingPoint.direction == UNKNOWN_D)
	    	{
		    	switch(mMap[j][i])
		    	{
		    		case '>':
		    			mStartingPoint.direction = EAST;
		    			break;
		    		case '<':
		    			mStartingPoint.direction = WEST;
		    			break;
		    		case '^':
		    			mStartingPoint.direction = NORTH;
		    			break;
		    		case 'V':
		    			mStartingPoint.direction = SOUTH;
		    			break;
		    	}
		    	if (mStartingPoint.direction != UNKNOWN_D)
		    	{
		    		mStartingPoint.x = j;
					mStartingPoint.y = i;
		    	}
		    }
	    	// std::cout << mMap[j][i];
	    }
	    // std::cout << "\n";
	}
	// std::cout << "My direction is currently " << PrintDirection(mStartingPoint) << "\n";
	mTurnerLocation = mStartingPoint;
}

std::string MazeTurner::PrintDirection(const Coordinates& coord)
{
	std::string directionStr = "";

	switch(coord.direction)
	{
		case EAST:
			directionStr = "EAST";
			break;
		case WEST:
			directionStr = "WEST";
			break;
		case NORTH:
			directionStr = "NORTH";
			break;
		case SOUTH:
			directionStr = "SOUTH";
			break;
		default:
			directionStr = "UNKNOWN";
	}
	return directionStr;
}

bool MazeTurner::NavigateMap()
{
	bool done = false;
	unsigned int move = MOVE;
	// std::cout << "My current location is " << mTurnerLocation.x << ":" 
		// << mTurnerLocation.y << " and my direction is " << mTurnerLocation.direction << "\n";
	sleep(1);
	switch(mTurnerLocation.direction)
	{
		case EAST:
			done = TravelEast(move);
			break;
		case WEST:
			done = TravelWest(move);
			break;
		case NORTH:
			done = TravelNorth(move);
			break;
		case SOUTH:
			done = TravelSouth(move);
			break;
	}
}

bool MazeTurner::TravelEast(unsigned int &move)
{
	// std::cout << "Moving East\n";
	mTurnerLocation.direction = EAST; 
	bool done = false;
	for (int i = 0; i < move; ++i)
	{
		if(mTurnerLocation.x < mMapSize.x)
		{
			switch(CheckMove(mTurnerLocation.x+1, mTurnerLocation.y))
			{
				case SPACE:
					++mTurnerLocation.x;
					TravelEast(move);
					break;
				case WALL:
					if (CheckMove(mTurnerLocation.x, mTurnerLocation.y+1))
					{
						TravelSouth(move);
					}
					else if (CheckMove(mTurnerLocation.x, mTurnerLocation.y-1))
					{
						TravelNorth(move);
					}
					else
					{
						TravelWest(move);
					}
					break;
				case EXIT:
					move = 0;
					done = true;
					break;
			}
		}
	}
	return done;
}

bool MazeTurner::TravelWest(unsigned int &move)
{
	// std::cout << "Moving West\n";
	mTurnerLocation.direction = WEST; 
	bool done = true;
	for (int i = 0; i < move; ++i)
	{
		if(mTurnerLocation.x > 0)
		{
			switch(CheckMove(mTurnerLocation.x-1, mTurnerLocation.y))
			{
				case SPACE:
					--mTurnerLocation.x;
					TravelWest(move);
					break;
				case WALL:
					if (CheckMove(mTurnerLocation.x, mTurnerLocation.y-1))
					{
						TravelNorth(move);
					}
					else if (CheckMove(mTurnerLocation.x, mTurnerLocation.y+1))
					{
						TravelSouth(move);
					}
					else
					{
						TravelEast(move);
					}
					break;
				case EXIT:
					move = 0;
					done = true;
					break;
			}
		}
	}
	return done;
}

bool MazeTurner::TravelNorth(unsigned int &move)
{
	// std::cout << "Moving North\n";
	mTurnerLocation.direction = NORTH; 
	bool done = true;
	for (int i = 0; i < move; ++i)
	{
		if(mTurnerLocation.y > 0)
		{
			switch(CheckMove(mTurnerLocation.x, mTurnerLocation.y-1))
			{
				case SPACE:
					--mTurnerLocation.y;
					TravelNorth(move);
					break;
				case WALL:
					if (CheckMove(mTurnerLocation.x+1, mTurnerLocation.y))
					{
						TravelEast(move);
					}
					else if (CheckMove(mTurnerLocation.x-1, mTurnerLocation.y))
					{
						TravelWest(move);
					}
					else
					{
						TravelSouth(move);
					}
					break;
				case EXIT:
					move = 0;
					done = true;
					break;
			}
		}
	}
	return done;
}

bool MazeTurner::TravelSouth(unsigned int &move)
{
	// std::cout << "Moving South\n";
	mTurnerLocation.direction = SOUTH; 
	bool done = true;
	for (int i = 0; i < move; ++i)
	{
		switch(CheckMove(mTurnerLocation.x, mTurnerLocation.y+1))
		{
			case SPACE:
				++mTurnerLocation.y;
				TravelSouth(move);
				break;
			case WALL:
				if (CheckMove(mTurnerLocation.x-1, mTurnerLocation.y))
				{
					TravelWest(move);
				}
				else if (CheckMove(mTurnerLocation.x+1, mTurnerLocation.y))
				{
					TravelEast(move);
				}
				else
				{
					TravelNorth(move);
				}
				break;
			case EXIT:
				move = 0;
				done = true;
				break;
		}
	}
	return done;
}

int MazeTurner::CheckMove(int x, int y)
{
	int valid = UNKNOWN_MM;
	switch(mMap[x][y])
	{
		case '#':
			valid = WALL;
			break;
		case ' ':
			valid = SPACE;
			break;
		case 'E':
			valid = EXIT;
			break;
	}
	return valid;
}


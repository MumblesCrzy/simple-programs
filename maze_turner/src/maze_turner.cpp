#include <algorithm>
#include <iterator>
#include <iostream>
#include <fstream>

#include "maze_turner.h"

MazeTurner::MazeTurner(std::string fileName) : mMyMap(fileName)
{
	mSameDirection = 0;
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
					std::cout << "My starting point is " << mStartingPoint.x+1 << ":" << mStartingPoint.y+1 << "\n";
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

int MazeTurner::NavigateMap()
{
	int status = MOVING;
	unsigned int move = MOVE;
	// std::cout << "My current location is " << mTurnerLocation.x+1 << ":" 
		// << mTurnerLocation+1.y << " and my direction is " << mTurnerLocation.direction << "\n";
	sleep(1);
	while(move >= 0 && status == MOVING)
	{
		switch(mTurnerLocation.direction)
		{
			case EAST:
			{
				status = TravelEast(move);
				break;
			}
			case WEST:
			{
				status = TravelWest(move);
				break;
			}
			case NORTH:
			{
				status = TravelNorth(move);
				break;
			}
			case SOUTH:
			{
				status = TravelSouth(move);
				break;
			}
		}
	}
	// 	std::cout << "My current location is " << mTurnerLocation.x+1 << ":" 
		// << mTurnerLocation.y+1 << " I have " << move << " moves left\n";
	// if (mSameDirection >= MOVE)
	std::cout << "I'm done? " << (status == DONE ? "yes" : "no") << "\n";
	if (status == MOVING)
	{
		if(mTurnerLocation.x == mStartingPoint.x &&
			mTurnerLocation.y == mStartingPoint.y)
		{
			status = IMPOSSIBLE;
		}
		TurnAround();
	}
	else
		status = DONE;

	return status;
}

void MazeTurner::TurnAround()
{
	std::cout << "I'm turning around\n";
	switch(mTurnerLocation.direction)
	{
		case EAST:
			mTurnerLocation.direction = WEST;
			break;
		case WEST:
			mTurnerLocation.direction = EAST;
			break;
		case NORTH:
			mTurnerLocation.direction = SOUTH;
			break;
		case SOUTH:
			mTurnerLocation.direction = NORTH;
			break;
	}
}

int MazeTurner::TravelEast(unsigned int &move)
{
	std::cout << "My current location is " << mTurnerLocation.x+1 << ":" 
		<< mTurnerLocation.y+1 << " I have " << move << " moves left\n";
	// std::cout << "Moving East\n";
	mTurnerLocation.direction = EAST; 
	int status = MOVING;
	while(move > 0)
	{
		if(mTurnerLocation.x < mMapSize.x)
		{
			switch(CheckMove(mTurnerLocation.x+1, mTurnerLocation.y))
			{
				case SPACE:
					++mTurnerLocation.x;
					++mSameDirection;
					--move;
					status = TravelEast(move);
					break;
				case WALL:
					if (CheckMove(mTurnerLocation.x, mTurnerLocation.y+1))
					{
						mSameDirection = 0;
						status = TravelSouth(move);
					}
					else if (CheckMove(mTurnerLocation.x, mTurnerLocation.y-1))
					{
						mSameDirection = 0;
						status = TravelNorth(move);
					}
					else
					{
						mSameDirection = 0;
						status = TravelWest(move);
					}
					break;
				case EXIT:
					++mTurnerLocation.x;
					move = 0;
					status = DONE;
					break;
			}
		}
	}
	return status;
}

int MazeTurner::TravelWest(unsigned int &move)
{
	std::cout << "My current location is " << mTurnerLocation.x+1 << ":" 
		<< mTurnerLocation.y+1 << " I have " << move << " moves left\n";
	// std::cout << "Moving West\n";
	mTurnerLocation.direction = WEST; 
	int status = MOVING;
	while(move > 0)
	{
		if(mTurnerLocation.x > 0)
		{
			switch(CheckMove(mTurnerLocation.x-1, mTurnerLocation.y))
			{
				case SPACE:
					--mTurnerLocation.x;
					++mSameDirection;
					--move;
					status = TravelWest(move);
					break;
				case WALL:
					if (CheckMove(mTurnerLocation.x, mTurnerLocation.y-1))
					{
						mSameDirection = 0;
						status = TravelNorth(move);
					}
					else if (CheckMove(mTurnerLocation.x, mTurnerLocation.y+1))
					{
						mSameDirection = 0;
						status = TravelSouth(move);
					}
					else
					{
						mSameDirection = 0;
						status = TravelEast(move);
					}
					break;
				case EXIT:
					move = 0;
					status = DONE;
					break;
			}
		}
	}
	return status;
}

int MazeTurner::TravelNorth(unsigned int &move)
{
		std::cout << "My current location is " << mTurnerLocation.x+1 << ":" 
		<< mTurnerLocation.y+1 << " I have " << move << " moves left\n";
	// std::cout << "Moving North\n";
	mTurnerLocation.direction = NORTH; 
	int status = MOVING;
	while(move > 0)
	{
		if(mTurnerLocation.y > 0)
		{
			switch(CheckMove(mTurnerLocation.x, mTurnerLocation.y-1))
			{
				case SPACE:
					--mTurnerLocation.y;
					++mSameDirection;
					--move;
					status = TravelNorth(move);
					break;
				case WALL:
					if (CheckMove(mTurnerLocation.x+1, mTurnerLocation.y))
					{
						mSameDirection = 0;
						status = TravelEast(move);
					}
					else if (CheckMove(mTurnerLocation.x-1, mTurnerLocation.y))
					{
						mSameDirection = 0;
						status = TravelWest(move);
					}
					else
					{
						mSameDirection = 0;
						status = TravelSouth(move);
					}
					break;
				case EXIT:
					move = 0;
					status = DONE;
					break;
			}
		}
	}
	return status;
}

int MazeTurner::TravelSouth(unsigned int &move)
{
	std::cout << "My current location is " << mTurnerLocation.x+1 << ":" 
		<< mTurnerLocation.y+1 << " I have " << move << " moves left\n";
	// std::cout << "Moving South\n";
	mTurnerLocation.direction = SOUTH; 
	int status = MOVING;
	while(move > 0)
	{
		switch(CheckMove(mTurnerLocation.x, mTurnerLocation.y+1))
		{
			case SPACE:
				++mTurnerLocation.y;
				++mSameDirection;
				--move;
				status = TravelSouth(move);
				break;
			case WALL:
				if (CheckMove(mTurnerLocation.x-1, mTurnerLocation.y))
				{
					mSameDirection = 0;
					status = TravelWest(move);
				}
				else if (CheckMove(mTurnerLocation.x+1, mTurnerLocation.y))
				{
					mSameDirection = 0;
					status = TravelEast(move);
				}
				else
				{
					mSameDirection = 0;
					status = TravelNorth(move);
				}
				break;
			case EXIT:
				move = 0;
				status = DONE;
				std::cout << "I'm done? " << (status == DONE ? "yes" : "no") << "\n";
				break;
		}
	}
	return status;
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


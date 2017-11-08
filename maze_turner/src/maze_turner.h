#include <string>

#define MOVE 6

enum DIRECTION 
{
	UNKNOWN_D = -1,
	EAST,
	WEST,
	NORTH,
	SOUTH
};

enum MAP_MARKER
{
	UNKNOWN_MM = -1,
	WALL,
	SPACE,
	EXIT
};

struct Coordinates
{
	unsigned int x;
	unsigned int y;
	short direction;
	Coordinates() {	direction = UNKNOWN_D; x = 0; y = 0; }
};

class MazeTurner
{
public:
	MazeTurner(std::string fileName);
	void GetMap();
	bool NavigateMap();
private:
	std::string PrintDirection(const Coordinates& coord);
	bool TravelEast(unsigned int &move);
	bool TravelWest(unsigned int &move);
	bool TravelNorth(unsigned int &move);
	bool TravelSouth(unsigned int &move);
	int CheckMove(int x, int y);

	Coordinates mMapSize;
	Coordinates mStartingPoint;
	Coordinates mTurnerLocation;
	std::string mMyMap;
	char **mMap;
};
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

enum STATUS
{
	IMPOSSIBLE = -1,
	MOVING,
	DONE
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
	int NavigateMap();
private:
	std::string PrintDirection(const Coordinates& coord);
	void TurnAround();
	int TravelEast(unsigned int &move);
	int TravelWest(unsigned int &move);
	int TravelNorth(unsigned int &move);
	int TravelSouth(unsigned int &move);
	int CheckMove(int x, int y);

	int mSameDirection;
	Coordinates mMapSize;
	Coordinates mStartingPoint;
	Coordinates mTurnerLocation;
	std::string mMyMap;
	char **mMap;
};
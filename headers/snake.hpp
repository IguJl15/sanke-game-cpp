#include "node.hpp"

enum Direction
{
	Up, Down, Left, Right
};

class Snake
{
public:
	Direction currentDir = Right;
	Node *body;
	bool canChangeDir;

	int length;

	Snake(int xInitialPos, int yInitialPos, unsigned int initLenght);
	~Snake();

	void moveFoward(void);
	void changeDirection(Direction direction);
	void growUp(void);
};

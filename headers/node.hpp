struct Position
{
	float x;
	float y;
};

class Node
{
public:

	Position position;
	Node *next = nullptr;
};

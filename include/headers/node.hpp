#pragma once

struct Position
{
	float x;
	float y;
};

template <typename T>
class Node
{
public:
	T value;
	Node<T> *next = nullptr;
};

class BodyPart : public Node<Position>
{
public:	
	// simple bridge to new attribute named position for best understanding
	Position position = value;
};
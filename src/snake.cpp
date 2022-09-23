#include <stdlib.h>
#include <iostream>
#include "../include/headers/snake.hpp"

#define MAX_LENGTH 1024

Snake::Snake(int xInitPos, int yInitPos, unsigned int initLength = 3)
{

	if (initLength < 1)
		initLength = 1;

	length = initLength;

	body = (BodyPart *)malloc(MAX_LENGTH * sizeof(BodyPart));

	body->position.x = xInitPos;
	body->position.y = yInitPos;
	body->next = nullptr;

	for (int i = 1; i < length; i++)
	{
		// previous
		body[i - 1].next = &body[i];

		// current
		body[i].position.x = body[i - 1].position.x - 1;
		body[i].position.y = body[i - 1].position.y;
		body[i].next = nullptr;
	}
}

void Snake::moveFoward()
{

	for (int i = length - 1; i > 0; i--)
	{
		body[i].position.x = body[i - 1].position.x;
		body[i].position.y = body[i - 1].position.y;
	}

	if (currentDir == Up)
	{
		body[0].position.y--;
	}
	else if (currentDir == Down)
	{
		body[0].position.y++;
	}
	else if (currentDir == Right)
	{
		body[0].position.x++;
	}
	else if (currentDir == Left)
	{
		body[0].position.x--;
	}

	canChangeDir = true;
}

void Snake::changeDirection(Direction direction)
{
	if (direction != currentDir && canChangeDir)
	{
		if (direction == Down)
			currentDir = currentDir == Up ? currentDir : direction;

		if (direction == Up)
			currentDir = currentDir == Down ? currentDir : direction;

		if (direction == Right)
			currentDir = currentDir == Left ? currentDir : direction;

		if (direction == Left)
			currentDir = currentDir == Right ? currentDir : direction;
		canChangeDir = false;
	}
}

void Snake::growUp()
{
	std::cout << "Grow up" << std::endl;
	
	// last body part
	BodyPart* tail = &body[length - 1];
	BodyPart* newTail = &body[length];
	
	newTail->position.x = tail->position.x;
	newTail->position.y = tail->position.y;
	newTail->next = nullptr;

	length++;
}

Snake::~Snake() {}
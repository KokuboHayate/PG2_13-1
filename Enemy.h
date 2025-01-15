#pragma once
#include "Vector2.h"

class Enemy
{
public:
	static int isAlive;

	Enemy(Vector2 pos);
	void Move();
	void Draw();

	Vector2 pos_;
	float radius_;
	float speed_;

};


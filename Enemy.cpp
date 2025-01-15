#include <Novice.h>
#include "Enemy.h"

Enemy::Enemy(Vector2 pos)
{
	isAlive = true;
	pos_.x = pos.x;
	pos_.y = pos.y;
	radius_ = 20.0f;
	speed_ = 10.0f;
}

void Enemy::Move()
{
	if (isAlive) {
		pos_.x += speed_;

		if (pos_.x < radius_ || pos_.x > 1280 - radius_) {
			speed_ *= -1.0f;
		}
	}
}

void Enemy::Draw()
{
	if (isAlive) {
		Novice::DrawEllipse(static_cast<int>(pos_.x), static_cast<int>(pos_.y),
			static_cast<int>(radius_), static_cast<int>(radius_), 0.0f, RED, kFillModeSolid);
	}
}


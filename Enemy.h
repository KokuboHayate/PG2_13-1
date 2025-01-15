#pragma once
#include "Vector2.h"

class Enemy
{
public:
	static int isAlive;

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">初期地点</param>
	Enemy(Vector2 pos);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Move();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	Vector2 pos_;
	float radius_;
	float speed_;

};


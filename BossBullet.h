#pragma once

class BossBullet
{
public:

	void Initialize(int x, int y);

	void Attack1();
	void Attack2();
	void Attack3();

	void Draw();

private:
	static const int BulletNum = 10;

	const int BulletSpeed = 7;

	int BulletX1[BulletNum];
	int BulletY1[BulletNum];
	int BulletR1[BulletNum] = { 64 };

	int Bullet1Shot[BulletNum];
};

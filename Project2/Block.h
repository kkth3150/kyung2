#pragma once
#include <random>

enum TYPE { T, L, O, Z, I, rL, rZ, end_count };
enum ANGLE { d0, d90, d180, d270, d360 };

class Block {
public:
	
	Point position;
	TYPE type;
	Point bcoord[4];
	ANGLE angle;

public:
	
	Block();
	Block(Point p);
	Block(Point p, TYPE t);
	Block(Point p, ANGLE a); //������ t �ޱ� a ����Ÿ��
	Block(Point p, TYPE t, ANGLE a);//������ p Ÿ��t �ޱ� a



	void ChangeType(TYPE t);
	void changeAngle(ANGLE a);
	void changeTypeAndAngle(TYPE t, ANGLE a); // Ÿ���� t, �ޱ��� a�� �ٲٰ�, �ޱ� �� Ÿ�Կ� �´� bricks ���� ������ ����


	TYPE returnRandomType(); // ������ Ÿ���� ����
	ANGLE returnRandomAngle(); // ������ �ޱ��� ����
};
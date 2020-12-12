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
	Block(Point p, ANGLE a); //포지션 t 앵글 a 랜덤타입
	Block(Point p, TYPE t, ANGLE a);//포지션 p 타입t 앵글 a



	void ChangeType(TYPE t);
	void changeAngle(ANGLE a);
	void changeTypeAndAngle(TYPE t, ANGLE a); // 타입을 t, 앵글을 a로 바꾸고, 앵글 및 타입에 맞는 bricks 내용 가져다 오기


	TYPE returnRandomType(); // 랜덤한 타입을 리턴
	ANGLE returnRandomAngle(); // 랜덤한 앵글을 리턴
};
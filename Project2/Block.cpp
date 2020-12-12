#include "pch.h"
#include "Block.h"

//0-0
//1 - 90(По)
//2 - 180
//3 - 270

Point bricks[end_count][d360][4] = {
	{{{0, 1}, {1, 1}, {2, 1}, {1, 2}}, //0
	{{1, 0}, {1, 1}, {1, 2}, {0, 1}}, //90
	{{2, 1}, {1, 1}, {0, 1}, {1, 0}}, //180
	{{1, 2}, {1, 1}, {1, 0}, {2, 1}}},	//270
	// T 

	{{{1, 0}, {1, 1}, {1, 2}, {2, 2}}, //0
	{{2, 1}, {1, 1}, {0, 1}, {0, 2}},	//90
	{{1, 2}, {1, 1}, {1, 0}, {0, 0}},//180
	{{0, 1}, {1, 1}, {2, 1}, {2, 0}}},//270
	// L

	{{{1, 1}, {2, 1},{1, 2}, {2, 2}},   //0
	{{1, 1}, {2, 1},{1, 2}, {2, 2}},	//90
	{{1, 1}, {2, 1},{1, 2}, {2, 2}},	//180
	{{1, 1}, {2, 1},{1, 2}, {2, 2}}},	//270
	// O

	{{{0, 1}, {1, 1},{1, 2}, {2, 2}},  //0
	{{1, 0}, {1, 1},{0, 1}, {0, 2}},	//90
	{{0, 1}, {1, 1},{1, 2}, {2, 2}},	//180
	{{1, 0}, {1, 1},{0, 1}, {0, 2}}},//270
	// Z

	{{{1, 0},{1, 1},{1, 2},{1, 3}},    //0
	{{2, 1},{1, 1},{0, 1},{-1, 1}},	//90
	{{1, 0},{1, 1},{1, 2},{1, 3}},		//180
	{{2, 1},{1, 1},{0, 1},{-1, 1}}},	//270
	// I

	{{{1, 0}, {1, 1}, {1, 2}, {0, 2}}, //0
	{{2, 1}, {1, 1}, {0, 1}, {0, 0}}, //90
	{{1, 2}, {1, 1}, {1, 0}, {2, 0}},  //180
	{{0, 1}, {1, 1}, {2, 1}, {2, 2}}},  //270
	// rL


	{{ {1, 1}, {2, 1},{0, 2}, {1, 2}},  //0
	{{1, 1}, {1, 2},{0, 0}, {0, 1}},  //90
	{{1, 1}, {2, 1},{0, 2}, {1, 2}},    //180
	{{1, 1}, {1, 2},{0, 0}, {0, 1}}}  //270
	// rZ 
};


Block::Block() {
	position = { 0,0 };

	
	changeTypeAndAngle(returnRandomType(), returnRandomAngle());

}


Block::Block(Point p)
{
	position = p;
	changeTypeAndAngle(returnRandomType(), returnRandomAngle());

}


Block::Block(Point p, TYPE t) {

	position = p;
	changeTypeAndAngle(t, returnRandomAngle());

}

Block::Block(Point p, ANGLE a) {
	
	position = p;
	changeTypeAndAngle(returnRandomType(), a);
}

Block::Block(Point p, TYPE t, ANGLE a) {
	
	position = p;
	changeTypeAndAngle(t,a);
}

void Block::ChangeType(TYPE t) {

	type = t;

	for (int i = 0; i < 4; ++i) {

		bcoord[i] = bricks[t][angle][i];

	}

}


void Block::changeAngle(ANGLE a) {

	angle = a; 

	for (int i = 0; i < 4; ++i) {  

		bcoord[i] = bricks[type][a][i];

	}

}

void Block::changeTypeAndAngle(TYPE t, ANGLE a) {

	type = t;
	angle = a;

	for (int i = 0; i < 4; ++i) {

		bcoord[i] = bricks[t][a][i];
	}

}


TYPE Block::returnRandomType() {

	std::default_random_engine dre;
	std::uniform_int_distribution<> uid(0, end_count - 1);

	return (TYPE)uid(dre);
}


ANGLE Block:: returnRandomAngle() {

	std::default_random_engine dre;
	std::uniform_int_distribution<> uid_a(0, d360 - 1);
	
	return (ANGLE)uid_a(dre);
}
#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<time.h>
#include<stdio.h>
#include<math.h>

#define ScWidth 1400
#define ScHeight 700
#define OpWidth 400

using namespace std;

// Dispaly Gameover screen and reset score
void GameOver();

// Draw game board and score / control area
void DrawBoard();

// if enemy hit player this function returns 1 
int EnemyHitPlayer();

// function to convert degree to radian
static double d2r(double degree);

// Player Variables
double px, py; // player X, player Y
int pSize = 20, step = 8;// player size, player speed

// Enemy Variables
// Enemy X, Enemy Y, Enemy Speed
double enemy[3][3] = {0,260,10,0,320,10,0,390,10};
int ei = 1; // enemy index

// Other Variables
char option, txtScore[5];
int score = 0;

int main(){
	// to make sure generation of random numbers
	srand((unsigned) time(0));

	// Initialize Graphics
	int gd = DETECT, gm, err, tmp;
	initgraph( & gd, & gm, "C:\\tc\\bgi");

	int i=0; // Angle (0-360) of ball (player)
	while(1){

		DrawBoard();

		// Drawing outer circle. player revolves at its circumference
		setcolor(WHITE);
		circle(500, 350, 100);

		// if any key is pressed
		if( kbhit()){
			option = getch(); // catch key in option variable
			if(option == 32){ // if key is spacebar
				step = -step; // reverse player direction
			}
		}

		for(int i=0; i<ei; i++){
			// Drawing enemey
			setcolor(YELLOW);
			setfillstyle(1,YELLOW);
			bar(enemy[i][0],enemy[i][1],enemy[i][0]+40,enemy[i][1]+20);

			// if enemy goes beyond player update score
			if( enemy[i][0] >= 600 && enemy[i][0] < 610 ){
				score++;
			}

			// update enemy position
			enemy[i][0] += enemy[i][2];

			// if enemy goes beyond screen reset enemy position
			if( enemy[i][0] >= 1000 ){
				enemy[i][0] = 0; 
				enemy[i][2] = 8+rand()%8;
			}

			// if first enemy goes beyond 300px from left generate next enemy
			if( enemy[i][0] >= 300 && enemy[i][0] < 310 )
				if( ei < 3 )
					ei++;
		}

		// If any of the enemies hit player
		if( EnemyHitPlayer() == 1 ){
			GameOver(); // display game over screen

			// Reset Enemy Positions
			enemy[0][0] = 0; 
			enemy[0][1] = 260;
			enemy[0][2] = 8+rand()%8;
			enemy[1][0] = 0; 
			enemy[1][1] = 320;
			enemy[1][2] = 8+rand()%8;
			enemy[2][0] = 0; 
			enemy[2][1] = 390;
			enemy[2][2] = 8+rand()%8;
		} 

		// Generate x, y coordinates of player from angle (i.e. i)
		px = 500 + -1*sin(d2r(i))*90;
		py = 350 + -1*cos(d2r(i))*90; 

		// drawing player
		setcolor(WHITE);
		setfillstyle(1,WHITE);
		fillellipse(px, py, pSize, pSize);

		// update player position
		i+=step;

		// if player angle is more than 360, take it back to 0
		if( i > 360)
			i = 0;

		delay(40);
		cleardevice();
	}


	getch();
	closegraph();
}


void GameOver(){
	cleardevice(); // clear screen

	setcolor(WHITE);
	// Print Game Over Text
	settextstyle(4,0,9);
	outtextxy(300,300,"Game Over");

	settextstyle(4,0,2);
	outtextxy(500,420,"Press any key to restart...");
	getch();
	score = 0; // reset score
} 

void DrawBoard(){	

	setcolor(WHITE);

	// draw board
	rectangle(0,0,ScWidth-OpWidth,ScHeight);
	rectangle(ScWidth-OpWidth,0,ScWidth,ScHeight);

	// print score
	// itoa function converts number to character array
	settextstyle(4,0,9);
	if( score<10 )
		outtextxy(ScWidth-270, 250, itoa(score,txtScore,10));
	else if( score>=10 )
		outtextxy(ScWidth-320, 250, itoa(score,txtScore,10));

	settextstyle(4,0,1);
	outtextxy(ScWidth-375, 500, "Controls: ");
	outtextxy(ScWidth-300, 550, "Spacebar");
}

int EnemyHitPlayer(){
	for(int i=0; i< ei; i++){
		if( enemy[i][0]+40 >= px-pSize && enemy[i][0] <= px+pSize ){
				if( py+pSize >= enemy[i][1] && py <= enemy[i][1] ){
					return 1;
				}
		}
	}
	return 0;
}

static double d2r(double degree)
{
    double pi = 3.14159265359;
    return (degree * (pi / 180));
} 

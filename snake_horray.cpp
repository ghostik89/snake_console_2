#include <iostream>
//for control moves
#include <conio.h>
#include <Windows.h>

using namespace std;
//indicator for gameover
bool gameover;
//size of field
const int width = 20;
const int height = 20;
//score
int x,y,fruitx,fruity,score;
//snake
int tailx[100], taily[100];
int ntail;
//for move
enum direction {STOP = 0,LEFT,RIGHT,UP,DOWN};
direction dir;

//intialization
void setup(){
	gameover = false;
	dir = STOP;
	x = width / 2 - 1;
	y = height / 2 - 1;
	fruitx = rand() % width;
	fruity = rand() % height;
	score = 0;
}

//for draw field
void draw(){
	//clear screen
	system("cls");
	for (int i = 0; i < width + 1; i++)
		cout<< "#";
	cout<<endl;

	//draw field
	for (int i = 0; i < height; i++){
	
		for (int j = 0; j < width; j++){
			if (j==0 || j == width - 1)
				cout<<"#";
		//draw head of snake
			if (i == y && j == x)
				cout << "0";
			//draw fruit
			else if (i == fruity && j == fruitx)
				cout<<"F";
			//draw tail of snake
			else{
				//for print nothing
				bool print = false;
				for (int k  = 0; k < ntail; k++){
					if (tailx[k] == j && taily[k] == i){
						print = true;
						cout<< "o";
					}
				}
				if (!print)
					cout<<" ";
			}
		}
		cout << endl;
	}
	//draw field
	for (int i = 0; i < width + 1; i++)
		cout<< "#";
	cout<<endl;
	//score
	cout << "Score :" << score << endl;
	cout<<"If you want exit, press x\n";
	//delay
	Sleep(100);
}

//moves of snake
void input(){
	//input keys from user
	if (_kbhit()){
		//if buttom clicked ...
		switch(_getch()){
		case 'a':
			dir = LEFT;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
			//for exit
		case 'x':
			gameover = true;
			break;
		}
	}
}

//logic of game
void logic(){
	//snakes tail move
	int prevx = tailx[0];//error for move vertical
	int prevy = taily[0];
	int prev2x,prev2y;
	tailx[0] = x;
	taily[0] = y;
	//move tail
	for (int i = 1; i < ntail; i++){
		prev2x = tailx[i];
		prev2y = taily[i];
		tailx[i] = prevx;
		taily[i] = prevy;
		prevx = prev2x;
		prevy = prev2y;
	}
	//yet move snake in field
	switch(dir){
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}
	//if wall touch
		if (x > width || x < 0 || y > height || y < 0)
			gameover = true;
		/*if (x >= width - 1)
			x = 0;
		else if (x < 0)
			x = width - 2;

		if (y >= height)
			y = 0;
		else if (y < 0);
			y = height - 1;*/
		//if tail touch
		for (int i = 0; i < ntail;i++){
			if (tailx[i] == x && taily[i] == y)
				gameover = true;
		}
		//if we eat fruit
		if ( x == fruitx && y == fruity){
			score += 10;
			fruitx = rand() % width;
			fruity = rand() % height;
			ntail++;
		}
}

int main(){
	//initialize
	setup();
	char ch;
	cout<<"Welcome to the game"
		<< endl << "Press Y, if you want to play, or N to exit\n";
	cin >> ch;
	//game
	if (ch == 'Y' || ch == 'y'){ 
		while(!gameover){
			draw();
			input();
			logic();
		}
	}
	else
		return 0;
}
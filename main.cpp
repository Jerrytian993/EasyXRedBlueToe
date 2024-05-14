#include <iostream>
#include <easyx/graphics.h>
#include <string>
using namespace std;

//represent initial board
char board_data[3][3] = {
	{'-', '-', '-'},
	{'-', '-', '-'},
	{'-', '-', '-'},
};

//current piece
char current_piece = 'O';

//check if player with character c wins, by going through all possibilities
bool CheckWin(char c) {
	if (board_data[0][0] == c && board_data[0][1] == c && board_data[0][2] == c) 
		return true;
	if (board_data[1][0] == c && board_data[1][1] == c && board_data[1][2] == c) 
		return true;
	if (board_data[2][0] == c && board_data[2][1] == c && board_data[2][2] == c) 
		return true;
	if (board_data[0][0] == c && board_data[1][0] == c && board_data[2][0] == c) 
		return true;
	if (board_data[0][1] == c && board_data[1][1] == c && board_data[1][2] == c) 
		return true;
	if (board_data[0][2] == c && board_data[1][2] == c && board_data[2][2] == c) 
		return true;
	if (board_data[0][0] == c && board_data[1][1] == c && board_data[2][2] == c) 
		return true;
	if (board_data[0][2] == c && board_data[1][1] == c && board_data[2][0] == c) 
		return true;
	return false;
}

//check if it is a draw by checking if all board chars no longer contain '-'
bool CheckDraw() {
	for(int i=0;i<=2;i++){
		for(int j=0;j<=2;j++){
			if(board_data[i][j] == '-')
				return false;
		}
	}
}

//draw functions 1: drawing board
void DrawBoard () {
	line(0,200,600,200);
	line(0,400,600,400);
	line(200,0,200,600);
	line(400,0,400,600);
}

//draw functions 2: each piece
void DrawPiece() {
	for(int i=0;i<=2;i++){
		for(int j=0;j<=2;j++){
			switch (board_data[i][j]) {
			case 'O':
				setfillcolor(RED);
				fillcircle(200*j+100,200*i+100,100);
				break;
			case 'X':
				setfillcolor(BLUE);
				fillcircle(200*j+100,200*i+100,100);
				break;
			case '-':
				break;
			}
		}
	}
}

//draw functions 3: prompt texts
void DrawTipText() {
	static TCHAR str[64];
	TCHAR currentColor[10]; // Allocate enough space for the color string
	if (current_piece == 'O') {
		_tcscpy_s(currentColor, _T("RED"));
	} else {
		_tcscpy_s(currentColor, _T("BLUE"));
	}
	_stprintf_s(str,_T("Current Turn: %s"),currentColor);
	settextcolor(RGB(225,175,45));
	outtextxy(0,0,str);
}

//main function
int main() {
	
	initgraph(600,600);
	
	bool running = true;
	
	ExMessage msg;
	
	BeginBatchDraw();
	
	while(running){
		while(peekmessage(&msg)){
			//check clicking
			if(msg.message == WM_LBUTTONDOWN){
				//get x,y value of the click
				int x = msg.x;
				int y = msg.y;
				int index_x = x / 200;
				int index_y = y / 200;
				//place the piece on board
				if(board_data[index_y][index_x] == '-'){
					board_data[index_y][index_x] = current_piece;
					//switch to the next turn
					if(current_piece == 'X'){
						current_piece = 'O';
					} else {
						current_piece = 'X';
					}
				}
			}
		}
		if(CheckWin('X')){
			MessageBox(GetHWnd(), _T("BLUE WINS"), _T("GAME OVER"), MB_OK);
			running = false;
		} else if(CheckWin('O')){
			MessageBox(GetHWnd(), _T("RED WINS"), _T("GAME OVER"), MB_OK);
			running = false;
		} else if(CheckDraw()){
			MessageBox(GetHWnd(), _T("DRAW"), _T("GAME OVER"), MB_OK);
			running = false;
		}
		
		cleardevice();
		DrawBoard();
		DrawPiece();
		DrawTipText();
		FlushBatchDraw();
	}
	EndBatchDraw();
	return 0;
}

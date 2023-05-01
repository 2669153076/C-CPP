#include<stdio.h>
#include<graphics.h>
#include<mmsystem.h>
#include<math.h>

#pragma comment(lib,"winmm.lib")	//播放音乐库文件

int flag = 0;	//表示下棋次数
int board[20][20] = { 0 };	//0表示棋盘没有棋子 1黑棋 2白棋

void initGame();	//画出棋盘
int judge(int a, int b);	//判断输赢
void playChess();	//下棋

int main() {
	initGame();
	playChess();
	
	getchar();
	return 0;
}

void initGame() {
	initgraph(1444, 1000);	//创建窗口
	//setbkcolor(BLUE);	//设置窗口背景颜色
	//cleardevice();	//刷新

	//贴图
	loadimage(NULL, _T("./src/bg.jpg"));

	//背景音乐	mci多媒体控制接口
	mciSendString(_T("open ./src/bg.mp3 alias bgmusic"), 0, 0, 0);
	mciSendString(_T("play bgmusic"), 0, 0, 0);

	//绘制棋盘
	//setlinecolor(GREEN);
	//画线 20 20 50 50 1000 1000
	for (int i = 0; i <= 1000; i += 50) {
		line(0, i, 1000, i);
		line(i, 0, i, 1000);
	}
	line(1001, 0, 1001, 1000);

	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 50;
	f.lfWeight = 50;
	_tcscpy_s(f.lfFaceName, _T("微软雅黑"));
	settextstyle(&f);
	outtextxy(1100, 400, _T("Player1:Black"));
	outtextxy(1100, 600, _T("Player2:White"));
}


void playChess() {
	MOUSEMSG m;		
	int x = 0, y = 0;	//坐标 
	int a = 0, b = 0;	//行列

	while (1) {
		m = GetMouseMsg();

		//获取距离鼠标最近的点的坐标信息
		for (int i = 1; i <= 20; i++) {
			for (int j = 1; j <= 20; j++) {
				if (abs(m.x - i * 50) < 15 && abs(m.y - j * 50) < 15) {
					x = i * 50;
					y = j * 50;
					a = i;
					b = j;
				}
			}
		}
		
		if (m.uMsg == WM_LBUTTONDOWN) {
			//棋子重复下在同一位置
			if (board[a][b] != 0) {
				continue;
			}

			//判断黑白子
			if (flag % 2 == 0) {
				setfillcolor(BLACK);
				solidcircle(x, y, 15);
				board[a][b] = 1;
			}
			else {
				setfillcolor(WHITE);
				solidcircle(x, y, 15);
				board[a][b] = 2;
			}
			flag++;
		}
		
		if (judge(a, b)) {
			if (flag % 2 == 0) {
				MessageBox(NULL, "Player2 Win", "Game Over", MB_OK);
				exit(0);
			}
			else{
				MessageBox(NULL, "Player1 Win", "Game Over", MB_OK);
				exit(0);
			}
		}
	}
}

int judge(int a, int b) {
	int i, j;
	int t = 2 - flag % 2;	//1 判断黑子是否胜利  2 判断白子
	//横向
	for (i = a - 4, j = b; i <= a; i++) {
		if (i > 0 && i < 15 && t == board[i][j] && t == board[i + 1][j] && t == board[i + 2][j] && t == board[i + 3][j] && t == board[i + 4][j])
			return 1;
	}

	//纵向
	for (i = a, j = b - 4; j <= b; j++) {
		if (j > 0 && j < 15 && t == board[i][j] && t == board[i][j + 1] && t == board[i][j + 2] && t == board[i][j + 3] && t == board[i][j + 4])
			return 1;
	}

	//由左上至右下
	for (i = a - 4, j = b - 4; i <= a,j <= b; i++, j++) {
		if (i > 0 && i < 15 && j > 0 && j < 15 && t == board[i][j] && t == board[i + 1][j + 1] && t == board[i + 2][j + 2] && t == board[i + 3][j + 3] && t == board[i + 4][j + 4])
			return 1;
	}

	//右上至左下
	for (i = a + 4, j = b - 4; i >= a, j <= b; i--, j++) {
		if (i > 0 && i < 15 && j > 0 && j < 15 && t == board[i][j] && t == board[i - 1][j + 1] && t == board[i - 2][j + 2] && t == board[i - 3][j + 3] && t == board[i - 4][j + 4])
			return 1;
	}

	return 0;
}
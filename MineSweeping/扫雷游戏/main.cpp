#include<graphics.h>
#include<conio.h>
#include<iostream>
#include<time.h>
#include<string>
using namespace std;

//定义布局大小
#define N 10
//地雷的个数
#define Num 10
//定义地图
//地图初始化为0
int map[N + 2][N + 2] = { 0 };
int tmap[N + 2][N + 2] = { 
	{10,10,10,10,10,10,10,10,10,10,10,10},
	{ 10,10,10,10,10,10,10,10,10,10,10,10 },
	{ 10,10,10,10,10,10,10,10,10,10,10,10 },
	{ 10,10,10,10,10,10,10,10,10,10,10,10 },
	{ 10,10,10,10,10,10,10,10,10,10,10,10 },
	{ 10,10,10,10,10,10,10,10,10,10,10,10 },
	{ 10,10,10,10,10,10,10,10,10,10,10,10 },
	{ 10,10,10,10,10,10,10,10,10,10,10,10 },
	{ 10,10,10,10,10,10,10,10,10,10,10,10 },
	{ 10,10,10,10,10,10,10,10,10,10,10,10 },
	{ 10,10,10,10,10,10,10,10,10,10,10,10 },
	{ 10,10,10,10,10,10,10,10,10,10,10,10 },
	
    };
//定义图片资源
IMAGE images[13];
//定义一个鼠标消息对象
MOUSEMSG msg = { 0 };
int win = 0;
//没有点击到炸弹时
bool flag = false;
//随机生成十个雷
void ProRandMine() {

	srand((unsigned int)time(NULL));
	int x;
	int y;
	for (int j = 1;j <= Num;) {
		x = rand() % 10 + 1;
		y = rand() % 10 + 1;
		if (map[x][y] != -1) {
			map[x][y] = -1;
			j++;
		}
	}
}
//计算每个中心周围的地雷个数，生成一个雷图
void calNumMine() {
	for (int i = 1;i <= N;i++) {
		for (int j = 1;j <= N;j++) {
			//当没有踩到地雷时
			if (map[i][j] != -1) {
				for (int x = i - 1;x <= i + 1;x++) {
					for (int y = j - 1;y <= j + 1;y++) {
					    //如果周围存在地雷，累加1
						if (map[x][y] == -1) {
							map[i][j]++;
						}
					}
				 }

			}
			cout << map[i][j] << '\t';
		}
		cout << endl;
	}
}
//图片资源初始化
void initImage() {

	loadimage(&images[0], L"J:/C++/pictures/0.jpg", 64, 64);
	loadimage(&images[1], L"J:/C++/pictures/1.jpg", 64, 64);
	loadimage(&images[2], L"J:/C++/pictures/2.jpg", 64, 64);
	loadimage(&images[3], L"J:/C++/pictures/3.jpg", 64, 64);
	loadimage(&images[4], L"J:/C++/pictures/4.jpg", 64, 64);
	loadimage(&images[5], L"J:/C++/pictures/5.jpg", 64, 64);
	loadimage(&images[6], L"J:/C++/pictures/6.jpg", 64, 64);
	loadimage(&images[7], L"J:/C++/pictures/7.jpg", 64, 64);
	loadimage(&images[8], L"J:/C++/pictures/8.jpg", 64, 64);
	loadimage(&images[9], L"J:/C++/pictures/9.jpg", 64, 64);
	loadimage(&images[10], L"J:/C++/pictures/空.jpg", 64, 64);
	loadimage(&images[11], L"J:/C++/pictures/雷.jpg", 64, 64);
	loadimage(&images[12], L"J:/C++/pictures/标记.jpg", 64, 64);

}
void drawMap(int M[][N+2]) {
	//加载完资源后进行贴图，鼠标点击雷区后，开始对对应位置进行贴图
	for (int i = 1;i <= N;i++) {
		for (int j = 1;j <= N;j++) {
			cout << M[i][j] << '\t';
			switch (M[i][j]) {
			case 0:putimage(64 * (i - 1), 64 * (j - 1), &images[0]);break;
			case 1:putimage(64 * (i - 1), 64 * (j - 1), &images[1]);break;
			case 2:putimage(64 * (i - 1), 64 * (j - 1), &images[2]);break;
			case 3:putimage(64 * (i - 1), 64 * (j - 1), &images[3]);break;
			case 4:putimage(64 * (i - 1), 64 * (j - 1), &images[4]);break;
			case 5:putimage(64 * (i - 1), 64 * (j - 1), &images[5]);break;
			case 6:putimage(64 * (i - 1), 64 * (j - 1), &images[6]);break;
			case 7:putimage(64 * (i - 1), 64 * (j - 1), &images[7]);break;
			case 8:putimage(64 * (i - 1), 64 * (j - 1), &images[8]);break;
			case 9:putimage(64 * (i - 1), 64 * (j - 1), &images[9]);break;
			case 10:putimage(64 * (i - 1), 64 * (j - 1), &images[10]);break;
			case -1:putimage(64 * (i - 1), 64 * (j - 1), &images[11]);break;
			case 12:putimage(64 * (i - 1), 64 * (j - 1), &images[12]);break;
			default:break;
			}
		}
	}

}
//初始化地雷地图
void initMap() {
	drawMap(tmap);
}

void playGame() {

	    int x, y;
		msg = GetMouseMsg();
		
		switch (msg.uMsg) {
			
		case WM_LBUTTONDOWN:
			x = msg.x / 64 + 1;
			y = msg.y / 64 + 1;
			//当没有被点击时:
			if (tmap[x][y] == 10) {
				
				//判断是否有地雷，没有时,并且周围都没有地雷
				if (map[x][y] == 0) {
						//判断周围情况
						for (int a = x - 1;a <= x + 1;a++) {
							for (int b = y - 1;b <= y + 1;b++) {
								//判断是否被点击过
								if (tmap[a][b] == 10) {
									tmap[a][b] = map[x][y];//点击记录
									win++;
								}
							}
						}
				}
				//如果有地雷
				else if (map[x][y] == -1) {
					flag = true;
					tmap[x][y] = map[x][y];
				}
				//如果不是地雷，且不是零
				else {
					tmap[x][y] = map[x][y];
					win++;
				}	
			}
			return;
			break;
		case WM_RBUTTONDOWN:
			x = msg.x / 64 + 1;
			y = msg.y / 64 + 1;
			if (tmap[x][y] == 10) { tmap[x][y] = 11; }
			else if (tmap[x][y] == 11) { tmap[x][y] = 10; }
			return;
			break;
		}
	
}
int main() {

	initgraph(N*64,N*64);

	ProRandMine();
	calNumMine();
	
	initImage();
	initMap();
	while (1) {
		playGame();
		drawMap(tmap);
		if (flag == true) {
			//输了退出
			drawMap(tmap);
			MessageBox(0, L"炸弹来了", L"你输了", MB_OK);
			break;
		}
		if (win==N*N-Num) {
			MessageBox(0, L"恭喜", L"你赢了", MB_OK);
		}
		
	}
	
	
	getchar();
	closegraph();
	system("pause");
	return 0;
}
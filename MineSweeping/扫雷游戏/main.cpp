#include<graphics.h>
#include<conio.h>
#include<iostream>
#include<time.h>
#include<string>
using namespace std;

//���岼�ִ�С
#define N 10
//���׵ĸ���
#define Num 10
//�����ͼ
//��ͼ��ʼ��Ϊ0
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
//����ͼƬ��Դ
IMAGE images[13];
//����һ�������Ϣ����
MOUSEMSG msg = { 0 };
int win = 0;
//û�е����ը��ʱ
bool flag = false;
//�������ʮ����
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
//����ÿ��������Χ�ĵ��׸���������һ����ͼ
void calNumMine() {
	for (int i = 1;i <= N;i++) {
		for (int j = 1;j <= N;j++) {
			//��û�вȵ�����ʱ
			if (map[i][j] != -1) {
				for (int x = i - 1;x <= i + 1;x++) {
					for (int y = j - 1;y <= j + 1;y++) {
					    //�����Χ���ڵ��ף��ۼ�1
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
//ͼƬ��Դ��ʼ��
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
	loadimage(&images[10], L"J:/C++/pictures/��.jpg", 64, 64);
	loadimage(&images[11], L"J:/C++/pictures/��.jpg", 64, 64);
	loadimage(&images[12], L"J:/C++/pictures/���.jpg", 64, 64);

}
void drawMap(int M[][N+2]) {
	//��������Դ�������ͼ������������󣬿�ʼ�Զ�Ӧλ�ý�����ͼ
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
//��ʼ�����׵�ͼ
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
			//��û�б����ʱ:
			if (tmap[x][y] == 10) {
				
				//�ж��Ƿ��е��ף�û��ʱ,������Χ��û�е���
				if (map[x][y] == 0) {
						//�ж���Χ���
						for (int a = x - 1;a <= x + 1;a++) {
							for (int b = y - 1;b <= y + 1;b++) {
								//�ж��Ƿ񱻵����
								if (tmap[a][b] == 10) {
									tmap[a][b] = map[x][y];//�����¼
									win++;
								}
							}
						}
				}
				//����е���
				else if (map[x][y] == -1) {
					flag = true;
					tmap[x][y] = map[x][y];
				}
				//������ǵ��ף��Ҳ�����
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
			//�����˳�
			drawMap(tmap);
			MessageBox(0, L"ը������", L"������", MB_OK);
			break;
		}
		if (win==N*N-Num) {
			MessageBox(0, L"��ϲ", L"��Ӯ��", MB_OK);
		}
		
	}
	
	
	getchar();
	closegraph();
	system("pause");
	return 0;
}
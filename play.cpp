#include<bits/stdc++.h>
#include<conio.h>
#include<windows.h>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
using namespace std;
void SetPos(int i,int j) {
	COORD pos={j,i};
	HANDLE Out=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(Out, pos);
}
void HideCurSor(void) {
	CONSOLE_CURSOR_INFO info={1,0};
	HANDLE Out=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(Out,&info);
}
void Setf(int r,int g,int b) {
	HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwMode=0;
	GetConsoleMode(hOut,&dwMode);
	dwMode|=0x0004;
	SetConsoleMode(hOut,dwMode);
	printf("\x1b[38;2;%d;%d;%dm",r,g,b);
}
void Setb(int r,int g,int b) {
	HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwMode=0;
	GetConsoleMode(hOut,&dwMode);
	dwMode|=0x0004;
	SetConsoleMode(hOut,dwMode);
	printf("\x1b[48;2;%d;%d;%dm",r,g,b);
}
void Setrgb(int fr,int fg,int fb,int br,int bg,int bb) {
	HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwMode=0;
	GetConsoleMode(hOut,&dwMode);
	dwMode|=0x0004;
	SetConsoleMode(hOut,dwMode);
	printf("\x1b[38;2;%d;%d;%dm\x1b[48;2;%d;%d;%dm",fr,fg,fb,br,bg,bb);
}
string t[4]={"  ","¡ö","¡ñ","¡ð"};
int color[30][30];//0 grey 1 red 2 yellow 3 blue 4 green
int color2[30][30];
int mp[30][30];//0 empty 1 wall 2 start 3 end
int mp2[30][30];
int rsx,rsy,ysx,ysy,bsx,bsy,gsx,gsy;
int rex,rey,yex,yey,bex,bey,gex,gey;
bool check() {
	return rsx&&ysx&&bsx&&gsx&&rex&&yex&&bex&&gex;
}
void prone(int i,int j,int tmp) {
	HideCurSor();
	if(color[i][j]==0) Setrgb(127,127,127,240,240,240);
	else if(color[i][j]==1) Setrgb(240,0,0,240,240,240);
	else if(color[i][j]==2) Setrgb(240,210,0,240,240,240);
	else if(color[i][j]==3) Setrgb(0,0,240,240,240,240);
	else if(color[i][j]==4) Setrgb(0,200,0,240,240,240);
	if(tmp) Setb(191,191,191);
	cout<<t[mp[i][j]];
}
void print() {
	SetPos(0,0);
	for(int i=1;i<=25;++i) {
		for(int j=1;j<=25;++j) {
			prone(i,j,0);
		}
		cout<<endl;
	}
}
void clear(int x,int y) {
	if(mp[x][y]>=2) {
		if(mp[x][y]==2) {
			if(color[x][y]==1) rsx=rsy=0;
			if(color[x][y]==2) ysx=ysy=0;
			if(color[x][y]==3) bsx=bsy=0;
			if(color[x][y]==4) gsx=gsy=0;
		}
		if(mp[x][y]==3) {
			if(color[x][y]==1) rex=rey=0;
			if(color[x][y]==2) yex=yey=0;
			if(color[x][y]==3) bex=bey=0;
			if(color[x][y]==4) gex=gey=0;
		}
	}
}
void create() {
	system("mode con cols=50 lines=28");
	for(int i=1;i<=25;++i) mp[i][0]=mp[i][26]=mp[0][i]=mp[26][i]=1;
	print();
	Setrgb(240,240,240,12,12,12);
	cout<<"               Press 'F' to finish                \n";
	cout<<"0:empty   1:wall    ";
	Setrgb(240,0,0,12,12,12);cout<<"2:start   3:end     ";
	Setrgb(240,210,0,12,12,12);cout<<"4:start   \n5:end     ";
	Setrgb(0,0,240,12,12,12);cout<<"6:start   7:end     ";
	Setrgb(0,200,0,12,12,12);cout<<"8:start   9:end     ";
	int x,y;
	x=y=1;
	while(!KEY_DOWN('F')||!check()) {
		SetPos(x-1,2*(y-1)),prone(x,y,1);
		if(KEY_DOWN('0')) clear(x,y),mp[x][y]=0,color[x][y]=0;
		if(KEY_DOWN('1')) clear(x,y),mp[x][y]=1,color[x][y]=0;
		if(KEY_DOWN('2')&&!rsx) clear(x,y),mp[x][y]=2,color[x][y]=1,rsx=x,rsy=y;
		if(KEY_DOWN('3')&&!rex) clear(x,y),mp[x][y]=3,color[x][y]=1,rex=x,rey=y;
		if(KEY_DOWN('4')&&!ysx) clear(x,y),mp[x][y]=2,color[x][y]=2,ysx=x,ysy=y;
		if(KEY_DOWN('5')&&!yex) clear(x,y),mp[x][y]=3,color[x][y]=2,yex=x,yey=y;
		if(KEY_DOWN('6')&&!bsx) clear(x,y),mp[x][y]=2,color[x][y]=3,bsx=x,bsy=y;
		if(KEY_DOWN('7')&&!bex) clear(x,y),mp[x][y]=3,color[x][y]=3,bex=x,bey=y;
		if(KEY_DOWN('8')&&!gsx) clear(x,y),mp[x][y]=2,color[x][y]=4,gsx=x,gsy=y;
		if(KEY_DOWN('9')&&!gex) clear(x,y),mp[x][y]=3,color[x][y]=4,gex=x,gey=y;
		if(KEY_DOWN(VK_UP)&&x>=2) {SetPos(x-1,2*(y-1)),prone(x,y,0),--x,SetPos(x-1,2*(y-1)),prone(x,y,1),Sleep(125);continue;}
		if(KEY_DOWN(VK_DOWN)&&x<=24) {SetPos(x-1,2*(y-1)),prone(x,y,0),++x,SetPos(x-1,2*(y-1)),prone(x,y,1),Sleep(125);continue;}
		if(KEY_DOWN(VK_LEFT)&&y>=2) {SetPos(x-1,2*(y-1)),prone(x,y,0),--y,SetPos(x-1,2*(y-1)),prone(x,y,1),Sleep(125);continue;}
		if(KEY_DOWN(VK_RIGHT)&&y<=24) {SetPos(x-1,2*(y-1)),prone(x,y,0),++y,SetPos(x-1,2*(y-1)),prone(x,y,1),Sleep(125);continue;}
	}
	SetPos(x-1,2*(y-1)),prone(x,y,0);
	for(int i=0;i<=26;++i)
		for(int j=0;j<=26;++j)
			mp2[i][j]=mp[i][j],color2[i][j]=color[i][j];
}
void play() {
//	system("mode con cols=50 lines=28");
//	print();
	SetPos(25,0);
	Setrgb(240,240,240,12,12,12);
	cout<<"               Press 'R' to restart               \n";
	cout<<"¡ö:wall                                           \n";
	cout<<"¡ñ:start                 ¡ð:end                   ";
	int x=rsx,y=rsy,cnw=1,cl=clock();
	while(1) {
//		if(mp[x][y]==0) mp[x][y]=1,color[x][y]=cnw;
		SetPos(x-1,2*(y-1)),prone(x,y,1);
		if(KEY_DOWN(VK_ESCAPE)) system("exit");
		if(KEY_DOWN('R')) {
			for(int i=0;i<=26;++i)
				for(int j=0;j<=26;++j)
					mp[i][j]=mp2[i][j],color[i][j]=color2[i][j];
			print();
			x=rsx,y=rsy,cnw=1;
			continue;
		}
		if(mp[x][y]==3) {
		SetPos(x-1,2*(y-1)),prone(x,y,0);
			if(cnw==4) {
				SetPos(10,6);
				Setrgb(240,240,240,240,0,0);
				printf("                                      ");
				SetPos(11,6);
//				Setrgb(240,240,240,240,0,0);
				printf("  You finished in %09.2lf seconds!  ",(clock()-cl)/1000.0);
				SetPos(12,6);
//				Setrgb(240,240,240,240,0,0);
				printf("          Press Esc to exit.          ");
				SetPos(13,6);
//				Setrgb(240,240,240,240,0,0);
				printf("                                      ");
				break;
			}
			else {
				++cnw;
				if(cnw==2) x=ysx,y=ysy;
				else if(cnw==3) x=bsx,y=bsy;
				else if(cnw==4) x=gsx,y=gsy;
				continue;
			}
		}
		if(KEY_DOWN(VK_UP)&&x>=2&&mp[x-1][y]!=1&&mp[x-1][y]!=2&&(mp[x-1][y]!=3||color[x-1][y]==cnw))
			{SetPos(x-1,2*(y-1)),prone(x,y,0),--x;
			if(mp[x][y]==0) mp[x][y]=1,color[x][y]=cnw;
			SetPos(x-1,2*(y-1)),prone(x,y,1),Sleep(125);continue;}
		if(KEY_DOWN(VK_DOWN)&&x<=24&&mp[x+1][y]!=1&&mp[x+1][y]!=2&&(mp[x+1][y]!=3||color[x+1][y]==cnw))
			{SetPos(x-1,2*(y-1)),prone(x,y,0),++x;
			if(mp[x][y]==0) mp[x][y]=1,color[x][y]=cnw;
			SetPos(x-1,2*(y-1)),prone(x,y,1),Sleep(125);continue;}
		if(KEY_DOWN(VK_LEFT)&&y>=2&&mp[x][y-1]!=1&&mp[x][y-1]!=2&&(mp[x][y-1]!=3||color[x][y-1]==cnw))
			{SetPos(x-1,2*(y-1)),prone(x,y,0),--y;
			if(mp[x][y]==0) mp[x][y]=1,color[x][y]=cnw;
			SetPos(x-1,2*(y-1)),prone(x,y,1),Sleep(125);continue;}
		if(KEY_DOWN(VK_RIGHT)&&y<=24&&mp[x][y+1]!=1&&mp[x][y+1]!=2&&(mp[x][y+1]!=3||color[x][y+1]==cnw))
			{SetPos(x-1,2*(y-1)),prone(x,y,0),++y;
			if(mp[x][y]==0) mp[x][y]=1,color[x][y]=cnw;
			SetPos(x-1,2*(y-1)),prone(x,y,1),Sleep(125);continue;}
	}
}
int main() {
	create();
	play();
	while(!KEY_DOWN(VK_ESCAPE));
	return 0;
}

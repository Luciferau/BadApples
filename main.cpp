#include<stdio.h>
#include <stdlib.h>
#include<windows.h> 
#include <mmsystem.h> 
#include<opencv2/opencv.hpp> 
  

 
#pragma comment(lib, "winmm.lib") 

using namespace cv; 

// 控制光标位置
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
COORD pos = { 0,0 }; // 控制最上边最左侧的位置
VideoCapture video;
Mat frameImg, grayImg;
bool ret = video.open("./apple.mp4");


// 读取视频特征信息
int framecount = video.get(CV_CAP_PROP_FRAME_COUNT); //视频文件的总帧数
int fps = video.get(CV_CAP_PROP_FPS); //帧率
int cols = video.get(CV_CAP_PROP_FRAME_WIDTH); //视频流中的帧宽
int rows = video.get(CV_CAP_PROP_FRAME_HEIGHT);//视频流中的帧高

// 定义抽样大小
int hSize = 10; // 每 10 行，每 5 列，转换为 1 个字符
int wSize = 5;

// 定义字符集合 
char charImgs[] = " .,-'`:!1&@#$";

int height = rows / hSize;
int width = cols / wSize;
char cmd[128];

int countpersent = 1;

// 待优化为指针数组 
int frameSize = height * (width + 1) + 1; //每行的末尾有一个回车符
char* data = (char*)malloc(sizeof(char) * framecount * frameSize);

int Init()
{

	SetConsoleTitle(L"坏苹果-M");
	sprintf_s(cmd, sizeof(cmd), "mode con cols=%d lines=%d", width, height);
	system(cmd);
	//隐藏光标
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info{ 1,0 };
	SetConsoleCursorInfo(hOut, &info);

	if (ret == false)
	{
		printf("视频文件打开失败!\n");
		exit(-1);
	}

	if (data == NULL)
	{
		printf("内存不足!\n");
		return 1;
	}

}

void setColor(unsigned short forwardColor, unsigned short backgroundColor)
{
	//获取输出设备的句柄
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);

	//一个字节来设置颜色（低四位前景色，高四位背景色）
	SetConsoleTextAttribute(hCon, forwardColor | backgroundColor << 4);
}


void load()
{
	setColor(0, 14);//黑色字，米黄色背景

	for (int i = 0; i <= 50; i++)
	{
		printf(" ");
		printf("%d%%", i * 2);
		Sleep(101 - i);
		printf("\b\b\b");//"\b"将输出位置左移一位
	}

	setColor(15, 0);//白色字，黑色背景
	printf("\n加载完成！");
	Sleep(2000);
	system("cls");
}


void readData()
{
	 
	 

	sprintf_s(cmd, sizeof(cmd), "mode con cols=%d lines=%d", 22, 4);
	system(cmd);
	 

		for (int n = 0; n < framecount; n++)
		{
				char* p = data + n * frameSize; video.read(frameImg); // 转换图片的色彩，这里转换为灰度效果
				cvtColor(frameImg, grayImg, COLOR_BGR2GRAY);
				string s = "";
				int k = 0;
				for (int row = 0; row < rows - hSize; row = row + hSize)
				{
						for (int col = 0; col < cols - wSize; col = col + wSize)
							 
						{
							int value = grayImg.at<uchar>(row, col);
							p[k++] = charImgs[int(value / 20)];	
						}
							p[k++] = '\n';
						
				}
							p[k++] = 0;
							 system("cls");
							printf("正在读取:%d / %d", n + 1, framecount);  
						 
							 
						 
						
							 				 						
		}
	 

	 

	mciSendString(L"play apple.mp3 repeat", 0, 0, 0);
	 

			 
}

void play()
{
	while (1)
	{
		for (int i = 0; i < framecount; i++)
		{
			char* p = data + i * frameSize; 
			SetConsoleCursorPosition(h, pos); // 跳转控制台光标位置 
			printf("%s", p); Sleep(1000 / fps);
		}
	}
}

void init2()
{
	sprintf_s(cmd, sizeof(cmd), "mode con cols=%d lines=%d", width, height);
	system(cmd);
}
int main(void)
{  
	Init();
	readData();
	init2();
	play();
	return 0;
}
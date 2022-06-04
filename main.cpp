#include<stdio.h>
#include <stdlib.h>
#include<windows.h> 
#include <mmsystem.h> 
#include<opencv2/opencv.hpp> 
  

 
#pragma comment(lib, "winmm.lib") 

using namespace cv; 

// ���ƹ��λ��
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
COORD pos = { 0,0 }; // �������ϱ�������λ��
VideoCapture video;
Mat frameImg, grayImg;
bool ret = video.open("./apple.mp4");


// ��ȡ��Ƶ������Ϣ
int framecount = video.get(CV_CAP_PROP_FRAME_COUNT); //��Ƶ�ļ�����֡��
int fps = video.get(CV_CAP_PROP_FPS); //֡��
int cols = video.get(CV_CAP_PROP_FRAME_WIDTH); //��Ƶ���е�֡��
int rows = video.get(CV_CAP_PROP_FRAME_HEIGHT);//��Ƶ���е�֡��

// ���������С
int hSize = 10; // ÿ 10 �У�ÿ 5 �У�ת��Ϊ 1 ���ַ�
int wSize = 5;

// �����ַ����� 
char charImgs[] = " .,-'`:!1&@#$";

int height = rows / hSize;
int width = cols / wSize;
char cmd[128];

int countpersent = 1;

// ���Ż�Ϊָ������ 
int frameSize = height * (width + 1) + 1; //ÿ�е�ĩβ��һ���س���
char* data = (char*)malloc(sizeof(char) * framecount * frameSize);

int Init()
{

	SetConsoleTitle(L"��ƻ��-M");
	sprintf_s(cmd, sizeof(cmd), "mode con cols=%d lines=%d", width, height);
	system(cmd);
	//���ع��
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info{ 1,0 };
	SetConsoleCursorInfo(hOut, &info);

	if (ret == false)
	{
		printf("��Ƶ�ļ���ʧ��!\n");
		exit(-1);
	}

	if (data == NULL)
	{
		printf("�ڴ治��!\n");
		return 1;
	}

}

void setColor(unsigned short forwardColor, unsigned short backgroundColor)
{
	//��ȡ����豸�ľ��
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);

	//һ���ֽ���������ɫ������λǰ��ɫ������λ����ɫ��
	SetConsoleTextAttribute(hCon, forwardColor | backgroundColor << 4);
}


void load()
{
	setColor(0, 14);//��ɫ�֣��׻�ɫ����

	for (int i = 0; i <= 50; i++)
	{
		printf(" ");
		printf("%d%%", i * 2);
		Sleep(101 - i);
		printf("\b\b\b");//"\b"�����λ������һλ
	}

	setColor(15, 0);//��ɫ�֣���ɫ����
	printf("\n������ɣ�");
	Sleep(2000);
	system("cls");
}


void readData()
{
	 
	 

	sprintf_s(cmd, sizeof(cmd), "mode con cols=%d lines=%d", 22, 4);
	system(cmd);
	 

		for (int n = 0; n < framecount; n++)
		{
				char* p = data + n * frameSize; video.read(frameImg); // ת��ͼƬ��ɫ�ʣ�����ת��Ϊ�Ҷ�Ч��
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
							printf("���ڶ�ȡ:%d / %d", n + 1, framecount);  
						 
							 
						 
						
							 				 						
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
			SetConsoleCursorPosition(h, pos); // ��ת����̨���λ�� 
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
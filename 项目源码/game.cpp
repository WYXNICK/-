#include<opencv2/opencv.hpp>
#include <iostream>
#include <Windows.h>
#include "hinder.h"
#include "source.h"
#include "ui.h"
#include "user.h"
#include "grade.h"
#include "isHit.h"
#include "play.h"
using namespace cv;

int main()
{
	int c = waitKey(100);
	int newGame = 0; //��������Ƿ�Ϊ��һ����Ϸ����Ϊ��һ����Ϸ���������о�̬�������¸���ֵ
	while (c != 35) {
		play(newGame);
		newGame++;
	}
}
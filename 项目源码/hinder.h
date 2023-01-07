#pragma once
#include<opencv2/opencv.hpp>
#include<windows.h>
#include <stdlib.h>
#include <iostream>
#include "source.h"
#include "user.h"
using namespace cv;

class Hinder
{//�ϰ�����
private:
	int weight;
	int high;
	String src;
	int speed;
	int direction;//1,2,3,4������������
	int location_x;
	int location_y;
	int T; //��ʱ��
	int flag;//������־
	enum udflagenum { downFlag, upFlag };

public:
	//�����������ȡ����
	int getT() { return T; }
	int getflag() { return flag; }
	int getWeight() { return weight; }
	int getHigh() { return high; }
	String getSrc() { return src; };
	int getSpeed() { return speed; }
	int getDirection() { return direction; }
	int getLocation_y() { return location_y; }
	int getLocation_x() { return location_x; }

	void setT(int n) { T = n; }
	void  setFlag(int n) { flag = n; }
	void setWeight(int w) { weight = w; }
	void setHigh(int h) { high = h; };
	void setSrc(String s) { src = s; };
	void setLocation_x(int n) { location_x = n; }
	void setLocation_y(int n) { location_y = n; }
	void setSpeed(int n) { speed = n; }
	//end

	Hinder(int w, int h, String s, int v, int d, int x, int y)
	{
		weight = w;
		high = h;
		src = s;
		speed = v;
		direction = d;
		location_x = x;
		location_y = y;
		T = 0;
		flag = 0;
	}

	void updownshow(Mat frame, Point2f center, bool udFlag, Hinder* up = NULL)
	{

		int high_t = this->getHigh();
		int weight_t = this->getWeight();
		if (this->location_x + this->getWeight() >= frame.size().width)
			weight_t = frame.size().width - location_x;
		if (this->location_y + this->getHigh() >= frame.size().height)
			high_t = frame.size().height - location_y;
		if (high_t == 0 || weight_t == 0)
			return;
		//User u1 = User(50, 50, "C:/Users/lenovo/Desktop/23.png");
		Rect roi(this->location_x, this->location_y, weight_t, high_t);
		Mat frame_roi = frame(roi);
		Mat pic = imread(this->src);

		cv::resize(pic, pic, Size(this->weight, this->high));
		pic = pic(Range(0, high_t), Range(0, weight_t));
		//pic2 = pic2(Range::all(), Range(0, 30)); ���ﵽ�߽��ʱ����Ҫ�ü�
		cv::addWeighted(frame_roi, 0, pic, 1, 1, frame_roi);
		this->setLocation_x(location_x + speed);

		if (this->getLocation_x() >= frame.size().width)
		{
			this->setLocation_x(0);
			if (udFlag) {
				int ran = rand() % (frame.size().height - 100);//Ԥ��60�����ظ�С��ͨ��
				this->setHigh(ran);
			}
			else {
				this->setHigh(frame.size().height - up->getHigh() - 100);
				this->setLocation_y(frame.size().height - this->getHigh());
			}
		}
	}

	void hindershow(Mat frame, Point2f center, User u1, Hinder* h2, Hinder* h3, Hinder* h4)
	{

		Hinder h1(this->getWeight(), this->getHigh(), this->getSrc(), this->getSpeed(), this->getDirection(), this->getLocation_x(), this->getLocation_y());
		h1.updownshow(frame, center, upFlag);
		this->setLocation_x(h1.getLocation_x());
		this->setHigh(h1.getHigh());
		h2->updownshow(frame, center, downFlag, &h1);
		if (this->speed == 0 || (this->T > (frame.size().width / 2) / this->speed))  //�ڶ���ܵ��ڵ�һ�����37֡�����
		{
			h3->updownshow(frame, center, upFlag);
			h4->updownshow(frame, center, downFlag, &*h3);
		}

	}
};
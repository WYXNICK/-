#pragma once
#include <iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
class Grade {

private:
	int grade;

public:
	int getgrade() { return grade; }
	int count(int newGame) {
		static int m = 0;
		static int grade = 0;
		static int a = newGame;
		if (newGame > a) {
			m = 0;
			grade = 0;
			a++;
		}
		m++;
		if (m >= 10) {    //ÿʮ��ѭ��������1
			grade++;
			m = m - 10;
		}
		return grade;
	}
	void showcount(Mat frame, int newGame) {
		String Text1;
		String Text2;
		static int gradelock = 1; //����Ϸ����ʱ����֤�������ٸı�
		static int finalcount = 0;
		static int bestscore = 0;
		static int a = newGame;
		if (newGame > a) {
			gradelock = 1;
			finalcount = 0;
			a++;
		}
		if (gradelock > 0) {
			finalcount = count(newGame);
			gradelock--;
		}
		if (bestscore < finalcount) {
			bestscore = finalcount;
		}
		Text1 = "This time your score is " + to_string(finalcount);
		Text2 = "Your best score is " + to_string(bestscore);
		putText(frame, Text1, Point(80, 100), CV_FONT_HERSHEY_COMPLEX, 1.2, Scalar(0, 0, 255), 1, CV_AA);
		putText(frame, Text2, Point(160, 145), CV_FONT_HERSHEY_COMPLEX, 1.2, Scalar(0, 0, 255), 1, CV_AA);
	}

};
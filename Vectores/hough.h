#pragma once
#ifndef VECTORLEARN_H
#define VECTORLEARN_H


#include <iostream>
#include <string>
#include <math.h>

#include <opencv2\core\core.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgcodecs\imgcodecs.hpp>


using namespace std;
using namespace cv;

class Hough {
public:
	Hough() {
	}
	void circle(cv::Mat eye);
private:

};
#endif // !VECTORLEARN_H




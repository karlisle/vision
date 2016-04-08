#pragma once
#pragma once
#ifndef MUESTRAS_H
#define MUESTRAS_H

#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>



#include <iostream>
#include <queue>
#include <stdio.h>
#include <math.h>
#include <string>
#include <fstream>

#include "captureFrame.h"


using namespace std;

class Muestras
{
public:
	//-- Constructor
	Muestras(){
	}
	void guardar(cv::Mat frame, cv::Mat X, cv::Mat lEye, cv::Mat rEye, int& intent, cv::VideoCapture& capture);

private:
	//-- capturar algunos frames de los ojos y guardar tanto las coordenadas como las imagenes
	void setData(cv::Mat, cv::Mat rEye, string p1, string p2, string p25, string p28, int intent );
	bool openEye(cv::Mat puntos);

};

#endif // !MUESTRAS_H
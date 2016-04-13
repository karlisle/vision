#pragma once
#pragma once
#ifndef MUESTRAS_H
#define MUESTRAS_H

#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

#include <sstream>
#include <Windows.h>
#include <stdlib.h>
#include <iostream>
#include <queue>
#include <stdio.h>
#include <math.h>
#include <string>
#include <fstream>



#include "mysql_connection.h"
#include "cppconn\sqlstring.h"
#include "cppconn\driver.h"
#include "cppconn\exception.h"
#include "cppconn\resultset.h"
#include "cppconn\statement.h"

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
	void setData(cv::Mat, cv::Mat rEye, int p20x, int p20y, int p21x, int p21y, int p23x, int p23y, int p24x, int p24y, int p26x, int p26y, int p27x, int p27y, int p29x, int p29y, int p30x, int p30y, int intent );
	bool openEye(cv::Mat puntos);
	void dataBase();

};

#endif // !MUESTRAS_H
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


#include "captureFrame.h"
#include "dataBase.h"


using namespace std;


class Muestras
{
public:
	//-- Constructor
	Muestras(){
	}
	//-- Desplegar un menú de opciones
	void muestrasSeccion(cv::Mat frame, cv::Mat X, vector<float> angles, cv::Mat lEye, cv::Mat rEye, int& intent, cv::VideoCapture& capture);
	
	/*
	 @.-- Guardam los datos en una base de datos SQLite
	*/
	void guardar(cv::Mat frame, cv::Mat X, vector<float> angles, cv::Mat lEye, cv::Mat rEye, int& intent, cv::VideoCapture& capture);
	void screenMap(cv::Mat frame, cv::Mat X0, vector<float> angulos, cv::Mat lEye, cv::Mat rEye, int& intent, cv::VideoCapture& capture);

private:
	Database db;
	//-- capturar algunos frames de los ojos y guardar tanto las coordenadas como las imagenes
	void setDataLite(cv::Mat, cv::Mat rEye, float roll, float yaw, float pitch, int p19x, int p19y, int p20x, int p20y, int p21x, int p21y, int p22x, int p22y, int p23x, int p23y, int p24x, int p24y, int p25x, int p25y, int p26x, int p26y, int p27x, int p27y, int p28x, int p28y, int p29x, int p29y, int p30x, int p30y, int intent );
	vector<int> splitPuntos(cv::Mat X);
	void setData(cv::Mat X0, vector<float> angulos, cv::Point posicion, int intent, string sector);
	bool openClose(cv::Mat X0);
	string saveImage(cv::Mat lEye, cv::Mat rEye, int intent);


};

#endif // !MUESTRAS_H
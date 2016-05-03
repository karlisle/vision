#pragma once
#ifndef CAPTUREFRAME_H
#define CAPTUREFRAME_H


// Cabeceras de la libreria estandar
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <time.h>
#include <Windows.h>
//Cabeceras de inclusion de OpenCV
//(verificar la ruta del sistema, o en su defecto local)
// en las propiedades del proyecto
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
// Librerias de IntraFace
#include <intraface\FaceAlignment.h>
#include <intraface\XXDescriptor.h>
// Cabeceras locales
//#include "prepare.h"
#include "test.h"
#include "muestras.h"
#include "prepare.h"
#include "cameraCalibration.h"
#include "trainer.h"
#include "dataBase.h"



class CaptureFrame {
public:
	CaptureFrame() {
	}
	//--Menu
	void menu();

	//Prepare prepare;
	int detect(int opt);

	//-- instancias la clase de pruebas
	Test test;

	//-- Instanciar la clase de entrenamiento
	Train oc;
	
	//-- instancias la clase de Cummulative Distribution Function
	Prepare prepare;
	//-- instancias la clase de CammeraCalibration
	Calibration calibration;

private:
	
	
};
#endif // !CAPTUREFRAME_H
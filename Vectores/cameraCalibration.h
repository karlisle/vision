#pragma once
#ifndef CAMERACALIBRATION_H
#define CAMERACALIBRATION_H

#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>



#include <iostream>
#include <string>

using namespace std;

class Calibration {
public:
	//-- constructor
	Calibration(){
	}
	void camCalibration();
private:

};




#endif // !CAMERACALIBRATION_H
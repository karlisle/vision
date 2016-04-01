#include "cameraCalibration.h"

using namespace std;

void Calibration::camCalibration() {
	cv::Mat chess;
	chess = cv::imread("chess1.jpg", CV_LOAD_IMAGE_COLOR);
	cv::imshow("Chess-Table", chess);


	bool found = cv::findChess
	cv::waitKey(0);
	cv::destroyAllWindows();
}
#include "hough.h"

using namespace std;
using namespace cv;


void Hough::circle(Mat eye)
{
	cv::Mat img;
	img = eye.clone();
	cv::Mat dest;

	/*
	resize(img, dest, Size(), 4, 4);
	imwrite("imgResize.bmp", dest);
	img = frame;
	
	
	Mat gray;
	Mat bordes;
	Mat binary;
	cvtColor(dest, gray, COLOR_BGR2GRAY);
	
	
	binary = gray > 128;
	//GaussianBlur(binary, binary, Size(5, 5), 1, 1);
	Canny(binary, bordes, 5, 60, 3);
	imwrite("bordeOjo.bmp", bordes);
	imshow("Frame_bordes", binary);
	*/

	vector<Vec3f> circles;


	HoughCircles(img, circles, HOUGH_GRADIENT, 1, img.rows/10, 200, 100, 0, 0 );
	if (!circles.empty())
	{
		cout << "Circulos detectados!" << endl;
		for (size_t i = 0; i < circles.size(); i++)
		{
			Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
			int radius = cvRound(circles[i][2]);
			//circle(dest, center, 3, Scalar(0, 255, 0), -1, 8, 0);
			//circle(dest, center, radius, Scalar(0, 0, 255), 3, 8, 0);
		}
		imshow("Cosos locos", dest);
	}
	else
	{
		cerr << "No hay circulos " << endl;
		("Img", img);
	}
	
	return;
}

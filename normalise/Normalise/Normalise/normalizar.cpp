#pragma once
#include "normalizar.h"

void Normalizar::equalise(cv::Mat frame, std::vector<float> angles, cv::Mat X)
{
	cv::Mat cpFrame;
	cv::Mat histEq;
	cv::cvtColor(frame, cpFrame, CV_BGR2GRAY);

	//-- Histogram-equalise
	cv::equalizeHist(cpFrame, histEq);

	

	//-- Translate image to focus midpoint of eyes corners
	int x19 = (int)X.at<float>(0, 19);
	int x28 = (int)X.at<float>(0, 28);
	float em = x28 - x19;
	float midPoint = em + x19;
	float offsetx = ((cpFrame.cols / 2.0) - x19);

	cv::circle(frame, cv::Point(midPoint, (int)X.at<float>(1, 19)), 2, cv::Scalar(256, 0, 256), -1);


	cv::Mat transFrame = (cv::Mat_<double>(2, 3) << 1, 0, offsetx, 0, 1, 0);
	cv::warpAffine(cpFrame, cpFrame, transFrame, cpFrame.size());

	imshow("Gaze", frame);
	//-- Rotate the image according to the Roll angle.
	double roll = -angles[0];

	//-- Get rotation matrix for rotating the iamge around its center
	cv::Point2f center(cpFrame.cols / 2.0, cpFrame.rows / 2.0);
	cv::Mat rot = cv::getRotationMatrix2D(center, angle, 1.0);
	//-- determine bounding rectangle
	cv::Rect bbox = cv::RotatedRect(center, cpFrame.size(), angle).boundingRect();
	//Adjust transformation matrix
	rot.at<double>(0, 2) += bbox.width / 2.0 - center.x;
	rot.at<double>(1, 2) += bbox.height / 2.0 - center.y;

	



	cv::Mat destino;
	cv::warpAffine(cpFrame, destino, rot, bbox.size());
	cv::imshow("Gaze-Rotate", destino);

}

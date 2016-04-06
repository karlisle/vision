#include "test.h"
#include "hough.h"

using namespace std;
void Test::display(cv::Mat frame, std::vector<cv::Rect> faces, cv::Rect lEye, cv::Rect rEye, cv::Mat X0)
//void Test::display()
{
	string wName = "Gaze";
	string nrEye = "R_eye";
	string nlEye = "L_eye";
	cv::namedWindow(wName, CV_WINDOW_AUTOSIZE);
	cv::namedWindow(nlEye, CV_WINDOW_NORMAL);
	cv::namedWindow(nrEye, CV_WINDOW_NORMAL);
	
	cv::Mat faceROI = frame.clone();                                                //-- Hacemos un clon de la imagen que se recive como parametro
<<<<<<< HEAD
	cv::cvtColor(frame, faceROI, CV_RGB2GRAY);
	frame.convertTo(faceROI, CV_8U, 2.48, -10.68);									//-- Posterior a eso modificamos el contraste de la imagen 
	
	cv::bilateralFilter(frame, faceROI, 10, 60, 60);
	//GaussianBlur(frame, faceROI, cv::Size(3, 3), 0, 0);
=======
	//cv::cvtColor(frame, frame, CV_RGB2GRAY);
	frame.convertTo(faceROI, CV_8U, 2.48, -10.68);									//-- Posterior a eso modificamos el contraste de la imagen 
	
	//cv::bilateralFilter(frame, faceROI, 10, 60, 60);
	GaussianBlur(frame, faceROI, cv::Size(3, 3), 0, 0);
>>>>>>> 13bedf7982093df7f8cff2d784aed625c0edcffe

	cv::Mat leye(faceROI(lEye));
	cv::Mat reye(faceROI(rEye));

	cv::Mat cleye = leye.clone();

	//cv::bilateralFilter(cleye, leye, 7, 30, 30);
	//cv::line(faceROI, Ell, Elr,  cv::Scalar(134, 0, 255), 1);
	cv::medianBlur(leye, leye, 5);
	cv::medianBlur(reye, reye, 5);
	//cv::bilateralFilter(leye, leye, 10, 4, 4);
	
	//cv::bitwise_not(leye, leye);
	//cv::bitwise_not(reye, reye);	
	
	//cv::circle(faceROI, cv::Point((int)X0.at<float>(0, 24), (int)X0.at<float>(1, 24)), 1, cv::Scalar(0, 255, 255), 1);	

	//-- Estos puntos se ilustran en el diagrama del block de notas
	cv::Point a1((int)X0.at<float>(0, 20), (int)X0.at<float>(1, 20));
	cv::Point a2((int)X0.at<float>(0, 21), (int)X0.at<float>(1, 21));
	cv::Point b2((int)X0.at<float>(0, 23), (int)X0.at<float>(1, 23));
	cv::Point b1((int)X0.at<float>(0, 24), (int)X0.at<float>(1, 24));

	
	/*-- Formamos una cuadricula para indicar la zona central de la region de interes, en este caso el iris
	*    dado que IntraFace ya nos da los puntos circundantes es solo cuestion de moverse sobre el eje 'Y'
	*    para obtener los M y N
	*/
	cv::Point m1((int)X0.at<float>(0, 19), (int)X0.at<float>(1, 19) - 10);
	cv::Point m2((int)X0.at<float>(0, 22), (int)X0.at<float>(1, 22) - 10);
	cv::line(faceROI, m1, m2, cv::Scalar(255, 255, 0), 1);
	cv::Point n1((int)X0.at<float>(0, 19), (int)X0.at<float>(1, 19) + 3);
	cv::Point n2((int)X0.at<float>(0, 22), (int)X0.at<float>(1, 22) + 3);
	//cv::line(faceROI, n1, n2, cv::Scalar(255, 255, 0), 1);
	//-- Esto es solo para servir de guía visual, se trazan lineas que unen los puntos mencionados.
	//cv::line(faceROI, a1, b1, cv::Scalar(0, 255, 0), 1);
	cv::line(faceROI, a2, b2, cv::Scalar(0, 255, 0), 1);
	//--------------------------------------------


	
	

	/*######################################################################*/
	//cv::imshow(nlEye, leye);
	//cv::imshow(nrEye, reye);
	this->getCenter(reye, nlEye);
	
	//cv::rectangle(faceROI, lEye, cv::Scalar(0, 255, 0));
	//cv::rectangle(faceROI, rEye, cv::Scalar(0, 255, 0));
	
	cv::imshow(wName, faceROI);
	
}

<<<<<<< HEAD
void Test::getCenter(cv::Mat eye, string nWindow)
{
	cv::Point center;
	cv::imshow(nWindow, eye);



	
=======
void getPositions(cv::Mat leye, cv::Mat reye, cv::Mat X)
{

>>>>>>> 13bedf7982093df7f8cff2d784aed625c0edcffe
}

cv::Mat Test::getSkin(cv::Mat src)
{
	cv::Mat dst = src.clone();
	
	cv::Vec3b cwhite = cv::Vec3b::all(255);
	cv::Vec3b cblack = cv::Vec3b::all(0);

	cv::Mat src_ycrcb, src_hsv;

	cv::cvtColor(src, src_ycrcb, CV_BGR2YCrCb);
	src.convertTo(src_hsv, CV_32FC3);
	cv::cvtColor(src_hsv, src_hsv, CV_BGR2HSV);

	cv::normalize(src_hsv, src_hsv, 0.0, 255.0, cv::NORM_MINMAX, CV_32FC3);

	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++) 
		{
			cv::Vec3b pix_bgr = src.ptr<cv::Vec3b>(i)[j];
			int B = pix_bgr.val[0];
			int G = pix_bgr.val[1];
			int R = pix_bgr.val[2];

			bool a = R1(R, G, B);

			cv::Vec3b pix_ycrcb = src_ycrcb.ptr<cv::Vec3b>(i)[j];
			int Y = pix_ycrcb.val[0];
			int Cr = pix_ycrcb.val[1];
			int Cb = pix_ycrcb.val[2];
			bool b = R2(Y, Cr, Cb);

			cv::Vec3b pix_hsv = src_hsv.ptr<cv::Vec3b>(i)[j];
			float H = pix_hsv.val[0];
			float S = pix_hsv.val[1];
			float V = pix_hsv.val[2];
			bool c = R3(H, S, V);
			if (!(a&&b&&c))
			{
				dst.ptr<cv::Vec3b>(i)[j] = cblack;
			}
		}

	}

	return dst;
}
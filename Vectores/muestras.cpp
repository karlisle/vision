#include "muestras.h"
#include "captureFrame.h"


void Muestras::guardar(cv::Mat frame, cv::Mat X0, cv::Mat lEye, cv::Mat rEye, int& intent)
{
	//cout << "\tTomando imagenes para muestras..." << endl;
	string wName = "Gaze";
	
	cv::namedWindow(wName, CV_WINDOW_NORMAL);

	char k = cv::waitKey(1);
	
	if (k == 's')
	{

		string wlEye = "Left-Eye";
		string wrEye = "Right-Eye";

		cv::namedWindow(wlEye, CV_WINDOW_NORMAL);
		cv::namedWindow(wrEye, CV_WINDOW_NORMAL);

		cout << "Guardando region de interes :)" << endl;
		string nlEye = "lEye" + to_string(intent) + "_.bmp";
		string nrEye = "rEye" + to_string(intent) + "_.bmp";
		++intent;
		cout << "Izquierdo: " << nlEye << " ||  Derecho: " << nrEye << endl;

		

		cv::Point a1((int)X0.at<float>(0, 19), (int)X0.at<float>(1, 19));
		cv::Point a2((int)X0.at<float>(0, 22), (int)X0.at<float>(1, 22));
		cv::circle(frame, a1, 1, cv::Scalar(0, 0, 255), 1);
		cv::circle(frame, a2, 1, cv::Scalar(0, 0, 255), 1);

		//cout << "Punto 19: " << a1 << "Punto 22: "<< a2 << endl;
		string p19 = to_string(a1.x) + "," + to_string(a1.y);
		string p22 = to_string(a2.x) + "," + to_string(a2.y);
		cv::putText(frame, p19, cv::Point((int)X0.at<float>(0, 19) - 20, (int)X0.at<float>(1, 19)), CV_FONT_HERSHEY_PLAIN, 0.3, cv::Scalar(255, 255, 0), 1);
		cv::putText(frame, p22, cv::Point((int)X0.at<float>(0, 22) - 20, (int)X0.at<float>(1, 22)), CV_FONT_HERSHEY_PLAIN, 0.3, cv::Scalar(255, 255, 0), 1);

		cv::imshow("Gaze", frame);
		//cv::namedWindow("Tool");
		cv::imshow(wlEye, lEye);
		cv::imshow(wrEye, rEye);

		cv::imshow(wName, frame);
	}
	else
	{
		if (k == 'r')
		{
			cout << "regresando al menu principal" << endl;
			cv::destroyAllWindows();
			CaptureFrame capt;
			capt.menu();

		}
		
	}
	
}



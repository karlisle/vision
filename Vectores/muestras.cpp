#include "muestras.h"
#include "captureFrame.h"


void Muestras::guardar(cv::Mat frame, cv::Mat X0, cv::Mat lEye, cv::Mat rEye, int& intent, cv::VideoCapture& capture)
{
	//cout << "\tTomando imagenes para muestras..." << endl;
	char k = cv::waitKey(1);

	//-- creamos la ventanas que se usaran localmente
	string wName = "Gaze";
	cv::namedWindow(wName, CV_WINDOW_NORMAL);
	string wlEye = "Left-Eye";
	string wrEye = "Right-Eye";
	cv::namedWindow(wlEye, CV_WINDOW_NORMAL);
	cv::namedWindow(wrEye, CV_WINDOW_NORMAL);	
	/*-- Obtenemos los puntos de intres, en orden serian de la siguiente forma:
	**-- [ojoIzqExterno, ojoIzqInterno, ojoDerInterno, ojoDerexterno]
	**-- de cualquier forma revisar el diagrama en la documentacion del proyecto.
	*/
	cv::Point a1((int)X0.at<float>(0, 19), (int)X0.at<float>(1, 19));
	cv::Point a2((int)X0.at<float>(0, 22), (int)X0.at<float>(1, 22));
	cv::Point b1((int)X0.at<float>(0, 25), (int)X0.at<float>(1, 25));
	cv::Point b2((int)X0.at<float>(0, 28), (int)X0.at<float>(1, 28));
	/*-- Dibujamos los puntos internos de ambos ojos.
	**-- aunque se podrian poner los cuatro, solo se usan de refrencia visual. 
	*/
	cv::circle(frame, b1, 1, cv::Scalar(0, 0, 255), 1);
	//cv::circle(frame, a1, 1, cv::Scalar(0, 0, 255), 1);
	//cv::circle(frame, b2, 1, cv::Scalar(0, 0, 255), 1);
	cv::circle(frame, a2, 1, cv::Scalar(0, 0, 255), 1);
	
	//-- Convertimos los puntos a cadenas para enviarlos a setData y guardarlos
	string p19 = to_string(a1.x) + "," + to_string(a1.y);
	string p22 = to_string(a2.x) + "," + to_string(a2.y);
	string p25 = to_string(b1.x) + "," + to_string(b1.y);
	string p28 = to_string(b2.x) + "," + to_string(b2.y);
	
	cv::imshow(wName, frame);
	bool openClose = this->openEye(X0);

	//-- enviamos los datos.
	this->setData(lEye, rEye, p19, p22, p25, p28, intent);

	cv::imshow(wlEye, lEye);
	cv::imshow(wrEye, rEye);
	/*-- Incrementamos el contador de frames, se hace desde aqui, aunque bien 
	*--- podria ser desde captureFrame, al caso es mas intuitivo desde aqui.
	*/
	++intent;
	
	
	if (k == 'r')
	{
		cout << "regresando al menu principal" << endl;
		capture.release();
		cv::destroyAllWindows();
		CaptureFrame capt;
		capt.menu();
	}
}

void Muestras::setData(cv::Mat, cv::Mat rEye, string p19, string p22, string p25, string p28, int intent)
{

	fstream imgPuntos;
	imgPuntos.open("puntos.txt", ios::app);

	string id;
	string puntos = p19 + "," + p22 + "," + "," + p25 + "," + "," + p28;
	/* En este bloque lo que hacemos es formatear el ID de la imagen muestra
	** a falta de una forma mas optima, esto funciona por ahora.
	++ podria usarse alguna forma de formateo, pero bueno, funciona así.
	*/
	if (intent <= 9)
	{
		id = "000" + to_string(intent);
	}
	else if (intent >= 10 && intent <= 99)
	{
		id = "00" + to_string(intent);
	}
	else if (intent >= 100 && intent <= 999)
	{
		id = "0" + to_string(intent);
	}
	else if (intent >= 1000 && intent <= 9990)
	{
		id = to_string(intent);
	}
	else if (intent == 9999)
	{
		cout << "Se han capturado suficientes muestras!" << endl;
		return;
	}

	string nlEye = id + "l.bmp";
	string nrEye = id + "r.bmp";

	cout << nlEye << endl;
	cout << nrEye << endl;


	imgPuntos << id << ","<< puntos << endl;
	//imgPuntos << nname << endl;
	//imgPuntos.close();
	//return;
	//--registra los puntos	
}

bool Muestras::openEye(cv::Mat puntos)
{

}


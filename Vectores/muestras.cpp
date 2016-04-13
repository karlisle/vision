#include "muestras.h"
#include "captureFrame.h"


void Muestras::guardar(cv::Mat frame, cv::Mat X0, cv::Mat lEye, cv::Mat rEye, int& nFrame, cv::VideoCapture& capture)
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
	if (openClose)
	{
		//-- enviamos los datos.
		this->setData(lEye, rEye, p19, p22, p25, p28, nFrame);

	}

	cv::imshow(wlEye, lEye);
	cv::imshow(wrEye, rEye);
	/*-- Incrementamos el contador de frames, se hace desde aqui, aunque bien 
	*--- podria ser desde captureFrame, al caso es mas intuitivo desde aqui.
	*/
	++nFrame;
	
	
	if (k == 'r')
	{
		cout << "regresando al menu principal" << endl;
		capture.release();
		cv::destroyAllWindows();
		CaptureFrame capt;
		capt.menu();
	}
}

void Muestras::setData(cv::Mat lEye, cv::Mat rEye, string p19, string p22, string p25, string p28, int nFrame)
{

	fstream imgPuntos;
	fstream contador;

	imgPuntos.open("puntos.txt", ios::app);
	
	char cont[128];
	//-- Obtenemos el ultimo valor de nFrame
	ifstream fe("contador.txt");
	fe.getline(cont, 128);
	cout << cont << endl;
	nFrame = stoi(cont);
	fe.close();

	
	ofstream fs("contador.txt");
	fs << nFrame + 1;
	fs.close();

	string id;
	string puntos = p19 + "," + p22 + "," + "," + p25 + "," + "," + p28;
	/* En este bloque lo que hacemos es formatear el ID de la imagen muestra
	** a falta de una forma mas optima, esto funciona por ahora.
	++ podria usarse alguna forma de formateo, pero bueno, funciona así.
	*/
	if (nFrame <= 9)
	{
		id = "000" + to_string(nFrame);
	}
	else if (nFrame >= 10 && nFrame <= 99)
	{
		id = "00" + to_string(nFrame);
	}
	else if (nFrame >= 100 && nFrame <= 999)
	{
		id = "0" + to_string(nFrame);
	}
	else if (nFrame >= 1000 && nFrame <= 9990)
	{
		id = to_string(nFrame);
	}
	else if (nFrame == 9999)
	{
		cout << "Se han capturado suficientes muestras!" << endl;
		return;
	}

	string nlEye = id + "l.bmp";
	string nrEye = id + "r.bmp";

	imgPuntos << id << ","<< puntos << endl;

	//-- Guardamos la captura de los ojos 
	cv::imwrite("muestras\\" + nlEye, lEye);
	cv::imwrite("muestras\\" + nrEye, rEye);

	//imgPuntos << nname << endl;
	imgPuntos.close();
	//return;
	//--registra los puntos	

	mysql




}



/*- Obtenemos un promedio en la separacion del los puntos (20, 24) y (21, 23) 
--- consideramos un umbral igual o mayor a 6 pixeles para considerar habierto el ojo
--- al menos en resoluciones de (640x420), es posible que haya que hacerlo en funcion 
--- de la resolucion del cudro, pero para eso primero conseguir otro dispositivo.
*/
bool Muestras::openEye(cv::Mat P)
{
	//-- Obtenemos los puntos del ojo derecho (19, 24)
	cv::Point p1((int)P.at<float>(0, 20), (int)P.at<float>(1, 20));
	cv::Point p2((int)P.at<float>(0, 21), (int)P.at<float>(1, 21));
	cv::Point q2((int)P.at<float>(0, 23), (int)P.at<float>(1, 23));
	cv::Point q1((int)P.at<float>(0, 24), (int)P.at<float>(1, 24));

	//-- Obtenemos los puntos del ojo derecho (25, 30)
	cv::Point r1((int)P.at<float>(0, 26), (int)P.at<float>(1, 26));
	cv::Point r2((int)P.at<float>(0, 27), (int)P.at<float>(1, 27));
	cv::Point s2((int)P.at<float>(0, 30), (int)P.at<float>(1, 30));
	cv::Point s1((int)P.at<float>(0, 29), (int)P.at<float>(1, 29));

	//cout << to_string(p1.y) << ":" << to_string(q1.y) << endl;
	
	double maxR = (q1.y - p2.y) / 2;
	double maxL = (s1.y - r1.y) / 2;

	if (maxR >= 6 && maxL >= 6)
	{
		//cout << "Está abierto" << endl;
		return true;
	}
	else if (maxR < 6 && maxL < 6)
	{
		//cout << "Está cerrado" << endl;
		return false;
	}
	return false;
}


#pragma once

#include "captureFrame.h"



using namespace std;
using namespace cv;

void CaptureFrame::menu()
{
	cout << "\t****************************" << endl;
	cout << "\t*   Seleccione una opción  *" << endl;
	cout << "\t* 1) Cargar (CDF)          *" << endl;
	cout << "\t* 2) Entrenar               *" << endl;
	cout << "\t* 3) Tomar muestras        *" << endl;
	cout << "\t* 4) Tomar muestras/seccion*" << endl;
	cout << "\t* 0) Salir                 *" << endl;
	cout << "\t****************************" << endl;
	cout << "\t>>> ";


	Database data;
	int opcion;
	cin >> opcion;

	switch (opcion)
	{
		case 0:
			exit(0);
			//break;
		case 1:
			this->detect(1);
			break;
		case 2:
			this->detect(2);
			break;
		case 3:
			this->detect(3);
			break;
		case 4:
			this - detect(4);
			break;
		default:
			this->detect(NULL);
			break;
	}
}
void drawPose(cv::Mat& img, const cv::Mat& rot, float lineL)
{
	int loc[2] = { 70, 70 };
	int thickness = 2;
	int lineType = 8;

	cv::Mat P = (cv::Mat_<float>(3, 4) <<
		0, lineL, 0, 0,
		0, 0, -lineL, 0,
		0, 0, 0, -lineL);
	P = rot.rowRange(0, 2)*P;
	P.row(0) += loc[0];
	P.row(1) += loc[1];
	cv::Point p0(P.at<float>(0, 0), P.at<float>(1, 0));

	line(img, p0, cv::Point(P.at<float>(0, 1), P.at<float>(1, 1)), cv::Scalar(255, 0, 0), thickness, lineType);
	line(img, p0, cv::Point(P.at<float>(0, 2), P.at<float>(1, 2)), cv::Scalar(0, 255, 0), thickness, lineType);
	line(img, p0, cv::Point(P.at<float>(0, 3), P.at<float>(1, 3)), cv::Scalar(0, 0, 255), thickness, lineType);
}

int CaptureFrame::detect(int opt)
{
	cout << "Iniciando componentes y variables del sistema Eye-gaze...!!" << endl;

	// Inicializar variables y la estructura de datos.
	int frameWidth = 1;
	int frameHeight = 1;
	int D = 1;
	int H = 1;
	//NewHough::OPTIONS detectionMode = NewHough::QUANTIZED_GRADIENT;
	//Trainer::MODEL gazeModel;
	bool maxDensity = false;
	bool binaryThresholding = false;
	float k[] = { 500, 0, 320, 0, 500, 240, 0, 0, 1 };
	const cv::Mat K(3, 3, CV_32F, (char*)k);
	bool blink = false;
	bool acquire = false;
	//Mat leftGaze, rightGaze;

	string videoName;
	string outputName;

	// Cargar los modeos entrenados y  los binarios de IntraFace
	char detectionModel[] = "models/DetectionModel-v1.5.bin";
	char trackingModel[] = "models/TrackingModel-v1.10.bin";
	string faceDetectionModel("models/haarcascade_frontalface_alt2.xml");

	// Inicualizar objeto XXDescriptor
	INTRAFACE::XXDescriptor xxd(4);
	// Inicializar objeto de FaceAligment
	INTRAFACE::FaceAlignment fa(detectionModel, trackingModel, &xxd);

	if (!fa.Initialized())
	{
		cerr << "FaceAligment cannot be initialized" << endl;
		return 0; 
	}
	// Cargar el modelo de detecion de rostros de OpenCV
	cv::CascadeClassifier face_cascade;
	if (!face_cascade.load(faceDetectionModel))
	{
		cerr << "Error: No se ha podido cargar el modelo de teccion de rostos!!" << endl;
		return 0;
	}

	// Inicializar variables para el loop principal
	// Inicializar dispositivo de captura.
	// Posteriormente se seleccionara a partir de un dialogo.
	

	VideoCapture capture;
	//capture.open("videoEyes.avi");
	//capture.open("eyes_two.avi");
	capture.open(0);
	Mat fOrig;
	Rect lEye;
	Rect rEye;
	//Mat leftEye;
	//Mat rightEye;
	Mat lEyeBW;
	Mat rEyeBW;
	Mat leftEyeBW;
	Mat rightEyeBW;
	Vec3i lCircle;
	Vec3i rCircle;

	int key = 0;
	int intent = 0;
	bool isDetect = true;
	float score, notFace = 0.3;
	Mat X, X0;
	vector<Rect> faces;
	vector<Rect> eyes;

	// Si el dispositivo se inicializo correctamente se inicia el ciclo principal.
	if (capture.isOpened())
	{
		// El siguinete delay es para dar tiempo a que el dispositivo 
		// termine de cargar
		Sleep(2000);
		while (true)
		{
			Mat frame;
			Mat frameOrig;
			capture.read(frameOrig);					// Se captura un frame
			frame = frameOrig.clone();
			fOrig = frame.clone();
			// Se comprueba que el frame contenga informacion
			// en caso contrario terminamos
			if (frame.rows == 0 || frame.cols == 0)
			{
				cout << "Error: No frame!!" << endl;
				break;
			}
			// Lo siguiente se ejecuta solo si isDetect es igual a true.
			// En otras palabras, solo si se ha detectado un rostro.
			if (isDetect)
			{
				// Detectamos los rostros del frame
				face_cascade.detectMultiScale(frame, faces, 1.2, 2, 0, Size(40, 40));
				
				// Comprobamos si el vector de rostros esta vacio
				// En caso de estarlo se muestra el frameactual 
				// y se contia a la siguiente instruccion
				if (faces.empty())
				{
					imshow("Gaze", frame);
					key = waitKey(5);
					continue;
				}
				// Detectar las caracteristicas en el rostro mas grande detectado
				// En este punto se envia el frame contenido en el vector <faces>
				// con mayores dimenciones (HxW), en caso de no ser un rostro, se termina.
				if (fa.Detect(frame, faces[0], X0, score) != INTRAFACE::IF_OK)
				{
					break;
				}
				// Si el vector <faces> esta vacio y/o se detecta que no es un rostro, 
				// isDetect se pone a "false"!
				isDetect = false;
			}
			else
			{
				// Seguimiento de las marcas faciales en el fotograma de entrada
				// En caso de no haberla, se termina le ejecucion
				if (fa.Track(frame, X0, X, score) != INTRAFACE::IF_OK)
				{
					break;
				}
				// Asignamos las nuevas marcas faciales a X0.
				// Donde X0 = actuales y X = anteriores
				X0 = X;
			}
			if (score < notFace)
			{
				isDetect = true;
			}
			else
			{
				// Dibujamos los marcadores faciales
				for (int i = 0; i < faces.size(); i++)
				{
					circle(frame, Point((int)X0.at<float>(0, i), (int)X0.at<float>(1, i)), 1, Scalar(0, 255, 0), -1);
				}

				// Estimar la posicion de la cabeza
				INTRAFACE::HeadPose hp;
				fa.EstimateHeadPose(X0, hp);
				// Dibujamos los ejes de la posicion.
				drawPose(frame, hp.rot, 50);
				
				//-- Extraer los ángulos del hp
				vector<float> angles;
				for (int i = 0; i <= 3; i++)
				{
					angles.push_back(hp.angles[i]);
					//cout << hp.angles[i] << endl;
				}
				

				// Identificar los ojos
				// Puntos del ojo izquierdo
				vector<Point> leftEyePoints;
				for (int i = 25; i <= 30 ; i++)
				{
					leftEyePoints.push_back(Point(X0.at<float>(0, i), X0.at<float>(1, i)));
					//circle(frame, Point((int)X0.at<float>(0, i), (int)X0.at<float>(1, i)), 2, Scalar(255, 255, 0), -1);
				}				

				// Puntos del ojo derecho
				vector<Point> rightEyePoints;
				for (int i = 19; i <= 24; i++)
				{
					rightEyePoints.push_back(Point(X0.at<float>(0, i), X0.at<float>(1, i)));
					//circle(frame, Point((int)X0.at<float>(0, i), (int)X0.at<float>(1, i)), 2, Scalar(255, 255, 0), -1);
				}

				Rect leftBoundRect = boundingRect(leftEyePoints);
				Rect rightBoundRect = boundingRect(rightEyePoints);
				/*-- Dibujamos el rectangulo que contine los iris de cada ojo
				* El interno (azul) es el que se calcula con los valores de IntraFace
				* el externo (verde) es el que se obtiene con las modificaciones en las 
				* dimensiones del mismo.
				* Pese a que el segundo presenta unas dimensiones mayores, para este 
				* caso usaremos el primero, pues delimita mejor la zona re interes.
				*/
				//-- Rectangulos internos
				//cv::rectangle(frame, leftBoundRect, cv::Scalar(255, 155, 0), 1);
				//cv::rectangle(frame, rightBoundRect, cv::Scalar(255, 155, 0), 1);


				leftBoundRect.x = leftBoundRect.x - 5;
				leftBoundRect.y = leftBoundRect.y - 5;
				leftBoundRect.width = leftBoundRect.width + 8;
				leftBoundRect.height = leftBoundRect.height + 8;

				rightBoundRect.x = rightBoundRect.x - 5;
				rightBoundRect.y = rightBoundRect.y - 5;
				rightBoundRect.width = rightBoundRect.width + 8;
				rightBoundRect.height = rightBoundRect.height + 8;

				lEye = leftBoundRect;
				rEye = rightBoundRect;
				
				Mat leftEye = frameOrig(leftBoundRect);
				Mat rightEye = frameOrig(rightBoundRect);
				//-- Rectangulos externos
				//cv::rectangle(frame, leftBoundRect, cv::Scalar(0, 155, 0), 1);
				//cv::rectangle(frame, rightBoundRect, cv::Scalar(0, 155, 0), 1);
				
				// Mostramos la imagen completa del rostro con los ojos punteados.
				/* Por ahora implementamos una forma de control rudimentaria para definir que
				* clases usaremos, aunque el menú de opciones esta en el main, la opcin se usa aqui :)
				*/

				//Muestras muestra;
				//muestra.guardar(frame, X0, leftEye, rightEye, NULL);
				Test test;
				Train begin;
				Muestras muestra;
				if (opt == 1)
				{
					
					test.display(frame, faces, lEye, rEye, X0, capture);
					cout << ".";
				}
				else if (opt == 2)
				{
					//-- Instanciar la clase de entrenamient
					begin.tryit(X0);
					break;
				}
				else if (opt == 3)
				{
					muestra.guardar(frame, X0, angles, leftEye, rightEye, intent, capture);
				}
				else if (opt == 4)
				{
					muestra.muestrasSeccion(frame, X0, angles, leftEye, rightEye, intent, capture);
				}
				//imshow("Gaze", frame);	
				else if (opt == 0)
				{
					capture.release();
					destroyAllWindows();
					break;
				}
				
			}
		}
	}
	else
	{
		cerr << "No se puede cargar el dispositivo de captura" << endl;
		cerr << "Asegurese de que el dispositivo esta conectado, \n e intentelo nuevamente." << endl;			
	}
	//exit(0);
	return 0;
	// Fin del metodo
}

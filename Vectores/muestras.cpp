#include "muestras.h"
#include "captureFrame.h"

#include "sqlite3.h"
#include <ios>
#include <stdio.h>


void Muestras::guardar(cv::Mat frame, cv::Mat X0, vector<float> angles, cv::Mat lEye, cv::Mat rEye, int& nFrame, cv::VideoCapture& capture)
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
	cv::Point p19((int)X0.at<float>(0, 19), (int)X0.at<float>(1, 19));
	cv::Point p20((int)X0.at<float>(0, 20), (int)X0.at<float>(1, 20));
	cv::Point p21((int)X0.at<float>(0, 21), (int)X0.at<float>(1, 21));
	cv::Point p22((int)X0.at<float>(0, 22), (int)X0.at<float>(1, 22));
	cv::Point p23((int)X0.at<float>(0, 23), (int)X0.at<float>(1, 23));
	cv::Point p24((int)X0.at<float>(0, 24), (int)X0.at<float>(1, 24));
	cv::Point p25((int)X0.at<float>(0, 25), (int)X0.at<float>(1, 25));
	cv::Point p26((int)X0.at<float>(0, 26), (int)X0.at<float>(1, 26));
	cv::Point p27((int)X0.at<float>(0, 27), (int)X0.at<float>(1, 27));
	cv::Point p28((int)X0.at<float>(0, 28), (int)X0.at<float>(1, 28));
	cv::Point p29((int)X0.at<float>(0, 29), (int)X0.at<float>(1, 29));
	cv::Point p30((int)X0.at<float>(0, 30), (int)X0.at<float>(1, 30));
	/*-- Dibujamos los puntos internos de ambos ojos.
	**-- aunque se podrian poner los cuatro, solo se usan de refrencia visual.
	*/
	//cv::circle(frame, b1, 1, cv::Scalar(0, 0, 255), 1);
	//cv::circle(frame, a1, 1, cv::Scalar(0, 0, 255), 1);
	//cv::circle(frame, b2, 1, cv::Scalar(0, 0, 255), 1);
	//cv::circle(frame, a2, 1, cv::Scalar(0, 0, 255), 1);

	//-- Convertimos los puntos a cadenas para enviarlos a setData y guardarlos
	//string pp20 = to_string(p20.x) + "," + to_string(p20.y);

	int p19x = p19.x;
	int p19y = p19.y;
	int p20x = p20.x;
	int p20y = p20.y;
	int p21x = p21.x;
	int p21y = p21.y;
	int p22x = p22.x;
	int p22y = p22.y;
	int p23x = p23.x;
	int p23y = p23.y;
	int p24x = p24.x;
	int p24y = p24.y;

	int p25x = p25.x;
	int p25y = p25.y;
	int p26x = p26.x;
	int p26y = p26.y;
	int p27x = p27.x;
	int p27y = p27.y;
	int p28x = p28.x;
	int p28y = p28.y;
	int p29x = p29.x;
	int p29y = p29.y;
	int p30x = p30.x;
	int p30y = p30.y;

	float roll, yaw, pitch;
	roll = angles[0];
	yaw = angles[1];
	pitch = angles[2];

	cv::imshow(wName, frame);

	//this->setData(lEye, rEye, roll, yaw, pitch, p19x, p19y, p20x, p20y, p21x, p21y, p22x, p22y, p23x, p23y, p24x, p24y, p25x, p25y, p26x, p26y, p27x, p27y, p28x, p28y, p29x, p29y, p30x, p30y, nFrame);
	/*
	bool openClose = this->openEye(X0);
	if (openClose)
	{
	//-- enviamos los datos.


	}
	*/
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

void Muestras::setData(cv::Mat lEye, cv::Mat rEye, float roll, float yaw, float pitch, int p19x, int p19y, int p20x, int p20y, int p21x, int p21y, int p22x, int p22y, int p23x, int p23y, int p24x, int p24y, int p25x, int p25y, int p26x, int p26y, int p27x, int p27y, int p28x, int p28y, int p29x, int p29y, int p30x, int p30y, int nFrame)
{

	fstream imgPuntos;
	fstream contador;

	imgPuntos.open("puntos.txt", ios::app);

	char cont[128];
	//-- Obtenemos el ultimo valor de nFrame
	ifstream fe("contador.txt");
	fe.getline(cont, 128);
	//cout << cont << endl;
	nFrame = stoi(cont);
	fe.close();


	ofstream fs("contador.txt");
	fs << nFrame + 1;
	fs.close();

	string id;
	//string points = p20x, p20y, p21x, p21y, p23x, p23y, p24x, p24y, p26x, p26y, p27x, p27y, p29x, p29y, p30x, p30y;

	/* En este bloque lo que hacemos es formatear el ID de la imagen muestra
	** a falta de una forma mas optima, esto funciona por ahora.
	++ podria usarse alguna forma de formateo, pero bueno, funciona as?.
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

	//-- Guardamos los puntos en un archivo de texto
	//imgPuntos << id << "," << roll << "," << yaw << "," << pitch << "," << p19x << "," << p19y << "," << p20x << "," << p20y << "," << p21x << "," << p21y << "," << p22x << "," << p22y << "," << p23x << "," << p23y << "," << p24x << "," << p24y << "," << p25x << "," << p25y << "," << p26x << "," << p26y << "," << p27x << "," << p27y << "," << p28x << "," << p28y << "," << p29x << "," << p29y << "," << p30x << "," << p30y << endl;
						
	/*	Guardamos en la base de datos
	*/
	sqlite3 *db;
	char *error = 0;
	int res;
	//char *sql;

	res = sqlite3_open("puntos.db", &db);
	if (res)
	{
		cerr << stderr << "No se puede abrir la base de datos" << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return;
	}
	else
	{
		//cout << stderr << ": Base de datos OK\n" << endl;
	}

	/* construimos una consulta*/

	char sql[999] = " ";
	sprintf(sql, "insert into puntosroi(roll, yaw, pitch, p19x, p19y, p20x, p20y, p21x, p21y, p22x, p22y, p23x, p23y, p24x, p24y, p25x, p25y, p26x, p26y, p27x, p27y, p28x, p28y, p29x, p29y, p30x, p30y) values (%f, %f, %f, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d);", roll, yaw, pitch, p19x, p19y, p20x, p20y, p21x, p21y, p22x, p22y, p23x, p23y, p24x, p24y, p25x, p25y, p26x, p26y, p27x, p27y, p28x, p28y, p29x, p29y, p30x, p30y);
	//cout << sql << endl;

	//-- Executamos la consulta
	res = sqlite3_exec(db, sql, NULL, 0, &error);

	if (res != SQLITE_OK)
	{
		fprintf(stderr, "Error: %s\n", error);
		sqlite3_free(error);
	}
	else
	{
		//fprintf(stdout, "Tabla creada!\n");
	}

	sqlite3_close(db);

	cv::imwrite("muestras/" + nlEye, lEye);
	cv::imwrite("muestras/" + nrEye, rEye);

	imgPuntos.close();
}

/*- Obtenemos un promedio en la separacion del los puntos (20, 24) y (21, 23)
--- consideramos un umbral igual o mayor a 6 pixeles para considerar habierto el ojo
--- al menos en resoluciones de (640x420), es posible que haya que hacerlo en funcion
--- de la resolucion del cudro, pero para eso primero conseguir otro dispositivo.
*/
bool Train::openClose(vector<vector<float>> euler, vector<vector<int>> puntos)
{

	cout << "Ok, intentando" << endl;



	//-- Normalizar las distancias
	for (int i = 0; i < puntos.size(); i++)
	{
		cout << puntos[i][0] << ", ";
		//Distancias ojo derecho
		float h1 = puntos[i][7] - puntos[i][1];
		float rn1 = (puntos[i][12] - puntos[i][4]) / h1;
		float rn2 = (puntos[i][10] - puntos[i][6]) / h1;
		//cout << puntos[i][12] << ":" << puntos[i][4] << endl;
		//cout << rn1 << ":" << rn2 << endl;
		//cout << endl;
		//Distancias ojo izquierdo
		float h2 = puntos[i][20] - puntos[i][13];
		float ln1 = (puntos[i][24] - puntos[i][16]) / h2;
		float ln2 = (puntos[i][22] - puntos[i][18]) / h2;
		//cout << puntos[i][24] << ":" << puntos[i][16] << endl;
		//cout << rn1 << ":" << rn2 << endl;


		float coef[5] = { 39.2325,-0.6976, 23.8160, -5.0245 };
		float dist[5] = { ln1, ln2, rn1, rn2 };

		vector<float> OX;
		vector<vector<float>> sig;
		for (int i = 0; i < 5; i++)
		{
			vector<float> tempo;
			float tmp = dist[i] * coef[i];
			float  sigma = 1 / (1 + pow(2.71828183, -tmp));
			//float  sigma = 1 / (1 + exp(-tmp));
			OX.push_back(tmp);
			tempo.push_back(sigma);
			sig.push_back(tempo);
		}

		float sum = 0;



		for (int i = 0; i < sig.size(); i++)
		{
			for (int j = 0; j < sig[0].size(); j++)
			{
				//cout << sig[i][j] << endl;
				sum = sum + sig[i][j];

			}
			//cout << sum / 5 << endl;
		}


		if ((sum / 4) < 0.77)
		{
			cout << "Abierto ";
			return 0;
		}
		else if ((sum / 4)>0.77)
		{
			cout << "Cerrado ";
			return 1;
		}
		cout << sum / 4;
		cout << " ," << puntos[i][25];
		cout << endl;


	}



	return 0;

}



#include "trainer.h"
#include "dataBase.h"

void Train::tryit(cv::Mat X)
{
	this->dataBase();
}

void Train::dataBase()
{
	try
	{
		sql::Driver *driver;
		sql::Connection *con;
		sql::Statement *stmt;
		sql::ResultSet *res;
		sql::PreparedStatement *pstmt;
		//-- Creamos la conexion 
		driver = get_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", "root", "");
		//-- conectamos a la base de datos requerida


		stmt = con->createStatement();
		stmt->execute("USE ojos");
		//stmt->execute("insert into tesy(id) values(1)");

		res = stmt->executeQuery("SELECT * from ojos where id <= 100");

		//-- En este vector almacenamos los grados de orientacion de la cabeza
		vector<vector<float>> euler;
		//-- En este alamacenamos las coordenadas de los puntos de interes y su ID
		vector<vector<int>> puntos;



		while (res->next())
		{
			//-- Alamacensmo los valores de roll, yaw y pitch en un vector
			//- posteriormente 
			vector<float> temp;
			//-- Obtenemos los valores que indican la direccion de la cabeza
			for (int i = 2; i <= 4; i++)
			{
				temp.push_back(res->getDouble(i));
			}
			euler.push_back(temp);
			//-- Inicializamos un vector que contendra los valores de las coordenadas 
			//-- Extraemos los valores, posteriormente se agregan al vector puntos
			vector<int> pTemp;
			pTemp.push_back(res->getInt(1));
			for (int j = 5; j <= 29; j++)
			{
				pTemp.push_back(res->getInt(j));
			}
			puntos.push_back(pTemp);

		}
		/*
		//-- Mostramos los valores del vector de orientacion
		for (int i = 0; i < euler.size(); i++)
		{
		for (int j = 0; j < euler[0].size(); j++)
		{
		cout << euler[i][j] << endl;
		}
		}
		cout << endl;
		//-- Mostramos los valores del vector de coordenadas
		for (int i = 0; i < puntos.size(); i++)
		{
		for (int j = 0; j < puntos[0].size(); j++)
		{
		cout << puntos[i][j] << "," ;
		}
		cout << endl;
		}
		*/
		//-- Enviamos los vectores a donde sea que los nececitemos :)	
		this->openClose(euler, puntos);
		//this->lr();
		cout << "Ok,llegamos hasta aqui!!" << endl;
		cin.get();
	}
	catch (sql::SQLException &e)
	{
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line »" << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}
}


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
		float ln1 = (puntos[i][24] - puntos[i][16])/h2;
		float ln2 = (puntos[i][22] - puntos[i][18])/h2;
		//cout << puntos[i][24] << ":" << puntos[i][16] << endl;
		//cout << rn1 << ":" << rn2 << endl;
		

		float coef[5] = {39.2325,-0.6976, 23.8160, -5.0245 };
		float dist[5] = {ln1, ln2, rn1, rn2 };

		vector<float> OX;
		vector<vector<float>> sig;
		for (int i = 0; i < 5; i++)
		{
			vector<float> tempo;
			float tmp = dist[i] * coef[i];
			float  sigma = 1 / (1 + pow(2.71828183,-tmp));
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
		

		if ((sum / 4) < 0.77 )
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


static void showImage(const cv::Mat &data, int columns, const string &name)
{
	cv::Mat bigImage;
	for (int i = 0; i < data.rows; i++)
	{
		bigImage.push_back(data.row(i).reshape(0, columns));
	}
	cv::imshow(name, bigImage);
}

static float calculateAccuracyPercent(const cv::Mat &original, const cv::Mat &predicted)
{
	return 100 * (float)cv::countNonZero(original == predicted) / predicted.rows;
}

void  Train::lr()
{
	const string filename = "data01.xml";
	cout << "**********************************************************************" << endl;
	cout << filename
		<< " contains digits 0 and 1 of 20 samples each, collected on an Android device" << endl;
	cout << "Each of the collected images are of size 28 x 28 re-arranged to 1 x 784 matrix"
		<< endl;
	cout << "**********************************************************************" << endl;

	cv::Mat data, labels;
	{
		cout << "Loading the datashet....";
		cv::FileStorage f;
		if (f.open(filename, cv::FileStorage::READ))
		{
			f["datamat"] >> data;
			f["labelsmat"] >> labels;
			f.release();
		}
		else
		{
			cerr << "file canot be oppened..." << filename << endl;
			return;
		}
		data.convertTo(data, CV_32F);
		labels.convertTo(labels, CV_32F);
		cout << "read" << data.rows << "rows of data" << endl;

	}

	cv::Mat data_train, data_test;
	cv::Mat labels_train, labes_test;

	for (int i = 0; i < data.rows; i++)
	{
		if (i % 2 == 0)
		{
			data_train.push_back(data.row(i));
			labels_train.push_back(labels.row(i));
		}
		else
		{
			data_test.push_back(data.row(i));
			labes_test.push_back(labels.row(i));
		}
	}

	cout << "training/testing samples count " << data_train.rows << "/" << data_test.rows << endl;

	// Display sample image
	showImage(data_train, 28, "train data");
	showImage(data_test, 28, "test data");

	// simple case batch gradient
	cout << "training...";
	//![init]
	cv::Ptr<cv::ml::LogisticRegression> lr1 = cv::ml::LogisticRegression::create();
	lr1->setLearningRate(0.0001);
	lr1->setIterations(10);
	lr1->setRegularization(cv::ml::LogisticRegression::REG_L2);
	lr1->setTrainMethod(cv::ml::LogisticRegression::BATCH);
	lr1->setMiniBatchSize(1);
	lr1->train(data_train, cv::ml::ROW_SAMPLE, labels_train);
	cout << "done" << endl;

	cout << "predicting..";
	cv::Mat responses;
	lr1->predict(data_test, responses);
	cout << "done!" << endl;

	// Show prediction report
	cout << "Original vs Predicted" << endl;
	labes_test.convertTo(labes_test, CV_32S);
	cout << labes_test.t() << endl;
	cout << responses.t() << endl;
	cout << "Accuracy: " << calculateAccuracyPercent(labes_test, responses) << "%" << endl;

	const string saveFileName = "NewLR_Trained.xml";
	cout << "Saving the classifier to" << saveFileName << endl;
	lr1->save(saveFileName);

	// Load de classifier onto new object
	cout << "loading  a new classifier from " << saveFileName << endl;
	cv::Ptr<cv::ml::LogisticRegression> lr2 = cv::ml::StatModel::load<cv::ml::LogisticRegression>(saveFileName);

	// Predict using lades classifier
	cout << "predicting the dataset using the loaded classifier...";
	cv::Mat responses2;
	lr2->predict(data_test, responses2);
	cout << "done!" << endl;

	// calculate accuracy
	cout << labes_test.t() << endl;
	cout << responses2.t() << endl;
	cout << "Accuracy: " << calculateAccuracyPercent(labes_test, responses2) << "%" << endl;
	cin.get();
	return;
}
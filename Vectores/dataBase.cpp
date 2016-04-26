#include "dataBase.h"


void Database::dataBase()
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

		res = stmt->executeQuery("SELECT * from ojos where id < 3");

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
		
		
		cout << "Ok,llegamos hasta aqui!!" << endl;
		return;
		

		
	}
	catch(sql::SQLException &e)
	{
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line »" << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}
	cin.get();

}

#include "dataBase.h"


void Database::dataBase()
{
	sql::Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;
	string resultado;

	//-- Intenta obtener un controlador para conectar con el sistema de base de datos	
	//--Intentar conectar con lka base de datos
	try
	{


		driver = get_driver_instance();
		con = driver->connect("localhost:3306", "root", "");
		con->setSchema("eyegaze");
		stmt = con->createStatement();
		res = stmt->executeQuery("insert into puntos(p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30) values(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12)");

	}
	catch (sql::SQLException &e)
	{
		cerr << "# ERR: " << e.what();
		cout << "(MySQL errro code: " << e.getErrorCode();
		cout << " : SQLState: " << e.getSQLState() << " )" << endl;
		return;
	}


	res->close();
	stmt->close();
	con->commit();
	con->close();
	//return "h";
}


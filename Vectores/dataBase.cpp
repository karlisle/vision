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
		con = driver->connect("tcp://127.0.0.1:3306", "root", "thrones");
		//-- conectamos a la base de datos requerida
		

		stmt = con->createStatement();
		stmt->execute("USE ojos");
		//stmt->execute("insert into tesy(id) values(1)");

		res = stmt->executeQuery("SELECT id from ojos where id < 10");
		
		while (res->next())
		{
			cout <<"ID: "<< res->getInt(1) << endl;
		}

		cin.get();
		

		cout << "Ok,llegamos hasta aqui!!" << endl;
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


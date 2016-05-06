#include "dataBase.h"


bool Database::insertarDatos(string consulta)
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
		//cout << consulta << endl;
		//--Ejecutamos la sentencia y retyornamos el estatus
		int insertData = stmt->executeUpdate(consulta.c_str());
		cout << insertData << endl;
		
		//--- Retornamos el estatus de la sentencia y cerramos la conexión
		delete stmt;
		return true;
	}
	catch(sql::SQLException &e)
	{
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line »" << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		return false;
	}
}

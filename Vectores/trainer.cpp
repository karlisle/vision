#include "trainer.h"



void Train::openClose()
{
	/*	Connectamos a la base de datos
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
		cout << stderr << ": Base de datos OK\n" << endl;
	}

	/* construimos una consulta*/

	char sql[999] = " ";
	sprintf(sql, "SELECT id FROM puntosroi where id < 10");
	//cout << sql << endl;

	sqlite3_stmt *stmt;
	if (sqlite3_prepare("puntos.db", sql, -1, &stmt, 0) == SQLITE_OK)
	{

	}






	//-- Executamos la consulta
	res = sqlite3_exec(db, sql, NULL, 0, &error);

	if (res != SQLITE_OK)
	{
		fprintf(stderr, "Error: %s\n", error);
		sqlite3_free(error);
	}
	else
	{
		fprintf(stdout, "OK!\n");		
	}

	sqlite3_close(db);

	// -- Mecanismo para regresar al menu principal
	char k = cv::waitKey(0);
	if (k == 'r')
	{
		cout << "regresando al menu principal" << endl;
		cv::destroyAllWindows();
		CaptureFrame capt;
		capt.menu();
	}
}


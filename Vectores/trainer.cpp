#include "trainer.h"

void reciveData(vector<vector<string>> datos)
{
	for (int i = 0; i < datos.size(); i++)
	{
		cout << "Ahora vamos a hacer algo genial" << endl;
		int p19x = stoi(datos[0][4]);
		int p19y = stoi(datos[0][5]);
		cout << "P19y:" << p19x << "," << p19y << endl;
		cin.get();


	}
	cin.get();
	
}


static int callback(void *data, int argc, char **argv, char **azColName) {
	int i;
	vector<vector<string>> datos;
	vector<string> row;
	fprintf(stderr, "%s: ", (const char*)data);
	for (i = 0; i<argc; i++) {
		//printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		row.push_back(argv[i]);
	}
	datos.push_back(row);
	reciveData(datos);	
	return 0;
}

int Train::openClose()
{
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char *sql;
	const char* data = "Callback function called";

	/* Open database */
	rc = sqlite3_open("puntos.db", &db);
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		exit(0);
	}
	else {
		fprintf(stderr, "Opened database successfully\n");
	}

	/* Create SQL statement */
	sql = "SELECT * from puntosroi";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
	cout << rc << endl;
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Operation done successfully\n");
	}
	sqlite3_close(db);
	cin.get();
	return 0;
}
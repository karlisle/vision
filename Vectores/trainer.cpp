#include "trainer.h"

void reciveData(vector<vector<string>> datos)
{
	cout << datos.size() << endl;
	for (int i = 0; i < datos.size(); i++)
	{
		cout << "Ahora vamos a hacer algo genial" << endl;
		int id = stoi(datos[i][0]);
		float roll = atof(datos[i][1].c_str());
		float yaw = atof(datos[i][2].c_str());
		float pitch = atof(datos[i][3].c_str());
		int p19x = stoi(datos[i][4]);
		int p19y = stoi(datos[i][5]);
		int p20x = stoi(datos[i][6]);
		int p20y = stoi(datos[i][7]);
		int p21x = stoi(datos[i][8]);
		int p21y = stoi(datos[i][9]);
		int p22x = stoi(datos[i][10]);
		int p22y = stoi(datos[i][11]);
		int p23x = stoi(datos[i][12]);
		int p23y = stoi(datos[i][13]);
		int p24x = stoi(datos[i][14]);
		int p24y = stoi(datos[i][15]);
		int p25x = stoi(datos[i][16]);
		int p25y = stoi(datos[i][17]);
		int p26x = stoi(datos[i][18]);
		int p26y = stoi(datos[i][19]);
		int p27x = stoi(datos[i][20]);
		int p27y = stoi(datos[i][21]);
		int p28x = stoi(datos[i][22]);
		int p28y = stoi(datos[i][23]);
		int p29x = stoi(datos[i][24]);
		int p29y = stoi(datos[i][25]);
		int p30x = stoi(datos[i][26]);
		int p30y = stoi(datos[i][27]);
		int state = stoi(datos[i][28]);

		cout << "ID:"<< id << " : Roll:" << roll << " : P19y:" << p19x << "," << p19y << endl;
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
	sql = "SELECT * from ojos";

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
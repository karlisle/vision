
#pragma once
#ifndef DATABASE_H
#define DATABASE_H

#include <sstream>
#include <Windows.h>
#include <stdlib.h>
#include <iostream>
#include <queue>
#include <stdio.h>
#include <math.h>
#include <string>
#include <fstream>
#include <cppconn\driver.h>
#include <cppconn\exception.h>
#include <cppconn\resultset.h>
#include <cppconn\statement.h>

#include "mysql_connection.h"
#include "dataBase.h"


using namespace std;


class Database
{
public:
	//-- Constructor
	Database() {
	}

	void dataBase();

private:
	

};

#endif // !DATABASE_H
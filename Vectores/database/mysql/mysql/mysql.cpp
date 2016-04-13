// mysql.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>



#include "mysql_connection.h"


#include <cppconn\driver.h>
#include <cppconn\exception.h>
#include <cppconn\resultset.h>
#include <cppconn\statement.h>
#include <cppconn\prepared_statement.h>


#define HOST "localhost"
#define USER "root"
#define PASS "thrones"
#define DB	"pruebas"

using namespace std;

int main(int argc, const char **argv)
{

	string url(HOST);
	const string user(USER);
	const string pass(PASS);
	const string db(DB);


	
	cin.get();
}


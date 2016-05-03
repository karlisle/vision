#pragma once
#pragma once
#ifndef TRAINER_H
#define TRAINER_H

#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2\ml\ml.hpp>

#include <sstream>
#include <Windows.h>
#include <stdlib.h>
#include <iostream>
#include <queue>
#include <stdio.h>
#include <math.h>
#include <string>
#include <fstream>
#include <ios>
#include <iomanip>

#include <cppconn\driver.h>
#include <cppconn\exception.h>
#include <cppconn\resultset.h>
#include <cppconn\statement.h>


#include "mysql_connection.h"
#include "dataBase.h"
#include "captureFrame.h"



using namespace std;

class Train
{
public:
	//-- Constructor
	Train() {
	}
	void tryit();
	int openClose(vector<vector<float>> euler, vector<vector<int>> punto);

private:
	//static int callback(void *data, int argc, char **argv, char **azColName);
	void dataBase();
	void  lr();
	
};
#endif // !TRAINER_H
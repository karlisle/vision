#include "captureFrame.h"
#include "test.h"
#include "cameraCalibration.h"
#include "captureFrame.h"

using namespace std;

int main(int argc, char** argv)
{
	cout << "\n\n\t****************************" << endl;
	cout << "\t* Welcome to EyeGaze-Dev!  *" << endl;
	cout << "\t****************************" << endl;
	cout << "\n >>> ";

	cout << "\t****************************" << endl;
	cout << "\t*   Seleccione una opción  *" << endl;
	cout << "\t* 1) Cargar (CDF)     *" << endl;
	cout << "\t* 2) Calibrar la camara *" << endl;
	cout << "\t* 3) Tomar muestras*" << endl;
	cout << "\t****************************" << endl;

	int opcion;
	cin >> opcion;
	switch (opcion)
	{
		case 1:
			CaptureFrame  device;
			device.detect();
			break;
		case 2: 
			Calibration calibration;
			calibration.camCalibration();
			break;
		case 3:

			break;
	default:
		break;
	}

	//Calibration camCalib;
	//camCalib.camCalibration();

	//CaptureFrame begin;
	//begin.detect();

	

	//Detener la ejecucion







	cin.get();
	return 0;
}
#include "captureFrame.h"
#include "test.h"
#include "cameraCalibration.h"

using namespace std;

int main(int argc, char** argv)
{
	cout << "\n\n\t****************************" << endl;
	cout << "\t* Welcome to EyeGaze-Dev!  *" << endl;
	cout << "\t****************************" << endl;
	cout << "\n >>> ";

	Calibration camCalib;
	camCalib.camCalibration();

	//CaptureFrame begin;
	//begin.detect();

	//Test cosos;
	//cosos.display();

	//Detener la ejecucion
	cin.get();
	return 0;
}
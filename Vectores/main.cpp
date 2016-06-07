#include "captureFrame.h"


using namespace std;

int main(int argc, char** argv)
{
	cout << "\n\n\t*****************************" << endl;
	cout << "\t* Welcome to EyeGaze-Dev!   *" << endl;
	cout << "\t*****************************" << endl;

	CaptureFrame capture;
	capture.menu();
	cout << "\n\n\t**********************************" << endl;
	cout << "\t* Gracias por usar EyeGaze-Dev!  *" << endl;
	cout << "\t**********************************" << endl;
	cout << "\n\t\t =.= ";
	cin.get();
	return 0;
}
#include "ofMain.h"
#include "ofApp.h"  
#include <string>
using namespace std; //allows me to skip filling in 'std' everywhere

int main()
{
	ofSetupOpenGL(900, 500, OF_WINDOW); // kicks off App, running it in a window
	return ofRunApp(std::make_shared<ofApp>());
}
//
// Copyright (c) 2018 Christopher Baker <https://christopherbaker.net>  MIT Licence
//
#include "ofMain.h"
#include "ofxTwitter.h"
#include "ofxTextSuite.h"

class ofApp : public ofBaseApp
{
public: //Declaring app functions
	void setup();
	void draw();
	void keyPressed(int key);
	void geoLocation1();
	void geoLocation2();
	void geoLocation3();
	void hashtag();
	void mentionHughJackman();
	void mentionVancityReynolds();
	void bathRugby();
	void worldOfWarcraft();
	void news();
	void freeSearch();
	void onStatus(const ofxTwitter::Status& status);
	void onError(const ofxTwitter::Error& error);
	void onException(const std::exception& exception); 
	void onMessage(const ofJson& json);

	ofxTwitter::SearchClient client; //Declares twitter search client

	int count = 0;
	int countMissed = 0;

	ofColor c1, c2;

	int menuSelection; //the integer to hold selection once available
	char menuReturn;

	ofImage twitterLogo; // holds the twitter logo used
	ofTrueTypeFont mainTXT, subTXT, errorTXT; // holds the font used
	stringstream menu; //puts menu on the GUI
	stringstream tweets;

	ofxTextBlock myPara;
	int paraY;

	bool allowSearch = false;
	string userSearch = "";

	bool error = false; // error message
	string errorMessage = "   Something went wrong, try something else.";
};

// Commented for later use/reference
//
//class ofApp : public ofBaseApp{
//
//	public:
//		void setup();
//		void update();
//		void draw();
//
//		void keyPressed(int key);
//		void keyReleased(int key);
//		void mouseMoved(int x, int y );
//		void mouseDragged(int x, int y, int button);
//		void mousePressed(int x, int y, int button);
//		void mouseReleased(int x, int y, int button);
//		void mouseEntered(int x, int y);
//		void mouseExited(int x, int y);
//		void windowResized(int w, int h);
//		void dragEvent(ofDragInfo dragInfo);
//		void gotMessage(ofMessage msg);
//		
//};

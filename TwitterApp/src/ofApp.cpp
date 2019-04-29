//
// Copyright (c) 2018 Christopher Baker <https://christopherbaker.net>  MIT Licence
//
#include "ofApp.h"
#include <string>
using namespace std; //allows me to skip filling in 'std' everywhere

void ofApp::setup()
{
	ofSetFrameRate(30); // keeps app framerate low
	client.setCredentialsFromFile("credentials.json"); // credentials file for access to twitter
	client.setPollingInterval(6000); //establishes new tweets will be retrieved every 6 seconds

	myPara.init("Arial.ttf", 11);
	paraY = 10;
	c1.set(7, 130, 175); //sets homepage to 'twitter blue'
	c2.set(255, 255, 255); //secondary colour of white used to make gradient visible

	mainTXT.load("Arial.ttf", 20);//main heading font set
	subTXT.load("Arial.ttf", 11); //body text font set
	errorTXT.load("Arial.ttf", 15);//error text sent

	menu.str(""); //makes use of stringstream to read from the string
	menu << "Pick your search:\n" << endl; 
	menu << "1 for Bath Spa University" << endl;
	menu << "2 for Bath" << endl;
	menu << "3 for Cornwall" << endl;
	menu << "4 for #YellowVest" << endl;
	menu << "5 for @RealHughJackman" << endl;
	menu << "6 for @VancityReynolds" << endl;
	menu << "7 for Bath Rugby" << endl;
	menu << "8 for Todays news" << endl;
	menu << "9 for World of Warcraft" << endl;
	menu << " 0 to make your own search" << endl;

	twitterLogo.load("twitterlogo.png");
}
void ofApp::draw() { // used to draw the GUI

	ofBackgroundGradient(c1, c2, OF_GRADIENT_LINEAR); //used to set background colour of GUI
	auto total = count + countMissed;

	stringstream ss; //stringstream used to display the number of tweets received
	ss << "Twitter Search" << endl;
	ss << "  Received: " << count << endl;
	ss << "    Missed: " << countMissed << endl;
	ss << "     Total: " << total << endl;

	if (total > 0){ 
		received = ofToString(static_cast<double>(count) / total * 100, 2);
	}

	ss << "% Received: " << received;

	ofDrawBitmapStringHighlight(ss.str(), 14, 14);
	ofSetColor(0, 0, 0); //sets background of rectangle to black
	ofDrawRectangle(0, 0, 275, 900); //draws rectangle to the left of screen
	ofSetColor(255, 255, 255); //sets text colour to white
	subTXT.drawString(menu.str(), 10, 150); //gives GUI options arial font
    twitterLogo.draw(10, 1, 110, 110);

	ofSetColor(255);
	myPara.setHtmlText(tweets.str()); //using html for line breaks
	myPara.wrapTextX(450); //sets wrap
	myPara.draw(300, paraY); //draws paragraph

	ofSetColor(0, 132, 180);
	ofDrawRectangle(275, 0, 525, 35);

	ofSetColor(255);
	mainTXT.drawString("Twitter Search", 450, 30); //using arial font to place into the GUI

	if (allowSearch) {
		ofSetColor(0);
		ofDrawBitmapStringHighlight("Enter Search Term: ", 15, 370);
		ofDrawBitmapStringHighlight(userSearch, 20, 390);
	}
	if (error) {
		ofSetColor(255, 0, 0);
		errorTXT.drawString(errorMessage, 15, 450);
	}
}
void ofApp::keyPressed(int key) { //assorts key functions for enter and delete before switch statement

	if (allowSearch) {
		if (key == OF_KEY_RETURN) { //ensures enter key will function as intended
			freeSearch();
			allowSearch = false;
		}
		else if (key == OF_KEY_DEL || key == OF_KEY_DEL) { // ensures delete will function as intended
			userSearch.pop_back();
		}
		else {
			ofAppendUTF8(userSearch, key);
		}
	}
	else {
		switch (key) {  // switch statement to display options
		case '1':
			error = false;
			geoLocation1(); // containing the search query for Bath Spa University using geocode
			break;
		case '2':
			error = false;
			geoLocation2(); // containing the search query for Bath using geocode
			break;
		case '3':
			error = false;
			geoLocation3(); // containing the search query for cornwall using geocode
			break;
		case '4':
			error = false;
			hashtag(); // containing the search query for the Yellow Vest hashtag
			break;
		case '5':
			error = false;
			mentionHughJackman(); // containing the search query for Hugh Jackman
			break;
		case '6':
			error = false;
			mentionVancityReynolds(); // containing the search query for Ryan Reynolds
			break;
		case '7':
			error = false;
			bathRugby(); // containing the search query for Bath Rugby
			break;
		case '8':
			error = false;
			news();  // containing the search query for up to date news
			break;
		case '9':
			error = false;
			worldOfWarcraft(); // allows the user to search for World of Warcraft
			break;
		case '0':
			error = false;
			allowSearch = true; // allows the user to search for anything
			userSearch = "";
			break;
		default:
			error = true;
			errorMessage;// displays error if something wrong is used
			break;
		}
	}
}
void ofApp::geoLocation1() {
	count = 0;
	tweets.str("");
	ofxTwitter::SearchQuery query("Bath Spa University");
	query.setGeoCode(51.3932808, -2.3717135, 10, ofxTwitter::SearchQuery::UNITS_MILES); // uses geocode for coordinates: Latitude, Longitude, Radius(Set to miles)
	query.setLanguage("en"); // returns tweets in english 
	client.search(query);
}
void ofApp::geoLocation2() {
	count = 0;
	tweets.str("");
	ofxTwitter::SearchQuery query("Bath");
	query.setGeoCode(51.3813864, -2.3596963, 20, ofxTwitter::SearchQuery::UNITS_MILES);
	query.setLanguage("en");
	client.search(query);
}
void ofApp::geoLocation3() {
	count = 0;
	tweets.str("");
	ofxTwitter::SearchQuery query("Cornwall");
	query.setGeoCode(50.416667, -4.75, 100, ofxTwitter::SearchQuery::UNITS_MILES);
	query.setLanguage("en");
	client.search(query);
}
void ofApp::hashtag() {
	count = 0;
	tweets.str("");
	ofxTwitter::SearchQuery query("#YellowVest");
	query.setLanguage("en");
	client.search(query);
}
void ofApp::mentionHughJackman() {
	count = 0;
	tweets.str("");
	ofxTwitter::SearchQuery query("@RealHughJackman");
	query.setLanguage("en");
	client.search(query);
}
void ofApp::mentionVancityReynolds() {
	count = 0;
	tweets.str("");
	ofxTwitter::SearchQuery query("@VancityReynolds");
	query.setLanguage("en");
	client.search(query);
}
void ofApp::bathRugby() {
	count = 0;
	tweets.str("");
	ofxTwitter::SearchQuery query("Bath Rugby");
	query.setLanguage("en");
	client.search(query);
}
void ofApp::worldOfWarcraft() {
	count = 0;
	tweets.str("");
	ofxTwitter::SearchQuery query("World of Warcraft");
	query.setLanguage("en");
	client.search(query);
}
void ofApp::news() {
	count = 0;
	tweets.str("");
	ofxTwitter::SearchQuery query("news");
	query.setLanguage("en");
	client.search(query);
}
void ofApp::freeSearch() {
	count = 0;
	tweets.str("");
	ofxTwitter::SearchQuery query(userSearch);
	query.setLanguage("en");
	client.search(query);
}
void ofApp::onStatus(const ofxTwitter::Status& status) { // called everytime a new tweet is received
    count++;//enables the tweets to be counted

	if (count <= 20) {
		//tweet display used by the GUI, format built on from example app
		tweets << status.user()->name() << ": " << status.text() << "<br/><br/>";
		ofLogNotice("ofApp::onStatus") << "Text: " << status.text();
		ofLogNotice("ofApp::onStatus") << "Coordinates: " << (status.coordinates() ? ofToString(status.coordinates()) : "NONE");
		ofLogNotice("ofApp::onStatus") << "Place: " << (status.place() ? ofToString(status.place()->fullName()) : "NONE");
	}
	else {
		client.stop(); //the search for tweets stops.
	}
}
void ofApp::onException(const std::exception & exception){ // returns exception if exception occurs during program
}
void ofApp::onError(const ofxTwitter::Error& error)
{
	std::cout << "Error: " << error.code() << " " << error.message();
}

// Commented for ease of copy/pasting
//--------------------------------------------------------------
//void ofApp::setup(){

	//}

//--------------------------------------------------------------
//void ofApp::update(){

	//}

//--------------------------------------------------------------
//void ofApp::draw(){

//}

//--------------------------------------------------------------
//void ofApp::keyPressed(int key){

	//}

//--------------------------------------------------------------
//void ofApp::keyReleased(int key){

	//}

//--------------------------------------------------------------
//void ofApp::mouseMoved(int x, int y ){

	//}

//--------------------------------------------------------------
//void ofApp::mouseDragged(int x, int y, int button){

	//}

//--------------------------------------------------------------
//void ofApp::mousePressed(int x, int y, int button){

//}

//--------------------------------------------------------------
//void ofApp::mouseReleased(int x, int y, int button){

//}

//--------------------------------------------------------------
//void ofApp::mouseEntered(int x, int y){

	//}

//--------------------------------------------------------------
//void ofApp::mouseExited(int x, int y){

	//}

//--------------------------------------------------------------
//void ofApp::windowResized(int w, int h){

	//}

//--------------------------------------------------------------
//void ofApp::gotMessage(ofMessage msg){

	//}
//
//--------------------------------------------------------------
//void ofApp::dragEvent(ofDragInfo dragInfo){ 
//
//}

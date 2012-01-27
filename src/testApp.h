#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxVectorMath.h"
#include "ofxBox2d.h"

#include "NanoKtl.h"
#include "VPaint.h"

//#include "wuAnimataKinectManager.h"
//#include "wuKinectSkel.h"
#include "wuNuvolManager.h"
#include "wuSkinManager.h"
#include "wuPapallonaManager.h"
#include "wuSolidCircleManager.h"
#include "wuForegroundSkinManager.h"
#include "wuSolidShapeManager.h"
#include "wuMassiveManager.h"
#include "wuMarManager.h"
#include "wuBocataManager.h"
#include "wuPlatformManager.h"
#include "wuSolidRectManager.h"
//#include "wuAnimalXMLManager.h"
//#include "wuAnimataXMLManager.h"
#include "wuSkinManager.h"
//#include "wuEnanito.h"
#include "wuBlobInspector.h"
//#include "wuMovieVec.h"
#include "wuSimpleMovie.h"
#include "wuGrassManager.h"

//#define _USE_KINECT // uncomment this to use kinect

#define OFF_SCREEN 860 // offset en el que comença la 2a pantalla
#define OFF_MENU 690 // offset del menu

#define WIDTH 640
#define HEIGHT 480

#define NUVOL 0
#define BOLA 1
#define MASSIVE 2
#define PAPERET 3
#define BOCATA 4
#define PEIX 5
#define PLATAFORMA 6
#define PAPALLONA 7
#define FONS 8
#define BOX 9
#define MOVIE 10
#define ANIMAL 11 
#define ANIMATA 12 
#define ANIMATAXML 13 
#define SIMPLE_MOVIE 14 
#define HIERBAJOS 15


class testApp : public ofBaseApp, public NanoKtl{

	public:
		void setup();
		void update();
		void draw();
    void drawInfo();
		void clear();
		void touch(int x, int y);
		void inunda();
		void kameame();
		void marabunta_animal();
    
    void mapMidiInput(); // MIDI
    void setThreshold();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

	ofxBox2d	box2d;			  //	the box2d world

	wuSolidRectManager boxes;
//	wuEnanito enanito;
//	wuAnimataKinectManager animata;
//	wuKinectSkel kinSkel;
	wuSolidShapeManager	tactils;	
	wuSkinManager fons;
	wuNuvolManager	nuvols;
	wuPapallonaManager papallones;
	wuSolidCircleManager boles;
	wuMassiveManager massives;
	wuMassiveManager	paperets;
	wuPlatformManager plataformes;
	wuMarManager mar;
//	wuMovieVec movies;
	wuBocataManager bocata;
//	wuMovieMonsterPlus movies[MAX_MOVIES];
	wuForegroundSkinManager ma;
//	wuAnimalXMLManager animals;
//	wuAnimataXMLManager animatasXML;
	wuBlobInspector blobInspector;
	wuSimpleMovie pajarraco;
    wuGrassManager hierbajos;
	
	// OpenCV
	bool					bDrawGray, isRaining;
	int						vw, vh;
	int actual_movie;

	bool bMa;

	int bBeforeFirstSpace;
    int		threshold, threshold_save;
	bool	bLearnBakground;
	bool	bTakeB2DShot;
	bool	bCambiazo;
	bool	bFixShapes, bShowLines;
	bool	bMar;
	bool	bBocata;
	int		obj_type;
	int enano_scale;

	// CV images
    ofVideoGrabber			vidGrabber;

	ofImage			color;
	ofImage			bgColor;

	ofImage deu;
    
    // cortina
    int curtainAlpha;
    
    ofFbo publicFbo, privateFbo;
    
    // VPaint
    VPaint vpaint;
    
};

#endif

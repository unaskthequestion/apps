#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup() {
	
	ofSetVerticalSync(true);
	ofBackground(0, 0, 0);
	ofSetLogLevel(OF_LOG_NOTICE);
//    ofSetFrameRate(12);
    
    NanoKtl::setup();
    
    curtainAlpha = 0 ;

	threshold		 = 29;
	bLearnBakground = true;

	bTakeB2DShot = false;
	bCambiazo = false;

	isRaining = false;
	bBeforeFirstSpace = true;

	vw = WIDTH;
	vh = HEIGHT;
    vidGrabber.listDevices();
    vidGrabber.setDeviceID(5);
	vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(vw, vh);
    
    publicFbo.allocate(vw,vh);
    privateFbo.allocate(vw,vh);

	color.allocate(vw, vh, OF_IMAGE_COLOR);
	bgColor.allocate(vw, vh, OF_IMAGE_COLOR);

	box2d.init();
	box2d.setGravity(0, 10);
	box2d.createFloor();
	box2d.checkBounds(true);
	box2d.setFPS(15.0);

 	#ifdef _USE_KINECT
	kinSkel.setup();
	animata.setup(&box2d, &kinSkel, vw, vh);
	enanito.setup(&box2d, vw, vh);
	#endif

	boxes.setup(&box2d, vw, vh);
	nuvols.setup(&box2d, vw, vh);
	fons.setup(vw, vh);
	papallones.setup(vw, vh);
	boles.setup(&box2d, vw, vh);

	ma.setup(vw, vh);
	ma.setMaxBlobs(3);

    massives.setup(&box2d, vw, vh);
	paperets.setParams(0.025, 0.6, 0.1);
	paperets.setResolution(4);
    paperets.setup(&box2d, vw, vh);

	plataformes.setup(&box2d, vw, vh);
//	movies.setup(&box2d, vw, vh, "peix.mov");


//	animals.setup(&box2d, "9animal.xml", vw, vh);
//	animals.setMaxBlobs(9);
//	animals.setup(&box2d, "2elefant.xml", vw, vh);
//	animals.setMaxBlobs(2);
//
//	animatasXML.setup(&box2d, "animata.xml", vw, vh);
//	animatasXML.setMaxBlobs(15);

	tactils.setup(&box2d, vw, vh);
	tactils.setMaxBlobs(1);

	mar.setup(&box2d, vw, vh);
	bocata.setup(vw,vh);
	
	blobInspector.setup(vw,vh);

	pajarraco.setup("falco_llarg-alpha_60fps.mov");
    pajarraco.scale(0.4);
    
    
    hierbajos.setup(&box2d, vw, vh);
    hierbajos.setMaxBlobs(1);

//	deu.setImageType(OF_IMAGE_COLOR_ALPHA);
//	deu.loadImage("deu.png");


	obj_type = NUVOL;
	bFixShapes = false;

	bShowLines = true;
	bMa = false;
	bMar = false;
	bBocata = false;

	enano_scale = 1;
    
    // VPaint
    vpaint.setVideoGrabber(vidGrabber);
    vpaint.setup();
}

//--------------------------------------------------------------
void testApp::update(){
	bool bNewFrame = false;

	vidGrabber.grabFrame();
    bNewFrame = vidGrabber.isFrameNew();

	if (bNewFrame) {
        color.setFromPixels(vidGrabber.getPixels(), vw,vh, OF_IMAGE_COLOR);

		if (bLearnBakground == true) {
			bgColor = color;
			bLearnBakground = false;
		}

		// mentre capturo no interessa tenir shape fisic
		if(bTakeB2DShot || bCambiazo)
            tactils.bypass(true);
		else
            tactils.bypass(false);

	   if(bFixShapes && !bTakeB2DShot && !bCambiazo)
            tactils.capture(&color,&bgColor);
	   if(bMa && !bTakeB2DShot && !bCambiazo)
            ma.capture(&color,&bgColor);
       if(bMar)
            mar.capture(&color,&bgColor);
       if(bShowLines)
            blobInspector.capture(&color,&bgColor);


        // Captura de l' objecte 2D
        if(bTakeB2DShot){

            bTakeB2DShot = false;
            // després de capturar passem a mostrar el fons i ocultar càmera

			if (obj_type == NUVOL)
				bCambiazo = nuvols.capture(&color,&bgColor);
			if (obj_type == FONS)
				bCambiazo = fons.capture(&color,&bgColor);
			if (obj_type == PAPALLONA)
				bCambiazo = papallones.capture(&color,&bgColor);
			if (obj_type == BOLA)
				bCambiazo = boles.capture(&color,&bgColor);
            if ( obj_type == MASSIVE)
			{
				massives.capture(&color,&bgColor);
				bCambiazo = true;
			}
			if (obj_type == PAPERET)
			{
				paperets.capture(&color,&bgColor);
				bCambiazo = true;
			}
			if (obj_type == PLATAFORMA)
			{
				plataformes.capture(&color,&bgColor);
	            bCambiazo = true;
			}
			if (obj_type == BOCATA)
				bCambiazo = bocata.capture(&color,&bgColor);

			if (obj_type == BOX)
			{
				ofPoint _mouse;
				_mouse.x = mouseX;
				_mouse.y = mouseY;
				bCambiazo = boxes.capture(&color,&bgColor, _mouse);
			}
		 	#ifdef _USE_KINECT
			if (obj_type == ANIMATA)
				animata.capture(&color,&bgColor);
			#endif
			
//			if (obj_type == ANIMAL)
//				bCambiazo = animals.capture(&color,&bgColor);
//			if (obj_type == ANIMATAXML)
//				bCambiazo = animatasXML.capture(&color,&bgColor);

//			if (obj_type == PEIX)
//				bCambiazo = movies.capture(&color,&bgColor);
			if (obj_type == SIMPLE_MOVIE)
				bCambiazo = pajarraco.play();
            if (obj_type == HIERBAJOS)
                hierbajos.capture(&color, &bgColor);
				
        }
	}

	nuvols.update();
	papallones.update();
	boles.update();
    massives.update();
    paperets.update();
//	movies.update();
	
	pajarraco.update();
    hierbajos.update();

#ifdef _USE_KINECT
	kinSkel.update();
	enanito.update( kinSkel.getSkeleton(), kinSkel.getPixelsImage(), kinSkel.getPixelsUsers());
	animata.update();
	//	kameame();
	#endif

	boxes.update();
//	animals.update();
//	animatasXML.update();

	box2d.update();


/*	if (bMar)
		inunda();

	#ifdef _USE_KINECT
//	bocata.setPosition(enanito.headPos());
	#endif
	
//	marabunta_animal();
*/

}

//--------------------------------------------------------------
void testApp::draw(){
    
// ------ VPAINT ---------------------
    vpaint.draw(100,100);

	ofSetColor(255,255,255);
// ------ PINTA PANTALLA PRAL (AMB TRUCOS) ---------------------
	if(bCambiazo)
        bgColor.draw(0,0);
    else
        color.draw(0,0);

	fons.draw();
    nuvols.draw(bShowLines);
    paperets.draw(bShowLines);
    papallones.draw(bShowLines);
	plataformes.draw(bShowLines);
	boles.draw(bShowLines);
//	movies.draw();
	pajarraco.draw(bShowLines);
    
//    publicFbo.begin();
    ofSetColor(124,108,29);
    hierbajos.draw(0,0);
    ofSetColor(255, 255, 255);
//    publicFbo.end();
    
//    publicFbo.draw(0,0);

	#ifdef _USE_KINECT
	animata.draw(bShowLines);
	enanito.draw(bShowLines);
	#endif

//	animals.draw(bShowLines);
//	animatasXML.draw(bShowLines);
    massives.draw(bShowLines);

	//	kinSkel.draw();

    if(bFixShapes && !bCambiazo)
	   tactils.draw(bShowLines);

	#ifdef _USE_KINECT
//	bocata.draw();
	#endif

	boxes.draw();

	if(bMar)
	   mar.draw(bShowLines);

	if(bMa && !bCambiazo && !bMar)
	   ma.draw(bShowLines);

	blobInspector.draw(bShowLines);

	if(mouseX>2 && mouseX < vw-2 && mouseY > 2 && mouseY < vh-2)
	{
		ofPushMatrix();
			ofEnableAlphaBlending();
			ofSetColor(255,255,255,150);
            deu.setAnchorPercent(0.5, 0.5);
			deu.draw(mouseX, mouseY);
			ofDisableAlphaBlending();
		ofPopMatrix();
	}
    
    // cortina
//    ofSetColor(0, 0, 0, curtainAlpha);
//    ofEnableAlphaBlending();
//    ofRect(0, 0, WIDTH, HEIGHT);
//    ofDisableAlphaBlending();
    
    drawInfo();
    
    // BG IMAGE
    ofSetHexColor(0xffffff);
    ofNoFill();
    ofRect(OFF_MENU, ofGetHeight()-HEIGHT/4-20, WIDTH/4, HEIGHT/4);
    ofFill();
    bgColor.draw(OFF_MENU, ofGetHeight()-HEIGHT/4-20, WIDTH/4, HEIGHT/4);
	ofSetColor(255, 255, 0);
    ////////


// ------ PINTA PANTALLA 2a (PEL PUBLIC) ---------------------
	ofSetColor(255,255,255);

	if(bCambiazo)
        bgColor.draw(OFF_SCREEN,0);
    else
        color.draw(OFF_SCREEN,0);

	fons.draw(OFF_SCREEN);
    nuvols.draw(false, OFF_SCREEN);
    paperets.draw(false, OFF_SCREEN);
    papallones.draw(OFF_SCREEN);
	plataformes.draw(false, OFF_SCREEN);
	boles.draw(false, OFF_SCREEN);
	pajarraco.draw(false, OFF_SCREEN);
    
    ofSetColor(124,108,29);
    hierbajos.draw(OFF_SCREEN,0);
    ofSetColor(255, 255, 255);
	

	#ifdef _USE_KINECT
//	enanito.draw(false, OFF_SCREEN);
	#endif

    massives.draw(false, OFF_SCREEN);

	#ifdef _USE_KINECT
	bocata.draw(false, OFF_SCREEN);
	#endif

	boxes.draw(OFF_SCREEN);

	if(bMar)
	   mar.draw(false, OFF_SCREEN);

	if(bMa && !bCambiazo && !bMar)
	   ma.draw(OFF_SCREEN);

	if(mouseX>2 && mouseX < vw-2 && mouseY > 2 && mouseY < vh-2)
	{
		ofPushMatrix();
			ofEnableAlphaBlending();
			ofSetColor(255,255,255,150);
            deu.setAnchorPercent(0.5, 0.5);
			deu.draw(mouseX+OFF_SCREEN, mouseY);
			ofDisableAlphaBlending();
		ofPopMatrix();
	}
    
    // cortina
    ofSetColor(0, 0, 0, curtainAlpha);
    ofEnableAlphaBlending();
    ofRect(OFF_SCREEN, 0, WIDTH, HEIGHT);
    ofDisableAlphaBlending();
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
	if(key == 'c') {
		clear();
	}
//	if(key == 'h') {
//		#ifdef _USE_KINECT
//		enanito.setFloor();
//		enanito.setPosition(100,9);
//		#endif
//	}

	if(key == 'q') {
		   obj_type = BOX;
           bTakeB2DShot = true;
	}
    
    box2d.setGravity(0,10);

	switch (key){
		case ' ':
			bLearnBakground = true;
			bBeforeFirstSpace = false;
			break;
		case 'k':
			bFixShapes = !bFixShapes;
			break;
		case 'm':
			bMa = !bMa;
			break;
		case 'a':
			bMar = !bMar;
			break;
		case 'l':
			bShowLines = !bShowLines;
			break;
		case 'n':
			   obj_type = NUVOL;
               bTakeB2DShot = true;
			break;
		case 'b':
			   obj_type = BOLA;
               bTakeB2DShot = true;
			break;
		case 'd':
			   obj_type = MASSIVE;
               bTakeB2DShot = true;
			break;
		case 's':
			   obj_type = PAPERET;
               bTakeB2DShot = true;
			break;
		case 'v':
			   obj_type = BOCATA;
               if (bBocata)
			   {
				   bBocata = false;
//				   bocata.clear();
			   }else 
                    bTakeB2DShot = true;
			break;
		case 'p':
			   obj_type = PEIX;
               bTakeB2DShot = true;
			break;
		case 't':
			   obj_type = PLATAFORMA;
               bTakeB2DShot = true;
			break;
		case 'f':
			   obj_type = FONS;
               bTakeB2DShot = true;
			break;
		case 'o':
			   obj_type = PAPALLONA;
               bTakeB2DShot = true;
			break;
		case 'r':
			isRaining = !isRaining;

			if (isRaining)
			{
				nuvols.startRain();
			}else
			{
				nuvols.stopRain();
			}
			break;
		case 'x':
			   obj_type = ANIMATA;
               bTakeB2DShot = true;
			break;
		case '0':
			break;
		case 'e':
			   obj_type = ANIMAL;
			   actual_movie = 1;
               bTakeB2DShot = true;
			break;
		case 'g':
            box2d.setGravity(ofSign(ofRandom(-1,1))*3, -10);
			obj_type = SIMPLE_MOVIE;
			bTakeB2DShot = true;
			break;
        case 'h':
            box2d.setGravity(ofSign(ofRandom(-1,1))*3, -10);
            obj_type = HIERBAJOS;
            bTakeB2DShot = true;
            break;
		case '1':
			   obj_type = ANIMATAXML;
			   actual_movie = 1;
               bTakeB2DShot = true;
			break;
		case '2':
			   obj_type = ANIMATAXML;
			   actual_movie = 1;
               bTakeB2DShot = true;
			break;
		case '3':
			   obj_type = ANIMATAXML;
			   actual_movie = 1;
               bTakeB2DShot = true;
			break;
	}
		// gray threshold
	if(key == OF_KEY_UP) {
		threshold ++;
		if(threshold > 255) threshold = 255;

		tactils.setThreshold(threshold);
		nuvols.setThreshold(threshold);
		papallones.setThreshold(threshold);
		boles.setThreshold(threshold);
		massives.setThreshold(threshold);
		paperets.setThreshold(threshold);
        plataformes.setThreshold(threshold);
//		animals.setThreshold(threshold);
//		animatasXML.setThreshold(threshold);
		blobInspector.setThreshold(threshold);
//		movies.setThreshold(threshold); // oju. Té un threshold2 de 90 per pillar el blob intern (peix)
	}
	if(key == OF_KEY_DOWN) {
		threshold --;
		if(threshold < 0) threshold = 0;

		tactils.setThreshold(threshold);
		nuvols.setThreshold(threshold);
		papallones.setThreshold(threshold);
		boles.setThreshold(threshold);
		massives.setThreshold(threshold);
		paperets.setThreshold(threshold);
        plataformes.setThreshold(threshold);
//		animals.setThreshold(threshold);
//		animatasXML.setThreshold(threshold);
		blobInspector.setThreshold(threshold);
//		movies.setThreshold(threshold); // oju. Té un threshold2 de 90 per pillar el blob intern (peix)
	}
	if(key == OF_KEY_LEFT) {
		#ifdef _USE_KINECT
		enano_scale --;
		if(enano_scale < 1) enano_scale = 1;
		enanito.setScale(enano_scale*0.25);
		enanito.setContourAmount((int)25. / enano_scale);
		enanito.setPosition(vw/2, vh-50);
		#endif
	}
	if(key == OF_KEY_RIGHT) {
		#ifdef _USE_KINECT
		enano_scale ++;
		if(enano_scale > 4) enano_scale = 4;
		enanito.setScale(enano_scale*0.25);
		enanito.setContourAmount((int)25. / enano_scale);
		enanito.setPosition(vw/2, vh-50);
		#endif
	}
	if(key == OF_KEY_BACKSPACE) 
        bCambiazo = false;

}


//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    hierbajos.mouseMoved(x,y);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

	touch(x,y);
		// amb el mouse
	pajarraco.drag(x,y);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

	pajarraco.dragOff();
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::clear(){

    nuvols.clear();
	fons.clear();
	papallones.clear();
	massives.clear();
	paperets.clear();
	plataformes.clear();
	boxes.clear();
	boles.clear();
    hierbajos.clear();
    
    
	box2d.init();
	box2d.setGravity(0, 10);
	box2d.createFloor();
	box2d.checkBounds(true);
	box2d.setFPS(15.0);
}


void testApp::touch(int x, int y)
{

	nuvols.drag(x,y);
	massives.touch(x,y);
	paperets.touch(x,y,100);
	boles.drag(x,y);
		
	#ifdef _USE_KINECT
//	if(enanito.istouched(x,y))
//		enanito.setPosition(x,y);
	#endif

}

void testApp::inunda()
{
/*	int nivellmar;
	ofPoint pos;

	for(int i=0; i<nuvols; i++) {
		for(int j=0; j<nuvols[i].getNumberSkins(); j++) {
			pos = nuvols[i].getPosition(j);
			nivellmar = mar.getNivell(pos);
			if(pos.y > nivellmar)
				nuvols[i].setPosition(j,pos.x,nivellmar);
		}
	}
	for (int i = 0; i < numMassives; i++)
	{
	}
	for(int i=0; i<num_boles; i++) {
		boles[i].stop();
		for(int j=0; j<boles[i].getNumberSkins(); j++) {
			pos = boles[i].getPosition(j);
			nivellmar = mar.getNivell(pos);
			if(pos.y > nivellmar)
				boles[i].setPosition(j,pos.x,nivellmar);
			else
				if(pos.y < vh-25)
					boles[i].setPosition(j,pos.x,pos.y+25);
		}
	}

	#ifdef _USE_KINECT
	pos = enanito.getPosition();
	nivellmar = mar.getNivell(pos);
	if(pos.y > nivellmar)
		enanito.setPosition(pos.x,nivellmar);
	#endif
	
	for(int i=0; i<boxes.boxes.size(); i++) {
		pos = boxes.boxes[i].getPosition();
		nivellmar = mar.getNivell(pos);
		if(pos.y > nivellmar)
			boxes.boxes[i].setPosition(pos.x,nivellmar);
	}
*/
/*	for(int i=0; i<num_peixos; i++) 
	{
		pos = moviemonsters[i].getPosition();
		nivellmar = mar.getNivell(pos);
		if(pos.y > nivellmar)
			moviemonsters[i].setPosition(pos.x,nivellmar);
	}*/

}
void testApp::kameame()
{
/*	#ifdef _USE_KINECT
	ofPoint p;
	
	p = enanito.isKameame();

	if(p.x != -1)
	{
		nuvols.touch(p.x,p.y);
		massives.touch(p.x,p.y,500, 100);
		paperets.touch(p.x,p.y,100);
		boles.touch(p.x,p.y);
//		boxes.touch(p.x,p.y,100);
	}
	#endif
	*/
}

void testApp::marabunta_animal()
{
}

void testApp::mapMidiInput(){
    cout << nanoId << ": " << nanoValue << endl;
    
    switch (nanoId) {
        case SLIDER_1:
            curtainAlpha = ofMap(nanoValue, 0, 127, 0, 255);
            break;
        case KNOB_1:
            threshold = ofMap(nanoValue, 0, 127, 0, 255);
            setThreshold();
            break;
        case UPPER_BUTTON_1:
            if(nanoValue > 0) bShowLines = !bShowLines;
            break;
        case LOWER_BUTTON_1:
            if(nanoValue > 0) keyPressed(' ');
            break;
        case UPPER_BUTTON_2:
            if(nanoValue > 0) keyPressed('h');
            break;
        case LOWER_BUTTON_2:
            if(nanoValue > 0) keyPressed('c');
            break;
        case UPPER_BUTTON_3:
            if(nanoValue > 0) keyPressed('g');
            break;
        case LOWER_BUTTON_3:
            break;
            
        default:
            break;
    }
}

void testApp::drawInfo(){
    
    
	ofSetColor(255, 255, 0);
	string info = "threshold: "+ofToString(threshold);
	ofDrawBitmapString(info, OFF_MENU, 20);
    
	info = "N-Nuvol";
	ofDrawBitmapString(info, OFF_MENU, 30);
    
	info = "B-Boles";
	ofDrawBitmapString(info, OFF_MENU, 40);
    
	info = "D-Densos";
	ofDrawBitmapString(info, OFF_MENU, 50);
    
	info = "S-Softs";
	ofDrawBitmapString(info, OFF_MENU, 60);
    
	info = "V-Vocata";
	ofDrawBitmapString(info, OFF_MENU, 70);
    
	info = "P-PeixMovie";
	ofDrawBitmapString(info, OFF_MENU, 80);
    
	info = "T-Plataforma";
	ofDrawBitmapString(info, OFF_MENU, 90);
    
	info = "F-Fons";
	ofDrawBitmapString(info, OFF_MENU, 100);
    
	info = "O-Ocells";
	ofDrawBitmapString(info, OFF_MENU, 110);
    
	info = "Q-God boxes";
	ofDrawBitmapString(info, OFF_MENU, 120);
    
	info = "M-MA";
	ofDrawBitmapString(info, OFF_MENU, 140);
	if(bMa)
		ofCircle(OFF_MENU-10, 138, 5);
    
	info = "K-SOLID SHAPE";
	ofDrawBitmapString(info, OFF_MENU, 150);
	if(bFixShapes && !bTakeB2DShot && !bCambiazo)
		ofCircle(OFF_MENU-10, 148, 5);
    
	info = "A-MAR(aigua)";
	ofDrawBitmapString(info, OFF_MENU, 160);
	if(bMar)
		ofCircle(OFF_MENU-10, 158, 5);
    
	info = "E-animalXML";
	ofDrawBitmapString(info, OFF_MENU, 170);
    
	info = "1-animataXML";
	ofDrawBitmapString(info, OFF_MENU, 180);
    
	info = "X-animataKinect";
	ofDrawBitmapString(info, OFF_MENU, 190);
    
	info = "FPS: "+ofToString(ofGetFrameRate());
	ofDrawBitmapString(info, OFF_MENU, 210);
    
	info = "G-pajarraco";
	ofDrawBitmapString(info, OFF_MENU, 190);
    
	info = "H-hierbajos";
	ofDrawBitmapString(info, OFF_MENU, 190);
    
    
	if(bCambiazo)
	{
		info = "treu els bixos i fes";
		ofDrawBitmapString(info, 310, 230);
		info = "----- BACKSPACE -----";
		ofDrawBitmapString(info, 310, 240);
	}
    
	if(bBeforeFirstSpace)
	{
		info = "Abans de res, apreta";
		ofDrawBitmapString(info, 310, 230);
		info = "----- SPACE !! -----";
		ofDrawBitmapString(info, 310, 240);
	}
}

void testApp::setThreshold(){
    
    tactils.setThreshold(threshold);
    nuvols.setThreshold(threshold);
    papallones.setThreshold(threshold);
    boles.setThreshold(threshold);
    massives.setThreshold(threshold);
    paperets.setThreshold(threshold);
    plataformes.setThreshold(threshold);
    //		animals.setThreshold(threshold);
    //		animatasXML.setThreshold(threshold);
    blobInspector.setThreshold(threshold);
    //		movies.setThreshold(threshold); // oju. Té un threshold2 de 90 per pillar el blob intern (peix)
}

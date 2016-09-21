#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofBackground(50);
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    
    img[0].load("quad_warp_kittens.png");
    img[1].load("Arduino.png");
    img[2].load("oF.png");
    
    //一旦削除
    /*
    for(int i = 0 ; i <3 ;i++){
    x[i] = (ofGetWidth() - img[i].getWidth()) * 0.5 + i*10;       // center on screen.
    y[i] = (ofGetHeight() - img[i].getHeight()) * 0.5 + i*10;     // center on screen.
    w[i] = img[i].getWidth();
    h[i] = img[i].getHeight();
    fbo[i].allocate(w[i], h[i]);//wとhをFBOに書き出し
    }

    for(int i = 0 ; i <3 ;i++){
        warper[i].setSourceRect(ofRectangle(0, 0, w[i], h[i]));              // this is the source rectangle which is the size of the image and located at ( 0, 0 )
        warper[i].setTopLeftCornerPosition(ofPoint(x[i], y[i]));             // this is position of the quad warp corners, centering the image on the screen.
        warper[i].setTopRightCornerPosition(ofPoint(x[i] + w[i], y[i]));        // this is position of the quad warp corners, centering the image on the screen.
        warper[i].setBottomLeftCornerPosition(ofPoint(x[i], y[i] + h[i]));      // this is position of the quad warp corners, centering the image on the screen.
        warper[i].setBottomRightCornerPosition(ofPoint(x[i] + w[i], y[i] + h[i])); // this is position of the quad warp corners, centering the image on the screen.
        warper[i].setup();
        warper[i].load(); // reload last saved changes.
    }*/
    int x = 0;
    int y = 0;
    

    for (int i=0; i<NUM; i++) {
        w[i] = img[i].getWidth();
        h[i] = img[i].getHeight();
        fbo[i].allocate(w[i], h[i]);
        
        warper[i].setSourceRect( ofRectangle( 0, 0, w[i], h[i] ) );
        warper[i].setTopLeftCornerPosition( ofPoint( x, y ) );
        warper[i].setTopRightCornerPosition( ofPoint( x + w[i], y ) );
        warper[i].setBottomLeftCornerPosition( ofPoint( x, y + h[i] ) );
        warper[i].setBottomRightCornerPosition( ofPoint( x + w[i], y + h[i] ) );
        warper[i].setup();
        
        x+=100;
        y+=100;
    }
    

    
}

//--------------------------------------------------------------
void ofApp::update()
{
    if(ofGetFrameNum() % 5 != 0) {
        // only update every 5 frames.
        return;
    }
    
    
    for(int i=0; i<10; i++) {
        // randomise points over the image area.
      //  points[i].x[0] = ofRandom(img[0].getWidth());
       // points[i].y[0] = ofRandom(img[0].getHeight());
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofSetColor(ofColor::magenta);
    ofDrawCircle(0, 0, ofRandom(ofGetWidth()/2));
    
    ofSetColor(255);
    
    //======================== 画像を画角の中のDrawで指定した場所に描画
    for(int i = 0 ; i <NUM ;i++){
    fbo[i].begin();
    img[i].draw(10, 10); //コメント会うとすると画像は表示されない。
    fbo[i].end();
        cout << &fbo[i] <<endl;
    }
    
    //======================== get our quad warp matrix.
    ofMatrix4x4 mat[NUM];
    
    for(int i = 0 ; i <NUM ;i++){
        mat[i] = warper[i].getMatrix();
    }
    
    
    
    //======================== use the matrix to transform our fbo.
     for(int i = 0 ; i <NUM ;i++){
    ofPushMatrix();
    ofMultMatrix(mat[i]);
    fbo[i].draw(0, 0);
    ofPopMatrix();
     }
    
    //======================== ランダムの線が描画される場所(一旦コメントアウト)
    
    ofSetLineWidth(2);
    ofSetColor(ofColor::cyan);
    
    //ノイズ部分は一旦消去
    /*for(int i=0; i<9; i++) {
        int j = i + 1;
        
        ofVec3f p1 = mat.preMult(ofVec3f(points[i].x, points[i].y, 0));
        ofVec3f p2 = mat.preMult(ofVec3f(points[j].x, points[j].y, 0));
        
        ofDrawLine(p1.x, p1.y, p2.x, p2.y);
    }*/
    
    //======================== UI部分の実装
    for(int i = 0 ; i <NUM ;i++){
        ofSetColor(ofColor::magenta);
        warper[i].drawQuadOutline();
        
        
        ofSetColor(ofColor::yellow);
        warper[i].drawCorners();
        
        ofSetColor(ofColor::magenta);
        warper[i].drawHighlightedCorner();
        
        ofSetColor(ofColor::red);
        warper[i].drawSelectedCorner();
    }
    
    //======================== info.
    
    ofSetColor(ofColor::white);
    ofDrawBitmapString("to warp the image, drag the corners of the image.", 20, 30);
    ofDrawBitmapString("press 's' to toggle quad warp UI. this will also disable quad warp interaction.", 20, 50);
    ofDrawBitmapString("press & hold 1, 2, 3, 4 to snap that point to the mouse", 20, 70);
    ofDrawBitmapString("when a corner is selected (red), use keyboard arrow keys to nudge the corner position.", 20, 90);
}

void ofApp::exit() {
    for(int i = 0 ; i <NUM ;i++){
    warper[i].save();
    }
}

//------------------------------------------各キーの割り当て
void ofApp::keyPressed(int key) {
    
    if(key == 's' || key == 'S') {
        for(int i = 0 ; i <NUM ;i++){
        warper[i].toggleShow();
        }
        
    }

    
    
    if(key == 'l' || key == 'L') {
        for(int i = 0 ; i <NUM ;i++){
        warper[i].load();
        }
    }
    
    if(key == 'h' || key == 'H') {
        for(int i = 0 ; i <NUM ;i++){
        warper[i].save();
        }

    }
    
    //以下指定した領域の画像を抜き出してFBOに入れて~みたな事をしようとしていた。
    
    if(key == 'z' || key == 'Z') {
        img_.grabScreen(0, 0 , ofGetWidth(), ofGetHeight());
        image.push_back(img_);
        
        ofxQuadWarp kariWarper;
        warper_.push_back(kariWarper);
        
        ofFbo kariFbo;
        fbo_.push_back(kariFbo);
        
        int w_ = image[0].getWidth();
        int h_ = image[0].getHeight();
        fbo_[0].allocate(w_, h_);
        
        warper_[0].setSourceRect( ofRectangle( 0, 0, w_, h_ ) );
        warper_[0].setTopLeftCornerPosition( ofPoint( x, y ) );
        warper_[0].setTopRightCornerPosition( ofPoint( x + w_, y ) );
        warper_[0].setBottomLeftCornerPosition( ofPoint( x, y + h_ ) );
        warper_[0].setBottomRightCornerPosition( ofPoint( x + w_, y + h_ ) );
        warper_[0].setup();
        
        fbo_[0].begin();
        image[0].draw(10, 10);
        fbo_[0].end();
        
        ofMatrix4x4 mat_;
        
       
        mat_ = warper_[0].getMatrix();
        
        ofPushMatrix();
        ofMultMatrix(mat_);
        fbo_[0].draw(0, 0);
        ofPopMatrix();
        
        
        
        ofSetColor(ofColor::magenta);
        warper_[0].drawQuadOutline();
        
        
        ofSetColor(ofColor::yellow);
        warper_[0].drawCorners();
        
        ofSetColor(ofColor::magenta);
        warper_[0].drawHighlightedCorner();
        
        ofSetColor(ofColor::red);
        warper_[0].drawSelectedCorner();

 
        
    }
}

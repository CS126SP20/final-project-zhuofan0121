// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <rph/NotificationManager.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "cinder/gl/Texture.h"
#include "cinder/Surface.h"
#include "cinder/ImageIo.h"
#include "cinder/ip/EdgeDetect.h"
#include "cinder/ip/Grayscale.h"

#include "cinder/params/Params.h"
#include "cinder/gl/gl.h"
#include "cinder/app/RendererGl.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

//#include "CinderOpenCV.h"

namespace myapp {

using cinder::app::KeyEvent;

/*
using cinder::Surface32f;
using cinder::vec2;
cinder::params::InterfaceGl mParams;
float mContrast, mContrastOld;
float mBrightness, mBrightnessOld;
Surface32f mImage, mImageOutput;
*/

cv::VideoCapture cap(0);
cv::Mat edges;

MyApp::MyApp() { }

void MyApp::setup() {

  /*
  rph::NotificationManager::getInstance()->add("Hello, World!", 10);

  mImage = loadImage(loadAsset("image.png"));
  mImageOutput = cinder::Surface32f(mImage.getWidth(), mImage.getHeight(), false);

  mContrast = 0.f;
  mContrastOld = -1.f;
  mBrightness = 0.f;
  mBrightnessOld = -1.f;

  mParams.addParam("Contrast", &mContrast, "min=-0.5 max=1.0 step=0.01");
  mParams.addParam("Brightness", &mBrightness, "min=-0.5 max=0.5 step=0.01");

//  cinder::gl::Texture texture = cinder::loadImage( "image.jpg" );
   */
  //cap.open(0);
  cv::namedWindow("edges",1);

//  auto size = this->getWindowSize();
//  fCaptureDev = Capture::create(size.x, size.y);
//  fCaptureDev->start();

}

void MyApp::update() {

  /*
  if (mContrastOld != mContrast || mBrightnessOld != mBrightness) {
    float c = 1.f + mContrast;
//    Surface32f::IterpixelIter = mImage.getIter();
//    Surface32f::IterpixelOutIter = mImageOutput.getIter();
  }
   */

  cv::Mat frame;
  cap >> frame; // get a new frame from camera
  cv::cvtColor(frame, edges, cv::COLOR_BGR2GRAY);
  cv::GaussianBlur(edges, edges, cv::Size(7,7), 1.5, 1.5);
  cv::Canny(edges, edges, 0, 30, 3);

}

void MyApp::draw() {
  cinder::gl::clear();

  /*
  rph::NotificationManager::getInstance()->draw();

  vec2 center = getWindowCenter();
  float r = 100;
  ci::gl::color( ci::Color( 1, 0, 0 ) ); // red
  ci::gl::drawSolidCircle( center + vec2( -r, r ), r );
  ci::gl::color( ci::Color( 0, 1, 0 ) ); // green
  ci::gl::drawSolidCircle( center + vec2( r, r ), r );
  ci::gl::color( ci::Color( 0, 0, 1 ) ); // blue
  ci::gl::drawSolidCircle( center + vec2( 0, -0.73 * r ), r );
   */

  imshow("edges", edges);
  //cv::imread("test-photo.jpg", 1);


}

void MyApp::keyDown(KeyEvent event) {
  if( event.getChar() == 'f' ) {
    // Toggle full screen when the user presses the 'f' key.
    setFullScreen( ! isFullScreen() );
  }
  if (event.getCode() == KeyEvent::KEY_ESCAPE) {
    if( isFullScreen() )
      setFullScreen( false );
    else
      quit();
  }
}

}  // namespace myapp

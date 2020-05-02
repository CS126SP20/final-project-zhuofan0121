// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <rph/NotificationManager.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "cinder/gl/gl.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>

#include <vector>
#include <string>

namespace myapp {

using cinder::app::KeyEvent;
using std::vector;

cv::VideoCapture capture(0);
//cv::Mat edges;

cv::CascadeClassifier mFaceDetector;
cv::CascadeClassifier mEyeDetector;
cv::CascadeClassifier mMouthDetector;
cv::CascadeClassifier mNoseDetector;

float scaleFactor = 3.0f;
cv::Mat image;

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
  //cv::namedWindow("edges",1);
  cv::namedWindow("Extracted Frame");

  /*
  if (mFaceDetector.empty())
    mFaceDetector.load("/usr/local/Cellar/opencv/4.3.0/share/opencv4"
                       "/haarcascades/haarcascade_frontalface_default.xml");
  if (mEyeDetector.empty())
    mEyeDetector.load("/Users/jiazhuofan/CLionProjects/cinder_0.9.2_mac"
                      "/blocks/opencv_contrib/modules/face/data/cascades/haarcascade_mcs_eyepair_big.xml");
  if (mNoseDetector.empty())
    mEyeDetector.load("/Users/jiazhuofan/CLionProjects/cinder_0.9.2_mac"
                      "/blocks/opencv_contrib/modules/face/data/cascades/haarcascade_mcs_nose.xml");
  if (mMouthDetector.empty())
    mMouthDetector.load("/Users/jiazhuofan/CLionProjects/cinder_0.9.2_mac"
                        "/blocks/opencv_contrib/modules/face/data/cascades/haarcascade_mcs_mouth.xml");
                        */

  mFaceDetector.load("/usr/local/Cellar/opencv/4.3.0/share/opencv4"
                     "/haarcascades/haarcascade_frontalface_default.xml");
  mEyeDetector.load("/Users/jiazhuofan/CLionProjects/cinder_0.9.2_mac"
                    "/blocks/opencv_contrib/modules/face/data/cascades/haarcascade_mcs_eyepair_big.xml");
  mEyeDetector.load("/Users/jiazhuofan/CLionProjects/cinder_0.9.2_mac"
                    "/blocks/opencv_contrib/modules/face/data/cascades/haarcascade_mcs_nose.xml");
  mMouthDetector.load("/Users/jiazhuofan/CLionProjects/cinder_0.9.2_mac"
                      "/blocks/opencv_contrib/modules/face/data/cascades/haarcascade_mcs_mouth.xml");


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
  capture >> frame;
  cv::Mat mElabImage;
  frame.copyTo(mElabImage);

  // detect face
  vector<cv::Rect> faceVec;
  mFaceDetector.detectMultiScale(frame, faceVec, scaleFactor);
  int i, j;
  for (i = 0; i < faceVec.size(); i++) {
    cv::rectangle(mElabImage, faceVec[i], CV_RGB(255,0,0), 2);
    cv::Mat face = frame(faceVec[i]);

    // detect eyes
    vector<cv::Rect> eyeVec;
    mEyeDetector.detectMultiScale(face, eyeVec);

    for (j = 0; j < eyeVec.size(); j++) {
      cv::Rect rect = eyeVec[j];
      rect.x += faceVec[i].x;
      rect.y += faceVec[i].y;

      cv::rectangle(mElabImage, rect, CV_RGB(0,255,0), 2);
    }

    // detect nose
    vector<cv::Rect> noseVec;
    mNoseDetector.detectMultiScale(face, noseVec, 3);

    for (j = 0; j < noseVec.size(); j++) {
      cv::Rect rect = noseVec[j];
      rect.x += faceVec[i].x;
      rect.y += faceVec[i].y;

      cv::rectangle(mElabImage, rect, CV_RGB(0,0,255), 2);
    }

    // detect mouth
    vector<cv::Rect> mouthVec;
    cv::Rect halfRect = faceVec[i];
    halfRect.height /= 2;
    halfRect.y += halfRect.height;

    cv::Mat halfFace = frame(halfRect);
    mMouthDetector.detectMultiScale(halfFace, mouthVec, 3);

    for (j = 0; j < mouthVec.size(); j++) {
      cv::Rect rect = mouthVec[j];
      rect.x += halfRect.x;
      rect.y += halfRect.y;

      cv::rectangle(mElabImage, rect, CV_RGB(255,255,255), 2);
    }
  }
  mElabImage.copyTo(image);
  //cv::imshow("Extracted Frame", image);

  /*
  cap >> frame; // get a new frame from camera
  cv::cvtColor(frame, edges, cv::COLOR_BGR2GRAY);
  cv::GaussianBlur(edges, edges, cv::Size(7,7), 1.5, 1.5);
  cv::Canny(edges, edges, 0, 30, 3);
   */

}

void MyApp::draw() {
  cinder::gl::clear();
  cv::imshow("Extracted Frame", image);

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

  //imshow("edges", edges);


}

void MyApp::keyDown(KeyEvent event) {
  if(event.getChar() == 'f') {
    // Toggle full screen when the user presses the 'f' key.
    setFullScreen(! isFullScreen());
  }
  if (event.getCode() == KeyEvent::KEY_ESCAPE) {
    if(isFullScreen())
      setFullScreen(false);
    else
      quit();
  }
}

}  // namespace myapp

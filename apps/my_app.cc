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

#include "CinderOpenCV.h"
#include "cinder/gl/Texture.h"
#include "cinder/Capture.h"

#include "cinder/Surface.h"
#include "cinder/ImageIo.h"

namespace myapp {

using cinder::app::KeyEvent;
using std::vector;

cv::VideoCapture cap(0);
cv::Mat edges;

cv::CascadeClassifier mFaceDetector;
cv::CascadeClassifier mEyeDetector;
cv::CascadeClassifier mMouthDetector;
cv::CascadeClassifier mNoseDetector;

float scaleFactor = 3.0f;
cv::Mat image;

cinder::Surface8u mImage;
cv::CascadeClassifier  mFaceCC;
vector<ci::Rectf>  mFaces;

cinder::gl::Texture2dRef mTex;

cinder::CaptureRef fCaptureDev;
cinder::gl::TextureRef fGlFrame;
vector<cv::Rect> faces;

MyApp::MyApp() { }

void MyApp::setup() {
  mFaces.clear();
  faces.clear();

  /*
  rph::NotificationManager::getInstance()->add("Hello, World!", 10);
   */
  //cap.open(0);
  //cv::namedWindow("edges",1);
  //cv::namedWindow("Extracted Frame");

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


//  mImage = loadImage(loadAsset("test-faces.jpg"));
  mFaceCC.load(getAssetPath("haarcascade_frontalface_alt.xml").string());
//
//  cv::Mat cvImage(toOcv(mImage, CV_8UC1));
//  std::vector<cv::Rect> faces;
//  mFaceCC.detectMultiScale(cvImage, faces);
//  std::vector<cv::Rect>::const_iterator faceIter;
//  for (faceIter = faces.begin(); faceIter != faces.end(); ++faceIter) {
//    ci::Rectf faceRect(cinder::fromOcv(*faceIter));
//    mFaces.push_back(faceRect);
//  }
//  mTex = cinder::gl::Texture2d::create(mImage);

  auto size = this->getWindowSize();
  fCaptureDev = cinder::Capture::create(size[0], size[1]);
  fCaptureDev->start();
  fGlFrame = cinder::gl::Texture::create(size.x, size.y);
}

void MyApp::update() {
  if (fCaptureDev->checkNewFrame()) {
    // Capture the current frame.
    const cinder::Surface8uRef rgbFrame = fCaptureDev->getSurface();

    // Convert rgb -> gray -> cv::Mat
    cv::Mat ocvGrayImage = toOcv(cinder::Channel(*rgbFrame));
    mFaceCC.detectMultiScale(ocvGrayImage, faces);

    std::vector<cv::Rect>::const_iterator faceIter;
    for (faceIter = faces.begin(); faceIter != faces.end(); ++faceIter) {
      ci::Rectf faceRect(cinder::fromOcv(*faceIter));
      mFaces.push_back(faceRect);
    }

    // Get the frame in a format OpenGL can draw, i.e. load it to GPU.
    fGlFrame->update(*rgbFrame);
  }
  /*
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
   */

//  cv::Mat frame;
//  cap >> frame; // get a new frame from camera
//  cv::cvtColor(frame, edges, cv::COLOR_BGR2GRAY);
//  cv::GaussianBlur(edges, edges, cv::Size(7,7), 1.5, 1.5);
//  cv::Canny(edges, edges, 0, 30, 3);
}

void MyApp::draw() {
  cinder::gl::clear();
  cinder::gl::color(1, 1, 1);
  cinder::gl::draw(fGlFrame);

  //cv::imshow("Extracted Frame", image);

  /*
  rph::NotificationManager::getInstance()->draw();
   */
//  imshow("edges", edges);
//
//  cinder::gl::color(cinder::Color::white());
//  cinder::gl::draw(mTex);
  cinder::gl::color(cinder::ColorA(1.f, 0.f, 0.f, 0.45f));
  std::vector<ci::Rectf>::const_iterator faceIter;
  for (faceIter = mFaces.begin(); faceIter != mFaces.end(); ++faceIter) {
    cinder::gl::drawStrokedRect(*faceIter, 3);
  }

  mFaces.clear();
  faces.clear();
}

void MyApp::keyDown(KeyEvent event) {
  // Toggle full screen when the user presses the 'f' key.
  if (event.getChar() == 'f') {
    setFullScreen(!isFullScreen());
  }

  // Quit full screen or quit app when the user presses the 'esc' key.
  if (event.getCode() == KeyEvent::KEY_ESCAPE) {
    if (isFullScreen()) {
      setFullScreen(false);
    } else {
      quit();
    }
  }
}

}  // namespace myapp

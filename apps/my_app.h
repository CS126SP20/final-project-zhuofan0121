// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>

#include "cinder/Capture.h"

//#include "cinder/params/Params.h"

namespace myapp {

using cv::Mat;

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;

 private:
  cv::VideoCapture cap;

  Mat mask;
  Mat frame, frameGray;
  Mat frameROI, faceMaskSmall;
  Mat grayMaskSmall, grayMaskSmallThresh, grayMaskSmallThreshInv;
  Mat maskedFace, maskedFrame;

  Mat edges;

  cv::CascadeClassifier mFaceDetector;
  cv::CascadeClassifier mEyeDetector;
  cv::CascadeClassifier mMouthDetector;
  cv::CascadeClassifier mNoseDetector;

  cv::Mat image;

  cinder::Surface8u mImage;
  // cv::CascadeClassifier mFaceCC;

  // cinder::params::InterfaceGl mParams;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_

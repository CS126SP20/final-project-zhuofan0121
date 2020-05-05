// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>

#include "cinder/Capture.h"

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
  cv::CascadeClassifier mFaceDetector;
  std::vector<cv::Rect> faces;
  Mat mask;
  Mat frame, frameGray;
  Mat frameROI, faceMaskSmall;
  Mat grayMaskSmall, grayMaskSmallThresh, grayMaskSmallThreshInv;
  Mat maskedFace, maskedFrame;
  Mat edges;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_

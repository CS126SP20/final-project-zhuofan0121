// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>

#include "cinder/gl/Texture.h"
#include "cinder/gl/gl.h"

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
  cv::CascadeClassifier face_detector;
  std::vector<cv::Rect> faces;
  Mat mask;
  Mat frame, frame_gray;
  Mat frame_roi, face_mask_small;
  Mat gray_mask_small, gray_mask_small_thresh, gray_mask_small_thresh_inv;
  Mat masked_face, masked_frame;
  Mat edges;
  cinder::Surface image_output;
  cinder::gl::TextureRef tex_output;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_

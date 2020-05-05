// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <opencv2/imgproc/types_c.h>

#include <string>
#include <vector>

#include "CinderOpenCV.h"
#include "cinder/Surface.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/gl.h"

namespace myapp {

using cinder::app::KeyEvent;
using std::string;
using std::vector;

float scalingFactor = 0.75;

vector<string> mask_paths;
int mask_index;

bool draw_rect;
bool draw_mask;
bool start_mask = true;
bool start_edge;

MyApp::MyApp() {
  string t =
      "/Users/jiazhuofan/CLionProjects/cinder_0.9.2_mac/my-projects/"
      "final-project-zhuofan0121/assets/mask-images/";
  mask_paths = {
      t + "mask.jpg",        t + "mask-new.jpg",   t + "mask-new2.jpg",
      t + "mask-new3.jpg",   t + "mask-new4.jpg",  t + "mask-new5.jpg",
      t + "mask-new6.jpg",   t + "mask-new7.jpg",  t + "mask-new8.jpg",
      t + "mask-new9.jpg",   t + "mask-new10.jpg", t + "mask-new11.jpg",
      t + "mask-images.jpg", t + "mask-new13.jpeg"};
}

void MyApp::setup() {
  mFaceDetector.load(getAssetPath("haarcascade_frontalface_alt.xml").string());
  cap = cv::VideoCapture(0);
  if (!cap.isOpened()) {
    std::cerr << "Error opening camera. Exiting!" << std::endl;
    quit();
  }
  mask = cv::imread(mask_paths[11]);
  if (!mask.data) {
    std::cerr << "Error loading mask image. Exiting!" << std::endl;
  }
}

void MyApp::update() {
  cap >> frame;
  if (start_mask) {
    cv::resize(frame, frame, cv::Size(), scalingFactor, scalingFactor,
               cv::INTER_AREA);
    cvtColor(frame, frameGray, CV_BGR2GRAY);
    equalizeHist(frameGray, frameGray);
    mFaceDetector.detectMultiScale(frameGray, faces, 1.1, 2,
                                   0 | cv::CASCADE_SCALE_IMAGE,
                                   cv::Size(30, 30));
  }

  if (start_edge) {
    cv::cvtColor(frame, edges, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(edges, edges, cv::Size(7, 7), 1.5, 1.5);
    cv::Canny(edges, edges, 0, 30, 3);
  }
}

void MyApp::draw() {
  cinder::gl::clear();
  cinder::gl::color(1, 1, 1);

  if (start_mask) {
    for (int i = 0; i < faces.size(); i++) {
      if (draw_rect) {
        cv::Rect faceRect(faces[i].x, faces[i].y, faces[i].width,
                          faces[i].height);
        cv::rectangle(frame, faceRect, CV_RGB(0, 255, 0), 2);
      }
      if (draw_mask) {
        int x = faces[i].x + int(0.1 * faces[i].width);
        int y = faces[i].y + int(0.5 * faces[i].height);
        int w = int(0.8 * faces[i].width);
        int h = int(0.5 * faces[i].height);

        frameROI = frame(cv::Rect(x, y, w, h));
        cv::resize(mask, faceMaskSmall, cv::Size(w, h));
        cvtColor(faceMaskSmall, grayMaskSmall, CV_BGR2GRAY);
        threshold(grayMaskSmall, grayMaskSmallThresh, 230, 255,
                  CV_THRESH_BINARY_INV);
        bitwise_not(grayMaskSmallThresh, grayMaskSmallThreshInv);
        bitwise_and(faceMaskSmall, faceMaskSmall, maskedFace,
                    grayMaskSmallThresh);
        bitwise_and(frameROI, frameROI, maskedFrame, grayMaskSmallThreshInv);
        add(maskedFace, maskedFrame, frame(cv::Rect(x, y, w, h)));
      }
    }

    cinder::Surface mImageOutput = cinder::Surface(cinder::fromOcv(frame));
    cinder::gl::TextureRef mTexOutput =
        cinder::gl::Texture2d::create(mImageOutput);
    cinder::gl::color(1, 1, 1);
    cinder::gl::draw(mTexOutput);
  }

  if (start_edge) {
    cinder::Surface mImageOutput = cinder::Surface(cinder::fromOcv(edges));
    cinder::gl::TextureRef mTexOutput =
        cinder::gl::Texture2d::create(mImageOutput);
    cinder::gl::draw(mTexOutput);
  }

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

  // Change to a different mask when the user presses the 'c' key.
  if (event.getChar() == 'c') {
    mask = cv::imread(mask_paths[mask_index]);
    if (!mask.data) {
      std::cerr << "Error loading mask image. Exiting!" << std::endl;
    }
    mask_index = (mask_index + 1) % (int)mask_paths.size();
  }

  // Toggle rectangle on face when the user presses the 'r' key.
  if (event.getChar() == 'r') {
    draw_rect = !draw_rect;
  }

  // Toggle mask when the user presses the 'm' key.
  if (event.getChar() == 'm') {
    draw_mask = !draw_mask;
  }

  // Press 's' to start the main "put on mask" app.
  if (event.getChar() == 's') {
    start_mask = true;
    start_edge = false;
  }

  // Press 'o' to start the sub "edge" app.
  if (event.getChar() == 'o') {
    start_mask = false;
    start_edge = true;
  }
}

}  // namespace myapp

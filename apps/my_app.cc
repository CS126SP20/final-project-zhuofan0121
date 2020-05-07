// Copyright (c) 2020 [Zhuofan Jia]. All rights reserved.

#include "my_app.h"

#include <opencv2/imgproc/types_c.h>

#include <string>
#include <vector>

#include "CinderOpenCV.h"
#include "cinder/ImageIo.h"
#include "cinder/Surface.h"

namespace myapp {

using cinder::app::KeyEvent;
using std::string;
using std::vector;

float scalingFactor = 0.75;

vector<string> mask_paths;
int mask_index = -1;

bool draw_rect;
bool draw_mask;
bool start_mask = true;
bool start_edge;
bool write_image;
bool load_image;
bool upload = true;

cinder::fs::path open_file_path;

MyApp::MyApp() {
  string t =
      "/Users/jiazhuofan/CLionProjects/cinder_0.9.2_mac/my-projects/"
      "final-project-zhuofan0121/assets/mask-images/";
  mask_paths = {
      t + "mask.jpg",       t + "mask-new.jpg",   t + "mask-new2.jpg",
      t + "mask-new3.jpg",  t + "mask-new4.jpg",  t + "mask-new5.jpg",
      t + "mask-new6.jpg",  t + "mask-new7.jpg",  t + "mask-new8.jpg",
      t + "mask-new9.jpg",  t + "mask-new10.jpg", t + "mask-new11.jpg",
      t + "mask-new12.jpg", t + "mask-new13.jpeg"};
}

void MyApp::setup() {
  face_detector.load(getAssetPath("haarcascade_frontalface_alt.xml").string());
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
  if (load_image) {
    if (upload) {
      open_file_path = getOpenFilePath();
      upload = false;
    }
    frame = cv::imread(open_file_path.string());
  } else {
    cap >> frame;
  }

  if (start_mask) {
    cv::resize(frame, frame, cv::Size(), scalingFactor, scalingFactor,
               cv::INTER_AREA);
    cvtColor(frame, frame_gray, CV_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);
    face_detector.detectMultiScale(frame_gray, faces, 1.1, 2,
                                   0u | cv::CASCADE_SCALE_IMAGE,
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
    for (auto& face : faces) {
      if (draw_rect) {
        cv::Rect faceRect(face.x, face.y, face.width, face.height);
        cv::rectangle(frame, faceRect, CV_RGB(0, 255, 0), 2);
      }
      if (draw_mask) {
        int x = face.x + int(0.1 * face.width);
        int y = face.y + int(0.5 * face.height);
        int w = int(0.8 * face.width);
        int h = int(0.5 * face.height);

        // extract the specific rect
        frame_roi = frame(cv::Rect(x, y, w, h));
        // resize mask image
        cv::resize(mask, face_mask_small, cv::Size(w, h));
        // convert mask image to gray
        cvtColor(face_mask_small, gray_mask_small, CV_BGR2GRAY);
        // change pixels greater than 230 to 0 (black) and smaller 230 to 255
        // (white)
        threshold(gray_mask_small, gray_mask_small_thresh, 230, 255,
                  CV_THRESH_BINARY_INV);
        // invert the above image
        bitwise_not(gray_mask_small_thresh, gray_mask_small_thresh_inv);
        // find the margin of mask
        bitwise_and(face_mask_small, face_mask_small, masked_face,
                    gray_mask_small_thresh);
        // add mask
        bitwise_and(frame_roi, frame_roi, masked_frame,
                    gray_mask_small_thresh_inv);
        // add to original image
        add(masked_face, masked_frame, frame(cv::Rect(x, y, w, h)));
      }
    }

    image_output = cinder::Surface(cinder::fromOcv(frame));
    tex_output = cinder::gl::Texture2d::create(image_output);
    cinder::gl::color(1, 1, 1);
    cinder::gl::draw(tex_output);

    if (write_image) {
      cinder::fs::path file_path = getSaveFilePath();
      if (!file_path.empty()) {
        cinder::writeImage(file_path, image_output);
      }
      write_image = false;
    }
  }

  if (start_edge) {
    image_output = cinder::Surface(cinder::fromOcv(edges));
    tex_output = cinder::gl::Texture2d::create(image_output);
    cinder::gl::draw(tex_output);

    if (write_image) {
      cinder::fs::path file_path = getSaveFilePath();
      if (!file_path.empty()) {
        cinder::writeImage(file_path, image_output);
      }
      write_image = false;
    }
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
    mask_index = (mask_index + 1) % (int)mask_paths.size();
    mask = cv::imread(mask_paths[mask_index]);
    if (!mask.data) {
      std::cerr << "Error loading mask image. Exiting!" << std::endl;
    }
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

  // Press 'w' to save the current window image.
  if (event.getChar() == 'w') {
    write_image = true;
  }

  // Press 'l' to load an image from path
  if (event.getChar() == 'l') {
    load_image = true;
    upload = true;
  }
}

}  // namespace myapp

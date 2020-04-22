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

namespace myapp {

using cinder::app::KeyEvent;

MyApp::MyApp() { }

void MyApp::setup() {
  rph::NotificationManager::getInstance()->add("Hello, World!", 10);
}

void MyApp::update() { }

void MyApp::draw() {
  cinder::gl::clear();
  rph::NotificationManager::getInstance()->draw();
}

void MyApp::keyDown(KeyEvent event) { }

}  // namespace myapp

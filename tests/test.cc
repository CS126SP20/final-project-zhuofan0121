// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <cinder/Rand.h>
#include <mylibrary/example.h>

#include <catch2/catch.hpp>
#include <opencv2/videoio.hpp>

TEST_CASE("Random sanity test", "[random]") {
  const float random = cinder::randFloat();
  REQUIRE(0. <= random);
  REQUIRE(random <= 1.);
}

TEST_CASE("Video capture test", "[capture]") {
  cv::VideoCapture cap(0);
  REQUIRE(cap.isOpened());
}
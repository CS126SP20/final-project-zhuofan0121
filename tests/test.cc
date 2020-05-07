// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <mylibrary/example.h>

#include <catch2/catch.hpp>

TEST_CASE("Init mask file path test", "[init]") {
  std::vector<std::string> mask_paths;
  mask_paths = mylibrary::InitMaskPaths(mask_paths);
  REQUIRE(mask_paths.size() == 14);
}
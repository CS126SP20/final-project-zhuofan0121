// Copyright (c) 2020 [Zhuofan Jia]. All rights reserved.

#include <mylibrary/example.h>

namespace mylibrary {

vector<string> InitMaskPaths(vector<string> mask_paths) {
  string t =
      "/Users/jiazhuofan/CLionProjects/cinder_0.9.2_mac/my-projects/"
      "final-project-zhuofan0121/assets/mask-images/";
  mask_paths = {
      t + "mask.jpg",       t + "mask-new.jpg",   t + "mask-new2.jpg",
      t + "mask-new3.jpg",  t + "mask-new4.jpg",  t + "mask-new5.jpg",
      t + "mask-new6.jpg",  t + "mask-new7.jpg",  t + "mask-new8.jpg",
      t + "mask-new9.jpg",  t + "mask-new10.jpg", t + "mask-new11.jpg",
      t + "mask-new12.jpg", t + "mask-new13.jpeg"};
  return mask_paths;
}

}  // namespace mylibrary

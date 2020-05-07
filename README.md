![Sample image](https://github.com/CS126SP20/final-project-zhuofan0121/blob/master/sample-pic.png)
# Final Project - Put On Your Mask
Course: CS 126 - Spring 2020

[![license](https://img.shields.io/badge/license-MIT-green)](LICENSE)
[![docs](https://img.shields.io/badge/docs-yes-brightgreen)](docs/README.md)

**Author**: Zhuofan Jia - [`zhuofan7@illinois.edu`](mailto:zhuofan7@illinois.edu)

*Put On Your Mask* is an app which is able to add a mask image lively to the video captured by your camera on the computer.
You can also upload an image.

keyboard shortcuts:
* Press 'esc' to quit full screen or quit app.
* Press 'f' to toggle full screen.
* Press 'c' to change to a different mask.
* Press 'r' to toggle rectangle on face.
* Press 'm' to toggle mask.
* Press 's' to start the main "put on mask" app.
* Press 'o' to start the sub "edge" app.
* Press 'w' to save the current window image.
* Press 'l' to load an image from path.
---

###Project Overview

I propose to design and implement a project which has some educational 
meanings but can also give users some entertainment 
during such hard time of the virus COVID-19. As it is known by us all, in
order to protect ourselves from droplet infection, wearing facial masks is an
effective way. Inspired by this idea, in this project, I plan to implement a 
function which can take in a picture with a (or more) human face in it and 
then automatically add an image of a mask in the proper position of the person's
face in the picture. The human face picture can either be taken by the 
computer's camera or uploaded by the user as an image file. After the mask is
generated, the user can take a screenshot and use it in any way he or she likes.

###Getting Started

This project uses C++. You can install CLion.
[Install CLion](https://www.jetbrains.com/clion/)

It uses the [Cinder](https://libcinder.org) framework. 

You can download the latest version Cinder for your platform [here](https://libcinder.org/download).

The latest version is v0.9.2.

Here is a basic tutorial on how to develop Cinder projects:
[tutorial](https://libcinder.org/docs/guides/tour/hello_cinder_chapter1.html).

Here is some documentation:
[documentation](https://libcinder.org/docs/reference/index.html).

**Setting up Cinder**

* Download Cinder (v0.9.2) for your platform. Extract the downloaded item into a folder. 
I’ll call this folder ~/Cinder throughout the write-up.
* Open the ~/Cinder folder in CLion and click the green build button. This will build libcinder. 
You only need to do this once per machine. This build might take a while.
* Create a directory, say my-projects in ~/Cinder. Clone the this project into this folder.
* Open the project in CLion, set the target to cinder-myapp and click the run button.

**External Libraries**

I used the Cinder Block [OpenCV3](https://github.com/cinder/Cinder-OpenCV3)
and also the library [OpenCV](https://github.com/opencv/opencv).

**Stretch Goals**

In the future, I would like to add the following things:
* Add buttons to the initial window that users can click and jump to corresponding functionality.
* Create an image gallery in 3D with processed pictures in it. You can switch
left and right to see each picture in the gallery.
 

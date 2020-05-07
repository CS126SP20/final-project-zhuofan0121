![Sample image](https://github.com/CS126SP20/final-project-zhuofan0121/blob/master/sample-pic.png)
# Final Project - Put On Your Mask
Course: CS 126 - Spring 2020

[![license](https://img.shields.io/badge/license-MIT-green)](LICENSE)
[![docs](https://img.shields.io/badge/docs-yes-brightgreen)](docs/README.md)

**Author**: Zhuofan Jia - [`zhuofan7@illinois.edu`](mailto:zhuofan7@illinois.edu)

*Put On Your Mask* is an app which is able to add a mask image lively to the video captured by your camera on the computer.
You can also upload an image.

Keyboard shortcuts:
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

### Project Overview

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

### Getting Started

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

First, let's say your cinder folder is at ~/Cinder.

NOTE: this might be different on your machine!! It might be ~/Downloads/Cinder or it could be 
/Users/rey/CLionProjects/Cinder, or it could be C:\Users\rey\Downloads\cinder_vs2015_0.9.2, 
or C:\Users\rey\cinder_vs2015_0.9.2\cinder_vs2015_0.9.2, or /Users/rey/Downloads/cinder_0.9.2, etc.

Formally, ${CINDER_PATH} is defined as the directory where the directory ${CINDER_PATH}/proj/cmake exists. 
Many of you had the pleasure of seeing this CMake error message when trying to load the CMake snake project. 
This should clear up some misunderstandings. So for example, your snake project already resides in the 
${CINDER_PATH}/my-projects/snake-<your-github-username>.

In CMake, you should define and literally use the variable ${CINDER_PATH} to refer to your Cinder location.

Okay, next let's integrate Cinder-OpenCV3 Cinder Block. Here is what you need to do:
1. On GitHub, make a fork of the Cinder Block.
Note that this isn't necessarily required, but it is typically what you would do if you want to make changes 
to a repo you don't own on GitHub.
2. In CLion, go to VCS > Get from Version Control, and then clone your forked version of the Cinder Block into 
${CINDER_PATH}/blocks/<name-of-cinder-block-repo> using the exact same name as the repo on GitHub.
So for Cinder-OpenCV3, you would type https://github.com/cinder/Cinder-OpenCV3.git as the URL,
and ${CINDER_PATH}/blocks/Cinder-OpenCV3 as the directory.
Remember, you won't type ${CINDER_PATH} literally, you type whatever this path is on your machine.
Then click the Clone button and open the repo in a new window.
3. In the new window, 
make the file ${CINDER_PATH}/blocks/Cinder-OpenCV3/proj/cmake/Cinder-OpenCV3Config.cmake, 
and place the following inside:
```
if(NOT TARGET Cinder-OpenCV3)
    # Define ${Cinder-OpenCV3_PROJECT_ROOT}. ${CMAKE_CURRENT_LIST_DIR} is just the current directory.
    get_filename_component(Cinder-OpenCV3_PROJECT_ROOT "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)

    # Define ${CINDER_PATH} as usual.
    get_filename_component(CINDER_PATH "${Cinder-OpenCV3_PROJECT_ROOT}/../.." ABSOLUTE)

    # Translate the <staticLibrary> tag.
    # cv-core
    add_library(cv-core STATIC IMPORTED)
    set_property(TARGET cv-core PROPERTY IMPORTED_LOCATION "${Cinder-OpenCV3_PROJECT_ROOT}/lib/macosx/libopencv_core.a")

    # cv-video
    add_library(cv-video STATIC IMPORTED)
    set_property(TARGET cv-video PROPERTY IMPORTED_LOCATION "${Cinder-OpenCV3_PROJECT_ROOT}/lib/macosx/libopencv_video.a")

    # cv_imgproc
    add_library(cv_imgproc STATIC IMPORTED)
    set_property(TARGET cv_imgproc PROPERTY IMPORTED_LOCATION "${Cinder-OpenCV3_PROJECT_ROOT}/lib/macosx/libopencv_imgproc.a")

    # cv_objdetect
    add_library(cv_objdetect STATIC IMPORTED)
    set_property(TARGET cv_objdetect PROPERTY IMPORTED_LOCATION "${Cinder-OpenCV3_PROJECT_ROOT}/lib/macosx/libopencv_objdetect.a")

    # ... keep going ...


    # There are no source files for this project. We have to create a "dummy" source.
    file(WRITE dummy.cc "")
    # Create the library from the source files. The target is now defined.
    add_library(Cinder-OpenCV3 dummy.cc)

    # Link the prebuilt libraries.
    target_link_libraries(Cinder-OpenCV3 cv-core cv-video)

    # Translate <includePath> tag.
    target_include_directories(Cinder-OpenCV3 INTERFACE
            "${Cinder-OpenCV3_PROJECT_ROOT}/include"
            "${Cinder-OpenCV3_PROJECT_ROOT}/include/opencv2"
            )

    target_include_directories(Cinder-OpenCV3 SYSTEM BEFORE INTERFACE "${CINDER_PATH}/include" )
endif()
```
### Stretch Goals

In the future, I would like to add the following:
* Add buttons to the initial window that users can click and jump to corresponding functionality.
* Create an image gallery in 3D with processed pictures in it. You can switch
left and right to see each picture in the gallery.
 

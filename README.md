# Final Project - Put On Your Mask

Course: CS 126 - Spring 2020

[![license](https://img.shields.io/badge/license-MIT-green)](LICENSE)
[![docs](https://img.shields.io/badge/docs-yes-brightgreen)](docs/README.md)

Read [this document](https://cliutils.gitlab.io/modern-cmake/chapters/basics/structure.html) to understand the project
layout.

**Author**: Zhuofan Jia - [`zhuofan7@illinois.edu`](mailto:zhuofan7@illinois.edu)
---

**Project Overview**

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

**Personal Background**

I do not have that much experience on such project except the experience I get from
the snake assignment.
Having spent a little time exploring the Cinder framework, I find that it integrates
a lot of interesting blocks and I am quite interested in the OpenCV's face
detection functionality. The reason why I would like to do this project is that
I think it will be interesting. When the epidemic starts, my friends all changed their avatars on their social
media into people with masks by using some type of apps. They have to select the image of 
mask and manually adjust positions to add on the face. I think it will be great
if I can make the mask automatically added.

**External Libraries**

I will be using a face detection library to detect face in the image:
[link to external library.](https://github.com/ShiqiYu/libfacedetection)
Here is [link to OpenCV.](https://github.com/cinder/Cinder-OpenCV)

**Rough Timeline**

* By the end of the first week, I should complete setting up the whole project and
the process of taking selfies or loading pictures. I should start working on 
the face detection process.
* By the end of the second week, I should complete the face detection and should
figure out where to add mask image. I should start working on adding image to 
the face.
* By the end of the third week, I should finish adding masks to the faces and 
finalize the whole project.

**Stretch Goals**

If there is still time remaining after I finish the above goals, here are some
stretch goals I can implement.
* Use a video stream from camera and process each frame to track faces of 
people and add masks in real time.
* Create an image gallery in 3D with processed pictures in it. You can switch
left and right to see each picture in the gallery.
 

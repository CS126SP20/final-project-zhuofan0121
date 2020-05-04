# Development

---
 - **4/21/20** Tried to set up external libraries
   - Spent so many hours trying to set up libfacedetection
   - Still cannot import it as how the writeup in final project does
   - Include it following the instructions in the lib's readme file
   - Still need to figure out how to use it to detect specific parts of faces
   
 - **4/28/20** Continued working on the project
   - Successfully imported OpenCV
   - Enabled VideoCapture
   - Generated a video consisting edges of every frame
   - Still need to integrate face-detection
 
 - **5/1/20** Implemented face detection
   - Found eyes, nose, and mouth from face
   - Drew rectangles on them
   - Still need to debug
   
 - **5/3/20** Figured out how to navigate between Cinder & OpenCV
   - Successfully drew rectangles on images with human faces
   - Implemented another GUI to show "edges" of frames captured by camera
   - Still need to figure out cinder's "capture" method
   - Also need to work on adding masks
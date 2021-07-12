Face Detection using OpenCV

Objective: Real time detection of faces and eyes in a video file or from a Webcam by implementing the gained basic knowledge of OpenCV library.

Description:
This is a self-project carried out to implement the OpenCV basics. This program uses the OpenCV library to detect faces and eyes in a live stream from webcam or in a video file stored in the local machine. This program detects faces in real time and tracks it. It uses pre-trained XML classifiers for the same. The classifiers used in this program have facial features trained in them. They use the Harrcascades multilevel method detecting faces or other objects.
The detected faces are highlighted by a red coloured bounding circle and the eyes are highlighted by a blue colour bounding circle and the detected different faces can be stored at the specified location inside the system (which must be given as input before execution of program). 

Explanation of Code:
Inside the main, each image from the video will be read and passed onto the detect image function. Inside this function, the image is converted from BGR to Grayscale and the faces are detected from the grayscale image and the bounding coordinates of each face is stored into a vector of rectangles. 
A threshold area is set to remove errors / filter the detected . This threshold area can be manually changed depending upon the size of face to be detected.
According to aspect ratio, bounding circle of red colour is drawn around the face and a bounding circle of blue colour is drawn around each of the eyes on the source image which will be displayed in real time.
Also, a copy of each face image is stored in the path specified.

Output:
•	On successful execution, all faces and eyes in real time are highlighted with the specified colours.
•	Also, all the detected real time faces will be stored at the path specified in the code in .jpg format.

Drawbacks:
•	In case of background infiltration and poor quality, mostly incorrect results are obtained. This is because the Haarcascades XML classifier is a primitive method and hence needs high quality footage for accuracy.
•	In a live stream or video, when the composure of an image changes, then the image will be detected as new image.
•	Threshold area for filtering varies from video to video.
•	Gives incorrect results when wearing spectacles.

Conclusion:
This is a good project for beginners to practically learn about OpenCV


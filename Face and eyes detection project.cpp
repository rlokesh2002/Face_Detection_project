#include<opencv2/objdetect.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp> //header file to work with harrcascade file

#include<iostream>

using namespace std;
using namespace cv;

/*PROJECT --> Detect face and eyes from a video / WebCam and stores different faces*/

void detectImage(Mat& imgsrc, CascadeClassifier& faceCascade, CascadeClassifier& eyesCascade, double scale, string& finpath)
{
	Mat imgGray;
	vector<Rect> faces; /*Stores the details of each face*/

	cvtColor(imgsrc, imgGray, COLOR_BGR2GRAY);
	resize(imgGray, imgGray, Size(), (1 / scale), (1 / scale), INTER_LINEAR); /*Resize the Grayscale Image*/
	equalizeHist(imgGray, imgGray);

	/*Detect faces of different sizes using cascade classifier*/
	faceCascade.detectMultiScale(imgGray, faces, 1.1, 2);

	for (int i = 0; i < faces.size(); i++)
	{
		Rect rect = faces[i];
		Mat currimg = imgsrc(rect);
		Point center;
		Scalar faceColor = Scalar(0, 0, 255); /*Color to draw around face --> Purple */
		Scalar eyeColor = Scalar(255, 0, 0); /*Color to draw around eyes --> Eyes */
		double rad;

		double aspect_ratio = (double)rect.width / rect.height; /*Finding aspect ratio of the detected client*/
		if (0.75 < aspect_ratio && aspect_ratio < 1.3)
		{
			/*Finding the center and radius of the circle to be drawn around the face*/
			center.x = cvRound((rect.x + rect.width * 0.5) * scale);
			center.y = cvRound((rect.y + rect.height * 0.5) * scale);
			rad = cvRound((rect.width + rect.height) * 0.25 * scale);
			circle(imgsrc, center, rad, faceColor, 4, 8); /*Drawing cirlce around the face on imgsrc*/
			circle(currimg, center, rad, faceColor, 4, 8); /*Drawing cirlce around the face on currimg*/
		}
		else
		{
			rectangle(imgsrc, rect, faceColor, 4, 8); /*Draws rectangle if the aspect ratio is not satisfied*/
		}

		if (eyesCascade.empty())	continue;
		Mat imgroi = imgGray(rect); /*roi is the current face of source image*/
		vector <Rect> eyes;
		eyesCascade.detectMultiScale(imgroi, eyes, 1.1, 2); /*Detecting eyes of the image*/

		for (size_t j = 0; j < eyes.size(); j++) /*Drawing circles around the eyes*/
		{
			Rect nr = eyes[j];
			center.x = cvRound((rect.x + nr.x + nr.width * 0.5) * scale);
			center.y = cvRound((rect.y + nr.y + nr.height * 0.5) * scale);
			rad = cvRound((nr.width + nr.height) * 0.25 * scale);
			circle(imgsrc, center, rad, eyeColor, 2, 8, 0);
			circle(currimg, center, rad, eyeColor, 2, 8, 0);
		}

		/*Saves the cropped Current single face image with detected eyes*/
		resize(currimg, currimg, Size(), 4, 4);
		imwrite((finpath + "Face_" + to_string((i + 1)) + ".jpg"), currimg);
	}

	imshow("Face Detection", imgsrc); /*Shows all the faces and eyes spotted*/
	return;
}

int main()
{
	//string path = "0"; /*This is for WebCam. In case of video, stores the path*/
	VideoCapture cap(0); /*Tool to capture the WebCam / Video*/
	Mat img;

	/*Path of Folder to store the different faces*/
	string savedpath = "Resources\\Faces\\";

	CascadeClassifier faceCascade, eyesCascade; /* PreDefined trained XML classifiers with facial features */

	/*Using haarcascades multilevel method --> Loading the classifiers*/
	faceCascade.load(".\\Resources\haarcascade_frontalface_default.xml");
	eyesCascade.load(".\Resources\haarcascade_eye_tree_eyeglasses.xml");
	double scale = 1;

	if (cap.isOpened())
	{
		cout << "Press L to exit/leave the window" << endl;
		while (true)
		{
			cap.read(img);
			if (img.empty())
				break;

			detectImage(img, faceCascade, eyesCascade, scale, savedpath);

			char c = (char)waitKey(10);
			if (c == 'l' || c == 'L')	break;
		}
	}
	else
	{
		cout << "Cannot open Cam/ Video" << endl;
	}

	return 0;
}
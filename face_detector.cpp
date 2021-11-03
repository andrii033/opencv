#include <opencv2/opencv.hpp>
using namespace cv;
int main()
{
 // Load Face cascade (.xml file)
 CascadeClassifier face_cascade;
 face_cascade.load("haarcascade_frontalface_alt2.xml");

Mat img;
 VideoCapture cap(0);
 while (true)
 {
 cap >> img;

//cvtColor(img, img, CV_BGR2GRAY);

// Detect faces
 std::vector<Rect> faces;
 face_cascade.detectMultiScale(img, faces, 1.1, 2, 0, Size(30, 30));


 // Draw circles on the detected faces
 for (int i = 0; i < faces.size(); i++)
 {
 Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
 ellipse(img, center, Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
 }
 
 imshow("Detected Face", img);
 waitKey(1);
 }
 return 0;
}
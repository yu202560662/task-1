#include<iostream>
#include<string>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int hmin=0,smin=0,vmin=0,hmax=179,smax=209,vmax=111;

int main()
{
Mat img,imgresize,imggray,imgcrop,imgbur,imgcanny,imgdilate,imghsv,mask;

Rect roi (250,300,300,300);
string path="/mnt/c/Users/yun/OneDrive/Pictures/redpot.jpg";
img=imread(path);
resize(img,imgresize,Size(),0.3,0.3);
cvtColor(imgresize,imggray,COLOR_BGR2GRAY);
imgcrop=imgresize(roi);
GaussianBlur(imgcrop,imgbur,Size(17,17),0,0);
Canny(imgbur,imgcanny,50,150);
Mat kenel=getStructuringElement(MORPH_RECT,Size(5,5));
dilate(imgcanny,imgdilate,kenel);
cvtColor(imgbur,imghsv,COLOR_BGR2HSV);
namedWindow("TRACKBARS",(640,200));
createTrackbar("hmin","TRACKBARS",&hmin,179);
createTrackbar("smin","TRACKBARS",&smin,255);
createTrackbar("vmin","TRACKBARS",&vmin,255);
createTrackbar("hmax","TRACKBARS",&hmax,179);
createTrackbar("smax","TRACKBARS",&smax,255);
createTrackbar("vmax","TRACKBARS",&vmax,255);
Scalar lower(hmin,smin,vmin);
Scalar upper(hmax,smax,vmax);
inRange(imghsv,lower,upper,mask);
int num=countNonZero(mask);
cout<<"非零素数:"<<num<<endl;
while (true)
{
 

Scalar lower(hmin,smin,vmin);
Scalar upper(hmax,smax,vmax);
inRange(imghsv,lower,upper,mask);
imshow("imghsv",imghsv);
imshow("mask",mask);

waitKey(1);

}



}
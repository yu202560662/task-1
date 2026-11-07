#include<iostream>
#include<string>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;
int hmin=75,smin=40,vmin=140,hmax=115,smax=255,vmax=255;
vector<Mat> rois;
void getContours(Mat mask,Mat img)
{

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    
    
    findContours(mask,contours,hierarchy,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
    vector<vector<Point>> conpoly(contours.size());
    
    vector<Rect> boundRect(contours.size());
    vector<RotatedRect> light;
    drawContours(img,contours,-1,Scalar(255,0,255),2);
    for (int i=0;i<contours.size();i++)
    {
    // {   float peri=arcLength(contours[i],true);
    //     approxPolyDP(contours[i],conpoly[i],0.02*peri,true);
    //     boundRect[i]=boundingRect(conpoly[i]);
            RotatedRect rect_min=minAreaRect(contours[i]);
            double ratio=max(rect_min.size.width,rect_min.size.height)/min(rect_min.size.width,rect_min.size.height);
            if (ratio>2.2)
            {
                light.push_back(rect_min);
            }}

            for(int a=0;a<light.size();a++)
            {
                RotatedRect ra=light[a];
                Point2f ca=ra.center;
                float angle=ra.angle;
                for (int b=a+1;b<light.size();b++)
                {
                    RotatedRect rb=light[b];
                    Point2f cb=rb.center;
                    float angleb=rb.angle;
                  
                    float ang_diff=fabs(angle-angleb);
                    float y_diff=fabs(ca.y-cb.y);
                    if (ang_diff<10 && y_diff<30)
                    {

                        Point2f psta[4],pstb[4];
                        ra.points(psta);
                        rb.points(pstb);
                        vector<Point2f> all_points;
                        // for (int j=0;j<4;j++)
                        // {
                        //     all_points.push_back(psta[j]);
                        //     all_points.push_back(pstb[j]);
                        // }
                        Rect bound_rect=boundingRect(all_points);

                        float x_min=1e9,x_max=-1e9,y_min=1e9,y_max=-1e9;
                        for(auto &p:psta)
                        {x_min=min(x_min,p.x);
                        x_max=max(x_max,p.x);
                        y_min=min(y_min,p.y);
                        y_max=max(y_max,p.y);}
                    
                    for(auto &p:pstb)
                {
                    
                    x_min=min(x_min,p.x);
                    x_max=max(x_max,p.x);
                    y_min=min(y_min,p.y);
                    y_max=max(y_max,p.y);
                }
                rectangle(img,Point(x_min,y_min),Point(x_max,y_max),Scalar(0,0,255),2);
                
                Rect roi_rect((int)x_min,(int)y_min,(int)(x_max-x_min),(int)(y_max-y_min));
                // rectangle(img,Point(bound_rect.x,bound_rect.y),Point(bound_rect.x+bound_rect.width,bound_rect.y+bound_rect.height),Scalar(0,0,255),2);
                Mat roi=img(roi_rect).clone();
                rois.push_back(roi);
               
                
                }}
            }
        }





            

    

int main()
{
Mat img,imghsv,imgblur,mask;
string path="/mnt/c/Users/yun/OneDrive/Pictures/zj3.jpg";
img=imread(path);
cvtColor(img,imghsv,COLOR_BGR2HSV);
GaussianBlur(imghsv,imgblur,Size(3,3),0,0);
// namedWindow("TRACKBARS",(640,200));
// createTrackbar("hmin","TRACKBARS",&hmin,179);
// createTrackbar("smin","TRACKBARS",&smin,255);
// createTrackbar("vmin","TRACKBARS",&vmin,255);
// createTrackbar("hmax","TRACKBARS",&hmax,179);
// createTrackbar("smax","TRACKBARS",&smax,255);
// createTrackbar("vmax","TRACKBARS",&vmax,255);




Scalar lower(hmin,smin,vmin);
Scalar upper(hmax,smax,vmax);
inRange(imgblur,lower,upper,mask);

getContours(mask,img);
imshow("img",img);
imshow("mask",mask);

for (int i=0;i<rois.size();i++)
{   string st="ROI"+to_string(i);
    imshow(st,rois[i]);
}

waitKey(0);
return 0;
}

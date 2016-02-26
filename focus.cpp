#include<iostream>
#include<string>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

int main()
{

  Mat orig_img= imread("test.jpg");
  Mat gray_img, hsv_img;
  Mat output_img = Mat(orig_img.rows, orig_img.cols, CV_8UC3);
  cvtColor(orig_img,gray_img, COLOR_BGR2GRAY);
  cvtColor(gray_img,gray_img, COLOR_GRAY2BGR);
  cvtColor(orig_img,hsv_img, COLOR_BGR2HSV);

  //TODO: select coordinates


  inRange(hsv_img, Scalar(150, 0, 0), Scalar(180,255,255), hsv_img);

  Mat kernel = (Mat_<uchar>(3,3) << 0,1,0,1,1,1,0,1,0);
  // erode(hsv_img, hsv_img, kernel);
  // erode(hsv_img, hsv_img, kernel);
  dilate(hsv_img, hsv_img, kernel);
  dilate(hsv_img, hsv_img, kernel);


  uchar* p;
  uchar* q;
  uchar* r;
  uchar* s;
  int i,j;

  for(i=0;i<orig_img.rows; i++)
	{
		p=orig_img.ptr<uchar>(i);
		q=output_img.ptr<uchar>(i);
    r=gray_img.ptr<uchar>(i);
    s=hsv_img.ptr<uchar>(i);
		for(j=0;j<orig_img.cols*orig_img.channels();j+=orig_img.channels())
		{
			if(s[j/3]==255)
			{
				q[j]=p[j];
				q[j+1]=p[j+1];
				q[j+2]=p[j+2];
			}
			else
			{
        q[j]=r[j];
        q[j+1]=r[j+1];
        q[j+2]=r[j+2];
			}
		}
	}

  imshow("Original",orig_img);
  imshow("Gray",gray_img);
  imshow("HSV",hsv_img);
  imshow("Output",output_img);

  waitKey(0);


}

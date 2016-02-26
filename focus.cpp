#include<iostream>
#include<string>
#include<vector>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

int main()
{

  Mat orig_img= imread("test3.jpg");
  Mat gray_img, hsv_img;
  Mat output_img = Mat(orig_img.rows, orig_img.cols, CV_8UC3);
  uchar* p;
  uchar* q;
  uchar* r;
  uchar* s;
  int i,j;
  vector<int> histogram;

  cvtColor(orig_img,gray_img, COLOR_BGR2GRAY);
  cvtColor(gray_img,gray_img, COLOR_GRAY2BGR);
  cvtColor(orig_img,hsv_img, COLOR_BGR2HSV);

  //TODO: select coordinates


  for(i=0;i<9;i++)
  {
    histogram.push_back(0);
  }

  for(i=0;i<hsv_img.rows; i++)
	{
		s=hsv_img.ptr<uchar>(i);
		for(j=0;j<hsv_img.cols*3;j+=3)
		{
      int hue=s[j];
      int sat=s[j+1];
      int val=s[j+2];
      if(val<13) //black
      {
          histogram[0]++;
      }
      if(sat<15) //white
      {
        histogram[1]++;
      }
      if(hue>=0 && hue<23) //orange
      {
        histogram[2]++;
      }
      if(hue>=23 && hue<35) //yellow
      {
        histogram[3]++;
      }
      if(hue>=35 && hue<80) //green
      {
        histogram[4]++;
      }
      if(hue>=80 && hue<100) //cyan
      {
        histogram[5]++;
      }
      if(hue>=100 && hue<135) //blue
      {
        histogram[6]++;
      }
      if(hue>=135 && hue<150) //pink
      {
        histogram[7]++;
      }
      if(hue>=150 && hue<=180) //red
      {
        histogram[8]++;
      }
    }
	}

  int h_min, h_max;
  int histogram_max=histogram[0];
  int histogram_max_index=0;
  for(i=1;i<9;i++)
  {
    if(histogram[i]>histogram_max)
    {
      histogram_max=histogram[i];
      histogram_max_index=i;
    }
  }

  cout << histogram_max_index << endl;

  switch(histogram_max_index) {
    case 2:
      h_min=5;
      h_max=22;
      break;
    case 3:
      h_min=23;
      h_max=34;
      break;
    case 4:
      h_min=35;
      h_max=79;
      break;
    case 5:
      h_min=80;
      h_max=99;
      break;
    case 6:
      h_min=100;
      h_max=134;
      break;
    case 7:
      h_min=135;
      h_max=149;
      break;
    case 8:
      h_min=150;
      h_max=180;
      break;
  }

  cout << h_min << endl;
  cout << h_max << endl;

  if(histogram_max_index==0 || histogram_max_index==1)
  {
    output_img=gray_img;
  }
  else
  {
    inRange(hsv_img, Scalar(h_min,15,13), Scalar(h_max,255,255), hsv_img);
    // inRange(hsv_img, Scalar(150,15,13), Scalar(180,255,255), hsv_img);

    Mat kernel = (Mat_<uchar>(3,3) << 0,1,0,1,1,1,0,1,0);
    erode(hsv_img, hsv_img, kernel);
    erode(hsv_img, hsv_img, kernel);
    erode(hsv_img, hsv_img, kernel);
    dilate(hsv_img, hsv_img, kernel);
    dilate(hsv_img, hsv_img, kernel);
    dilate(hsv_img, hsv_img, kernel);
    // dilate(hsv_img, hsv_img, kernel);
    // dilate(hsv_img, hsv_img, kernel);



    for(i=0;i<orig_img.rows; i++)
  	{
  		p=orig_img.ptr<uchar>(i);
  		q=output_img.ptr<uchar>(i);
      r=gray_img.ptr<uchar>(i);
      s=hsv_img.ptr<uchar>(i);
  		for(j=0;j<orig_img.cols*3;j+=3)
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
  }
  imshow("Original",orig_img);
  imshow("Gray",gray_img);
  imshow("HSV",hsv_img);
  imshow("Output",output_img);
  waitKey(0);
}

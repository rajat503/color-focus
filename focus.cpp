#include<iostream>
#include<string>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

Mat dst, src_gray, detected_edges, src;
int lowThreshold;

void CannyThreshold(int, void*)
{
  /// Reduce noise with a kernel 3x3
  blur( src_gray, detected_edges, Size(3,3) );

  /// Canny detector
  Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*3, 3 );

  /// Using Canny's output as a mask, we display our result
  dst = Scalar::all(0);

  src.copyTo( dst, detected_edges);
  imshow( "Edge Map", dst );
  imshow("",src);
 }


void canny()
{

  dst.create( src.size(), src.type() );
  cvtColor( src, src_gray, CV_BGR2GRAY );
  namedWindow( "Edge Map", CV_WINDOW_AUTOSIZE );
  createTrackbar( "Min Threshold:", "Edge Map", &lowThreshold, 100, CannyThreshold );
  CannyThreshold(0, 0);
  waitKey(0);
}

int main()
{
	//src = imread("Lenna.png");

  //TODO: select coordinates

  //canny();

  Mat orig_img= imread("Lenna.png",0);
  Mat outerBox = Mat(orig_img.size(), CV_8UC1);
  GaussianBlur(orig_img, orig_img, Size(11,11), 0);
  adaptiveThreshold(orig_img, outerBox, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 5, 2);
  bitwise_not(outerBox, outerBox);
  Mat kernel = (Mat_<uchar>(3,3) << 0,1,0,1,1,1,0,1,0);
  erode(outerBox, outerBox, kernel);

  imshow("",outerBox);
  waitKey(0);


}

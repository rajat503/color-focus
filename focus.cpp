#include<iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

void detectBlob(Mat orig_img)
{
  
}

int main()
{
  Mat orig_img;
	orig_img = imread("Lenna.png");

  //TODO: select coordinates

  detectBlob(orig_img);

  imshow("Output",orig_img);
  waitKey();

}

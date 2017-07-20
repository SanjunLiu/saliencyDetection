/*************************************************

Copyright: Guangyu Zhong all rights reserved

Author: Guangyu Zhong

Date:2014-09-27

Description: codes for Manifold Ranking Saliency Detection
Reference http://ice.dlut.edu.cn/lu/Project/CVPR13[yangchuan]/cvprsaliency.htm

**************************************************/
#include "PreGraph.h"

#include <iostream>
#include <unistd.h>
#include <string>

#include <cv.h>
#include <highgui.h>

using namespace std;
using namespace cv;

void usage(char * s)
{
    fprintf(stderr, "\n");
    fprintf(stderr, "%s -s <source file> build: %s-%s\n",
            s, __DATE__, __TIME__);
    fprintf(stderr, "s: path image file\n");
    fprintf(stderr, "\n example: %s -s ../testImages/corn.jpg\n", s);
}

int main(int argc, char* argv[])
{

    int c;
    std::string image_path;
    while((c = getopt(argc, argv, "s:?")) != -1){
        switch(c){
          case 's':
             image_path = optarg;
             break;
          case '?':
          default:
             usage(argv[0]);
             return -1;
        }
    }
    if (image_path.empty()){
        usage(argv[0]);
        return -1;
    }
	Mat img = imread(image_path.c_str());
	PreGraph SpMat;
	Mat superpixels = SpMat.GeneSp(img);
	Mat sal = SpMat.GeneSal(img);
	cout << sal;
	Mat salMap = SpMat.Sal2Img(superpixels, sal);
	Mat tmpsuperpixels;
	normalize(salMap, tmpsuperpixels, 255.0, 0.0, NORM_MINMAX);
	tmpsuperpixels.convertTo(tmpsuperpixels, CV_8UC3, 1.0);
    imwrite("salinceImage.jpg", tmpsuperpixels);

	return 0;
}

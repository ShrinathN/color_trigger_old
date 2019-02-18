#include <iostream>
#include <stdio.h>
#include <opencv2/core.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio/videoio.hpp>
#define CORD1 100
#define CORD2 150
using namespace std;
using namespace cv;
int main()
{
    //this is the video device, please change this
    VideoCapture videoCap("/dev/video0");
    Mat capturedImage, regionToScan, statusZone;
    char byt, flag;
    long longR, longG, longB;
    Scalar color(0,0,255);
    namedWindow("Testing");
    do
    {
        flag = 0; //this means if the color in the box is red
        videoCap >> capturedImage; //frame capture into capturedImage
        Point point1,point2; //two points
        point1.x = CORD1;
        point1.y = CORD1;
        point2.x = CORD2;
        point2.y = CORD2;
        Range r;//range
        r.start = CORD1;
        r.end = CORD2;
        regionToScan = capturedImage(r,r);
        longR = 0; //three variables for storing the total of all the RGB in the zone
        longG = 0;
        longB = 0;
        //now we'll sum all the RGB values in the area-of-interest
        for(unsigned char x_counter = 0; x_counter < CORD2 - CORD1; x_counter++)
        {
            for(unsigned char y_counter = 0; y_counter < CORD2 - CORD1; y_counter++)
            {
                longB += regionToScan.at<Vec3b>(x_counter, y_counter)[0];
                longG += regionToScan.at<Vec3b>(x_counter, y_counter)[1];
                longR += regionToScan.at<Vec3b>(x_counter, y_counter)[2];
            }
        }
        //averaging the 3 channels
        longR /= 10000;
        longG /= 10000;
        longB /= 10000;
        printf("R%d\nG%d\nB%d\n\n",longR,longG,longB);
        //=================================
        //THIS IS A HORRIBLE WAY TO DO THIS
        //=================================
        //it works, but barely, ideally you'd want to calculate the ratio between the three colors,
        //and ranges to what a particular color can be
        if((longR >50) &&
                (longG < 50) &&
                (longB < 50))
        {
            printf("Red detected\n");
            flag = 1;
            statusZone = capturedImage(r,r);
        }
        //now we'll draw the rectangle
        if(flag == 0)
            rectangle(capturedImage,point1,point2,Scalar(0,0,0xff));
        else
            rectangle(capturedImage,point1,point2,Scalar(0,0xff,0));
        imshow("Testing",capturedImage);
        byt = waitKey(2);
    }
    while(byt != 'a'); //press 'a' to exit
}

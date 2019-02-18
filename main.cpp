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
    VideoCapture videoCap("/dev/video0");
    Mat capturedImage, regionToScan, statusZone;
    char byt, flag, x_counter, y_counter;
    long longR, longG, longB;
    Scalar color(0,0,255);
    namedWindow("wind");
    do
    {
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
        for(x_counter = 0; x_counter < CORD2 - CORD1; x_counter++)
        {
            for(y_counter = 0; y_counter < CORD2 - CORD1; y_counter++)
            {
                longB += regionToScan.at<Vec3b>(x_counter, y_counter)[0];
                longG += regionToScan.at<Vec3b>(x_counter, y_counter)[1];
                longR += regionToScan.at<Vec3b>(x_counter, y_counter)[2];
            }
        }
        longR /= 10000;
        longG /= 10000;
        longB /= 10000;
        printf("R%d\nG%d\nB%d\n\n",longR,longG,longB);
        if((longR >50) &&
                (longG < 120) &&
                (longB < 120))
        {
            printf("red detected\n");
            flag = 1;
            statusZone = capturedImage(r,r);
        }
        else
        {
            flag = 0;
        }
        if(flag == 0)
            rectangle(capturedImage,point1,point2,Scalar(0,0,0xff));
        else
            rectangle(capturedImage,point1,point2,Scalar(0,0xff,0));
        imshow("wind",capturedImage);
        byt = waitKey(2);
    }
    while(byt != 'a');
}

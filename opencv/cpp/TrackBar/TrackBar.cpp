// This program adds a trackbar to demonstrate GUI controls.

#include <opencv2/opencv.hpp>
#include <highgui.h>
#include <iostream>

using namespace cv;
using namespace std;

/// Global Variables
const int alpha_slider_max = 100;
int alpha_slider;
double alpha;
double beta;

/// Matrices to store images
Mat src1;
Mat src2;
Mat dst;

void on_trackbar( int, void* )
{
    alpha = (double) alpha_slider/alpha_slider_max ;
    beta = ( 1.0 - alpha );

    addWeighted( src1, alpha, src2, beta, 0.0, dst );

    // reshow the image
    imshow( "Linear Blend", dst );
}

int main( int argc, char** argv)
{
    // Load the source images
    if( argc == 3)
    {
        src1 = imread(argv[1], CV_LOAD_IMAGE_COLOR);
        src2 = imread(argv[2], CV_LOAD_IMAGE_COLOR);
        if( src1.empty() || src2.empty())
        {
            cout << "Error loading one of the images!" << endl;
            return -1;
        }
    }
    else
    {
        cout << "Usage: Trackbar path_to_image" << endl;
        return -1;
    }

    // Initialize values
    alpha_slider = 0;

    // Create windows
    namedWindow( "Linear Blend", 1 );

    // Create trackbars
    char TrackbarName[50];
    sprintf( TrackbarName, "Alpha x %d", alpha_slider_max );

    createTrackbar( TrackbarName, "Linear Blend",
            &alpha_slider, alpha_slider_max, on_trackbar );

    // Show the image with initial trackbar placement
    on_trackbar( alpha_slider, 0 );

    waitKey(0);
    return 0;
}

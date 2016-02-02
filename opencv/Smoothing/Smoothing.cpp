// Smoothing (aka blurring), is a simple and frequently used technique.
// This tutorial focuses on smoothing to reduce noise.

// To smooth we apply a filter to the image, the most common type being linear
// in which an output pixel's value is determined by a weighted sum of the
// input pixel values.
// g(i, j) = sum over k,l [f(i + k, j + l) * h(k, l)]
// h(k, l) is the kernel, which is just the coefficients of the filter.
// It helps to visualize a filter as a window of coefficients sliding across
// the image.

// Normalized box filter is the simplest filter.
// Each output pixel is the mean of its kernel neighbors.

// Gaussian filter is not the fastest, but is probably the most useful filter.
// Each point in the input array is convolved with a Gaussian kernel and summed.

// Median filter runs through each element of the signal and replaces each
// pixel with the median of its neighboring pixels.

// Bilateral filter is useful when wanting to avoid smoothing away edges.
// It is similar to the Gaussian filter but takes into account the difference
// in intensity between the neighboring pixels and the evaluated one.

// This program loads an image and applies 4 different types of filters.

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace std;
using namespace cv;

/// Global Variables
int DELAY_CAPTION = 1500;
int DELAY_BLUR = 500;
int MAX_KERNEL_LENGTH = 31;

Mat src; Mat dst;
char window_name[] = "Filter Demo 1";

/// Function headers
int display_caption( const char* caption );
int display_dst( int delay );

int main( int argc, char** argv)
{
    namedWindow(window_name, CV_WINDOW_AUTOSIZE);

    // Load the source image
    if( argc == 2)
    {
        src = imread(argv[1], CV_LOAD_IMAGE_COLOR);
        if( src.empty() )
        {
            return -1;
        }
    }
    else
    {
        cout << "Usage: Smoothing path_to_image" << endl;
        return -1;
    }

    if( display_caption( "Original Image" ) != 0) { return 0; }

    dst = src.clone();
    if( display_dst( DELAY_CAPTION ) != 0 ) { return 0; }

    // Applying homogenous blur
    if( display_caption( "Homogeneous Blur" ) != 0 ) { return 0; }
    for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
    {
        // Size(w, h) defines the size of the kernel, w/h in pixels
        // Point(-1, -1) indicates where the anchor point is located with
        // respect to the neighborhood. A negative value sets the
        // center of the kernel as the anchor point.
        blur(src, dst, Size(i, i), Point (-1, -1));
        if( display_dst( DELAY_BLUR ) != 0 ) { return 0; }
    }

    // Applying Gaussian blur
    if( display_caption( "Gaussian Blur" ) != 0 ) { return 0; }
    for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
    {
        // Size(w, h) is the size of the kernel, which is the number of
        // neighbors to be considered. w/h have to be odd and positive numbers
        // otherwise the size will be calculated with the following two
        // arguments.
        // 0, 0 are the standard deviation x and y. 0 implies that they
        // are calculated using the kernel size.
        GaussianBlur(src, dst, Size(i, i), 0, 0);
        if( display_dst( DELAY_BLUR ) != 0 ) { return 0; }
    }

    // Applying Median blur
    if( display_caption( "Median Blur" ) != 0 ) { return 0; }
    for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
    {
        // i is the size of the kernel, which must be odd and is only
        // one value in this example because we are using a square window.
        medianBlur(src, dst, i);
        if( display_dst( DELAY_BLUR ) != 0 ) { return 0; }
    }

    // Applying Bilateral blur
    if( display_caption( "Bilateral Blur" ) != 0 ) { return 0; }
    for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
    {
        // i is the diameter of each pixel neighborhood
        // i*2 is the standard deviation in color space
        // i/2 is the standard deviation in the coordinate space in pixels
        bilateralFilter(src, dst, i, i*2, i/2);
        if( display_dst( DELAY_BLUR ) != 0 ) { return 0; }
    }

    // Wait until user presses a key
    display_caption( "Demo has finished, press a key to exit");

    waitKey(0);
    return 0;
}

int display_caption( const char* caption)
{
    dst = Mat::zeros( src.size(), src.type() );
    putText( dst, caption,
            Point( src.cols/4, src.rows/2), CV_FONT_HERSHEY_COMPLEX,
            1, Scalar(255, 255, 255) );
    imshow( window_name, dst );
    int c = waitKey( DELAY_CAPTION );
    if( c >= 0 )
    {
        return -1;
    }
    return 0;
}

int display_dst ( int delay )
{
    imshow( window_name, dst );
    int c = waitKey(delay);
    if( c >= 0 )
    {
        return -1;
    }
    return 0;
}

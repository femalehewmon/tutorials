// Threshold is the simplest segmentation method.

// For example, can be used in separating out region so thes image based on the
// variation of intensity between the object pixels and background pixels.
// To differentiate pixels, we perform acomparsion of each pixel intensity
// value to a threshold. We can then assign them to a constant value to fully
// identify them (ie. assign them 0 or 255).

// Types of thresholding in OpenCV with the threshold function:

// 0: Binary Threshold
//  if the intensity of a pixel is higher than thresh, then the new pixel
//  intensity is set to maxVal, otherwise it is set to 0.

// 1: Binary Threshold, Inverted
//  if the intensity of a pixel is higher than thresh, then the new pixel
//  intnsity is set to 0, otherwise it is set to maxVal

// 2: Truncated Threshold
//  if the intesnity of a pixel is higher than thresh, then the new pixel
//  intensity is set to thresh, otherwise it is kept the same

// 3: Threshold to Zero
//  if the intensity of a pixel is lower than threw, then the new pixel
//  intensity is set to 0

// 4: Threshold to Zero, Inverted
//  if the intensity of a pixel is higher than thresh, then the new pixel
//  intensity is set to 0

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;

/// Global variables

int threshold_value = 0;
int threshold_type = 3;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;

Mat src, src_gray, dst;
const char* window_name = "Threshold Demo";

const char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
const char* trackbar_value = "Value";

/// Function headers
void Threshold_Demo( int, void* );

int main( int argc, char** argv )
{
    // Load an image
    src = imread( argv[1], 1 );
    if( src.empty() )
    {
        cout << "Image not valid: " << argv[1] << endl;
        return -1;
    }

    // Convert to greyscale
    cvtColor( src, src_gray, CV_BGR2GRAY );

    // Create a window
    namedWindow( window_name, CV_WINDOW_AUTOSIZE) ;

    // Create trackbars to choose type of thresholding
    createTrackbar( trackbar_type, window_name, &threshold_type,
            max_type, Threshold_Demo );
    createTrackbar( trackbar_value, window_name, &threshold_value,
            max_value, Threshold_Demo );

    // Initial call to function to intialize
    Threshold_Demo( 0, 0 );

    waitKey (0);
    return 0;
}

void Threshold_Demo( int, void* )
{
      /* 0: Binary
         1: Binary Inverted
         2: Threshold Truncated
         3: Threshold to Zero
         4: Threshold to Zero Inverted
       */

    // input_image, output_image, threshold_value, maxval, type_of_threshold
    // typically used for binarizing an image or removing noise -
    // removing pixels with too small or too large values
    threshold( src_gray, dst, 
            threshold_value, max_BINARY_value, threshold_type);

    imshow(window_name, dst);
}

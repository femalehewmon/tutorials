// A general image processing operator is a function that takes one or more input images and produces an output image
// Two types of image transformations:
//      1. Point operators (pixel transforms)
//          --> each ouput pixel depends on only the input pixel and adjustment
//          --> examples: brightness and contrast adjustments, color correction
//      2. Neighborhood (area-based) operators

// Brightness and contrast adjustment:
// Two point processes are multiplication and addition with a constant
//      g(x) = alpha*f(x) + beta
// The parameters alpha > 0 and beta are often called gain and bias parameters
//      --> gain controls contrast
//      --> bias controls brightness
//     f(x) are the source image pixels, g(x) are the output image pixels
//          g(i,j) = alpha*f(i,j) + beta
//     where i and j indicate the pixel located in the i-th row and j-th column

// Two primary methods for adjusting brightness and contrast:
//      1. Basic method seen below
//      2. image.convertTo(new_image, -1, alpha, beta) -- built-in, easy!

#include <opencv2/opencv.hpp>
#include <highgui.h>
#include <iostream>

using namespace std;
using namespace cv;

double alpha; /**< Simple contrast control */
int beta;  /**< Simple brightness control */

int main( int argc, char** argv )
{
 // Read image given by user
 Mat image = imread( argv[1] );
 // New image must have the following features:
 //     - initial pixel values equal to zero
 //     - same size and type as original image 
 Mat new_image = Mat::zeros( image.size(), image.type() );

 // Initialize values
 std::cout<<" Basic Linear Transforms "<<std::endl;
 std::cout<<"-------------------------"<<std::endl;
 std::cout<<"* Enter the alpha value [1.0-3.0]: ";std::cin>>alpha;
 std::cout<<"* Enter the beta value [0-100]: "; std::cin>>beta;

 /// Create Windows
 namedWindow("Original Image", 1);
 namedWindow("New Image - hand written", 1);
 namedWindow("New Image - convertTo", 1);
 /// Show original image
 imshow("Original Image", image);

 // Do the operation new_image(i,j) = alpha*image(i,j) + beta
 double t = (double)getTickCount();
 for( int y = 0; y < image.rows; y++ )
 {
    for( int x = 0; x < image.cols; x++ )
    {
        // Access all 3 channels of the BGR image separately
        // Use saturate_cast to make sure values are valid uchar types
        for( int c = 0; c < 3; c++ )
        {
            new_image.at<Vec3b>(y,x)[c] =
              saturate_cast<uchar>( alpha*( image.at<Vec3b>(y,x)[c] ) + beta );
       }
     }
 }
 t = ((double)getTickCount() - t)/getTickFrequency();
 cout << "Hand written function times passed in seconds: " << t << endl;
 imshow("New Image - hand written", new_image);

 // Built-in converTo
 t = (double)getTickCount();
 image.convertTo(new_image, -1, alpha, beta);
 cout << "Built-in convertTo time passed in seconds: " << t << endl;
 imshow("New Image - convertTo", new_image);

 /// Wait until user press some key
 waitKey();
 return 0;
}

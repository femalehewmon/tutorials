// Mask operations on matrices!
// Recalculate each pixel in an image according to a mask matrix: aka, kernel.
// This mask holds values that will adjust how much influence neighboring pixels have on new pixel values.

// There are 2 primary methods to accomplish applying a mask:
//      1. The Basic Method
//      2. filter2D

// Example mask replicated in methods below:
//      I(i,j) = 5 * I(i,j) - [I(i-1,j) + I(i+1,j) + I(i,j-1) + I(i,j+1)]

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

static void help(char* progName)
{
    cout << endl
        <<  "This program shows how to filter images with mask: the write it yourself and the"
        << "filter2d way. " << endl
        <<  "Usage:"                                                                        << endl
        << progName << " [image_name -- default lena.jpg] [G -- grayscale] "        << endl << endl;
}

void Sharpen(const Mat& myImage,Mat& Result);

int main( int argc, char* argv[])
{
    help(argv[0]);
    const char* filename = argc >=2 ? argv[1] : "lena.jpg";

    Mat I, J, K;

    if (argc >= 3 && !strcmp("G", argv[2]))
        I = imread( filename, CV_LOAD_IMAGE_GRAYSCALE);
    else
        I = imread( filename, CV_LOAD_IMAGE_COLOR);

    namedWindow("Input", WINDOW_AUTOSIZE);
    namedWindow("Output", WINDOW_AUTOSIZE);

    imshow("Input", I);

    // basic method, manually applying a mask (or kernel)
    double t = (double)getTickCount();
    Sharpen(I, J);
    t = ((double)getTickCount() - t)/getTickFrequency();
    cout << "Hand written function times passed in seconds: " << t << endl;

    imshow("Output", J);
    waitKey(0);

    // filter2D method, built in and optimized version made by OpenCV
    Mat kern = (Mat_<char>(3,3) <<  0, -1,  0,
                                   -1,  5, -1,
                                    0, -1,  0);
    t = (double)getTickCount();
    filter2D(I, K, I.depth(), kern );
    t = ((double)getTickCount() - t)/getTickFrequency();
    cout << "Built-in filter2D time passed in seconds:      " << t << endl;

    imshow("Output", K);

    waitKey(0);
    return 0;
}

// The Basic Method
void Sharpen(const Mat& myImage, Mat& Result)
{ 
    // Only accept uchar images
    CV_Assert(myImage.depth() == CV_8U);

    // Create an output image with the same size as the input image
    Result.create(myImage.size(), myImage.type());
    const int nChannels = myImage.channels();

    // Use C [] operator to acces pixels
    for (int j = 1; j < myImage.rows - 1; ++j)
    {
        // create pointers to all needed pixels to simplify access
        const uchar* previous = myImage.ptr<uchar>(j - 1);
        const uchar* current  = myImage.ptr<uchar>(j    );
        const uchar* next     = myImage.ptr<uchar>(j + 1);

        uchar* output = Result.ptr<uchar>(j);

        for(int i = nChannels; i < nChannels * (myImage.cols - 1); ++i)
        {
            *output++ = saturate_cast<uchar>(5 * current[i]
                         -current[i - nChannels] 
                         -current[i + nChannels]
                         -previous[i]
                         -next[i]);
        }
    }

    // The previous notation results in undefined pixels on the image borders
    // This is caused by inexistent pixel locations in prevous/next border vals
    // To fix these undefined locations, set all border pixels to 0
    Result.row(0).setTo(Scalar(0));                 // top row
    Result.row(Result.rows - 1).setTo(Scalar(0));   // bottom row
    Result.col(0).setTo(Scalar(0));                 // left column
    Result.col(Result.cols - 1).setTo(Scalar(0));   // right column
}


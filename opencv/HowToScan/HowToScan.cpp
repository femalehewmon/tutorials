// Using unsigned char (8 bit, 0-255) for all 3 color channels will leave us with 16 million possible colors. This large number may be too heavy for our algs.
// In this case, it is common to make a color space reduction but dividing the color space current value with a new input value to end up with fewer colors.
// For example, every value between 0-9 will be assigned the value 0.
// Every value between 10-19 will be assigned the value 10, and so on.
// To do this:
// 	Inew = (Iold/10) * 10;
// 	--> works because fractions are rounded down if char types used
// This should be applied to every pixel to make the color space reduction.
// This is great, expect it uses expensive multiplications and divisions.
// A lookup table will help.

// The following code will step through all 3 methods of adjusting an image pixel by pixel.

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <sstream>

using namespace std;
using namespace cv;

static void help()
{
    cout
        << "\n--------------------------------------------------------------------------" << endl
        << "This program shows how to scan image objects in OpenCV (cv::Mat). As use case"
        << " we take an input image and divide the native color palette (255) with the "  << endl
        << "input. Shows C operator[] method, iterators and at function for on-the-fly item address calculation."<< endl
        << "Usage:"                                                                       << endl
        << "./howToScanImages imageNameToUse divideWith [G]"                              << endl
        << "if you add a G parameter the image is processed in gray scale"                << endl
        << "--------------------------------------------------------------------------"   << endl
        << endl;
}

Mat& ScanImageAndReduceC(Mat& I, const uchar* table);
Mat& ScanImageAndReduceIterator(Mat& I, const uchar* table);
Mat& ScanImageAndReduceRandomAccess(Mat& I, const uchar * table);

int main(int argc, char* argv[])
{
    help();
    if (argc < 3)
    {
        cout << "Not enough parameters" << endl;
        return -1;
    }

    Mat I, J;
    if( argc == 4 && !strcmp(argv[3],"G") )
        I = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
    else
        I = imread(argv[1], CV_LOAD_IMAGE_COLOR);

    if (!I.data)
    {
        cout << "The image" << argv[1] << " could not be loaded." << endl;
        return -1;
    }

    // convert our input string to a number - C++ style
    int divideWidth = 0;
    stringstream s;
    s << argv[2];
    s >> divideWidth;
    if (!s || !divideWidth)
    {
        cout << "Invalid number entered for dividing. " << endl;
        return -1;
    }

    // create lookup table
    uchar table[256];
    for (int i=0; i < 256; ++i)
    {
        table[i] = (uchar)(divideWidth * (i/divideWidth));
    }

    const int times = 100;
    double t;

    // C-Style Scanning
    t = (double)getTickCount();
    for (int i = 0; i < times; ++i)
    {
        cv::Mat clone_i = I.clone();
        J = ScanImageAndReduceC(clone_i, table);
    }

    t = 1000*((double)getTickCount() - t)/getTickFrequency();
    t /= times;

    cout << "Time of reducing with the C operator [] (averaged for "
         << times << " runs): " << t << " milliseconds."<< endl;

    // Iterator Scanning
    t = (double)getTickCount();
    for (int i = 0; i < times; ++i)
    {
        cv::Mat clone_i = I.clone();
        J = ScanImageAndReduceIterator(clone_i, table);
    }

    t = 1000*((double)getTickCount() - t)/getTickFrequency();
    t /= times;

    cout << "Time of reducing with the iterator (averaged for "
        << times << " runs): " << t << " milliseconds."<< endl;

    // Random Access Scanning
    t = (double)getTickCount();
    for (int i = 0; i < times; ++i)
    {
        cv::Mat clone_i = I.clone();
        ScanImageAndReduceRandomAccess(clone_i, table);
    }

    t = 1000*((double)getTickCount() - t)/getTickFrequency();
    t /= times;

    cout << "Time of reducing with the on-the-fly address generation - at function (averaged for "
        << times << " runs): " << t << " milliseconds."<< endl;

    // LUT Scanning
    Mat lookUpTable(1, 256, CV_8U);
    uchar* p = lookUpTable.data;
    for( int i = 0; i < 256; ++i)
        p[i] = table[i];

    t = (double)getTickCount();
    for (int i = 0; i < times; ++i)
        LUT(I, lookUpTable, J);

    t = 1000*((double)getTickCount() - t)/getTickFrequency();
    t /= times;

    cout << "Time of reducing with the LUT function (averaged for "
        << times << " runs): " << t << " milliseconds."<< endl;
    return 0;
}

// C style pointer access to step through and alter matrix: Efficient!
Mat& ScanImageAndReduceC(Mat& I, const uchar* const table)
{
    // accept only char type matrices
    CV_Assert(I.depth() == CV_8U);
    
    int channels = I.channels();

    int nRows = I.rows;
    int nCols = I.cols * channels;

    // check if the matrix stores data in a single continuous row
    // if yes, adjust column and row counts
    if (I.isContinuous())
    {
        nCols *= nRows;
        nRows = 1;
    }

    int i, j;
    uchar* p;
    for (i = 0; i < nRows; ++i)
    {
        p = I.ptr<uchar>(i);
        for (j = 0; j < nCols; ++j){
            p[j] = table[p[j]];
        }
    }
    return I;
}

// Iterator method to step through and alter matrix: Safe!
Mat& ScanImageAndReduceIterator(Mat& I, const uchar* const table)
{
    // accept only char type matrices
    CV_Assert(I.depth() == CV_8U);

    const int channels = I.channels();
    switch(channels)
    {
    case 1:
        {
            MatIterator_<uchar> it, end;
            for (it=I.begin<uchar>(), end=I.end<uchar>(); it != end; ++it)
            {
                *it = table[*it];
            }
            break;
        }
    case 3:
        {
            MatIterator_<Vec3b> it, end;
            for (it=I.begin<Vec3b>(), end=I.end<Vec3b>(); it != end; ++it)
            {
                (*it)[0] = table[(*it)[0]];
                (*it)[1] = table[(*it)[1]];
                (*it)[2] = table[(*it)[2]];
            }
            break;
        }
    }

    return I;
}

// On-the-fly address calculation with reference returning: Not for scanning!
// Made to acquire or midfy random elements in an image, should not be used
// for sequential scanning of all pixels in the image.
Mat& ScanImageAndReduceRandomAccess(Mat& I, const uchar* const table)
{
    // accept only char type matrices
    CV_Assert(I.depth() == CV_8U);
    const int channels = I.channels();
    switch(channels)
    {
    case 1:
        {
            for ( int i = 0; i < I.rows; ++i)
            {
                for (int j = 0; j < I.cols; ++j)
                {
                    I.at<uchar>(i, j) = table[I.at<uchar>(i,j)];
                }
            }
            break;
        }
    case 3:
        {
            Mat_<Vec3b> _I = I;
            for (int i = 0; i < I.rows; ++i)
            {
                for (int j = 0; j < I.cols; ++j)
                {
                    _I(i,j)[0] = table[_I(i,j)[0]];
                    _I(i,j)[1] = table[_I(i,j)[1]];
                    _I(i,j)[2] = table[_I(i,j)[2]];
                }
            }
            I = _I;
            break;
        }
    }

    return I;
}


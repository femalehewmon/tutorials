// This samples shows how to calculate and display the magnitude image of a DFT

// DFT performance is fastest for images sizes that multiples of 2, 3, and 5.
// Therefore, it is a good idea to pad border values to get to such a size.
//      int getOptimalDFTSize(int vecsize), returns the minimum number that is greater than or eqaul to inpu so that the DFT can be processed efficiently

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char ** argv){

    if( argc != 2)
    {
        cout << "Usage: DFT path_to_image" << endl;
        return -1;
    }

    // Read the file
    Mat I = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
    if( I.empty())
    {
        return -1;
    }

    // pad border of image to get an optimal size (multiple of 2,3, or 5)
    // NOTE: when src is a ROI, the copy will use pixels outside of the ROI
    // for the border unless instructed not to 
    Mat padded;
    int m = getOptimalDFTSize( I.rows );
    int n = getOptimalDFTSize( I.cols );
    copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, BORDER_CONSTANT,
            Scalar::all(0));

    // make space for the complex and real values resulting from the DFT
    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    Mat complexI;
    merge(planes, 2, complexI);

    // make the DFT as an in-place calculation (same input and output)
    dft(complexI, complexI);

    // transform the real and complex values to magnitude
    // planes[0] = Re(DFT(I)) 
    // planes[1] = Im(DFT(I)) 
    // void magnitude(inputArray x, inputArray y, outputArray magnitude);
    // mag(I) = sqrt(x(I)^2 + y(I)^2)
    split(complexI, planes);
    magnitude(planes[0], planes[1], planes[0]);
    Mat magI = planes[0];

    // the dynamic range of the Fourier coefficients are too large to be
    // displayed on screen, therefore, we switch to a log scale
    // void log(inputArray src, outputArray dst);
    // log_mag = log(1 + mag)
    magI += Scalar::all(1);
    log(magI, magI);

    // crop out the padded border and rearrange the quadrants so that the
    // origin corresponds with the image center
    magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));
    int cx = magI.cols/2;
    int cy = magI.rows/2;

    Mat q0(magI, Rect(0, 0, cx, cy)); // top-left, create a ROI per quadrant
    Mat q1(magI, Rect(cx, 0, cx, cy)); // top-right
    Mat q2(magI, Rect(0, cy, cx, cy)); // bottom-left
    Mat q3(magI, Rect(cx, cy, cx, cy)); // bottom-right

    Mat tmp;            // swap quadrants (top-left with bottom-right)
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);     // swap quadrants (top-right with bottom-left)
    q2.copyTo(q1);
    tmp.copyTo(q2);

    // normalize the display range to values between 0 - 1
    // to be able to view them in an image 
    normalize(magI, magI, 0, 1, CV_MINMAX);

    // show the result!
    imshow("Input Image", I);
    imshow("spectrum magnitude", magI);
    waitKey();

    return 0;
}

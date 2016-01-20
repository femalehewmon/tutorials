#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    if( argc != 2)
    {
	cout << "Usage: display_image ImageToLoadAndDisplay" << endl;
	return -1;
    }

    // Create a Mat object to store the data of the loaded image 
    Mat image;

    // Read the file
    // CV_LOAD_IMAGE_UNCHANGED loads the image as is
    // CV_LOAD_IMAGE_GRAYSCALE loads the image as an intensity one
    // CV_LOAD_IMAGE_COLOR loads the image in the BGR format -- DEFAULT
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR);

    // Check for invalid input
    if(image.empty())
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    // Create an OpenCV window for display
    // automatically managed by OpenCV once created
    // WINDOW_AUTOSIZE window size takes up the size of the image -- DEFAULT
    //     only option supported if you do not use the Qt backend
    // WINDOW_NORMAL image resizes itself according to window size
    namedWindow( "Happy Fish Display window", WINDOW_AUTOSIZE );

    // Show our image inside it
    //     specify the name of the window and the iamage to load
    imshow( "Happy Fish Display window", image );

    // Wait for a keystroke in the window
    waitKey(0);
    return 0;
}

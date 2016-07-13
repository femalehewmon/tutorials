#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int main( int argc, char** argv )
{
    if( argc != 2)
    {
	printf("Usage: display_image ImageToLoadAndDisplay");
	return -1;
    }

    char* imageName = argv[1];

    // Create a Mat object to store the data of the loaded image 
    Mat image;
    image = imread(imageName, CV_LOAD_IMAGE_COLOR);
    if(!image.data)
    {
	printf("No image data \n");
        return -1;
    }

    // Convert image from BGR to Grayscale
    //     takes in source image, destination image, type of transformation
    Mat gray_image;
    cvtColor(image, gray_image, CV_BGR2GRAY);

    // Save new grayscale image to disk
    imwrite("./Gray_image.jpg", gray_image);

    // Open image to see our grayscale transformation
    namedWindow( "color window", CV_WINDOW_AUTOSIZE );
    namedWindow( "grayscale window", CV_WINDOW_AUTOSIZE );

    imshow("color window", image);
    imshow("grayscale window", gray_image );

    waitKey(0);
    return 0;
}

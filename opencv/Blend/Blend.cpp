// How to perform linear blending on two images:
//      g(x) = (l - a)f_o(x) + af_1(x)
//      --> f_0 is image 0, f_1 is image 1
// Performs a temporal cross-dissolve between two images or vides, as seen in slide shows and film productions

// Alpha value of 0 shows only src0 image
// Alpha value of 1 shows only src1 image

#include <opencv2/opencv.hpp>
#include <highgui.h>
#include <iostream>

using namespace cv;

int main( int argc, char** argv )
{
 double alpha = 0.5; double beta; double input;

 Mat src1, src2, dst;

 /// Ask the user enter alpha
 std::cout<<" Simple Linear Blender "<<std::endl;
 std::cout<<"-----------------------"<<std::endl;
 std::cout<<"* Enter alpha [0-1]: ";
 std::cin>>input;

 /// We use the alpha provided by the user if it is between 0 and 1
 if( input >= 0.0 && input <= 1.0 )
   { alpha = input; }

 /// Read image ( must be the same size, same type )
 src1 = imread("../images/LinuxLogo.jpg");
 src2 = imread("../images/WindowsLogo.jpg");

 if( !src1.data ) { printf("Error loading src1 \n"); return -1; }
 if( !src2.data ) { printf("Error loading src2 \n"); return -1; }

 /// Create Windows
 namedWindow("Linear Blend", 1);

 beta = ( 1.0 - alpha );
 // addWeighted produces:
 //     dst = alpha*src1 + beta*src2 + gamma
 //     --> below, gamma == 0.0 is a scalar added to each sum
 addWeighted( src1, alpha, src2, beta, 0.0, dst);

 imshow( "Linear Blend", dst );

 waitKey(0);
 return 0;
}

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <stdio.h>
using namespace cv;

static void help()
{
    printf("\nThis program demonstrates OpenCV drawing and text output functions.\n"
    "Usage:\n"
    "   ./drawing\n");
}

static Scalar randomColor(RNG& rng)
{
    int icolor = (unsigned)rng;
    return Scalar(icolor&255, (icolor>>8)&255, (icolor>>16)&255);
}

const int DELAY = 5;
const int NUMBER = 10;
const int window_width = 1000;
const int window_height = 700;
const int x1 = -window_width/2;
const int x2 = window_width*3/2;
const int y1 = -height/2;
const int y2 = height*3/2;

int main(int argc, char** argv[])
{

    char window_name[] = "Drawing Demo";

    // create a Random Number Generator object (RNG)
    RNG rng(0xFFFFFFFF);

    // Initialize a matrix filled with zeroes
    Mat image = Mat::zeros(window_height, window_width, CV_8UC3);

    // Show it in a window during DELAY ms
    imshow(window_name, image);

    // Now let's draw some crazy stuff
    // Draw lines
    c = Drawing_Random_Lines(image, window_name, rng);
    if (c != 0) return 0;

    // Draw rectangles
    c = Drawing_Random_Rectangles(image, window_name, rng);
    if (c != 0) return 0;

    // Draw ellipses
    c = Drawing_Random_Ellipses(image, window_name, rng);
    if (c != 0) return 0;

    // Draw polylines
    c = Drawing_Random_Polylines(image, window_name, rng);
    if (c != 0) return 0;

    // Draw polygons
    c = Drawing_Random_Filled_Polygons(image, window_name, rng);
    if (c != 0) return 0;

    // Draw circles
    c = Drawing_Random_Circles(image, window_name, rng);
    if (c != 0) return 0;

    // Display text in random positions 
    c = Drawing_Random_Text(image, window_name, rng);
    if (c != 0) return 0;

    // Display the finale!
    c = Displaying_Big_End(image, window_name, rng);
}

int Displaying_Big_End( Mat image, char* window_name, RNG rng )
{
  Size textsize = getTextSize("OpenCV forever!", CV_FONT_HERSHEY_COMPLEX, 3, 5, 0);
  Point org((window_width - textsize.width)/2, (window_height - textsize.height)/2);
  int lineType = 8;

  Mat image2;

  for( int i = 0; i < 255; i += 2 )
  {
    image2 = image - Scalar::all(i);
    putText( image2, "OpenCV forever!", org, CV_FONT_HERSHEY_COMPLEX, 3,
           Scalar(i, i, 255), 5, lineType );

    imshow( window_name, image2 );
    if( waitKey(DELAY) >= 0 )
      { return -1; }
  }

  return 0;
}

int Displaying_Random_Text( Mat image, char* window_name, RNG rng )
{
  int lineType = 8;

  for ( int i = 1; i < NUMBER; i++ )
  {
    Point org;
    org.x = rng.uniform(x1, x2);
    org.y = rng.uniform(y1, y2);

    putText( image, "Testing text rendering", org, rng.uniform(0,8),
             rng.uniform(0,100)*0.05+0.1, randomColor(rng), rng.uniform(1, 10), lineType);

    imshow( window_name, image );
    if( waitKey(DELAY) >= 0 )
      { return -1; }
  }

  return 0;
}

int Drawing_Random_Lines( Mat image, char* window_name, RNG rng )
{
  int lineType = 8;
  Point pt1, pt2;

    for( int i = 0; i < NUMBER; i++ )
    {
        pt1.x = rng.uniform( x1, x2 );
        pt1.y = rng.uniform( y1, y2 );
        pt2.x = rng.uniform( x1, x2 );
        pt2.y = rng.uniform( y1, y2 );

        line( image, pt1, pt2, randomColor(rng), rng.uniform(1, 10), 8 );
        imshow( window_name, image );
        if( waitKey( DELAY ) >= 0 )
        { return -1; }
    }
    return 0;
}

int Drawing_Random_Rectangles( Mat image, char* window_name, RNG rng )
{
    int lineType = 8;
    for (int i = 0; i < NUMBER; i++)
    {
        Point pt1, pt2;
        pt1.x = rng.uniform(x1, x2);
        pt1.y = rng.uniform(y1, y2);
        pt2.x = rng.uniform(x1, x2);
        pt2.y = rng.uniform(y1, y2);
        int thickness = rng.uniform(-3, 10);

        rectangle( image, pt1, pt2, randomColor(rng), MAX(thickness, -1), lineType );

        imshow(window_name, image);
        if(waitKey(DELAY) >= 0)
            return -1;
    }
    return 0;
}

int Drawing_Random_Ellipses( Mat image, char* window_name, RNG rng )
{
    int lineType = 8;
    for (int i = 0; i < NUMBER; i++)
    {
        Point center;
        center.x = rng.uniform(x1, x2);
        center.y = rng.uniform(y1, y2);
        Size axes;
        axes.width = rng.uniform(0, 200);
        axes.height = rng.uniform(0, 200);
        double angle = rng.uniform(0, 180);

        ellipse( image, center, axes, angle, angle - 100, angle + 200,
                 randomColor(rng), rng.uniform(-1,9), lineType );

        imshow(window_name, image);
        if(waitKey(DELAY) >= 0)
            return -1;
    }
    return 0;
}

int Drawing_Random_Polylines( Mat image, char* window_name, RNG rng )
{
    int lineType = 8;
    for (int i = 0; i< NUMBER; i++)
    {
        Point pt[2][3];
        pt[0][0].x = rng.uniform(x1, x2);
        pt[0][0].y = rng.uniform(y1, y2);
        pt[0][1].x = rng.uniform(x1, x2);
        pt[0][1].y = rng.uniform(y1, y2);
        pt[0][2].x = rng.uniform(x1, x2);
        pt[0][2].y = rng.uniform(y1, y2);
        pt[1][0].x = rng.uniform(x1, x2);
        pt[1][0].y = rng.uniform(y1, y2);
        pt[1][1].x = rng.uniform(x1, x2);
        pt[1][1].y = rng.uniform(y1, y2);
        pt[1][2].x = rng.uniform(x1, x2);
        pt[1][2].y = rng.uniform(y1, y2);
        const Point* ppt[2] = {pt[0], pt[1]};
        int npt[] = {3, 3};

        polylines(image, ppt, npt, 2, true, randomColor(rng), rng.uniform(1,10), lineType);

        imshow(window_name, image);
        if(waitKey(DELAY) >= 0)
            return -1;
    }
    return 0;
}

int Drawing_Random_Filled_Polygons( Mat image, char* window_name, RNG rng )
{
    int lineType = 8;
    for (int i = 0; i< NUMBER; i++)
    {
        Point pt[2][3];
        pt[0][0].x = rng.uniform(x1, x2);
        pt[0][0].y = rng.uniform(y1, y2);
        pt[0][1].x = rng.uniform(x1, x2);
        pt[0][1].y = rng.uniform(y1, y2);
        pt[0][2].x = rng.uniform(x1, x2);
        pt[0][2].y = rng.uniform(y1, y2);
        pt[1][0].x = rng.uniform(x1, x2);
        pt[1][0].y = rng.uniform(y1, y2);
        pt[1][1].x = rng.uniform(x1, x2);
        pt[1][1].y = rng.uniform(y1, y2);
        pt[1][2].x = rng.uniform(x1, x2);
        pt[1][2].y = rng.uniform(y1, y2);
        const Point* ppt[2] = {pt[0], pt[1]};
        int npt[] = {3, 3};

        fillPoly(image, ppt, npt, 2, randomColor(rng), lineType);

        imshow(window_name, image);
        if(waitKey(DELAY) >= 0)
            return -1;
    }
    return 0;
}

int Drawing_Random_Circles( Mat image, char* window_name, RNG rng )
{
    int lineType = 8;
    for (int i = 0; i < NUMBER; i++)
    {
        Point center;
        center.x = rng.uniform(x1, x2);
        center.y = rng.uniform(y1, y2);

        circle(image, center, rng.uniform(0, 300), randomColor(rng),
               rng.uniform(-1, 9), lineType);

        imshow(window_name, image);
        if(waitKey(DELAY) >= 0)
            return -1;
    }
    return 0;
}

int Drawing_Random_Text( Mat image, char* window_name, RNG rng )
{
    int lineType = 8;
    for (int i = 1; i < NUMBER; i++)
    {
        Point org;
        org.x = rng.uniform(x1, x2);
        org.y = rng.uniform(y1, y2);

        putText(image, "Testing text rendering", org, rng.uniform(0,8),
                rng.uniform(0,100)*0.05+0.1, randomColor(rng), rng.uniform(1, 10), lineType);

        imshow(window_name, image);
        if(waitKey(DELAY) >= 0)
            return -1;
    }
    return 0;
}

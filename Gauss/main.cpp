#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

using namespace cv;
using namespace std;

double pixelDistance(double u, double v)
{
    return cv::sqrt(u*u + v*v);
}



double gaussianCoeff(double u, double v, double d0)
{
    double d = pixelDistance(u, v);
    return  1 - cv::exp((-d*d) / (2*d0*d0));// Low Frequency Filter
	
}



cv::Mat createGaussianLowPassFilter(cv::Size size, double cutoffInPixels)
{
    Mat glpf(size, CV_64F);// Float 

    cv::Point center(size.width / 2, size.height / 2);

	for(int v = 0; v < glpf.rows; v++)
    {
		for(int u = 0; u< glpf.cols; u++)
        {
            glpf.at<double>(u, v) = gaussianCoeff(v - center.x, u - center.y, cutoffInPixels);
        }
    }

    return glpf;
}


int main(int /*argc*/, char** /*argv*/)
{

	Mat glpf = createGaussianLowPassFilter(Size(256, 256), 10.0);

	glpf.convertTo(glpf, CV_8UC3, 255.0); //imwrite prints on a 0 to 255 line,converts from float to integers

	imwrite("result.png", glpf);

	cvNamedWindow("glpf",CV_WINDOW_FULLSCREEN);
	
	imshow("glpf", glpf);
	
	waitKey(0);

    return 0;
}
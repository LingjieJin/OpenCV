/*
ref: https://www.w3cschool.cn/opencv/opencv-fmpy2cer.html
*/


#include <iostream>
#include <complex>

#include <opencv4/opencv2/opencv.hpp>

using namespace std;
using namespace cv;


int mandelbrot(const complex<float> &z0, const int max)
{
    complex<float> z = z0;
    for (int t = 0; t < max; t++)
    {
        if (z.real()*z.real() + z.imag()*z.imag() > 4.0f) return t;
        z = z*z + z0;
    }
    return max;
}

int mandelbrotFormula(const complex<float> &z0, const int maxIter=500) 
{
    int value = mandelbrot(z0, maxIter);
    if(maxIter - value == 0)
    {
        return 0;
    }
    return cvRound(sqrt(value / (float) maxIter) * 255);
}

void sequentialMandelbrot(Mat &img, const float x1, const float y1, const float scaleX, const float scaleY)
{
    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            float x0 = j / scaleX + x1;
            float y0 = i / scaleY + y1;
            complex<float> z0(x0, y0);
            uchar value = (uchar) mandelbrotFormula(z0);
            img.ptr<uchar>(i)[j] = value;
        }
    }
}

class ParallelMandelbrot : public ParallelLoopBody
{
public:
    ParallelMandelbrot (Mat &img, const float x1, const float y1, const float scaleX, const float scaleY)
        : m_img(img), m_x1(x1), m_y1(y1), m_scaleX(scaleX), m_scaleY(scaleY)
    {
    }
    virtual void operator ()(const Range& range) const
    {
        for (int r = range.start; r < range.end; r++)
        {
            int i = r / m_img.cols;
            int j = r % m_img.cols;
            float x0 = j / m_scaleX + m_x1;
            float y0 = i / m_scaleY + m_y1;
            complex<float> z0(x0, y0);
            uchar value = (uchar) mandelbrotFormula(z0);
            m_img.ptr<uchar>(i)[j] = value;
        }
    }
    ParallelMandelbrot& operator=(const ParallelMandelbrot &) {
        return *this;
    };
private:
    Mat &m_img;
    float m_x1;
    float m_y1;
    float m_scaleX;
    float m_scaleY;
};

int main()
{
    Mat mandelbrotImg(4800, 5400, CV_8U);
    float x1 = -2.1f, x2 = 0.6f;
    float y1 = -1.2f, y2 = 1.2f;
    float scaleX = mandelbrotImg.cols / (x2 - x1);
    float scaleY = mandelbrotImg.rows / (y2 - y1);


    sequentialMandelbrot(mandelbrotImg, x1, x2, scaleX, scaleY);

    // ParallelMandelbrot parallelMandelbrot(mandelbrotImg, x1, y1, scaleX, scaleY);
    // parallel_for_(Range(0, mandelbrotImg.rows * mandelbrotImg.cols), parallelMandelbrot);

    // lambda
    // parallel_for_(Range(0, mandelbrotImg.rows*mandelbrotImg.cols), [&](const Range& range){
    //     for (int r = range.start; r < range.end; r++)
    //     {
    //         int i = r / mandelbrotImg.cols;
    //         int j = r % mandelbrotImg.cols;
    //         float x0 = j / scaleX + x1;
    //         float y0 = i / scaleY + y1;
    //         complex<float> z0(x0, y0);
    //         uchar value = (uchar) mandelbrotFormula(z0);
    //         mandelbrotImg.ptr<uchar>(i)[j] = value;
    //     }
    // });


    imshow("mandelbrotImg", mandelbrotImg);

    waitKey();

    return 0;
}


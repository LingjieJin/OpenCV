#include <opencv2/opencv.hpp>

cv::Mat norm_0_255(cv::InputArray _src)
{
    cv::Mat src = _src.getMat();
    cv::Mat dst;

    switch (src.channels())
    {
    case 1:
        cv::normalize(_src, dst, 0, 255, cv::NORM_MINMAX, CV_8UC1);
        break;
    case 3:
        cv::normalize(_src, dst, 0, 255, cv::NORM_MINMAX, CV_8UC3);
        break;
    default:
        src.copyTo(dst);
        break;
    }

    return dst;
}
#ifndef imageprocess_hpp
#define imageprocess_hpp


#include <opencv2/opencv.hpp>

#include <vector>

using namespace std;



vector<cv::Mat> cutImage(cv::Mat image, int num, int type);
vector<cv::Mat> cutImage(cv::Mat *image, int num, int type);

cv::Mat catImage(vector<cv::Mat> v, int type);



#endif
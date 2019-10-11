#include "imageprocess.hpp"

vector<cv::Mat> cutImage(cv::Mat image, int num, int type)
{
    int rows = image.rows;
    int cols = image.cols;
    vector<cv::Mat> v;
    if(type == 0)
    {
        // 水平分割
        for (size_t i =0; i<num; i++)
        {
            int start = (int) (rows / num *i);
            int end = (int) (rows / num * (i+1));
            if(i == num -1)
            {
                end = rows-1;
            }
            v.push_back(image.rowRange(start, end));
        }
    }
    else if(type == 1)
    {
        // 垂直分割
        for (size_t i = 0; i < num; i++)
        {
            int star = (int) (cols / num *i);
            int end = (int) (cols / num *(i + 1));
            if (i == num - 1)
            {
                end = cols-1;
            }
            v.push_back(image.colRange(star, end));
        }
    }
    //
    return v;
}

vector<cv::Mat> cutImage(cv::Mat *image, int num, int type)
{
    int rows = image->rows;
    int cols = image->cols;
    vector<cv::Mat> v;
    if(type == 0)
    {
        // 水平分割
        for (size_t i =0; i<num; i++)
        {
            int start = (int) (rows / num *i);
            int end = (int) (rows / num * (i+1));
            if(i == num -1)
            {
                end = rows-1;
            }
            // cv::Mat temp = image.rowRange(start, end);
            v.push_back(image->rowRange(start, end));
        }
    }
    else if(type == 1)
    {
        // 垂直分割
        for (size_t i = 0; i < num; i++)
        {
            int star = (int) (cols / num *i);
            int end = (int) (cols / num *(i + 1));
            if (i == num - 1)
            {
                end = cols-1;
            }
            v.push_back(image->colRange(star, end));
        }
    }
    //
    return v;
}

cv::Mat catImage(vector<cv::Mat> v, int type)
{
    cv::Mat dest= v.at(0);
    for (size_t i = 1; i < v.size(); i++)
    {
        if (type == 0)//水平拼接
        {
            cv::vconcat(dest, v.at(i), dest);
        }
        else if (type == 1)//垂直
        {
            cv::hconcat(dest, v.at(i), dest);
        }
    }
    //
    return dest;
}

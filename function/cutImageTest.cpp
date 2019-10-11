#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;


vector<cv::Mat> cutImage(cv::Mat image, int num, int type);
vector<cv::Mat> cutImage(cv::Mat *image, int num, int type);


int main()
{
    clock_t t1, t2;
    double dif;
    vector<cv::Mat> mats;

    cv::Mat src = cv::imread("../image/1920x1080.jpg");
    printf("src image addr %p .\n", &src);

    t1 = clock();
    mats = cutImage(src, 4, 1);
    t2 = clock();
    dif = (double)(t2-t1) / CLOCKS_PER_SEC;
    printf("1. 1000 次分割图像需要 %f s.\n", dif);
    printf("src image addr %p .\n", &src);
    printf("mats first image addr %p .\n",&mats[0]);


    t1 = clock();
    mats = cutImage(&src, 4, 1);
    t2 = clock();
    dif = (double)(t2 -t1) / CLOCKS_PER_SEC;
    printf("2. 1000 次分割图像需要 %f s.\n", dif);
    printf("mats first image addr %p .\n",&mats[0]);

    return 0;
}



/*
C++: Mat Mat::rowRange(int startrow, int endrow) const
C++: Mat Mat::rowRange(const Range& r) const

Parameters:
- startrow – An inclusive 0-based start index of the row span.// 从0开始的行间距索引
- endrow – An exclusive 0-based ending index of the row span.//终止索引
- r – Range structure containing both the start and the end indices.

The method makes a new header for the specified row span of the matrix. 
Similarly to Mat::row() and Mat::col() , this is an O(1) operation.
函数包括左边界，但是不包括右边界
*/

vector<cv::Mat> cutImage(cv::Mat image, int num, int type)
{
    printf("cut image with \"pass by value\".\n");
    printf("image addr %p .\n", &image);
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
    printf("cut image with \"pass by pointer\".\n");
    printf("image addr %p .\n", image);
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


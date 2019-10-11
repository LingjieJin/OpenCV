#include <opencv2/opencv.hpp>
#include <time.h>

#include <vector>

using namespace std;

vector<cv::Mat> cutImage(cv::Mat image, int num, int type);

int main()
{
    
    int maxCore = 6;
    int calCount = 2000;
    clock_t t1, t2;
    double dif;

    /*************************************************/
    // 计算图片加载速度

    cv::Mat src ;
    t1 = clock();
    src = cv::imread("../image/1920x1080.jpg");
    t2 = clock();
    dif = (double)(t2 - t1) / CLOCKS_PER_SEC;
    printf("加载一张 1920*1080 图片需要 %f s.\n", dif);

    /*********************************************/

    vector<cv::Mat> mats;
    vector<cv::Mat> fg_masks;
    vector<cv::Ptr<cv::BackgroundSubtractorMOG2>> mog2_bgs;
    cv::Mat fg_mask;
    cv::Mat gray_src;
    cv::cvtColor(src, gray_src, cv::COLOR_BGR2GRAY);

    /*
    对比背景处理时间
    */


    /*********************************************************/
    // 1份图像 
    int cutCount = 1;
    
    mats = cutImage(gray_src, cutCount, 1);
    fg_masks = cutImage(gray_src, cutCount, 1);
    mog2_bgs.clear();
    for (size_t i = 0; i < cutCount; i++)
    {
        cv::Ptr<cv::BackgroundSubtractorMOG2> bg = cv::createBackgroundSubtractorMOG2();
        mog2_bgs.push_back(bg);
    }
    
    t1 = clock();
    for (size_t i = 0; i < calCount; i++)
    {
        for (size_t j = 0; j < cutCount; j++)
        {
            mog2_bgs[j]->apply(mats[0], fg_masks[0]);
        }
    }
    t2 = clock();
    dif = (double)(t2 - t1) / CLOCKS_PER_SEC;

    printf("一张 1920*1080 灰度图 分成 %d 份 进行 %d 次 mog2 背景建模需要 %f s.\n", cutCount, calCount, dif);
    
    /*********************************************************/
    // 2份
    cutCount = 2;

    mats = cutImage(gray_src, cutCount, 1);
    fg_masks = cutImage(gray_src, cutCount, 1);
    mog2_bgs.clear();
    for (size_t i = 0; i < cutCount; i++)
    {
        cv::Ptr<cv::BackgroundSubtractorMOG2> bg = cv::createBackgroundSubtractorMOG2();
        mog2_bgs.push_back(bg);
    }

    t1 = clock();
    for (size_t i = 0; i < calCount; i++)
    {
        for (size_t j = 0; j < cutCount; j++)
        {
            mog2_bgs[j]->apply(mats[0], fg_masks[0]);
        }
    }
    t2 = clock();
    dif = (double)(t2 - t1) / CLOCKS_PER_SEC;

    printf("一张 1920*1080 灰度图 分成 %d 份 进行 %d 次 mog2 背景建模需要 %f s.\n", cutCount, calCount, dif);

    /*********************************************************/


     /*********************************************************/
    // 3份
    cutCount = 3;

    mats = cutImage(gray_src, cutCount, 1);
    fg_masks = cutImage(gray_src, cutCount, 1);
    mog2_bgs.clear();
    for (size_t i = 0; i < cutCount; i++)
    {
        cv::Ptr<cv::BackgroundSubtractorMOG2> bg = cv::createBackgroundSubtractorMOG2();
        mog2_bgs.push_back(bg);
    }

    t1 = clock();
    for (size_t i = 0; i < calCount; i++)
    {
        for (size_t j = 0; j < cutCount; j++)
        {
            mog2_bgs[j]->apply(mats[0], fg_masks[0]);
        }
    }
    t2 = clock();
    dif = (double)(t2 - t1) / CLOCKS_PER_SEC;

    printf("一张 1920*1080 灰度图 分成 %d 份 进行 %d 次 mog2 背景建模需要 %f s.\n", cutCount, calCount, dif);

    /*********************************************************/

    /*********************************************************/
    // 4份
    cutCount = 4;

    mats = cutImage(gray_src, cutCount, 1);
    fg_masks = cutImage(gray_src, cutCount, 1);
    mog2_bgs.clear();
    for (size_t i = 0; i < cutCount; i++)
    {
        cv::Ptr<cv::BackgroundSubtractorMOG2> bg = cv::createBackgroundSubtractorMOG2();
        mog2_bgs.push_back(bg);
    }

    t1 = clock();
    for (size_t i = 0; i < calCount; i++)
    {
        for (size_t j = 0; j < cutCount; j++)
        {
            mog2_bgs[j]->apply(mats[0], fg_masks[0]);
        }
    }
    t2 = clock();
    dif = (double)(t2 - t1) / CLOCKS_PER_SEC;

    printf("一张 1920*1080 灰度图 分成 %d 份 进行 %d 次 mog2 背景建模需要 %f s.\n", cutCount, calCount, dif);

    /*********************************************************/

    return 0;
}



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
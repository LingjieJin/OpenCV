//
//  main.cpp
//  camara
//
//  Created by kIng_martin on 2019/4/10.
//  Copyright © 2019 kIng_martin. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class Camera
{
public:
    Camera();
    Camera(string path);
    cv::Mat getFrame();
    
    string getCapInfo();
    //
    // 获取视频的帧率
    string getVideoFPS();
    // 获取视频的宽度
    string getVideoFrameWidth();
    // 获取视频的高度
    string getVideoFrameHeight();
    // 获取视频文件的总帧数
    string getVideoFrameCount();
    //
    
private:
    cv::VideoCapture cap;
    string capInfo;
    
};

Camera::Camera()
{
    this->cap = NULL;
    this->capInfo = "";
}

Camera :: Camera(string path)
{
    this->cap.open(path);
    if(cap.isOpened())
    {
        this->capInfo = "FPS:"+getVideoFPS()+",Width:"+getVideoFrameWidth() +",Height"+getVideoFrameHeight();
    }
    else
    {
        printf("error: cant open the camera!");
        this->cap = NULL;
    }
    
}

cv::Mat Camera :: getFrame()
{
    cv::Mat temp;
    if( !this->cap.read(temp))
    {
        printf("error: cant read image!");
    }
    if(temp.empty())
    {
        printf("error: empty frame!");
        temp = NULL;
    }
    return temp;
}

string Camera::getCapInfo()
{
    return this->capInfo;
}

// get 方法
string Camera::getVideoFPS()
{
    return std::to_string( (int)cap.get(cv::CAP_PROP_FPS) );

}

string Camera::getVideoFrameWidth()
{
    return std::to_string( (int)cap.get(cv::CAP_PROP_FRAME_WIDTH) );

}

string Camera::getVideoFrameHeight()
{
    return  std::to_string( (int)cap.get(cv::CAP_PROP_FRAME_HEIGHT) );

}

string Camera::getVideoFrameCount()
{
    return std::to_string( (int)cap.get(cv::CAP_PROP_FRAME_COUNT) );
}

void showVideoStatusInFrame(cv::Mat img, const string &text);
vector<cv::Mat> calHist(cv::Mat &img);
bool isNight(cv::Mat &img);
cv::Mat convertBGRToHistogramm(cv::Mat &img, int histSize);
cv::Mat convertImageToHistogramm(cv::Mat &src_img, int histSize);

int main(int argc, const char * argv[]) 
{
    
    string path = "rtsp://admin:ab123456:554/h264/ch1/main/av_stream";
    string ipc = "rtsp://admin:ab123456@192.168.10.30/Streaming/Channels/102";
    string ipc_main = "rtsp://admin:ab123456@192.168.10.30/Streaming/Channels/101";

    Camera camera = Camera(anbang_6);
    
    cv::Mat temp;
    while (1)
    {
        temp = camera.getFrame();
        //
        
        //
        Mat hsv ;
        Mat gray;
        cvtColor(temp, hsv, COLOR_BGR2HSV);
        cvtColor(temp, gray, COLOR_BGR2GRAY);
//        int r = temp.rows;
//        int c = temp.cols;
//        int d = temp.depth();
//        int ch = temp.channels();
//        int flags = temp.flags;
//        int dims = temp.dims;
//        printf("image info row:%d, col:%d, depth:%d, ch:%d, dims:%d, flags:%d.\n",r,c,d, ch, dims,flags);
        //
        if (isNight(temp))
        {
            printf("night model.\n");
        }
        else
        {
            printf("day model.\n");
        }
        cv::Mat hist = convertImageToHistogramm(temp, 256);
        cv::Mat hsv_hist = convertImageToHistogramm(hsv, 256);
        cv::Mat gray_hist = convertImageToHistogramm(gray, 256);
        
        namedWindow("src", WINDOW_AUTOSIZE);
        imshow("src", hist);
        namedWindow("hsv", WINDOW_AUTOSIZE);
        imshow("hsv", hsv_hist);
        namedWindow("gray", WINDOW_AUTOSIZE);
        imshow("gray", gray_hist);
        
        //
        showVideoStatusInFrame(temp, camera.getCapInfo());
        cv::imshow("frame", temp);
        char keycode = (char)cv::waitKey(30);
        // get the input from the keyboard
        if (keycode == 'q' || keycode == 27)
            break;
    }
    
    return 0;
}

void showVideoStatusInFrame(cv::Mat img, const string &text)
{
    cv::putText(img, text, cv::Point(15,15), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255,255,255));
    
}

vector<cv::Mat> calHist(cv::Mat &img)
{
    //分割成三通道图像
    vector<Mat> channels;
    split(img, channels);
    
    //设定bin数目
    int histBinNum = 255;
    
    //设定取值范围
    float range[] = {0, 255};
    const float* histRange = {range};
    
    bool uniform = true;
    bool accumulate = false;
    
    //声明三个通道的hist数组
    Mat red_hist, green_hist, blue_hist;
    
    //计算直方图
    calcHist(&channels[0], 1, 0, Mat(), red_hist, 1, &histBinNum, &histRange, uniform, accumulate);
    calcHist(&channels[1], 1, 0, Mat(), green_hist, 1, &histBinNum, &histRange, uniform, accumulate);
    calcHist(&channels[2], 1, 0, Mat(), blue_hist, 1, &histBinNum, &histRange, uniform, accumulate);
    
    //
    vector<Mat> ret;
    ret.push_back(red_hist);
    ret.push_back(green_hist);
    ret.push_back(blue_hist);
    
    return ret;
}

bool isNight(cv::Mat &img)
{
    vector<cv::Mat> channels;
    cv::split(img, channels);
    //
    //设定梯度
    int histSize = 256;
    //设定取值范围
    float range[] = {0, 255};
    const float* histRange = {range};
    //
    bool uniform = true;
    bool accumulate = false;
    //
    //声明三个通道的hist数组
    Mat red_hist, green_hist, blue_hist;
    //计算直方图
    calcHist(&channels[0], 1, 0, Mat(), blue_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&channels[1], 1, 0, Mat(), green_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&channels[2], 1, 0, Mat(), red_hist, 1, &histSize, &histRange, uniform, accumulate);
    //
    int red_sum =0, green_sum = 0, blue_sum =0;
    for (int i =0; i<histSize; i++)
    {
        red_sum += red_hist.at<uchar>(i);
        green_sum += green_hist.at<uchar>(i);
        blue_sum += blue_hist.at<uchar>(i);
    }
//    printf("red:%d, green:%d, blue:%d.\n",red_sum, green_sum, blue_sum);
    //
    if ( (red_sum == green_sum)  && (red_sum == blue_sum) )
    {
        return true;
    }
    return false;
}

cv::Mat convertBGRToHistogramm(cv::Mat &img, int histSize)
{
    //
    cv::Mat hist = cv::Mat(img.rows,img.cols,CV_8UC3,Scalar(0,0,0));
    //
    vector<cv::Mat> channels;
    cv::split(img, channels);
    //
    vector<cv::Scalar> colors;
    colors.push_back(cv::Scalar(255,0,0));
    colors.push_back(cv::Scalar(0,255,0));
    colors.push_back(cv::Scalar(0,0,255));
    //
    //设定取值范围
    float range[] = {0, 255};
    const float* histRange = {range};
    bool uniform = true;
    bool accumulate = false;
    //声明三个通道的hist数组
    Mat red_hist, green_hist, blue_hist;
    
    //计算直方图
    calcHist(&channels[0], 1, 0, Mat(), blue_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&channels[1], 1, 0, Mat(), green_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&channels[2], 1, 0, Mat(), red_hist, 1, &histSize, &histRange, uniform, accumulate);
    //
    //
    int bin_w = cvRound((double)img.cols/histSize);
    //
    normalize(red_hist, red_hist, 0, hist.rows, NORM_MINMAX, -1, Mat());
    normalize(green_hist, green_hist, 0, hist.rows, NORM_MINMAX, -1, Mat());
    normalize(blue_hist, blue_hist, 0, hist.rows, NORM_MINMAX, -1, Mat());
    //
    for(int i = 1; i < histSize; i++)
    {
        line(hist, Point(bin_w*(i-1), img.rows - cvRound(red_hist.at<float>(i-1))),
             Point(bin_w*(i), img.rows - cvRound(red_hist.at<float>(i))), Scalar(0, 0, 255), 2, 8, 0);
        line(hist, Point(bin_w*(i-1), img.rows - cvRound(green_hist.at<float>(i-1))),
             Point(bin_w*(i), img.rows - cvRound(green_hist.at<float>(i))), Scalar(0, 255, 0), 2, 8, 0);
        line(hist, Point(bin_w*(i-1), img.rows - cvRound(blue_hist.at<float>(i-1))),
             Point(bin_w*(i), img.rows - cvRound(blue_hist.at<float>(i))), Scalar(255, 0, 0), 2, 8, 0);
    }
    //
    return hist;
}


cv::Mat convertImageToHistogramm(cv::Mat &src_img, int histSize)
{
    //
    cv::Mat hist = cv::Mat(src_img.rows,src_img.cols,CV_8UC3,Scalar(0,0,0));
    //
    vector<cv::Mat> channels;
    cv::split(src_img, channels);
    //
    vector<cv::Scalar> colors;
    colors.push_back(cv::Scalar(255,0,0));
    colors.push_back(cv::Scalar(0,255,0));
    colors.push_back(cv::Scalar(0,0,255));
    //
    //设定取值范围
    float range[] = {0, 255};
    const float* histRange = {range};
    bool uniform = true;
    bool accumulate = false;
    //
    int bin_w = cvRound((double)src_img.cols/histSize);
    
    //
    cv::Mat hist_temp;
    for (int i=0; i<channels.size(); i++)
    {
        calcHist(&channels[i], 1, 0, cv::Mat(), hist_temp, 1, &histSize, &histRange, uniform, accumulate);
        //
        normalize(hist_temp, hist_temp, 0, hist.rows, cv::NORM_MINMAX, -1, cv::Mat());
        //
        for (int j=1; j<histSize; j++)
        {
            line(hist, Point(bin_w*(j-1), src_img.rows - cvRound(hist_temp.at<float>(j-1))),
                 Point(bin_w*(j), src_img.rows - cvRound(hist_temp.at<float>(j))), colors[i], 2, 8, 0);
        }
    }
    //
    return hist;
}

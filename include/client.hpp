//
//  client.hpp
//  图像捕捉
//
//  Created by 张涵健 on 2018/10/15.
//  Copyright © 2018 张涵健Coder.@. All rights reserved.
//

#ifndef client_hpp
#define client_hpp

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;

#define CHAR_W 6
#define CHAR_H 11


struct c_Range{
    int min;
    int max;
    bool enable;
    c_Range(){
        enable = true;
        min = 0;
        max = 10;
    }
    bool operator == (int a){
        bool k = (a <= max && a>=min);
        if (enable)
            return k;
        else
            return !k;
    }
};

class client{
private:
    string src_name;
    Mat dst;
    int WIDTH;
    int HEIGHT;
    VideoCapture cap;
    bool if_dynamic;
    c_Range color;
    
public:
    void open(string n);
    void write_to_text();
    void outputString(string n);
    void run();
    void randomOutput(string n);
    void dynamic();
    void Video();
    void set_color_range(int, int, bool);
    void set_WIDTH_HEIGHT(int, int);
    void color_to_gray(bool isWrite=true);
};

void video_combine();
void draw_char(Mat& src, int row, int col, int n);
#endif /* client_hpp */

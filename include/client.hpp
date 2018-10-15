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

#define color 20
class client{
private:
    string src_name;
    Mat dst;
    bool if_dynamic;
public:
    void open(string n);
    void outputString(string n);
    void run();
    void ramdomOutput(string n);
    void dynamic();
};
#endif /* client_hpp */

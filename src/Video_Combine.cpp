//
//  Video_Combine.cpp
//  图像捕捉
//
//  Created by 张涵健 on 2018/10/19.
//  Copyright © 2018 张涵健Coder.@. All rights reserved.
//

#include "../include/client.hpp"

void video_combine(){
    VideoCapture cap1;
    VideoCapture cap2;
    cap1.open("1.mp4");
    cap2.open("BAD APPLE (C++).mp4");
    Mat dst;
    Mat src1;
    Mat src2;
    while (1){
        cap1 >> src1;
        cap2 >> src2;
        resize(src1, dst, src1.size());
        imshow("combine", dst);
        waitKey(1);
        resize(src2, dst, src1.size());
        imshow("combine", dst);
        waitKey(1);
    }
}

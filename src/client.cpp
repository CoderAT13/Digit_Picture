//
//  client.cpp
//  图像捕捉
//
//  Created by 张涵健 on 2018/10/15.
//  Copyright © 2018 张涵健Coder.@. All rights reserved.
//

#include "../include/client.hpp"
void client::open(string n){
    src_name = n;
    Mat src = imread(src_name);
    //int resize_height = 150;
    resize(src, dst, Size(100, 30));

}

void client::outputString(string n){
    system("clear");
    int count = 0;
    for (int x=0; x<dst.rows; x++) {
        for (int y=0; y<dst.cols; y++){
            int b = dst.at<Vec3b>(x, y)[0];
            int g = dst.at<Vec3b>(x, y)[1];
            int r = dst.at<Vec3b>(x, y)[2];
            if ((b < color) && (g < color) && (r < color) )
            {
                cout << n[count++];
                if (count == n.length())
                    count = 0;
            }
            else
                cout << ' ';
        }
        cout << '\n';
    }
    usleep(2000000);
}

void client::ramdomOutput(string n){
    system("clear");
    int count = 0;
    srand((unsigned int)time(NULL));
    for (int x=0; x<dst.rows; x++) {
        for (int y=0; y<dst.cols; y++){
            int b = dst.at<Vec3b>(x, y)[0];
            int g = dst.at<Vec3b>(x, y)[1];
            int r = dst.at<Vec3b>(x, y)[2];
            if (b > color && g > color && r > color )
            {
                count = rand()%n.length();
                cout << n[count];
            }
            else
                cout << ' ';
        }
        cout << '\n';
    }
    usleep(10000);

}

void client::dynamic(){
    if_dynamic = true;
}

void client::run(){
    string n;
    system("printf '\e[8;31;100t'");
    if_dynamic = false;
    cout << "Colored Picture to Digit Picture System" << endl;
    cout << "Please input picture name with relative path (If video, input null): ";
    cin >> n;
    cout << "1.Output digit picture with a string in order output" << endl;
    cout << "2.Output digit picture with a string in ramdom order" << endl;
    cout << "3.Dynamic output" << endl;
    cout << "4.Video mod" << endl;
    int op;
    string str;
    cin >> op;
    cout << "Input output's string:";
    cin >> str;
    switch(op){
        case 1:
            open(n);
            outputString(str);
            break;
        case 2:
            open(n);
            ramdomOutput(str);
            break;
        case 3:
            dynamic();
            break;
        case 4:
            Video(str);
            break;
        default:
            cout << "Illegal Input" << endl;
    }
    while (if_dynamic){
        ramdomOutput(str);
    }
}

void client::Video(string n){
    string v_n;
    cout << "Input the video with relative path: ";
    cin >> v_n;
    cap.open(v_n);
    Mat src;
    cap >> src;
    //int resize_height = 150;
    resize(src, dst, Size(100, 30));
    while(!dst.empty()){
        ramdomOutput(n);
        cap >> src;
        resize(src, dst, Size(100, 30));
    }
}

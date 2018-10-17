//
//  client.cpp
//  图像捕捉
//
//  Created by 张涵健 on 2018/10/15.
//  Copyright © 2018 张涵健Coder.@. All rights reserved.
//

#include "../include/client.hpp"
void client::open(string n){
    cout << "Please input picture name with relative path (If video, input null): ";
    cin >> n;
    src_name = n;
    Mat src = imread(src_name);
    //int resize_height = 150;
    resize(src, dst, Size(WIDTH, HEIGHT));

}

void client::outputString(string n){
    system("clear");
    int count = 0;
    for (int x=0; x<dst.rows; x++) {
        for (int y=0; y<dst.cols; y++){
            int b = dst.at<Vec3b>(x, y)[0];
            int g = dst.at<Vec3b>(x, y)[1];
            int r = dst.at<Vec3b>(x, y)[2];
            if (color == b && color == g && color == r )
            {
                cout << n[count++];
                if (count == n.length())
                    count = 0;
            }
            else
                cout << ' ';
        }
        //if (x != dst.rows-1)
            cout << '\n';
    }
    usleep(2000000);
}

void client::randomOutput(string n){
    system("clear");
    int count = 0;
    srand((unsigned int)time(NULL));
    for (int x=0; x<dst.rows; x++) {
        for (int y=0; y<dst.cols; y++){
            int b = dst.at<Vec3b>(x, y)[0];
            int g = dst.at<Vec3b>(x, y)[1];
            int r = dst.at<Vec3b>(x, y)[2];
            if (color == b && color == g && color == r )
            {
                count = rand()%n.length();
                cout << n[count];
            }
            else
                cout << ' ';
        }
        //if (x != dst.rows-1)
            cout << '\n';
    }
    usleep(10000);

}

void client::dynamic(){
    if_dynamic = true;
}

void client::run(){
    string n;
    int min, max;
    bool enable;
    n = "printf '\e[8;" + to_string(HEIGHT+1) + ";" + to_string(WIDTH)+"t'";
    system(n.data());
    if_dynamic = false;
    cout << "Colored Multimedia to Digit Multimedia System" << endl;
    cout << "Set the color you want to be digit or not to be digit (R = G = B)" << endl;
    cout << "Input min: " ; cin >> min;
    cout << "Input max: " ; cin >> max;
    cout << "Enable or not? (1.yes | 0.no) "; cin >> enable;
    set_color_range(min, max, enable);
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
            randomOutput(str);
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
        randomOutput(str);
    }
}

void client::Video(string n){
    string v_n;
    cout << "Input the video with relative path: ";
    cin >> v_n;
    cap.open(v_n);
    Mat src;
    cap >> src;
    //Mat background_src = imread("background.png");
    //Mat background;
    //resize(background_src, background_src, src.size());
    //int resize_height = 150;
    resize(src, dst, Size(WIDTH, HEIGHT));
    while(!dst.empty()){
        /*
        background_src.copyTo(background);
        //ramdomOutput(n);
        int count = 0;
        stringstream ss;
        srand((unsigned int)time(NULL));
        for (int x=0; x<dst.rows; x++) {
            for (int y=0; y<dst.cols; y++){
                int b = dst.at<Vec3b>(x, y)[0];
                int g = dst.at<Vec3b>(x, y)[1];
                int r = dst.at<Vec3b>(x, y)[2];
                if (color == b && color == g && color == r )
                {
                    count = rand()%n.length();
                    ss << n[count];
                }
                else
                    ss << ' ';
            }
            if (x != dst.rows-1)
                ss << '\n';
        }
        string output;
        ss >> output;
        putText( background, output, Point(0, src.rows), 4, 0.1,Scalar( 0, 0, 0 ), 1);
        imshow("Digit video", background);
        waitKey(1000);
         */
        randomOutput(n);
        cap >> src;
        if (!src.empty())
            resize(src, dst, Size(WIDTH, HEIGHT));


    }
}

void client::set_color_range(int min, int max, bool enable){
    color.min = min;
    color.max = max;
    color.enable = enable;
}

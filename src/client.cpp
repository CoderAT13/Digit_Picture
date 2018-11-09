//
//  client.cpp
//  图像捕捉
//
//  Created by 张涵健 on 2018/10/15.
//  Copyright © 2018 张涵健Coder.@. All rights reserved.
//

#include "../include/client.hpp"
const string gray_level = "@8MNHQ&OC?7*+=>!:-;.";

void client::run(){
    string n;
    cout << "1.Picture mod" << endl;
    cout << "2.Video Mod" << endl;
    cout << "3.Write to Test" << endl;
    int op;
    //string str;
    cin >> op;
    switch(op){
        case 1:
            open(n);
            color_to_gray();
            break;
        case 2:
            open(n);
            Video();
            break;
        case 3:
            open(n);
            write_to_text();
            break;
        default:
            cout << "Illegal Input" << endl;
    }

}

void client::open(string n){
    cout << "Please input media name with relative path: ";
    cin >> n;
    src_name = n;
    /*
    for ( int i = 0; i < 20; i++){
        string s = "../data/src_string/" + to_string(i) + ".png";
        Mat src = imread(s);
        s = "../data/dst_string/" + to_string(i) + ".jpg";
        resize(src, src, Size(CHAR_W, CHAR_H));
        imwrite(s, src);
    }
     */
    //Mat src = imread(src_name);
    //int resize_height = 150;
    //resize(src, dst, Size(WIDTH, HEIGHT));
}

void client::Video(){
    cap.open(src_name);
    cap >> dst;
    resize(dst, dst, Size(dst.cols*3/4, dst.rows*3/4));
    int counter = 0;
    int total = cap.get(CV_CAP_PROP_FRAME_COUNT);
    //cout << total << endl;
    //imshow("1", dst);
    //waitKey(1);
    color_to_gray(false);
    //imshow("2", dst);
    //waitKey(1);
    VideoWriter writer("../Output/result.mp4", CV_FOURCC('D', 'I', 'V', 'X'), 60, dst.size());

    //Mat background_src = imread("background.png");
    //Mat background;
    //resize(background_src, background_src, src.size());
    //int resize_height = 150;
    //resize(src, dst, Size(WIDTH, HEIGHT));

    while(!dst.empty()){
        //cvtColor(dst, dst, CV_8U);
        //cout << dst.channels() << endl;
        //cout << dst.channels() << endl;
        cvtColor(dst, dst, CV_GRAY2BGR);
        writer << dst;
        //cout << dst.channels() << endl;
        //writer << dst;
        cap >> dst;

        if (!dst.empty()){
            resize(dst, dst, Size(dst.cols*3/4, dst.rows*3/4));
            color_to_gray(false);
        }
        cout << (double)(counter ++)*100/total << "%" << endl;
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
        //randomOutput(n);
    }
    writer.release();
}

void client::set_color_range(int min, int max, bool enable){
    color.min = min;
    color.max = max;
    color.enable = enable;
}

void client::set_WIDTH_HEIGHT(int w = 100, int h = 30){
    WIDTH = w;
    HEIGHT = h;
}

void client::write_to_text(){
    Mat src = imread(src_name);
    Mat dst;
    ofstream txt;
    txt.open("../Output/result.txt");
    resize(src, dst, Size(255, 255*5));
    for (int x=0; x<dst.rows; x++) {
        for (int y=0; y<dst.cols; y++){
            //int b = dst.at<Vec3b>(x, y)[0];
            //int g = dst.at<Vec3b>(x, y)[1];
            int r = dst.at<Vec3b>(x, y)[2];
            if (r < 150)
                txt << x << " " << y << " " << 0 << " " << 0 << " "<< 0 << endl;
            else
                txt << x << " " << y << " " << 255 << " " << 255 << " "<< 255 << endl;
        }

    }
    txt.close();
}

void client::color_to_gray(bool isWrite){
    //Mat gray_image;
    //dst.copyTo(gray_image);
    //Mat dst;
    if (isWrite){
        Mat src = imread(src_name);
        cvtColor(src, dst, CV_BGR2GRAY);
    }else{
        //dst.convertTo(dst, CV_8UC3);
        //cout<<dst.channels();
        //imshow("1", dst);
        //waitKey(1);

        cvtColor(dst, dst, CV_BGR2GRAY);
    }
    //resize(gray_image, dst, Size(WIDTH, HEIGHT));
    //imshow("dst", dst);
    //waitKey(1);
    //string res = "";
    int RowSize = dst.rows / 100 + 1;
    int ColSize = RowSize/2;
    Mat result;
    resize(dst, result, Size(CHAR_W*dst.cols/ColSize, CHAR_H*dst.rows/RowSize));
    //imshow("result",result);
    //waitKey(1);
    int AvgGray = 0;
    for (int i = 0; i < dst.rows/RowSize; i++){
        int Hoffset = i * RowSize;
        for (int j = 0; j < dst.cols/ColSize; j++){
            AvgGray = 0;
            int Woffset = j * ColSize;
            for (int x = 0; x < RowSize; x++)
            {
                for (int y = 0; y < ColSize; y++)
                {
                    AvgGray += dst.ptr<uchar>(Hoffset + x)[Woffset + y];
                }
            }
            AvgGray /= RowSize * ColSize;
            if ((int)(AvgGray / 12.75) < gray_level.length()){
                //res += gray_level[(int)(AvgGray/12.75)];
                draw_char(result, i, j, (int)(AvgGray / 12.75));
            }
            else{
                draw_char(result, i, j, 20);
            }
            //cout << (int)result.ptr<uchar>(i)[j] << endl;
        }
        //res += "\n";
    }

    if(isWrite)
        imwrite("../Output/Result.png", result);
    result.copyTo(dst);
    //return result;
    /*
    ofstream result;
    result.open("wk.txt");
    result << res;
    result.close();
    cout << "done" << endl;
     */
}

void draw_char(Mat& src, int row, int col, int n){
    int r = row * CHAR_H;
    int c = col * CHAR_W;
    if (n == 20){
        for (int i = r; i < r + CHAR_H; i++){
            for (int j = c; j < c + CHAR_W; j++){
                src.at<uchar>(i,j) = 255;
            }
        }
        return;
    }
    Mat target_char = imread("../data/dst_string" + to_string(n) + ".jpg");

    cvtColor(target_char, target_char, CV_BGR2GRAY);
    for (int i = r; i < r + CHAR_H; i++){
        for (int j = c; j < c + CHAR_W; j++){
            src.at<uchar>(i, j) = target_char.at<uchar>(i - r, j - c);
            //src.ptr<uchar>(i)[j] = 255;
        }
    }
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

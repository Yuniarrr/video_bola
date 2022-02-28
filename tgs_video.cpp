#include <bits/stdc++.h>
#include <opencv2/opencv.hpp> 

using namespace std;
using namespace cv;

int main() {
    VideoCapture vid("Gambar/video.mp4");
    Mat bingkai, hasil_resize, versi_hsv, hit_put;

    int L_H = 0;
    int U_H = 179;
    int L_S = 0;
    int U_S = 255; 
    int L_V = 0;
    int U_V = 255;

    // slider
    namedWindow("video", WINDOW_AUTOSIZE);
    createTrackbar("L_H", "video", &L_H, 179);    
    createTrackbar("U_H", "video", &U_H, 179);
    createTrackbar("L_S", "video", &L_S, 255);
    createTrackbar("U_S", "video", &U_S, 255);
    createTrackbar("L_V", "video", &L_V, 255);
    createTrackbar("U_S", "video", &U_S, 255);

    while (true) {
        vid.read(bingkai);
        resize(bingkai, hasil_resize, Size(), 0.5, 0.5);
        cvtColor(hasil_resize, versi_hsv, COLOR_BGR2HSV);

        inRange(versi_hsv, Scalar(L_H, L_S, L_V), Scalar(U_H, U_S, U_V), hit_put);

        vector<vector<Point>> kontur;
        findContours(hit_put, kontur, RETR_TREE, CHAIN_APPROX_NONE);

        for (int i = 0; i < kontur.size(); i++)
        {
            vector<Point>contours_baru;
            float jari_jari;
            Point2f tengah;
            contours_baru = kontur[i];
            minEnclosingCircle(contours_baru, tengah, jari_jari);

            if (jari_jari > 15 && jari_jari < 50)
            {
                circle(hasil_resize, tengah, jari_jari, Scalar(255, 255, 255), 3);
                printf("x: %2f y: %2f rad: %f \n\n", tengah.x, tengah.y, jari_jari);
            }
            
        }
        
        imshow("Video_1",hasil_resize);
        imshow("Video_2",hit_put);

        // char 32 = space
        if ( (char)32 == (char) waitKey(200) )
        {
            break;
        }
        
    }

    return 0;
}
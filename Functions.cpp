//
// Created by mauri on 02-Dec-19.
//
#include "File.cpp"
void Filter(vector<unsigned char> &imagen,size_t &w,size_t &h,int &a,int &b,const string &path) {
    auto temp = imagen;
    auto colored = [&temp](size_t h, size_t m, size_t w, int a, int b) {
        for (size_t i = h; i < m; i++) {
            for (size_t j = 0; j < w * 4; j += 4) {
                temp[i * w * 4 + j + a] = 0;
                temp[i * w * 4 + j + b] = 0;
            }
        }
    };
    auto end = (h / nt);
    auto initial = 0;
    vector<thread> vt(nt);
    for (auto & i : vt) {
        i = thread(colored, initial, end, w, a, b);
        initial += h / nt;
        end += h / nt;
    }
    for (auto &t: vt)
        t.join();
    encode(path, temp, w, h);
}
void green_filter(vector<unsigned char> imagen,size_t w,size_t h) {
    int a=0;int b=2; string path = "../green_filter.png";
    Filter(imagen,w,h,a,b,path);
}
void red_filter(vector<unsigned char> imagen,size_t w,size_t h) {
    int a=1;int b=2; string path = "../red_filter.png";
    Filter(imagen,w,h,a,b,path);
}
void blue_filter(vector<unsigned char> imagen,size_t w,size_t h) {
    int a=0;int b=2; string path = "../blue_filter.png";
    Filter(imagen,w,h,a,b,path);
}
void rotate(vector<unsigned char> imagen,size_t w,size_t h) {
    auto temp = imagen;
    for (size_t i = 0; i < h; i++) {
        for (size_t j = 0; j < w * 4; j += 4) {
            temp[(i*w*4+j+0)*sin(45)]=temp[i * w * 4 + j + 0]; // Red component
            temp[(i*w*4+j+1)*sin(45)]=temp[i * w * 4 + j + 1];
            temp[(i*w*4+j+2)*sin(45)]=temp[i * w * 4 + j + 2];
            temp[(i*w*4+j+3)*sin(45)]=temp[i * w * 4 + j + 3];
        }
    }
    encode("rotated.png",temp,w,h);
}


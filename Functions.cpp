//
// Created by mauri on 02-Dec-19.
//
#include "Headers.h"
std::vector<unsigned char> decode(string_view filename,
                                  unsigned int& width, unsigned int& height) {

    std::vector<unsigned char> result;
    unsigned error = lodepng::decode(result, width, height, filename.data());
    if (error) {
        std::cerr << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
    }
    return result;
}

void encode(string_view filename, std::vector<unsigned char>& image, unsigned width, unsigned height) {
    unsigned error = lodepng::encode(filename.data(), image, width, height);
    if (error) {
        std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
    }
}
void green_filter(vector<unsigned char> imagen,size_t w,size_t h) {
    auto temp = imagen;
    auto colored=[&temp](size_t h, size_t m, size_t w){
        for (size_t i = h; i < m; i++) {
            for (size_t j = 0; j < w * 4; j += 4) {
                temp[i * w * 4 + j + 0] = 0;
                temp[i * w * 4 + j + 2] = 0;
            }
        }
    };
    auto end=(h/nt);
    auto initial=0;
    vector<thread> vt(nt);
    for (int i=0;i<vt.size();i++){
        vt[i]=thread (colored, initial, end, w);
        initial+=h/nt;
        end+=h/nt;
    }
    for (auto &t: vt)
        t.join();
    encode("green.png",temp,w,h);
}
void red_filter(vector<unsigned char> imagen,size_t w,size_t h) {
    auto temp = imagen;
    auto colored=[&temp](size_t h, size_t m, size_t w){
        for (size_t i = h; i < m; i++) {
            for (size_t j = 0; j < w * 4; j += 4) {
                temp[i * w * 4 + j + 1] = 0;
                temp[i * w * 4 + j + 2] = 0;
            }
        }
    };
    auto end=(h/nt);
    auto initial=0;
    vector<thread> vt(nt);
    for (int i=0;i<vt.size();i++){
        vt[i]=thread (colored, initial, end, w);
        initial+=h/nt;
        end+=h/nt;
    }
    for (auto &t: vt)
        t.join();
    encode("red.png",temp,w,h);
}
void blue_filter(vector<unsigned char> imagen,size_t w,size_t h) {
    auto temp = imagen;
    auto colored=[&temp](size_t h, size_t m, size_t w){
        for (size_t i = h; i < m; i++) {
            for (size_t j = 0; j < w * 4; j += 4) {
                temp[i * w * 4 + j + 0] = 0;
                temp[i * w * 4 + j + 1] = 0;
            }
        }
    };
    auto end=(h/nt);
    auto initial=0;
    vector<thread> vt(nt);
    for (int i=0;i<vt.size();i++){
        vt[i]=thread (colored, initial, end, w);
        initial+=h/nt;
        end+=h/nt;
    }
    for (auto &t: vt)
        t.join();
    encode("blue.png",temp,w,h);
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


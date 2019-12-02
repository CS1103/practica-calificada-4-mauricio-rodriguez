

#include "Headers.h"

using namespace std;

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
void green_filter(vector<unsigned char> imagen,int w,int h) {
    auto temp = imagen;
    auto colored=[&temp](int h, int m, int w){
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
void red_filter(vector<unsigned char> imagen,int w,int h) {
    auto temp = imagen;
    auto colored=[&temp](int h, int m, int w){
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
void blue_filter(vector<unsigned char> imagen,int w,int h) {
    auto temp = imagen;
    auto colored=[&temp](int h, int m, int w){
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
void rotate(vector<unsigned char> imagen,int w,int h) {
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
int main()
{
    unsigned int w;
    unsigned int h;
    auto image = decode("in.png", w, h);
    //green_filter(image,w,h);
    green_filter(image,w,h);
    //blue_filter(image,w,h);
    //rotate(image,w,h);
    // Un comment if you want to check buffer content
    /*for (size_t i = 0; i < h; i++) {
        for (size_t j = 0; j < w * 4; j += 4) {
            int r = image[i * w * 4 + j + 0]; // Red component
            int g = image[i * w * 4 + j + 1]; // Green component
            int b = image[i * w * 4 + j + 2]; // Blue component
            int a = image[i * w * 4 + j + 3]; // Alpha component
            std::cout << r << " ";
            std::cout << g << " ";
            std::cout << b << " ";
            std::cout << a << "|";
        }
        std::cout << endl;
    }
*/
    auto nt = thread::hardware_concurrency();
    auto range =  image.size()/ nt;

    return 0;

}

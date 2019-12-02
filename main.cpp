#include "Functions.cpp"
using namespace std;

int main()
{
    unsigned int w;
    unsigned int h;
    auto image = decode("../in.png", w, h);
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
    return 0;

}

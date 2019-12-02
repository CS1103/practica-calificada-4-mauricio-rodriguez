//
// Created by mauri on 01-Dec-19.
//

#ifndef PC4_HEADERS_H
#define PC4_HEADERS_H
#include <iostream>
#include <vector>
#include <string_view>
#include "lodepng.h"
#include <thread>
#include <cmath>
using namespace std;

auto nt = thread::hardware_concurrency();
vector<unsigned char> decode(string_view filename, unsigned int& width, unsigned int& height);
void encode(string_view filename, std::vector<unsigned char>& image, unsigned width, unsigned height);

#endif //PC4_HEADERS_H

#include "Color.h"
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <algorithm>


Color::Color(float r, float g, float b){
	rgb = glm::vec3(std::min(std::max(r, 0.0f), 1.0f), std::min(std::max(g, 0.0f), 1.0f), std::min(std::max(b, 0.0f), 1.0f));
	alpha = 1.0f;
}

Color::~Color(){

}

// void Color::addRGB(float r, float g, float b){
// 	rgb += glm::vec3(r, g, b);
// }

unsigned char Color::getRed(){
	return (unsigned char) (rgb.x * 255);
}

unsigned char Color::getBlue(){
	return (unsigned char) (rgb.y * 255);
}

unsigned char Color::getGreen(){
	return (unsigned char) (rgb.z * 255);
}

unsigned char Color::getAlpha(){
	return (unsigned char) (alpha * 255);
}

void Color::print(){
	printf("The Color is (%f, %f, %f)\n", rgb.x, rgb.y, rgb.z);
}
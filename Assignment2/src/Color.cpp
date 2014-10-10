#include "Color.h"
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <cmath>


Color::Color(float r, float g, float b){
	rgb = glm::vec3(min(max(r, 0.0f), 1.0f), min(max(g, 0.0f), 1.0f), min(max(b, 0.0f), 1.0f));
	alpha = 1.0f;
}

Color::~Color(){

}

unsigned char Color::getRed(){
	return (unsigned char) rgb.x * 255;
}

unsigned char Color::getBlue(){
	return (unsigned char) rgb.y * 255;
}

unsigned char Color::getGreen(){
	return (unsigned char) rgb.z * 255;
}

unsigned char Color::getAlpha(){
	return (unsigned char) alpha * 255;
}

void Color::print(){
	printf("The Color is (%f, %f, %f)\n", rgb.x, rgb.y, rgb.z);
}
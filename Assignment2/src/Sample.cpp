#include "Sample.h"
#include <cstdlib>
#include <ctime>
#include <cstdio>

Sample::Sample(int i, int j, float u, float v){
	i = i;
	j = j;
	u = u;
	v = v;
}

Sample::~Sample(){

}

int Sample::getI(){
	return i;
}

int Sample::getJ(){
	return j;
}

float Sample::getU(){
	return u;
}

float Sample::getV(){
	return v;
}

void Sample::print(){
	printf("The Sample coordinates (%f, %f)", u , v);
}
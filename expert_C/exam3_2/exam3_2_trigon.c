#include <math.h>

// 헤더 파일을 포함해야 합니다.
// 매크로 PI를 사용하기 위해서입니다.
#include "exam3_2_geometry.h"

double to_radian(double deg){
	return (PI * deg) / 180;
}

double to_degree(double rad){
	return (180 * rad) / PI;
}

double cos_deg(double deg){
	return cos(to_radian(deg));
}

double acos_deg(double deg) {
	return acos(to_radian(deg));
}

double sin_deg(double deg){
	return sin(to_radian(deg));
}

double asin_deg(double deg){
	return asin(to_radian(deg));
}

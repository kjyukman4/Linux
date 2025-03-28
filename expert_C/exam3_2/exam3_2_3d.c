#include <math.h>

// 헤더 파일을 포함해야 합니다.
// 다른 소스 파일에 구현된 polar_pos_2d_t, cartesian_pos_2d_t 등과 삼각함수를 사용하기 위해서입니다.
#include "exam3_2_geometry.h"

cartesian_pos_3d_t convert_to_3d_cartesian_pos(const polar_pos_3d_t* polar_pos){
	cartesian_pos_3d_t result;
	result.x = polar_pos->length * sin_deg(polar_pos->theta) * cos_deg(polar_pos->phi);
	result.y = polar_pos->length * sin_deg(polar_pos->theta) * sin_deg(polar_pos->phi);
	result.z = polar_pos->length * cos_deg(polar_pos->theta);
	return result;
}

polar_pos_3d_t convert_to_3d_polar_pos(const cartesian_pos_3d_t* cartesian_pos){
	polar_pos_3d_t result;
	result.length = sqrt(cartesian_pos->x * cartesian_pos->x + cartesian_pos->y * cartesian_pos->y + cartesian_pos->z * cartesian_pos->z);
	result.theta = to_degree(acos(cartesian_pos->z / result.length));
	result.phi = to_degree(atan(cartesian_pos->y / cartesian_pos->x));
	return result; 
}

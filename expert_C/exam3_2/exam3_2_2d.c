#include <math.h>

// 헤더 파일을 포함해야 합니다.
// 다른 소스 파일에 구현된 polar_pos_2d_t, cartesian_pos_2d_t 등과 삼각함수를 사용하기 위해서입니다.
#include "exam3_2_geometry.h"

cartesian_pos_2d_t convert_to_2d_cartesian_pos(const polar_pos_2d_t* polar_pos) {
	cartesian_pos_2d_t result;
	result.x = polar_pos->length * cos_deg(polar_pos->theta);
	result.y = polar_pos->length * sin_deg(polar_pos->theta);
	return result;
}

polar_pos_2d_t convert_to_2d_polar_pos(const cartesian_pos_2d_t* cartesian_pos) {
	polar_pos_2d_t result;
	result.length = sqrt(cartesian_pos->x * cartesian_pos->x + cartesian_pos->y * cartesian_pos->y);
	result.theta = to_degree(atan(cartesian_pos->y / cartesian_pos->x));
}

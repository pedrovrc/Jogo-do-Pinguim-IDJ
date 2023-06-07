#include "GeneralFunctions.h"

#define _USE_MATH_DEFINES
#include <cmath>

int RandomInt(int lim_lo, int lim_hi) {
	int random = ((int) rand()) / (int) RAND_MAX;
	int diff = lim_hi - lim_lo;
	int r = random * diff;
	return lim_lo + r;
}

float RandomFloat(float lim_lo, float lim_hi) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = lim_hi - lim_lo;
    float r = random * diff;
    return lim_lo + r;
}

float Deg2Rad (float angleDeg) {
	return angleDeg * M_PI/180;
}

float Rad2Deg (float angleRad) {
	return angleRad * 180/M_PI;
}

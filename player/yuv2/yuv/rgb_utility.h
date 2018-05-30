#pragma once

#ifndef _RGB_UTILITY_H_
#define _RGB_UTILITY_H_

#include "stdint.h"

class RgbUtility {
public:
	RgbUtility();
	~RgbUtility();

	static void RgbCombine(uint32_t width, uint32_t height, int image_num, uint8_t *img[], uint8_t *output_rgb);
private:
};

#endif  //_RGB_UTILITY_H_
#include "stdafx.h"
#include "stdint.h"

#include "stdlib.h"

#include "rgb_utility.h"

RgbUtility::RgbUtility(void)
{
	return;
}

RgbUtility::~RgbUtility(void)
{
	return;
}
uint8_t *RgbUtility::RgbCombine(uint32_t width, uint32_t height, int image_num, uint8_t *img[])
{
	uint8_t *output_rgb = (uint8_t*)malloc(width * height * 3 * 4);
	if (output_rgb == NULL) {
		//–{“–‚ÍƒGƒ‰[ˆ—
	}

	if (image_num == 1) {
		memcpy(output_rgb, img[0], width * height * 3);
	}
	else if (image_num == 2) {
		uint8_t *rgb_pointer = output_rgb;
		for (uint32_t i = 0; i < height; i++) {
			memcpy(rgb_pointer, img[0] + ((width * 3) * i), width * 3);
			rgb_pointer += width * 3;
			memcpy(rgb_pointer, img[1] + ((width * 3) * i), width * 3);
			rgb_pointer += width * 3;
		}
	}
	else if (image_num == 3) {
		uint8_t *rgb_pointer = output_rgb;
		for (uint32_t i = 0; i < height; i++) {
			memcpy(rgb_pointer, img[0] + ((width * 3) * i), width * 3);
			rgb_pointer += width * 3;
			memcpy(rgb_pointer, img[1] + ((width * 3) * i), width * 3);
			rgb_pointer += width * 3;
		}
		for (uint32_t i = 0; i < height; i++) {
			memcpy(rgb_pointer, img[2] + ((width * 3) * i), width * 3);
			rgb_pointer += width * 3;
//			memcpy(rgb_pointer, img[3] + ((width * 3) * i), width * 3);
			rgb_pointer += width * 3;
		}

	}
	else {
		uint8_t *rgb_pointer = output_rgb;
		for (uint32_t i = 0; i < height; i++) {
			memcpy(rgb_pointer, img[0] + ((width * 3) * i), width * 3);
			rgb_pointer += width * 3;
			memcpy(rgb_pointer, img[1] + ((width * 3) * i), width * 3);
			rgb_pointer += width * 3;
		}
		for (uint32_t i = 0; i < height; i++) {
			memcpy(rgb_pointer, img[2] + ((width * 3) * i), width * 3);
			rgb_pointer += width * 3;
			//			memcpy(rgb_pointer, img[3] + ((width * 3) * i), width * 3);
			rgb_pointer += width * 3;
		}

	}
	return output_rgb;
}





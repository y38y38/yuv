#include "stdio.h"
#include "stdbool.h"
#include "cmm422.h"

#include "cmm2cmm.h"

int inputFrameSize(int width, int height) {
    return cmm422GetFrameSize(width, height);
}

int outputFrameSize(int width, int height) {
    return cmm422GetFrameSize(width, height);
}

int cmm2cmm(unsigned char* input, unsigned char *output,  int input_width, int input_height, int output_width,int output_height)
{
    int i;
    int j;
    unsigned short  value;
    unsigned short *output_short = (unsigned short*)output;

	int width_scale = input_width / output_width;
	int height_scale = input_height / output_height;

    //y
	int set_pixel = 0;
    for(i = 0;i < input_height;i++) {
		if (i < (output_height * height_scale)) {
			if (!(i % height_scale)) {
		        for(j = 0;j < input_width;j++) {
					if (j < (output_width * width_scale)) {
	 					if (!(j % width_scale)) {
		    		        cmm422GetYPixel((unsigned short*)input, ((i * input_width) + j), &value, input_width, input_width);
//							printf("%d ", value);
       			    	 	cmm422SetYPixel((unsigned short*)output, set_pixel, value, output_width, output_height);
							set_pixel++;
						}
					}
        		}
			}
		}
    }

    int c_input_width = input_width / 2;
    int c_input_height = input_height;
    
    int c_output_width = output_width / 2;
    int c_output_height = output_height;




    //cb
	set_pixel = 0;
    for(i = 0;i < c_input_height;i++) {
		if (i < (c_output_height * height_scale)) {
			if (!(i % height_scale)) {
		        for(j = 0;j < c_input_width;j++) {
					if (j < (c_output_width * width_scale)) {
	 					if (!(j % width_scale)) {
		    		        cmm422GetCbPixel((unsigned short*)input, ((i * c_input_width) + j), &value, c_input_width, c_input_height);
							//printf("%x\n", value);
       			    	 	cmm422SetCbPixel((unsigned short*)output, set_pixel, value, c_output_width, c_output_height);
							set_pixel++;
						}
					}
        		}
			}
		}
    }
	set_pixel = 0;
    for(i = 0;i < c_input_height;i++) {
		if (i < (c_output_height * height_scale)) {
			if (!(i % height_scale)) {
		        for(j = 0;j < c_input_width;j++) {
					if (j < (c_output_width * width_scale)) {
	 					if (!(j % width_scale)) {
		    		        cmm422GetCrPixel((unsigned short*)input, ((i * c_input_width) + j), &value, c_input_width, c_input_height);
							cmm422SetCrPixel((unsigned short*)output, set_pixel, value, c_output_width, c_output_height);
							set_pixel++;
						}
					}
        		}
			}
		}
    }

    return 0;
}


#pragma once

class YuvRgb {
public:
	YuvRgb(void) {return;};
	~YuvRgb(void) { return; }
	void ypbpr2rgb(short y, short pb, short pr, unsigned char *rgb);

private:

};
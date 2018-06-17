#pragma once

#ifndef __RTP_HEADER__
#define __RTP_HEADER__

#include <stdint.h>


struct RtpExtendHeader {
	uint16_t extended_sequnece_number;
	uint16_t srd_length;
	uint16_t f : 1;
	uint16_t srd_row_number : 15;
	uint16_t c : 1;
	uint16_t srd_offset : 15;
};
struct RtpHeader {
	uint8_t v : 2;
	uint8_t p : 1;
	uint8_t x : 1;
	uint8_t cc : 4;
	uint8_t m : 1;
	uint8_t pt : 7;
	uint16_t sequence_number;
	uint32_t time_stap;
	uint32_t ssrc;
};

#endif //__RTP_HEADER__



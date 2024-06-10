#pragma once
#include <iostream>

struct RGBData 
{
	uint16_t red = 0;
	uint16_t green = 0;
	uint16_t blue = 0;
	RGBData(uint16_t red, uint16_t green, uint16_t blue);
	RGBData() = default;
};
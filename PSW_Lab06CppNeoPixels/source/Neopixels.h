#ifndef NEOPIXELS_H_
#define NEOPIXELS_H_
#include <vector>
#include <algorithm>
#include "fsl_spi.h"
#define GET_BIT(k, n) (k & (1 << (n)))
#define SET_BIT(k, n) (k |= (1 << (n)))
#define CLR_BIT(k, n) (k &= ~(1 << (n)))

#define CODE_0 0b10000 //16
#define CODE_1 0b11100 // 28
class Neopixels {
public:
	Neopixels(SPI_Type *base);
	virtual ~Neopixels();
	uint32_t getLedsNumber();
	void addColor(uint32_t color);
	void writeColors(std::vector<uint32_t> color);
	void sendData();
	void shiftLeft();
	void shiftRight();
private:
	SPI_Type *SPI_base=NULL;
	std::vector<uint32_t> buffer;
};
#endif /* NEOPIXELS_H_ */

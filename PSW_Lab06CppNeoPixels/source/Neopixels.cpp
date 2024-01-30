#include <Neopixels.h>
Neopixels::Neopixels(SPI_Type *base) {
	SPI_base = base;
}
Neopixels::~Neopixels() {
	buffer.clear();
}
uint32_t Neopixels::getLedsNumber() {
	return buffer.size();
}
void Neopixels::addColor(uint32_t color) {
	buffer.push_back(color);
}
void Neopixels::writeColors(std::vector<uint32_t> color) {
	buffer.clear();
	buffer = color;
}
void Neopixels::sendData() {
	uint16_t LED_data=0;
	uint32_t configFlags=0U;
	/* ignore RX */
	configFlags |= (1<< 22);
	for(uint32_t j=0; j<buffer.size(); j++) {
		for(int i=23; i>=0; i--) {
			LED_data = GET_BIT(buffer[j], i) ? CODE_1 : CODE_0;
			while(!(SPI_GetStatusFlags(SPI_base) & kSPI_TxNotFullFlag))
				;
			SPI_WriteData(SPI_base, LED_data, configFlags);
		}
	}
	// Reset >= 50 us
	LED_data=0;
	for(int j=0; j<60; j++) {
		while(!(SPI_GetStatusFlags(SPI_base) & kSPI_TxNotFullFlag))
			;
		SPI_WriteData(SPI_base, LED_data, configFlags);
	}
}
void Neopixels::shiftLeft() {
	std::rotate(buffer.begin(), buffer.begin() + 1, buffer.end());
	sendData();
}
void Neopixels::shiftRight() {
	std::rotate(buffer.rbegin(), buffer.rbegin() + 1, buffer.rend());
	sendData();
}

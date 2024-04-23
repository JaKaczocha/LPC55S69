
#ifndef LPC25HB_H_
#define LPC25HB_H_

#include "fsl_i2c.h"


// Inicjalizacja czujnika LPS25HB
// Obudzenie i automatyczne pomiary
// return - HAL_OK lub HAL_ERROR
status_t lps25hb_init(void);

// Odczyt temperatury
// return - wynik w stopniach C
float lps25hb_read_temp(void);

// Odczyt ciśnienia
// reuturn - wynik w hPa
float lps25hb_read_pressure(void);

bool I2C_ReadAccelWhoAmI(void);
#endif /* LPC25HB_H_ */

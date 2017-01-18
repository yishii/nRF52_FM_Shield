#ifndef __IODEFINE_H__
#define __IODEFINE_H__

// TODO: Values are just defined. need to confirm with the defines of Arduino PF
#define HIGH 1
#define LOW 0
#define OUTPUT 1
#define INPUT 0
#define INPUT_PULLUP 2

#define IO_YMF_RD (24)
#define IO_YMF_WR (23)
#define IO_YMF_CS (22)
#define IO_YMF_ADDR_0 (26)
#define IO_YMF_ADDR_1 (25)
#define IO_YMF_DATA_0 (11)
#define IO_YMF_DATA_1 (12)
#define IO_YMF_DATA_2 (13)
#define IO_YMF_DATA_3 (14)
#define IO_YMF_DATA_4 (15)
#define IO_YMF_DATA_5 (16)
#define IO_YMF_DATA_6 (17)
#define IO_YMF_DATA_7 (18)
#define IO_YMF_RESET (27)

#define IO_LED_1 (17)
#define IO_LED_2 (18)
#define IO_LED_3 (19)
#define IO_LED_4 (20)

#ifdef __cplusplus
extern "C" {
#endif
void pinMode(uint32_t pin, uint32_t state);
void digitalWrite(uint32_t pin, uint32_t value);
uint32_t digitalRead(uint32_t pin);
#ifdef __cplusplus
}
#endif

#endif /* __IODEFINE_H__ */

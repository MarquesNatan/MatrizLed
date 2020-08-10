#ifndef SCROLLING_TEXT_H
#define SCROLLING_TEXT_H
/*============================================================================*/


void WriteMatrix(uint8_t matrix[][8], uint8_t vectorBytes[8]);
void ScrollingDisplay(uint8_t matrix[][8], int8_t* line, int8_t* posBit);




/*============================================================================*/
#endif /*SCROLLING_TEXT_H*/
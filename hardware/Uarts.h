#ifndef _Uarts_H
#define _Uarts_H

#include "public.h"
#include "stdio.h"
void UartsInit(int baudrate, int uartsId);
void NvicConfiguration(int uartsId);
#endif

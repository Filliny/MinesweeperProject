#pragma once

#ifdef _M_AMD64

void printSys(int sys = 64);

#else

void printSys(int sys = 32,int def= 0);

#endif // WIN64



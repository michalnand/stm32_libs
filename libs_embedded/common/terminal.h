#ifndef _TERMINAL_H_
#define _TERMINAL_H_

#include <stdint.h>

class Terminal
{
  public:
    Terminal();
    virtual ~Terminal();

    void init();

    void putc(char c);
    void puts(const char *s);
    void puts(char *s);
    void puti(int32_t n);
    void putui(uint32_t n);
    void putx(uint32_t n);
    void putf(float n, unsigned char decimal_places);
    void printf(const char *str, ...);

    Terminal& operator<< (const char *op);
    Terminal& operator<< (char *op);
    Terminal& operator<< (int op);
    Terminal& operator<< (unsigned int op);
    Terminal& operator<< (int32_t op);
    Terminal& operator<< (uint32_t op);
    Terminal& operator<< (float op);  
    Terminal& operator<< (bool op);
};

#endif

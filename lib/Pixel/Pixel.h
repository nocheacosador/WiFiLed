#pragma once

#include <stdint.h>
#include <stdio.h>

struct Color
{
    uint8_t r, g, b;
    
    uint8_t& operator[] (int i) 
    {
        switch (i)
        {
        case 1:
            return g;
        case 2:
            return b; 
        default:
            return r;
        }
    };

    char* str()
    {
        static char buf[8];
        sprintf(buf, "#%02X%02X%02X", r, g, b);
        return buf;
    }
};

class Pixel
{
public:
    Pixel(uint8_t r, uint8_t g, uint8_t b);

    void Write(uint8_t r, uint8_t g, uint8_t b);
    void Write(Color rgb);

private:
    uint8_t m_RedPin, m_GreenPin, m_BluePin;
};
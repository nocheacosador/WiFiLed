#include "Pixel.h"

#include <Arduino.h>

Pixel::Pixel(uint8_t r, uint8_t g, uint8_t b) : m_RedPin(r), m_GreenPin(g), m_BluePin(b)
{
    analogWriteResolution(8);
    pinMode(m_RedPin, OUTPUT);
    pinMode(m_GreenPin, OUTPUT);
    pinMode(m_BluePin, OUTPUT);
    Write(0, 0, 0);
}

void Pixel::Write(uint8_t r, uint8_t g, uint8_t b)
{
    analogWrite(m_RedPin, r);
    analogWrite(m_GreenPin, g);
    analogWrite(m_BluePin, b);
}

void Pixel::Write(Color color)
{
    analogWrite(m_RedPin, color.r);
    analogWrite(m_GreenPin, color.g);
    analogWrite(m_BluePin, color.b);
}
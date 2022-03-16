#ifndef FONT8X8_BASIC_H
#define FONT8X8_BASIC_H

// Following font is borrowed from
// https://github.com/dhepper/font8x8/blob/master/font8x8_basic.h

uint8_t ASCII[128][8] = {
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // 0 (null)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // 1 (start of heading)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // 2 (start of text)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // 3 (end of text)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // 4 (end of transmission)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // 5 (enquiry)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // 6 (acknowledge)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // 7 (bell)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // 8 (backspace)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // 9 (horizontal tab)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // A (line feed)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // B (vertical tab)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // C (form feed)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // D (carriage return)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // E (shift out)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // F (shift in)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // 10 (data link escape)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // 11 (device control 1)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // 12 (device control 2)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // 13 (device control 3)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // 14 (device control 4)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // 15 (negative acknowledge)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // 16 (synchronous idle)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // 17 (end of trans. block)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // 18 (cancel)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // 19 (end of medium)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // 1A (substitute)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // 1B (escape)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // 1C (file separator)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // 1D (group separator)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // 1E (record separator)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // 1F (unit separator)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // 20 (space)
    { 0x00, 0x00, 0x06, 0x5F, 0x5F, 0x06, 0x00, 0x00 },   // 21 (!)
    { 0x00, 0x03, 0x03, 0x00, 0x03, 0x03, 0x00, 0x00 },   // 22 (")
    { 0x14, 0x7F, 0x7F, 0x14, 0x7F, 0x7F, 0x14, 0x00 },   // 23 (#)
    { 0x24, 0x2E, 0x6B, 0x6B, 0x3A, 0x12, 0x00, 0x00 },   // 24 ($)
    { 0x46, 0x66, 0x30, 0x18, 0x0C, 0x66, 0x62, 0x00 },   // 25 (%)
    { 0x30, 0x7A, 0x4F, 0x5D, 0x37, 0x7A, 0x48, 0x00 },   // 26 (&)
    { 0x04, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00 },   // 27 (')
    { 0x00, 0x1C, 0x3E, 0x63, 0x41, 0x00, 0x00, 0x00 },   // 28 (()
    { 0x00, 0x41, 0x63, 0x3E, 0x1C, 0x00, 0x00, 0x00 },   // 29 ())
    { 0x08, 0x2A, 0x3E, 0x1C, 0x1C, 0x3E, 0x2A, 0x08 },   // 2A (*)
    { 0x08, 0x08, 0x3E, 0x3E, 0x08, 0x08, 0x00, 0x00 },   // 2B (+)
    { 0x00, 0x80, 0xE0, 0x60, 0x00, 0x00, 0x00, 0x00 },   // 2C (,)
    { 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00 },   // 2D (-)
    { 0x00, 0x00, 0x60, 0x60, 0x00, 0x00, 0x00, 0x00 },   // 2E (.)
    { 0x60, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x01, 0x00 },   // 2F (/)
    { 0x3E, 0x7F, 0x71, 0x59, 0x4D, 0x7F, 0x3E, 0x00 },   // 30 (0)
    { 0x40, 0x42, 0x7F, 0x7F, 0x40, 0x40, 0x00, 0x00 },   // 31 (1)
    { 0x62, 0x73, 0x59, 0x49, 0x6F, 0x66, 0x00, 0x00 },   // 32 (2)
    { 0x22, 0x63, 0x49, 0x49, 0x7F, 0x36, 0x00, 0x00 },   // 33 (3)
    { 0x18, 0x1C, 0x16, 0x53, 0x7F, 0x7F, 0x50, 0x00 },   // 34 (4)
    { 0x27, 0x67, 0x45, 0x45, 0x7D, 0x39, 0x00, 0x00 },   // 35 (5)
    { 0x3C, 0x7E, 0x4B, 0x49, 0x79, 0x30, 0x00, 0x00 },   // 36 (6)
    { 0x03, 0x03, 0x71, 0x79, 0x0F, 0x07, 0x00, 0x00 },   // 37 (7)
    { 0x36, 0x7F, 0x49, 0x49, 0x7F, 0x36, 0x00, 0x00 },   // 38 (8)
    { 0x06, 0x4F, 0x49, 0x69, 0x3F, 0x1E, 0x00, 0x00 },   // 39 (9)
    { 0x00, 0x00, 0x66, 0x66, 0x00, 0x00, 0x00, 0x00 },   // 3A (:)
    { 0x00, 0x80, 0xE6, 0x66, 0x00, 0x00, 0x00, 0x00 },   // 3B (;)
    { 0x08, 0x1C, 0x36, 0x63, 0x41, 0x00, 0x00, 0x00 },   // 3C (<)
    { 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x00, 0x00 },   // 3D (=)
    { 0x00, 0x41, 0x63, 0x36, 0x1C, 0x08, 0x00, 0x00 },   // 3E (>)
    { 0x02, 0x03, 0x51, 0x59, 0x0F, 0x06, 0x00, 0x00 },   // 3F (?)
    { 0x3E, 0x7F, 0x41, 0x5D, 0x5D, 0x1F, 0x1E, 0x00 },   // 40 (@)
    { 0x7C, 0x7E, 0x13, 0x13, 0x7E, 0x7C, 0x00, 0x00 },   // 41 (A)
    { 0x41, 0x7F, 0x7F, 0x49, 0x49, 0x7F, 0x36, 0x00 },   // 42 (B)
    { 0x1C, 0x3E, 0x63, 0x41, 0x41, 0x63, 0x22, 0x00 },   // 43 (C)
    { 0x41, 0x7F, 0x7F, 0x41, 0x63, 0x3E, 0x1C, 0x00 },   // 44 (D)
    { 0x41, 0x7F, 0x7F, 0x49, 0x5D, 0x41, 0x63, 0x00 },   // 45 (E)
    { 0x41, 0x7F, 0x7F, 0x49, 0x1D, 0x01, 0x03, 0x00 },   // 46 (F)
    { 0x1C, 0x3E, 0x63, 0x41, 0x51, 0x73, 0x72, 0x00 },   // 47 (G)
    { 0x7F, 0x7F, 0x08, 0x08, 0x7F, 0x7F, 0x00, 0x00 },   // 48 (H)
    { 0x00, 0x41, 0x7F, 0x7F, 0x41, 0x00, 0x00, 0x00 },   // 49 (I)
    { 0x30, 0x70, 0x40, 0x41, 0x7F, 0x3F, 0x01, 0x00 },   // 4A (J)
    { 0x41, 0x7F, 0x7F, 0x08, 0x1C, 0x77, 0x63, 0x00 },   // 4B (K)
    { 0x41, 0x7F, 0x7F, 0x41, 0x40, 0x60, 0x70, 0x00 },   // 4C (L)
    { 0x7F, 0x7F, 0x0E, 0x1C, 0x0E, 0x7F, 0x7F, 0x00 },   // 4D (M)
    { 0x7F, 0x7F, 0x06, 0x0C, 0x18, 0x7F, 0x7F, 0x00 },   // 4E (N)
    { 0x1C, 0x3E, 0x63, 0x41, 0x63, 0x3E, 0x1C, 0x00 },   // 4F (O)
    { 0x41, 0x7F, 0x7F, 0x49, 0x09, 0x0F, 0x06, 0x00 },   // 50 (P)
    { 0x1E, 0x3F, 0x21, 0x71, 0x7F, 0x5E, 0x00, 0x00 },   // 51 (Q)
    { 0x41, 0x7F, 0x7F, 0x09, 0x19, 0x7F, 0x66, 0x00 },   // 52 (R)
    { 0x26, 0x6F, 0x4D, 0x59, 0x73, 0x32, 0x00, 0x00 },   // 53 (S)
    { 0x03, 0x41, 0x7F, 0x7F, 0x41, 0x03, 0x00, 0x00 },   // 54 (T)
    { 0x7F, 0x7F, 0x40, 0x40, 0x7F, 0x7F, 0x00, 0x00 },   // 55 (U)
    { 0x1F, 0x3F, 0x60, 0x60, 0x3F, 0x1F, 0x00, 0x00 },   // 56 (V)
    { 0x7F, 0x7F, 0x30, 0x18, 0x30, 0x7F, 0x7F, 0x00 },   // 57 (W)
    { 0x43, 0x67, 0x3C, 0x18, 0x3C, 0x67, 0x43, 0x00 },   // 58 (X)
    { 0x07, 0x4F, 0x78, 0x78, 0x4F, 0x07, 0x00, 0x00 },   // 59 (Y)
    { 0x47, 0x63, 0x71, 0x59, 0x4D, 0x67, 0x73, 0x00 },   // 5A (Z)
    { 0x00, 0x7F, 0x7F, 0x41, 0x41, 0x00, 0x00, 0x00 },   // 5B ([)
    { 0x01, 0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x00 },   // 5C (\)
    { 0x00, 0x41, 0x41, 0x7F, 0x7F, 0x00, 0x00, 0x00 },   // 5D (])
    { 0x08, 0x0C, 0x06, 0x03, 0x06, 0x0C, 0x08, 0x00 },   // 5E (^)
    { 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80 },   // 5F (_)
    { 0x00, 0x00, 0x03, 0x07, 0x04, 0x00, 0x00, 0x00 },   // 60 (`)
    { 0x20, 0x74, 0x54, 0x54, 0x3C, 0x78, 0x40, 0x00 },   // 61 (a)
    { 0x41, 0x7F, 0x3F, 0x48, 0x48, 0x78, 0x30, 0x00 },   // 62 (b)
    { 0x38, 0x7C, 0x44, 0x44, 0x6C, 0x28, 0x00, 0x00 },   // 63 (c)
    { 0x30, 0x78, 0x48, 0x49, 0x3F, 0x7F, 0x40, 0x00 },   // 64 (d)
    { 0x38, 0x7C, 0x54, 0x54, 0x5C, 0x18, 0x00, 0x00 },   // 65 (e)
    { 0x48, 0x7E, 0x7F, 0x49, 0x03, 0x02, 0x00, 0x00 },   // 66 (f)
    { 0x98, 0xBC, 0xA4, 0xA4, 0xF8, 0x7C, 0x04, 0x00 },   // 67 (g)
    { 0x41, 0x7F, 0x7F, 0x08, 0x04, 0x7C, 0x78, 0x00 },   // 68 (h)
    { 0x00, 0x44, 0x7D, 0x7D, 0x40, 0x00, 0x00, 0x00 },   // 69 (i)
    { 0x60, 0xE0, 0x80, 0x80, 0xFD, 0x7D, 0x00, 0x00 },   // 6A (j)
    { 0x41, 0x7F, 0x7F, 0x10, 0x38, 0x6C, 0x44, 0x00 },   // 6B (k)
    { 0x00, 0x41, 0x7F, 0x7F, 0x40, 0x00, 0x00, 0x00 },   // 6C (l)
    { 0x7C, 0x7C, 0x18, 0x38, 0x1C, 0x7C, 0x78, 0x00 },   // 6D (m)
    { 0x7C, 0x7C, 0x04, 0x04, 0x7C, 0x78, 0x00, 0x00 },   // 6E (n)
    { 0x38, 0x7C, 0x44, 0x44, 0x7C, 0x38, 0x00, 0x00 },   // 6F (o)
    { 0x84, 0xFC, 0xF8, 0xA4, 0x24, 0x3C, 0x18, 0x00 },   // 70 (p)
    { 0x18, 0x3C, 0x24, 0xA4, 0xF8, 0xFC, 0x84, 0x00 },   // 71 (q)
    { 0x44, 0x7C, 0x78, 0x4C, 0x04, 0x1C, 0x18, 0x00 },   // 72 (r)
    { 0x48, 0x5C, 0x54, 0x54, 0x74, 0x24, 0x00, 0x00 },   // 73 (s)
    { 0x00, 0x04, 0x3E, 0x7F, 0x44, 0x24, 0x00, 0x00 },   // 74 (t)
    { 0x3C, 0x7C, 0x40, 0x40, 0x3C, 0x7C, 0x40, 0x00 },   // 75 (u)
    { 0x1C, 0x3C, 0x60, 0x60, 0x3C, 0x1C, 0x00, 0x00 },   // 76 (v)
    { 0x3C, 0x7C, 0x70, 0x38, 0x70, 0x7C, 0x3C, 0x00 },   // 77 (w)
    { 0x44, 0x6C, 0x38, 0x10, 0x38, 0x6C, 0x44, 0x00 },   // 78 (x)
    { 0x9C, 0xBC, 0xA0, 0xA0, 0xFC, 0x7C, 0x00, 0x00 },   // 79 (y)
    { 0x4C, 0x64, 0x74, 0x5C, 0x4C, 0x64, 0x00, 0x00 },   // 7A (z)
    { 0x08, 0x08, 0x3E, 0x77, 0x41, 0x41, 0x00, 0x00 },   // 7B ({)
    { 0x00, 0x00, 0x00, 0x77, 0x77, 0x00, 0x00, 0x00 },   // 7C (|)
    { 0x41, 0x41, 0x77, 0x3E, 0x08, 0x08, 0x00, 0x00 },   // 7D (})
    { 0x02, 0x03, 0x01, 0x03, 0x02, 0x03, 0x01, 0x00 },   // 7E (~)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }    // 7F (delete)
};
#endif
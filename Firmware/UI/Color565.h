#ifndef COLOR565_H
#define COLOR565_H

enum class Color565
{
    Black = 0x0000,         ///<   0,   0,   0
    Navy = 0x000F,          ///<   0,   0, 128
    DarkGreen = 0x03E0,     ///<   0, 128,   0
    DarkCyan = 0x03EF,      ///<   0, 128, 128
    Maroon = 0x7800,        ///< 128,   0,   0
    Purple = 0x780F,        ///< 128,   0, 128
    Olive = 0x7BE0,         ///< 128, 128,   0
    LightGrey = 0xC618,     ///< 192, 192, 192
    DarkGrey = 0x7BEF,      ///< 128, 128, 128
    Blue = 0x001F,          ///<   0,   0, 255
    Green = 0x07E0,         ///<   0, 255,   0
    Cyan = 0x07FF,          ///<   0, 255, 255
    Red = 0xF800,           ///< 255,   0,   0
    Magenta = 0xF81F,       ///< 255,   0, 255
    Yellow = 0xFFE0,        ///< 255, 255,   0
    White = 0xFFFF,         ///< 255, 255, 255
    Orange = 0xFD20,        ///< 255, 165,   0
    GreenYellow = 0xAFE5,   ///< 173, 255,  47
    Pink = 0xFC18,          ///< 255, 128, 192
    MenuBackground = 0xB5B6,///< 180, 180, 180
    IconPart1 = 0xC5F7,     ///< 194, 191, 188
    IconPart2 = 0xF489      ///< 244, 114,  72
};

#endif //COLOR565_H

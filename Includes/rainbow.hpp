#ifndef RAINBOW_HPP
#define RAINBOW_HPP

#include <CTRPluginFramework.hpp>
#include "Helpers.hpp"
#include "Unicode.h"

namespace CTRPluginFramework
{
int OTINPO_RGB;
u32 ONE_RGB = 0x00000000;
u32 SECOND_RGB = 0x00000000;
u32 RAINBOW_RGB = 0x002BFFFF;    //RGB
bool TINPO_RGB = true;

    void incRGB(void) {
    SECOND_RGB += 0x000f0608;
}
    
void WAHRGB(void) {
    SECOND_RGB += 0x000f0608;
}
    
void MENURGB(void) {
    incRGB();
}
    
void RGBRainbow( void ) {
    if(TINPO_RGB == true) {
        RAINBOW_RGB += 0x000f0608;
    }
}

}
#ifndef CHEATS_H
#define CHEATS_H

#include <CTRPluginFramework.hpp>
#include "Helpers.hpp"
#include "Unicode.h"

namespace CTRPluginFramework
{
    using StringVector = std::vector<std::string>;
    void set_background_border_color(MenuEntry *entry);
    u8 color_input(const std::string& color_name) ;
}

#endif
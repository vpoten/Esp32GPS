/*
    Copyright 2019 Jan Pomikalek <jan.pomikalek@gmail.com>

    This file is part of the DAVEga firmware.

    DAVEga firmware is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    DAVEga firmware is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with DAVEga firmware.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "davega_ili9225_screen.h"
#include "davega_config.h"
#include "SPI.h"

#if defined(ESP32)
SPIClass hspi(HSPI);
#endif

TFT_22_ILI9225 tft = TFT_22_ILI9225(TFT_RST, TFT_RS, TFT_CS, TFT_LED, 200);
TFT_22_ILI9225* p_tft = nullptr;

void DavegaILI9225Screen::init(t_davega_screen_config *config) {
  DavegaScreen::init(config);
  if (!p_tft) {
    p_tft = &tft;

#if defined(ESP32)
    hspi.begin();
    p_tft->begin(hspi);
#else
    p_tft->begin();
#endif

    p_tft->setOrientation(config->orientation);
    p_tft->setBackgroundColor(COLOR_BLACK);
  }
  _tft = p_tft;
}

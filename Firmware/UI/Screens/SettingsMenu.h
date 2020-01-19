#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

#include "IMenu.h"
#include "../Painter.h"
#include "../Widgets/MenuItem.h"

//#include "../Widgets/MainPageButton.h"

#include "../ButtonDefinitions.h"

#include "../../GlobalSettings.h"

#include "../../../Bootloader/Periphery/USB/IUSBDevice.h"

#include <Helpers.h>

class SettingsMenu : public IMenu
{
    IUSBDevice* _usbDevice;

    char* _label;
    char* _menuBreadcrumbs;
    MenuItem _menuItems[10];
    uint8_t _menuSelectionIndex;
    uint8_t _menuItemsCount;
    uint8_t _parameterSelectionIndex;
    uint8_t _parameterMenuActive;
    uint8_t _menuOffset;

    // Color Defintions
    uint16_t _menuBackgroundColor;
    uint16_t _menuItemColor;
    uint16_t _menuDimmedItemColor;
    uint16_t _menuDisabledItemColor;
    uint16_t _menuSelectedItemColor;
    uint16_t _menuHightlightedItemColor;
    uint16_t _menuTextColor;
    uint16_t _menuDisabledTextColor;
    uint16_t _menuSelectedTextColor;

  public:
    explicit SettingsMenu(IUSBDevice* cdcDevice)
    {
        UNUSED(cdcDevice);

        _label = "Settings Menu";
        _menuItemsCount = 10;
        _menuSelectionIndex = 0;

        _menuBreadcrumbs = "Settings Menu";

        int i = 0;
        _menuItems[i].SetLabel("Test Item 1");
        i++;
        _menuItems[i].SetDisabled(true);
        _menuItems[i].SetLabel("Test Item 2");
        i++;
        _menuItems[i].SetLabel("Test Item 3");
        //_menuItems[i].SetHighlighted(true);
        i++;
        _menuItems[i].SetLabel("Test Item 4");
        i++;
        _menuItems[i].SetLabel("Test Item 5");
        i++;
        _menuItems[i].SetLabel("Test Item 6");
        i++;
        _menuItems[i].SetLabel("Test Item 7");
        i++;
        _menuItems[i].SetLabel("Test Item 8");
        i++;
        _menuItems[i].SetLabel("Test Item 9");
        i++;
        _menuItems[i].SetLabel("Test Item 10");

        // Color defintions
        _menuBackgroundColor = RGB565(180, 180, 180);
        _menuItemColor = (uint16_t)Color565::White;
        _menuSelectedItemColor = RGB565(255, 128, 0);
        _menuDimmedItemColor = RGB565(247, 251, 247);
        _menuSelectedTextColor = RGB565(255, 255, 255);
        _menuHightlightedItemColor = RGB565(0, 128, 255);
        _menuTextColor = (uint16_t)Color565::Black;
        _menuDisabledTextColor = RGB565(40, 40, 40);
        _menuDisabledItemColor = RGB565(180, 180, 180);

        // init menu selection indexes
        _parameterMenuActive = 0;
        _parameterSelectionIndex = 0;
        _menuOffset = 0;

        /*
                _menuItems[2] = new MenuItem();
                _menuItems[2].SetLabel("Test Item 3");

                _menuButton.SetHandler(&MenuButtonHandler);

                _analogGainButton.SetHandler(&AnalogGainButtonHandler);
                _digitalGainButton.SetHandler(&DigitalGainButtonHandler);*/
    }

    void SetLabel(char* value)
    {
        _label = value;
    }

    char* GetLabel()
    {
        return _label;
    }

    int8_t GetMenuItemsCount()
    {
        return _menuItemsCount;
    }

  protected:
    void Draw(Painter* painter) override
    {

        // clear the screen
        painter->Fill(_menuBackgroundColor);
        // painter->DrawFillRectangle(0, 0, GlobalSettings::LCDWidth, GlobalSettings::LCDHeight, _menuBackgroundColor);

        // draw header background
        painter->DrawFillRectangle(0, GlobalSettings::LCDHeight - 28, GlobalSettings::LCDWidth, 28, _menuItemColor);

        // draw header bread crumbs
        painter->DrawText(5, GlobalSettings::LCDHeight - 22, _menuBreadcrumbs, _menuTextColor, Font::FreeSans9pt7b,
                          TextAlign::TEXT_ALIGN_LEFT, 0);

        // two header separation lines
        painter->DrawLine(0, GlobalSettings::LCDHeight - 29, GlobalSettings::LCDWidth - 1,
                          GlobalSettings::LCDHeight - 29, _menuSelectedItemColor);

        painter->DrawLine(0, GlobalSettings::LCDHeight - 30, GlobalSettings::LCDWidth - 1,
                          GlobalSettings::LCDHeight - 30, _menuBackgroundColor);

        /*for (int8_t i = 0; i < _menuItemsCount; i++)
        {
            //_menuItems[i].Draw(painter);
            painter->DrawFillRectangle(0, GlobalSettings::LCDHeight - 35 - 30 - i * 30, 200, 25, _menuItemColor);
        }*/

        // Side Icons
        /*
                // Side Icons Background
                fill_rect(0, 0, 30, FRAMEBUFFER_HEIGHT - 30, menu_item_color);

                // Home Icon
                if (home_icon_highlighted)
                {
                    drawRGBBitmap(0, 158, (uint16_t*)(home_icon_highlight.pixel_data), home_icon_highlight.width,
                                  home_icon_highlight.height);
                } else
                {
                    drawRGBBitmap(0, 158, (uint16_t*)(home_icon.pixel_data), home_icon.width, home_icon.height);
                }

                // Back Icon
                if (back_icon_highlighted)
                {
                    drawRGBBitmap(0, 108, (uint16_t*)(back_icon_highlight.pixel_data), back_icon_highlight.width,
                                  back_icon_highlight.height);
                } else
                {
                    drawRGBBitmap(0, 108, (uint16_t*)(back_icon.pixel_data), back_icon.width, back_icon.height);
                }
        */
        // draw menu items
        uint8_t a;
        for (a = 0; a < _menuItemsCount; a++)
        {
            uint8_t i;

            // this is the index of the 7 menu items drawn on screen currently
            int8_t displaySelectionIndex = _menuSelectionIndex - _menuOffset;

            // the _menu_offset is added to the item index and defines which item is the first one shown on screen

            // scrolling up from the first item
            if (displaySelectionIndex < 0)
            {
                _menuOffset -= 1;
            }

            // scrolling down from the last item
            if (displaySelectionIndex >= 7)
            {
                _menuOffset += 1;
            }

            // only up to 7 menu items fit on screen at once
            uint8_t menuItemsCount = _menuItemsCount;
            menuItemsCount = LimitRange(menuItemsCount, 0, 7);

            // draw up to 7 menu items
            for (i = 0; i < menuItemsCount; i++)
            {
                DrawMenuItem(30, (GlobalSettings::LCDHeight - 29 - 30) - i * 30, i + _menuOffset, painter);
            }

            // draw scroll bar indicator only if there are 7 or more menu items
            if (menuItemsCount == 7)
            {
                DrawScrollIndicator(menuItemsCount, _menuItemsCount, painter);
            }

            // draw parameter menu
            if (_parameterMenuActive != 0)
            {
                // the drawing coordinates in this case are provided as top right corner of the menu item
                // that triggers the parameter menu
                // the width depends on the text length of the options
                // the y coordinate may be shifted up or down if the choices would end up off screen
                uint16_t offset = (GlobalSettings::LCDHeight - 1 - 30) - (_parameterMenuActive - _menuOffset) * 30 - 2;

                if (menuItemsCount == 7)
                {
                    // if there is a scrollbar
                    // draw_parameter_menu(GlobalSettings::LCDWidth - 1 - 16, offset, a, _parameterMenuActive);
                } else
                {
                    // if there is no scrollbar
                    // draw_parameter_menu(FRAMEBUFFER_RIGHT, offset, a, parameter_menu_active);
                }
            }
        }
    }

    void DrawScrollIndicator(uint8_t current_menu_item_screen_count, uint8_t current_menu_item_count, Painter* painter)
    {
        // maximum height is the screen without header area
        uint8_t srollbar_max_framebuffer_height = GlobalSettings::LCDHeight - 30;

        // height of the scroll indicator is defined by the ratio of number of items on screen vs total number of item.
        // if there are 7 items on screen of total 14 items the scroll indicator shall be 50% of the scrollbar height
        uint8_t scrollbarheight = srollbar_max_framebuffer_height *
                                  (float)((float)current_menu_item_screen_count / (float)(current_menu_item_count));

        //
        uint8_t scrollbaroffset = ((current_menu_item_count - current_menu_item_screen_count) - _menuOffset) *
                                  ((srollbar_max_framebuffer_height - scrollbarheight) /
                                   (current_menu_item_count - current_menu_item_screen_count));

        // Background
        painter->DrawFillRectangle(GlobalSettings::LCDWidth - 16, 0, 16, GlobalSettings::LCDHeight - 30,
                                   _menuItemColor);

        // Thin Line
        painter->DrawFillRectangle(GlobalSettings::LCDWidth - 9, 0, 4, GlobalSettings::LCDHeight - 30, _menuTextColor);

        // Thick Line
        painter->DrawFillRectangle(GlobalSettings::LCDWidth - 13, scrollbaroffset, 12, scrollbarheight, _menuTextColor);
    }

    void DrawMenuItem(uint16_t x, uint16_t y, uint8_t item_index, Painter* painter)
    {
        uint16_t yoffset_label_from_base = 7;

        // don't draw empty items
        if (_label == NULL)
        {
            return;
        }

        char* value = "test";

        if (_menuItems[item_index].GetMenuType() == MenuItemType::MENU_ITEM_TYPE_SUBMENU)
        {
            // submenu items are indicated by a ">" sign
            value = ">";
        } else if (_menuItems[item_index].GetMenuType() == MenuItemType::MENU_ITEM_TYPE_PAGELINK)
        {
            // page links have no value icon displayed
            value = "";
        } else if (_menuItems[item_index].GetMenuType() == MenuItemType::MENU_ITEM_TYPE_BACKLINK)
        {
            // backlinks point to a menu higher in the menu hierarchy
            value = "";
        } else
        {
            if (0) //_menuItems[item_index].current_value_ptr != NULL)
            {
                /*strcpy(value, (*main_menu[menu_index].menu_item[item_index].current_value_ptr)(menu_index,
                item_index));

                sprintf(value, "%s",
                        (*main_menu[menu_index].menu_item[item_index].current_value_ptr)(menu_index, item_index));
                        */
            } else
            {
                value = _menuItems[item_index].GetValue();
            }
        }

        // is the current line highlighted and not disabled?
        if (_menuItems[item_index].IsHighlighted() && !_menuItems[item_index].IsDisabled())
        {
            painter->DrawFillRectangle(x, y, GlobalSettings::LCDWidth - x, 29, _menuHightlightedItemColor);

            // label
            painter->DrawText(x + 5, y + yoffset_label_from_base, _menuItems[item_index].GetLabel(),
                              _menuSelectedTextColor, Font::FreeSans9pt7b, TextAlign::TEXT_ALIGN_LEFT, 0);

            // value
            painter->DrawText(x + 180, y + yoffset_label_from_base, value, _menuSelectedTextColor, Font::FreeSans9pt7b,
                              TextAlign::TEXT_ALIGN_RIGHT, 80);
            return;
        }

        // is a parameter menu active currently and the item is disabled?
        if (_parameterMenuActive && _menuItems[item_index].IsDisabled())
        {
            painter->DrawFillRectangle(x, y, GlobalSettings::LCDWidth - x, 29, _menuDimmedItemColor);

            // label
            painter->DrawText(x + 5, y + yoffset_label_from_base, _menuItems[item_index].GetLabel(),
                              _menuDisabledTextColor, Font::FreeSans9pt7b, TextAlign::TEXT_ALIGN_LEFT, 0);

            // value
            painter->DrawText(x + 180, y + yoffset_label_from_base, value, _menuDisabledTextColor, Font::FreeSans9pt7b,
                              TextAlign::TEXT_ALIGN_LEFT, 80);
            return;
        }

        // is a parameter menu active currently?
        if (_parameterMenuActive)
        {
            painter->DrawFillRectangle(x, y, GlobalSettings::LCDWidth - x, 29, _menuDimmedItemColor);

            // label
            painter->DrawText(x + 5, y + yoffset_label_from_base, _menuItems[item_index].GetLabel(), _menuTextColor,
                              Font::FreeSans9pt7b, TextAlign::TEXT_ALIGN_LEFT, 0);

            // value
            painter->DrawText(x + 180, y + yoffset_label_from_base, value, _menuTextColor, Font::FreeSans9pt7b,
                              TextAlign::TEXT_ALIGN_RIGHT, 80);
            return;
        }

        // is the current line selected and disabled?
        if (_menuItems[item_index].IsSelected() && _menuItems[item_index].IsDisabled())
        {
            painter->DrawFillRectangle(x, y, GlobalSettings::LCDWidth - x, 29, _menuDisabledItemColor);

            // disabled indicators on the side
            painter->DrawFillRectangle(30, y, 4, 29, _menuSelectedTextColor);
            painter->DrawFillRectangle(GlobalSettings::LCDWidth - 16 - 4, y, 4, 29, _menuSelectedTextColor);

            // label
            painter->DrawText(x + 5, y + yoffset_label_from_base, _menuItems[item_index].GetLabel(),
                              _menuDisabledTextColor, Font::FreeSans9pt7b, TextAlign::TEXT_ALIGN_LEFT, 0);

            // value
            painter->DrawText(x + 180, y + yoffset_label_from_base, value, _menuDisabledTextColor, Font::FreeSans9pt7b,
                              TextAlign::TEXT_ALIGN_RIGHT, 80);
            return;
        }

        // is the current line disabled?
        if (_menuItems[item_index].IsDisabled())
        {
            painter->DrawFillRectangle(x, y, GlobalSettings::LCDWidth - x, 29, _menuDisabledItemColor);

            // label
            painter->DrawText(x + 5, y + yoffset_label_from_base, _menuItems[item_index].GetLabel(),
                              _menuDisabledTextColor, Font::FreeSans9pt7b, TextAlign::TEXT_ALIGN_LEFT, 0);

            // value
            painter->DrawText(x + 180, y + yoffset_label_from_base, value, _menuDisabledTextColor, Font::FreeSans9pt7b,
                              TextAlign::TEXT_ALIGN_RIGHT, 80);
            return;
        }
        // start comment out here

        // is the current line selected (cursor)?
        if (_menuItems[item_index].IsSelected())
        {
            painter->DrawFillRectangle(x, y, GlobalSettings::LCDWidth - x, 29, _menuSelectedItemColor);

            // value
            painter->DrawText(x + 5, y + yoffset_label_from_base, _menuItems[item_index].GetLabel(),
                              _menuSelectedTextColor, Font::FreeSans9pt7b, TextAlign::TEXT_ALIGN_LEFT, 0);

            // label
            painter->DrawText(x + 180, y + yoffset_label_from_base, value, _menuSelectedTextColor, Font::FreeSans9pt7b,
                              TextAlign::TEXT_ALIGN_RIGHT, 80);
            return;
        }

        // if nothing of the above applies simply draw the line item normally
        painter->DrawFillRectangle(x, y, GlobalSettings::LCDWidth - x, 29, _menuItemColor);

        // label
        painter->DrawText(x + 5, y + yoffset_label_from_base, _menuItems[item_index].GetLabel(), _menuTextColor,
                          Font::FreeSans9pt7b, TextAlign::TEXT_ALIGN_LEFT, 0);

        // value
        painter->DrawText(x + 180, y + yoffset_label_from_base, value, _menuTextColor, Font::FreeSans9pt7b,
                          TextAlign::TEXT_ALIGN_RIGHT, 80);
    }

    void UnselectAllMenuItems()
    {
        uint8_t b;
        for (b = 0; b < _menuItemsCount; b++)
        {
            _menuItems[b].SetSelected(false);
        }
    }

    void UnhighlightAllMenuItems()
    {
        uint8_t b;
        for (b = 0; b < _menuItemsCount; b++)
        {
            _menuItems[b].SetHighlighted(false);
        }
    }

    void Update(Button button, int8_t knob, IMenuSystem* menuSystem, USBCDCDevice* cdcDevice) override
    {
        //_menuSelectionIndex += knob;

        switch (button)
        {
        case Button::BUTTON_3_UP:
            _menuSelectionIndex++;
            break;
        case Button::BUTTON_6_UP:
            _menuSelectionIndex--;
            break;
        }

        _menuSelectionIndex = LimitRange(_menuSelectionIndex, 0, _menuItemsCount - 1);
        UnhighlightAllMenuItems();
        UnselectAllMenuItems();
        _menuItems[_menuSelectionIndex].SetSelected(true);

        //_usbDevice->Send((uint8_t*)"Knob \r\n", 10);

        //UNUSED(button);
        UNUSED(menuSystem);
    }
};

#endif // SETTINGSMENU_H
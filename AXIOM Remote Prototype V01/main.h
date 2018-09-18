/*	AXIOM Remote
 **
 **	Copyright (C) 2018 Sebastian Pichelhofer
 * 
 **
 **	This program is free software; you can redistribute it and/or modify
 **    	it under the terms of the GNU General Public License 2 as published 
 **	by the Free Software Foundation.
 **
 **	Compile with -O6 for best experience
 */

#include "definitions.h"
#include "gfxfont.h"

#ifndef MAIN_H
#define MAIN_H

extern uint16_t _cursor_x;
extern uint16_t _cursor_y;

extern enum _menus_t _current_menu;

extern uint8_t _menu_offset; // when scrolling the menu this is the offset for the items

extern uint8_t _parameter_menu_active; // is a parameter menu currently visible (0 = no)
extern uint8_t _parameter_selection_index; // index of the item currently selected in a parameter menu

typedef struct drop_down_choice_t {
    char label[32];
    uint8_t value;
} drop_down_choice_t;

enum _menus_t {
    Main, Submenu1, Submenu2
};
enum _menus_t _current_menu;

typedef enum {
    submenu, readonly, numeric, dropdown
} menu_item_type_t;

typedef struct menu_item_t {
    char label[64];
    bool disabled;
    bool hidden;
    enum _menus_t link_to_submenu;
    menu_item_type_t type;
    uint8_t value;
    bool(*action_ptr)(); //function pointer to the action when that menu entry is clicked
    char* (*current_value_ptr)(); //function pointer to return the current value
    drop_down_choice_t choices[30];
    uint8_t choice_count;
} menu_item_t;

typedef enum {
    left, center, right
} textAlign;

// AXIOM Remote buttons and knobs
extern bool btn_E1_pressed;
extern bool btn_E2_pressed;
extern bool btn_S1_pos;
extern bool btn_TS1_pos;
extern bool btn_TS2_pos;
extern uint8_t E1_pos;
extern uint8_t E2_pos;

extern uint8_t _menu_selection_index;

extern drop_down_choice_t mainMenuItem2Choices[2];
extern drop_down_choice_t mainMenuItem3Choices[4];

extern menu_item_t _menu_main_item[10];

extern menu_item_t _menu_sub1_item[3];
extern menu_item_t _menu_sub2_item[5];

extern char menu_breadcrumbs[64];

// Color Definitions
extern uint16_t menu_item_color;
extern uint16_t menu_dimmed_item_color;
extern uint16_t _menu_disabled_item_color;
extern uint16_t menu_selected_item_color;
extern uint16_t _menu_hightlighted_item_color;
extern uint16_t menu_background_color;
extern uint16_t menu_text_color;
extern uint16_t _menu_disabled_text_color;
extern uint16_t _menu_selected_text_color;

extern GFXfont gfxFont;

extern uint16_t _framebuffer[_width][_height];

#endif /* MAIN_H */
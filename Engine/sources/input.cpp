#include <vector>
#include <iostream>

#include "Engine/input.h"

bool Input::pressed_keys[255];

void Input::key_pressed(unsigned char key, int x, int y)
{
    Input::pressed_keys[key] = true;
}

void Input::key_up(unsigned char key, int x, int y)
{
    Input::pressed_keys[key] = false;
}

bool Input::is_key_pressed(unsigned char key)
{
    return Input::pressed_keys[key];
}
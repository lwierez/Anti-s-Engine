#include <vector>
#include <iostream>

#include "Engine/input.h"

std::vector<unsigned char> Input::pressed_keys;

void Input::key_pressed(unsigned char key, int x, int y)
{
    Input::pressed_keys.push_back(key);
}

void Input::key_up(unsigned char key, int x, int y)
{
    Input::pressed_keys.clear();
}

bool Input::is_key_pressed(unsigned char key)
{
    for (auto current_key : Input::pressed_keys)
        if (current_key == key)
            return true;
    return false;
}
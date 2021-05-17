#ifndef INPUT_H
#define INPUT_H

#include <vector>

class Input
{
public:
    static void key_pressed(unsigned char, int, int);
    static void key_up(unsigned char, int, int);
    static bool is_key_pressed(unsigned char);
private:
    static std::vector<unsigned char> pressed_keys;
};

#endif
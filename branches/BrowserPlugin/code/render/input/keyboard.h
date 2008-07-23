#pragma once
#ifndef INPUT_KEYBOARD_H
#define INPUT_KEYBOARD_H
//------------------------------------------------------------------------------
/**
    @class Input::Keyboard
    
    An input handler which represents a keyboard for polling.

    (C) 2007 Radon Labs GmbH
*/
#if __WIN32__
#include "input/base/keyboardbase.h"
namespace Input
{
class Keyboard : public Base::KeyboardBase
{
    DeclareClass(Keyboard);
};
}
#elif __XBOX360__
#include "input/xbox360/xbox360keyboard.h"
namespace Input
{
class Keyboard : public Xbox360::Xbox360Keyboard
{
    DeclareClass(Keyboard);
};
}
#elif __WII__
#include "input/wii/wiikeyboard.h"
namespace Input
{
class Keyboard : public Wii::WiiKeyboard
{
    DeclareClass(Keyboard);
};
}
#else
#error "Keyboard class not implemented on this platform!"
#endif
//------------------------------------------------------------------------------
#endif

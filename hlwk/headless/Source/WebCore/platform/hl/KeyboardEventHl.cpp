/*
 * Copyright (C) 2007 Kevin Ollivier <kevino@theolliviers.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

#include "config.h"
#include "PlatformKeyboardEvent.h"
#include "PlatformString.h"

#include "WindowsKeyboardCodes.h"
#include "ExtraKeyCodes.h"

namespace WebCore {

PlatformKeyboardEvent::PlatformKeyboardEvent(Type type, UChar k, int modifiers)
{
    m_type = type;
    m_windowsVirtualKeyCode = 0;
    m_shiftKey = modifiers & ShiftKey;
    m_ctrlKey = modifiers & CtrlKey;
    m_altKey = modifiers & AltKey;

    m_autoRepeat = false;
    
    switch(k) {
        case UNICODE_SHIFT:
            m_windowsVirtualKeyCode = VK_SHIFT;
            m_keyIdentifier = "Shift";
            break;
        case UNICODE_CONTROL:
            m_windowsVirtualKeyCode = VK_CONTROL;
            m_keyIdentifier = "Control";
            break;
        case UNICODE_ALT:
            m_windowsVirtualKeyCode = VK_MENU;
            m_keyIdentifier = "Alt";
            break;
        case UNICODE_BACK_SPACE:
            m_windowsVirtualKeyCode = VK_BACK;
            m_keyIdentifier = "Backspace";
            break;
        case UNICODE_RETURN:
        case UNICODE_ENTER:
        case '\n':
            m_windowsVirtualKeyCode = VK_RETURN;
            m_keyIdentifier = "Return";
            m_text = "\n";
            break;
        case ' ':
        case UNICODE_SPACE:
            m_windowsVirtualKeyCode = VK_SPACE;
            m_keyIdentifier = "Space";
            m_text = " ";
            break;
        case UNICODE_PAGE_UP:
            m_windowsVirtualKeyCode = VK_PRIOR;
            m_keyIdentifier = "PageUp";
            break;
        case UNICODE_PAGE_DOWN:
            m_windowsVirtualKeyCode = VK_NEXT;
            m_keyIdentifier = "PageDown";
            break;
        case UNICODE_END:
            m_windowsVirtualKeyCode = VK_END;
            m_keyIdentifier = "End";
            break;
        case UNICODE_HOME:
            m_windowsVirtualKeyCode = VK_HOME;
            m_keyIdentifier = "Home";
            break;
        case UNICODE_LEFT:
            m_windowsVirtualKeyCode = VK_LEFT;
            m_keyIdentifier = "Left";
            break;
        case UNICODE_UP:
            m_windowsVirtualKeyCode = VK_UP;
            m_keyIdentifier = "Up";
            break;
        case UNICODE_RIGHT:
            m_windowsVirtualKeyCode = VK_RIGHT;
            m_keyIdentifier = "Right";
            break;
        case UNICODE_DOWN:
            m_windowsVirtualKeyCode = VK_DOWN;
            m_keyIdentifier = "Down";
            break;
        case UNICODE_DELETE:
            m_windowsVirtualKeyCode = VK_DELETE;
            m_keyIdentifier = "U+007F";
            break;
    
        case UNICODE_NUMPAD0:
            m_windowsVirtualKeyCode = VK_NUMPAD0;
            m_keyIdentifier = "Numpad0";
            m_text = "0";
            break;
        case UNICODE_NUMPAD1:
            m_windowsVirtualKeyCode = VK_NUMPAD1;
            m_keyIdentifier = "Numpad1";
            m_text = "1";
            break;
        case UNICODE_NUMPAD2:
            m_windowsVirtualKeyCode = VK_NUMPAD2;
            m_keyIdentifier = "Numpad2";
            m_text = "2";
            break;
        case UNICODE_NUMPAD3:
            m_windowsVirtualKeyCode = VK_NUMPAD3;
            m_keyIdentifier = "Numpad3";
            m_text = "3";
            break;
        case UNICODE_NUMPAD4:
            m_windowsVirtualKeyCode = VK_NUMPAD4;
            m_keyIdentifier = "Numpad4";
            m_text = "4";
            break;
        case UNICODE_NUMPAD5:
            m_windowsVirtualKeyCode = VK_NUMPAD5;
            m_keyIdentifier = "Numpad5";
            m_text = "5";
            break;
        case UNICODE_NUMPAD6:
            m_windowsVirtualKeyCode = VK_NUMPAD6;
            m_keyIdentifier = "Numpad6";
            m_text = "6";
            break;
        case UNICODE_NUMPAD7:
            m_windowsVirtualKeyCode = VK_NUMPAD7;
            m_keyIdentifier = "Numpad7";
            m_text = "7";
            break;
        case UNICODE_NUMPAD8:
            m_windowsVirtualKeyCode = VK_NUMPAD8;
            m_keyIdentifier = "Numpad8";
            m_text = "8";
            break;
        case UNICODE_NUMPAD9:
            m_windowsVirtualKeyCode = VK_NUMPAD9;
            m_keyIdentifier = "Numpad9";
            m_text = "9";
            break;
        case UNICODE_MULTIPLY:
            m_windowsVirtualKeyCode = VK_MULTIPLY;
            m_keyIdentifier = "Multiply";
            m_text = "*";
            break;
        case UNICODE_ADD:
            m_windowsVirtualKeyCode = VK_ADD;
            m_keyIdentifier = "Add";
            m_text = "+";
            break;
        case UNICODE_SEPARATOR:
            m_windowsVirtualKeyCode = VK_SEPARATOR;
            m_keyIdentifier = "Separator";
            m_text = ",";
            break;
        case UNICODE_SUBTRACT:
            m_windowsVirtualKeyCode = VK_SUBTRACT;
            m_keyIdentifier = "Subtract";
            m_text = "-";
            break;
        case UNICODE_DECIMAL:
            m_windowsVirtualKeyCode = VK_DECIMAL;
            m_keyIdentifier = "Decimal";
            m_text = ".";
            break;
        case UNICODE_DIVIDE:
            m_windowsVirtualKeyCode = VK_DIVIDE;
            m_keyIdentifier = "Divide";
            m_text = "/";
            break;
        case UNICODE_SEMICOLON:
            m_keyIdentifier = "Semicolon";
            m_text = ";";
            break;
        case UNICODE_EQUALS:
            m_keyIdentifier = "Equals";
            m_text = "=";
            break;
        
        case UNICODE_F1:
            m_windowsVirtualKeyCode = VK_F1;
            m_keyIdentifier = "F1";
            m_text = "\0";
            break;
        case UNICODE_F2:
            m_windowsVirtualKeyCode = VK_F2;
            m_keyIdentifier = "F2";
            m_text = "\0";
            break;
        case UNICODE_F3:
            m_windowsVirtualKeyCode = VK_F3;
            m_keyIdentifier = "F3";
            m_text = "\0";
            break;
        case UNICODE_F4:
            m_windowsVirtualKeyCode = VK_F4;
            m_keyIdentifier = "F4";
            m_text = "\0";
            break;
        case UNICODE_F5:
            m_windowsVirtualKeyCode = VK_F5;
            m_keyIdentifier = "F5";
            m_text = "\0";
            break;
        case UNICODE_F6:
            m_windowsVirtualKeyCode = VK_F6;
            m_keyIdentifier = "F6";
            m_text = "\0";
            break;
        case UNICODE_F7:
            m_windowsVirtualKeyCode = VK_F7;
            m_keyIdentifier = "F7";
            m_text = "\0";
            break;
        case UNICODE_F8:
            m_windowsVirtualKeyCode = VK_F8;
            m_keyIdentifier = "F8";
            m_text = "\0";
            break;
        case UNICODE_F9:
            m_windowsVirtualKeyCode = VK_F9;
            m_keyIdentifier = "F9";
            m_text = "\0";
            break;
        case UNICODE_F10:
            m_windowsVirtualKeyCode = VK_F10;
            m_keyIdentifier = "F10";
            m_text = "\0";
            break;
        case UNICODE_F11:
            m_windowsVirtualKeyCode = VK_F11;
            m_keyIdentifier = "F11";
            m_text = "\0";
            break;
        case UNICODE_F12:
            m_windowsVirtualKeyCode = VK_F12;
            m_keyIdentifier = "F12";
            m_text = "\0";
            break;
        default:
            m_text.append(k);
            m_keyIdentifier = String::format("U+%04X", k);
    }
    m_nativeVirtualKeyCode = m_windowsVirtualKeyCode;
    if (m_text.isNull())  {
        m_text.append( (char)m_windowsVirtualKeyCode );
    }
    // FIXME: It is not 100% correct, need to map special characters like !"# to numbers, etc.
    // Lowercasing and mapping slows down execution of tests and unmodifiedText seems not used
    // in real life, do we need it at all?
    m_unmodifiedText = m_text.lower();
}

void PlatformKeyboardEvent::disambiguateKeyDownEvent(Type type, bool)
{
}

bool PlatformKeyboardEvent::currentCapsLockState()
{
    return false;
}

}

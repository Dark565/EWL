#pragma once

#include <queue>

#include <cstdint>

#include "../Input/mouse.hpp"

namespace ql {
    struct Event {
        enum Type {
            exit,
            activate,
            resize,
            move,
            fold,
            mouseMove,
            mouseButton,
            keyboardKey
            
        };
        Type type;

        union {
            struct {
                uint32_t x,y;
            } MouseMove, WindowMove, WindowResize;

            struct {
                mouse::Button button;
                mouse::Press press;
                uint32_t wheel;
            } MouseButton;

            struct {
                keyboard::Key key;
                keyboard::Press press;
            } KeyboardKey;

            struct {
                bool on;
            } Fold;
        };
    };

    struct EventQue {
    protected:
        std::queue<Event> ev_q;
    };
}
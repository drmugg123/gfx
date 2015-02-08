#ifndef WINDOW_EVENT_HPP
#define WINDOW_EVENT_HPP

namespace core {
    enum WINDOW_EVENT {
        WINDOW_EVENT_NONE,
        WINDOW_EVENT_SHOWN,
        WINDOW_EVENT_HIDDEN,
        WINDOW_EVENT_EXPOSED,
        WINDOW_EVENT_MOVED,
        WINDOW_EVENT_RESIZED,
        WINDOW_EVENT_MINIMIZED,
        WINDOW_EVENT_MAXIMIZED,
        WINDOW_EVENT_RESTORED,
        WINDOW_EVENT_ENTER,
        WINDOW_EVENT_LEAVE,
        WINDOW_EVENT_FOCUS_GAINED,
        WINDOW_EVENT_FOCUS_LOST,
        WINDOW_EVENT_CLOSE,
        
        WINDOW_EVENT_COUNT //for bounds checking
    };
}

#endif //WINDOW_EVENT_HPP
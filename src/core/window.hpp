#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include <string>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "core/window.hpp"
#include "core/window_event.hpp"
#include "core/keyboard_keys.hpp"

namespace core {
    class Window {
        public:
            std::string title;
            glm::vec2 resolution;
            glm::vec2 position;
            bool open, fullscreen, maximized, hidden, focused, initialized;

            virtual bool initialize(const std::string&, const glm::vec2&) = 0;

            virtual std::string getTitle() = 0;
            virtual bool setTitle(const std::string&) = 0;

            virtual glm::vec2 getResolution() = 0;
            virtual bool setResolution(const glm::vec2&) = 0;

            virtual glm::vec2 getPosition() = 0;
            virtual bool setPosition(const glm::vec2&) = 0;

            virtual bool isOpen() = 0;
            virtual bool close() = 0; 

            virtual bool isFullscreen() = 0;
            virtual bool setFullscreen(bool) = 0;
            virtual bool setBorderlessFullscreen(bool) = 0;

            virtual bool isMaximized() = 0;
            virtual bool setMaximized(bool) = 0;

            virtual bool isHidden() = 0;
            virtual bool setHidden(bool) = 0;

            virtual bool isFocused() = 0;
            virtual bool setFocused(bool) = 0;
 
            virtual bool isKeyPressed(core::KEYBOARD_KEY) = 0;

            virtual WINDOW_EVENT pollEvents() = 0;

            virtual void swapBuffers() = 0;
    };
}

#endif //WINDOW_HPP

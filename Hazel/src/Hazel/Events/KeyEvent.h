#pragma once
//处理响应键盘事件
#include "Event.h"

namespace Hazel {

    class HAZEL_API KeyEvent : public Event
    {
    public:
        inline int GetKeyCode() const { return m_KeyCode; }

        //键盘事件都是输入事件
        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
    protected:
        KeyEvent(int keycode)
            : m_KeyCode(keycode) {
        }

        int m_KeyCode;
    };
    //按键盘事件
    class HAZEL_API KeyPressedEvent : public KeyEvent
    {
    public:
        //按的什么字符，重复了多少次
        KeyPressedEvent(int keycode, int repeatCount)
            : KeyEvent(keycode), m_RepeatCount(repeatCount) {
        }

        inline int GetRepeatCount() const { return m_RepeatCount; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)
    private:
        int m_RepeatCount;
    };

    //松键盘事件
    class HAZEL_API KeyReleasedEvent : public KeyEvent
    {
    public:
       //松键盘事件只需要得到按了什么字符
        KeyReleasedEvent(int keycode)
            : KeyEvent(keycode) {
        }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };
}
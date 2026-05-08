#pragma once

#include "hzpch.h"
#include "Hazel/Core.h"

namespace Hazel{
    //事件类型
    enum class EventType
    {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };
    //事件用flag表示,哪一位是1就表明当前事件是哪种类型
    //例如:假设当前事件是鼠标按下：分类标记 = 00010 | 01000 | 10000 = 11010
    enum EventCategory {
        None = 0,
        EventCategoryApplication = BIT(0),
        EventCategoryInput = BIT(1),
        EventCategoryKeyboard = BIT(2),
        EventCategoryMouse = BIT(3),
        EventCategoryMouseButton = BIT(4)
    };
    //宏定义，因为每个事件都需要有这三个函数，所以宏定义一下方便写
    //一个#是转换成字符串，两个#是原语句替换 
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }
    
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

    class HAZEL_API Event
    {
        friend class EventDispatcher;//在一个类中指明其他的类（或者）函数能够直接访问该类中的private和protected成员。
    public:
        virtual EventType GetEventType() const = 0;//虚函数写了个接口，具体由子类实现
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;
        virtual std::string ToString() const { return GetName(); }

        inline bool IsInCategory(EventCategory category)//判断该事件是否是category的事件
        {
            return GetCategoryFlags() & category;
        }
    protected:
        bool m_Handled = false;
    };
    //事件调度器
    class EventDispatcher
    {   
        //T表示占位，真正要用的时候，T全部被替换为输入的东西
        //把std::function<bool(T&)>简写为EventFn,意思是定义应该函数变量，这个函数的返回类型为bool
        template<typename T>
        using EventFn = std::function<bool(T&)>;
    public:
        //构造函数
        EventDispatcher(Event& event)
            : m_Event(event)
        {
        }
        //func把函数表示为变量
        // 2. 类型强转 + 调用处理函数
                //函数返回 true = 事件被拦截 / 吃掉，不再往下传递
                //返回 false = 事件继续传递给其他系统
            // 1. 类型匹配检查
        template<typename T>
        bool Dispatch(EventFn<T> func)
        {
            if (m_Event.GetEventType() == T::GetStaticType())
            {
                
                m_Event.m_Handled = func(*(T*)&m_Event);
                return true;
            }
            return false;
        }
    private:
        Event& m_Event;
    };	
    
    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.ToString();
    }
}
#pragma once

#include "Hazel/Core.h"
#include "Hazel/Events/Event.h"

namespace Hazel {

    class HAZEL_API Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer();

        virtual void OnAttach() {}//当layer添加到layer stack的时候会调用此函数，相当于Init函数
        virtual void OnDetach() {}//当layer从layer stack移除的时候会调用此函数，相当于Shutdown函数
        virtual void OnUpdate() {}
        virtual void OnEvent(Event& event) {}

        inline const std::string& GetName() const { return m_DebugName; }
    protected:
        std::string m_DebugName;
    };

}
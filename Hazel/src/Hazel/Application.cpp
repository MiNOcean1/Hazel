#include "hzpch.h"
#include "Application.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Log.h"

#include <GLFW/glfw3.h>

namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
        m_Window = std::unique_ptr<Window>(Window::Create());
        //&Application::OnEvent：拿到成员函数指针
        //this：把这个成员函数绑定到“当前这个 Application 实例”
        //std::placeholders::_1：表示“回调被调用时传进来的第 1 个参数”，会被转发给 OnEvent
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{
	}

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer* layer)
    {
        m_LayerStack.PushOverlay(layer);
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
        {
            (*--it)->OnEvent(e);
            if (e.Handled)
                break;
        }
    }

	void Application::Run()
	{   
        while (m_Running) {
            glClearColor(1, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            m_Window->OnUpdate();
        }
	}

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }

}

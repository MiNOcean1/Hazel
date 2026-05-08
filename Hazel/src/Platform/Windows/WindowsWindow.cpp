#include "hzpch.h"
#include "WindowsWindow.h"

namespace Hazel {

    static bool s_GLFWInitialized = false;

    Window* Window::Create(const WindowProps& props)
    {
        return new WindowsWindow(props);
    }

    WindowsWindow::WindowsWindow(const WindowProps& props)
    {
        Init(props);
    }

    WindowsWindow::~WindowsWindow()
    {
        Shutdown();
    }

    void WindowsWindow::Init(const WindowProps& props)
    {
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;

        HZ_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);
        //保证只初始化一次
        if (!s_GLFWInitialized)
        {
            // TODO: glfwTerminate on system shutdown
            int success = glfwInit();
            HZ_CORE_ASSERT(success, "Could not intialize GLFW!");

            s_GLFWInitialized = true;
        }
        //创建窗口
        m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
        //把这个窗口的上下文设置为当前线程正在使用的上下文
        //没有 context，OpenGL 函数不知道该改哪份状态、把东西画到哪里。
        glfwMakeContextCurrent(m_Window);
        //给 GLFW 窗口绑一个“用户指针”，这里绑的是 m_Data 的地址。
        //常用于在 GLFW 的回调函数里，通过 glfwGetWindowUserPointer(window) 取回引擎自己的数据（例如事件系统 / 回调）。
        glfwSetWindowUserPointer(m_Window, &m_Data);
        
        //开启垂直同步
        SetVSync(true);
    }

    void WindowsWindow::Shutdown()
    {
        glfwDestroyWindow(m_Window);
    }

    void WindowsWindow::OnUpdate()
    {
        //处理窗口消息/输入事件（键盘鼠标、关闭窗口等），并触发回调。
        glfwPollEvents();
        //交换前后缓冲，把渲染结果显示到屏幕（双缓冲渲染流程的一部分）。
        glfwSwapBuffers(m_Window);
    }

    void WindowsWindow::SetVSync(bool enabled)
    {
        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_Data.VSync = enabled;
    }

    bool WindowsWindow::IsVSync() const
    {
        return m_Data.VSync;
    }

}
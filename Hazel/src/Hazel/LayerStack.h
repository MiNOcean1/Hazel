#pragma once

#include "Hazel/Core.h"
#include "Layer.h"

#include <vector>

namespace Hazel {

    class HAZEL_API LayerStack
    {
    public:
        LayerStack();
        ~LayerStack();
        // lay代表普通的layer, Overlay代表离屏幕最远的layer
        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        void PopLayer(Layer* layer);
        void PopOverlay(Layer* overlay);

        std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
        std::vector<Layer*>::iterator end() { return m_Layers.end(); }
    private:
        std::vector<Layer*> m_Layers;//存储layer的栈
        std::vector<Layer*>::iterator m_LayerInsert;//指向[ 普通 Layers ... ][ Overlays ... ]的分界的地方
    };

}
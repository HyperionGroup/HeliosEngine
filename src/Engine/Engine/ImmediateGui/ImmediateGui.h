#pragma once

#include <imgui.h>
#include "Core\Str.h"

namespace gui
{
    class CImmediateGui
    {
    public:
        CImmediateGui() = default;
        virtual ~CImmediateGui() = default;
        virtual void OnGui() = 0;
        void BeginWindow(const core::CStr& _title, Float2 _position = Float2(-1,-1))
        {
            if(_position.x > 0 && _position.y > 0 )
                ImGui::SetNextWindowPos(ImVec2(_position.x, _position.y));

            ImGui::Begin(_title.c_str());
        }
        void EndWindow() { return ImGui::End(); }
        void Indent() { ImGui::Indent(); }
        void Unindent() { ImGui::Unindent(); }
        bool CollapsingHeader(const core::CStr& _title) { return ImGui::CollapsingHeader(_title.c_str()); }
        void LabelText(const core::CStr& _label, const core::CStr& _text) { ImGui::LabelText(_label.c_str(), _text.c_str()); }
    };
}

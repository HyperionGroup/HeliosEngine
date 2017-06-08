#pragma once

#include <imgui.h>
#include "StringUtils.h"

namespace gui
{
    class CImmediateGui
    {
    public:
        CImmediateGui() = default;
        virtual ~CImmediateGui() = default;
        virtual void OnGui() = 0;
        void BeginWindow(const std::string& _title, Float2 _position = Float2(-1,-1))
        {
            if(_position.x > 0 && _position.y > 0 )
                ImGui::SetNextWindowPos(ImVec2(_position.x, _position.y));

            ImGui::Begin(core::ToUpperCase(_title).c_str());
        }
        void EndWindow() { return ImGui::End(); }
        void Indent() { ImGui::Indent(); }
        void Unindent() { ImGui::Unindent(); }
        bool CollapsingHeader(const std::string& _title) { return ImGui::CollapsingHeader(core::ToUpperCase(_title).c_str()); }
        void LabelText(const std::string& _label, const std::string& _text) { ImGui::LabelText(core::ToUpperCase(_label).c_str(), _text.c_str()); }
    };
}

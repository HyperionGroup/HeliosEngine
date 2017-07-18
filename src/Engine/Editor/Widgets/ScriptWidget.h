#pragma once

#include <QWidget>

#include "Core/Components.h"
#include "Logic/Script.h"

namespace editor
{
  class CScriptWidget : public QWidget
  {
    Q_OBJECT
  public:
    CScriptWidget(logic::CScript * _script);
    virtual ~CScriptWidget() = default;
  };
}
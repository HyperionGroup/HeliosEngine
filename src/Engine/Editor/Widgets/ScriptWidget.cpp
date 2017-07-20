#include "Editor.h"
#include "ScriptWidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

namespace editor
{
  CScriptWidget::CScriptWidget(logic::CScript * _script)
  {
    QVBoxLayout* lLayout = new QVBoxLayout(this);

    auto v_lua_vars = _script->GetVarsVector();

    for each (auto var in v_lua_vars)
    {
      QHBoxLayout* lVarLayout = new QHBoxLayout(this);
      lVarLayout->addWidget(new QLabel(tr(var.name.c_str()), this));

      if (var.type == std::to_string((int)sol::type::number))
      {
        float val = var.value.as<float>();
        //lVarLayout->addWidget( new CFloatWidget( "", &val ) );
      }
      else
      {
        //lVarLayout->addWidget(new QLabel(tr(var.value.as<std::string>().c_str()), this));
      }

      lLayout->addLayout(lVarLayout);
    }

    setLayout(lLayout);
  }
}
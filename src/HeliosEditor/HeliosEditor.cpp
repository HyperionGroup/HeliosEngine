#include <Mathpp.h>
#include "d3d11/Textures/Sampler.h"
#include "Assets/TextureAsset.h"
#include "RenderableView.h"
#include <QApplication>
#include "d3d11/RenderContext.h"
#include <QListWidget>
#include <QDockWidget>
#include <QStyleFactory>
#include "EditorWindow.h"
#include "SceneView.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    user::CEditorWindow lEditorWindow;

    QDockWidget *dock = new QDockWidget(QObject::tr("Customers"), &lEditorWindow);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    
    QListWidget* customerList = new QListWidget(dock);
    customerList->addItems(QStringList()
        << "John Doe, Harmony Enterprises, 12 Lakeside, Ambleton"
        << "Jane Doe, Memorabilia, 23 Watersedge, Beaton"
        << "Tammy Shea, Tiblanka, 38 Sea Views, Carlton"
        << "Tim Sheen, Caraba Gifts, 48 Ocean Way, Deal"
        << "Sol Harvey, Chicos Coffee, 53 New Springs, Eccleston"
        << "Sally Hobart, Tiroli Tea, 67 Long River, Fedula");
    dock->setWidget(customerList);

    user::CSceneView view(&lEditorWindow);
    render::CRenderContext::GetInstance().CreateContext(view.GetHWND());
    lEditorWindow.setCentralWidget(&view);
    lEditorWindow.addDockWidget(Qt::RightDockWidgetArea, dock);

    app.setStyle(QStyleFactory::create("Fusion"));

    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));

    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);

    app.setPalette(darkPalette);

    app.setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");


    lEditorWindow.show();
    return app.exec();

    /*
    Float3 point;
    Float3 point2(3.0f);
    Float3 point3 = point + point2;
        
    render::CSampler lSampler;

    std::ofstream file("out.json");
    std::ifstream filein("in.json");

    cereal::JSONOutputArchive archive(file);
    archive(cereal::make_nvp("sampler", lSampler));

    cereal::JSONInputArchive archivein(filein);
    archivein(cereal::make_nvp("sampler", lSampler));

    io::CTextureAsset lTexture("opiece.jpg");
    lTexture.Load();
    archive(cereal::make_nvp("texture_asset", lTexture));
    return 0;
    */
}
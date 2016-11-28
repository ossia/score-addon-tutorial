#include "TutorialProcessView.hpp"
#include <Process/Style/ScenarioStyle.hpp>
#include <QPainter>
namespace Tutorial
{

TutorialView::TutorialView(
        QGraphicsItem* parent):
    LayerView{parent}
{

}

void TutorialView::setText(const QString& txt)
{
    m_text = txt;
    update();
}

void TutorialView::paint_impl(QPainter* painter) const
{
    auto font = iscore::Skin::instance().MonoFont;
    font.setPointSize(25);
    painter->setFont(font);
    painter->setPen(Qt::white);

    painter->drawText(QPointF{5., height() / 2.}, m_text);
}
}

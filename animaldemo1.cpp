#include "animaldemo1.h"

#include <QPushButton>
#include <QPainter>
#include <QSequentialAnimationGroup>

AnimalDemo1::AnimalDemo1(int w, int h, QWidget *parent):
    QWidget(parent)
{
    this->resize(w, h);
    initUi();
}

void AnimalDemo1::initUi()
{
    m_pBaseWidget = new QWidget(this);
    m_pBaseWidget->resize(58, 494);
    m_pBaseWidget->move(this->width()/2 - m_pBaseWidget->width()/2,
                        this->height()/2 - m_pBaseWidget->height()/2);

    m_pBgWidget = new BgWidget(m_pBaseWidget);
    m_pBgWidget->move(0, 156);


    for(int i = 0; i < 9; ++i) {
        QPushButton *btn = new QPushButton(m_pBaseWidget);
        btn->setStyleSheet("background:red;");
        btn->resize(32, 32);
        btn->move(m_pBaseWidget->width()/2 - btn->width()/2, 21 + i*(btn->height() + 20));
        m_btnList.append(btn);
        initBtnHideAnimal(btn, btn->pos());
        if(i < 3){
            btn->resize(0, 0);
        }
        if(i == 3){
            connect(btn, &QPushButton::clicked, this, [=](){
                checked = !checked;
                m_btnList.at(0)->resize(0, 0);
                m_btnList.at(1)->resize(0, 0);
                m_btnList.at(2)->resize(0, 0);
                if(checked) {
                    m_pBgWidget->startAnimal(QPropertyAnimation::Forward);
                    m_pPreviewAnimalGroup->start();
                }
                else {
                    m_pBgWidget->startAnimal(QPropertyAnimation::Backward);
                }
            });
        }
    }

    m_pPreviewAnimalGroup = new QSequentialAnimationGroup(this);
    m_pPreviewAnimalGroup->addAnimation(m_animalMap.value(m_btnList.at(2)));
    m_pPreviewAnimalGroup->addAnimation(m_animalMap.value(m_btnList.at(1)));
    m_pPreviewAnimalGroup->addAnimation(m_animalMap.value(m_btnList.at(0)));

}


void AnimalDemo1::initBtnHideAnimal(QWidget *item, QPoint pos)
{
    QPropertyAnimation *animation = new QPropertyAnimation(item, "geometry", m_pBaseWidget);
    animation->setDuration(200);
    animation->setStartValue(QRect(this->width()/2, item->y() + item->height()/2, 0, 0));
    animation->setEndValue(QRect(pos, item->size()));
    m_animalMap.insert(item, animation);
}



/***********************************************************************************************/

BgWidget::BgWidget(QWidget *parent):
    QWidget(parent), m_normalSize(58, 338), m_expandSize(58, 494)
{
    this->resize(m_normalSize);
    m_pPreviewShowAnimation = new QPropertyAnimation(this, "geometry", this);
    m_pPreviewShowAnimation->setDuration(300);
    m_pPreviewShowAnimation->setKeyValueAt(0, QRect(0, 156,
                                                    m_normalSize.width(), m_normalSize.height()));
    m_pPreviewShowAnimation->setKeyValueAt(1, QRect(0, 0,
                                                    m_normalSize.width(), m_expandSize.height()));
}

void BgWidget::startAnimal(QAbstractAnimation::Direction direction)
{
    m_direction = direction;
    m_pPreviewShowAnimation->setDirection(direction);
#if 1
    if(direction == QPropertyAnimation::Forward){
        m_pPreviewShowAnimation->setDuration(300);
    }else{
        m_pPreviewShowAnimation->setDuration(200);
    }
#endif
    m_pPreviewShowAnimation->start();
}

void BgWidget::setChecked(bool checked)
{
    m_bIsExpand = checked;
    if(m_bIsExpand){
        this->resize(m_expandSize);
    }else{
        this->resize(m_normalSize);
    }

    update();
}

void BgWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::HighQualityAntialiasing);
    painter.setBrush(Qt::white);
    QPen pen;
    pen.setWidth(2);
    pen.setColor(QColor("#d1d1d1"));
    painter.setPen(pen);
    painter.drawRoundedRect(QRect(2, 2, this->width() - 4, this->height() - 4), 10, 10);

    QWidget::paintEvent(event);
}

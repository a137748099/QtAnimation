#include "beatanimal.h"
#include <QPropertyAnimation>
#include <QLabel>
#include <QThread>
#include <QPushButton>

BeatAnimal::BeatAnimal(int w, int h, QWidget *parent):
    QWidget(parent)
{
    this->resize(w, h);

    m_pStartBtn = new QPushButton(this);
    m_pStartBtn->setGeometry(0, 10, 100, 40);
    connect(m_pStartBtn, &QPushButton::clicked, this, [=](){
        m_pAnimal->start();
    });

    m_pTargetLabel = new QLabel(this);
    m_pTargetLabel->setStyleSheet("background:red;");
    m_pTargetLabel->resize(100, 100);
    m_pTargetLabel->move(this->width()/2 - m_pTargetLabel->width()/2, this->height()/2 - m_pTargetLabel->height()/2);

    initAnimal();
}

void BeatAnimal::initAnimal()
{
    m_pAnimal = new QPropertyAnimation(m_pTargetLabel, "geometry", this);
    m_pAnimal->setDuration(800);
    QRect originRect = m_pTargetLabel->geometry();
    m_pAnimal->setKeyValueAt(0, originRect);
    m_pAnimal->setKeyValueAt(0.2, QRect(originRect.x() - 10, originRect.y() - 10,
                                                 originRect.width() + 20, originRect.height() + 20));
    m_pAnimal->setKeyValueAt(0.6, QRect(originRect.x() - 10, originRect.y() - 10,
                                                 originRect.width() + 20, originRect.height() + 20));
    m_pAnimal->setKeyValueAt(0.7, originRect);
    m_pAnimal->setKeyValueAt(0.9, QRect(originRect.x() - 3, originRect.y() - 3,
                                                 originRect.width() + 6, originRect.height() + 6));
    m_pAnimal->setKeyValueAt(1, originRect);
    connect(m_pAnimal, &QPropertyAnimation::finished, this, [=](){
        ++m_nAnimalCount;
        //执行2次
        if(m_nAnimalCount < 3){
            QThread::msleep(300);
            m_pAnimal->start();
        }
        else {
            m_nAnimalCount = 0;
        }
    });
}


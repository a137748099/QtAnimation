#ifndef ANIMALDEMO1_H
#define ANIMALDEMO1_H

#include <QWidget>
#include <QPropertyAnimation>

class QPushButton;
class BgWidget;
class QSequentialAnimationGroup;

class AnimalDemo1 : public QWidget
{
    Q_OBJECT
public:
    explicit AnimalDemo1(int w, int h, QWidget *parent = Q_NULLPTR);

protected:
    void initUi();
    void initBtnHideAnimal(QWidget *item, QPoint pos);

private:
    QWidget *m_pBaseWidget = Q_NULLPTR;
    BgWidget *m_pBgWidget = Q_NULLPTR;
    QMap<QWidget *, QPropertyAnimation *> m_animalMap;
    QList<QWidget *> m_btnList;
    bool checked = false;
    QSequentialAnimationGroup *m_pPreviewAnimalGroup = Q_NULLPTR;

};

class BgWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BgWidget(QWidget *parent = Q_NULLPTR);

    void startAnimal(QPropertyAnimation::Direction direction);
    void setChecked(bool checked);

protected:
    void paintEvent(QPaintEvent *event);

signals:
    void sigFinished();


private:
    QSize m_normalSize;
    QSize m_expandSize;

    bool m_bIsExpand = false;

    QPropertyAnimation *m_pPreviewShowAnimation = Q_NULLPTR;
    QPropertyAnimation::Direction m_direction = QPropertyAnimation::Forward;

};


#endif // ANIMALDEMO1_H

#ifndef BEATANIMAL_H
#define BEATANIMAL_H

#include <QWidget>
class QPropertyAnimation;
class QLabel;
class QPushButton;

class BeatAnimal : public QWidget
{
    Q_OBJECT
public:
    explicit BeatAnimal(int w, int h, QWidget *parent = Q_NULLPTR);

protected:
    void initAnimal();

private:
    QLabel *m_pTargetLabel = Q_NULLPTR;
    QPropertyAnimation *m_pAnimal = Q_NULLPTR;
    int m_nAnimalCount = 0;
    QPushButton *m_pStartBtn = Q_NULLPTR;

};

#endif // BEATANIMAL_H

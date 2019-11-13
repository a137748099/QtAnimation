#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QTabWidget;
class BeatAnimal;
class AnimalDemo1;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void initUi();

private:
    QTabWidget *m_pTabWidget = Q_NULLPTR;

    BeatAnimal *m_pBeatAnimalWidget = Q_NULLPTR;
    AnimalDemo1 *m_pAnimalDemo1 = Q_NULLPTR;

};

#endif // MAINWINDOW_H

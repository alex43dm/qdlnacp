#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QWidgetAction>
#include <QSlider>
#include <QSpinBox>
#include <QLabel>

#include "UPnP_CP.h"
#include "Timer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public UPnP_CP
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void exit();
    void onMediaServersPic(QTreeWidgetItem * item, int column);
    void onMediaRendererPic(QTreeWidgetItem * item, int column);
    void onLibraryPic(QTreeWidgetItem * item, int column);
    void onPlayList(QTreeWidgetItem * item, int column);

    void setText(QString i);
    void clearText();
    void threadError(QString err);
    void onPlay();
    void onPause();
    void onStop();
    void onNext();
    void onPrev();
    void onVolChange(int);
    void onVolShow();
    void onPlayerSliderChange(int);
private:
    Ui::MainWindow *ui;

    QWidgetAction *actVolSlider;
    QWidgetAction *actPlayerSlider;
    QWidgetAction *actPlayerLabel;
    QSpinBox *volSlider;
    //QSlider *volSlider;
    //QToolButton *userInputButton;
    QLabel  *playerTime;
    QSlider *playerSlider;

    QWidgetAction *actSongName;
    QLabel  *songName;

    QTreeWidgetItem *curItem;

    virtual bool onDeviceAdd();
    virtual bool onScanStop();
    virtual bool onScanStart();
    virtual void timerTick();
    virtual void timerFinish();
private slots:

};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setTransforms();

private slots:
    void on_Z_slider_sliderMoved(int position);

    void on_X_slider_sliderMoved(int position);

    void on_Y_Slider_sliderMoved(int position);

    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    std::vector< std::vector<int> > _sliders;
    int _current;
    bool skeletonVisible;
};

#endif // MAINWINDOW_H

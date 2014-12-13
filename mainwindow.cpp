#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    std::vector<int> temp;
    temp.push_back(0);
    temp.push_back(0);
    temp.push_back(0);
    for(int i = 0; i < ui->comboBox->count();i++){
        _sliders.push_back(temp);
    }
    _current = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_X_slider_sliderMoved(int position)
{
    _sliders[_current][0] = position;
    setTransforms();

}

void MainWindow::on_Y_Slider_sliderMoved(int position)
{
    _sliders[_current][1] = position;
    setTransforms();
}

void MainWindow::on_Z_slider_sliderMoved(int position)
{
    _sliders[_current][2] = position;
    setTransforms();
}


void MainWindow::on_pushButton_clicked()
{

    ui->widget->_skeletonVisible = !ui->widget->_skeletonVisible;
    if(ui->widget->_skeletonVisible) ui->pushButton->setText("View Mesh");
    else ui->pushButton->setText("View Skeleton");
    ui->widget->updateGL();

}

void MainWindow::on_comboBox_currentIndexChanged(int index){

    _current = index;
    ui->X_slider->setValue(_sliders[_current][0]);
    ui->Y_Slider->setValue(_sliders[_current][1]);
    ui->Z_slider->setValue(_sliders[_current][2]);

}

void MainWindow::setTransforms(){

    float toRadians = M_PI/180;
    float rX = _sliders[_current][0]*toRadians;
    float rY = _sliders[_current][1]*toRadians;
    float rZ = _sliders[_current][2]*toRadians;

    ui->widget->_mySkeleton->setJointTransform(_current,rX,rY,rZ);
    ui->widget->_mySkeleton->updateCurrentJointToWorldTransforms();
    ui->widget->_mySkeleton->updateMesh();

    ui->widget->updateGL();


}


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtXml/QtXml>
#include <QFile>
#include "QListWidgetItem"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    Ui::MainWindow *ui;
    QString _fileName;

private slots:
    void openFile();
    void readFile();
    //void selected();

    void on_comboBox_vertexesCurrentIndexChanged(int index);
    void on_list_vertexes_itemClicked(QListWidgetItem * item);

};

#endif // MAINWINDOW_H

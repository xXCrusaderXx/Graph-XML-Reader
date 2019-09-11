#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtXml/QtXml>
#include "QFileDialog"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->button_openFile,SIGNAL(clicked()),this,SLOT(openFile()));
    connect(ui->button_readFile,SIGNAL(clicked()),this,SLOT(readFile()));

    //connect(ui->list_vertexes,SIGNAL(),this,SLOT(selected()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile()
{
    _fileName = QFileDialog::getOpenFileName(this,tr("Open Image"), "", tr("Image Files (*.xml)"));
    ui->statusBar->showMessage(_fileName+" wurde geladen!",5000);
    ui->label_fileName->setText(_fileName);

    std::vector<QString> liste;
    QFile file(_fileName);

    ui->list_vertexes->clear();

    file.open(QIODevice::ReadOnly);
    QXmlStreamReader reader(&file);

    if(reader.readNextStartElement())
    {
        if(reader.name() == "boost_serialization")
        {
            while(reader.readNextStartElement())
            {
                if(reader.name() == "_base_graph")
                {
                    while(reader.readNextStartElement())
                    {
                        if(reader.name() == "vertex_property")
                        {
                            while(reader.readNextStartElement())
                            {
                                if(reader.name() == "property_base")
                                {
                                    while(reader.readNextStartElement())
                                    {
                                        if(reader.name() == "Name")
                                        {
                                            QString vertexName = reader.readElementText();

                                            int size = vertexName.size();
                                            int hit = 0;
                                            for(int index = 0; index<size; ++index)
                                            {
                                                if(vertexName[index]==":")
                                                    hit = index;
                                            }
                                            vertexName = vertexName.left(hit);
                                            bool matchFound = false;

                                            for(auto value : liste)
                                            {
                                                if(value.contains(vertexName))
                                                {
                                                    matchFound = true;
                                                }
                                            }

                                            if(matchFound == false)
                                            {
                                            liste.push_back(vertexName);
                                            ui->list_vertexes->addItem(vertexName);
                                            }
                                        }
                                        else
                                           reader.skipCurrentElement();
                                    }
                                }
                                else
                                   reader.skipCurrentElement();
                            }
                        }
                         else
                            reader.skipCurrentElement();
                    }
                }
            }
        }
        else
        {
            reader.raiseError(QObject::tr("Incorrect file"));
            ui->statusBar->showMessage("Incorrect file",5000);
        }
    }
    repaint();
}

void MainWindow::readFile()
{
    ui->list_vertexes->clear();

    int vertexIndex = 0;
    QFile file(_fileName);

    file.open(QIODevice::ReadOnly);
    QXmlStreamReader reader(&file);

    if(reader.readNextStartElement())
    {
        if(reader.name() == "boost_serialization")
        {
            while(reader.readNextStartElement())
            {
                if(reader.name() == "_base_graph")
                {
                    while(reader.readNextStartElement())
                    {
                        if(reader.name() == "vertex_property")
                        {
                            while(reader.readNextStartElement())
                            {
                                if(reader.name() == "property_base")
                                {
                                    while(reader.readNextStartElement())
                                    {
                                        if(reader.name() == "Name")
                                        {
                                            vertexIndex = vertexIndex+1;
                                            QString tmp;
                                            tmp = tmp.setNum(vertexIndex)+ ": ";
                                            QString vertexName = reader.readElementText();
                                            QString fullName = tmp + vertexName;
                                            ui->list_vertexes->addItem(fullName);
                                        }
                                        else
                                           reader.skipCurrentElement();
                                    }
                                }
                                else
                                   reader.skipCurrentElement();
                            }
                        }
                         else
                            reader.skipCurrentElement();
                    }
                }
            }
        }
        else
        {
            reader.raiseError(QObject::tr("Incorrect file"));
            ui->statusBar->showMessage("Incorrect file",5000);
        }
    }
    repaint();
}

void MainWindow::selected()
{
    ui->statusBar->showMessage("Funktioniert",5000);
}

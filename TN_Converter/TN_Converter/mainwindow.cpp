#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QCheckBox>
#include <QStandardItemModel>

#include <QFile>
#include <QTextStream>
#include <QDebug>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonParseError>

#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QXmlStreamAttribute>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusbar->showMessage("Программа запущена.");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_OpenFileDialog_clicked()
{
    QString str = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.csv *.json *.xml");
    ui->fileName->setText(str);
    if (str.endsWith(".csv") || str.endsWith(".CSV"))
    {
        csvModel = new QStandardItemModel(this);
        csvModel->setColumnCount(3);
//
        ui->tableView->setModel(csvModel);
        ui->tableView->setColumnWidth( 0, 170 );
        ui->tableView->setColumnWidth( 1, 40 );
        // Open the file from the resources. Instead of the file
        // Need to specify the path to your desired file
        QFile file(ui->fileName->text());
        if ( !file.open(QFile::ReadOnly | QFile::Text) )
            ui->statusbar->showMessage("Файл CSV не открыт."); 
        else
        {
            // Create a thread to retrieve data from a file
            QTextStream in(&file);
            //Reads the data up to the end of file
            while (!in.atEnd())
            {
                QString line = in.readLine();
                if (line=="Tag;Type;Address")
                    csvModel->setHorizontalHeaderLabels(QStringList() << "Tag" << "Type" << "Process");
                else
                {
                // Adding to the model in line with the elements
                QList<QStandardItem *> standardItemsList;
                // consider that the line separated by semicolons into columns
                for (QString item : line.split(";"))
                    standardItemsList.append(new QStandardItem(item));
                csvModel->insertRow(csvModel->rowCount(), standardItemsList);
                }
            }
            file.close();
        }
    ui->Convert->setEnabled(true);
    ui->statusbar->showMessage("Файл CSV открыт.");
    }

    if (str.endsWith(".json") || str.endsWith(".JSON"))
    {
        jsonModel = new QStandardItemModel(this);
        jsonModel->setColumnCount(3);
//        jsonModel->setHorizontalHeaderLabels(QStringList() << "1" << "2" << "3");
        ui->tableView->setModel(jsonModel);
        ui->tableView->setColumnWidth( 0, 40 );
        ui->tableView->setColumnWidth( 1, 180 );

    QString val;
    QFile file;
    file.setFileName(ui->fileName->text());
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8(), &error);
//    qDebug() << "Error: " << error.errorString() << error.offset << error.error;
    if (doc.isObject())
    {
        QJsonObject json = doc.object();
        QJsonArray jsonArray = json["TypeInfos"].toArray();
        foreach (const QJsonValue & value, jsonArray)
        {
            if (value.isObject())
            {
                QJsonObject obj = value.toObject();
                QJsonObject PropertysName = obj["Propertys"].toObject();
                QString TypeName = obj["TypeName"].toString();
                {
                    QList <QStandardItem *> standardItemsList;
                    QString item = TypeName;
                    standardItemsList.append(new QStandardItem(item));
                    jsonModel->insertRow(jsonModel->rowCount(), standardItemsList);
                }
                QStringList KeyList = PropertysName.keys();
                for (int i=0; i<PropertysName.count(); i++)
                {
                    QString KeyName = KeyList[i];
                    QString strValue = PropertysName.value(KeyName).toString();
                    {
                        QList <QStandardItem *> standardItemsList;
                        QString item = "";
                        standardItemsList.append(new QStandardItem(item));
                        item = KeyName;
                        standardItemsList.append(new QStandardItem(item));
                        item = strValue;
                        standardItemsList.append(new QStandardItem(item));
                        jsonModel->insertRow(jsonModel->rowCount(), standardItemsList);
                    }
                }
            }
        }
    }
    ui->Convert->setEnabled(false);
    ui->statusbar->showMessage("Файл JSON открыт.");
    }

    if (str.endsWith(".xml") || str.endsWith(".XML"))
    {
        xmlReadModel = new QStandardItemModel(this);
        xmlReadModel->setColumnCount(2);
        xmlReadModel->setHorizontalHeaderLabels(QStringList() << "Tag" << "Offset");
        ui->tableView->setModel(xmlReadModel);
        ui->tableView->setColumnWidth( 0, 250 );
        ui->tableView->setColumnWidth( 1, 40 );

        QString xmlTag;
        QString xmlAdress;
        /* Открываем файл для Чтения */
        QFile file(ui->fileName->text());
        if (!file.open(QFile::ReadOnly | QFile::Text))
        {
            ui->statusbar->showMessage("Файл XML не открыт.");
        } else {
            /* Создаем объект, с помощью которого осуществляется чтение из файла */
            QXmlStreamReader xmlReader;
            xmlReader.setDevice(&file);
            xmlReader.readNext();   // Переходит к первому элементу в файле
            /* Крутимся в цикле до тех пор, пока не достигнем конца документа */
            while(!xmlReader.atEnd())
            {
                /* Проверяем, является ли элемент началом тега */
                if(xmlReader.isStartElement())
                {
                    if(xmlReader.name() == "node-path") xmlTag = xmlReader.readElementText();
                    if(xmlReader.name() == "address")
                    {
                        xmlAdress = xmlReader.readElementText();
                        QList <QStandardItem *> standardItemsList;
                        QString item = xmlTag;
                        standardItemsList.append(new QStandardItem(item));
                        item = xmlAdress;
                        standardItemsList.append(new QStandardItem(item));
                        xmlReadModel->insertRow(xmlReadModel->rowCount(), standardItemsList);
                    }
                }
                xmlReader.readNext(); // Переходим к следующему элементу файла
            }
            file.close(); // Закрываем файл
        }
    ui->Convert->setEnabled(false);
    ui->statusbar->showMessage("Файл XML открыт.");
    }

}

void MainWindow::on_Convert_clicked()
{
    xmlModel = new QStandardItemModel(this);
    xmlModel->setColumnCount(2);
    xmlModel->setHorizontalHeaderLabels(QStringList() << "Tag" << "Offset");
    ui->tableViewConv->setModel(xmlModel);
    ui->tableViewConv->setColumnWidth( 0, 250 );
    ui->tableViewConv->setColumnWidth( 1, 40 );

    QString val;
    QFile file;
    file.setFileName("TypeInfos.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8(), &error);
//    qDebug() << "Error: " << error.errorString() << error.offset << error.error;

    unsigned int lastRow = csvModel->rowCount();
    long int Adress = 0;
    for(unsigned int ConvertedRow=0; ConvertedRow < lastRow; ConvertedRow++)
    {
        QString ConvTag =   csvModel->data(csvModel->index(ConvertedRow, 0)).toString();
        QString ConvType =  csvModel->data(csvModel->index(ConvertedRow, 1)).toString();
        QString ConvAdr =   csvModel->data(csvModel->index(ConvertedRow, 2)).toString();
//    csvModel->insertRow(ConvertedRow + 1);
//    csvModel->setData(csvModel->index((ConvertedRow + 1), 0), ConvTag);
        ui->tableView->selectRow(ConvertedRow);
        ui->tableView->setFocus();
        if (ConvAdr != "")
        {
            if (doc.isObject())
            {
                QJsonObject json = doc.object();
                QJsonArray jsonArray = json["TypeInfos"].toArray();
                foreach (const QJsonValue & value, jsonArray)
                {
                    if (value.isObject())
                    {
                        QJsonObject obj = value.toObject();
                        QJsonObject PropertysName = obj["Propertys"].toObject();
                        QString TypeName = obj["TypeName"].toString();
                        if (TypeName ==  ConvType)
                        {
                            QStringList KeyList = PropertysName.keys();
                            for (int i=0; i<PropertysName.count(); i++)
                            {
                                QString KeyName = KeyList[i];
                                QString strValue = PropertysName.value(KeyName).toString();
                                {
                                    QList <QStandardItem *> standardItemsList;
                                    QString item = ConvTag + "." + KeyName;
                                    standardItemsList.append(new QStandardItem(item));
                                    item.setNum(Adress);
                                  //  Adress = Adress + sizeof(strValue);
                                    Adress = Adress + strValue.size();
                                    standardItemsList.append(new QStandardItem(item));
                                    xmlModel->insertRow(xmlModel->rowCount(), standardItemsList);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    ui->SaveFileDialog->setEnabled(true);
    ui->statusbar->showMessage("Файл CSV сконвертирован по данным файла TypeInfos.json");
}

void MainWindow::on_SaveFileDialog_clicked()
{
    /* Вызываем диалог выбора файла для сохранения */
    QString filename = QFileDialog::getSaveFileName(this, "Save Xml", "Result.xml", "*.xml");

    /* Открываем файл для Записи */
    QFile file(filename);
    file.open(QIODevice::WriteOnly);
    /* Создаем объект, с помощью которого осуществляется запись в файл */
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);  // Устанавливаем автоформатирование текста
    xmlWriter.writeStartDocument();     // Запускаем запись в документ
    xmlWriter.writeStartElement("root");   // Записываем первый элемент

    unsigned int lastRow = xmlModel->rowCount();

    for(unsigned int ConvertedRow=0; ConvertedRow < lastRow; ConvertedRow++)
    {
        xmlWriter.writeStartElement("item");
        xmlWriter.writeAttribute("Binding", "Introduced");
        QString Tag = xmlModel->data(xmlModel->index(ConvertedRow, 0)).toString();
        QString Adr = xmlModel->data(xmlModel->index(ConvertedRow, 1)).toString();

        xmlWriter.writeStartElement("node-path");  // Записываем тег с именем
        xmlWriter.writeCharacters(Tag);
        xmlWriter.writeEndElement();               // Закрываем тег

        xmlWriter.writeStartElement("address");  // Записываем тег с именем
        xmlWriter.writeCharacters(Adr);
        xmlWriter.writeEndElement();             // Закрываем тег
        /* Закрываем тег "item" */
        xmlWriter.writeEndElement();
    }
    /* Закрываем тег "root" */
    xmlWriter.writeEndElement();
    /* Завершаем запись в документ */
    xmlWriter.writeEndDocument();
    file.close();   // Закрываем файл

    ui->statusbar->showMessage("Файл XML сохранен.");
}

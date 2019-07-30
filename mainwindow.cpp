/**
 * \file mainwindow.cpp
 * \brief Plik implementacji moduˆu \a mainwindow.
 *
 * Moduˆ \a mainwindow zawiera funkcje niezb©dne
 * do inicjacji GUI oraz interakcji z nim
 *
 *
 * \see mainwindow.h
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "labcalc.h"
#include "tabsop.h"
#include <QMessageBox>
#include <QLinearGradient>
#include <QMouseEvent>
#include <cmath>
#include <QGraphicsScene>
#include <fstream>
#include <sys/stat.h>

/*
 *Aby dzia³a³o poprawnie odkomentuj pêtle w MousPressEvent w tym pliku
 *zmiana dla generowania mapy dla Pacmana
 *
*/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ///Deklaracje startowe zmiennych
    description_head=NULL;
    lab_list_head=NULL;
    h=5;
    w=5;
    scale=1;
    edit_mode=0;
    scene=NULL;
    ///inicjacja stanu pocz¥tkowego tablicy i  jej pokazania w GUI
    load_lab_list(lab_list_head);
    tab=mktab(h,w,scale);
    picsupdate();
}

MainWindow::~MainWindow()
{
    deletepics(tab,h,w);
    del(tab,w);
    del_description(description_head);
    save_lab_list(lab_list_head);
    del_lab_list(lab_list_head);
    delete ui;
}

void MainWindow::on_pushButton_close_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Uwaga!");
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setText("Wychodzisz z programu!");
    msgBox.setInformativeText("Projekt zostanie bezpowrotnie utracony!");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);

    int ret = msgBox.exec();

    switch (ret) {
    case QMessageBox::Cancel:
        break;
    case QMessageBox::Ok:
        deletepics(tab,h,w);
        del(tab,w);
        del_description(description_head);
        save_lab_list(lab_list_head);
        del_lab_list(lab_list_head);
        exit(0);
    default:
        break;
    }
    return;
}

void MainWindow::on_pushButton_reset_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Uwaga!");
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setText("Reset programu!");
    msgBox.setInformativeText("Struktura labiryntu zostanie zresetowana!");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);

    int ret = msgBox.exec();

    switch (ret) {
    case QMessageBox::Cancel:
        break;
    case QMessageBox::Ok:
        del(tab,w);
        tab=mktab(h,w,scale);
        picsupdate();
        del_description(description_head);
        text_update(description_head);
    default:
        break;
    }
    return;
}

void MainWindow::on_radioButton_wall_clicked()
{
    edit_mode=0;
    return;
}

void MainWindow::on_radioButton_way_clicked()
{
    edit_mode=1;
    return;
}

void MainWindow::on_radioButton_start_clicked()
{
    edit_mode=2;
    return;
}

void MainWindow::on_radioButton_end_clicked()
{
    edit_mode=3;
    return;
}

void MainWindow::on_pushButton_labGen_clicked()
{
    int nw=ui->horizontalSlider->value();
    int nh=ui->verticalSlider->value();
    tab=newsize(tab,h,w,nh,nw,scale);
    picsupdate();
    clockupdate();
    QMessageBox msgBox;
    msgBox.setWindowTitle("Success!");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setInformativeText("Wykonano pomyslnie!");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);

    int ret = msgBox.exec();

    switch (ret) {
    case QMessageBox::Ok:
    default:
        break;
    }
    return;
}

void MainWindow::on_pushButton_make_clicked()
{
    del_description(description_head);
    if(waysearch(tab,h,w,description_head)){        ///Je˜li znaleziono drog©...
        mkgreen(tab,h,w);
        deletepics(tab,h,w);
        createpics(tab,h,w,scale);
        picsupdate();
        text_update(description_head);
        QMessageBox msgBox;
        msgBox.setWindowTitle("Success!");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setInformativeText("Wykonano pomyslnie!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);

        int ret = msgBox.exec();

        switch (ret) {
        case QMessageBox::Ok:
        default:
            break;
        }
    }else{
        QMessageBox msgBox;
        msgBox.setWindowTitle("Fail!");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Sprawdz konfiguracje labiryntu!");
        msgBox.setInformativeText("Nie udalo sie wyznaczyc drogi przez labirynt!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);

        int ret = msgBox.exec();

        switch (ret) {
        case QMessageBox::Ok:
        default:
            break;
        }
    }
    return;
}

void MainWindow::on_pushButton_save_clicked()
{
    QMessageBox msgBox;
    QString name;
    name=ui->lineEdit->text();
    name += ".txt";
    struct stat buf;
    if ( stat(name.toStdString().c_str(), &buf) == 0 ){     ///Sprawdzanie czy zapisywany plik labiryntu istnieje(nadpisanie)
        msgBox.setWindowTitle("Warning!");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Dane moga zostac nadpisane!");
        msgBox.setInformativeText("Upewnij sie, ze nie utracisz danych!");
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);

        int ret = msgBox.exec();

        switch (ret) {
        case QMessageBox::Cancel:
            break;
        case QMessageBox::Ok:
            name=ui->lineEdit->text();
            printsave(tab,h,w,name);
        default:
            break;
        }
        return;
    }else{
        msgBox.setWindowTitle("Success!");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Pomyslnie zapisano!");
        msgBox.setInformativeText("Plik zapisany!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);

        int ret = msgBox.exec();

        switch (ret) {
        case QMessageBox::Ok:
            name=ui->lineEdit->text();
            printsave(tab,h,w,name);
            add_new_lab(lab_list_head,name);
        default:
            break;
        }
        return;
    }
}

void MainWindow::on_pushButton_load_clicked()
{
    QMessageBox msgBox;
    QString name;
    name=ui->lineEdit->text();
    name += ".txt";
    struct stat buf;
    if ( stat(name.toStdString().c_str(), &buf) == 0 ){     ///Sprawdzanie czy wczytywany plik labiryntu istnieje
        msgBox.setWindowTitle("Uwaga!");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Obecny projekt zostanie nadpisany!");
        msgBox.setInformativeText("Wczytujesz plik z innym labiryntem!");
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);

        int ret = msgBox.exec();

        switch (ret) {
        case QMessageBox::Cancel:
            break;
        case QMessageBox::Ok:
            tab=load(tab,h,w,name,scale);
            picsupdate();
            clockupdate();
            add_new_lab(lab_list_head,ui->lineEdit->text());
        default:
            break;
        }
        return;
    }else{
        QString name;
        msgBox.setWindowTitle("Error!");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Blad wczytywania!");
        msgBox.setInformativeText("Sprawdz czy plik istnieje!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);

        int ret = msgBox.exec();

        switch (ret) {
        case QMessageBox::Ok:
        default:
            break;
        }
        return;
    }
}


void MainWindow::picsupdate()
{
    if(scene!=NULL)
        delete scene;
    scene = new QGraphicsScene();       ///Stawiam scene na nowo
    scene->setBackgroundBrush(Qt::cyan);
    scene->clear();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();

    for(int i=0;i<w;i++){
        for(int j=0;j<h;j++){

            QRadialGradient grad(QPointF((i*50+25)*scale, (j*50+25)*scale), 100*scale);     ///Korzystam z bibliotek QRadialGradient do tworzenia graficznego wygl¥du p¢l labiryntu

            switch(tab[i][j].str_type)
            {
            case 0:
                grad.setColorAt(0.1, Qt::black);        ///Definicja gradientu
                grad.setColorAt(0.5, Qt::red);
                grad.setColorAt(0.9, Qt::black);
                tab[i][j].pic->setBrush(grad);          ///Zastosowanie gradientu
                break;
            case 1:
                grad.setColorAt(0.1, Qt::gray);
                grad.setColorAt(0.5, Qt::white);
                grad.setColorAt(0.9, Qt::gray);
                tab[i][j].pic->setBrush(grad);
                break;
            case 2:
                grad.setColorAt(0.1, Qt::red);
                grad.setColorAt(0.5, Qt::black);
                grad.setColorAt(0.9, Qt::red);
                tab[i][j].pic->setBrush(grad);
                break;
            case 3:
                grad.setColorAt(0.1, Qt::yellow);
                grad.setColorAt(0.5, Qt::black);
                grad.setColorAt(0.9, Qt::yellow);
                tab[i][j].pic->setBrush(grad);
                break;
            case 4:
                grad.setColorAt(0.1, Qt::green);
                grad.setColorAt(0.5, Qt::black);
                grad.setColorAt(0.9, Qt::green);
                tab[i][j].pic->setBrush(grad);
                break;
            default:
                break;
            }
        }
    }
    //to do: here is a source of QGraphicsScene::addItem: item has already been added to this scene
    for(int i=0;i<w;i++){      ///Monta¾ obiekt¢w na scenie(p¢l labirytnu)
        for(int j=0;j<h;j++){
            scene->addItem(tab[i][j].pic);
        }
    }
    ui->graphicsView->update();
}

void MainWindow::clockupdate(){
    ui->lcdNumber_hotwidth->display(w);
    ui->lcdNumber_hotheigh->display(h);
    ui->horizontalSlider->setValue(w);
    ui->verticalSlider->setValue(h);
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    QPointF pt = ui->graphicsView->mapToScene(event->pos());        ///Pobranie pozycji klikni©cia myszk¥
    int i,j;
    i=floor((pt.x()-13)/50/scale);      ///wsp¢ˆrz©dne klikni©tego pola labiryntu
    j=floor((pt.y()-13)/50/scale);
    if(i<w && i>=0 && j<h && j>=0){     ///Je˜li klikni©to w labirynt
        QRadialGradient grad(QPointF((i*50+25)*scale, (j*50+25)*scale), 100*scale);
        switch(edit_mode)           ///zamiana wy˜wietlanego pola labiryntu
        {
        case 0:
            grad.setColorAt(0.1, Qt::black);
            grad.setColorAt(0.5, Qt::red);
            grad.setColorAt(0.9, Qt::black);
            tab[i][j].pic->setBrush(grad);
            break;
        case 1:
            grad.setColorAt(0.1, Qt::gray);
            grad.setColorAt(0.5, Qt::white);
            grad.setColorAt(0.9, Qt::gray);
            tab[i][j].pic->setBrush(grad);
            break;
        case 2:                 ///dla case 2 i 3 sprawdzamy czy nie ma innych p¢l typu start i koniec, w razie wyst¥pienia takiej sytuacji pola te s¥ zamieniane na pola typu 1(way)
            for(int n=0;n<w;n++){
                for(int m=0;m<h;m++){
                    if(tab[n][m].str_type==2){
                        QRadialGradient grad2(QPointF((n*50+25)*scale, (m*50+25)*scale), 100*scale);
                        tab[n][m].str_type=1;
                        grad2.setColorAt(0.1, Qt::gray);
                        grad2.setColorAt(0.5, Qt::white);
                        grad2.setColorAt(0.9, Qt::gray);
                        tab[n][m].pic->setBrush(grad2);
                    }
                }
            }
            grad.setColorAt(0.1, Qt::red);
            grad.setColorAt(0.5, Qt::black);
            grad.setColorAt(0.9, Qt::red);
            tab[i][j].pic->setBrush(grad);
            break;
        case 3:
            for(int n=0;n<w;n++){
                for(int m=0;m<h;m++){
                    if(tab[n][m].str_type==3){
                        QRadialGradient grad2(QPointF((n*50+25)*scale, (m*50+25)*scale), 100*scale);
                        tab[n][m].str_type=1;
                        grad2.setColorAt(0.1, Qt::gray);
                        grad2.setColorAt(0.5, Qt::white);
                        grad2.setColorAt(0.9, Qt::gray);
                        tab[n][m].pic->setBrush(grad2);
                    }
                }
            }
            grad.setColorAt(0.1, Qt::yellow);
            grad.setColorAt(0.5, Qt::black);
            grad.setColorAt(0.9, Qt::yellow);
            tab[i][j].pic->setBrush(grad);
            break;
        case 4:
            grad.setColorAt(0.1, Qt::green);
            grad.setColorAt(0.5, Qt::black);
            grad.setColorAt(0.9, Qt::green);
            tab[i][j].pic->setBrush(grad);
            break;
        default:
            break;
        }
        tab[i][j].str_type=edit_mode;       ///aktualizacja struktury labirynut
        scene->addItem(tab[i][j].pic);      ///aktualizacja sceny i graphicView
    }
}


void MainWindow::on_doubleSpinBox_valueChanged(double arg1)
{
    scale=arg1;     ///argument z obiektu SpinBox jest mno¾nikiem dla wielko˜ci obiekt¢w graficznych i skalowania gradient¢w dla zachowania takiego samego wygl¥du p¢l
    deletepics(tab,h,w);
    createpics(tab,h,w,scale);
    picsupdate();
}

void MainWindow::del_description(way_description* &description_head){
    way_description* description_pointer;
    way_description* tmp;
    if(description_head!=NULL){
        while(description_head->nextmove!=NULL){
            description_pointer=description_head;
            while(description_pointer->nextmove->nextmove!=NULL){
                description_pointer=description_pointer->nextmove;
            }
            tmp=description_pointer;
            description_pointer=description_pointer->nextmove;
            delete description_pointer;
            tmp->nextmove=NULL;
        }
        delete description_head;
        description_head=NULL;
    }
}

void MainWindow::text_update(way_description* description_head){
    way_description* description_pointer=description_head;
    int i=1;
    ui->textBrowser->setText("Lista krokow do przejscia labiryntu:");
    while(description_pointer!=NULL){
        ui->textBrowser->append(QString::number(i)+=". "+description_pointer->move);
        description_pointer=description_pointer->nextmove;
        i++;
    }
}

void MainWindow::load_lab_list(lab_list* &lab_list_head){
    struct stat buf;
    if ( stat("LabExplorer.data", &buf) == 0 ){     ///Sprawdzanie czy wczytywany plik labiryntu istnieje
        std::ifstream data;
        lab_list* tmp;
        tmp=lab_list_head;
        data.open("LabExplorer.data", std::ios::in);
        if(data.good()==true){
            while(!data.eof()){
                if(lab_list_head==NULL){
                    lab_list_head=new lab_list;
                    tmp=lab_list_head;
                }else{
                    tmp->next_lab=new lab_list;
                    tmp=tmp->next_lab;
                }
                tmp->next_lab=NULL;
                getline(data ,tmp->lab_name);
            }
        }
        data.close();
        show_lab_list(lab_list_head);
    }else{
        std::ofstream data;
        data.open("LabExplorer.data", std::ios::in);
        data.close();
    }
}


void MainWindow::show_lab_list(lab_list* lab_list_head){
    lab_list* tmp;
    tmp=lab_list_head;
    while(tmp!=NULL){
        ui->listWidget->addItem(QString::fromStdString(tmp->lab_name));
        tmp=tmp->next_lab;
    }
}

void MainWindow::del_lab_list(lab_list* &lab_list_head){
    lab_list* lab_list_pointer;
    lab_list* tmp;
    if(lab_list_head!=NULL){
        while(lab_list_head->next_lab!=NULL){
            lab_list_pointer=lab_list_head;
            while(lab_list_pointer->next_lab->next_lab!=NULL){
                lab_list_pointer=lab_list_pointer->next_lab;
            }
            tmp=lab_list_pointer;
            lab_list_pointer=lab_list_pointer->next_lab;
            delete lab_list_pointer;
            tmp->next_lab=NULL;
        }
        delete lab_list_head;
        lab_list_head=NULL;
    }
}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QString lab_name=item->text();
    struct stat buf;
    if ( stat(lab_name.toStdString().c_str(), &buf) == 0 ){     ///Sprawdzanie czy wczytywany plik labiryntu istnieje
        tab=load(tab,h,w,item->text(),scale);
        picsupdate();
        clockupdate();
    }else{
        del_lab_element(lab_list_head,lab_name);
    }
}

void MainWindow::on_pushButton_open_clicked()
{
    QString lab_name=ui->listWidget->currentItem()->text();
    struct stat buf;
    if(ui->listWidget->currentItem()!=NULL){
        if ( stat(lab_name.toStdString().c_str(), &buf) == 0 ){     ///Sprawdzanie czy wczytywany plik labiryntu istnieje
            tab=load(tab,h,w,ui->listWidget->currentItem()->text(),scale);
            picsupdate();
            clockupdate();
        }else{
            del_lab_element(lab_list_head,lab_name);
        }
    }
}

void MainWindow::on_pushButton_delete_clicked()
{
    del_lab_element(lab_list_head,ui->listWidget->currentItem()->text());
}

void MainWindow::save_lab_list(lab_list* lab_list_head){
    lab_list* lab_list_pointer=lab_list_head;
    std::ofstream data;
    data.open("LabExplorer.data", std::ios::out);
    if(data.good()==true){
        while(lab_list_pointer!=NULL){
            data<<lab_list_pointer->lab_name;
            if(lab_list_pointer->next_lab!=NULL)
                data<<'\n';
            lab_list_pointer=lab_list_pointer->next_lab;
        }
    }
    data.close();
}

void MainWindow::add_new_lab(lab_list* &lab_list_head,QString new_lab_name){
    lab_list* lab_list_pointer=lab_list_head;
    new_lab_name += ".txt";
    bool is=false;
    while(lab_list_pointer!=NULL){
        if(lab_list_pointer->lab_name==new_lab_name.toStdString().c_str()){
            is=true;
        }
        lab_list_pointer=lab_list_pointer->next_lab;
    }
    if(is==false){
        lab_list_pointer=new lab_list;
        lab_list_pointer->lab_name=new_lab_name.toStdString().c_str();
        lab_list_pointer->next_lab=lab_list_head;
        lab_list_head=lab_list_pointer;
        ui->listWidget->clear();
        show_lab_list(lab_list_head);
    }
}

void MainWindow::del_lab_element(lab_list* &lab_list_head,QString lab_name){
    lab_list* tmp;
    lab_list* lab_list_pointer=lab_list_head;
    if(lab_list_head->lab_name!=lab_name.toStdString().c_str()){
        while(lab_list_pointer->next_lab->lab_name!=lab_name.toStdString().c_str()){
            lab_list_pointer=lab_list_pointer->next_lab;
        }
        tmp=lab_list_pointer->next_lab->next_lab;
        delete lab_list_pointer->next_lab;
        lab_list_pointer->next_lab=tmp;
    }else{
        lab_list_head=lab_list_head->next_lab;
        delete lab_list_pointer;
    }
    delete ui->listWidget->currentItem();
}



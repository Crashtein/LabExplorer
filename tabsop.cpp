/**
 * \file tabsop.cpp
 * \brief Plik implementacji moduˆu \a tabsop.
 *
 * Moduˆ \a tabsop zawiera funkcje niezb©dne
 * do operowania tablicami zawieraj¥cymi struktury labirynt¢w
 *
 *
 * \see tabsop.h
 */

#include "tabsop.h"
#include <fstream>

lab ** mktab(int heigh,int width,double scale){
    lab **wsk=new lab *[width];
    for(int i=0;i<width;i++)
        wsk[i]=new lab[heigh];
    reset(wsk,heigh,width);
    createpics(wsk,heigh,width,scale);
    return wsk;
}

void del(lab **wsk, int width){
    for(int i=0;i<width;i++){
        delete [] wsk[i];
    }
    delete [] wsk;
}

void reset(lab **wsk, int heigh, int width){
    for(int i=0;i<width;i++){
        for(int j=0;j<heigh;j++){
            wsk[i][j].str_type=0;
            wsk[i][j].exp=0;
        }
    }
}

void mkgreen(lab **wsk, int heigh, int width){
    for(int i=0;i<width;i++){
        for(int j=0;j<heigh;j++){
            if(wsk[i][j].exp==1 && wsk[i][j].str_type==1){
                wsk[i][j].str_type=4;
            }
        }
    }
}

void copy(lab **oldtab,lab **newtab,int heigh, int width, int newheigh, int newwidth){
    if(heigh>newheigh){
        heigh=newheigh;
    }
    if(width>newwidth){
        width=newwidth;
    }
    for(int i=0;i<width;i++){
        for(int j=0;j<heigh;j++){
            newtab[i][j].str_type=oldtab[i][j].str_type;
        }
    }
}

lab ** newsize(lab **wsk, int &heigh, int &width, int newheigh, int newwidth,double scale){
    lab **newtab;
    newtab=mktab(newheigh,newwidth,scale);
    copy(wsk,newtab,heigh,width,newheigh,newwidth);
    del(wsk,width);
    heigh=newheigh;
    width=newwidth;
    return newtab;
}

void delgreen(lab **wsk,int heigh,int width){
    for(int i=0;i<width;i++){
        for(int j=0;j<heigh;j++){
            if(wsk[i][j].str_type==4){
                wsk[i][j].str_type=1;
            }
        }
    }
}

void printsave(lab **wsk, int heigh, int width, QString name){
    std::ofstream data;
    name += ".txt";
    data.open(name.toStdString().c_str(), std::ios::out);
    if(data.good()==true){
        data<<heigh<<' '<<width;
        data<<'\n';
        for(int i=0;i<heigh;i++){
            for(int j=0;j<width;j++){
                data<<wsk[j][i].str_type;
                data<<' ';
            }
            data<<'\n';
        }
    }
    data.close();
}


lab ** load(lab **wsk,int &heigh,int &width,QString name,double scale){
    std::ifstream data;
    int lw,lh;
    data.open(name.toStdString().c_str(), std::ios::in);
    if(data.good()==true){
        data>>lw>>lh;
        wsk=newsize(wsk,heigh,width,lw,lh,scale);
        for(int i=0;i<heigh;i++){
            for(int j=0;j<width;j++){
                data>>wsk[j][i].str_type;
            }
        }
    }
    data.close();
    return wsk;
}

void createpics(lab **wsk, int heigh, int width,double scale){
    for(int i=0;i<width;i++){
        for(int j=0;j<heigh;j++){
            wsk[i][j].pic=new QGraphicsRectItem(i*50*scale,j*50*scale,50*scale,50*scale);
        }
    }
}

void deletepics(lab **wsk, int heigh, int width){
    for(int i=0;i<width;i++){
        for(int j=0;j<heigh;j++){
            delete wsk[i][j].pic;
        }
    }
}










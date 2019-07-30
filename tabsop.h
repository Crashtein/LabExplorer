/**
 * \file tabsop.h
 * \brief Plik nagˆ¢wkowy moduˆu \a tabsop.
 *
 * Moduˆ \a tabsop zawiera funkcje niezb©dne
 * do operowania tablicami zawieraj¥cymi struktury labirynt¢w
 *
 * \see tabsop.cpp
 */

#ifndef TABSOP_H
#define TABSOP_H
#include "mainwindow.h"

/**
 * @brief Tworzy tablice o podanych wymiarach
 * tworzy elementy graficzne o odowiadaj¥cej skali wielko˜ci
 *
 * @param scale mno¾nik domy˜lnej wielko˜ci graficznych zmiennych struktury labiryntu
 * @param heigh warto˜† wysoko˜ci labiryntu
 * @param width warto˜† szeroko˜ci labiryntu
 * @return zwraca wska«nik na tablic© ze struktur¥ labiryntu
 */
lab ** mktab(int heigh,int width,double scale);
/**
 * @brief str_type=0 dla caˆej tablicy
 *
 * @param wsk wska«nik na tablic© labiryntu
 * @param heigh warto˜† wysoko˜ci labiryntu
 * @param width warto˜† szeroko˜ci labiryntu
 */
void reset(lab **wsk, int heigh, int width);
/**
 * @brief Wstawia w pola o str_type==1 oraz exp==1 parametr str_type=4
 *
 * @param wsk wska«nik na tablic© labiryntu
 * @param heigh warto˜† wysoko˜ci labiryntu
 * @param width warto˜† szeroko˜ci labiryntu
 */
void mkgreen(lab **wsk, int heigh, int width);
/**
 * @brief tworzy now¥ tablic©, kopiuje do niej mo¾liwe do skopiowania dane, zmienia wska«nik pocz¥tka tablicy
 *
 * @param wsk wska«nik na tablic© labiryntu
 * @param scale mno¾nik domy˜lnej wielko˜ci graficznych zmiennych struktury labiryntu
 * @param heigh warto˜† wysoko˜ci labiryntu
 * @param width warto˜† szeroko˜ci labiryntu
 * @param newheigh nowa warto˜† wysoko˜ci labiryntu
 * @param newwidth nowa warto˜† szeroko˜ci labiryntu
 * @param scale mno¾nik domy˜lnej wielko˜ci graficznych zmiennych struktury labiryntu
 * @return zwraca wska«nik na tablic© ze struktur¥ labiryntu
 */
lab ** newsize(lab **wsk, int &heigh, int &width, int newheigh, int newwidth,double scale);
/**
 * @brief kasuje tablice przed wyˆ¥czeniem programu
 *
 * @param wsk wska«nik na tablic© labiryntu
 * @param width warto˜† szeroko˜ci labiryntu
 */
void del(lab **wsk, int width);
/**
 * @brief zapis labiryntu do pliku
 *
 * @param wsk wska«nik na tablic© labiryntu
 * @param width warto˜† szeroko˜ci labiryntu
 * @param heigh warto˜† wysoko˜ci labiryntu
 * @param name wprowadzona nazwa do zapisu
 */
void printsave(lab **wsk, int heigh, int width, QString name);
/**
 * @brief kopiuje z jednej tablicy do drugiej tyle ile jest to mo¾liwe
 *
 * @param oldtab wska«nik na star¥ tablic© labiryntu
 * @param newtab wska«nik nowej tablicy labirntu
 * @param heigh warto˜† wysoko˜ci labiryntu
 * @param width warto˜† szeroko˜ci labiryntu
 * @param newheigh nowa warto˜† wysoko˜ci labiryntu
 * @param newwidth nowa warto˜† szeroko˜ci labiryntu
 */
void copy(lab **oldtab,lab **newtab,int heigh, int width, int newheigh, int newwidth);
/**
 * @brief zamienia strukture p¢l dobrej drogi na zwykˆ¥ drog©, pozwala uruchomi† obliczanie drogi jeszcze raz
 *
 * @param wsk wska«nik na tablic© labiryntu
 * @param heigh warto˜† wysoko˜ci labiryntu
 * @param width warto˜† szeroko˜ci labiryntu
 */
void delgreen(lab **wsk,int heigh,int width);
/**
 * @brief ˆaduje plik z labiryntem o podanej nazwie z pola tekstowego
 *
 * @param wsk wska«nik na tablic© labiryntu
 * @param heigh warto˜† wysoko˜ci labiryntu
 * @param width warto˜† szeroko˜ci labiryntu
 * @param scale mno¾nik domy˜lnej wielko˜ci graficznych zmiennych struktury labiryntu
 * @param name wprowadzona nazwa do wczytania
 * @return zwraca wska«nik na tablic© ze struktur¥ labiryntu
 */
lab ** load(lab **wsk, int &heigh, int &width, QString name,double scale);
/**
 * @brief Tworzenie zmiennych obrazowych
 *
 * @param wsk wska«nik na tablic© labiryntu
 * @param heigh warto˜† wysoko˜ci labiryntu
 * @param width warto˜† szeroko˜ci labiryntu
 * @param scale mno¾nik domy˜lnej wielko˜ci graficznych zmiennych struktury labiryntu
 */
void createpics(lab **wsk, int heigh, int width,double scale);
/**
 * @brief kasowanie zmiennych obrazowych
 *
 * @param wsk wska«nik na tablic© labiryntu
 * @param heigh warto˜† wysoko˜ci labiryntu
 * @param width warto˜† szeroko˜ci labiryntu
 */
void deletepics(lab **wsk, int heigh, int width);

#endif // TABSOP_H

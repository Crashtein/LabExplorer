/**
 * \file mainwindow.h
 * \brief Plik nagˆ¢wkowy moduˆu \a mainwindow.
 *
 * Moduˆ \a mainwindow zawiera funkcje niezb©dne
 * do inicjacji GUI oraz interakcji z nim
 *
 *
 * \see mainwindow.cpp
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QGraphicsRectItem>
#include <QListWidgetItem>

///struktura listy z opisem drogi przez labirynt
struct way_description{     ///struktura dla listy ruch¢w
    ///pole move zawiera ruch opisuj¥cy kierunek przemieszczania
    QString move;
    ///wska«nik na nowe pole
    way_description* nextmove;
};

///struktura tablicy labiryntu
struct lab      ///definicja struktury p¢l labiryntu
{
    ///pole typu struktury 0-˜ciana.1-droga,2-start,3-koniec,4-dobra droga
    short str_type;
    ///okre˜la czy pole zwiedzone 0-nie 1-raz 2-˜lepy zauˆek
    short exp;
    ///obiekt graficzny, odpowiada kolorem dla warto˜ci str_type
    QGraphicsRectItem * pic;
};

///struktura listy z nazwami plik¢w labirynt¢w
struct lab_list{
    ///pole nazwy labiryntu
    std::string lab_name;
    ///wska«nik na now¥ nazw© labiryntu
    lab_list *next_lab;
};

/**
 * @brief UserInterface
 *
 */
namespace Ui {
/**
 * @brief Klasa MainWindow
 *
 */
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ///Okno MainWindow
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    /**
     * @brief Prywatne funkcje mainwindow
     *
     */
    /// @cond COND1
private slots:                                      ///<funkcje przycisk¢w, slider¢w i radioButton'¢w
    /**
     * @brief Funkcja zamykania po przyci˜ni©ciu przycisku 'Zamknij'
     *
     */
    void on_pushButton_close_clicked();
    /**
     * @brief Funkcja resetowania po przyci˜ni©ciu przycisku 'Reset'
     *
     */
    void on_pushButton_reset_clicked();
    /**
     * @brief Przeˆ¥czanie w tryb dodawania p¢l ˜cian
     *
     */
    void on_radioButton_wall_clicked();
    /**
     * @brief Przeˆ¥czanie w tryb dodawania p¢l drogi
     *
     */
    void on_radioButton_way_clicked();
    /**
     * @brief Przeˆ¥czanie w tryb dodawania p¢l startu
     *
     */
    void on_radioButton_start_clicked();
    /**
     * @brief Przeˆ¥czanie w tryb dodawania p¢l koäca
     *
     */
    void on_radioButton_end_clicked();
    /**
     * @brief Funkcja generowania labiryntu po przyci˜ni©ciu przycisku 'Generuj labirynt'
     *
     */
    void on_pushButton_labGen_clicked();
    /**
     * @brief Funkcja wyznaczania drogi po przyci˜ni©ciu przycisku 'Znajd« drog©'
     *
     */
    void on_pushButton_make_clicked();
    /**
     * @brief Funkcja zapisywania struktury labiryntu do pliku
     *
     */
    void on_pushButton_save_clicked();
    /**
     * @brief Funkcja wczytywania struktury labiryntu z pliku
     *
     */
    void on_pushButton_load_clicked();
    /**
     * @brief Funkcja otwierania wybranego labirytnu z listy
     *
     */
    void on_pushButton_open_clicked();
    /**
     * @brief Funkcja usuwania wybranego labiryntu z listy
     *
     */
    void on_pushButton_delete_clicked();
    /**
     * @brief Update aktualnego rozmiaru wy˜wietlanego na lcd
     *
     */
    void clockupdate();
    /**
     * @brief Update sceny dla graphicView
     *
     */
    void picsupdate();
    /**
     * @brief czyszczenie listy opisu drogi, kasuje wszystkie elementy listy
     *
     * @param description_head wska«nik na gˆow© listy opisuj¥cej drog© przej˜cia przez labirynt
     */
    void del_description(way_description* &description_head);
    /**
     * @brief wypisuje list© ruch¢w
     *
     * @param description_head wska«nik na gˆow© listy opisuj¥cej drog© przej˜cia przez labirynt
     */
    void text_update(way_description* description_head);
    /**
     * @brief funkcja zmiany struktury wskazanego przez myszk© bloku
     *
     * @param mouseEvent zmienna podana przez funkcj© mousePressEvent, zawiera wsp¢ˆrz©dne klikni©cia
     */
    void	 mousePressEvent(QMouseEvent * mouseEvent);
    /**
     * @brief funkcja przeskalowywuj¥ca obrazy na ekranie
     *
     * @param arg1 nowa warto˜† na SpinBoxi'e
     */
    void on_doubleSpinBox_valueChanged(double arg1);
    /**
     * @brief aduje list© zapisanych labirynt¢w z pliku LabExplorer.data
     *
     * @param lab_list_head wska«nik na gˆow© listy spisu labirynt¢w
     */
    void load_lab_list(lab_list* &lab_list_head);
    /**
     * @brief Pokazuje liste labirynt¢w w elemencie listView
     *
     * @param lab_list_head wska«nik na gˆow© listy spisu labirynt¢w
     */
    void show_lab_list(lab_list* lab_list_head);
    /**
     * @brief Kasuje list© z nazwami plik¢w labirynt¢w
     *
     * @param lab_list_head wska«nik na gˆow© listy spisu labirynt¢w
     */
    void del_lab_list(lab_list* &lab_list_head);
    /**
     * @brief otwiera labirynt z listy po dwukrotnym klikni©ciu
     *
     * @param item element listy GUI, dwukrotnie klikni©ty przez u¾ytkownika
     */
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    /**
     * @brief Zapisuje liste labirynt¢w do pliku
     *
     * @param lab_list_head wska«nik na gˆow© listy spisu labirynt¢w
     */
    void save_lab_list(lab_list* lab_list_head);
    /**
     * @brief Dodawanie nowej pozycji do listy labirynt¢w
     *
     * @param lab_list_head wska«nik na gˆow© listy spisu labirynt¢w
     * @param new_lab_name nowa nazwa labiryntu
     */
    void add_new_lab(lab_list* &lab_list_head,QString new_lab_name);
    /**
     * @brief Kasowanie pozycji labiryntu o podanej nazwie z listy
     *
     * @param lab_list_head wska«nik na gˆow© listy spisu labirynt¢w
     * @param lab_name nowa nazwa labiryntu
     */
    void del_lab_element(lab_list* &lab_list_head, QString lab_name);
private:
    ///Okno UI MainWindow
    Ui::MainWindow *ui;
    ///zmienna przechowuj¥ca obrazy struktur p¢l labiryntu
    QGraphicsScene *scene;
    ///Wska«nik na labirynt
    lab **tab;
    ///wysoko˜† labiryntu
    int w;
    ///szerokosc labiryntu
    int h;
    ///zmienna dla edytowania labiryntu
    int edit_mode;
    ///wsp¢ˆczynnik skali
    double scale;
    ///gˆowa listy z ruchami
    way_description* description_head;
    ///gˆowa listy z zapisanymi labiryntami
    lab_list* lab_list_head;
};
/// @endcond



#endif // MAINWINDOW_H

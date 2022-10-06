#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QTextStream>
#include <QFileDialog>
#include <QDir>
#include <QResource>
#include <QFile>
#include <QTranslator>
#include <QApplication>
#include <QKeyEvent>
#include <QEvent>
#include <QDebug>
#include <QPrinter>
#include <QPrintDialog>
#include <QMdiArea>
#include <QGridLayout>
#include <QTextEdit>
#include <QMdiSubWindow>
#include <QToolBar>
#include <QMenu>
#include <QTextDocumentFragment>
#include <QTextDocument>
#include <QPushButton>
#include <QFontDialog>
#include <QIcon>
#include <QDateTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void save_as_click();

    void open_click();

    void open_read_click();

    void rus_click();

    void eng_click();

    void dark_click();

    void light_click();

    void print_click();

    void add_time_click();

    void new_click();

    void chng_font();

    void get_font_sl();

    void set_font_sl();

    void l_align_sl();

    void r_align_sl();

    void c_align_sl();

protected:
    virtual void keyReleaseEvent(QKeyEvent *event);
private:
    Ui::MainWindow *ui;

    QTranslator *translator;

    QMenu *fileMenu;
    QMenu *langMenu;
    QMenu *themeMenu;
    QMenu *openMenu;

    QAction *saveAct;
    QAction *printAct;
    QAction *exitAct;
    QAction *OpenAct;
    QAction *OpenActRead;
    QAction *rusAct;
    QAction *engAct;
    QAction *darkAct;
    QAction *lightAct;
    QAction *newAct;

    QGridLayout *lay;

    QMdiArea *mdiArea;

    QTextEdit *textEdit;

    QWidget *centralW;

    QToolBar *txtBar;
    QPushButton *font_button;
    QPushButton *get_font_button;
    QPushButton *set_font_button;
    QPushButton *left_alignment_btn;
    QPushButton *right_alignment_btn;
    QPushButton *centre_alignment_btn;
    QPushButton *clock_btn;

    QFont *font_g;


    void lang_switch(QString lang);
};

#endif // MAINWINDOW_H

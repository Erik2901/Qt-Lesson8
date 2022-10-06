#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fileMenu = menuBar()->addMenu(tr("File"));
    langMenu = menuBar()->addMenu(tr("Language"));
    themeMenu = menuBar()->addMenu(tr("Theme"));
    newAct = fileMenu->addAction(tr("New File (Ctrl + N)"));
    openMenu = fileMenu->addMenu(tr("Open"));
    saveAct = fileMenu->addAction(tr("Save As (Ctrl + S)"));
    printAct = fileMenu->addAction(tr("Print (Ctrl + P)"));
    exitAct = fileMenu->addAction(tr("Exit (Ctrl + Q)"));
    OpenAct = openMenu->addAction(tr("Open File (Ctrl + O)"));
    OpenActRead = openMenu->addAction(tr("Open File Only Reading"));
    rusAct = langMenu->addAction(tr("Rus"));
    engAct = langMenu->addAction(tr("Eng"));
    darkAct = themeMenu->addAction(tr("Dark"));
    lightAct = themeMenu->addAction(tr("Light"));
    translator = new QTranslator();

    mdiArea = new QMdiArea(this);
    textEdit = new QTextEdit(this);
    centralW = new QWidget(this);
    lay = new QGridLayout(this);
    setCentralWidget(centralW);
    centralW->setLayout(lay);
    lay->addWidget(mdiArea,1,0,10,5);
    mdiArea->addSubWindow(textEdit);

    txtBar = addToolBar(tr("Tool Bar"));
    font_button = new QPushButton(this);
    font_button->setIcon(QIcon(":/res/font.png"));

    get_font_button = new QPushButton(this);
    get_font_button->setIcon(QIcon(":/res/get-format.png"));

    set_font_button = new QPushButton(this);
    set_font_button->setIcon(QIcon(":/res/set-format.png"));

    left_alignment_btn = new QPushButton(this);
    left_alignment_btn->setIcon(QIcon(":/res/left-text-alignment.png"));

    centre_alignment_btn = new QPushButton(this);
    centre_alignment_btn->setIcon(QIcon(":/res/center-text-alignment.png"));

    right_alignment_btn = new QPushButton(this);
    right_alignment_btn->setIcon(QIcon(":/res/right-text-alignment.png"));

    clock_btn = new QPushButton(this);
    clock_btn->setIcon(QIcon(":/res/clock.png"));

    txtBar->addWidget(font_button);
    txtBar->addWidget(left_alignment_btn);
    txtBar->addWidget(centre_alignment_btn);
    txtBar->addWidget(right_alignment_btn);
    txtBar->addWidget(get_font_button);
    txtBar->addWidget(set_font_button);
    txtBar->addWidget(clock_btn);
    font_g = new QFont();

    connect(saveAct,SIGNAL(triggered(bool)),this,SLOT(save_as_click()));
    connect(exitAct,SIGNAL(triggered(bool)),this,SLOT(close()));
    connect(OpenAct,SIGNAL(triggered(bool)),this,SLOT(open_click()));
    connect(OpenActRead,SIGNAL(triggered(bool)),this,SLOT(open_read_click()));
    connect(rusAct,SIGNAL(triggered(bool)),this,SLOT(rus_click()));
    connect(engAct,SIGNAL(triggered(bool)),this,SLOT(eng_click()));
    connect(darkAct,SIGNAL(triggered(bool)),this,SLOT(dark_click()));
    connect(lightAct,SIGNAL(triggered(bool)),this,SLOT(light_click()));
    connect(printAct,SIGNAL(triggered(bool)),this,SLOT(print_click()));
    connect(newAct,SIGNAL(triggered(bool)),this,SLOT(new_click()));
    connect(font_button,SIGNAL(clicked(bool)),this,SLOT(chng_font()));
    connect(get_font_button,SIGNAL(clicked(bool)),this,SLOT(get_font_sl()));
    connect(set_font_button,SIGNAL(clicked(bool)),this,SLOT(set_font_sl()));
    connect(left_alignment_btn,SIGNAL(clicked(bool)),this,SLOT(l_align_sl()));
    connect(right_alignment_btn,SIGNAL(clicked(bool)),this,SLOT(r_align_sl()));
    connect(centre_alignment_btn,SIGNAL(clicked(bool)),this,SLOT(c_align_sl()));
    connect(clock_btn,SIGNAL(clicked(bool)),this,SLOT(add_time_click()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete translator;
    delete mdiArea;
    delete textEdit;
    delete centralW;
    delete txtBar;
    delete font_button;
    delete get_font_button;
    delete set_font_button;
    delete left_alignment_btn;
    delete right_alignment_btn;
    delete centre_alignment_btn;
    delete font_g;
    delete clock_btn;
}

void MainWindow::lang_switch(QString lang){
    translator->load(":/res/switchlang_" + lang + ".qm");
    qApp->installTranslator(translator);
    fileMenu->setTitle(tr("File"));
    langMenu->setTitle(tr("Language"));
    themeMenu->setTitle(tr("Theme"));
    openMenu->setTitle(tr("Open"));
    saveAct->setText(tr("Save As (Ctrl + S)"));
    newAct->setText(tr("New File (Ctrl + N)"));
    printAct->setText(tr("Print (Ctrl + P)"));
    exitAct->setText(tr("Exit (Ctrl + Q)"));
    OpenAct->setText(tr("Open File (Ctrl + O)"));
    OpenActRead->setText(tr("Open File Only Reading"));
    rusAct->setText(tr("Rus"));
    engAct->setText(tr("Eng"));
    darkAct->setText(tr("Dark"));
    lightAct->setText(tr("Light"));
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{

    if(event->key() == Qt::Key_O && event->modifiers() == Qt::ControlModifier){
        open_click();
    }
    if(event->key() == Qt::Key_S && event->modifiers() == Qt::ControlModifier){
        save_as_click();
    }
    if(event->key() == Qt::Key_N && event->modifiers() == Qt::ControlModifier){
        new_click();
    }
    if(event->key() == Qt::Key_Q && event->modifiers() == Qt::ControlModifier){
        qApp->quit();
    }
    if(event->key() == Qt::Key_P && event->modifiers() == Qt::ControlModifier){
        print_click();
    }
    if(event->key() == Qt::Key_T && event->modifiers() == Qt::ControlModifier){
        add_time_click();
    }
}

void MainWindow::new_click()
{
    textEdit = new QTextEdit(this);
    mdiArea->addSubWindow(textEdit);
    textEdit->show();
}

void MainWindow::chng_font()
{
    QMdiSubWindow *activeSubWindow = mdiArea->activeSubWindow();
    QWidget *widg = activeSubWindow->widget();
    QTextEdit *tedit = (QTextEdit*)widg;
    QFont font = tedit->textCursor().charFormat().font();
    QFontDialog fntDlg(font,this);
    bool b[]={true};
    font = fntDlg.getFont(b);
    if(b[0]){
        QTextCharFormat fmt;
        fmt.setFont(font);
        tedit->textCursor().setCharFormat(fmt);
    }

}

void MainWindow::get_font_sl()
{
    QMdiSubWindow *activeSubWindow = mdiArea->activeSubWindow();
    QWidget *widg = activeSubWindow->widget();
    QTextEdit *tedit = (QTextEdit*)widg;
    *font_g = tedit->textCursor().charFormat().font();
}

void MainWindow::set_font_sl()
{
    QMdiSubWindow *activeSubWindow = mdiArea->activeSubWindow();
    QWidget *widg = activeSubWindow->widget();
    QTextEdit *tedit = (QTextEdit*)widg;
    QFont font = tedit->textCursor().charFormat().font();
    QTextCharFormat fmt;
    fmt.setFont(*font_g);
    tedit->textCursor().setCharFormat(fmt);
}

void MainWindow::l_align_sl()
{
    QMdiSubWindow *activeSubWindow = mdiArea->activeSubWindow();
    QWidget *widg = activeSubWindow->widget();
    QTextEdit *tedit = (QTextEdit*)widg;
    tedit->setAlignment(Qt::AlignLeft);
}

void MainWindow::r_align_sl()
{
    QMdiSubWindow *activeSubWindow = mdiArea->activeSubWindow();
    QWidget *widg = activeSubWindow->widget();
    QTextEdit *tedit = (QTextEdit*)widg;
    tedit->setAlignment(Qt::AlignRight);
}

void MainWindow::c_align_sl()
{
    QMdiSubWindow *activeSubWindow = mdiArea->activeSubWindow();
    QWidget *widg = activeSubWindow->widget();
    QTextEdit *tedit = (QTextEdit*)widg;
    tedit->setAlignment(Qt::AlignCenter);
}

void MainWindow::save_as_click()
{
    if (mdiArea == nullptr)
    {
        return;
    }
    QMdiSubWindow *activeSubWindow = mdiArea->activeSubWindow();
    QWidget *widg = activeSubWindow->widget();
    QTextEdit *tedit = (QTextEdit*)widg;
    QString s = QFileDialog::getSaveFileName(this, "window", QDir::current().path(), "Text(*.txt)");
    if(s.length() > 0){
        QString ext = QString(&(s.data()[s.length() - 4]));
        if(ext==".txt"){
            QFile file(s);
            if(file.open(QFile::WriteOnly | QFile::NewOnly))
            {
                QTextStream stream(&file);
                stream << tedit->toPlainText();
                file.close();
            }
        }
    }
}

void MainWindow::open_click()
{
    QString s = QFileDialog::getOpenFileName(this, "window", QDir::current().path(), "Text(*.txt)");
    int index = s.indexOf(".txt");

    if (s.length()!=0){
        if(index != -1 && s.length()-4 == index){
            QFile file(s);
            if(file.open(QFile::ReadOnly | QFile::ExistingOnly))
            {
                QTextStream stream(&file);
                textEdit = new QTextEdit(this);
                textEdit->setPlainText(stream.readAll());
                textEdit->setReadOnly(false);
                mdiArea->addSubWindow(textEdit);
                textEdit->show();
                file.close();
            }
        }
    }
}

void MainWindow::open_read_click()
{
    QString s = QFileDialog::getOpenFileName(this, "window", QDir::current().path(), "Text(*.txt)");
    int index = s.indexOf(".txt");

    if (s.length()!=0){
        if(index != -1 && s.length()-4 == index){
            QFile file(s);
            if(file.open(QFile::ReadOnly | QFile::ExistingOnly))
            {
                QTextStream stream(&file);
                textEdit = new QTextEdit(this);
                textEdit->setPlainText(stream.readAll());
                textEdit->setReadOnly(true);
                mdiArea->addSubWindow(textEdit);
                textEdit->show();
                file.close();
            }
        }
    }
}

void MainWindow::rus_click()
{
    lang_switch("ru");
}

void MainWindow::eng_click()
{
    lang_switch("en");
}

void MainWindow::dark_click()
{
    qApp->setStyleSheet("QMainWindow { background-color:#808080} QPushButton {background-color:#A9A9A9; color:#000000;}");
}

void MainWindow::light_click()
{
    qApp->setStyleSheet("QMainWindow { background-color:#F5FFFA } QPushButton {background-color:#F0F8FF; color:#808080}");
}

void MainWindow::print_click()
{
    if (mdiArea == nullptr)
    {
        return;
    }
    QMdiSubWindow *activeSubWindow = mdiArea->activeSubWindow();
    QWidget *widg = activeSubWindow->widget();
    QTextEdit *tedit = (QTextEdit*)widg;
    QPrinter printer;
    QPrintDialog dlg(&printer,this);
    dlg.setWindowTitle("Print");
    if(dlg.exec() != QDialog::Accepted){
        return;
    }
    tedit->print(&printer);
}

void MainWindow::add_time_click()
{
    QDateTime dateTime = QDateTime::currentDateTime();
    QTime time = dateTime.time();
    QDate date = dateTime.date();
    QString dt = QString::number(time.hour()) + ":" + QString::number(time.minute()) + "  " + QString::number(date.day()) + "․" + QString::number(date.month()) + "․" + QString::number(date.year());
    QMdiSubWindow *activeSubWindow = mdiArea->activeSubWindow();
    QWidget *widg = activeSubWindow->widget();
    QTextEdit *tedit = (QTextEdit*)widg;
    tedit->textCursor().insertText(dt);
}


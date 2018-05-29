#include "menu.h"
#include "ui_menu.h"

menu::menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);
}

menu::~menu()
{
    delete ui;
}

void menu::on_nivel1_clicked()
{
    escenarios = new niveles();
    escenarios->objetosN1();
    escenarios->actualizacion();
    escenarios->show();
    this->close();
}

void menu::on_nivel2_clicked()
{
    escenarios = new niveles();
    escenarios->objetosN2();
    escenarios->actualizacion();
    escenarios->show();
    this->close();
}

void menu::on_nivel3_clicked()
{

    escenarios = new niveles();
    escenarios->objetosN3();
    escenarios->actualizacion();
    escenarios->show();
    this->close();
}

void menu::on_nivel4_clicked()
{
    escenarios = new niveles();
    escenarios->objetosN4();
    escenarios->actualizacion();
    escenarios->show();
    this->close();
}

void menu::on_nivel5_clicked()
{
    escenarios = new niveles();
    escenarios->objetosN5();
    escenarios->actualizacion();
    escenarios->show();
    this->close();
}

void menu::on_nivel6_clicked()
{
    escenarios = new niveles();
    escenarios->objetosN6();
    escenarios->actualizacion();
    escenarios->show();
    this->close();
}

void menu::on_nivel7_clicked()
{
    escenarios = new niveles();
    escenarios->objetosN7();
    escenarios->actualizacion();
    escenarios->show();
    this->close();
}

void menu::on_nivel8_clicked()
{
    escenarios = new niveles();
    escenarios->objetosN8();
    escenarios->actualizacion();
    escenarios->show();
    this->close();
}

void menu::on_nivel9_clicked()
{
    escenarios = new niveles();
    escenarios->objetosN9();
    escenarios->actualizacion();
    escenarios->show();
    this->close();
}

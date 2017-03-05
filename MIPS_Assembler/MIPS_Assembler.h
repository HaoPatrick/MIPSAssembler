#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MIPS_Assembler.h"
class MIPS_Assembler : public QMainWindow
{
	Q_OBJECT

public:
	MIPS_Assembler(QWidget *parent = Q_NULLPTR);

private:
	Ui::MIPS_AssemblerClass ui;
	private slots:
	void on_fileButton_clicked();
};

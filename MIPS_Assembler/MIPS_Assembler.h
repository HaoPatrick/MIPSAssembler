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
	void changeWindowTitle();

	private slots:
	void openFile();
	void saveFile();
	void createActions();
	void textChanged();
protected:
	std::string filePath;
	bool fileSaved = true;
	//void contextMenuEvent(QContextMenuEvent *event);
};

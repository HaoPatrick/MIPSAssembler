#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MIPS_Assembler.h"
#include <QFileDialog>
#include <fstream>
#include <string>
#include <iostream>
#include <QDebug>
#include <QMenuBar>
class MIPS_Assembler : public QMainWindow
{
	Q_OBJECT

public:
	MIPS_Assembler(QWidget *parent = Q_NULLPTR);

private:
	Ui::MIPS_AssemblerClass ui;
	void changeWindowTitle();
	QString parseLine(std::string eachLine);

	private slots:
	void openFile();
	void saveFile();
	void createActions();
	void textChanged();
	void testHTML();
	void pasteFile() {
		ui.textEdit->paste();
	}
	void copyFile() {
		ui.textEdit->copy();
	}
	void cutFile() {
		ui.textEdit->cut();
	}
protected:
	std::string filePath;
	bool fileSaved = true;
	//void contextMenuEvent(QContextMenuEvent *event);
};

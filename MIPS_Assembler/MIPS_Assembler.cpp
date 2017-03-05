#include "MIPS_Assembler.h"
#include <QFileDialog>
#include <fstream>
#include <string>
#include <QDebug>
#include <QMenuBar>
MIPS_Assembler::MIPS_Assembler(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	createActions();
}

void MIPS_Assembler::openFile() {
	QString fileName = QFileDialog::getOpenFileName(
		this, tr("Open File"), "/", tr("Text File (*.txt)")
	);
	ui.fileLabel->setText(fileName);
	this->filePath = fileName.toStdString();

	std::fstream targetFile;
	targetFile.open(this->filePath, std::ios::in);
	std::string fileLine;
	ui.textEdit->clear();
	if (targetFile.is_open()) {
		while (std::getline(targetFile, fileLine)) {
			ui.textEdit->append(QString::fromStdString(fileLine));
		}
	}
	targetFile.close();
}

void MIPS_Assembler::saveFile() {
	QString plainText = ui.textEdit->toPlainText();
	if (this->filePath != "") {
		std::ofstream targetFile;
		targetFile.open(this->filePath, std::ios::trunc);
		targetFile << plainText.toStdString();
		targetFile.close();
		qDebug() << QString::fromStdString(this->filePath);
		qDebug() << "triggered agein";
	}
}

void MIPS_Assembler::createActions() {
	connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
	connect(ui.actionSave, SIGNAL(triggered()), this, SLOT(saveFile()));
}

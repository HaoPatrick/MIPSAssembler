#include "MIPS_Assembler.h"
#include <QFileDialog>
#include <fstream>
#include <string>
#include <iostream>
#include <QDebug>
#include <QMenuBar>

MIPS_Assembler::MIPS_Assembler(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	createActions();
}

void MIPS_Assembler::createActions() {
	connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
	connect(ui.actionSave, SIGNAL(triggered()), this, SLOT(saveFile()));
	connect(ui.textEdit, SIGNAL(textChanged()), this, SLOT(textChanged()));
	connect(ui.actionTest, SIGNAL(triggered()), this, SLOT(testHTML()));
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
			ui.textEdit->append(parseLine(fileLine));
		}
	}
	targetFile.close();
	//qDebug() << ui.textEdit->toHtml();
}

void MIPS_Assembler::saveFile() {
	QString plainText = ui.textEdit->toPlainText();
	if (this->filePath != "") {
		std::ofstream targetFile;
		targetFile.open(this->filePath, std::ios::trunc);
		targetFile << plainText.toStdString();
		targetFile.close();
	}
	fileSaved = true;
	changeWindowTitle();
}

void MIPS_Assembler::changeWindowTitle() {
	QString preWindowTitle = windowTitle();
	if (fileSaved) {
		if (preWindowTitle.endsWith('*')) {
			preWindowTitle.remove(preWindowTitle.lastIndexOf('*'), 1);
		}
	}
	else {
		if(!preWindowTitle.endsWith('*'))
			preWindowTitle.push_back('*');
	}
	setWindowTitle(preWindowTitle);
}
void MIPS_Assembler::textChanged() {
	fileSaved = false;
	changeWindowTitle();
}

QString MIPS_Assembler::parseLine(std::string eachLine) {
	QString qLine;
	QString htmlLine;
	QStringList lineTokens;
	qLine = QString::fromStdString(eachLine);
	lineTokens = qLine.split(' ', QString::SkipEmptyParts);
	for (int i = 0; i < lineTokens.size(); i++) {
		if (i % 2)
			htmlLine.append(QString("<span style='color:blue'>%1 </span> ").arg(lineTokens.at(i)));
		else
			htmlLine.append(QString("<span style='color:red'>%1 </span> ").arg(lineTokens.at(i)));
	}
	return htmlLine;
}
void MIPS_Assembler::testHTML() {
	ui.textEdit->append("<h2>asdf</h2>");
}

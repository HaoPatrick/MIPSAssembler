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

	qLine = QString::fromStdString(eachLine);
	QRegExp instrucReg("(\\s*)?(\\w+)(\\s+)(\\$\\w+)(\\s*)?(,)(\\s*)?(\\$\\w+)(\\s*)?(,)(\\s*)?(\\$\\w+)(\\s*)?(;)(\\s*)(\\/\\/.*)?");
	// Pattern: add $zero, $zero, $zero;
	QRegExp startReg("(\\s*)(\\w+)(\\s*)(:)(\\s*)(\\/\\/.*)?");
	// Pattern: start:\n
	QRegExp labelReg("(\\s*)(\\.\\w+)(\\s+)(\\w+)(\\s*)(\\/\\/.*)?");
	// Pattern: .text 0x00000000
	QRegExp commentReg("(\\s*)(\\/\\/)(\\s*)(.+)");
	// Pattern: //comment here

	int instructPos = instrucReg.indexIn(qLine);
	int startPos = startReg.indexIn(qLine);
	int labelPos = labelReg.indexIn(qLine);
	int commentPos = commentReg.indexIn(qLine);
	QStringList instructTokens = instrucReg.capturedTexts();
	QStringList startTokens = startReg.capturedTexts();
	QStringList labelTokens = labelReg.capturedTexts();
	QStringList commentTokens = commentReg.capturedTexts();
	if (instructPos > -1) {
		for (int i = 1; i < instructTokens.count(); i++) {
			if (instructTokens.at(i).contains('$')) {
				htmlLine.append(QString("<span style='color: #16a085'>%1</span>").arg(instructTokens.at(i)));
			}
			else if(instructTokens.at(i).contains(',')){
				htmlLine.append(QString("<span style='color: #9b59b6'>%1</span>").arg(instructTokens.at(i)));
			}
			else if (instructTokens.at(i).contains("//")) {
				htmlLine.append(QString("<span style='color: #bdc3c7'>%1</span>").arg(instructTokens.at(i)));
			}
			else {
				htmlLine.append(QString("<span style='color: #7f8c8d'>%1</span>").arg(instructTokens.at(i)));
			}
		}
	}
	else if(startPos>-1){
		for (int i = 1; i < startTokens.count(); i++) {
			if(startTokens.at(i).contains('st'))
				// Hard code here
				htmlLine.append(QString("<span style='color: #e67e22'>%1</span>").arg(startTokens.at(i)));
			else if (startTokens.at(i).contains(':')) {
				htmlLine.append(QString("<span style='color: #9b59b6'>%1</span>").arg(startTokens.at(i)));
			}
			else if (instructTokens.at(i).contains("//")) {
				htmlLine.append(QString("<span style='color: #bdc3c7'>%1</span>").arg(startTokens.at(i)));
			}
			else {
				htmlLine.append(QString("<span style='color: #7f8c8d'>%1</span>").arg(startTokens.at(i)));
			}
		}
	}
	else if (labelPos > -1) {
		for (int i = 1; i < labelTokens.count(); i++) {
			if (labelTokens.at(i).contains('.')) {
				htmlLine.append(QString("<span style='color: #e67e22'>%1</span>").arg(labelTokens.at(i)));
			}
			else if (labelTokens.at(i).contains(':')) {
				htmlLine.append(QString("<span style='color: #9b59b6'>%1</span>").arg(labelTokens.at(i)));
			}
			else if (instructTokens.at(i).contains("//")) {
				htmlLine.append(QString("<span style='color: #bdc3c7'>%1</span>").arg(labelTokens.at(i)));
			}
			else {
				htmlLine.append(QString("<span style='color: #9b59b6'>%1</span>").arg(labelTokens.at(i)));
			}
		}
	}
	else if (commentPos > -1) {
		htmlLine.append(QString("<span style='color: #bdc3c7'>%1</span>").arg(qLine));
	}
	else {
		htmlLine.append(QString("<span style='color: #9b59b6'>%1</span>").arg(qLine));
	}
	return htmlLine;
}
void MIPS_Assembler::testHTML() {
	ui.textEdit->append("<h2>asdf</h2>");
}

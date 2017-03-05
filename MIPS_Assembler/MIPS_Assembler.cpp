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

	std::fstream targetFile;
	targetFile.open(fileName.toStdString(), std::ios::in);
	std::string fileLine;
	ui.textEdit->clear();
	if (targetFile.is_open()) {
		while (std::getline(targetFile, fileLine)) {
			ui.textEdit->append(QString::fromStdString(fileLine));
		}
	}
	targetFile.close();
}

void MIPS_Assembler::createActions() {
	connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
}
//void MIPS_Assembler::contextMenuEvent(QContextMenuEvent *event) {
	//QMenu menu(this);
	//menu.addAction(actionOpen);
//}
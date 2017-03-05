#include "MIPS_Assembler.h"
#include <QFileDialog>
#include <fstream>
#include <string>
MIPS_Assembler::MIPS_Assembler(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

void MIPS_Assembler::on_fileButton_clicked() {
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
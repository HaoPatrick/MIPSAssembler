#pragma once
#include <QtWidgets/QMainWindow>
#include "HTMLContent.h"
class OpenedFile
{
public:
	OpenedFile();
	~OpenedFile();
	void append(QString line) {
		this->rawLine.append(line);
		HTMLLine htmlResult;
		htmlResult.hilightRawText(line.toStdString());
		this->htmlLine.append(htmlResult.fetchHTML());
	}
	QString getLines() {
		QString returnResult;
		for (int i = 0; i < htmlLine.size(); i++) {
			returnResult += (htmlLine.at(i) + "<br>");
		}
		return returnResult;
	}
protected:
	QStringList htmlLine;
	QStringList rawLine;
};


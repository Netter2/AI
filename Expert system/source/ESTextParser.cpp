
#include "ESTextParser.h"

#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QDebug>

QString ReadWord (QTextStream & ts) {
    QChar c = ' ';
    while ((c == ' ') || (c == '\t') || (c == '\n') || (c == '\r')) {
        ts >> c;
    }
    QString res;
    while ((c != ' ') && (c != '\t') && (c != '\n') && (c != '\r') && (!ts.atEnd ())) {
        res += c;
        ts >> c;
    }
    //qDebug () << "RW: " << res;
    return res;
}

QString ReadLine (QTextStream & ts) {
    QChar c = ' ';
    while ((c == ' ') || (c == '\t') || (c == '\n') || (c == '\r')) {
        ts >> c;
    }
    QString res = c + ts.readLine ();
    //qDebug () << "RL: " << res;
    return res;
}

void ESTextParser::Parse () {
    QFile textFile (filename);
    if (!textFile.open (QIODevice::ReadOnly)) {
        qFatal ("ERROR: Cannot open the file.");
    }
    //qFatal ("FATAL ERROR: I do not want to work."); // DELETE THIS
    QTextStream textStream (&textFile);
    textStream.setCodec(QTextCodec::codecForName("UTF-8"));
    QString buffer = ReadLine (textStream); // считает слово "abilities"
    for (int i = 0; i < 3; i ++) { // считывание трёх категорий
        buffer = ReadLine (textStream); // считает слово "question"
        while (!textStream.atEnd ()) { // цикл для считывания вопросов
            bool nextCategory = false;
            Question question;
            question.text = ReadLine (textStream);
            // считает "tags:" или "answer"
            buffer = ReadWord (textStream);
            if (buffer == "tags:") {
                //textStream >> buffer; // считает первый тег
                buffer = ReadWord (textStream);
                while (buffer != "answer") {
                    if (buffer [buffer.size () - 1] == ',') {
                        buffer.chop (1);
                    }
                    question.tags.append (buffer);
                    //textStream >> buffer;
                    buffer = ReadWord (textStream);
                }
            }
            // слово "answer" уже считано
            while (true) { // цикл для считывания ответов
                Answer answer;
                answer.text = ReadLine (textStream);
                buffer = ReadWord (textStream);
                // считает либо одну из разбалловок, либо "tags:", либо "answer",
                // либо "question", либо название категории, либо конец файла
                //qDebug () << "======" << buffer << "======";
                while ((buffer == "work") || (buffer == "college") || (buffer == "university")) { // считывание разбалловки
                    if (buffer == "work") {
                        buffer = ReadWord (textStream);
                        answer.work = buffer.toInt ();
                        buffer = ReadWord (textStream);
                    }
                    else if (buffer == "college") {
                        buffer = ReadWord (textStream);
                        answer.college = buffer.toInt ();
                        buffer = ReadWord (textStream);
                    }
                    else if (buffer == "university") {
                        buffer = ReadWord (textStream);
                        answer.university = buffer.toInt ();
                        buffer = ReadWord (textStream);
                    }
                }
                if (buffer == "tags:") {
                    // считает первый тег
                    buffer = ReadWord (textStream);
                    while ((buffer != "answer")
                           && (buffer != "question")
                           && (buffer != "limitations")
                           && (buffer != "preferences")) {
                        if (buffer [buffer.size () - 1] == ',') {
                            buffer.chop (1);
                        }
                        answer.tags.append (buffer);
                        buffer = ReadWord (textStream);
                    }
                }
                question.answers.append (answer);
                if (buffer == "answer") {
                    continue;
                }
                else if (buffer == "question") {
                    break;
                }
                else if ((buffer == "limitations") || (buffer == "preferences")) {
                    nextCategory = true;
                    break;
                }
                else { // скорее всего, это EOF
                    nextCategory = true;
                    break;
                }
            }
            allQuestions [i].append (question);
            if (nextCategory) {
                break;
            }
        }
    }
    textFile.close ();
}

// debug function
void ESTextParser::Print () {
    for (int i = 0; i < 3; i ++) {
        for (int j = 0; j < allQuestions [i].size (); j ++) {
            qDebug () << "Question:";
            qDebug () << allQuestions [i] [j].text;
            qDebug () << allQuestions [i] [j].tags;
            for (int k = 0; k < allQuestions [i] [j].answers.size (); k ++) {
                qDebug () << "Answer " << k + 1 << ":";
                qDebug () << allQuestions [i] [j].answers [k].text;
                qDebug () << allQuestions [i] [j].answers [k].tags;
                qDebug () << allQuestions [i] [j].answers [k].work << "  "
                          << allQuestions [i] [j].answers [k].college << "  "
                          << allQuestions [i] [j].answers [k].university;
            }
        }
        qDebug () << "------------------------------";
    }
}

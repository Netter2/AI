#ifndef ESTEXTPARSER_H
#define ESTEXTPARSER_H

#include <QString>
#include <QVector>

struct Answer {
    QString text;
    int work;
    int college;
    int university;
    QVector <QString> tags;
    Answer () {
        work = 0;
        college = 0;
        university = 0;
    }
    void clear () {
        text = "";
        work = 0;
        college = 0;
        university = 0;
        tags.clear ();
    };
};

struct Question {
    QString text;
    QVector <QString> tags;
    QVector <Answer> answers;
    void clear () {
        text = "";
        tags.clear ();
        for (int i = 0; i < answers.size (); i ++) {
            answers [i].clear ();
        }
    }
};

class ESTextParser {
private:
    QString filename;
    QVector <Question> allQuestions [3];

public:
    ESTextParser () {
        filename = "text.txt";
    }
    void Parse ();
    QVector <Question> GetAbility () {
        return allQuestions [0];
    }
    QVector <Question> GetLimitation () {
        return allQuestions [1];
    }
    QVector <Question> GetPreference () {
        return allQuestions [2];
    }
    // debug functions
    void Print ();
};

#endif // ESTEXTPARSER_H

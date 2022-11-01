#ifndef PROGRAM_H
#define PROGRAM_H

#include "ESTextParser.h"
#include <QDebug>


void Assignment();
void newAssigment ();
Question NewQuestion();
// 'n' - задай следующий вопрос
// 'e' - закончились вопросы
// a - номер ответа начиная с нуля
char AddAnswer(int a);

#endif // PROGRAM_H

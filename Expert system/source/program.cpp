#include "program.h"
#include "ESTextParser.h"
#include "QRandomGenerator"
#include "QtMath"
#include "QString"

ESTextParser tp;
QVector <Question> abilities;
QVector <Question> limitations;
QVector <Question> preferences;
Question nowQuestion;
QVector <Question> allAbilities;
QVector <Question> allLimitation;
QVector <Question> allPreferencesWork;
QVector <Question> allPreferencesCollege;
QVector <Question> allPreferencesUniversity;
int i = 0;
int ww = 0, cc = 0, uu = 0;
bool pp = false;
bool ppp = false;
char winner;
QVector <QString> tt;

int mmin = 6;
float plan1 = 0.8;
float plan2 = 0.3;
bool ee = false;
QString eText = "Извините, мы не можем определить куда вас послать";

void newAssigment() {
    allAbilities.clear();
    allLimitation.clear();
    allPreferencesWork.clear();
    allPreferencesCollege.clear();
    allPreferencesUniversity.clear();
    i = 0;
    ww = 0;
    cc = 0;
    uu = 0;
    pp = false;
    ppp = false;
    allAbilities = abilities;
    for (int j = 0; j < limitations.size(); j++){
        if (limitations[j].tags.size() == 0){
            allLimitation.push_back(limitations[j]);
        }
    }
    for (int j = 0; j < preferences.size(); j++){
        if (preferences[j].answers[0].work != 0){
            allPreferencesWork.push_back(preferences[j]);
        }
        else if (preferences[j].answers[0].college != 0){
            allPreferencesCollege.push_back(preferences[j]);
        }
        else {
            allPreferencesUniversity.push_back(preferences[j]);
        }
    }
}

void Assignment(){
    tp.Parse();
    abilities = tp.GetAbility ();
    limitations = tp.GetLimitation ();
    preferences = tp.GetPreference ();
    newAssigment();
}

Question NewQuestion(){
    nowQuestion.clear();
    float perWork = 0;
    float perCollege = 0;
    float perUniversity = 0;
    int rand = 0;
    float mmax = 0;
    float mmax1 = 0;
    float mmax2 = 0;
    if (ww > 0 || cc > 0 || uu > 0){
        perWork = (float)ww / (float)(ww + cc + uu);
        perCollege = (float)cc / (float)(ww + cc + uu);
        perUniversity = (float)uu / (float)(ww + cc + uu);
    }
    if (allAbilities.size() > 0){
        rand = 0;
        nowQuestion = allAbilities[rand];
        allAbilities.remove(rand);
    }
    else if (allLimitation.size() > 0 && ((i < mmin) || (i >= mmin  && perWork < plan1
                                                                    && perCollege < plan1
                                                                    && perUniversity < plan1)) ){
        i++;
        rand = QRandomGenerator::global() -> bounded(0, allLimitation.size());
        nowQuestion = allLimitation[rand];
        allLimitation.remove(rand);
    }
    else if (perWork  < plan1
             && perCollege < plan1
             && perUniversity < plan1){
        pp = true;
        mmax = qMax(perWork, qMax (perCollege, perUniversity));
        if (mmax == perWork && allPreferencesWork.size() > 0){
            rand = QRandomGenerator::global() -> bounded(0, allPreferencesWork.size());
            nowQuestion = allPreferencesWork[rand];
            allPreferencesWork.remove(rand);
        }
        else if (mmax == perCollege && allPreferencesCollege.size() > 0){
            rand = QRandomGenerator::global() -> bounded(0, allPreferencesCollege.size());
            nowQuestion = allPreferencesCollege[rand];
            allPreferencesCollege.remove(rand);
        }
        else if (mmax == perUniversity && allPreferencesUniversity.size() > 0){
            rand = QRandomGenerator::global() -> bounded(0, allPreferencesUniversity.size());
            nowQuestion = allPreferencesUniversity[rand];
            allPreferencesUniversity.remove(rand);
        }
        else {
            if (mmax == perWork){
                mmax1 = qMax(perCollege, perUniversity);
            }
            else if (mmax == perCollege){
                mmax1 = qMax(perWork, perUniversity);
            }
            else {
                mmax1 = qMax(perWork, perCollege);
            }
            if (mmax1 > plan2){
                if (mmax1 == perWork && allPreferencesWork.size() > 0){
                    rand = QRandomGenerator::global() -> bounded(0, allPreferencesWork.size());
                    nowQuestion = allPreferencesWork[rand];
                    allPreferencesWork.remove(rand);
                }
                else if (mmax1 == perCollege && allPreferencesCollege.size() > 0){
                    rand = QRandomGenerator::global() -> bounded(0, allPreferencesCollege.size());
                    nowQuestion = allPreferencesCollege[rand];
                    allPreferencesCollege.remove(rand);
                }
                else if (mmax1 == perUniversity && allPreferencesUniversity.size() > 0){
                    rand = QRandomGenerator::global() -> bounded(0, allPreferencesUniversity.size());
                    nowQuestion = allPreferencesUniversity[rand];
                    allPreferencesUniversity.remove(rand);
                }
                else {
                    if (mmax1 == perWork){
                        mmax2 = qMax(perCollege, perUniversity);
                    }
                    else if (mmax1 == perCollege){
                        mmax2 = qMax(perWork, perUniversity);
                    }
                    else {
                        mmax2 = qMax(perWork, perCollege);
                    }
                    if (mmax2 > plan2){
                        if (mmax2 == perWork && allPreferencesWork.size() > 0){
                            rand = QRandomGenerator::global() -> bounded(0, allPreferencesWork.size());
                            nowQuestion = allPreferencesWork[rand];
                            allPreferencesWork.remove(rand);
                        }
                        else if (mmax2 == perCollege && allPreferencesCollege.size() > 0){
                            rand = QRandomGenerator::global() -> bounded(0, allPreferencesCollege.size());
                            nowQuestion = allPreferencesCollege[rand];
                            allPreferencesCollege.remove(rand);
                        }
                        else if (mmax2 == perUniversity && allPreferencesUniversity.size() > 0){
                            rand = QRandomGenerator::global() -> bounded(0, allPreferencesUniversity.size());
                            nowQuestion = allPreferencesUniversity[rand];
                            allPreferencesUniversity.remove(rand);
                        }
                        else{
                            nowQuestion.text = "Извините, мы не можем определить куда вас послать";
                            ee = true;
                        }
                    }
                }
            }
        }
    }
    else if (allLimitation.size() == 0){
        nowQuestion.text = "Извините, мы не можем определить куда вас послать";
        ee = false;
    }
    else {
        nowQuestion.text = "Мы знаем куда вам";
        nowQuestion.answers[0].text = "Узнать ответ";
    }
    return nowQuestion;
}

// true - задай следующий вопрос
char AddAnswer(int a){
    winner = 'e';
    float perWork = 0;
    float perCollege = 0;
    float perUniversity = 0;
    QVector <QString> tag;
    //qDebug () << ww << cc << uu << i;
    ww += nowQuestion.answers[a].work;
    cc += nowQuestion.answers[a].college;
    uu += nowQuestion.answers[a].university;
    if (ww > 0 || cc > 0 || uu > 0){
        perWork = (float)ww / (float)(ww + cc + uu);
        perCollege = (float)cc / (float)(ww + cc + uu);
        perUniversity = (float)uu / (float)(ww + cc + uu);
    }
    if (nowQuestion.answers[a].tags.size() > 0){
       tag = nowQuestion.answers[a].tags;
       tt += tag;
       for (int j = 0; j < limitations.size(); j++){
           for (int k = 0; k < tag.size(); k++){
               for (int q = 0; q < limitations[j].tags.size(); q++){
                   if (limitations[j].tags[q] == tag[k]){
                       allLimitation.push_back(limitations[j]);
                   }
               }
           }
       }
    }
    if (i >= mmin){
        if ((float)ww / (float)(ww + cc + uu) > plan1){
            winner = 'w';
            //qDebug () << "w";
        }
        else if ((float)cc / (float)(ww + cc + uu) > plan1){
            winner = 'c';
            //qDebug () << "c";
        }
        else if ((float)uu / (float)(ww + cc + uu) > plan1){
            winner = 'u';
            //qDebug () << "u";
        }
        return winner;
    }
    if (pp == true && a == 0){
        if (nowQuestion.answers[a].work != 0){
            winner = 'w';
        }
        else if (nowQuestion.answers[a].college != 0){
            winner = 'c';
        }
        else {
             winner = 'u';
        }
        return winner;
    }
    if (ee){
        return 'e';
    }
    return 'n';
}



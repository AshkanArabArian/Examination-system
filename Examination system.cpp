#include <iostream>
#include <vector>
#include <ctime>
#include <stdio.h>
#include <string>
#include <set>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "json.hpp"
 
using json = nlohmann::json;

int qqq = 10000; // bara code yekta azmoon ta tedad argham taiin shan
using namespace std;

bool showAllExamsCode();
string idToName(string );

bool wordislogout(string word){
    if (word == "logout"){
        return true;
    }
    return false;
}

class Question {
public:
    bool operator==(const Question* rhs) const {
        return this->number == rhs->number;
    }
    bool answered; // vasat azmoon be soal javab dade shode ya na, difult hame false and;
    void pushNumber(int inputnumber){
        number = inputnumber;
        return;
    }
    void pushText(string inputtext){
        text = inputtext;
    }
    string getText(){
        return text;
    }
    int getNumber(){ 
        return number; 
    }
    virtual void desplayInfoquestion(int ){}
    virtual string getNoe(){return "1";}
    virtual string getAnswer(){return "1";} // bara kotah va boland
    virtual float getAnswer4(){return 1.0;}
    virtual float getManfi(){return 1.0;}
    virtual int pushManfi(float ){return 1;}
    virtual float getMosbat(){return 1.0;}
    virtual int pushMosbat(float ){return 1;}
    virtual void setAns(){}
    virtual float getChoises(int ){return 1;}
    virtual void pushChoise(int, float){}
    virtual void pushAns(string){}
private:
    int number; // shomare qu to exam hastan
    string text;
};

Question notfoundq; // just an object for when, we are not found Qu

class q4 : public Question {
public :
    int pushMosbat(float inputnumber) override{
        if(inputnumber < 0){
            return 0;
        }
        mosbat = inputnumber;
        return 1;
    }
    float getMosbat() override { 
        return mosbat; 
    }
    int pushManfi(float inputnumber) override{
        if(inputnumber < 0){
            return 0;
        }
        manfi = inputnumber;
        return 1;
    }
    float getManfi() override { 
        return manfi; 
    }
    float getChoises(int index) override {
        return choises[index];
    }
    void pushChoise(int i, float inputc) override {
        choises[i] = inputc;
    }
    void desplayInfoquestion(int r) override {
        cout << "#Question[" << getNumber() << "] (4 choises Q): ";
        cout << getText();
        if(r != 1) {
            cout << "?";
        }        
        cout << " | nomre manfi: ";
        cout << getManfi() << " " ;
        cout << " | nomre mosbat: ";
        cout << getMosbat() << " " << endl << endl;
        showChoise(r);
    }
    void showChoise(int r){
        int tartib[4] = {5, 5, 5, 5};
        randomSaz(tartib);
        for(int i = 0; i < 4; i++){
            char ch = 'A' + i;
            cout << ch << '.' << choises[tartib[i]];
            if ((r == 1) && (tartib[i] == 0)){
                cout << "(correct)";
            }
            cout << "     ";
        }
        cout << endl << endl;
    }
    void randomSaz(int tartib[]){
        for (int i = 0; i < 4; i++){
            bool tmp = true;
            int w = rand() % 4;
            for(int j = 0; j < 4; j++){
                if (tartib[j] == w){
                    tmp = false;
                }
            }
            if(tmp){
                tartib[i] = w;
            }
            else {
                i--;
            }
        }
    }
    bool areSame(float c[]){
        bool same = false;
        for (int i = 0; i < 4; i++){
            for (int j = i + 1; j < 4; j++){
                if (c[i] == c[j]){
                    cout << "choise " << i + 1 << " and " << j + 1 << " are the same" << endl;
                    same = true;
                }
            }
        }
        return same;
    }
    void setAns() override {
        float c[4];
        while(true){
            bool same = false;
            cout << "please write 4 choises (first choise is the correct answer)\n";
            for (int i = 0; i < 4; i++){
                char ch = 'A' + i;
                cout << ch << '.';
                cin >> c[i];
            }
            if(!areSame(c)){
                break;
            }
        }
        for (int i = 0; i < 4; i++){
            pushChoise(i, c[i]);
        }
    }
    string getNoe() override{
        return "4";
    }
    string getAnswer() override {
        return to_string(choises[0]);
    }
private :
    float choises[4]; // choises[0] is write answer
    float manfi;
    float mosbat;
};


class qk : public Question {
public :
    int pushMosbat(float inputnumber) override{
        if(inputnumber < 0){
            return 0;
        }
        mosbat = inputnumber;
        return 1;
    }
    float getMosbat() override { 
        return mosbat; 
    }
    int pushManfi(float inputnumber) override{
        if(inputnumber < 0){
            return 0;
        }
        manfi = inputnumber;
        return 1;
    }
    float getManfi() override { 
        return manfi; 
    }
    void desplayInfoquestion(int r) override{
        cout << "#Question[" << getNumber() << "] (kotah pasokh Q): ";
        cout << getText();
        if(r != 1) {
            cout << "?";
        } 
        cout << " | nomre manfi: ";
        cout << getManfi() << " " ;
        cout << " | nomre mosbat: ";
        cout << getMosbat() << " " << endl;
        if (r == 1){
            cout <<"$answer: " << answer << endl << endl;
        }
    }
    void pushAns(string inputans) override {
        answer = inputans;
    }
    void setAns() override {
        string text;
        while (true){
            cout << "please write answer of Q: ";
            getline(cin >> ws, text);
            if (text.find(' ') != string::npos){
                cout << "sorry the answer of kotah pasokh must be a num or word,\n";
                continue;
            }
            break;
        }
        pushAns(text);
    }
    string getNoe() override{
        return "k";
    }
    string getAnswer() override {
        return answer;
    }
    float getAnswer4() override {// hichvaght farakhani nemishe bara teste
        return 0;
    }
private :
    string answer;
    float manfi;
    float mosbat;
};


class qb : public Question {
public:
    int pushMosbat(float inputnumber) override{
        if(inputnumber < 0){
            return 0;
        }
        mosbat = inputnumber;
        return 1;
    }
    float getMosbat() override { 
        return mosbat; 
    }
    void desplayInfoquestion(int r) override{
        cout << "#Question[" << getNumber() << "] (boland pasokh Q): ";
        cout << getText();
        cout << " | nomre mosbat: ";
        cout << getMosbat();
        if (r == 1){
            cout << endl << "$answer: " << answer;
        }
        else {
            cout << "?";
        }
    }
    void pushAns(string inputans){
        answer = inputans;
    }
    void setAns(){
        cout << "please write answer of Q: (if you wand end send an empty line)\n";
        string text, line;
        cin >> ws;
        while(getline(cin, line)){
            if(line.empty()){
                break;
            }
            text += line + '\n';
        }
        pushAns(text);
    }
    string getNoe() override{
        return "b";
    }
    string getAnswer() override {
        return answer;
    }
private :
    string answer;
    float mosbat;
};


class soaljavab {
private :
    friend class barge;
    Question *q;
    string studentAnswer;
    bool tassihShode;
    float nomre = 0;

    soaljavab(string a, Question* qu){
        q = qu;
        studentAnswer = a;
        tassihShode = false;
    }
    soaljavab(float n, float a, Question* qu){
        q = qu;
        studentAnswer = to_string(a);
        nomre = n;
        tassihShode = true;
    }
    soaljavab(float n, string a, Question* qu){
        q = qu;
        studentAnswer = a;
        nomre = n;
        tassihShode = true;
    }
    Question* getQ(){
        return q;
    }
    void pushNomre(float n){
        n = nomre;
    }
    float getMosbat(){
        return q->getMosbat();
    }
    string getStudentAnswer(){
        return studentAnswer;
    }
    float getNomre(){
        return nomre;
    }
    bool getTassihShode(){
        return tassihShode;
    }
    void showSoalJavab(){
        q->desplayInfoquestion(1);
        cout << "$student answer ---> " << studentAnswer << endl;
        cout << "&student score---> " << nomre << endl;
    }    
};


class barge {
private :
    friend class Exam;
    friend class Sherkat;
    friend class loadFromFiles;
    friend class saveToFiles;
    string studentId;
    vector <soaljavab*> sp;
    float nomre;
    int tedad;

    void pushTedad(int t){
        tedad = t;
    }
    void showSoalJavabs(){
        for(soaljavab *ss : sp){
            ss->showSoalJavab();
        }
    }
    float getNomre(){
        return nomre;
    }
    void pushStudentId(string id){
        studentId = id;
    }
    string getStudentId(){
        return studentId;
    }
    void pushN(float inputnomre){
        nomre = inputnomre;
    }
    void addQA(Question* q, string a){
        soaljavab* s = new soaljavab(a, q);
        sp.push_back(s);
    }
    void addQA(Question* q, string a, float nomre){
        soaljavab* s = new soaljavab(nomre, a, q);
        sp.push_back(s);
    }
    void addQA(Question* q, float a, float nomre){
        soaljavab* s = new soaljavab(nomre, a, q);
        sp.push_back(s);
    }
    bool getBarge(string** qs, int number){
        if(sp.size() <= 0){
            return false;
        }
        for(int i = 0; i < number; i++){
            qs[i][0] = sp[i]->getQ()->getText();
            qs[i][1] = sp[i]->getStudentAnswer();
            qs[i][2] = sp[i]->getQ()->getAnswer();
            qs[i][3] = to_string(sp[i]->getNomre());
        }
        return true;
    }
    float tassihBarge(){
        float newNomre = nomre;
        cout << "soalat boland, pasokh dade shode: \n";
        for(soaljavab* ss : sp){
            if(!ss->getTassihShode()){
                ss->showSoalJavab();
                if(wantTassih()){
                    float addedNomre;
                    while(true){
                        cout << "please enter the nomre of this Q:(can be negative)";
                        cin >> addedNomre;
                        if(addedNomre > ss->getMosbat()){
                            cout << "the max weight of Qu is: " << ss->getMosbat() << endl;
                            continue;
                        }
                        ss->pushNomre(addedNomre);
                        break;
                    }
                    newNomre = editNomre(nomre, addedNomre);
                }
            }
        }
        cout << "-----soalat tashrihi tamam shodand!-----\n";
        pushN(newNomre);
        return newNomre;
    }
    float editNomre(float nomre, float addedNomre){
        float newNomre = nomre + addedNomre;
        tedad++;
        return newNomre;
    }
    bool wantTassih(){
        cout << "you want tassih this Q?(yes/else)";
        string ss;
        getline(cin >> ws, ss);
        if((ss == "yes" || (ss == "y"))){
            return true;
        }
        else {
            return false;
        }
    }
};

struct nomid{
    string id;
    float nomre;
    bool operator>(const nomid& dovomi) const {
        return nomre < dovomi.nomre;
    }
    bool operator<(const nomid& dovomi) const {
        return nomre > dovomi.nomre;
    }
    bool operator>=(const nomid& dovomi) const {
        return nomre <= dovomi.nomre;
    }
    bool operator<=(const nomid& dovomi) const {
        return nomre >= dovomi.nomre;
    }
    bool operator==(const nomid& dovomi) const {
        return nomre == dovomi.nomre;
    }
    bool operator!=(const nomid& dovomi) const {
        return nomre != dovomi.nomre;
    }
};

class Exam {
private :
    string name;
    int code;
    vector <Question*> Questions;
    vector <barge*> bargha;
    multiset <nomid> nomarat;
    float timemin;
    int number;
    float allWeight = 0;
    float tassihWeight = 0;

    friend class loadFromFiles;
    friend class saveToFiles;
    int Nobnumber;// shayad naaaaaaaaaaaaaaa
public :
    void addAweight(float w){
        allWeight += w;
    }
    void addTweight(float w){
        tassihWeight += w;
    }
    float getTweight(){
        return tassihWeight;
    }
    float getAweight(){
        return allWeight;
    }
    int getCode(){
        return code;
    }
    int getNumber(){
        return number;
    }
    float getTimemin(){
        return timemin;
    }
    string getName(){ 
        return name;
    }
    float getNomre(int index){
        auto iterator = nomarat.begin();
        advance(iterator, index);
        return iterator->nomre;
    }
    float getNomreS(string id){
        int i = 0;
        for (nomid ss : nomarat){
            if(ss.id == id){
                return getNomre(i);
            }
            i++;
        }
        return 0;
    }
    double getAvg(){
        double sum = 0;
        for(int i = 0; i < nomarat.size(); i++){
            sum += getNomre(i);
        }
        return sum / nomarat.size();
    }
    int getTedadSherkatha(){
        return nomarat.size();
    }
    int getGrade(float nomre){
        for(int i = 0; i < nomarat.size(); i++){
            if(getNomre(i) == nomre){
                return i + 1;
            }
        }
        return -1;
    }
    void addNomre(string id, float nomre){
        for (auto it = nomarat.begin(); it != nomarat.end(); ++it){
            if(it->id == id){
                nomarat.erase(it);
                break;
            }
        }
        nomid *n = new nomid;
        n->id = id;
        n->nomre = nomre;
        nomarat.insert(*n);
    }
    void pushCode(int inputcode){
        code = inputcode;
        return;
    }
    void pushNumber(int inputnumber){
        number = inputnumber;
        return;
    }
    void pushName(string inputname){
        name = inputname;
    }
    bool pushTimemin(float inputTimemin){
        if(inputTimemin <= 0){
            return false;
        }
        timemin = inputTimemin;
        return true;
    }
    int getNobNumber(){
        return Nobnumber;
    }
    void pushNobNumber(int inputnumber){
        Nobnumber = inputnumber;
    }
    void addBarge(barge* barge){
        bargha.push_back(barge);
    }
    void addQuestion(Question* question) {
        Questions.push_back(question);
    }
    bool removeQuestion(int chandomin){ // shomare midi ta pak kone
        bool i = false;
        auto it = find_if(Questions.begin(), Questions.end(), [chandomin](Question* q){
            return q->getNumber() == chandomin;
        });
        Questions.erase(it);
        for (Question* qq : Questions){
            if(qq->getNumber() > chandomin){
                qq->pushNumber(qq->getNumber() - 1); // jlotaria jasho migiran
                i = true;
            }
        }
        return i;
    }
    void desplayInfoexam(int i){ /// neshon dadan azmon ha 
        cout << "################# # # ################\n";
        cout << "Exams name: " << getName() << "| with time(min): " << getTimemin() << "| and unique code: " << getCode() <<";\n";
        if (i == 1){ /// teacher ha mitonan soalaroham bbinan vali studenta na 
            cout << "the exams Questions:\n\n";
            for (Question* qq : Questions){
                if (qq->getNumber() != 0){
                    qq->desplayInfoquestion(1);// polimorfism dare & 1 yanei ye teacher dare mibine
                }
            }
        }
        cout << "################# # END OF EXAM # ################" << endl << endl;
    }
    Question* getQu(int inputnumber){ // shomare soal midi qu mide
        for (Question* qq : Questions){
            if(qq->getNumber() == inputnumber){
                return qq;
            }
        }
        return &notfoundq;
    }
    void changeAnsweredQu(Question* q){
        for (Question* qq : Questions){
            if(qq->getNumber() == q->getNumber()){
                if(!qq->answered){
                    qq->answered = true;
                }
                else {
                    qq->answered = false;
                }
            }
        }
    }
    int showCurrentQ(int inputnumber, barge* barge){ /// vaghti dare exam mide soal feli ro neshon dade v jvab migire
        while(1){
            Question* q = getQu(inputnumber);
            q->desplayInfoquestion(2);
            cout << "\n(if you want answer Qu send 'a' and if you want go to next Qu send 'n' and if you want go back Qu send 'p') ";
            string dastor;
            getline(cin >> ws, dastor);
            if (dastor == "n"){
                return 1;
            }
            if(dastor == "p"){
                return -1;
            }
            else if(dastor == "a"){
                if (q->answered){
                    cout << "you answered this Qu before\n";
                    continue;
                }
                return answeringQ(q, barge);
            }
            else if(dastor == "end"){
                break;
            }
            else {
                cout << "sorry i dont undrestand, ";
                continue;
            }
        }
        return -10;
    }
    int answeringQ(Question* q, barge* b){
        changeAnsweredQu(q);
        if(q->getNoe() == "4"){
            return answering4Q(q, b);
        }
        else if(q->getNoe() == "k"){
            return answeringkQ(q, b);
        }
        else if(q->getNoe() == "b"){
            return answeringbQ(q, b);
        }
        return 0;
    }
    int answering4Q(Question* q, barge* barge){
        float answer;
        cout << "write your answer amount: ";
        cin >> answer;
        if (q->getAnswer4() == answer){
            barge->addQA(q, answer, q->getMosbat());
            return 10;
        }
        else {
            barge->addQA(q, answer, -1*q->getManfi());
            return 0;
        }
    }
    int answeringkQ(Question* q, barge* barge){
        string answer;
        cout << "please write your answer: ";
        getline(cin >> ws, answer);
        cout << answer;
        if (q->getAnswer() == answer){
            barge->addQA(q, answer, q->getMosbat());
            return 10;
        }
        else {
            barge->addQA(q, answer, -1*q->getManfi());
            return 0;
        }
    }
    int answeringbQ(Question* q, barge* barge){
        string answer, line;
        cout << "please write your answer(enter empty line to end):\n";
        cin >> ws;
        while(getline(cin, line)){
            if(line.empty()){
                break;
            }
            answer += line + '\n';
        }
        barge->addQA(q, answer);
        return 5;
    }
    string generateKarnameFile(string id){
        const string fileName = "KARNAME-" + id + "-" + to_string(getCode()) + ".csv";
        ofstream file(fileName);
        file << "Student name: " << idToName(id) << ",";
        file << "Student id: " << id << ",";
        file << "Exams name: " << getName() << ",";
        file << "Student score(from 20): " << 20 * getNomreS(id) / getAweight() << "\n";
        file << "#" << "," << "#" << "," << "#" << "," << "#\n";
        file << "Questions text" << "," << "Student answer";
        file << "," << "Original answer" << "," << "Scored" << "\n";

        string** questions = new string*[number];
        for(int i = 0; i < number; i++){
            questions[i] = new string[4];
        }
        for(barge *bb : bargha){
            if(bb->getStudentId() == id){
                bb->getBarge(questions, number);
            }
        }
        for (int i = 0; i < number; i++){
            char c;
            for(char &c : questions[i][1]){
                if (c == '\n')
                    c = ' ';
            }
            for(char &c : questions[i][2]){
                if (c == '\n')
                    c = ' ';
            }   
            file << "#" << i + 1 << "." << questions[i][0] << "," << questions[i][1];
            file << "," << "$" << questions[i][2] << "," << questions[i][3] << "\n";
        }
        file << "#" << "," << "#" << "," << "#" << "," << "#";
        file << "\n" << "Avrage of Nomarat: "<< getAvg();
        file << "," << "Maximum of Nomarat: " << getNomre(0);
        file << "," << "Student ranking: " << getGrade(getNomreS(id));
        file << "," << "Total participants: " << nomarat.size();
        for (int i = 0; i < number; i++){
            delete [] questions[i];
        }
        delete [] questions;
        file.close();
        return fileName;
    }
    bool showBarge(string id){
        bool i = false;
        for(barge *bb : bargha){
            i = true;
            if(bb->getStudentId() == id){
                cout << "Student : " << id << endl;
                cout << "Exam : " << getName() << endl;
                cout << "your nomre : " << bb->getNomre() << " from : " << getAweight();
                cout << " (from 20 ---> " << 20 * bb->getNomre() / getAweight() << ") " << endl;
                bb->showSoalJavabs();
                return i;
            }
        }
        return i;
    }
    float getNomre(string id){
        for(barge *bb : bargha){
            if(bb->getStudentId() == id){
                return bb->getNomre();
            }
        }
        return 0;
    }
    string generateNomaratFile(){
        int rank = 0;
        float prev = -100000;
        const string fileName = "NATAYEJ-" + to_string(getCode()) + ".csv";
        ofstream file(fileName);
        file << "ranks" << "," << "student name" << "," << "student id" << "," <<  "student nomre(from 20)" << "\n";
        for (auto iterator = nomarat.begin(); iterator != nomarat.end(); ++iterator){
            if(iterator->nomre != prev){
                prev = iterator->nomre; 
            }
            else {
                rank--;
            }
            auto tmp1 = rank + 1;
            auto tmp2 = idToName(iterator->id);
            auto tmp3 = iterator->id;
            auto tmp4 = 20 * iterator->nomre / getAweight();
            file << tmp1 << "," << tmp2 << "," << tmp3 << "," << tmp4 << "\n";
        }
        file << "maximum of nomarat ->" << "," << nomarat.begin()->nomre;
        file << "," << "average of nomarat ->" << "," << getAvg();
        file.close();
        return fileName;
    }
    bool showNomarat(){
        bool i = false;
        int rank = 0;
        float prev = -100000;
        for (auto iterator = nomarat.begin(); iterator != nomarat.end(); ++iterator){
            i = true;
            if(iterator->nomre != prev){
                prev = iterator->nomre; 
            }
            else {
                rank--;
            }
            auto tmp1 = rank + 1;
            auto tmp2 = idToName(iterator->id);
            auto tmp3 = iterator->id;
            auto tmp4 = 20 * iterator->nomre / getAweight();
            cout << tmp1 << "." << tmp2;
            cout << " | with id : " << tmp3 << " | NOMRE :" << tmp4 << endl;
            rank++;
        }
        if(rank == 0){
            cout << "# sorry hich studenti sherkat nakarde! #\n";
        }
        else {
            cout << "," << "averege of nomarat ->" << "," << getAvg();
        }
        return i;
    }
    bool sherkatShode(string id){
        for(barge *bb : bargha){
            if(bb->getStudentId() == id){
                return true;
            }
        }
        return false;
    }
    bool tassihBarge(string id){
        for(barge *bb : bargha){
            if(bb->getStudentId() == id){
                float newNomre = bb->tassihBarge();
                cout << "&&the new nomre of student is : " << newNomre  << " from " << getAweight() << endl;
                addNomre(id, newNomre);
                return true;
            }
        }
        return false;
    }
    void getMax(){
        cout << "maximum of nomarat: " << 20.0 * getNomre(0) / getAweight() << endl; // chonke mulltyset nozoli hastesh
    }
};

Exam* getExam(int);
Exam notfounde;

class Sherkat {
public :
    Sherkat(Exam* exam, string id){
        barge *b = new barge;
        b->pushTedad(exam->getNobNumber());
        b->pushStudentId(id);
        float nomre = 0;
        int current = 1;
        int startTime = time(nullptr);
        float timeSec = exam->getTimemin()*60;
        while(true){
            int a = exam->showCurrentQ(current, b);
            if (time(nullptr) - startTime >= timeSec){
                endSherkat(exam, nomre, true, b);
                break;
            }
            if (a == 1){
                if (current != exam->getNumber()){
                    current++;
                }
                else {
                    cout << "you are in last Qu\n";
                    continue; 
                }
            }
            else if (a == -1){
                if (current > 1){
                    current--;
                }
                else{
                    cout << "you are in first Qu";
                    continue;
                }
            }
            else if (a == 0){
                /// eshtebahhhhhhh
                nomre -= exam->getQu(current)->getManfi();
                if(current != exam->getNumber()){
                    current++;
                }
            }
            else if (a == 10){
                /// doooorost
                nomre += exam->getQu(current)->getMosbat();
                if(current != exam->getNumber()){
                    current++;
                }
            }
            else if(a == 5){
                // pasokh be boland pasokh
                current++;
            }
            else if (a == -10){
                endSherkat(exam, nomre, false, b);
                break;
            }
        }
    }    
    void endSherkat(Exam* exam, float nomre, bool time, barge* barge){
        if(time){
            cout << "the azmons time is ended.";
        }
        cout << " your Grade(including all Qu) == ";
        printf("%.2f from %.2f\n", nomre, exam->getAweight());

        cout << " your Grade(including all 4/k Qu) == ";
        printf("%.2f from %.2f\n", nomre, exam->getTweight());

        for (int i = 0; i < exam->getNumber(); i++){
            if(exam->getQu(i)->answered){
                exam->changeAnsweredQu(exam->getQu(i));  /// age dobare khast azmoon bede
            }
            else if(exam->getQu(i)->getNoe() == "4"){
                barge->addQA(exam->getQu(i), 6464646.646464, 0);
            }
            else {
                barge->addQA(exam->getQu(i), "! NotAnswered !", 0);
            }
        }
        barge->pushN(nomre);
        exam->addBarge(barge);
        exam->addNomre(barge->getStudentId(), nomre);
        return;
    }
};


class User {
protected :
    string name;
    string password;
    string id;
    int code; // if 1 user teachere if 2 user
public :
    User(string name, string password, string id) : name(name), password(password), id(id) { } // bejai estefade az this->

    friend class loadFromFiles;
    friend class saveToFiles;
    int getCode(){
        return code;
    }
    bool login(string inputId, string inputPassword) {
        return (id == inputId && password == inputPassword);
    }
    string getId(){ 
        return id; 
    }
    string getName() { 
        return name; 
    }
    virtual Exam* findExam(int) = 0;
    virtual bool showExamsCode(){return true;}
    virtual bool removequ(int, int){return true;}
    virtual bool showExams(){return true;}
    virtual bool showKarname(int ){return true;}
    virtual void addqu(int, int){}
    virtual void displayInfo(){}
    virtual int addExam(){return 1;}
};


class Teacher : public User {
private:
    vector <string> coursesTaught; // bara chand dars
    vector <Exam> Exams;
public:
    Teacher(string name, string password, string id) : User(name, password, id) {code = 1;}

    friend class loadFromFiles;
    friend class saveToFiles;
    void addCourse(string course) {
        coursesTaught.push_back(course);
    }
    int addExam() override {
        Exam e;
        srand(time(0));
        e.pushNumber(0);
        e.pushNobNumber(0);
        string name;
        cout << "please write the exams name: ";
        getline(cin >> ws, name);
        if (wordislogout(name)){ 
            return 0;
        }
        e.pushName(name);
        while(true){
            float timemin;
            cout << "please write the exams time (minutes). congratulations!! you can send a float: ";
            cin >> timemin;
            while(!e.pushTimemin(timemin)){
                cout << "oh, time is incorrect, ";
                cin >> ws;
                float m;
                cin >> m;
                timemin = m;
            }
            break;
        }
        while(true){
            A :
            int code = rand() % qqq;
            for (Exam aa : Exams){
                if(aa.getCode() == code){
                    goto A;
                }
            }
            e.pushCode(code);
            break;
        }
        cout << "create and add an exam with name : "<< name << " | and code : " << e.getCode() << " | was successfully!\n";
        Exams.push_back(e);
        return e.getCode();
    }
    void addqu4(int code, int chandomin){
        string text;
        for (Exam &aa : Exams){
            if(aa.getCode() == code){
                Question* q = new q4;
                q->pushNumber(chandomin);
                q->answered = false;
                cout << "please write the question["<< chandomin <<"] text\n";
                cin.ignore();
                getline(cin >> ws, text);
                q->pushText(text);
                q->setAns();
                while(true){
                    float manfi;
                    cout << "please write the nomre MANFI(can be a float) of Q: ";
                    cin >> manfi;
                    while(!q->pushManfi(manfi)){
                        cout << "adad manfi ghabol nist!\n";
                        cin >> manfi;
                    }
                    break;
                }
                while(true){
                    float mosbat;
                    cout << "please write the nomre MOSBAT(can be a float) of Q: ";
                    cin >> mosbat;
                    while(!q->pushMosbat(mosbat)){
                        cout << "adad manfi ghabol nist!\n";
                        cin >> mosbat;
                    }
                    aa.addAweight(mosbat);
                    aa.addTweight(mosbat);
                    break;
                }
                aa.addQuestion(q);
                aa.pushNumber(aa.getNumber() + 1);
                aa.pushNobNumber(aa.getNobNumber() + 1);
                break;
            }
        }
    }
    void addquK(int code, int chandomin){
        string text;
        for (Exam &aa : Exams){
            if(aa.getCode() == code){
                Question* q = new qk;
                q->pushNumber(chandomin);
                q->answered = false;
                cout << "please write the question["<< chandomin <<"] text\n";
                cin.ignore();
                getline(cin >> ws, text);
                q->pushText(text);
                q->setAns();
                while(true){
                    float manfi;
                    cout << "please write the nomre MANFI(can be a float) of Q: ";
                    cin >> manfi;
                    if(!q->pushManfi(manfi)){
                        cout << "adad manfi ghabol nist!\n";
                        continue;
                    }
                    break;
                }
                while(true){
                    float mosbat;
                    cout << "please write the nomre MOSBAT(can be a float) of Q: ";
                    cin >> mosbat;
                    while(!q->pushMosbat(mosbat)){
                        cout << "adad manfi ghabol nist!\n";
                        cin >> mosbat;
                    }
                    aa.addAweight(mosbat);
                    aa.addTweight(mosbat);
                    break;
                }
                aa.addQuestion(q);
                aa.pushNumber(aa.getNumber() + 1);
                aa.pushNobNumber(aa.getNobNumber() + 1);
                break;
            }
        }
    }
    void addquB(int code, int chandomin){
        string text;
        for (Exam &aa : Exams){
            if(aa.getCode() == code){
                Question* q = new qb;
                q->pushNumber(chandomin);
                q->answered = false;
                cout << "please write the question["<< chandomin <<"] text\n";
                cin.ignore();
                getline(cin >> ws, text);
                q->pushText(text);
                while(true){
                    float mosbat;
                    cout << "please write the nomre MOSBAT(can be a float) of Q: ";
                    cin >> mosbat;
                    while(!q->pushMosbat(mosbat)){
                        cout << "adad manfi ghabol nist!\n";
                        float nmosbat;
                        cin >> nmosbat;
                        mosbat = nmosbat;
                    }
                    aa.addAweight(mosbat);
                    break;
                }
                q->setAns();
                aa.addQuestion(q);
                aa.pushNumber(aa.getNumber() + 1);
                break;
            }
        }
    }
    void addqu(int code, int chandomin) override { // add qu be azmoni ke codsho besh dadim
        while(true){
            cout << "*if you want add a 4 choises question write 4,\n";
            cout << "*and if you want add kotah pasokh write k,\n";
            cout << "*and for  boland write b,\n";
            cout << "*and if you wnat back write back: ";
            string noe;
            getline(cin >> ws, noe);
            if (noe == "4"){
                addqu4(code, chandomin);
            }
            else if(noe == "k"){
                addquK(code, chandomin);
            }
            else if(noe == "b"){
                addquB(code, chandomin);
            }
            else if (noe == "back"){
                return;
            }
            else {
                cout << "sorry i dont undrestand,\n";
                continue;
            }
            cout << "#question[" << chandomin << "] Added seccessfully\n";
            break;
        }
    }
    bool showExams() override { // show azmoon be sabk teacher
        cout << "please enter that exams code you want to show: ";
        int code;
        cin >> code;
        Exam* aa = findExam(code);
        if (aa->getCode() == 0){
            return false;
        }
        aa->desplayInfoexam(1); // 1 yanei ostad mikhad bebine
        return true;
    }
    Exam* findExam (int inputcode) override { // code midi exam mide age codi bedi k nabashe ye exam mide k codesh 0 hast, 0!
        for (Exam &aa : Exams){
            if(aa.getCode() == inputcode){
                return &aa;
            }
        }
        return &notfounde;
    }
    bool showExamsCode() override { //// hame exam haaa
        bool i = false;
        for (Exam aa : Exams){
            cout << aa.getCode() << endl;
            i = true;
        }
        return i;
    }
    bool removequ(int code, int chandomin){ // shomare qu v code azmon migire pak mikone
        int i = 0;
        int j = 0;
        for (Exam &aa : Exams){
            if(aa.getCode() == code){
                if(aa.removeQuestion(chandomin)){
                    aa.pushNumber(aa.getNumber() - 1);
                    j = 1;
                }
                i = 1;
            }
        }
        if ((i == 1) && (j == 1)){
            return true;
        }
        return false;
    }
    void displayInfo() override {
        cout << "Teacher: " << name << " | ID: " << id;
        int i = 1;
        cout << " | Courses : ";
        for (const auto& course : coursesTaught){
            cout << course << "["<< i <<"] ";
            i++;
        }
        cout << endl;
    }
    bool showKarname(int code) override {
        bool i = false;
        Exam* e = getExam(code);
        if(e->getCode() == 0){
            cout << "exam was not found!\n";
            return i;
        }
        for (Exam aa : Exams){
            if(aa.getCode() == code){
                if(aa.showNomarat()){
                    showMA(aa);
                    cout << "\n###all of this informations writed in ";
                    cout << aa.generateNomaratFile() << "###" << endl;
                }
                return true;
            }
        }
        cout << "you didn't create this exam!\n";
        return i;
    }
    void showMA(Exam e){
        cout << "\t--------------------\n";
        e.getMax();
        cout << "avrege of nomarat: " << 20.0 * e.getAvg() / e.getAweight() <<  endl;
    }
};
    

class Student : public User {
private:
    string fieldOfStudy;
    vector <Exam> Exams;
public:
    Student(string name, string password, string id, string fieldOfStudy) : User(name, password, id), fieldOfStudy(fieldOfStudy) {code = 2;}
    friend class loadFromFiles;
    friend class saveToFiles;

    void displayInfo() override {
       cout << "Student: " << name << " | ID: " << id << " | Field of Study: " << fieldOfStudy << endl;
    }
    string getFieldOfStudy() { 
        return fieldOfStudy;
    }
    int addExam() override {
       if(!showAllExamsCode()){
            return -2;
        }
        cout << "please enter the code of exam that you want it: ";
        int code;
        cin >> code;
        for (Exam a : Exams){
            if(a.getCode() == code){
                return -1;
            }
        }
        Exam* e = getExam(code);
        if (e->getCode() != 0){
            Exams.push_back(*e);
        }
        return e->getCode();
    }
    bool showExams() override {
        bool i = false;
        for (Exam &aa : Exams){
            aa.desplayInfoexam(2);
            i = true;;
        }
        return i;
    }
    Exam* findExam (int inputcode) override {// in tabe hichvaght farakhany nemishe, shayad badan nyaz she!
        return &notfounde;
    }
    bool showKarname(int code) override {
        Exam* e = new Exam;
        e = getExam(code);
        if(e->getCode() == 0){
            cout << "exam was not found!\n";
            return false;
        }
        if(!e->showBarge(getId())){
            cout << "dar in exam sherkat nakardi!\n";
            return false;
        }
        showMAR(e);
        cout << "\n###_all of this informations writed in ";
        cout << e->generateKarnameFile(getId()) << "_###" << endl;
        return true;
    }
    void showMAR(Exam* e){
        cout << "\t--------------------\n";
        e->getMax();
        cout << "avrege of nomarat: " << 20.0 * e->getAvg() / e->getAweight() <<  endl;
        cout << "your rotbe in students is: " << e->getGrade(e->getNomre(getId())) <<" of "<< e->getTedadSherkatha() << endl;
    }
};

void loginedTeacher(User& teacher){
    while(1){
        cout << "What can i do for you?\n";
        cout << "*if you want create an exam enter create,\n";
        cout << "*aid if you want see your exams enter see,\n";
        cout << "*and if you want tassih a karname enter tassih,\n";
        cout << "*and if you want see an natayej of an exam enter karname: ";
        string dast;
        getline(cin >> ws, dast);
        if (wordislogout(dast)) { break;}
        if (dast == "create"){
            int code = teacher.addExam();
            int i = 0;
            if (code != 0) {
                while(true){
                    cout << "if you want add question write Add and if you want remove";
                    cout << " a question write Remove: (write end to end exam editting) ";
                    string dastor;

                    getline(cin >> ws, dastor);
                    if (wordislogout(dastor)) { 
                        return;
                    }
                    i++;
                    if (dastor == "Add"){
                        teacher.addqu(code, i);
                    }
                    else if (dastor == "Remove"){
                        int f;
                        cout << "please write the number of question that you want remove that: ";
                        cin >> f;
                        if(teacher.removequ(code, f)){
                            cout << "remuve question was seccessfully!\n";
                            i--;
                            i--;
                        }
                        else {
                            cout << "remove question was failed (the exams code or question number is incorrect!\n";
                        }
                        continue;
                    }
                    else if (dastor == "end"){
                        i--;
                        getExam(code)->pushNumber(i);
                        break;
                    }
                    else {
                        cout << "sorry i dont undrestand, ";
                        i--;
                        continue;
                    }
                }
            }
            else {
                break;
            }
        }
        else if (dast == "see"){
            if(!teacher.showExamsCode()){
                cout << "sorry your exams list is empty!\n";
                continue;
            }
            if(!teacher.showExams()){
                cout << "this exam not exists!\n";
            }
        }
        else if((dast == "karname") || (dast == "k")){
            cout << "please enter the code of exam that you want see that karname haa: ";
            int code;
            cin >> code;
            teacher.showKarname(code);
            cout << "\t--------------------\n";
        }
        else if((dast == "tassih") || (dast == "t")){
            while(true){
                cout << "please enter the code of exam that you want TASSiH that(if you want back enter 0): ";
                int code;
                cin >> code;
                if(code == 0){
                    break;
                }
                Exam *e = getExam(code);
                if(e->getNobNumber() == e->getNumber()){
                    cout << "this exam tashrihi boland pasokh nadare!\n";
                    continue;
                }
                if(teacher.showKarname(code)){
                    cout << "please enter the students id that you want tassih that!: ";
                    string d;
                    getline(cin >> ws, d);
                    if(!e->tassihBarge(d)){
                        cout << "the student with id, " << d << " did not participate in this exam!\n";
                    }
                }
                else {
                    cout << "# nobody sherkat in this exam! #\n";
                    break; 
                }
            }
        }
        else {
            cout << "sorry i dont undrestand, ";
            continue;
        }
    }
}
void loginedStudent (User& student){
    while(1){
        cout << "What can i do for you?\n";
        cout << "*if you want add an exam enter add,\n";
        cout <<  "*and if you want see your exams enter see,\n";
        cout << "*and if you want sherkat in exam enter sherkat,\n";
        cout << "*and if you want your karnames enter karname: ";
        string dast;
        getline(cin >> ws, dast);
        if (wordislogout(dast)) {
            break;
        }
        if ((dast == "add") || (dast == "a")){
            A :
            int code = student.addExam();
            if ((code == 0) || (code == -1)){
                while(true){
                    if(code == 0){
                        cout << "this exam not exist!";
                    }   
                    else if(code == -1){
                        cout << "you already have this exam!\n";
                    }
                    cout << " do you want choose another one?(yes/no): ";
                    string dastor;
                    getline(cin >> ws, dastor);
                    if (dastor == "yes"){
                        goto A;
                    }
                    else if (dastor == "no"){
                        break;
                    }
                    else {
                        cout << "sorry i dont undrestand,";
                        continue;
                    }
                }
            }
            else if(code == -2){
                cout << "sorry, but there is no exams(boro bekhab exami nist)\n";
            }
            else {
                cout << "the exam with code: " << code << " added seccessfully\n"; 
            }
        }
        else if (dast == "see"){
            if(!student.showExams()){
                cout << "sorry your exams list is empty!\n"; 
            }
        }
        else if (dast == "sherkat"){
            if(!student.showExams()){
                cout << "sorry your exams list is empty!\n"; 
            }
            else {
                cout << "\ndo you want sherkat to kodam azmoon?(please write that code): ";
                int code;
                cin >> code;
                string id = student.getId();
                Exam* e = getExam(code);
                bool i = true;
                if(e->sherkatShode(id)){
                    i = false;
                    while(true){
                        cout << "dar in Azmoon sherkat kardi! mikhay karnamato to bebini?(yes/no) ";
                        string d;
                        getline(cin >> ws, d);
                        if(wordislogout(d)){
                            return;
                        }
                        if(d == "yes"){    
                            student.showKarname(code);
                            break;
                        }
                        else if(d == "no"){ 
                            break;
                        }
                        else {
                            cout << "sorry i dont undrestand;\n";
                            continue;
                        }
                    }
                }
                if(i){
                    Sherkat(e, id);
                }
            }
        }
        else if((dast == "karname") || (dast == "k")){
            cout << "please enter the code of exam that you want see that karname: ";
            int code;
            cin >> code;
            Exam *e = getExam(code);
            student.showKarname(code);
        }
        else {
            cout << "sorry i dont undrestand, ";
            continue;
        }
    }
}


class UserManager {
public :
    ~UserManager() {
        for (User* user : users) {
            delete user;
        }
    }
private :
    vector <User*> users; // baray negah dashtan hame

    friend class Signup_Login;
    friend class loadFromFiles;
    friend class saveToFiles;
    friend Exam* getExam(int );
    friend bool showAllExamsCode();
    friend string idToName(string);

    bool isIdUnique(string id) {
        for (User* user : users) {
            if (user->getId() == id) {
                return false;
            }
        }
        return true;
    }
    bool idIsNum(string id){
        for (char c : id){
            if ((c < '0') || (c > '9')){
                cout << "id must be a number. please choose another one: ";
                return false;
            }
        }
        return true;
    }
    string registerStudent(string name, string password, string id, string fieldOfStudy) {
        if (!isIdUnique(id)) {
            cout << "Error: This ID is already taken. Please choose and write another one: ";
            getline(cin >> ws, id);
            return registerStudent(name, password, id, fieldOfStudy);
        }
        Student* studentS = new Student(name, password, id, fieldOfStudy);
        users.push_back(studentS);
        cout << "Student " << name << " registered successfully!\n";
        return id;
    }
    string registerTeacher(string name, string password, string id, vector <string> courses) {
        if (!isIdUnique(id)) {
            cout << "Error: This ID is already taken. Please choose another one: ";
            getline(cin >> ws, id);
            return registerTeacher(name, password, id, courses);
        }
        Teacher* teacherT = new Teacher(name, password, id);
        for (const auto& course : courses){
            teacherT -> addCourse(course);
        }
        users.push_back(teacherT);
        cout << "Teacher " << name << " registered successfully!\n";
        return id;
    }
    bool loginUser(string id, string password) {
        for (User* user : users) {
            if (user->login(id, password)) {
                cout << "Login successful! Welcome, " << user->getName() << ".\n";
                user->displayInfo();

                if(user->getCode() == 1){
                    loginedTeacher(*user);
                }
                if(user->getCode() == 2){
                    loginedStudent(*user);
                }
                return true;
            }
        }
        cout << "Login failed! Incorrect ID or password.\n";
        return false;
    }
};

UserManager userManager; /////// har bar ejra yedone azina darim ke gharare koool user haro negah dare

string idToName(string id){
    for (User* user : userManager.users) {
        if(user->getId() == id){
            return user->getName();
        }
    }
    return "ashakn";
}

Exam* getExam(int inputcode){ /// code mide exam migiri
    for (User* user : userManager.users) {
        if(user->getCode() == 1){
            Exam *e =  new Exam;
            e = user->findExam(inputcode);
            if(e->getCode()){
                return e;
            }
        } 
    }
    return &notfounde;
}

bool showAllExamsCode(){ // hame exam teacher haaa
    int i = 0;
    for (User* user : userManager.users) {
        if (user->getCode() == 1) {
            user->showExamsCode();
            i = 1;
        }
    }
    if (!i) { 
        return false;
    }
    return true;
}

class Signup_Login {
public :
    void sup(){
        while(true){
            cout << "are you a teacher or student?(if you want back, write back ...) ";
            string tmp;
            getline(cin >> ws, tmp);
            if ((tmp == "teacher") || (tmp == "t")){
                supT();
            }
            else if ((tmp == "student") ||  (tmp == "s")){
                supS();
            }
            else if (tmp == "back"){
                break;
            }
            else {
                cout << "sorry i dont undrestand please say again, ";
                continue;
            }
            break;
        }
    }
    void supT(){
        string name, pass, id;
        vector <string> courses;
        string course;
        cout << "please write your name: "; 
        getline(cin >> ws, name); 
        if (wordislogout(name)) { return;}
        cout <<"\nplease write your password: ";
        getline(cin >> ws, pass);
        if (wordislogout(pass)) { return;}
        cout <<"\nplease write personal ID: ";
        int k = 1;
        while(true){
            getline(cin >> ws, id);
            if (wordislogout(id)) { k = 0; break;}
            if(!userManager.idIsNum(id)){
                continue;
            }
            break;
        }
        if(k == 0){
            return;
        }
        int i = 1;
        string areyou = "yes";
        while(1){
            if (i != 1){
                cout << "do you want add another course? (yes / no): ";
                getline(cin >> ws, areyou);
                if (wordislogout(areyou)) {break;}
            }
            i++;
            if (areyou == "yes"){
                cout << "\nplease write your corse[number "<< i-1 <<"]: ";
                getline(cin >> ws, course);
                if (wordislogout(course)) { break;}
                courses.push_back(course);
            }
            else if(areyou == "no"){
                break;
            }
            else {
                cout << "sorry i dont undrstand, ";
                i--;
            }
        }
        string lastid = userManager.registerTeacher(name, pass, id, courses);
        userManager.loginUser(lastid, pass);
    }
    void supS(){
        string name, pass, FieldOfStudy, id;
        cout << "please write your name: "; 
        getline(cin >> ws, name);
        if (wordislogout(name)) { return;}
        cout <<"\nplease write your password: ";
        getline(cin >> ws, pass);
        if (wordislogout(pass)) { return;}
        cout <<"\nplease write field of study: ";
        getline(cin >> ws, FieldOfStudy);
        if (wordislogout(FieldOfStudy)) { return;}
        cout <<"\nplease write personal ID: ";
        int k = 1;
        while(true){
            getline(cin >> ws, id);
            if (wordislogout(id)) { k = 0; break;}
            if(!userManager.idIsNum(id)){
                continue;
            }
            break;
        }
        if(k == 0){
            return;
        }
        string lastid = userManager.registerStudent(name, pass, id, FieldOfStudy);
        userManager.loginUser(lastid, pass);
    }
    void logi(){
        while(true){
            string id, pass;
            cout <<"\nplease write personal ID: ";
            getline(cin >> ws, id);
            if (wordislogout(id))
                break;
            cout <<"\nplease write your password: ";
            getline(cin >> ws, pass);
            if (wordislogout(pass))
                break;
            if(!userManager.loginUser(id, pass))
                continue;
            break;
        }
    }
};


class loadFromFiles{
private :
    friend int main();

    void loadUsersFromFile(const string& filePath) {
        ifstream file(filePath);
        if (!file.is_open()) {
            cerr << "Error: Could not open users.json file.\n";
            file.close();
            return;
        }
        json usersJson;
        file >> usersJson;
        if (usersJson.empty()) {
            cerr << "Error: users.json is empty.\n";
            file.close();
            return;
        }
        for (const auto& user : usersJson) {
            string type = user["type"];
            string name = user["name"];
            string password = user["password"];
            string id = user["id"];
            if (type == "teacher") {
                vector<string> courses = user["courses"];
                userManager.registerTeacher(name, password, id, courses);
            } 
            else if (type == "student") {
                string fieldOfStudy = user["fieldOfStudy"];
                userManager.registerStudent(name, password, id, fieldOfStudy);
            }
        }
        file.close();
    }
    void loadExamsFromFile(const string& filePath) {
        ifstream file(filePath);
        if (!file.is_open()) {
            cerr << "Error: Could not open exams.json file.\n";
            file.close();
            return;
        }
        json examsJson;
        file >> examsJson;
        if (examsJson.empty()) {
            cerr << "Error: exams.json is empty.\n";
            file.close();
            return;
        }
        for (const auto& examData : examsJson) {
            Exam e;
            e.pushName(examData["name"]);
            e.pushCode(examData["code"]);
            e.pushTimemin(examData["time"]);

            for (const auto& question : examData["questions"]) {
                Question* q;
                if (question["type"] == "4") {
                    q = new q4;
                    q->pushText(question["text"]);
                    q->pushNumber(question["number"]);
                    q->pushChoise(0, question["choices"][0]);
                    q->pushChoise(1, question["choices"][1]);
                    q->pushChoise(2, question["choices"][2]);
                    q->pushChoise(3, question["choices"][3]);
                    q->pushMosbat(question["mosbat"]);
                    q->pushManfi(question["manfi"]);
                }
                else if (question["type"] == "k") {
                    q = new qk;
                    q->pushText(question["text"]);
                    q->pushNumber(question["number"]);
                    q->pushAns(question["answer"]);
                    q->pushMosbat(question["mosbat"]);
                    q->pushManfi(question["manfi"]);
                }
                else if (question["type"] == "b") {
                    q = new qb;
                    q->pushText(question["text"]);
                    q->pushNumber(question["number"]);
                    q->pushAns(question["answer"]);
                    q->pushMosbat(question["mosbat"]);
                }
                e.addQuestion(q);
            }
            for (const auto& bargeData : examData["barges"]) {
                barge* b = new barge;
                b->pushStudentId(bargeData["studentId"]);
                b->pushN(bargeData["score"]);
                for (const auto& answerData : bargeData["answers"]) {
                    string questionText = answerData["question"];
                    string studentAnswer = answerData["studentAnswer"];
                    string correctAnswer = answerData["correctAnswer"];
                    float score = answerData["score"];

                    for (Question* q : e.Questions) {
                        if (q->getText() == questionText) {
                            if(q->getNoe() == "b"){
                                if(score == 0)
                                    b->addQA(q, studentAnswer);
                                else 
                                    b->addQA(q, studentAnswer, score);
                                break;
                            }
                            b->addQA(q, studentAnswer, score);
                            break;
                        }
                    }
                }
                e.addBarge(b);
            }
            for (const auto& nomid : examData["nomarat"]){
                e.addNomre(nomid["id"], nomid["nomre"]);
            }
            e.addAweight(examData["allWeight"]);
            e.addTweight(examData["4/k Weight"]);
            e.pushNumber(examData["number"]);
            string teacherId = examData["teacherId"];

            for (User* user : userManager.users) {
                if ((user->getCode() == 1) && (user->getId() == teacherId)) { // teachere
                    Teacher* teacher = dynamic_cast<Teacher*>(user);
                    if (teacher) {
                        teacher->Exams.push_back(e); 
                    }
                }
            }
            for (const auto& studentId : examData["studentsId"]) {
                for (User* user : userManager.users) {
                    if ((user->getCode() == 2) && (user->getId() == studentId)) { // studente
                        Student* student = dynamic_cast<Student*>(user);
                        if (student) {
                            student->Exams.push_back(e);
                        }
                    }
                }
            }
        }
        file.close();
    }
};


class saveToFiles {
private :
    friend int main();
    void saveUsersToFile(const string& filePath) {
        json usersJson;
        for (User* user : userManager.users) {
            json userJson;
            userJson["name"] = user->getName();
            userJson["password"] = user->password;
            userJson["id"] = user->getId();

            if (user->getCode() == 1) { // Teacher
                userJson["type"] = "teacher";
                Teacher* teacher = dynamic_cast<Teacher*>(user);
                if (teacher) {
                    userJson["courses"] = teacher->coursesTaught;
                }
            } else if (user->getCode() == 2) { // Student
                userJson["type"] = "student";
                Student* student = dynamic_cast<Student*>(user);
                if (student) {
                    userJson["fieldOfStudy"] = student->getFieldOfStudy();
                }
            }
            usersJson.push_back(userJson);
        }
        ofstream file(filePath);
        if (!file.is_open()) {
            cerr << "Error: Could not open users.json file for writing.\n";
            return;
        }
        file << usersJson.dump(4);
        file.close();
    }
    void saveExamsToFile(const string& filePath) {
        json examsJson;
        for (User* user : userManager.users) {
            if (user->getCode() == 1) {
                Teacher* teacher = dynamic_cast<Teacher*>(user);
                if (teacher) {
                    for (Exam& exam : teacher->Exams) {
                        json examJson;
                        examJson["name"] = exam.getName();
                        examJson["code"] = exam.getCode();
                        examJson["time"] = exam.getTimemin();
                        examJson["number"] = exam.getNumber();
                        examJson["allWeight"] = exam.getAweight();
                        examJson["4/k Weight"] = exam.getTweight();
                        examJson["teacherId"] = teacher->getId();
                        examJson["studentsId"];
                        for (User* user : userManager.users) {
                            if(user->getCode() == 2){
                                Student* student = dynamic_cast<Student*>(user);
                                for (Exam ee : student->Exams){
                                    if(ee.getCode() == exam.getCode()){
                                        examJson["studentsId"].push_back(student->getId());
                                    }
                                }
                            }
                        }
                        json questionsJson;
                        for (Question* q : exam.Questions) {
                            json questionJson;
                            questionJson["type"] = q->getNoe();
                            questionJson["text"] = q->getText();
                            questionJson["number"] = q->getNumber();

                            if (q->getNoe() == "4") {
                                questionJson["choices"] = {q->getChoises(0), q->getChoises(1), q->getChoises(2), q->getChoises(3)};
                                questionJson["mosbat"] = q->getMosbat();
                                questionJson["manfi"] = q->getManfi();
                            }
                            else if (q->getNoe() == "k") {
                                questionJson["answer"] = q->getAnswer();
                                questionJson["mosbat"] = q->getMosbat();
                                questionJson["manfi"] = q->getManfi();
                            } 
                            else if (q->getNoe() == "b") {
                                questionJson["answer"] = q->getAnswer();
                                questionJson["mosbat"] = q->getMosbat();
                            }
                            questionsJson.push_back(questionJson);
                        }
                        examJson["questions"] = questionsJson;

                        json bargesJson;
                        for (barge* b : exam.bargha) {
                            json bargeJson;
                            bargeJson["studentId"] = b->getStudentId();
                            bargeJson["score"] = b->getNomre();

                            json answersJson;
                            json answerJson;
                            string** questions = new string*[exam.getNumber()];
                            for (int j = 0; j < exam.getNumber(); j++) {
                                questions[j] = new string[4];
                            }
                            if(b->getBarge(questions, exam.getNumber())){
                                for(int i = 0; i < exam.getNumber(); i++){
                                    answerJson["question"] = questions[i][0];
                                    answerJson["studentAnswer"] = questions[i][1];
                                    answerJson["correctAnswer"] = questions[i][2];
                                    answerJson["score"] = stof(questions[i][3]);
                                    answersJson.push_back(answerJson);
                                }
                                for (int j = 0; j < exam.getNumber(); j++) {
                                    delete[] questions[j];
                                }
                                delete[] questions;
                                
                                bargeJson["answers"] = answersJson;
                                bargesJson.push_back(bargeJson);
                            }
                        }
                        examJson["barges"] = bargesJson;

                        json nomarat;
                        for (nomid nn : exam.nomarat){
                            json nomid;
                            nomid["nomre"] = nn.nomre;
                            nomid["id"] = nn.id;
                            nomarat.push_back(nomid);
                        }
                        examJson["nomarat"] = nomarat;
                        examsJson.push_back(examJson);
                    }
                }
            }
        }
        ofstream file(filePath);
        if (!file.is_open()) {
            cerr << "Error: Could not open exams.json file for writing.\n";
            return;
        }
        file << examsJson.dump(4);
        file.close();
    }
};


int main() {
    notfoundq.pushNumber(-1);
    notfounde.pushCode(0);
    loadFromFiles lff;
    saveToFiles stf;
    Signup_Login sl;

    lff.loadUsersFromFile("users.json");
    lff.loadExamsFromFile("exams.json");
    while (1) {
        string dastor;
        cout << "you are in first page what can i do for you?(sup/logi/END): ";
        getline(cin >> ws, dastor);
        if ((dastor,"signup")) {
            sl.sup();
        } 
        else if (dastor == "login") {
            sl.logi();
        } 
        else if (dastor == "END") {
            break;
        } 
        else {
            cout << "sorry i dont undrestand, ";
            continue;
        }
    }
    stf.saveUsersToFile("users.json");
    stf.saveExamsToFile("exams.json");
    return 0;
}
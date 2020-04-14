#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

void MainMenu(string username) // Display Main Menu;
{
    cout << "Welcome " << username <<", please choose from the following options: \n\n";
    cout << "[1] Go to administration menu \n"
         << "[2] Update your name \n"
         << "[3] Start a new quiz \n"
         << "[4] Display your scores statistics \n"
         << "[5] Display all your scores\n"
         << "[6] Exit \n"
         << "\nChoice: ";
}
void AdminMenu()// Display Administration Menu;
{
    cout << "Welcome to the administration menu, please choose from the following options: \n\n";
    cout << "[1] View all questions \n"
         << "[2] Add new question \n"
         << "[3] Load questions from file \n"
         << "[4] Go back to main menu \n"
         << "\nChoice: ";
}

struct body // Creating Question Body Struct;
{
    string question_text;
    string choices[4];
}   temp_question; // declaring a structure variable

// Global Declarations

vector <body> aquestion; // A Vector of Structs;
vector<double>scores;
vector<double>right_answer_per_quiz;
static double quiz_counter;
static double score_summation;

void add_new_question()
{
    string star=" ";
    string s_choice;
    cout << "Consider the following format" << endl;
    cout << "\nQuestion: \n";
    cout << "\nChoice1: \n" << "Choice2: \n" << "Choice3: \n" << "Choice4: " << endl;
    cout << "\nNote that: The first choice should be the answer of the question!\n" << endl;
     system("pause");
     system("cls");
    cout << "Enter your question: ";
    cin.get();
    getline(cin,temp_question.question_text);
    //  system("cls");
    for(int i=0; i<4; i++)
    {
        cin.get();
        getline(cin,s_choice);
        if(i==0)
        {
            s_choice+=star;
        }
        temp_question.choices[i]=s_choice;
    }
    aquestion.push_back(temp_question);
    system("cls");
}

void delete_question()
{
    char d;
    unsigned int n;
    cout << "Consider the following format to delete a question ::" << ">> d #" << "\nas d stands for delete and # stands for nth question" << endl << endl;
    system("pause");
    cout << "Delete: ";
    cin >> d >> n;
    if(n>aquestion.size())
    {
        cout << "The question doesn't exit!\n";
        system("pause");
    }
    else
    {
        aquestion.erase(aquestion.begin()+ n - 1); // remove a specific question at specific position.
    }
}

void print_all_questions()
{
    if(aquestion.size()==0)
    {
        cout << "There is no questions to view!\n";
        system("pause");
        system("cls");
    }
    else
    {
        cout << "Number of questions: " << aquestion.size() << endl << endl;
        for(unsigned int i=0; i<aquestion.size(); i++)
        {
            int ascii=65;
            cout <<'[' << i+1 << ']' << " " << aquestion[i].question_text << endl;
            for(unsigned int j=0; j<4; j++)
            {
                char&p=aquestion[i].choices[j].at(aquestion[i].choices[j].length()-1);

                cout <<'[' << char(ascii++) <<']' << " ";
                if(p==' '){
                    cout << aquestion[i].choices[j] << "";
                }
                else
                   cout << aquestion[i].choices[j] << " ";
            }
            cout << endl << endl;
        }
        string answer;
        cout << "Do you want to delete a question? (answer with yes or no)\n";
        cin.get();
        getline(cin,answer);
        if(answer=="yes")
        {
            system("cls");
            delete_question();
        }
        system("cls");
    }
}

void randomize_choices()
{
    srand(time(0));
    for(unsigned int i=0; i<aquestion.size(); i++)
    {
        for(unsigned int j=0; j<4; j++)
        {
            int random_index2=rand()%4;
            swap(aquestion[i].choices[j],aquestion[i].choices[random_index2]);
        }
    }
}

void randomize_questions()
{
    srand(time(0));
    for(unsigned int i=0; i<aquestion.size(); i++)
    {
        int random_index1=rand()%aquestion.size();
        swap(aquestion[i],aquestion[random_index1]);
    }
}

void load_from_file()
{
    string filename;
    string star=" ";
    int pointer=0;
    cin.get();
    cout << "Add .txt at the end of your filename.\n";
    cout << "Filename: ";
    getline(cin,filename);
    system("cls");
    ifstream myfile;
    myfile.open(filename);
    if(!myfile.is_open())
    {
        cout << "file isn't open properly, check filename again." << endl;
    }
    else
    {
    string line;
    while(getline(myfile,line))
        {
        pointer++;
        switch(pointer)
            {
            case 1: aquestion.push_back(body());
                    aquestion[aquestion.size()-1].question_text=line;
                    break;
            case 2:
                    aquestion[aquestion.size()-1].choices[0]=line;
                    aquestion[aquestion.size()-1].choices[0]+=star;
                    break;
            case 3:
                    aquestion[aquestion.size()-1].choices[1]=line;
                    break;
            case 4:
                    aquestion[aquestion.size()-1].choices[2]=line;
                    break;
            case 5:
                    aquestion[aquestion.size()-1].choices[3]=line;
                    pointer-=5;
                    break;
            }
        }
    }
myfile.close();
cout << "File is read!\n\n";
system("pause");
system("cls");
}

void internal_switch() // Administration Menu Switch
{
    while(true)
    {
        int admin_menu_choice;
        AdminMenu();
        cin >> admin_menu_choice;
        system("cls");
        switch(admin_menu_choice)
        {

        case 1:
                print_all_questions();
                break;
        case 2:
                add_new_question();
                break;
        case 3:
                load_from_file();
                break;
        case 4:
                break;
        default:
                cout << "Not an option! \n";
                system("pause");
                system("cls");
                break;

        }
        if(admin_menu_choice==4)
        {
            system("cls");
            break;
        }
    }
}

void start_quiz()
{
    int right_answers=0,total_score=0;
    if(aquestion.size()>=5)
    {
        randomize_questions();
        randomize_choices();
        for(unsigned int i=0; i<5; i++)
        {
            int ascii=65;
            cout <<'[' << i+1 << ']' << " " << aquestion[i].question_text << endl;
            for(unsigned int j=0; j<4; j++)
            {
                char&p=aquestion[i].choices[j].at(aquestion[i].choices[j].length()-1);

                cout <<'[' << char(ascii++) <<']' << " ";
                if(p==' '){
                    cout << aquestion[i].choices[j] << "";
                }
                else
                   cout << aquestion[i].choices[j] << " ";
            }
            cout << endl;
            char answer;
            cout << "\nChoice: ";
            cin >> answer;
            switch(answer)
            {
            case 'a':
            case 'A':
                {


                //  cout << names[0].var[0].at(names[0].var[0].length()-1);
                    char&a=aquestion[i].choices[0].at(aquestion[i].choices[0].length()-1);
                    if(a==' ')
                    {
                    total_score+=5;
                    right_answers+=1;
                    }
                    break;
                }
            case 'b':
            case 'B':
                {
                    char&b=aquestion[i].choices[1].at(aquestion[i].choices[1].length()-1);
                    if(b==' ')
                    {
                    total_score+=5;
                    right_answers+=1;
                    }
                    break;
                }
            case 'c':
            case 'C':
                {
                    char&c=aquestion[i].choices[2].at(aquestion[i].choices[2].length()-1);
                    if(c==' ')
                    {
                    total_score+=5;
                    right_answers+=1;
                    }
                    break;
                }
            case 'd':
            case 'D':
                {
                    char&d=aquestion[i].choices[3].at(aquestion[i].choices[3].length()-1);
                    if(d==' ')
                    {
                    total_score+=5;
                    right_answers+=1;
                    }
                    break;
                }
            }
            cout << endl << endl;
        }
            score_summation+=total_score;
            scores.push_back(total_score);
            right_answer_per_quiz.push_back(right_answers);
            quiz_counter++;
            cout << "You have done  " << quiz_counter << " quiz(s)" << endl;
            cout << "Total Score:   " << total_score << endl;
            cout << "Right Answers: " << right_answers << "\nWrong Answers " << 5-right_answers << endl;
            system("pause");
            system("cls");
    }
    else
    {
        cout << "Quiz should contain 5 questions. There is ";
        if(aquestion.size()==0)
        {
            cout << "no questions\n\n";
            cout << "Please load from file or add questions. \n\n";
            system("pause");
            system("cls");
        }
        else
        {
            cout << "already " << aquestion.size() << "question/s in the pool.\n\n";
            cout << "Add questions to the pool!\n";
            system("pause");
            system("cls");
        }
    }
}

void statistics_history()
{
    if(quiz_counter!=0)
    {
                cout << "Quiz History\n\n";
                cout << "You have done " << quiz_counter << " quiz(s)\n\n";
                for(int i=0;i<quiz_counter;i++)
                {
                    cout << "Quiz " << (i+1)  << " statistics: \n\n";
                    cout << "Total Score  : " << scores[i] << endl;
                    cout << "Right Answers: " << right_answer_per_quiz[i]   << endl;
                    cout << "Wrong Answers: " << 5-right_answer_per_quiz[i] << endl;

                    if(i==quiz_counter-1)
                    {
                        cout << "\n";
                    }
                    else
                        cout << "\n------------------------\n";
                }
    }
    else
        cout << "Do a quiz first!\n";
                system("pause");
                system("cls");
}

void score_statistics()
{
                if(quiz_counter!=0)
                {
                sort(scores.begin(), scores.end());
                cout << "Your Statistics is: \n\n";
                cout << "\tYou have done   " << quiz_counter << " quiz(s)\n\n";
                cout << "\tHighest score : " << scores[scores.size()-1] << endl;
                cout << "\tLowest  score : " << scores[0]               << endl;
                cout << "\tAverage score : " << (score_summation)/5     << endl;
                }
                else{
                    cout << "Do a quiz first!\n\n";
                }
            system("pause");
            system("cls");
}

int main()
{
    string username="USER";
    while(true)
    {
        int main_menu_choice=0;
        MainMenu(username);
        cin >> main_menu_choice;
        system("cls");
        switch(main_menu_choice)
            {
        case 1:
                internal_switch();
                break;
        case 2:
                cout << "Set user name to: ";
                cin >> username;
                system("cls");
                break;
        case 3:
                start_quiz();
                break;
        case 4: score_statistics();
                break;
        case 5:
                statistics_history();
                break;
        case 6:
                return 0; // exit the program;
        default:
                cout << "Not an option! \n";
                system("pause");
                system("cls");
                break;
            }
    }
    return 0;
}

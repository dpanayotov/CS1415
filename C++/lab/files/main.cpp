#include <iostream>
#include <fstream>

using namespace std;


struct StudentData
{

    int fn;
    char name[100];
};

struct SubjectData
{
  int code;
  char name[100];
  char teacher[100];

};

struct GradeData
{
  int studentFn, subjectCode;
  int d,m,y;
  double value;

};

void createStudents ()
{
    ifstream inpStud ("students.txt");
    ofstream outpStud ("students.bin",ios::binary);

    StudentData student;


    while (inpStud >> student.fn)
    {
        inpStud.getline (student.name,100);
        cout << "Read stundet:" << student.name << endl;

        outpStud.seekp ((student.fn-1000)*sizeof(StudentData));
        outpStud.write ((char*)&student,sizeof(StudentData));

    }

    outpStud.seekp(0,ios::end);
    cout << "Number of all records =" << outpStud.tellp()/sizeof(StudentData) << endl;




}

void createSubjects ()
{

    ifstream inpSubj ("subjects.txt");
    ofstream outpSubj ("subjects.bin",ios::binary);

    SubjectData subj;


    while (inpSubj >> subj.code)
    {
        inpSubj.getline (subj.name,100);
        inpSubj.getline (subj.teacher,100);
        cout << "Read subject:" << subj.name << endl;

        outpSubj.seekp (subj.code*sizeof(SubjectData));
        outpSubj.write ((char*)&subj,sizeof(SubjectData));

    }


}

void createGrades ()
{
    ifstream inp ("grades.txt");
    ofstream outp ("grades.bin",ios::binary);

    GradeData gr;


    while (inp >> gr.studentFn)
    {
        inp >> gr.subjectCode >> gr.d >> gr.m >> gr.y >> gr.value;
        cout << "Read grade of:" << gr.studentFn << endl;

        outp.write ((char*)&gr,sizeof(GradeData));

    }



}

int main()
{

    createStudents();
    createSubjects();
    createGrades();

    cout << "Hello world!" << endl;
    return 0;
}

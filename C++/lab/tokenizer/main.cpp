#include <iostream>
#include <fstream>
#include <string>


using namespace std;

class Tokenizer
{
  private:


    istream &in;
    ifstream tokensList;
    string currentToken;


  public:
        Tokenizer (istream& _in, char *fname):in(_in)
        {
            tokensList.open (fname);
        }

        bool getNextToken ()
        {

            return in >> currentToken;
        }

        int tokenId ()
        {
            //currentToken? tokensList

            tokensList.clear();
            tokensList.seekg(0);

            string tmp;
            int count = 0;
            while (tokensList >> tmp)
            {

                if (tmp == currentToken)
                    return count;

                count++;

            }

            return -1;
        }

        string tokenString ()
        {
            return currentToken;

        }

        bool duplicates ()
        {
            //определя дали във файла
            //с токините има повторения
            return false;
        }

        void ingnoreDuplicates (bool ingrone = true)
        {
            //при активиране на режима
            //ingnoreDuplicates индексирането на
            //токените зачита само първото срещане
            //на дублираните токени. Например в следния списък
            //aa
            //bb
            //cc
            //bb
            //dd
            //Смятаме, че токенът bb има индекс 1,
            //а dd има индекс 3

        }

};

int main()
{


    Tokenizer t (cin, "tokens.txt");

    while (t.getNextToken())
    {

        cout << t.tokenString ()
             << "("
             << t.tokenId()
             << ")";
    }


}

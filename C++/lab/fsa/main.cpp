#include <iostream>
#include <assert.h>
#include <vector>

using namespace std;

/*
dot.exe -Tpdf test1.dot -o test1.pdf
*/

template <class T>
void ensureIndex (vector<T>& v, int index, const T& initEl)
{
  for (int i = v.size(); i <= index; i++)
  {
    v.push_back (initEl);
  }
}


struct trans
{
  int start, end;
  char symbol;

};

class NFSA
{
  private:
    vector<vector<vector<int> > > transitions;
    //transition[start][symbol][#]
    int startState;
    vector<bool> finalStates;
  public:

  NFSA ()
  {
    startState = 0;
  }

  void setStartState (int state)
  {
    startState = state;
  }

  void setFinalState (int state, bool final=true)
  {
    ensureIndex (finalStates, state, false);
    finalStates[state] = final;
  }


  bool recognize (char *w, int currentState)
  {
    if (w[0] == 0)
      return finalStates[currentState];


    //ЕПСИЛОН ПРЕХОДИ И ЕПСИСЛОН ЦИКЛИ!!!
    const vector<int>& neigh
      = transitions[currentState][w[0]-'a'];

    for (int i = 0; i < neigh.size(); i++)
    {
      if (recognize(w+1,neigh[i]))
        return true;
    }

    return false;
  }

  NFSA& addTrans (int fromState, int toState, char symbol)
  {

    assert (symbol >= 'a' && symbol <= 'z'+1);

    vector<vector<int> >emptyRow;
    ensureIndex(emptyRow,'z'-'a'+1,vector<int> ());

    ensureIndex (transitions,fromState,emptyRow);
    assert (transitions.size() > fromState);
    assert (transitions[fromState].size() > 'z'-'a'+1);

    transitions[fromState][symbol-'a'].push_back (toState);

    return *this;

  }

  friend ostream& operator << (ostream&, const NFSA& a);

  void shiftStates (int minIndex)
  //Осигурява, че най-малкият индекс на състояние на
  //автомата в minIndxex
  {

  }

  bool finiteLangiage()
  //проверява дали езикът на автомата е краен
  {

  }

  void printAllWords ()
  //печата всички думи от езика на автомата,
  //ако езикът е краен
  {

  }


};

ostream& operator << (ostream &out, const NFSA& a)
{
  out << "digraph{" << endl;

  int fromState, count;

  char symbol;

  for (fromState = 0; fromState < a.transitions.size(); fromState++)
  {
    for (symbol = 0; symbol < 'z'-'a'+1;symbol++)
    {
      const vector<int>& toStates = a.transitions[fromState][symbol];
      for (count = 0; count < toStates.size(); count++)
      {
        //fromState -(symbol)->toStates[i]
        out << fromState << "->" << toStates[count] << "[label=\"" << (char)(symbol+'a')<<"\"];" << endl;
      }
    }
  }


  for (count = 0; count < a.finalStates.size(); count++)
  {
    if (a.finalStates[count])
      out << count << "[style=filled];" << endl;
  }

  out << a.startState << "[shape=box];" << endl;

  out << "}";

  return out;
}


int main()
{

    NFSA a;


    a.addTrans(100,200,'a');

    a.addTrans (0,1,'a').addTrans(0,1,'b').
      addTrans (1,2,'c').addTrans(2,30,'x').
      addTrans (1,4,'u').addTrans(4,30,'z').
      addTrans (4,30,'a').addTrans(4,2,'a');



    a.setFinalState (30);
    a.setFinalState (4);

    cout << a;

    cout << endl << "?=" << a.recognize ("bua",0) << endl;

    //cout << "Hello world!" << endl;
    return 0;
}

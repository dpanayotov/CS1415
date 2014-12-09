#include <iostream>
#include <assert.h>
#include <vector>

using namespace std;

/*
dot.exe -Tpdf test1.dot -o test1.pdf
*/

template <class T>
void ensureIndex (vector<T> &v, int index, const T &initEl)
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
    vector<int> visited;
public:

    NFSA ()
    {
        startState = 0;
    }

    void setStartState(int state)
    {
        startState = state;
    }

    void setFinalState(int state, bool final = true)
    {
        ensureIndex (finalStates, state, false);
        finalStates[state] = final;
    }


    bool recognize(char *w, int currentState)
    {
        if (w[0] == 0)
            return finalStates[currentState];


        //ЕПСИЛОН ПРЕХОДИ И ЕПСИСЛОН ЦИКЛИ!!!
        const vector<int> &neigh
            = transitions[currentState][w[0] - 'a'];

        for (int i = 0; i < neigh.size(); i++)
        {
            if (recognize(w + 1, neigh.at(i)))
                return true;
        }

        return false;
    }

    NFSA &addTrans(int fromState, int toState, char symbol)
    {

        assert (symbol >= 'a' && symbol <= 'z' + 1);

        vector<vector<int> >emptyRow;
        ensureIndex(emptyRow, 'z' - 'a' + 1, vector<int> ());
        ensureIndex(transitions, toState, emptyRow);
        ensureIndex (transitions, fromState, emptyRow);
        assert (transitions.size() > fromState);
        assert (transitions[fromState].size() > 'z' - 'a' + 1);

        transitions[fromState][symbol - 'a'].push_back (toState);

        return *this;

    }

    friend ostream &operator << (ostream &, const NFSA &a);

    void shiftStates(int minIndex)
    //Осигурява, че най-малкият индекс на състояние на
    //автомата в minIndxex
    {
        NFSA temp;
        for (int fromState = 0; fromState < transitions.size(); fromState++)
        {
            for (int symbol = 0; symbol < 'z' - 'a' + 1; symbol++)
            {
                const vector<int> &toStates = transitions[fromState][symbol];
                for (int count = 0; count < toStates.size(); count++)
                {
                    temp.addTrans(fromState + minIndex, toStates.at(count) + minIndex, (char)(symbol + 'a'));
                }
            }
        }

        temp.setStartState(startState + minIndex);

        for (int i = 0; i < finalStates.size(); i++)
        {
            temp.setFinalState(finalStates[i] + minIndex);
        }

        *this = temp;

    }


    bool finiteLanguage()
    //проверява дали езикът на автомата е краен
    {
        vector<int> visited;
        return !hasLoop(visited, startState);
    }

    bool hasTransition(int from, int to)
    {
        vector<vector<int> >emptyRow;
        ensureIndex(emptyRow, 'z' - 'a' + 1, vector<int> ());
        ensureIndex(transitions, from, emptyRow);
        for (int symbol = 0; symbol < 'z' - 'a' + 1; symbol++)
        {
            const vector<int> &toStates = transitions[from][symbol];
            for (int toState = 0; toState < toStates.size(); toState++)
            {
                if (toStates[toState] == to)
                {
                    return true;
                }
            }
        }

        return false;
    }


    bool hasLoop(vector<int>& visited, int currentState)
    {
        for(int i = 0; i < visited.size(); i++)
        {
            if(currentState == visited[i])
            {
                return true;
            }
        }

        visited.push_back(currentState);
        for (int symbol = 0; symbol < 'z'-'a'+1; symbol++)
        {
            const vector<int>& toStates = transitions[currentState][symbol];
            for (int count = 0; count < toStates.size(); count++)
            {
                if(hasLoop(visited, toStates[count]))
                {
                    return true;
                }
                visited.pop_back();
            }
        }

        return false;
    }

    void printAllWords ()
    {
        if(finiteLanguage())
        {
            string word;
            words(word, 0);
        }
    }

    void words(string word, int currentState)
    {

        if (finalStates[currentState])
        {
            cout << word << endl;
        }

        for (int symbol = 0; symbol < 'z'-'a'+1; symbol++)
        {
            const vector<int>& toStates = transitions[currentState][symbol];
            const char letter = (char)(symbol + 'a');
            word += letter;

            for (int toState = 0; toState < toStates.size(); toState++)
            {
                words(word, toStates[toState]);

            } word.resize(word.size() - 1);
        }
    }

    bool isFinalState(int state)
    {
        return finalStates[state];
    }


};

ostream &operator << (ostream &out, const NFSA &a)
{
    out << "digraph{" << endl;

    int fromState, count;

    char symbol;

    for (fromState = 0; fromState < a.transitions.size(); fromState++)
    {
        for (symbol = 0; symbol < 'z' - 'a' + 1; symbol++)
        {
            const vector<int> &toStates = a.transitions[fromState][symbol];
            for (count = 0; count < toStates.size(); count++)
            {
                //fromState -(symbol)->toStates[i]
                out << fromState << "->" << toStates.at(count) << "[label=\"" << (char)(symbol + 'a') << "\"];" << endl;
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

    //loops
   //a.addTrans(2, 0, 'a');
    //a.addTrans(2,0, 'x');//.addTrans(1,0,'k');

    a.setStartState(0);


    //a.shiftStates(10);
    cout<<a<<endl;

    cout<<"is finite? "<<a.finiteLanguage()<<endl;

    a.printAllWords();
    cout << "?=" << a.recognize ("bux", 0) << endl;
    return 0;
}

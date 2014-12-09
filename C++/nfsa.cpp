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


    bool recognize (char *w, int currentState)
    {
        if (w[0] == 0)
            return finalStates[currentState];

        const vector<int>& neigh = transitions[currentState][w[0]-'a'];
        for (int i = 0; i < neigh.size(); i++)
        {
            if (recognize(w+1,neigh[i]))
                return true;
        }
        return false;
    }

    NFSA &addTrans(int fromState, int toState, char symbol)
    {

        assert (symbol >= 'a' && symbol <= 'z' + 1);

        vector<vector<int> >emptyRow;
        ensureIndex(emptyRow, 'z' - 'a' + 1, vector<int> ());

        ensureIndex (transitions, fromState, emptyRow);
        ensureIndex(transitions, toState, emptyRow);

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

    bool finiteLangiage()
    //проверява дали езикът на автомата е краен
    {
        for (int fromState = 0; fromState < transitions.size(); fromState++)
        {
            for (char symbol = 0; symbol < 'z' - 'a' + 1; symbol++)
            {
                const vector<int> &toStates = transitions[fromState][symbol];
                for (int toState = 0; toState < toStates.size(); toState++)
                {
                    if(hasTransition(fromState, toStates.at(toState)))
                    {
                        if(hasLoop(fromState, toStates.at(toState)))
                        {
                            return false;
                        }
                    }

                    if(hasTransition(toStates.at(toState), fromState))
                    {
                        if(hasLoop(toStates.at(toState), fromState))
                        {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }

    bool finiteStack()
    {
        vector<int> visited;
        bool finite = true;

        for(int i = 0; i < transitions.size(); i++)
        {
            if(hasLoopStack(visited, i))
            {
                return false;
            }

            visited.clear();
        }

        return finite;
    }

    bool hasLoopStack(vector<int>& visited, int state)
    {
        for(int i = 0; i<visited.size(); i++)
        {
            if(state == visited[i])
            {
                return true;
            }
        }

        visited.push_back(state);

        for (int symbol = 0; symbol < 'z'-'a'+1; symbol++)
        {
            const vector<int>& toStates = transitions[state][symbol];
            for (int toState = 0; toState < toStates.size(); toState++)
            {
                if(hasLoopStack(visited, toStates[toState]))
                {
                    return true;
                }
                visited.pop_back();
            }
        }

        return false;
    }

    bool hasTransition(int from, int to)
    {
        for (int fromState = from; fromState < transitions.size(); fromState++)
        {
            for (char symbol = 0; symbol < 'z' - 'a' + 1; symbol++)
            {
                const vector<int> &toStates = transitions[fromState][symbol];
                for (int toState = 0; toState < toStates.size(); toState++)
                {
                    if (transitions[fromState][symbol][toState] == to)
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    bool hasTransitionLetter(int from, int to, char letter)
    {
        for (int fromState = 0; fromState < transitions.size(); fromState++)
        {
            for (char symbol = 0; symbol < 'z' - 'a' + 1; symbol++)
            {
                const vector<int> &toStates = transitions[fromState][symbol];
                for (int toState = 0; toState < toStates.size(); toState++)
                {
                    if (transitions[fromState][symbol][toState] == to && (char)(symbol+'a') == letter && fromState == from)
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    bool hasLoop(int currentState, int startedFrom)
    {
        //cout<<"Current: "<<currentState<<" Target: "<<startedFrom<<endl;
        if(currentState == startedFrom)
        {
            return true;
        }

        for (int fromState = currentState; fromState < transitions.size(); fromState++)
        {
            for (char symbol = 0; symbol < 'z' - 'a' + 1; symbol++)
            {
                const vector<int> &toStates = transitions[fromState][symbol];
                for (int toState = 0; toState < toStates.size(); toState++)
                {
                    if(hasTransition(fromState,toStates.at(toState)) && hasTransition(toStates.at(toState), fromState))
                    {
                        cout<<"Loop from: "<<fromState<<" to "<<toStates.at(toState)<<endl;
                        return true;
                    }

                    if(hasTransition(fromState, toStates.at(toState)))
                    {
                        hasLoop(fromState+1,toStates.at(toState));
                    }
                    if(hasTransition(toStates.at(toState), startedFrom))
                    {
                        hasLoop(toStates.at(toState), startedFrom);
                    }
                }
            }
        }
        return false;
    }

    void printAllWords()
    //печата всички думи от езика на автомата,
    //ако езикът е краен
    {
        if (finiteLangiage())
        {
            //loop through the words and print them
            //recursive function for each state (if reached final state => word)
            vector<char> word;

            for (int fromState = 0; fromState < transitions.size(); fromState++)
            {
                for (char symbol = 0; symbol < 'z' - 'a' + 1; symbol++)
                {
                    const vector<int> &toStates = transitions[fromState][symbol];
                    for (int toState = 0; toState < toStates.size(); toState++)
                    {
                        if (hasTransition(fromState, toStates.at(toState)))
                        {
                            // word.push_back(nextLetter(fromState));
                        }
                    }
                }
                for(int i =0; i<word.size(); i++)
                {
                    cout<<word[i];
                }
                word.clear();
            }
        }
    }

    bool isFinalState(int state)
    {
        return finalStates[state];
    }

    NFSA operator + (NFSA& other)
    {
        //L1 u L2 => N1 u N2 = new start state with epsilon transitions to the old starting states
        if(!finiteLangiage() || !other.finiteLangiage())
        {
            //no changes made
            cout<<"Can't combine two non-finite languages"<<endl;
            return *this;
        }

        NFSA newAutomaton;

        for (int fromState = 0; fromState < transitions.size(); fromState++)
        {
            for (int symbol = 0; symbol < 'z' - 'a' + 1; symbol++)
            {
                const vector<int> &toStates = transitions[fromState][symbol];
                for (int count = 0; count < toStates.size(); count++)
                {
                    newAutomaton.addTrans(fromState, toStates.at(count), (char)(symbol + 'a'));
                }
            }
        }
        int newStart = newAutomaton.transitions.size() + 1;
        newAutomaton.setStartState(newStart);
        //add epsilon transitions
        newAutomaton.addTrans(newStart, this->startState, (char)('z'+1));
        newAutomaton.addTrans(newStart, other.startState, (char)('z'+1));

        for (int fromState = 0; fromState < other.transitions.size(); fromState++)
        {
            for (int symbol = 0; symbol < 'z' - 'a' + 1; symbol++)
            {
                const vector<int> &toStates = other.transitions[fromState][symbol];
                for (int count = 0; count < toStates.size(); count++)
                {
                    //check if we haven't already added the transition
                    if(!newAutomaton.hasTransitionLetter(fromState, toStates.at(count), (char)(symbol+'a')))
                    {
                        newAutomaton.addTrans(fromState, toStates.at(count), (char)(symbol+'a'));
                    }
                }
            }
        }


        for(int i = 0; i < finalStates.size(); i++)
        {
            if(finalStates[i] == true)
            {
                newAutomaton.setFinalState(i);
            }
        }

        for(int i = 0; i < other.finalStates.size(); i++)
        {
            if(other.finalStates[i] == true)
            {
                newAutomaton.setFinalState(i);
            }
        }

        if(finalStates[startState] || other.finalStates[startState])
        {
            newAutomaton.setFinalState(startState);
        }

        return newAutomaton;
    }

};

ostream &operator << (ostream &out, const NFSA &a)
{
    out << "digraph{" << endl;

    int fromState, count;

    char symbol;

    for (fromState = 0; fromState < a.transitions.size(); fromState++)
    {
        for (symbol = 0; symbol <= 'z' - 'a' + 1; symbol++)
        {
            const vector<int> &toStates = a.transitions[fromState][symbol];
            for (count = 0; count < toStates.size(); count++)
            {
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

    NFSA a, b;

    a.addTrans (0, 1, 'a').addTrans(0, 1, 'b').
    addTrans (1, 2, 'c').addTrans(2, 30, 'x').
    addTrans (1, 4, 'u').addTrans(4, 30, 'z').
    addTrans (4, 30, 'a');

    //loops
    //.addTrans(4, 2, 'a');
    //a.addTrans(2,0, 'x');//.addTrans(1,0,'k');

    a.setStartState(0);
    a.setFinalState (30);
    a.setFinalState (4);

    //a.shiftStates(10);
    cout << a<<endl;
    //cout<<a.hasTransition(11, 14);
    cout<<"is finite? "<<a.finiteLangiage()<<endl;
    //a.printAllWords();
    cout << endl << "?=" << a.recognize ("bua", 0) << endl;

    b.addTrans(0,1,'b').addTrans(1,5,'c');
    b.addTrans(5,10,'b').addTrans(10,20,'d').addTrans(20,30,'x');//.addTrans(2,30,'c');
    b.setStartState(5);
    b.setFinalState(30);
    cout<<b<<endl;
    NFSA c = a + b;
    cout<<endl<<"Union:"<<endl<<c<<endl;;
    return 0;
}

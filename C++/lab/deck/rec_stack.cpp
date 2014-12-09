#include <iostream>
#include <stack>
#include <queue>
#include <vector>

using namespace std;

#define MAZE_W 5
#define MAZE_H 5

int maze[MAZE_W][MAZE_H] = {0,1,0,0,0,
             	      		0,1,0,1,0,
			                0,1,0,1,0,
		                	0,0,0,1,0,
		                	1,1,1,1,0};
bool correct (int x, int y)
{
	return x >=0 && x < MAZE_W &&
	       y >=0 && y < MAZE_H &&
	       maze[x][y] == 0;
}

bool way (int x, int y, int targetX, int targetY)
{
	if (!correct (x,y))
		return false;

	if (x == targetX && y == targetY)
		return true;

	maze[x][y] = 2;

	return way (x,y-1,targetX,targetY) ||
		   way (x-1,y,targetX, targetY) ||
		   way (x+1,y,targetX,targetY) ||
		   way (x,y+1,targetX,targetY);
}

vector<pair<int, int> > findWayRec (int x, int y, int targetX, int targetY)
{
	vector<pair<int, int> > result;
	if (!correct (x,y))
	{
		//result is empty
		return result;
	}

	result.push_back(pair<int, int> (x,y));
	if (x == targetX && y == targetY)
		return result;

	maze[x][y] = 2;


	vector<pair<int, int> > nextSteps;

	nextSteps = findWayRec(x,y-1, targetX, targetY);
	if(nextSteps.size() > 0)
	{
		nextSteps = findWayRec(x-1,y, targetX, targetY);
	}
	if(nextSteps.size() > 0)
	{
		nextSteps = findWayRec(x+1,y, targetX, targetY);
	}
	if(nextSteps.size() > 0)
	{
		nextSteps = findWayRec(x,y+1, targetX, targetY);
	}

	if(nextSteps.size() > 0)
	{
		nextSteps.push_back(pair<int, int> (x, y));
		return nextSteps;
	}

	return nextSteps;
}


bool wayIter (int x, int y, int targetX, int targetY)
{

	stack<pair<int,int> >s;

	s.push (pair<int,int> (x,y));

	while (!s.empty() &&
		   (s.top().first != targetX ||
		   	s.top().second != targetY))
	{
		pair<int,int> current = s.top();
		s.pop();

		maze[current.first][current.second]=2;

		if (correct (current.first,current.second-1))
			s.push (pair<int,int> (current.first,current.second-1));
		if (correct (current.first-1,current.second))
			s.push (pair<int,int> (current.first-1,current.second));
		if (correct (current.first+1,current.second))
			s.push (pair<int,int> (current.first+1,current.second));
		if (correct (current.first,current.second+1))
			s.push (pair<int,int> (current.first,current.second+1));

	}

	return !s.empty();
}

bool wayBfs(int x, int y, int targetX, int targetY)
{
	queue<pair<int,int> >q;

	q.push (pair<int,int> (x,y));

	while (!q.empty() &&
		   (q.front().first != targetX ||
		   	q.front().second != targetY))
	{
		pair<int,int> current = q.front();
		q.pop();

		maze[current.first][current.second]=2;

		if (correct (current.first,current.second-1))
			q.push (pair<int,int> (current.first,current.second-1));
		if (correct (current.first-1,current.second))
			q.push (pair<int,int> (current.first-1,current.second));
		if (correct (current.first+1,current.second))
			q.push (pair<int,int> (current.first+1,current.second));
		if (correct (current.first,current.second+1))
			q.push (pair<int,int> (current.first,current.second+1));
	}

	return !q.empty();
}

void cleanup()
{
	for (int i = 0; i < MAZE_H; ++i)
	{
		for (int j = 0; j < MAZE_W; ++j)
		{
			if(maze[i][j] == 2)
			{
				maze[i][j] = 0;
			}
		}
	}
}

void hanoi (int fromPile, int toPile, int tempPile, int k)
{
	stack<vector<int> > s;
    vector<int> element;
    element.push_back(fromPile);
    element.push_back(tempPile);
    element.push_back(toPile);
    element.push_back(k);
    s.push(element);

	while (!s.empty())
	{
		std::vector<int> current = s.top();
		s.pop();

        if (current[3] == 1)
        {
            cout << "Please move the top disk from " << current[0];
            cout<< " to " << current[1] << endl;

            return;
        }
        else
        {
        	element.clear();
        	element.push_back(current[2]);
        	element.push_back(current[1]);
        	element.push_back(current[0]);
        	element.push_back(current[3]- 1);
        	s.push(element);

        	// clear
        	element.clear();
        	element.push_back(current[0]);
        	element.push_back(current[1]);
        	element.push_back(current[2]);

        	s.push(element);
        	//push 0,1,2,1
        	//push el

        	element.clear();
        	element.push_back(current[0]);
        	element.push_back(current[2]);
        	element.push_back(current[1]);
        	element.push_back(current[3] - 1);
        	s.push(element);
        	//clear
        	//push 0, 2, 1, [3] - 1
        	//push el
            hanoi (from,temp,to,k1-1);
            hanoi (from,to,temp,1);
            hanoi (temp,to,from,k1-1);
        }
	}
}

template <class T>
vector<T> tail(const vector<T>& v)
{
	vector<T> result = v;
	result.erase(result.begin());
	return result;
}

void printway(const vector<pair<int, int> >& way)
{
	if(way.size() == 0)
	{
		return;
	}

	cout<<"["<<way[0].first<<","<<way[0].second<<"]";
	printway(tail(way));
}

int main ()
{
	cout<<wayIter(0,0,4,4)<<endl;
	cleanup();
	cout << wayBfs (0,0,4,4) << endl;
	cleanup();
	printway(findWayRec(0,0,4,4));

	//hanoi (1,2,3,3);
}


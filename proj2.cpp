#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <climits>

using namespace std;

void isPal(const string &pal, int length, vector< vector<int> > &P);
void cuts(const string &pal, int length, vector< vector<int> > &P, vector<int> &C, vector<int> &B);
void backtrack(const string &pal, int length, vector<int> &C, vector<int> &B);

int main()
{
  string pal = "";
  cin >> pal;

  int length = pal.length();
  vector< vector<int> > P(length);

  for (int i = 0; i < length; i++)
  {
    for (int j = 0; j < length; j++)
    {
      P[i].push_back(0);
    }
  }

  isPal(pal, length, P);

  vector<int> C(length, INT_MAX);
  vector<int> B(length, 0);

  C[0] = 0;
  B[0] = -1;

  cuts(pal, length, P, C, B);

  backtrack(pal, length - 1, C, B);
  
  return 0;
}

void isPal(const string &pal, int length, vector< vector<int> > &P)
{
  if ((pal == "") || (length < 2))
    return;

  for (int i = length - 1; i >= 0; i--)
  {
    for (int j = i; j < length; j++)
    {
      if (i == j)
        P[i][j] = 1;

      else if (pal[i] == pal[j])
      {
        if ((j - i) == 1)
          P[i][j] = 1;
        else
          P[i][j] = P[i + 1][j - 1];
      }

      else
        P[i][j] = 0;
    }
  }

  //check P matrix
  /*
  for (int i = 0; i < (int)P.size(); i++)
  {
    for (int j = 0; j < (int)P[i].size(); j++)
    {
      cout << P[i][j] << " ";
    }
    cout << endl;
  }
  */
}

void cuts(const string &pal, int length, vector< vector<int> > &P, vector<int> &C, vector<int> &B)
{
  for (int i = 0; i < length; i++)
  {
    if (P[0][i] == 1)
    {
      C[i] = 0;
      B[i] = -1;
    }
    
    else
    {
      for (int j = 0; j <= i - 1; j++)
      {
        if (P[j + 1][i] == 1)
        {
          if (1 + C[j] < C[i])
          {
            C[i] = std::min(C[i], 1 + C[j]);
            B[i] = j;
          }
        }
      }
    }
  }

  /*
  cout << "C: ";
  for (int i = 0; i < length; i++)
  {
    cout << C[i] << " ";
  }

  cout << endl;

  cout << "B: ";
  for (int i = 0; i < length; i++)
  {
    cout << B[i] << " ";
  }

  cout << endl;
  */
}

void backtrack(const string &pal, int length, vector<int> &C, vector<int> &B)
{
  string temp = "";

  if (B[length] == -1)
  {
    temp = pal.substr(0, length - B[length]);
    cout << temp << endl;
    return;
  }

  backtrack(pal, B[length], C, B);

  temp = pal.substr(B[length] + 1, length - B[length]);

  cout << temp << endl;
}

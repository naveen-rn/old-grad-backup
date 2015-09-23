# include <stdio.h>
# include <vector>
# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <iomanip>
# include <map>


using namespace std;

vector <string> fileIP;
vector <string> tot_words;
vector <string> unique_words;
vector <int>    unique_count;

int get_IP_from_file_ ()
{
  for (string line; getline (cin, line);)
    fileIP. push_back (line);
  return 0;
}

int get_num_of_lines_ ()
{
  int num_lines = fileIP. size ();
  return (num_lines);
}

int get_num_of_words_ ()
{
  int count = 0;
  
  for (int iBuffer = 0; iBuffer < fileIP. size (); iBuffer++)
  { 
    string temp_string;
    istringstream StrStream (fileIP[iBuffer]); 
    while (StrStream)
    {
      getline (StrStream, temp_string, ' ');
      tot_words. push_back (temp_string); 
    }
  }
  return 0;
}

int get_word_occurance_ ()
{
  for (int iBuffer = 0; iBuffer < tot_words. size (); iBuffer++)
  {
    int count = 0;
    for (int jBuffer = 0; jBuffer < unique_words. size (); jBuffer++)
    {
      if (tot_words[iBuffer] == unique_words[jBuffer])
      {
 	count++;
        unique_count[jBuffer] = unique_count[jBuffer] + 1;
      }
    }
    if (count == 0 )
    {
      unique_words. push_back (tot_words[iBuffer]);
      unique_count. push_back (1);
    }
  }
  return 0;
}

int put_output_ ()
{
  ofstream opFile;
  opFile. open ("output");
  if (unique_words. size() == unique_count. size())
  {
    opFile << left;
    opFile << "Total Number of Unique Word Count in File" << unique_words. size() << endl;
    opFile << "__________________________________________________________________________" << endl; 
    opFile << setw(30) << "Word" << "Word Count" << endl;
    opFile << "__________________________________________________________________________" << endl;
    for (int iBuffer = 0; iBuffer < unique_words. size(); iBuffer++)
      opFile << setw(30) << unique_words[iBuffer] << unique_count[iBuffer] << endl;
  } 
  return 0;
}


int main ()
{
  get_IP_from_file_ ();
  int num_lines = get_num_of_lines_ ();
  cout << "Number of Lines: " << num_lines << endl;
  get_num_of_words_ ();
  cout << "Number of Words: " << tot_words.size() << endl; 
  get_word_occurance_ ();
  put_output_ ();
  return (0);  
}


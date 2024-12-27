#include <iostream>
#include <string>
#include <cstddef>

#include "Token.h"
#include "DList.h"

using namespace std;

void parse(string& str, Queue<Token>& queue)
{
 string const delims{ " +-*/()^" };
 string tmp;
 size_t pos;
 while (!str.empty()) // until there is nothing left ...
 {
 pos = str.find_first_of(delims);
 tmp = str.substr(0, pos);
 if (tmp.size() == 0) // first token is an operator
{
 //cout << str.substr(0, 1);
 queue.enqueue(Token(str.substr(0, 1))); // add to queue
 str.erase(0, 1); // and delete from string
}
else // first token is a number
{
 float number = stof(tmp); 
 //cout << number;
 queue.enqueue(Token(number)); // add to queue
 str.erase(0, pos); // delete from string
 }
 }
}
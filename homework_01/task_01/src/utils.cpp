#include <iostream>
#include <stack>
#include <string>
#include <vector>

std::vector<std::string> SplitString(const std::string &data) {
  std::string delimiter = " ";
  std::string new_data = data;
  new_data += ' ';
  size_t pos = 0;
  std::string token;
  std::vector<std::string> substrings;
  std::vector<int> del_inds;
  int f = 0;

  for (int i = 0; i < new_data.length(); i++) {
    if (new_data[i] == '\t') {
      new_data[i] = ' ';
    }
    if (new_data[i] == '(') {
      f++;
    }
    if (new_data[i] == ' ' && f != 0) {
      del_inds.push_back(new_data.length() - i);
      ;
    }
    if (new_data[i] == ')') {
      f--;
      for (int j = 0; j < del_inds.size(); j++) {
        new_data[new_data.length() - del_inds[j]] = '_';
      }
    }
  }
  while ((pos = new_data.find(delimiter)) != std::string::npos) {
    token = new_data.substr(0, pos);
    for (int i = 0; i < token.length(); i++) {
      if (token[i] == '_') {
        for (int j = 0; j < del_inds.size(); j++) {
          if (new_data.length() - i == del_inds[j]) {
            token[i] = ' ';
            del_inds.erase(del_inds.begin() + j);
            break;
          }
        }
      }
    }
    if (token.length() > 0) {
      substrings.push_back(token);
    }
    new_data.erase(0, pos + delimiter.length());
  }

  return substrings;
}

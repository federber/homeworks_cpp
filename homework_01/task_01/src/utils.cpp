#include <iostream>
#include <stack>
#include <string>
#include <vector>

std::vector<std::string> SplitString(const std::string &data) {
  std::string delimiter = " ";
  std::string newdata = data;
  newdata += ' ';
  size_t pos = 0;
  std::string token;
  std::vector<std::string> substrings;
  std::vector<int> pi;
  int ii = 0;
  int f = 0;
  for (int i = 0; i < newdata.length(); i++) {
    if (newdata[i] == '(') {
      f++;
    }
    if ((newdata[i] == ' ') && (f != 0)) {
      pi.push_back(newdata.length() - i);
      ;
    }
    if ((newdata[i] == ')')) {
      f--;
      for (int j = 0; j < pi.size(); j++) {
        newdata[newdata.length() - pi[j]] = '_';
      }
    }
  }
  while ((pos = newdata.find(delimiter)) != std::string::npos) {
    token = newdata.substr(0, pos);
    for (int i = 0; i < token.length(); i++) {
      if (token[i] == '_') {
        for (int j = 0; j < pi.size(); j++) {
          if (newdata.length() - i == pi[j]) {
            token[i] = ' ';
            pi.erase(pi.begin() + j);
            break;
          }
        }
      }
    }
    substrings.push_back(token);
    newdata.erase(0, pos + delimiter.length());
  }

  return substrings;
}

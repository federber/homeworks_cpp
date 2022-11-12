#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

std::string CalcTwo(std::vector<std::string> vec) {
  if (vec[1] == "+") {
    return std::to_string(std::atof(vec[0].c_str()) +
                          std::atof(vec[2].c_str()));
  }
  if (vec[1] == "-") {
    return std::to_string(std::atof(vec[0].c_str()) -
                          std::atof(vec[2].c_str()));
  }
  if (vec[1] == "*") {
    return std::to_string(std::atof(vec[0].c_str()) *
                          std::atof(vec[2].c_str()));
  }
  if (vec[1] == "/") {
    return std::to_string(std::atof(vec[0].c_str()) /
                          std::atof(vec[2].c_str()));
  } else
    return "NaN";
}

std::vector<std::string> SplitToTokens(const std::string &data) {

  std::vector<char> delimiters = {'+', '-', '*', '/'};
  std::string newdata = data;
  if (newdata[0] == '(' && newdata[newdata.length() - 1] == ')') {
    newdata.erase(0, 1);
    newdata.pop_back();
  }
  if (newdata[0] != '-' && newdata[0] != '+' && newdata[0] != '/' &&
      newdata[0] != '*') {
    newdata = '+' + newdata;
  }
  std::string token;
  std::vector<std::string> tokens;
  std::vector<std::pair<int, char>> ppi;
  int f = 0;
  for (int i = 0; i < newdata.length(); i++) {
    if (newdata[i] == '(') {
      f++;
    }
    if ((std::find(delimiters.begin(), delimiters.end(), newdata[i]) !=
         delimiters.cend()) &&
        (f != 0)) {
      std::pair<int, char> pr;
      pr.first = newdata.length() - i;
      pr.second = newdata[i];
      ppi.push_back(pr);
    }
    if ((newdata[i] == ')')) {
      f--;
      for (int j = 0; j < ppi.size(); j++) {
        newdata[newdata.length() - ppi[j].first] = '_';
      }
    }
  }
  if (f == 0) {
    int k = 0;
    while (newdata.length() > 0) {
      std::vector<char>::iterator itr =
          std::find(delimiters.begin(), delimiters.end(), newdata[k]);
      token = newdata.substr(0, k);
      if (k >= newdata.length()) {
        tokens.push_back(newdata.erase(0, 1));
        break;
      }
      if (itr != delimiters.cend()) {
        int delind = std::distance(delimiters.begin(), itr);
        token = newdata.substr(0, k);
        for (int i = 0; i < token.length(); i++) {
          if (token[i] == '_') {
            for (int j = 0; j < ppi.size(); j++) {
              if (newdata.length() - i == ppi[j].first) {
                token[i] = ppi[j].second;
                ppi.erase(ppi.begin() + j);
                break;
              }
            }
          }
        }
        tokens.push_back(token.erase(0, 1));
        std::string sstr(1, delimiters[delind]);
        tokens.push_back(sstr);
        newdata.erase(0, newdata.substr(0, k).length());
        k = 0;
      }
      k++;
    }
  }
  if (tokens[0] == "") {
    tokens[0] = "0";
  }
  return tokens;
}

std::vector<std::string> Calc(std::vector<std::string> vec) {
  if (vec.size() == 1) {
    return vec;
  }
  for (int i = 0; i < vec.size(); i++) {
    if (vec[i][0] == '(' && vec[i][vec[i].length() - 1]) {
      vec[i].erase(0, 1);
      vec[i].pop_back();
      vec[i] = Calc(SplitToTokens(vec[i]))[0];
    }
  }
  for (int i = 0; i < vec.size(); i++) {
    if (vec[i] == "*" || vec[i] == "/") {
      vec[i] = CalcTwo({vec[i - 1], vec[i], vec[i + 1]});
      vec.erase(vec.begin() + i + 1);
      vec.erase(vec.begin() + i - 1);
      return Calc(vec);
    }
  }
  for (int i = 0; i < vec.size(); i++) {
    if (vec[i] == "+" || vec[i] == "-") {
      vec[i] = CalcTwo({vec[i - 1], vec[i], vec[i + 1]});
      vec.erase(vec.begin() + i + 1);
      vec.erase(vec.begin() + i - 1);
      return Calc(vec);
    }
  }
}

int Calculate(const std::string &data) {
  return (int)std::atof(Calc(SplitToTokens(data))[0].c_str());
}

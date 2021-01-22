#include <iostream>
#include <map>
#include <string>

void parseUrl(std::string &url, std::map<std::string, std::string> &res) {
  int         n   = url.find("?");
  std::string tmp = url.substr(n + 1);  // 只保留参数部分
  while (std::string::npos != (n = tmp.find("&"))) {
    std::string param = tmp.substr(0, n - 1);
    int         l     = param.find("=");  // 分割key，value
    std::string key   = param.substr(0, l - 1);
    std::string value = param.substr(l + 1);
    res.insert(std::make_pair(key, value));
    tmp = tmp.substr(n + 1);
  }
  // 处理最后一部分
  int         l     = tmp.find("=");  // 分割key，value
  std::string key   = tmp.substr(0, l - 1);
  std::string value = tmp.substr(l + 1);
  res.insert(std::make_pair(key, value));
}

int main(int argc, char **argv) {
  std::map<std::string, std::string> res;
  std::string url = "http://www.baidu.com?id=123&style=789&code=781";
  parseUrl(url, res);
  std::cout << "url is " << url << std::endl;
  for (std::map<std::string, std::string>::iterator iter = res.begin();
       iter != res.end(); iter++) {
    std::cout << iter->first << "=" << iter->second << std::endl;
  }
}

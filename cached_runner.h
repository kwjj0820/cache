#ifndef CACHED_RUNNER_H
#define CACHED_RUNNER_H

#include "cache.h"
#include <fstream>
#include <string>

class CachedRunner {
private:
  // TODO: private 멤버 변수와 함수 추가 가능
  enum TaskType { MULTIPLY, PALINDROME };
  int hitCount;
  int missCount;
  Cache *cache_;
    
  bool isPalindrome(std::string str)
  {
    for (int i = 0; i < str.size() / 2; i++) {
      if (str[i] != str[str.size() - i - 1]) {
        return false;
      }
    }
    return true;
  }

public:
  CachedRunner(Cache &cache);

  // 파일의 숫자를 전부 곱하여 반환한다
  double multiply(std::string filename);

  // 파일에서 가장 긴 팰린드롬을 찾아 인덱스를 반환한다
  int palindrome(std::string filename);

  // 캐시에 히트한 횟수를 반환한다
  int hits();

  // 캐시에 미스한 횟수를 반환한다
  int misses();
};

#endif
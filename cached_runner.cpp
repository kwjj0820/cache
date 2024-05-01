#include "cached_runner.h"

CachedRunner::CachedRunner(Cache &cache)
{
  cache_ = cache;
  hitCount = 0;
  missCount = 0;
}

// 파일의 숫자를 전부 곱하여 반환한다
double CachedRunner::multiply(std::string filename)
{
  std::ifstream file(filename);
  double result = 1;
  double number;
  if(cache_.get(filename, number))
  {
    hitCount++;
    return number;
  }
  while(file >> number)
  {
    result *= number;
  }
  cache_.add(filename, number);
  missCount++;
  return result;
}

// 파일에서 가장 긴 팰린드롬을 찾아 인덱스를 반환한다
int CachedRunner::palindrome(std::string filename)
{
  std::ifstream file(filename);
  std::string fullText;
  std::string line;
  while (std::getline(file, line))
  {
    fullText += line;
  }

  int maxLength = 0;
  int maxIndex = 0;
  std::string maxPalindrome;
  if(cache_.get(filename, maxIndex))
  {
    hitCount++;
    return maxIndex;
  }

  for (int i = 0; i < fullText.size(); i++)
  {
    for (int j = i + 1; j < fullText.size(); j++)
    {
      std::string sub = fullText.substr(i, j - i + 1);
      if (isPalindrome(sub) && sub.size() > maxLength)
      {
        maxLength = sub.size();
        maxIndex = i;
        maxPalindrome = sub;
      }
    }
  }
  cache_.add(filename, maxIndex);
  missCount++;
  return maxIndex;
}

// 캐시에 히트한 횟수를 반환한다
int CachedRunner::hits()
{
  return hitCount;
}

// 캐시에 미스한 횟수를 반환한다
int CachedRunner::misses()
{
  return missCount;
}

#include "cache.h"
  
Cache::Cache()
{
  head = NULL;
  rear = NULL;
  size = 0;
}

Cache::~Cache()
{
  Node* cur = head;
  Node* temp;
  while(cur != NULL)
  {
    temp = cur;
    cur = cur->getNext();
    delete temp;
  }
}

void Cache::moveToHead(Node* node)
{
  if(node == head) return;
  else if(node == rear)
  {
    rear = rear->getPrev();
    rear->setNext(NULL);
  }
  else
  {
    node->getPrev()->setNext(node->getNext());
    node->getNext()->setPrev(node->getPrev());
  }
  node->setNext(head);
  node->setPrev(NULL);
  head->setPrev(node);
  head = node;
}

// int를 cache에 추가한다
void Cache::add(std::string key, int value)
{
  Node* cur = head;

  std::string newKey;
  if(key[10] == 'm') newKey = "multyply(" + key + ")";
  else newKey = "palindrome(" + key + ")";

  while(cur != NULL)
  {
    if(cur->getKey() == newKey)
    {
      moveToHead(cur);
      return;
    }
    cur = cur->getNext();
  }

  if(size == CACHE_SIZE)
  {
    Node* temp = rear;
    rear->getPrev()->setNext(NULL);
    rear = rear->getPrev();
    delete temp;
    size--;
  }

  Node* newNode = new Node(newKey, value);
  if(size == 0)
  {
    head = newNode;
    rear = newNode;
    size++;
  }
  else
  {
    head->setPrev(newNode);
    newNode->setNext(head);
    head = newNode;
    size++;
  }
}

// double을 cache에 추가한다
void Cache::add(std::string key, double value)
{
  Node* cur = head;
  std::string newKey;
  if(key[10] == 'm') newKey = "multyple(" + key + ")";
  else newKey = "palindrome(" + key + ")";
  while(cur != NULL)
  {
    if(cur->getKey() == newKey)
    {
      moveToHead(cur);
      return;
    }
    cur = cur->getNext();
  }

  if(size == CACHE_SIZE)
  {
    Node* temp = rear;
    rear->getPrev()->setNext(NULL);
    rear = rear->getPrev();
    delete temp;
    size--;
  }

  Node* newNode = new Node(newKey, value);
  if(size == 0)
  {
    head = newNode;
    rear = newNode;
    size++;
  }
  else
  {
    head->setPrev(newNode);
    newNode->setNext(head);
    head = newNode;
    size++;
  }
}

// key에 해당하는 value를 cache에서 가져온다
bool Cache::get(std::string key, int &value)
{
  Node* cur = head;
  std::string newKey;
  if(key[10] == 'm') newKey = "multyple(" + key + ")";
  else newKey = "palindrome(" + key + ")";
  while(cur != NULL)
  {
    if(cur->getKey() == newKey)
    {
      value = cur->getIntVal();
      moveToHead(cur);
      return true;
    }
    cur = cur->getNext();
  }
  return false;
}

// key에 해당하는 value를 cache에서 가져온다.
bool Cache::get(std::string key, double &value)
{
  Node* cur = head;
  std::string newKey;
  if(key[10] == 'm') newKey = "multyple(" + key + ")";
  else newKey = "palindrome(" + key + ")";
  while(cur != NULL)
  {
    if(cur->getKey() == newKey)
    {
      value = cur->getDoubleVal();
      moveToHead(cur);
      return true;
    }
    cur = cur->getNext();
  }
  return false;
}


// 디버그 및 채점 용: 연결 리스트를 문자열로 표현하여 반환한다
// 다음과 같이 표현된 문자열을 반환한다
// [key1: value1] -> [key2: value2] -> ... -> [keyN: valueN]
std::string Cache::toString()
{
  std::string result; 
  Node* cur = head;
  std::cout << "size: " << size << std::endl;
  while(cur != NULL)
  {
    result += "[" + cur->getKey() + ": ";
    if(cur->checkInt())
    {
      result += std::to_string(cur->getIntVal());
    }
    else
    {
      result += std::to_string(cur->getDoubleVal());
    }
    cur = cur->getNext();
    if(cur != NULL) result += "] -> "; 
    else result += "]";
  }
  return result; 
}
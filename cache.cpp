#include "cache.h"
  
Cache::Cache()
{
  head = NULL;
  rear = NULL;
  size = 0;
  hash_ = new Hash();
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
  if (node == head) // 노드가 이미 맨 앞에 있는 경우
    return;

  if (node == rear) // 노드가 맨 뒤에 있는 경우
  {
    rear = node->getPrev();
    if (rear) // rear가 NULL이 아닌 경우에만
      rear->setNext(NULL);
  }
  else // 노드가 중간에 있는 경우
  {
    Node* prevNode = node->getPrev();
    Node* nextNode = node->getNext();

    if (prevNode)
      prevNode->setNext(nextNode);
    if (nextNode)
      nextNode->setPrev(prevNode);
  }

  node->setNext(head); // 현재 head 앞에 노드를 추가
  if (head) // head가 NULL이 아닌 경우에만
    head->setPrev(node);

  head = node; // head를 현재 노드로 업데이트
  node->setPrev(NULL); // 현재 노드의 prev를 NULL로 설정
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
    hash_->remove(rear);
    rear->getPrev()->setNext(NULL);
    rear = rear->getPrev();
    delete temp;
    size--;
  }

  Node* newNode = new Node(newKey, value);
  hash_->insert(newKey, value);
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
    hash_->remove(rear);
    rear->getPrev()->setNext(NULL);
    rear = rear->getPrev();
    delete temp;
    size--;
  }

  Node* newNode = new Node(newKey, value);
  hash_->insert(newKey, value);
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

  if(hash_->get(newKey, value))
  {
    Node* cur = head;
    {
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
    }
    return true;
  }
  else return false;
}

// key에 해당하는 value를 cache에서 가져온다.
bool Cache::get(std::string key, double &value)
{
  Node* cur = head;
  std::string newKey;
  if(key[10] == 'm') newKey = "multyply(" + key + ")";
  else newKey = "palindrome(" + key + ")";

  if(hash_->get(newKey, value))
  {
    Node* cur = head;
    {
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
    }
    return true;
  }
  else return false;
}


// 디버그 및 채점 용: 연결 리스트를 문자열로 표현하여 반환한다
// 다음과 같이 표현된 문자열을 반환한다
// [key1: value1] -> [key2: value2] -> ... -> [keyN: valueN]
std::string Cache::toString()
{
  std::string result; 
  Node* cur = head;
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
  return result + '\n'; 
}

int Cache::Hash::hash(std::string key)
{
  int sum = 0;
  for(int i = 0; i < key.length(); i++)
  {
    sum += key[i];
  }
  return sum % HASH_SIZE;
}

Cache::Hash::Hash()
{
  for(int i = 0; i < HASH_SIZE; i++)
  {
    table[i] = NULL;
  }
}

Cache::Hash::~Hash()
{
  for (int i = 0; i < HASH_SIZE; ++i)
  {
    Node* cur = table[i];
    while (cur != NULL)
    {
      Node* temp = cur;
      cur = cur->getNext();
      delete temp;
    }
    table[i] = NULL;
  }
}

void Cache::Hash::insert(std::string key, int value)
{
  int idx = hash(key);
  Node* cur = table[idx];
  while(cur != NULL)
  {
    if(cur->getKey() == key)
    {
      return;
    }
    cur = cur->getNext();
  }

  // 중복 키가 없으면 새 노드 추가
  Node* newNode = new Node(key, value);
  newNode->setNext(table[idx]);
  if(table[idx] != NULL)
  {
    table[idx]->setPrev(newNode);
  }
  table[idx] = newNode;
}

void Cache::Hash::insert(std::string key, double value)
{
  int idx = hash(key);
  Node* cur = table[idx];
  while(cur != NULL)
  {
    if(cur->getKey() == key)
    {
      return;
    }
    cur = cur->getNext();
  }

  // 중복 키가 없으면 새 노드 추가
  Node* newNode = new Node(key, value);
  newNode->setNext(table[idx]);
  if(table[idx] != NULL)
  {
    table[idx]->setPrev(newNode);
  }
  table[idx] = newNode;
}

bool Cache::Hash::get(std::string key, int& val)
{
  int idx = hash(key);
  Node* cur = table[idx];
  while(cur != NULL)
  {
    if(cur->getKey() == key)
    {
      val = cur->getIntVal();
      return true; 
    }
    cur = cur->getNext(); 
  }
  return false;
}

bool Cache::Hash::get(std::string key, double& val)
{
  int idx = hash(key);
  Node* cur = table[idx];
  while(cur != NULL)
  {
    if(cur->getKey() == key)
    {
      val = cur->getDoubleVal();
      return true; 
    }
    cur = cur->getNext(); 
  }
  return false;
}

void Cache::Hash::remove(Node* node)
{
  int idx = hash(node->getKey());
  Node* cur = table[idx];
  Node* prev = NULL;

  while (cur != NULL)
  {
    if (cur->getKey() == node->getKey())
    {
      if (prev == NULL)
      {
        table[idx] = cur->getNext();
        if (table[idx] != NULL)
        {
          table[idx]->setPrev(NULL);
        }
      }
      else
      {
        prev->setNext(cur->getNext());
        if (cur->getNext() != NULL)
        {
          cur->getNext()->setPrev(prev);
        }
      }
      delete cur;
      return;
    }
    prev = cur;
    cur = cur->getNext();
  }
}
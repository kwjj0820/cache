#ifndef CACHE_H
#define CACHE_H

#include <string>
#include <iostream>

#define CACHE_SIZE 10
#define HASH_SIZE 10

class Cache {
private:
  // TODO: private inner struct/class 선언 가능
  // TODO: private 멤버 변수와 함수 추가 가능
  class Node
  {
    private:
      int intVal;
      double doubleVal;
      bool isInt;
      Node* next;
      Node* prev;
      std::string key;

      public:
        Node(std::string key, int value): key(key), prev(NULL), next(NULL), intVal(value), isInt(true), doubleVal(0){};
        Node(std::string key, double value): key(key), prev(NULL), next(NULL), doubleVal(value), isInt(false), intVal(0){};
        int getIntVal(){return intVal;}
        double getDoubleVal(){return doubleVal;}
        Node* getNext(){return next;}
        Node* getPrev(){return prev;}
        void setNext(Node* node){next = node;}
        void setPrev(Node* node){prev = node;}
        std::string getKey(){return key;}
        bool checkInt(){return isInt;}
  };

  Node* head;
  Node* rear;
  int size;
  void moveToHead(Node* node);

  class Hash
  {
    private:
      Node* table[HASH_SIZE];

    public:
      Hash();
      ~Hash();
      int hash(std::string key);
      void insert(std::string key, int value);
      void insert(std::string key, double value);
      bool get(std::string key, int& val);
      bool get(std::string key, double& val);
      void remove(Node* node);
  };
  Hash* hash_;

public:
  Cache();
  ~Cache();
  // int를 cache에 추가한다
  void add(std::string key, int value);

  // double을 cache에 추가한다
  void add(std::string key, double value);

  // key에 해당하는 value를 cache에서 가져온다
  // 타입과 key가 동일한 원소가 없다면 false를 반환한다.
  bool get(std::string key, int &value);

  // key에 해당하는 value를 cache에서 가져온다.
  // 타입과 key가 동일한 원소가 없다면 false를 반환한다.
  bool get(std::string key, double &value);

  // 디버그 및 채점 용: 연결 리스트를 문자열로 표현하여 반환한다
  // 다음과 같이 표현된 문자열을 반환한다
  // [key1: value1] -> [key2: value2] -> ... -> [keyN: valueN]
  std::string toString();
};

#endif
#ifndef DILEMMA_FACTORY_H
#define DILEMMA_FACTORY_H

#include <string>
#include <map>
#include <memory>
#include <functional>
#include <ctime>
#include "strategy.h"

template<class T>
class Factory final{

public:
    ~Factory(){}

    template<class S>
    S* create(const std::string& _name) {
        auto i = Strategy_map.find(_name);
        if( i != Strategy_map.end()){
            return (i->second)();
        }
        return nullptr;
    }

    template <class S>
    bool add(const std::string& _name){
        auto i = Strategy_map.find(_name);
        if(i == Strategy_map.end()){
            Strategy_map[_name] = [](){return new S;};
            return true;
        }
        return false;
    }

    bool Is_Register(const std::string& _name) {
        return Strategy_map.find(_name) != Strategy_map.end();
    }

    static Factory& init(){
        static Factory factory;
        return factory;
    }

    Factory(const Factory& other) = delete;
    Factory& operator=(const Factory& other) = delete;

private:
    Factory<T>(){std::srand(std::time(0));}
    std::map<std::string, std::function<T* ()>> Strategy_map;

};

extern Factory<Strategy>& factory;



#endif //DILEMMA_FACTORY_H

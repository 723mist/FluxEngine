#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include "../Objects/object.hpp"
#include <string>

class Map {
private:
    std::string name;
    std::vector<Object> objects;

public:
    Map(const std::string& name = "Map") : name(name) {}

    void addObject(const Object& obj) {
        objects.push_back(obj);
    }

    Object& createObject(const std::string& objName = "NewObject") {
        objects.emplace_back(objName);
        return objects.back();
    }

    std::vector<Object>& GetObjects() { return objects; }

    Object* findObject(const std::string& name) {
        for (auto& obj : objects) {
            if (obj.name == name) return &obj;
        }
        return nullptr;
    }

    std::string getName() const { return name; }
    size_t getObjectCount() const { return objects.size(); }
};
#endif

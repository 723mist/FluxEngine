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

    void AddObject(const Object& obj) {
        objects.push_back(obj);
    }

    Object& CreateObject(const std::string& objName = "NewObject") {
        objects.emplace_back(objName);
        return objects.back();
    }

    std::vector<Object>& GetObjects() { return objects; }

    Object* FindObject(const std::string& name) {
        for (auto& obj : objects) {
            if (obj.name == name) return &obj;
        }
        return nullptr;
    }

    std::string GetName() const { return name; }
    size_t GetObjectCount() const { return objects.size(); }
};
#endif

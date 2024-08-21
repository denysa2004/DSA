#pragma once
#include "Map.h"
class MapIterator
{
	//DO NOT CHANGE THIS PART
	friend class Map;
private:
	const Map& map;
    int index; //fur die Position
    MapIterator(const Map& m);
    MapIterator(const Map& m, int n);//constructorul nou

public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
    void nextiterator(int n);//functia noua
};



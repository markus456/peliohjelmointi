#pragma once
#include "SDL.h"
#include <vector>
#include "Tiili.h"
#include "Road.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
using std::vector;

const int MAP_HEIGHT = 19;		//kartan koko tiileiss‰
const int MAP_WIDTH = 25;
const int TILE_HEIGHT = 32;
const int TILE_WIDTH = 32;

template <typename T> class DataSet {
protected:
	std::vector<T> values;
	std::vector<unsigned int> indices;
public:
	void clear()
	{
		values.clear();
		indices.clear();
	}
	void reserve(unsigned int x, unsigned int y)
	{
		values.reserve(x*y);
		indices.reserve(y);
	}
	unsigned int rows()
	{
		return indices.size();
	}
	unsigned int columns(unsigned int row)
	{
		if(row<indices.size()-1) {
			return indices[row+1] - indices[row];
		} else if(row<indices.size()) {
			return indices[row] - indices[row-1];
		}
	}
	
	

	std::vector<T> at(unsigned int y)
	{
		std::vector<T> row;
		if(y<indices.size()-1) {
			row.assign(values.begin()+indices[y],values.begin()+indices[y+1]);
		} else if(y<indices.size()) {
			row.assign(values.begin()+indices[y],values.end());
		}
		return row;
	}
	T& at(unsigned int x, unsigned int y)
	{
		if(y<indices.size()-1) {
			if(x<indices[y+1]-indices[y]) {
				return values[indices[y]+x];
			}
		} else if(y<indices.size()) {
			if(x+indices[y]<values.size()) {
				return values[indices[y]+x];
			}
		}
		return T();
	}
	T& iterate(unsigned int i){
		return values[i];
	}
	unsigned int totalSize(){
		return values.size();
	}
	void push_row(std::vector<T> row)
	{
		indices.push_back(values.size());
		values.insert(values.end(),row.begin(),row.end());
	}
	void push_back(T cell)
	{
		values.push_back(cell);
	}
	void new_row()
	{
		indices.push_back(values.size());
	}
	void pop_back()
	{
		values.pop_back();
	}
	void pop_row()
	{
		values.erase(values.begin()+indices.back(),values.end());
		indices.pop_back();
	}
};


class TileMap
{
private:
	vector <Tiili> map;				//sis‰lt‰‰ kaikki kartan tiilet
	vector <Road> roadmap;
	DataSet<Road> allroads;
	vector <int> typeMap;
	SDL_Texture* tileTexture;		//spritesheet
	//SDL_Rect clips[ TILE_COUNT ];	//pilkotut kuvat
	SDL_Renderer* rndr;

public:
	TileMap(void);
	virtual ~TileMap(void);
	void addTiles();
	void addRoads();
	void drawMap();
	void setTexture(std::string filename, SDL_Renderer* rndr);
	void setRenderer(SDL_Renderer* rndr);
	void setClips();
	void setMap(std::string filename);
	std::vector<Tiili>& getMap();
	void newRoad();
	std::vector<Road>& getRoad(unsigned int i = 0);
};


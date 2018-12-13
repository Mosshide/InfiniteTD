#pragma once
#include "TextureBox.h"
#include "TerrainType.h"
#include "VBORectangle.h"

class Node
{
public:
	Node(int a, int b, TerrainType t);
	~Node();
	void tryNewParent(int a, int b, int pc);
	SDL_Point getPoint();
	SDL_Point getPPoint();

	int x; //node x location
	int y; //node y location
	int px; //parent x location
	int py; //parent y location
	TerrainType terrain;
	bool occupied;
	int c; //path cost
	int checkState;
};

///////

class Navigation
{
public:
	Navigation();
	~Navigation();
	void draw();
	void setNodes(int w, int h);
	std::vector<Vertex> getPath(Vertex a, Vertex b, std::vector<TerrainType> ok);
	std::vector<Vertex> getStartEndPath(std::vector<TerrainType> ok);
	void setTerrain(int x, int y, TerrainType t);
	void setTerrain(SDL_Point p, TerrainType t) { return setTerrain(p.x, p.y, t); }
	TerrainType getTerrain(int x, int y);
	TerrainType getTerrain(SDL_Point p) { return getTerrain(p.x, p.y); }
	void setOccupied(int x, int y, bool o);
	void setOccupied(SDL_Point p, bool o) { return setOccupied(p.x, p.y, o); }
	bool getOccupied(int x, int y);
	bool getOccupied(SDL_Point p) { return getOccupied(p.x, p.y); }
	SDL_Point getClosestTile(GLfloat x, GLfloat y);
	SDL_Point getClosestTile(int x, int y) { return getClosestTile((GLfloat)x, (GLfloat)y); }
	SDL_Point getClosestTile(Vertex v) { return getClosestTile(v.x, v.y); }
	bool checkterrainOK(TerrainType tt, std::vector<TerrainType> ok);
	bool blocksStartEndPath(int x, int y, std::vector<TerrainType> ok);
	void setStartEnd(int s, int e);
	Vertex getStartPoint();
	Vertex getEndPoint();

	SDL_Point goal;

private:
	void resetNodes();
	void checkNode(int x, int y, int px, int py, std::vector<TerrainType> ok, std::vector<Node*> *tnodes);
	std::vector<Vertex> refinePath(std::vector<Vertex> path, Vertex a, Vertex  b, std::vector<TerrainType> ok);
	bool straightPath(Vertex a, Vertex b, std::vector<TerrainType> ok);

	std::vector<Node> _nodes;
	int _density;
	int wTiled;
	int hTiled;
	
	int _startEnd[2];
	std::vector<Vertex> _startEndPath;

	VBORectangle _rect;
};
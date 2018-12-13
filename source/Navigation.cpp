#include "Navigation.h"

Node::Node(int a, int b, TerrainType t)
{
	x = a;
	y = b;
	px = -1;
	py = -1;
	c = INT_MAX;
	terrain = t;
	occupied = false;
	checkState = -1;
}

Node::~Node()
{
}

void Node::tryNewParent(int a, int b, int pc)
{
	if (pc + 1 < c)
	{
		px = a;
		py = b;
		c = pc + 1;
	}
}

SDL_Point Node::getPoint()
{
	SDL_Point v = { x, y };
	return v;
}

SDL_Point Node::getPPoint()
{
	SDL_Point v = { px, py };
	return v;
}

//////

Navigation::Navigation()
{
	_density = 1;

	_startEnd[0] = 0;
	_startEnd[1] = 0;

	_rect.setRGBA(red);
	_rect.setUI(false);
}

Navigation::~Navigation()
{
}

void Navigation::draw()
{
	for (int i = 0; i < wTiled; i++)
	{
		for (int ii = 0; ii < hTiled; ii++)
		{
			_rect.setRect(fRectangle(wTiled * TILE_WIDTH, hTiled * TILE_HEIGHT, 16, 16));
			_rect.draw();
		}
	}
}

void Navigation::setNodes(int w, int h)
{
	wTiled = w;
	hTiled = h;
	_nodes.clear();
	for (int i = 0; i < hTiled; i++)
	{
		for (int ii = 0; ii < wTiled; ii++)
		{
			Node n(ii, i, trnGrass);
			_nodes.push_back(n);
		}
	}

	_startEnd[0] = 0;
	_startEnd[1] = (int)_nodes.size() - 1;

	//setTerrain(_startPnt.x, _startPnt.y, trnStart);
	//setTerrain(_endPnt.x, _endPnt.y, trnEnd);
}

void Navigation::resetNodes()
{
	for (int i = 0; i < hTiled; i++)
	{
		for (int ii = 0; ii < wTiled; ii++)
		{
			_nodes[ii + i * wTiled].px = -1;
			_nodes[ii + i * wTiled].py = -1;
			_nodes[ii + i * wTiled].c = INT_MAX;
			_nodes[ii + i * wTiled].checkState = -1;
		}
	}
}

std::vector<Vertex> Navigation::getPath(Vertex a, Vertex b, std::vector<TerrainType> ok)
{
	resetNodes();

	//go
	std::vector<Vertex> path;
	SDL_Point p = getClosestTile(a);
	SDL_Point q = getClosestTile(b);
	//printf("%d, %d -> %d, %d\n", p.x, p.y, q.x, q.y);

	//make sure end isnt out of bounds
	if (q.x < wTiled && q.x >= 0 && q.y < hTiled && q.y >= 0)
	{
		//make sure start and end points are walkable tiles
		if (checkterrainOK(_nodes[p.x + p.y * wTiled].terrain, ok) && checkterrainOK(_nodes[q.x + q.y * wTiled].terrain, ok))
		{
			//if not changing tile
			if (p.x == q.x && p.y == q.y)
			{
				Vertex tpoint = b;
				path.push_back(tpoint);
				printf("Start and end are same tile.\n");
			}
			else
			{
				SDL_Point t = { p.x, p.y };

				//init first node
				_nodes[p.x + p.y * wTiled].c = 0;
				std::vector<Node*> tnodes;
				tnodes.push_back(&_nodes[p.x + p.y * wTiled]);

				//while there are more nodes to check
				while (!tnodes.empty())
				{
					int currTNode = 0;

					t.x = tnodes[currTNode]->x;
					t.y = tnodes[currTNode]->y;
					//find node closest to end
					for (int i = 1; i < (int)tnodes.size(); i++)
					{
						if (distance(t, q) > distance(tnodes[i]->getPoint(), q))
						{
							currTNode = i;
							t.x = tnodes[i]->x;
							t.y = tnodes[i]->y;
						}
					}

					_nodes[t.x + t.y * wTiled].checkState = 1;

					if (t.x - 1 > -1) checkNode(t.x - 1, t.y, t.x, t.y, ok, &tnodes);
					if (t.x + 1 < wTiled) checkNode(t.x + 1, t.y, t.x, t.y, ok, &tnodes);
					if (t.y - 1 > -1) checkNode(t.x, t.y - 1, t.x, t.y, ok, &tnodes);
					if (t.y + 1 < hTiled) checkNode(t.x, t.y + 1, t.x, t.y, ok, &tnodes);

					//if the current node is the end
					if (t.x == q.x && t.y == q.y)
					{
						//until there is no more parent node
						while (_nodes[t.x + t.y * wTiled].px != -1 && _nodes[t.x + t.y * wTiled].py != -1)
						{
							//add point to the path
							Vertex tpoint = { (GLfloat)t.x * (TILE_WIDTH / _density) + (TILE_WIDTH / (_density * 2)),
												(GLfloat)t.y * (TILE_HEIGHT / _density) + (TILE_HEIGHT / (_density * 2)) };
							path.push_back(tpoint);
							int ttx = _nodes[t.x + t.y * wTiled].px;
							int tty = _nodes[t.x + t.y * wTiled].py;
							t.x = ttx;
							t.y = tty;
						}
						//add final points to the path
						Vertex tpoint = { (GLfloat)t.x * (TILE_WIDTH / _density) + (TILE_WIDTH / (_density * 2)),
											(GLfloat)t.y * (TILE_HEIGHT / _density) + (TILE_HEIGHT / (_density * 2)) };
						path.push_back(tpoint);
						//path = refinePath(path, a, b, ok);
						break;
					}
					else tnodes.erase(tnodes.begin() + currTNode);
				}
			}
		}
		else printf("Start and end not pathable.\n");
	}
	else printf("Out of bounds.\n");

	/*for (int i = 0; i < (int)path.size(); i++)
	{
		printf("%d, %d\n", path[i].x, path[i].y);
	}*/
	//printf("%d\n", SDL_GetTicks() - time);
	return path;
}

void Navigation::checkNode(int x, int y, int px, int py, std::vector<TerrainType> ok, std::vector<Node*> *tnodes)
{
	//make sure node is walkable
	if (checkterrainOK(_nodes[x + y * wTiled].terrain, ok))
	{
		//if node hasnt been checked
		if (_nodes[x + y * wTiled].checkState == -1)
		{
			//add to vector of nodes to check the surroundings of
			tnodes->push_back(&_nodes[x + y * wTiled]);
			_nodes[x + y * wTiled].checkState = 0;
		}
		//check if a new parent node is warranted
		_nodes[x + y * wTiled].tryNewParent(px, py, _nodes[px + py * wTiled].c);
	}
}

std::vector<Vertex> Navigation::getStartEndPath(std::vector<TerrainType> ok)
{
	_startEndPath = getPath(getStartPoint(), getEndPoint(), ok);
	//printf("%d\n", (int)_startEndPath.size());
	return _startEndPath;
}

void Navigation::setTerrain(int x, int y, TerrainType t)
{
	if (x < 0 || x >= wTiled || y < 0 || y >= hTiled)
	{
		printf("set terrain out of bounds");
	}
	else
	{
		for (int i = 0; i < _density; i++)
		{
			for (int ii = 0; ii < _density; ii++)
			{
				_nodes[(x * _density) + i + (y * _density + ii) * wTiled].terrain = t;
			}
		}
	}
}

TerrainType Navigation::getTerrain(int x, int y)
{
	if (x < 0 || x >= wTiled || y < 0 || y >= hTiled)
	{
		printf("set terrain out of bounds\n");
		return TERRAIN_TYPE_SIZE;
	}
	else return _nodes[(x * _density) + (y * _density) * wTiled].terrain;
}

void Navigation::setOccupied(int x, int y, bool o)
{
	if (x < 0 || x >= wTiled || y < 0 || y >= hTiled)
	{
		printf("set occupied out of bounds");
	}
	else
	{
		for (int i = 0; i < _density; i++)
		{
			for (int ii = 0; ii < _density; ii++)
			{
				_nodes[(x * _density) + i + (y * _density + ii) * wTiled].occupied = o;
			}
		}
	}
}

bool Navigation::getOccupied(int x, int y)
{
	if (x < 0 || x >= wTiled || y < 0 || y >= hTiled)
	{
		printf("set terrain out of bounds\n");
		return true;
	}
	else return _nodes[(x * _density) + (y * _density) * wTiled].occupied;
}

SDL_Point Navigation::getClosestTile(GLfloat x, GLfloat y)
{
	SDL_Point p = { (int)x / (TILE_WIDTH / _density) , (int)y / (TILE_HEIGHT / _density) };

	if (p.x < 0) p.x = 0;
	else if (p.x >= wTiled) p.x = wTiled - 1;
	if (p.y < 0) p.y = 0;
	else if (p.y >= hTiled) p.y = hTiled - 1;

	return p;
}

bool Navigation::checkterrainOK(TerrainType tt, std::vector<TerrainType> ok)
{
	for (int i = 0; i < (int)ok.size(); i++)
	{
		if (tt == ok[i]) return true;
	}

	return false;
}

bool Navigation::blocksStartEndPath(int x, int y, std::vector<TerrainType> ok)
{
	TerrainType tt = getTerrain(x, y);

	//setTerrain(x, y, trnOccupied);

	getStartEndPath(ok);

	setTerrain(x, y, tt);

	if (_startEndPath.size() > 0) return false;
	return true;
}

void Navigation::setStartEnd(int s, int e)
{
	_startEnd[0] = s;
	_startEnd[1] = e;
}

Vertex Navigation::getStartPoint()
{
	Vertex p;
	if (wTiled > 0)
	{
		p = { (GLfloat)(_startEnd[0] % wTiled) * (TILE_WIDTH / _density),
			(GLfloat)(_startEnd[0] / wTiled) * (TILE_HEIGHT / _density) };
	}
	else
	{
		p = { 0, 0 };
	}
	return p;
}

Vertex Navigation::getEndPoint()
{
	Vertex p;
	if (wTiled > 0)
	{
		p = { (GLfloat)(_startEnd[1] % wTiled) * (TILE_WIDTH / _density),
			(GLfloat)(_startEnd[1] / wTiled) * (TILE_HEIGHT / _density) };
	}
	else
	{
		p = { 0, 0 };
	}
	return p;
}

std::vector<Vertex> Navigation::refinePath(std::vector<Vertex> path, Vertex a, Vertex  b, std::vector<TerrainType> ok)
{
	if ((int)path.size() > 0)
	{
		path[0] = a;
		/*printf("path[%d] : %d, %d\n", 0, path[0].x, path[0].y);
		for (int i = 1; i < (int)path.size(); i++)
		{
			if (path[i - 1].x > path[i].x + (3 * TILE_WIDTH / 4))
			{
				path[i].x = path[i].x + (3 * TILE_WIDTH / 4);
			}
			else if (path[i - 1].x > path[i].x + (TILE_WIDTH / 4))
			{
				path[i].x = path[i - 1].x;
			}
			
			if (path[i - 1].y > path[i].y + TILE_HEIGHT)
			{
				path[i].y = path[i].y + TILE_HEIGHT;
			}
			else if (path[i - 1].y > path[i].y)
			{
				path[i].y = path[i - 1].y;
			}
			printf("path[%d] : %d, %d\n", i, path[i].x, path[i].y);
		}*/

		std::vector<Vertex> shortcut;
		shortcut.push_back(path[0]);
		for (int i = 1; i < (int)path.size(); i++)
		{
			if (i + 1 < (int)path.size())
			{
				if (!straightPath(shortcut.back(), path[i + 1], ok))
				{
					shortcut.push_back(path[i]);
					//printf("col\n");
				}
			}
			else
			{
				shortcut.push_back(path[i]);
			}
		}
		if ((int)shortcut.size() > 1) shortcut.pop_back();

		/*for (int i = 0; i < (int)shortcut.size(); i++)
		{
			printf("shortcut[%d] : %d, %d\n", i, shortcut[i].x, shortcut[i].y);
		}*/
		//printf("end\n");

		return shortcut;
	}

	else return path;
}

bool Navigation::straightPath(Vertex a, Vertex b, std::vector<TerrainType> ok)
{
	std::vector<SDL_Point> checkTiles;
	SDL_Point p = getClosestTile(a);
	SDL_Point q = getClosestTile(b);
	if (a.x == b.x && a.y == b.y) return true;
	else if (a.x == b.x)
	{
		if (q.y > p.y)
		{
			for (int i = p.y; i < q.y; i++)
			{
				SDL_Point a = { p.x, i };
				checkTiles.push_back(a);
			}
		}
		else
		{
			for (int i = q.y; i < p.y; i++)
			{
				SDL_Point a = { p.x, i };
				checkTiles.push_back(a);
			}
		}
	}
	else if (a.y == b.y)
	{
		if (q.x > p.x)
		{
			for (int i = p.x; i < q.x; i++)
			{
				SDL_Point a = { i, p.y };
				checkTiles.push_back(a);
			}
		}
		else
		{
			for (int i = q.x; i < p.x; i++)
			{
				SDL_Point a = { i, p.y };
				checkTiles.push_back(a);
			}
		}
	}
	else
	{
		int dx = abs(q.x - p.x);
		int dy = abs(q.y - p.y);
		int tx = p.x;
		int ty = p.y;
		int n = 1 + dx + dy;
		int x_inc = (q.x > p.x) ? 1 : -1;
		int y_inc = (q.y > p.y) ? 1 : -1;
		int error = dx - dy;
		dx *= 2;
		dy *= 2;

		for (int i = n; i > 0; --i)
		{
			SDL_Point a = { tx, ty };
			checkTiles.push_back(a);

			if (error > 0)
			{
				tx += x_inc;
				error -= dy;
			}
			else
			{
				ty += y_inc;
				error += dx;
			}
		}
	}

	for (int i = 0; i < (int)checkTiles.size(); i++)
	{
		if (!checkterrainOK(_nodes[checkTiles[i].x + checkTiles[i].y * wTiled].terrain, ok))
		{
			return false;
		}
	}
	return true;
}
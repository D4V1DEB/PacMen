#include "ghostmoving.h"
#include <iostream>
#include<vector>
#include "SFML/Graphics.hpp"
#include<queue>
using namespace sf;
using namespace std;


ghostmoving::ghostmoving(int arr[][50] , int a , int b , int ghostspeed) {
	speed = ghostspeed;
	width = a;
	height = b;
	go[0] = 1;	
	go[1] = -1;	
	go[2] = width;	 
	go[3] = -width;  
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (arr[i][j] == 1)
				continue;
			int from = i * width + j;
			for (int k = 0; k < 4; k++)  {
				int to = from + go[k];

				if (to < 0 || to/width >= height || ( to % width==0 && k==1) || (to%width==width-1 &&k==0) 
					                                                         || arr[to/width][to%width]==1 )
					continue;

				edge[from].push_back(to);
			}
		}
	}
}

void ghostmoving::intialize() {
	for (int i = 0; i < 2888; i++) {
		path[i] = 0;
		dis[i] = 1e9;
	}
}


Sprite ghostmoving::findpath(Sprite player, Sprite ghost) {
	int y = player.getPosition().x / 32;
	int x = player.getPosition().y / 32;
	int from = x * width + y;

	y = ghost.getPosition().x / 32; 
	x = ghost.getPosition().y / 32;
	int to = x * width + y;

	if (path[to] == 0) {
		intialize();
		int node = from;
		dis[node] = 0;
		queue<int> q;
		q.push(node);
		while (!q.empty()) {
			node = q.front();
			q.pop();
			for (int i = 0; i < edge[node].size(); i++) {
				int child = edge[node][i];
				if (dis[child] > dis[node] + 1) {
					path[child] = node;
					dis[child] = dis[node] + 1;
					q.push(child);
				}
			}
		}
	}
	int aa = ghost.getPosition().x, bb = ghost.getPosition().y;

	if (player.getPosition().x == ghost.getPosition().x && player.getPosition().y== ghost.getPosition().y
		&& (aa / 32 * 32 == aa) && (bb / 32 * 32 == bb))
		xx = 0, yy = 0;
	else {

		if (path[to] != 0 && (aa / 32 * 32 == aa) && (bb / 32 * 32 == bb)) {
			
			int x = path[to];
			int d = x - to;

			if (d == 1)
				xx = speed, yy = 0;
			else if (d == -1)
				xx = -speed, yy = 0;
			else if (d == width)
				xx = 0, yy = speed;
			else
				xx = 0, yy = -speed;
		}
	}
	ghost.setPosition(ghost.getPosition().x + xx, ghost.getPosition().y + yy);

	if (ghost.getPosition().x <= 0)
		ghost.setPosition(896, ghost.getPosition().y);
	if (ghost.getPosition().x >= 896)
		ghost.setPosition(0, ghost.getPosition().y);
	return ghost;
}

#include "Game.h"



Game::Game()
{
}

void Game::draw(int count, vertexBuffer & vb, indexBuffer & ib, vertexAttribute & va)
{
	vb.bind();
	ib.bind();
	va.bind();

	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);

}


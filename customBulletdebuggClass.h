/////////////////////////////////////////////
//customBulletdebuggClass
//Copyright(c) 2019 Luta Vlad
//https://github.com/meemknight/OpenGLEngine
/////////////////////////////////////////////

#pragma once
#include <btBulletCollisionCommon.h>
#include <GL/glew.h>
#include "Shader.h"
#include "vertexBuffer.h"
#include "vertexAttribute.h"
#include "indexBuffer.h"
#include "Camera.h"

class customBulletdebuggClass: public btIDebugDraw
{
	void init();
	int debugMode = btIDebugDraw::DBG_DrawAabb;
public:
	customBulletdebuggClass() { init(); }
	customBulletdebuggClass(ShaderProgram *sp, Camera *camera) :sp(sp), camera(camera) { init(); }

	ShaderProgram *sp;
	vertexBuffer vb;
	vertexAttribute va;
	Camera *camera;

	void	drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override;

	void	drawTriangle(const btVector3& v0, const btVector3& v1, const btVector3& v2, const btVector3& color, btScalar /*alpha*/) override;
	
	void	drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) override;
	
	void	reportErrorWarning(const char* warningString) override;
	
	void	draw3dText(const btVector3& location, const char* textString) override;
	
	void	setDebugMode(int debugMode) override;
	
	int		getDebugMode() const override;
};


#include "custumBulletdebuggClass.h"
#include "tools.h"

void custumBulletdebuggClass::init()
{
	
	vb.createData(0, sizeof(float) * 18);
	va.pushAttribute(Attribute(3, sizeof(float), GL_FLOAT));
	va.pushAttribute(Attribute(3, sizeof(float), GL_FLOAT));
}

void custumBulletdebuggClass::drawLine(const btVector3 & from, const btVector3 & to, const btVector3 & color)
{
	float data[12];
	data[0] = from.getX();
	data[1] = from.getY();
	data[2] = from.getZ();
	data[3] = color.getX();
	data[4] = color.getY();
	data[5] = color.getZ();

	data[6] = to.getX();
	data[7] = to.getY();
	data[8] = to.getZ();
	data[9] = color.getX();
	data[10] = color.getY();
	data[11] = color.getZ();

	vb.subData(data, 0, sizeof(data));
	va.bind();
	sp->bind();
	auto m = camera->getProjectionViewMatrix();
	glUniformMatrix4fv(sp->getUniformLocation("u_full"), 1, 0, &m[0][0]);
	
	glDrawArrays(GL_LINES, 0, 2);
}

void custumBulletdebuggClass::drawTriangle(const btVector3 & v0, const btVector3 & v1, const btVector3 & v2, const btVector3 & color, btScalar)
{
	float data[18];
	data[0] = v0.getX();
	data[1] = v0.getY();
	data[2] = v0.getZ();
	data[3] = color.getX();
	data[4] = color.getY();
	data[5] = color.getZ();

	data[6] = v1.getX();
	data[7] = v1.getY();
	data[8] = v1.getZ();
	data[9] = color.getX();
	data[10] = color.getY();
	data[11] = color.getZ();

	data[12] = v2.getX();
	data[13] = v2.getY();
	data[14] = v2.getZ();
	data[15] = color.getX();
	data[16] = color.getY();
	data[17] = color.getZ();

	vb.subData(data, 0, sizeof(data));
	va.bind();
	sp->bind();
	auto m = camera->getProjectionViewMatrix();
	glUniformMatrix4fv(sp->getUniformLocation("u_full"), 1, 0, &m[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 3);
}


void custumBulletdebuggClass::drawContactPoint(const btVector3 & PointOnB, const btVector3 & normalOnB, btScalar distance, int lifeTime, const btVector3 & color)
{
}

void custumBulletdebuggClass::reportErrorWarning(const char * warningString)
{
	elog(warningString);
}

void custumBulletdebuggClass::draw3dText(const btVector3 & location, const char * textString)
{
}

void custumBulletdebuggClass::setDebugMode(int debugMode)
{
	this->debugMode = debugMode;
}

int custumBulletdebuggClass::getDebugMode() const
{
	return debugMode;
}

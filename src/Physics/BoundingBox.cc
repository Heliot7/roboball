#include "BoundingBox.hh"

BoundingBox::BoundingBox(const vec3& minimum, const vec3& maximum) : min(minimum), max(maximum) { }

void BoundingBox::update(const vec3& p)
{
	if (p.x < min.x) min.x=p.x;
	if (p.y < min.y) min.y=p.y;
	if (p.z < min.z) min.z=p.z;
	if (p.x > max.x) max.x=p.x;
	if (p.y > max.y) max.y=p.y;
	if (p.z > max.z) max.z=p.z;
}

float BoundingBox::maxDist()
{
	float dist = max.x - min.x;
	if (dist < (max.y - min.y)) dist = max.y - min.y;
	else if (dist < (max.z - min.z)) dist = max.z - min.z;
	return dist;
}

vec3 BoundingBox::baseCentre()
{
        vec3 base;
	base.x = min.x + ( (max.x - min.x) / 2 );
	base.y = min.y;
	base.z = min.z + ( (max.z - min.z) / 2 );
	return base;
}

vec3 BoundingBox::centreBoxLocal()
{	
        vec3 centre;

	centre.x = (max.x - min.x) / 2;
	centre.y = (max.y - min.y) / 2;
	centre.z = (max.z - min.z) / 2;
	
	return centre;
}

vec3 BoundingBox::centreBox()
{	
        vec3 centre;

	centre.x = min.x + (max.x - min.x) / 2;
	centre.y = min.y + (max.y - min.y) / 2;
	centre.z = min.z + (max.z - min.z) / 2;
	
	return centre;
}

void BoundingBox::drawBB()
{
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin (GL_LINE_LOOP); 
	glVertex3f(max.x,max.y,min.z); // 0
	glVertex3f(min.x,max.y,min.z); // 1
	glVertex3f(min.x,min.y,min.z); // 2
	glVertex3f(max.x,min.y,min.z); // 3
	glEnd();

	glBegin (GL_LINE_LOOP); 
	glVertex3f(max.x,min.y,max.z); // 4
	glVertex3f(max.x,max.y,max.z); // 5
	glVertex3f(min.x,max.y,max.z); // 6
	glVertex3f(min.x,min.y,max.z); // 7
	glEnd();

	glBegin (GL_LINE_LOOP); 
	glVertex3f(max.x,max.y,min.z); // 0
	glVertex3f(max.x,max.y,max.z); // 5
	glVertex3f(min.x,max.y,max.z); // 6
	glVertex3f(min.x,max.y,min.z); // 1
	glEnd();

	glBegin (GL_LINE_LOOP); 
	glVertex3f(max.x,min.y,max.z); // 4
	glVertex3f(min.x,min.y,max.z); // 7
	glVertex3f(min.x,min.y,min.z); // 2 
	glVertex3f(max.x,min.y,min.z); // 3

	glEnd();
}

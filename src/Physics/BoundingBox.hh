#ifndef BOUNDINGBOX_HH
#define BOUNDINGBOX_HH

#include <glm/glm.hpp>
#include <stdlib.h>
#include <GL/gl.h>
#include <math.h>
#include <iostream>
#include <vector>

#ifdef min 
#undef min
#endif

#ifdef max 
#undef max
#endif

using namespace glm;
using namespace std;

class BoundingBox
{
public:

	// Constructor
        BoundingBox(const vec3& minimum=vec3(), const vec3& maximum=vec3());

	// Update - Expands the bounding box to include "p"
        void update(const vec3& p);
	
        // Check if a point is cointained within the bounding box
        bool contains(vec3 p)
        {
            return (p.x >= min.x && p.y >= min.y && p.z >= min.z &&
                    p.x <= max.x && p.y <= max.y && p.z <= max.z );
        }

        // Check what plane (returns its normal) intersects the ray from the center
        static vec3 rayFromCenterNormal(vec3 ray)
        {
            // Normalize ray
            ray = normalize(ray);
            if(ray.x >= 0.5f)
                ray.x = 1.0f;
            else if(ray.x <= -0.5f)
                ray.x = -1.0f;
            else
                ray.x = 0.0f;

            if(ray.y >= 0.5f)
                ray.y = 1.0f;
            else if(ray.y <= -0.5f)
                ray.y = -1.0f;
            else
                ray.y = 0.0f;

            if(ray.z >= 0.5f)
                ray.z = 1.0f;
            else if(ray.z <= -0.5f)
                ray.z = -1.0f;
            else
                ray.z = 0.0f;
            return ray;
        }

        static vec3 closestVertexToPlane(vec3 normal, vec3 min, vec3 max)
        {
            float value = dot(normal,min);
            //cout << "dot " << dot(normal,min) << endl;
            vec3 res = min;
            //cout << "dot " << dot(normal,max) << endl;
            if(dot(normal,max) < value)
            {
                value = dot(normal,max);
                res = max;
            }
            //cout << "dot " << dot(normal,vec3((min.x,min.y,max.z))) << endl;
            if(dot(normal,vec3(min.x,min.y,max.z)) < value)
            {
                value = dot(normal,vec3(min.x,min.y,max.z));
                res = vec3(min.x,min.y,max.z);
            }
            //cout << "dot " << dot(normal,vec3((max.x,min.y,min.z))) << endl;
            if(dot(normal,vec3(max.x,min.y,min.z)) < value)
            {
                value = dot(normal,vec3(max.x,min.y,min.z));
                res = vec3(max.x,min.y,min.z);
            }
            //cout << "dot " << dot(normal,vec3(min.x,max.y,min.z)) << endl;
            if(dot(normal,vec3(min.x,max.y,min.z)) < value)
            {
                value = dot(normal,vec3(min.x,max.y,min.z));
                res = vec3(min.x,max.y,min.z);
            }
            //cout << "dot " << dot(normal,vec3(max.x,min.y,max.z)) << endl;
            if(dot(normal,vec3(max.x,min.y,max.z)) < value)
            {
                value = dot(normal,vec3(max.x,min.y,max.z));
                res = vec3(max.x,min.y,max.z);
            }
            //cout << "dot " << dot(normal,vec3(max.x,max.y,min.z)) << endl;
            if(dot(normal,vec3(max.x,max.y,min.z)) < value)
            {
                value = dot(normal,vec3(max.x,max.y,min.z));
                res = vec3(max.x,max.y,min.z);
            }
            //cout << "dot " << dot(normal,vec3(min.x,max.y,max.z)) << endl;
            if(dot(normal,vec3(min.x,max.y,max.z)) < value)
            {
                value = dot(normal,vec3(min.x,max.y,max.z));
                res = vec3(min.x,max.y,max.z);
            }
            return res;
        }

        vec3 closestVertexToPlane(vec3 normal)
        {
            float value = dot(normal,min);
            vec3 res = min;
            if(dot(normal,max) < value)
            {
                value = dot(normal,max);
                res = max;
            }
            if(dot(normal,vec3(min.x,min.y,max.z)) < value)
            {
                value = dot(normal,vec3(min.x,min.y,max.z));
                res = vec3(min.x,min.y,max.z);
            }
            if(dot(normal,vec3(max.x,min.y,min.z)) < value)
            {
                value = dot(normal,vec3(max.x,min.y,min.z));
                res = vec3(max.x,min.y,min.z);
            }
            if(dot(normal,vec3(min.x,max.y,min.z)) < value)
            {
                value = dot(normal,vec3(min.x,max.y,min.z));
                res = vec3(min.x,max.y,min.z);
            }
            if(dot(normal,vec3(max.x,min.y,max.z)) < value)
            {
                value = dot(normal,vec3(max.x,min.y,max.z));
                res = vec3(max.x,min.y,max.z);
            }
            if(dot(normal,vec3(max.x,max.y,min.z)) < value)
            {
                value = dot(normal,vec3(max.x,max.y,min.z));
                res = vec3(max.x,max.y,min.z);
            }
            if(dot(normal,vec3(min.x,max.y,max.z)) < value)
            {
                value = dot(normal,vec3(min.x,max.y,max.z));
                res = vec3(min.x,max.y,max.z);
            }
            return res;
        }

        vector<vec3> getAllVertices()
        {
            vector<vec3> v;
            v.push_back(min);
            v.push_back(max);
            v.push_back(vec3(min.x,min.y,max.z));
            v.push_back(vec3(max.x,min.y,min.z));
            v.push_back(vec3(min.x,max.y,min.z));
            v.push_back(vec3(max.x,min.y,max.z));
            v.push_back(vec3(max.x,max.y,min.z));
            v.push_back(vec3(min.x,max.y,max.z));
            return v;
        }

	// Borders of the Box
        vec3 min, max;

	// Returns the distance between the 2 most separated points of the BB
	float maxDist();
	// Returns the distance in XYZ-axis from max to min points
        float distX() { return abs(max.x - min.x); }
        float distY() { return abs(max.y - min.y); }
        float distZ() { return abs(max.z - min.z); }
        vec3 dist() { return vec3(distX(), distY(), distZ()); }
        float radius() { return maxDist()/2.0; }
	// Bounding Box center of the base
        vec3 baseCentre();
	// Center of Bounding Box (min point is 0,0,0)
        vec3 centreBoxLocal();
	// Center of Bounding Box
        vec3 centreBox();
	// Draws the Bounding Box with OpenGL commands
	void drawBB();
};

#endif

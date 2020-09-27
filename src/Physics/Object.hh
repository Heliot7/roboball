#ifndef OBJECT_HH
#define OBJECT_HH

#include <vector>
#include <QString> 
#include <QDir>

#include "BoundingBox.hh"
#include "Material.hh"

using namespace std;

struct Vertex
{
    Vertex(vec3 _coord) { coord = _coord; }
    vec3 coord;
    vec3 normal;
    vector<int> faces;
};

struct Face
{
    Face() {}
    Face(int i1, int i2, int i3, int i4 = -1)
    {
        vertices.push_back(i1);
        vertices.push_back(i2);
        vertices.push_back(i3);
        if (i4!=-1)
            vertices.push_back(i4);
    }

    // material ID (index)
    int material;
    // Vector with indexes of vertexs of the face
    vector<int> vertices;
    // Vector with indexes of texture coordenates of the face
    vector<int> texCoords;
    // Normal per face
    vec3 normal;
};

struct BoxTree
{
    BoxTree() { isObject = false; isEnd = false;}
    BoxTree(vec3 min, vec3 max, BoxTree* parentTree = NULL) { box.min = min; box.max = max; isObject = false; isEnd = false; parent = parentTree; }
    BoundingBox box;
    BoxTree* topLeftNear;
    BoxTree* topLeftFar;
    BoxTree* topRightNear;
    BoxTree* topRightFar;
    BoxTree* bottomLeftNear;
    BoxTree* bottomLeftFar;
    BoxTree* bottomRightNear;
    BoxTree* bottomRightFar;
    BoxTree* parent;
    bool isObject;
    bool isEnd;
    vec3 point;
    vec3 normal;
};


// Object - allws to read .obj files
class Object
{
public:
	Object();

        Object(char* path);

	static void setModel(char* path, Object* model)
	{
                QString pathTestObj = QDir::currentPath().append("/Geometry");
                pathTestObj.append(path);
                // if(getenv("windir") != NULL)
                //      pathTestObj.replace("/", "\\");
		model->readObj(pathTestObj.toAscii().data());
		model->updateBoundingBox();
                model->calculateNormalPerVertex();
                model->updateCollisionTree(model, 0, model->getCollisionTree(), true);
	}

	// Reads the model from and OBJ file
	void readObj(const char* filename);

	// Bounding Box is calculated
	void updateBoundingBox();
        // Hierarchical collision detection is done
        void updateCollisionTree(Object* obj, int depth = 0, BoxTree* bbTree = NULL, bool gather = false);
	// Getter of Bounding Box
        BoundingBox boundingBox() const;

	// Getter of texture Id
	GLuint* getTextureId() { return &textureId; }
	// Setter of texture Id
	void setTextureId(GLuint newTextureId) { textureId = newTextureId; }

	// Getter materials
	MaterialLib* getMatLib() { return &matlib; }

	// Calculate all normals per face from scratch
	void calculateNormalPerFace();

	// Calculate all normals per vertex from scratch
	void calculateNormalPerVertex();

	// Scale factor getters and setters
	float getScale() { return scaleFactor; }
	void setScaleFactor(float scale) { scaleFactor = scale; }
	void updateScaleFactor(float scale) { scaleFactor += scale; }

private:
	void make_face ( char **words, int nwords, int material );


public:
	// Vector with all object vertices
	vector<Vertex>	vertices;
	// Vector with all object faces
	vector<Face>	faces;
	// Vector with all texture coordinates
	vector<vec3>	texCoords;
        // Object Convex Hull BB (set of points)
        vector<int>    convexHull;
        // Getter collision tree
        BoxTree* getCollisionTree() { return collisionTree; }
        vector<vec3> getValuesTree() { return valuesTree; }
private:
        BoundingBox _boundingBox;
        BoxTree* collisionTree;
        vector<vec3> valuesTree;
        // Depth of tree (bigger number more precision but slower)
        int _depth;
	MaterialLib matlib;
	GLuint textureId;
	float scaleFactor;
};


#endif


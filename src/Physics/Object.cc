#include <string>
#include <stdio.h>
#include <iostream>

#include "Object.hh"

using namespace std;

/*
	OBJ File Reader

	Contains fragments of the code from obj_2_ply.c (C) Greg Turk

	-----------------------------------------------------------------------
	Copyright (c) 1998 Georgia Institute of Technology.  All rights reserved.   

	Permission to use, copy, modify and distribute this software and its   
	documentation for any purpose is hereby granted without fee, provided   
	that the above copyright notice and this permission notice appear in   
	all copies of this software and that you do not sell the software.   
*/

Object::Object()
{
    scaleFactor = 1.0;
}

Object::Object(char* path)
{
    scaleFactor = 1.0;
    _depth = 2;
    Object::setModel(path, this);
}

BoundingBox Object::boundingBox() const
{
    return _boundingBox;
}

void Object::updateBoundingBox()
{
    unsigned i;
    // 1st vertex assigned as min and max point
    _boundingBox = BoundingBox(vertices[0].coord,vertices[0].coord);

    // Through all point we calculate the bounding box
    for(i = 1 ; i < vertices.size(); i++)
            _boundingBox.update(vertices[i].coord);
}

void Object::updateCollisionTree(Object* obj, int depth, BoxTree* bbTree, bool gather)
{
    // Starting point
    if(depth == 0)
    {
        collisionTree = new BoxTree(_boundingBox.min,_boundingBox.max);
        collisionTree->isObject = true;
        bbTree = collisionTree;
    }

    vec3 sumCoord;
    vec3 sumNorm;
    vec3 farAwayV;
    float dist = 0.0f;
    int numV = 0;
    for(int i = 0; i < vertices.size(); ++i)
    {
        Vertex v = vertices.at(i);
        if(bbTree->box.contains(v.coord))
        {
            bbTree->isObject = true;
            vec3 vAux = bbTree->box.centreBox()-v.coord;
            if(sqrt(vAux.x*vAux.x+vAux.y*vAux.y+vAux.z*vAux.z) > dist)
            {
                farAwayV = v.coord;
                dist = sqrt(vAux.x*vAux.x+vAux.y*vAux.y+vAux.z*vAux.z);
            }
            sumCoord = sumCoord + v.coord;
            sumNorm = sumNorm + v.normal;
            numV++;
        }
    }

    // Base case
    if(depth == _depth)
    {
        bbTree->isEnd = true;
        if(bbTree->isObject)
        {
            bbTree->point = sumCoord / (float)numV;
            bbTree->normal = sumNorm / (float)numV;
            valuesTree.push_back(farAwayV);
        }
    }
    // Go further - recursion
    else
    {
        if(bbTree->isObject)
        {
            bbTree->point = sumCoord / (float)numV;
            bbTree->normal = sumNorm / (float)numV;
            vec3 min = bbTree->box.min;
            vec3 max = bbTree->box.max;
            vec3 mid = min + (max - min)/2.0f;

            bbTree->topLeftNear = new BoxTree(vec3(min.x,mid.y,min.z), vec3(mid.x,max.y,mid.z), bbTree);
            obj->updateCollisionTree(this, depth+1, bbTree->topLeftNear);
            bbTree->topLeftFar = new BoxTree(vec3(min.x,mid.y,mid.z), vec3(mid.x,max.y,max.z), bbTree);
            obj->updateCollisionTree(this, depth+1, bbTree->topLeftFar);
            bbTree->topRightNear = new BoxTree(vec3(mid.x,mid.y,min.z), vec3(max.x,max.y,mid.z), bbTree);
            obj->updateCollisionTree(this, depth+1, bbTree->topRightNear);
            bbTree->topRightFar = new BoxTree(vec3(mid.x,mid.y,mid.z), vec3(max.x,max.y,max.z), bbTree);
            obj->updateCollisionTree(this, depth+1, bbTree->topRightFar);
            bbTree->bottomLeftNear = new BoxTree(vec3(min.x,min.y,min.z), vec3(mid.x,mid.y,mid.z), bbTree);
            obj->updateCollisionTree(this, depth+1, bbTree->bottomLeftNear);
            bbTree->bottomLeftFar = new BoxTree(vec3(min.x,min.y,mid.z), vec3(mid.x,mid.y,max.z), bbTree);
            obj->updateCollisionTree(this, depth+1, bbTree->bottomLeftFar);
            bbTree->bottomRightNear = new BoxTree(vec3(mid.x,min.y,min.z), vec3(max.x,mid.y,mid.z), bbTree);
            obj->updateCollisionTree(this, depth+1, bbTree->bottomRightNear);
            bbTree->bottomRightFar = new BoxTree(vec3(mid.x,min.y,mid.z), vec3(max.x,mid.y,max.z), bbTree);
            obj->updateCollisionTree(this, depth+1, bbTree->bottomRightFar);
        }
        else
        {
            bbTree->isEnd = true;
            vec3 dTree = bbTree->box.centreBox() - boundingBox().centreBox();
            vec3 dParent = bbTree->parent->point - boundingBox().centreBox();
            if ( dTree.x*dTree.x + dTree.y*dTree.y + dTree.z*dTree.z <= dParent.x*dParent.x + dParent.y*dParent.y + dParent.z*dParent.z)
            {
                bbTree->isObject = true;
                bbTree->normal = bbTree->parent->normal;
                bbTree->point = bbTree->box.centreBox();
            }
        }
    }
}

void Object::calculateNormalPerFace()
{
    vec3 v1, v2, v3;
    Face f;
    vec3 auxNormal = vec3();

    for (unsigned int i = 0; i < faces.size(); i++)
    {
        // We get the
        f = faces[i];
        v1 = vertices[f.vertices[0]].coord;
        v2 = vertices[f.vertices[1]].coord;
        v3 = vertices[f.vertices[2]].coord;

        // We calculate both lines of 3 points
        float Px = v2.x - v1.x;
        float Py = v2.y - v1.y;
        float Pz = v2.z - v1.z;
        float Qx = v3.x - v1.x;
        float Qy = v3.y - v1.y;
        float Qz = v3.z - v1.z;

        // We obtain the normal vector and we normalize it
        auxNormal.x = Py * Qz - Pz * Qy;
        auxNormal.y = Pz * Qx - Px * Qz;
        auxNormal.z = Px * Qy - Py * Qx;
        normalize(auxNormal);

        faces[i].normal = auxNormal;
    }
}

void Object::calculateNormalPerVertex()
{
    vec3 auxNormal = vec3();
    calculateNormalPerFace();

    for(unsigned i = 0; i < vertices.size(); ++i)
    {
        for(unsigned j = 0; j < vertices[i].faces.size(); ++j)
                auxNormal += faces[vertices[i].faces[j]].normal;
        auxNormal /= vertices[i].faces.size();
        vertices[i].normal = auxNormal;
    }
}

// For file reading
static char **words;
static int max_words = 0;
static int num_words = 0;
#define BIG_STRING 4096
static char str[BIG_STRING];
static char str_orig[BIG_STRING];

void get_indices ( char *word, int *vindex, int *tindex, int *nindex )

/******************************************************************************

GET_INDICES breaks up a word that may have slash-separated numbers into one or more
numbers.

Entry:
word - word to break up

Exit:
vindex - first number (vertex index)
tindex - second number (texture index)
nindex - third number (normal vector index)
******************************************************************************/
{
	char *null = " ";
	char *ptr;
	char *tp;
	char *np;

	/* by default, the texture and normal pointers are set to the null string */

	tp = null;
	np = null;

	/* replace slashes with null characters and cause tp and np to point */
	/* to character immediately following the first or second slash */

	for (ptr = word; *ptr != '\0'; ptr++) {

		if (*ptr == '/') {

			if (tp == null)
				tp = ptr + 1;
			else
				np = ptr + 1;

			*ptr = '\0';
		}
	}

	*vindex = atoi (word);
	*tindex = atoi (tp);
	*nindex = atoi (np);
}

void Object::make_face ( char **words, int nwords, int currentMaterial )
{
	Face face;
	for (int i = 0; i < nwords; i++) 
	{
		int vindex;
		int nindex;
		int tindex;

		if(strlen(words[i]) <= 1)
			break;
		get_indices (words[i], &vindex, &tindex, &nindex);

#if 0
		printf ("vtn: %d %d %d\n", vindex, tindex, nindex);
#endif

		/* store the vertex index */

		if (vindex > 0)       /* indices are from one, not zero */
		{
			face.vertices.push_back(vindex - 1);
			vertices[vindex - 1].faces.push_back(faces.size());
		}
		else if (vindex < 0)  /* negative indices mean count backwards */
		{
			face.vertices.push_back(vertices.size() + vindex);
			vertices[vertices.size() + vindex].faces.push_back(faces.size());
		}
		else 
		{
			fprintf (stderr, "Zero indices not allowed: '%s'\n", str_orig);
			exit (-1);
		}

		if (tindex > 0)
			face.texCoords.push_back(tindex - 1);
		else if (tindex < 0)
			face.texCoords.push_back(texCoords.size() + tindex);
		else
		{
			fprintf (stderr, "Zero indices not allowed: '%s'\n", str_orig);
			exit (-1);
		}
	}
	face.material = currentMaterial;

	faces.push_back(face);
	
}

char *fetch_line ( FILE *fp )
{
	//int i,j;
	char *ptr;
	char *ptr2;
	char *result;
	//char *comment_ptr;

	/* read in a line */
	result = fgets (str, BIG_STRING, fp);

	/* return NULL if we're at the end-of-file */
	if (result == NULL)
		return ((char *) -1);

	/* convert line-feed and tabs into spaces */
	/* (this guarentees that there will be a space before the */
	/*  null character at the end of the string) */

	str[BIG_STRING-2] = ' ';
	str[BIG_STRING-1] = '\0';

	for (ptr = str; *ptr != '\0'; ptr++) {
		if (*ptr == '\t') {
			*ptr = ' ';
		}
		else if (*ptr == '\n') {
			*ptr = ' ';
			break;
		}
	}

	/* copy the line */
	for (ptr = str, ptr2 = str_orig; *ptr != '\0'; ptr++, ptr2++)
		*ptr2 = *ptr;
	*ptr2 = '\0';

	/* look to see if this is a comment line (first non-space is '#') */

	for (ptr = str; *ptr != '\0'; ptr++) {
		if (*ptr == '#') {
			ptr++;
			while (*ptr == ' ')
				ptr++;
			return (ptr);
		}
		else if (*ptr != ' ') {
			break;
		}
	}

	/* if we get here, we've got a non-comment line */

	/* strip off trailing comments */

	while (*ptr != '\0') {
		if (*ptr == '#') {
			*ptr++ = ' ';
			*ptr = '\0';
			break;
		}
		ptr++;
	}

	return (NULL);
}

int fetch_words ( void )
{
	char *ptr;

	/* allocate room for words if necessary */
	if (max_words == 0) {
		max_words = 20;
		words = (char **) malloc (sizeof (char *) * max_words);
	}

	/* find the words in the line */

	ptr = str;
	num_words = 0;

	while (*ptr != '\0') {

		/* jump over leading spaces */
		while (*ptr == ' ')
			ptr++;

		/* break if we reach the end */
		if (*ptr == '\0')
			break;

		/* allocate more room for words if necessary */
		if (num_words >= max_words) {
			max_words += 10;
			words = (char **) realloc (words, sizeof (char *) * max_words);
		}

		/* save pointer to beginning of word */
		words[num_words++] = ptr;

		/* jump over non-spaces */
		while (*ptr != ' ')
			ptr++;

		/* place a null character here to mark the end of the word */
		*ptr++ = '\0';
	}

	/* return the number of words */
	return (num_words);
}

string getPath(const string& filename)
{
	int i=filename.length()-1;
	bool found = false;
	while (i>=0 && !found)
	{
		if (filename[i]=='/' || filename[i]=='\\') found=true;
		else --i;
	}
	return filename.substr(0, i+1);
}

// reads all mtl files and add them to "matlib"
void read_mtllib( char **words, int nwords, MaterialLib& matlib, const string& filename )
{
	string path = getPath(filename);
	for (int i = 0; i < nwords; i++) 
	{
		int size = strlen(words[i])-1;
		while (size && (words[i][size]=='\n' || words[i][size]=='\r') ) words[i][size--]=0;
		matlib.readMtl((path+words[i]).c_str());
	}
}

void Object::readObj(const char* filename)
{
	int currentMaterial = -1;  

	FILE *fp = fopen(filename,"rb");
	if (!fp)
	{
		cout << "No puc obrir el fitxer " << filename << endl;
	}

	while (true) 
	{
		char *comment_ptr = fetch_line (fp);

		if (comment_ptr == (char *) -1)  /* end-of-file */
			break;

		/* did we get a comment? */
		if (comment_ptr) {
			//make_comment (comment_ptr);
			continue;
		}

		/* if we get here, the line was not a comment */
		int nwords = fetch_words();

		/* skip empty lines */
		if (nwords == 0)
			continue;

		char *first_word = words[0];

		if (!strcmp (first_word, "v")) 
		{
			if (nwords < 4) 
			{
				fprintf (stderr, "Too few coordinates: '%s'", str_orig);
				exit (-1);
			}
			float x = atof (words[1]);
			float y = atof (words[2]);
			float z = atof (words[3]);

			if (nwords == 5) 
			{
				float w = atof (words[4]);
				x/=w;
				y/=w;
				z/=w;
			}

			//addVertex(Vertex(Point(x,y,z)));
                        vertices.push_back(Vertex(vec3(x,y,z)));
		}
		else if (!strcmp (first_word, "vn")) {
		}
		else if (!strcmp (first_word, "vt")) {
			if (nwords < 3) 
			{
				fprintf (stderr, "Too few coordinates: '%s'", str_orig);
				exit (-1);
			}
			float x = atof (words[1]);
			float y = atof (words[2]);
			float z = 0.0f;
			if(nwords > 3)
				float z = atof (words[3]);
			
                        texCoords.push_back(vec3(x,y,z));
		}
		else if (!strcmp (first_word, "f")) {
			make_face (&words[1], nwords - 1, currentMaterial);
		}
		// added 
		else if (!strcmp (first_word, "mtllib")) {
			read_mtllib (&words[1], nwords-1, matlib, filename);
		}
		else if (!strcmp (first_word, "usemtl")) {
			int size = strlen(words[1])-1;
			while (size && (words[1][size]=='\n' || words[1][size]=='\r') ) words[1][size--]=0;
			currentMaterial = matlib.index(words[1]);
		}
		// fadded
		else {
			//fprintf (stderr, "Do not recognize: '%s'\n", str_orig);
		}

	}
}




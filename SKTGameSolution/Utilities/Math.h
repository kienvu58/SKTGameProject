#pragma once

#define RADIAN_PER_DEGREE (3.1415926535897932384626433832795f / 180.0f);
#define PIXEL_PER_METER 70.0f;
#define SECOND_PER_MINUTE 60;

#include <Box2D/Common/b2Math.h>
#include <GLES2/gl2.h>

//Vector2

class Vector2
{
public:
	//Constructors
	Vector2() : x(0.0f), y(0.0f){}
	Vector2(GLfloat _x, GLfloat _y) : x(_x), y(_y) {}
	Vector2(GLfloat * pArg) : x(pArg[0]), y(pArg[1]) {}
	Vector2(const Vector2 & vector) : x(vector.x), y(vector.y) {}

	//Vector's operations
	GLfloat Length() const;
	Vector2 & Normalize();
	Vector2 operator + (const Vector2 & vector) const;
	Vector2 & operator += (const Vector2 & vector);
	Vector2 operator - () const;
	Vector2 operator - (const Vector2 & vector) const;
	Vector2 & operator -= (const Vector2 & vector);
	Vector2 operator * (GLfloat k) const;
	Vector2 & operator *= (GLfloat k);
	Vector2 operator / (GLfloat k) const;
	Vector2 & operator /= (GLfloat k);
	Vector2 & operator = (const Vector2 & vector);
	Vector2 Modulate(const Vector2 & vector) const;
	GLfloat Dot(const Vector2 & vector) const;

	//access to elements
	GLfloat operator [] (unsigned int idx) const;

	//data members
	GLfloat x;
	GLfloat y;
};

//Vector3

class Vector3
{
public:
	//Constructors
	Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
	Vector3(GLfloat _x, GLfloat _y, GLfloat _z) : x(_x), y(_y), z(_z) {}
	Vector3(GLfloat * pArg) : x(pArg[0]), y(pArg[1]), z(pArg[2]) {}
	Vector3(const Vector3 & vector) : x(vector.x), y(vector.y), z(vector.z) {}
	
	//Vector's operations
	GLfloat Length() const;
	Vector3 & Normalize();
	Vector3 operator + (const Vector3 & vector) const;
	Vector3 & operator += (const Vector3 & vector);
	Vector3 operator - () const;
	Vector3 operator - (const Vector3 & vector) const;
	Vector3 & operator -= (const Vector3 & vector);
	Vector3 operator * (GLfloat k) const;
	Vector3 & operator *= (GLfloat k);
	Vector3 operator / (GLfloat k) const;
	Vector3 & operator /= (GLfloat k);
	Vector3 & operator = (const Vector3 & vector);
	Vector3 Modulate(const Vector3 & vector) const;
	GLfloat Dot(const Vector3 & vector) const;
	Vector3 Cross(const Vector3 & vector) const;

	// implement a more precise Vector3 ==, in fact of coordinates are made of float values.
	static bool SameDirectionWith(const Vector3& other);
	bool operator== (const Vector3& other) const {return x == other.x && y == other.y && z == other.z;}
	bool operator!= (const Vector3& other) const {return x != other.x || y != other.y || z != other.z;}
	bool operator < (const Vector3& other) const {return x != other.x ? x < other.x : y != other.y ? y < other.y : z < other.z;}

	//access to elements
	GLfloat operator [] (unsigned int idx) const;

	// data members
	GLfloat x;
	GLfloat y;
	GLfloat z;
};

inline Vector3 operator - (const Vector3 & vector1, const Vector3 & vector2)
{
	return Vector3(vector1.x - vector2.x, vector1.y - vector2.y, vector1.z - vector2.z);
}

inline Vector3 operator + (const Vector3 & vector1, const Vector3 & vector2)
{
	return Vector3(vector1.x + vector2.x, vector1.y + vector2.y, vector1.z + vector2.z);
}

//Vector4

class Matrix;

class Vector4
{
public:
	//Constructors
	Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
	Vector4(GLfloat _x, GLfloat _y, GLfloat _z) : x(_x), y(_y), z(_z), w(1.0f) {}
	Vector4(GLfloat _x, GLfloat _y, GLfloat _z, GLfloat _w) : x(_x), y(_y), z(_z), w(_w) {}
	Vector4(GLfloat * pArg) : x(pArg[0]), y(pArg[1]), z(pArg[2]), w(pArg[3]) {}
	Vector4(const Vector3 & vector) : x(vector.x), y(vector.y), z(vector.z), w(1.0f){}
	Vector4(const Vector3 & vector, GLfloat _w) : x(vector.x), y(vector.y), z(vector.z), w(_w) {}
	Vector4(const Vector4 & vector) : x(vector.x), y(vector.y), z(vector.z), w(vector.w) {}

	//Vector's operations
	GLfloat Length() const;
	Vector4 & Normalize();
	Vector4 operator + (const Vector4 & vector) const;
	Vector4 & operator += (const Vector4 & vector);
	Vector4 operator - () const;
	Vector4 operator - (const Vector4 & vector) const;
	Vector4 & operator -= (const Vector4 & vector);
	Vector4 operator * (GLfloat k) const;
	Vector4 & operator *= (GLfloat k);
	Vector4 operator / (GLfloat k) const;
	Vector4 & operator /= (GLfloat k);
	Vector4 & operator = (const Vector4 & vector);
	Vector4 Modulate(const Vector4 & vector) const;
	GLfloat Dot(const Vector4 & vector) const;

	//matrix multiplication
	Vector4 operator * ( Matrix & m ) const;

	//access to elements
	GLfloat operator [] (unsigned int idx) const;

	//data members
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat w;
};

//Matrix 4 X 4


class Matrix
{
public:
	//constructors
	Matrix() { SetIdentity(); }
	Matrix(GLfloat val);
	Matrix(const Matrix & mat);

	// Matrix operations
	Matrix & SetZero();
	Matrix & SetIdentity();

	Matrix & SetRotationX(GLfloat angle);
	Matrix & SetRotationY(GLfloat angle);
	Matrix & SetRotationZ(GLfloat angle);
	Matrix & SetRotationAngleAxis( float angle, float x, float y, float z );

	Matrix & SetScale(GLfloat scale);
	Matrix & SetScale(GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ);
	Matrix & SetScale(GLfloat * pScale);
	Matrix & SetScale(const Vector3 &scaleVec);

	Matrix & SetTranslation(GLfloat x, GLfloat y, GLfloat z);
	Matrix & SetTranslation(GLfloat *pTrans);
	Matrix & SetTranslation(const Vector3 &vec);

	Matrix & SetPerspective(GLfloat fovY, GLfloat aspect, GLfloat nearPlane, GLfloat farPlane);
	Matrix & SetOrthographic(GLfloat left, GLfloat right, GLfloat top, GLfloat bottom, GLfloat nearPlane, GLfloat farPlane);

	Matrix Transpose();

	Matrix operator + (Matrix & mat) const;
	Matrix & operator += (Matrix & mat);
	Matrix operator - (Matrix & mat) const;
	Matrix &operator -= (Matrix & mat);

	Matrix operator * (const Matrix & mat) const;
	Matrix operator * (GLfloat k) const;
	Matrix & operator *= (GLfloat k);

	Vector4 operator * (const Vector4 & vec);

	Matrix & operator = (const Matrix & mat);

	//data members
	GLfloat m[4][4];
};


Matrix & SetOrthographic(GLfloat left, GLfloat right, GLfloat top, GLfloat bottom, GLfloat nearPlane, GLfloat farPlane);
inline float Radians(float degrees)
{
	return degrees * RADIAN_PER_DEGREE;
}

inline float PixelsFromMeters(float meters)
{
	return meters * PIXEL_PER_METER;
}

inline float MetersFromPixels(float pixels)
{
	return pixels / PIXEL_PER_METER;
}

inline Vector2 GraphicsFromPhysics(b2Vec2 physicsPosition)
{
	Vector2 graphicsPosition;
	graphicsPosition.x = PixelsFromMeters(physicsPosition.x);
	graphicsPosition.y = PixelsFromMeters(physicsPosition.y);
	return graphicsPosition;
}

inline float MinutesFromSeconds(float seconds)
{
	return seconds / SECOND_PER_MINUTE;
}

inline float Sigmoid(float x, float scale)
{
	float result = 1.0f / (1 - exp(-scale*x));
	return result;
}

#pragma once
#include "Vector2.h"
#include "Vector4.h"
//#include "Color.h"
struct VertexIn
{
	Vector4 pos;
	Vector4 normal;
	Vector4 tangent;
	//Color color;
	Vector2 uv;
};

struct VertexOut
{
	Vector4 pos;
	Vector4 normal;
	Vector2 uv;
	Vector4 posH;
	//Color color;
	float oneDivZ;
	VertexOut() = default;
	VertexOut(Vector4 pos,Vector4 normal,Vector2 uv,Vector4 posH,Color color,float oneDivZ)
		:pos(pos),normal(normal),uv(uv),posH(posH),color(color),oneDivZ(oneDivZ){}

	
};
#pragma once
#ifndef ALPHA_Engine_H
#define ALPHA_Engine_H


class Object;
class PathShader;

class GameFunction {
public:
	virtual void Start();
	virtual void Update();

};

#ifdef __cplusplus
extern "C" {
#endif

#ifdef ALPHA_Engine
#define ALPHA_Engine_H __declspec(dllexport)
#else
#define ALPHA_Engine_H __declspec(dllimport)
#endif

#ifdef __cplusplus
}
#endif

void ALPHA_Engine_H Test();

#endif


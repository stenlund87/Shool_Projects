#pragma once
#include <vm_mathlib.h>

class LightNode
{
	public:
		void SetPos(float x, float y, float z);
		void SetSpec(float x, float y, float z);
		void SetDiff(float x, float y, float z);
		void SetAmb(float x, float y, float z);
		void SetIntensity(float shiny);

		Vector4D GetPos();
		Vector4D GetSpec();
		Vector4D GetDiff();
		Vector4D GetAmb();
		float GetIntensity();

	protected:
		Vector4D pos;
		Vector4D spec;
		Vector4D diff;
		Vector4D amb;
		//Matrix4D mat;
		float intensity;

};
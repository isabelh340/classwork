#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include <math.h>

#include <glm/glm.hpp>

using namespace glm;

string toString(vec2 v)
{
	return "[ " + std::to_string(v.x) + ", " + std::to_string(v.y) + " ]";
}

string toString(vec3 v)
{
	return "[ " + std::to_string(v.x) + ", " + 
			      std::to_string(v.y) + ", " + 
				  std::to_string(v.z) + " ]";
}

string toString(vec4 v)
{
	return "[ " + std::to_string(v.x) + ", " + 
				  std::to_string(v.y) + ", " + 
				  std::to_string(v.z) + ", " + 
				  std::to_string(v.w)+ " ]";
}

string toString(mat2 m)
{   
	string s = "\n";

	for (int col = 0; col < 2 ; col++) {
			s+= "|\t";
		for (int row = 0; row < 2; row++) {
			s+= std::to_string(m[row][col]) + "\t";
		}
		s+= "\t|\n";
	}
	s+= "\n";

	return s;
}

string toString(mat3 m)
{   
	string s = "\n";
	for (int col = 0; col < 3 ; col++) {
	 {
		s+= "|\t";
		for (int row = 0; row < 3; row++)	
			s+= std::to_string(m[row][col]) + "\t";
		}
		s+= "\t|\n";
	}
	s+= "\n";

	return s;
}

string toString(mat4 m)
{   
	string s = "\n";
	for (int col = 0; col < 4 ; col++) {
		s+= "|\t";
		for (int row = 0; row < 4; row++) {
			s+= std::to_string(m[row][col]) + "\t";
		}
		s+= "\t|\n";
	}
	s+= "\n";

	return s;
}
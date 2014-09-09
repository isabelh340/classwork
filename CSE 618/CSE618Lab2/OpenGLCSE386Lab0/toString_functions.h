#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <glm/glm.hpp>


std::string toString(glm::vec2 v)
{
	return "[ " + std::to_string(v.x) + ", " + std::to_string(v.y) + " ]";
}

std::string toString(glm::vec3 v)
{
	return "[ " + std::to_string(v.x) + ", " + 
			      std::to_string(v.y) + ", " + 
				  std::to_string(v.z) + " ]";
}

std::string toString(glm::vec4 v)
{
	return "[ " + std::to_string(v.x) + ", " + 
				  std::to_string(v.y) + ", " + 
				  std::to_string(v.z) + ", " + 
				  std::to_string(v.w)+ " ]";
}

std::string toString(glm::mat2 m)
{   
	std::string s = "\n";

	for (int row = 0; row < 2; row++) {
		s+= "|\t";
		for (int col = 0; col < 2 ; col++) {
			s+= std::to_string(m[row][col]) + "\t";
		}
		s+= "\t|\n";
	}
	s+= "\n";

	return s;
}

std::string toString(glm::mat3 m)
{   
	std::string s = "\n";

	for (int row = 0; row < 3; row++) {
		s+= "|\t";
		for (int col = 0; col < 3 ; col++) {
			s+= std::to_string(m[row][col]) + "\t";
		}
		s+= "\t|\n";
	}
	s+= "\n";

	return s;
}

std::string toString(glm::mat4 m)
{   
	std::string s = "\n";

	for (int row = 0; row < 4; row++) {
		s+= "|\t";
		for (int col = 0; col < 4 ; col++) {
			s+= std::to_string(m[row][col]) + "\t";
		}
		s+= "\t|\n";
	}
	s+= "\n";

	return s;
}
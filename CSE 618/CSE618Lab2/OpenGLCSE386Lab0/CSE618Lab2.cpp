#include <iostream>
#include <string>
#include <vector>
#define _USE_MATH_DEFINES // for C++
#include <cmath>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm\glm.hpp>
#include "toString_functions.h"

void setPixel( float x, float y, GLubyte rgb[]) {
	// Set the raster position for pixel
	glWindowPos2f( x, y );

	// Set the color for the pixel
	glDrawPixels(1, 1, GL_RGB, GL_UNSIGNED_BYTE, rgb);
} // end setPixel



void problemOne(){ 
	std::cout << "0 degrees equals " << glm::radians(0.0) << " radians." << std::endl;
	std::cout << "45 degrees equals " << glm::radians(45.0) << " radians." << std::endl;
	std::cout << "135 degrees equals " << glm::radians(135.0) << " radians." << std::endl;
	std::cout << "270 degrees equals " << glm::radians(270.0) << " radians." << std::endl;
	std::cout << "360 degrees equals " << glm::radians(360.0) << " radians." << std::endl;
}

void problemTwo() {
	std::cout << "pi/4 radians equals " << glm::degrees(M_PI/4.0) << " degrees." << std::endl;
	std::cout << "pi radians equals " << glm::degrees(M_PI) << " degrees." << std::endl;
	std::cout << "3pi/2 radians equals " << glm::degrees(3*M_PI/2.0) << " degrees." << std::endl;
	std::cout << "2pi radians equals " << glm::degrees(2.0*M_PI) << " degrees." << std::endl;
}

void problemThree() {
	double x1 = 9, y1 = 11, x2 = 2, y2 = -4;
	glm::vec2 p1(x1,y1), p2(x2,y2);
	double glmDistance = glm::distance(p1,p2);
	double myDistance = std::sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
	std::cout << "Distance between [ "<< x1 << "," << y1 << " ] and [ " << x2 << "," << y2 << " ]" << std::endl
			  << "using glm distance function is " << glmDistance << std::endl
			  << "Calculated distance is " << myDistance << std::endl;
}

void problemFour() {
	glm::vec2 p1(2,3), p2(5,-2);
	double glmLengthP1 = glm::length(p1);
	double glmLengthP2 = glm::length(p2);
	int glmDot = glm::dot(p1,p2);
	float cosTheta = glmDot / (glmLengthP2 * glmLengthP1);
	float theta = glm::acos(cosTheta);
	float myDot = std::sqrt(p1.x*p1.y + -p2.x*p2.y);
	float myLength1 = std::sqrt((p1.x*p1.x)+(p1.y*p1.y));
	float myLength2 = std::sqrt((p2.x*p2.x)+(p2.y*p2.y));
	
	std::cout << "Problem four " << std::endl 
			  << "glm length of vec 1 = " << glmLengthP1 << std::endl
			  << "glm length of vec 2 = " << glmLengthP2 << std::endl
			  << "glm dot product is = "  << glmDot << std::endl 
			  << "my length of vec 1 = " << myLength1 << std::endl
			  << "my length of vec 2 = " << myLength2 << std::endl
			  << "my dot product is = "  << myDot << std::endl 
			  << "angle between points  ="<< theta << std::endl;
}

void problemFive() {
	glm::vec2 p1(8,4), p2(3,0);
	glm::vec2 p2Normalized = glm::normalize(p2);
	glm::vec2 projection = p1 * p2Normalized;
	double cosTheta = glm::dot(p1,p2) / (glm::length(p1) * glm::length(p2));
	std::cout << "Problem five " << std::endl 
		      << "Projection vector = " << toString(projection) << std::endl
			  << "cosTheta = " << cosTheta << std::endl;
}

void problemSix() {
	glm::vec2 p1(9,-3);
	glm::vec2 glmNormal = glm::normalize(p1);
	glm::vec2 myNormal  = p1/glm::length(p1);
	std::cout << "Problem six " << std::endl 
		<< "Glm normal is " << toString(glmNormal) << std::endl
		<< "My normal is "  << toString(myNormal) << std::endl;
}

void problemSeven() {
	glm::vec2 p1(2,3), p2(7,-4);
	glm::vec2 result(p2.x - p1.x, p2.y - p1.y);
	std::cout << "Problem seven " << std::endl 
		<< "Vector that runs from " << toString(p1) << " to " << toString(p2) 
		<< " is " << toString(result) << std::endl;
}

void problem8() {
	glm::vec2 p1(2,3), p2(7,-4);
	glm::vec2 result = p2 - p1;
	std::cout << "Problem eight " << std::endl 
		<< "Vector representing both" << toString(p1) << " and " << toString(p2) 
		<< " is " << toString(result) << std::endl;

}

void problem9() { 
	glm::vec2 p1(5,4);
	glm::vec2 p2 = glm::vec2(p1);
	p2.x*=-0.5;
	p2.y*=-0.5;
	std::cout << "Problem nine " << std::endl 
		<< "Vector half and opposite of " << toString(p1)  
		<< " is " << toString(p2) << std::endl;
}

void problem10() {
	glm::mat2 a(5,3,2,3);
	glm::mat2 a_inverse = glm::inverse(a);
	glm::mat2 id_mat = a * a_inverse;
	glm::mat2 a_transpose = glm::transpose(a);
	std::cout << "Problem ten " << std::endl 
		<< "matrix " << toString(a) << " has inverse " << toString(a_inverse) 
		<< " and the id matrix is " << toString(id_mat) << std::endl
		<< " and is transposed as " << toString(a_transpose) << std::endl;

}

void swap( glm::vec2 &p1, glm::vec2 &p2 ) {
	glm::vec2 temp = p1;
	p1 = p2;
	p2 = temp;
}

void drawVerticalLine(glm::vec2 p1,glm:: vec2 p2, GLubyte rgb[]) {
	if (p2.y < p1.y) {
		swap(p1, p2);
	}

	for( float y = p1.y; y < p2.y; y++ ) {
		setPixel( p1.x, y, rgb );
	}

} // end drawVerticalLine

void drawHorizontalLine(glm::vec2 p1, glm::vec2 p2, GLubyte rgb[]) {
	if (p2.x < p1.x) {
		swap(p1, p2);
	}

	for(float x = p1.x; x < p2.x; x++ ) {
		setPixel(x, p1.y, rgb );
	}
}

void drawDiagonalLine(glm::vec2 p1, glm::vec2 p2, GLubyte rgb[]) {
	if (p2.x < p1.x && p2.y < p1.y) {
		swap(p1, p2);
	}

	for(float x = p1.x, y = p1.y; x < p2.x && y < p2.y; x++, y++) {
		setPixel(x, y, rgb );
	}
}

void BresLine(glm::vec2 p1, glm::vec2 p2, GLubyte rgb[]) {
	if (p1.x == p2.x) {
		drawVerticalLine(p1,p2,rgb);
	} else if (p1.y == p2.y) {
		drawHorizontalLine(p1,p2,rgb);
	} else if (p1.x == p1.y && p2.x == p2.y) {
		drawDiagonalLine(p1,p2,rgb);
	}

	// handle negative slope line, by swapping points
	if (p1.y > p2.y) {
		swap(p1, p2);
	}

	int x = p1.x, y = p1.y;
	int dx = p2.x - p1.x, dy = p2.y - p1.y;
	int dT = 2 * (dy -dx), dS = 2  * dy;
	int d = 2 * dy - dx;
	for (; x < p2.x; x++) {
		setPixel(x,y,rgb);
		if (d < 0) {
			d+= dS;
		} else {
			y++;
			d+=dT;
		}
	}
}

void BresLineHomogenous(glm::vec3 p1, glm::vec3 p2, GLubyte rgb[]) {
	glm::vec2 p1Temp(0,0), p2Temp(0,0);
	p1Temp.x = p1.x;
	p1Temp.y = p1.y;
	p2Temp.x = p2.x;
	p2Temp.y = p2.y;
	BresLine(p1Temp,p2Temp, rgb);
}


void problem11() {
	GLubyte white[] = {128, 128, 128};
	GLubyte blue[] = {0, 0, 255};
	glm::vec2 p1(50,75), p2(130,200), shift(100,75);
	BresLine(p1,p2,blue);
	p1 += shift;
	p2 += shift;
	BresLine(p1,p2,white);
}

void problem12() {
	GLubyte white[] = {128, 128, 128};
	GLubyte blue[] = {0, 0, 255};
	const int NUMBER_OF_2D_HOMOGENOUS = 3;
	// I hate visual studio.
	std::vector<glm::vec3> transMatrix;
	transMatrix.push_back(glm::vec3(1,0,100));
	transMatrix.push_back(glm::vec3(0,1,75));
	transMatrix.push_back(glm::vec3(0,0,1));
	

	glm::vec3 p1(50,75,1),p2(130,200,1), shiftP1(0,0,0), shiftP2(0,0,0);
	BresLineHomogenous(p1,p2,blue);
	for (int i = 0; i < transMatrix.size(); i++) {
		int temp = 0;
		for (int j = 0; j < NUMBER_OF_2D_HOMOGENOUS; j++) {
			temp += transMatrix[i][j] * p1[j]; 
		}
		shiftP1[i] = temp;
		temp = 0;
		for (int j = 0; j < NUMBER_OF_2D_HOMOGENOUS; j++) {
			temp += transMatrix[i][j] * p2[j]; 
		}
		shiftP2[i] = temp;
	}
	BresLineHomogenous(shiftP1,shiftP2,white);
}

void problem13() {
	GLubyte white[] = {128, 128, 128};
	GLubyte blue[] = {0, 0, 255};
	const int NUMBER_OF_2D_HOMOGENOUS = 3;
	// I hate visual studio.
	std::vector<glm::vec3> transMatrix;
	transMatrix.push_back(glm::vec3(1,0,100));
	transMatrix.push_back(glm::vec3(0,1,125));
	transMatrix.push_back(glm::vec3(0,0,1));
	
	glm::vec3 p1(50,75,1),p2(130,200,1), shiftP1(0,0,0), shiftP2(0,0,0);
	BresLineHomogenous(p1,p2,blue);
	for (int i = 0; i < transMatrix.size(); i++) {
		int temp = 0;
		for (int j = 0; j < NUMBER_OF_2D_HOMOGENOUS; j++) {
			temp += transMatrix[i][j] * p1[j]; 
		}
		shiftP1[i] = temp;
		temp = 0;
		for (int j = 0; j < NUMBER_OF_2D_HOMOGENOUS; j++) {
			temp += transMatrix[i][j] * p2[j]; 
		}
		shiftP2[i] = temp;
	}
	BresLineHomogenous(shiftP1,shiftP2,white);

}

void problem14() {

}

void problem15() {

}

void problem16() {

}

void problem17() {

}

void problem18() {

}

/**
* Acts as the display function for the window. 
*/
static void RenderSceneCB() {
    // Clear the color and depth buffers
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glClearColor(255,255,255,1);

	// TODO
	// Your rendering code
	problem11();
	problem12();
	problem13();

	// Flush all drawing commands and swapbuffers
	glutSwapBuffers();
} // end RenderSceneCB


/**
* Called each time the window is resized
*/
static void ResizeCB(int width, int height) {
	glutPostRedisplay();
}


int main(int argc, char** argv) {
	// Lab two problems
	problemOne();
	problemTwo();
	problemThree();
	problemFour();
	problemFive();
	problemSix();
	problemSeven();
	problem8();
	problem9();
	problem10();

    // Pass any applicable command line arguments to GLUT. These arguments
	// are platform dependent.
    glutInit(&argc, argv);

	// Set the initial window size
	glutInitWindowSize( 400, 400 );

	// Create a window using a string and make it the current window.
	glutCreateWindow("CSE 618 Lab2");

	// Indicate to GLUT that the flow of control should return to the program after
	// the window is closed and the GLUTmain loop is exited.
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	// GLEW does not entirely support the Core GLUT Profile out of the box. 
	// The following statement fixes the problem.
	glewExperimental = GL_TRUE;

	// Intilize GLEW. This must be done after glut is initialized.
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return false; // GLEW could not be initialized.
	}

	// Callback for window redisplay
	glutDisplayFunc(RenderSceneCB);		
	glutReshapeFunc(ResizeCB);

	// Set window clear color
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f);

	// Unbind shader in use to enable fixed function pipeline functionality (compatability mode)
	glUseProgram(0);
	
	// Enter the GLUT main loop. Control will not return until the
	// window is closed.
    glutMainLoop();

	return 0;

} // end main
#ifndef TEXT_READER_H_
#define TEXT_READER_H_

#include <glm/glm.hpp>

#include "Scene.h"
#include "ControlPoint.h"
#include "Curve.h"
#include "Patch.h"

class TextReader{
	public:
		TextReader();
		virtual ~TextReader();

		void parse(Scene& scene, const char* file_loc);
};

#endif
#include <glm/glm.hpp>
#include "Sample.h"

class Film{
	float width;
	float height;

	std::vector<Sample> samples;

	public:
		Film(float w, float h);
		virtual ~Film();

		void encodeImage();
		void addSample();
};
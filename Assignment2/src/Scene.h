#include <glm/glm.hpp>
#include "Ray.h"

class Scene{
	glm::vec3 UL;
	glm::vec3 LL;
	glm::vec3 UR;
	glm::vec3 LR;
	
	Camera cam;

	std::vector<Ray> rays;

	public:
		Scene(float ULx, float ULy, float ULz, float LLx, float LLy, float LLz, float URx, float URy, float URz, float LRx, float LRy, float LRz, Camera cam);
		virtual ~Scene();

		void render();

		void print();
};
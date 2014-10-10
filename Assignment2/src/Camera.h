#include <glm/glm.hpp>

class Camera{
	glm::vec3 position;
	glm::vec3 view;
	glm::vec3 yaw;
	glm::vec3 pitch;

	float depth;

	public:
		Camera(float x, float y, float z);
		virtual ~Camera();
};
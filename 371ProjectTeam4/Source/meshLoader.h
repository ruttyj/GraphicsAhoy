

#include <GLM/glm.hpp>
#include <map>
#include <vector>
#include <string>

class MeshLoader
{
public:
	MeshLoader();
	~MeshLoader();
	void Draw(glm::mat4 worldMat);
private:
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 color;
	};
	
	std::vector<Vertex>* mVertexArray;
	unsigned int mVertexArrayID;
	unsigned int mVertexBufferID;
	unsigned int mNumOfVertices;
};

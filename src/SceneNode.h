#ifndef GRAPH_NODE_H
#define GRAPH_NODE_H
#include <vector>
#include <Model.h>

using std::vector;

class Transform
{
	// transformations that affect object and it's children
	glm::mat4 world_ = glm::mat4(1.0f);

	// transformations that affect only object
	glm::mat4 local_ = glm::mat4(1.0f);
public:
	Transform() = default;

	/**
	 * \brief Combine this with other transformation, but only on world_ fields (inherited)
	 * \param other Transformations object to combine with
	 */
	void combine(Transform& other)
	{
		this->world_ = other.world_ * this->world_;
	}

	/**
	 * \brief Combine all transformations to one matrix
	 * \return matrix4 of all object transformations
	 */
	glm::mat4 combine()
	{
		return world_ * local_;
	}

	glm::mat4 get_world() const
	{
		return world_;
	}

	glm::mat4 get_local() const
	{
		return local_;
	}

	void set_world(glm::mat4 world)
	{
		world_ = world;
	}

	void set_local(glm::mat4 local)
	{
		local_ = local;
	}

	
};


class GraphNode
{
private:
	Transform transform_;
	bool dirty_;
	Drawable* model_;
	vector<GraphNode*> children_;

public:
	GraphNode(Drawable* model)
		: model_(model),
		transform_(Transform()),
		dirty_(true)
	{}


	void render(glm::mat4 projection, glm::mat4 view, Transform parentWorld = Transform(), bool dirty = false)
	{
		dirty |= dirty_;
		if (dirty)
		{
			transform_.combine(parentWorld);
			dirty_ = false;
		}
		// xxx
		if (model_)
		{
			model_->getShader()->use();
			model_->getShader()->setMat4("projection", projection);
			model_->getShader()->setMat4("view", view);
			model_->getShader()->setMat4("model", transform_.combine());
			model_->Draw();
		}
		// xxx

		for (auto child : children_)
		{
			child->render(projection, view, transform_, dirty);
		}
	}

	void setTransform(Transform local)
	{
		transform_ = local;
		dirty_ = true;
	}

	void rotate(float x, float y, float z) {
		transform_.set_world(glm::rotate(transform_.get_world(), x, glm::vec3(1, 0, 0)));
		transform_.set_world(glm::rotate(transform_.get_world(), y, glm::vec3(0, 1, 0)));
		transform_.set_world(glm::rotate(transform_.get_world(), z, glm::vec3(0, 0, 1)));
	}

	void translate(float x, float y, float z) {
		transform_.set_world(glm::translate(transform_.get_world(), glm::vec3(x, y, z)));
	}

	void scale(float x, float y, float z) {
		transform_.set_world(glm::scale(transform_.get_world(), glm::vec3(x, y, z)));
	}

	void addChild(GraphNode* child)
	{
		children_.push_back(child);
	}

	vector<GraphNode*> getChildren()
	{
		return children_;
	}
};

#endif
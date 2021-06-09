
#pragma once
#include "Core/Events/WindowEvents.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Vortex
{
	enum class CameraType
	{
		Orthographical,
		Perspective
	};

	class Camera
	{
	public:
		virtual ~Camera() = default;
		static Ref<Camera> Create(const CameraType type, const float width, const float height, const float min, const float max);

		virtual void Resize(const float width, const float height) = 0;
		virtual void OnEvent(Event& e) = 0;

		virtual void SetZoom(const float zoom) = 0;
		const float& GetZoom() const { return m_Zoom; }

		const glm::vec4& GetRect() const { return m_Rect; }

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix(const glm::vec3& position = glm::vec3(0.f), const glm::vec3& rotation = glm::vec3(0.f)) { RecalculateViewMatrix(position, rotation); return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix(const glm::vec3& position = glm::vec3(0.f), const glm::vec3& rotation = glm::vec3(0.f)) { RecalculateViewMatrix(position, rotation); return m_ViewProjectionMatrix; }

	protected:
		virtual bool OnWindowResize(WindowResizeEvent& event) = 0;

		void RecalculateViewMatrix(const glm::vec3& position, const glm::vec3& rotation);

	protected:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec4 m_Rect;

		float m_Near, m_Far;

		float m_AspectRatio;
		float m_Zoom = 0.f;

	};

	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(float width, float height, float min = -1.f, float max = 10.f);
		virtual void SetZoom(const float zoom) override;

		virtual void Resize(const float width, const float height) override;
		virtual void OnEvent(Event& e) override;

	private:
		virtual bool OnWindowResize(WindowResizeEvent& event) override;
	};
}
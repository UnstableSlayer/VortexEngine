
#pragma once
#include "Core/Events/WindowEvents.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Vortex
{
	/// Camera ////////////////////////////////////

	enum class CameraType
	{
		Orthographic,
		Perspective
	};

	class Camera
	{
	public:
		virtual ~Camera() = default;
		static Ref<Camera> Create(const CameraType type, const float width, const float height, const float zNear = 0.1f, const float zFar = 1000.f, const float fov = 60.f);

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


	/// Orthographic ////////////////////////////////////

	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(float width, float height, float zNear, float zFar, float fov = 0.f);
		virtual void SetZoom(const float zoom) override;

		virtual void Resize(const float width, const float height) override;
		virtual void OnEvent(Event& e) override;

	private:
		virtual bool OnWindowResize(WindowResizeEvent& event) override;
	};


	/// Perspective ////////////////////////////////////

	class PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(const float width, const float height, const float zNear, const float zFar, const float fov);
		virtual void SetZoom(const float zoom) override;

		virtual void Resize(const float width, const float height) override;
		virtual void OnEvent(Event& e) override;

	private:
		virtual bool OnWindowResize(WindowResizeEvent& event) override;

	private:
		float m_FOV;
	};
}
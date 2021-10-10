
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

	class VORTEX_API Camera
	{
	public:
		virtual ~Camera() = default;
		static Ref<Camera> Create(const CameraType type, const float width, const float height, const float zNear = 0.1f, const float zFar = 1000.f, const float fov = 60.f);

		virtual void Resize(const float width, const float height) = 0;
		virtual void OnEvent(Event& e) = 0;

		virtual void SetZoom(const float zoom) = 0;
		const float& GetZoom() const { return m_Zoom; }

		void SetClipSpace(const float zNear, const float zFar) { m_Near = zNear; m_Far = zFar; }
		const glm::vec2& GetClipSpace() const { return {m_Near, m_Far}; }

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix(const glm::vec3& position = glm::vec3(0.f), const glm::quat& rotation = glm::quat(1.f, 0.f, 0.f, 0.f))
			{ RecalculateViewMatrix(position, rotation); return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix(const glm::vec3& position = glm::vec3(0.f), const glm::quat& rotation = glm::quat(1.f, 0.f, 0.f, 0.f))
			{ RecalculateViewMatrix(position, rotation); return m_ViewProjectionMatrix; }

	protected:
		virtual bool OnWindowResize(WindowResizeEvent& event) = 0;

		void RecalculateViewMatrix(const glm::vec3& position, const glm::quat& rotation);

	protected:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		float m_Near, m_Far;

		float m_AspectRatio;
		float m_Zoom;
	};


	/// Orthographic ////////////////////////////////////

	class VORTEX_API OrthographicCamera : public Camera
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

	class VORTEX_API PerspectiveCamera : public Camera
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
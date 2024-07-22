#pragma once
#include <Mesh.h>
#include <MeshLoader.h>
#include <glm/glm.hpp>
#include <entt.hpp>

namespace Square
{
	class Scene;

	struct Entity
	{
		entt::entity Entity;
		Scene* scene;
	};

	struct TagComponent
	{
		std::string tag;

		inline TagComponent(const std::string& t) {
			tag = t;
		}
	};

	struct TransformComponent
	{
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
	};

	struct MeshComponent
	{
		std::string meshPath;
		Mesh* mesh;

		inline MeshComponent(const std::string& m) {
			meshPath = m;
		};
	};

	class Scene
	{
	public:
		Scene();
		void Start();
		void ReloadMesh(Entity e);
		void Update();
		void Render();
		void Destroy();

		void DeleteEntity(Entity e);

		template<typename T, typename... Args>
		void AddComponent(Entity e, Args&&... args);

		template <typename T>
		T& GetComponent(Entity e);

		template <typename T>
		bool HasComponent(Entity e);

		Entity AddEntity();
		Entity AddEntityDefaultTemplate(const std::string& tag);

		Entity GetEntityByUUID(uint64_t uuid);
		uint64_t GetEntityUUID(Entity e);

		Entity GetEntityByTag(std::string tag);
		std::string GetEntityTag(Entity e);

		std::vector<Entity> AllEntities();
	private:
		entt::registry reg;
		std::unordered_map<uint64_t, entt::entity> entities;
	};

	inline Scene* activeScene;
	inline void SetActiveScene(Scene* sc) { activeScene = sc; };
	inline Scene* GetActiveScene() { return activeScene; };

	template <typename T>
	inline T GetComponent(Entity e) { return GetActiveScene()->GetComponent<T>(e); };
}

#include <ECSManager.inl>
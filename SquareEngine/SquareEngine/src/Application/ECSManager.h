#pragma once
#include <Mesh.h>
#include <MeshLoader.h>
#include <glm/glm.hpp>
#include <entt.hpp>
#include <ScriptEngine.h>
#include "../../Coral.Native/Include/Coral/ManagedObject.hpp"

namespace Square
{
	typedef uint32_t UU_ID;

	class Scene;

	struct Entity
	{
		entt::entity EnttEntity;
		Scene* scene;

		// Equality operator as a member function
		bool operator==(const Entity& other) const {
			return EnttEntity == other.EnttEntity;
		}
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
			mesh = nullptr;
		};
	};

	struct ScriptObject
	{
		Coral::Type type;
		Coral::ManagedObject instance;

		ScriptObject operator=(const ScriptObject& other) {
			ScriptObject temp = ScriptObject();
			temp.type = other.type;
			temp.instance = other.instance;
			return temp;
		}
	};

	struct ScriptComponent
	{
		std::string typeName;
		ScriptObject sob;

		inline ScriptComponent(const std::string& t) {
			typeName = t;
		}
	};

	class Scene
	{
	public:
		Scene(int argc, char** argv, const std::string& dllPath);
		
		void ResetAssembly(int argc, char** argv, const std::string& dllPath);

		void Start();
		void ReloadMesh(Entity e);
		void ReloadScripts();
		void Update();
		void Render();
		void Destroy();

		void UpdateTransform(TransformComponent transform, UU_ID uuid);

		template <typename T>
		void RemoveComponent(Entity entity);

		void DeleteEntity(Entity e);

		template<typename T, typename... Args>
		void AddComponent(Entity e, Args&&... args);

		template <typename T>
		T& GetComponent(Entity e);

		template <typename T>
		bool HasComponent(Entity e);

		Entity AddEntity();
		Entity AddEntityDefaultTemplate(const std::string& tag);

		Entity GetEntityByUUID(UU_ID uuid);
		UU_ID GetEntityUUID(Entity e);
		UU_ID GetEntityUUID(entt::entity e);

		Entity GetEntityByTag(std::string tag);
		std::string GetEntityTag(Entity e);

		void ReloadAssets();

		std::vector<Entity> AllEntities();
	private:
		entt::registry reg;
		std::unordered_map<UU_ID, entt::entity> entities;

		Assembly assembly;
		int argc;
		char** argv = nullptr;
	};

	inline Scene* activeScene;
	inline void SetActiveScene(Scene* sc) { activeScene = sc; };
	inline Scene* GetActiveScene() { return activeScene; };

	template <typename T>
	inline T GetComponent(Entity e) { return GetActiveScene()->GetComponent<T>(e); };
}

#include <ECSManager.inl>

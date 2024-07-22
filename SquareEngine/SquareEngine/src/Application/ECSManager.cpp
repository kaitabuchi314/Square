#include "ECSManager.h"
#include <MeshLoader.h>
#include <Renderer.h>
#include <Random.h>

namespace Square
{
	Scene::Scene()
	{
		reg = entt::registry();
	}

	void Scene::Start()
	{
		auto transformView = reg.view<TransformComponent>();
		//auto meshView = reg.view<MeshComponent>();
		auto meshView = reg.view<MeshComponent>();

		for (auto entity : meshView)
		{
			auto& mesh = meshView.get<MeshComponent>(entity);
			const char* mls = mesh.meshPath.c_str();
			mesh.mesh = Square::loadMesh(mls);
			mesh.mesh->mat.shine = 10;
			mesh.mesh->mat.texture = Square::loadTexture("Resources/grid.png");
		}
	}

	void Scene::ReloadMesh(Entity e)
	{
		Square::MeshComponent& mesh = GetComponent<MeshComponent>(e);

		bool hasMaterialGen = mesh.mesh;
		Material pmat;

		if (hasMaterialGen)
			pmat = mesh.mesh->mat;

		mesh.mesh = Square::loadMesh(mesh.meshPath.c_str());

		if (hasMaterialGen)
			mesh.mesh->mat = pmat;
	}

	void Scene::Update()
	{
		//auto transformView = reg.view<TransformComponent>();
		//auto meshView = reg.view<MeshComponent>();

		//for (auto entity : meshView)
		//{
		//	auto& mesh = meshView.get<MeshComponent>(entity);
		//	mesh.mesh = Square::loadMesh(mesh.meshPath.c_str());
		//}
	}

	void Scene::Render()
	{
		auto transformView = reg.view<TransformComponent>();
		auto meshView = reg.view<MeshComponent>();

		for (auto entity : meshView)
		{
			auto& mesh = meshView.get<MeshComponent>(entity);
			auto& transform = reg.get<TransformComponent>(entity);

			Square::GetActiveRenderer()->RenderMesh(mesh.mesh, transform.position, transform.rotation, transform.scale);
		}
	}

	void Scene::Destroy()
	{
		auto meshView = reg.view<MeshComponent>();

		for (auto entity : meshView)
		{
			auto& mesh = meshView.get<MeshComponent>(entity);
			delete mesh.mesh;
		}
	}

	void Scene::DeleteEntity(Entity e)
	{
		for (const auto& pair : entities)
		{
			if (pair.second == e.Entity)
			{
				entities.erase(pair.first);
				break;
			}
		}

		reg.destroy(e.Entity);
	}

	Entity Scene::AddEntity()
	{
		Entity e = { reg.create(), this };
		entities[Square::RandomEntityUUID()] = e.Entity;
		return e;
	}

	Entity Scene::AddEntityDefaultTemplate(const std::string& tag)
	{
		Entity entity = AddEntity();
		AddComponent<TagComponent>(entity, tag);
		AddComponent<TransformComponent>(entity, glm::vec3(0), glm::vec3(0), glm::vec3(1));

		return entity;
	}

	Entity Scene::GetEntityByUUID(uint64_t uuid)
	{
		return Entity { entities[uuid], this };
	}

	uint64_t Scene::GetEntityUUID(Entity e)
	{
		uint64_t key;

		for (const auto& pair : entities)
		{
			if (pair.second == e.Entity)
			{
				key = pair.first;
				break;
			}
		}

		return key;
	}

	Entity Scene::GetEntityByTag(std::string tag)
	{
		auto tagView = reg.view<TagComponent>();

		for (auto entity : tagView)
		{
			auto& tagC = tagView.get<TagComponent>(entity);
			
			if (tagC.tag == tag)
				return Entity { entity };
		}
		
		Square::Log("ERROR::Cannot Find Entity: " + tag);
		std::exit(0);
	}

	std::string Scene::GetEntityTag(Entity e)
	{
		return GetComponent<TagComponent>(e).tag;
	}

	std::vector<Entity> Scene::AllEntities()
	{
		std::vector<Entity> ent;

		for (auto& pair : entities)
		{
			ent.push_back({ pair.second });
		}

		return ent;
	}
}

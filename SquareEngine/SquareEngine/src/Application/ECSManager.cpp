#include "ECSManager.h"
#include <MeshLoader.h>
#include <Renderer.h>
#include <Random.h>
#include <ApplicationState.h>

namespace Square
{
	Scene::Scene(int ac, char** av, const std::string& dllPath) : assembly(LoadAssembly(ac, av, dllPath))
	{
		argc = ac;
		argv = av;
		reg = entt::registry();
	}

	void Scene::ResetAssembly(int argc, char** argv, const std::string& dllPath)
	{
		this->argc = argc;
		this->argv = argv;
		assembly = LoadAssembly(argc, argv, dllPath, assembly.context, assembly.host);
	}

	void Scene::Start()
	{
		auto transformView = reg.view<TransformComponent>();
		auto meshView = reg.view<MeshComponent>();

		for (auto entity : meshView)
		{
			auto& mesh = meshView.get<MeshComponent>(entity);
			const char* mls = mesh.meshPath.c_str();
			mesh.mesh = Square::loadMesh(mls);
			mesh.mesh->mat.shine = 10;
			mesh.mesh->mat.texture = Square::loadTexture("Resources/grid.png");
			mesh.mesh->mat.texPath = "Resources/grid.png";
		}
	}

	void Scene::ReloadMesh(Entity e)
	{
		Square::MeshComponent& mesh = GetComponent<MeshComponent>(e);

		bool hasMaterialGen = mesh.mesh != nullptr;

		Material mat;
		if (hasMaterialGen)
		{
			mat = mesh.mesh->mat;
			delete mesh.mesh;
			mesh.mesh = nullptr;
		}

		mesh.mesh = Square::loadMesh(mesh.meshPath.c_str());

		if (hasMaterialGen)
			mesh.mesh->mat = mat;
	}

	void Scene::ReloadScripts()
	{
		auto scriptView = reg.view<ScriptComponent>();
		
		for (auto entity : scriptView)
		{
			auto& script = scriptView.get<ScriptComponent>(entity);
			if (script.typeName != std::string(""))
			{
				script.sob.type = assembly.coralAssembly.GetType(script.typeName);

				if (script.sob.type)
				{
					script.sob.instance = script.sob.type.CreateInstance();
				}
			}
		}
	}

	void Scene::Update()
	{
		auto scriptView = reg.view<ScriptComponent>();
		if (AppStates::HasChanged())
		{
			AppStates::ReceivedChange();

			if (AppStates::IsPlaying())
			{
				ReloadScripts();
				for (auto entity : scriptView)
				{
					auto& script = scriptView.get<ScriptComponent>(entity);
					script.sob.instance.InvokeMethod("Void OnStart(UInt32)", GetEntityUUID(entity));
				}

				SQ_LOG("Start");
			}
		}

		if (AppStates::IsPlaying())
		{
			for (auto entity : scriptView)
			{
				auto& script = scriptView.get<ScriptComponent>(entity);

				if (script.typeName != std::string("") && script.sob.type)
					script.sob.instance.InvokeMethod("OnUpdate");
			}
		}
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
			mesh.mesh = nullptr;
		}
	}

	void Scene::UpdateTransform(TransformComponent transform, UU_ID uuid)
	{
		GetComponent<TransformComponent>(GetEntityByUUID(uuid)).position = transform.position;
		GetComponent<TransformComponent>(GetEntityByUUID(uuid)).rotation = transform.rotation;
		GetComponent<TransformComponent>(GetEntityByUUID(uuid)).scale = transform.scale;
	}

	void Scene::DeleteEntity(Entity e)
	{
		for (const auto& pair : entities)
		{
			if (pair.second == e.EnttEntity)
			{
				entities.erase(pair.first);
				break;
			}
		}

		reg.destroy(e.EnttEntity);
	}

	Entity Scene::AddEntity()
	{
		Entity e = { reg.create(), this };
		entities[Square::RandomEntityUUID()] = e.EnttEntity;
		return e;
	}

	Entity Scene::AddEntityDefaultTemplate(const std::string& tag)
	{
		Entity entity = AddEntity();
		AddComponent<TagComponent>(entity, tag);
		AddComponent<TransformComponent>(entity, glm::vec3(0), glm::vec3(0), glm::vec3(1));

		return entity;
	}

	Entity Scene::GetEntityByUUID(UU_ID uuid)
	{
		if (entities.contains(uuid))
			return Entity { entities[uuid], this };
		else
		{
			SQ_LOG("ECS::ERROR::CANNOT FIND " + uuid);
			std::exit(0);
		}
	}

	UU_ID Scene::GetEntityUUID(Entity e)
	{
		UU_ID key;

		for (const auto& pair : entities)
		{
			if (pair.second == e.EnttEntity)
			{
				key = pair.first;
				break;
			}
		}

		return key;
	}

	UU_ID Scene::GetEntityUUID(entt::entity e)
	{
		UU_ID key;

		for (const auto& pair : entities)
		{
			if (pair.second == e)
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
		
		SQ_LOG("ERROR::Cannot Find Entity: " + tag);
	}

	std::string Scene::GetEntityTag(Entity e)
	{
		return GetComponent<TagComponent>(e).tag;
	}

	void Scene::ReloadAssets()
	{
		auto meshView = reg.view<MeshComponent>();

		for (auto entity : meshView)
		{
			Entity e = Entity { entity };
			ReloadMesh(e);

			MeshComponent mesh = GetComponent<MeshComponent>(e);

			if (mesh.mesh != nullptr)
			{
				mesh.mesh->mat.texture = loadTexture(mesh.mesh->mat.texPath.c_str());
			}
		}
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

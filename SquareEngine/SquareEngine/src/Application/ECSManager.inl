namespace Square
{
	template<typename T>
	inline void Scene::RemoveComponent(Entity entity)
	{
		reg.remove<T>(entity.EnttEntity);
	}

	template<typename T, typename... Args>
	void Scene::AddComponent(Entity e, Args&&... args)
	{
		reg.emplace<T>(e.EnttEntity, std::forward<Args>(args)...);
	}

	template<typename T>
	T& Scene::GetComponent(Entity e)
	{
		return reg.get<T>(e.EnttEntity);
	}

	template<typename T>
	bool Scene::HasComponent(Entity e)
	{
		auto view = reg.view<T>();

		for (auto entity : view)
		{
			if (entity == e.EnttEntity)
			{
				return true;
			}
		}

		return false;
	}
}

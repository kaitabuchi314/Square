namespace Square
{
	template<typename T, typename... Args>
	void Scene::AddComponent(Entity e, Args&&... args)
	{
		reg.emplace<T>(e.Entity, std::forward<Args>(args)...);
	}

	template<typename T>
	T& Scene::GetComponent(Entity e)
	{
		return reg.get<T>(e.Entity);
	}

	template<typename T>
	inline bool Scene::HasComponent(Entity e)
	{
		auto view = reg.view<T>();

		for (auto entity : view)
		{
			if (entity == e.Entity)
			{
				return true;
			}
		}

		return false;
	}
}

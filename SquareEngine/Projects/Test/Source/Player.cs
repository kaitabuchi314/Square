using System;
using SquareEngine;

namespace Example
{
	public unsafe class ScriptA : Entity
	{
		public float speed = 4.0f;

		public void OnStart(UInt32 uuid)
		{
			base.PreCreate(uuid);

			transform.position = new Vector3(0, 0, 0);

			Log("Start!");

			base.Create();
		}

		public void OnUpdate()
		{
			base.PreUpdate();

			if (IsKeyDown(S_KEY_RIGHT))
				transform.position.x += speed * 0.01f;
			else if (IsKeyDown(S_KEY_LEFT))
				transform.position.x -= speed * 0.01f;

			if (IsKeyDown(S_KEY_UP))
				transform.position.z -= speed * 0.01f;
			else if (IsKeyDown(S_KEY_DOWN))
				transform.position.z += speed * 0.01f;

			base.Update();
		}
	}
}

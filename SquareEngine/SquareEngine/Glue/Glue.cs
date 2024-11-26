using System;
using Coral.Managed.Interop;

namespace SquareEngine
{
	public struct Vector2
	{
		public float x, y;
	
		// Constructor
		public Vector2(float x = 0, float y = 0)
		{
			this.x = x;
			this.y = y;
		}
	
		// Overload + operator
		public static Vector2 operator +(Vector2 a, Vector2 b)
		{
			return new Vector2(a.x + b.x, a.y + b.y);
		}
	
		// Overload - operator
		public static Vector2 operator -(Vector2 a, Vector2 b)
		{
			return new Vector2(a.x - b.x, a.y - b.y);
		}
	
		// Overload * operator (scalar multiplication)
		public static Vector2 operator *(Vector2 a, float scalar)
		{
			return new Vector2(a.x * scalar, a.y * scalar);
		}
	
		// Overload / operator (scalar division)
		public static Vector2 operator /(Vector2 a, float scalar)
		{
			return new Vector2(a.x / scalar, a.y / scalar);
		}
	
		// Overload * operator (dot product)
		public static float operator *(Vector2 a, Vector2 b)
		{
			return a.x * b.x + a.y * b.y;
		}
	
		// Print the vector (for debugging)
		public void Print()
		{
			Console.WriteLine($"Vector2({x}, {y})");
		}
	}
	
	public struct Vector3
	{
		public float x, y, z;
	
		// Constructor
		public Vector3(float x = 0, float y = 0, float z = 0)
		{
			this.x = x;
			this.y = y;
			this.z = z;
		}
	
		// Overload + operator
		public static Vector3 operator +(Vector3 a, Vector3 b)
		{
			return new Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
		}
	
		// Overload - operator
		public static Vector3 operator -(Vector3 a, Vector3 b)
		{
			return new Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
		}
	
		// Overload * operator (scalar multiplication)
		public static Vector3 operator *(Vector3 a, float scalar)
		{
			return new Vector3(a.x * scalar, a.y * scalar, a.z * scalar);
		}
	
		// Overload / operator (scalar division)
		public static Vector3 operator /(Vector3 a, float scalar)
		{
			return new Vector3(a.x / scalar, a.y / scalar, a.z / scalar);
		}
	
		// Overload * operator (dot product)
		public static float operator *(Vector3 a, Vector3 b)
		{
			return a.x * b.x + a.y * b.y + a.z * b.z;
		}
	
		/// <summary>
		/// Print the vector.
		/// </summary>
		public String toString()
		{
			return $"Vector3({x}, {y}, {z})";
		}
	}
	public struct TransformComponent
	{
		public Vector3 position;
		public Vector3 rotation;
		public Vector3 scale;
		public TransformComponent() {
			position = new Vector3(0,0,0);
			rotation = new Vector3(0,0,0);
			scale = new Vector3(1,1,1);
		}
	};

	public unsafe class Entity
	{
		public const int S_KEY_SPACE = 32;
		public const int S_KEY_APOSTROPHE = 39;  // '
		public const int S_KEY_COMMA = 44;  // ,
		public const int S_KEY_MINUS = 45;  // -
		public const int S_KEY_PERIOD = 46;  // .
		public const int S_KEY_SLASH = 47;  // /
		public const int S_KEY_0 = 48;
		public const int S_KEY_1 = 49;
		public const int S_KEY_2 = 50;
		public const int S_KEY_3 = 51;
		public const int S_KEY_4 = 52;
		public const int S_KEY_5 = 53;
		public const int S_KEY_6 = 54;
		public const int S_KEY_7 = 55;
		public const int S_KEY_8 = 56;
		public const int S_KEY_9 = 57;
		public const int S_KEY_SEMICOLON = 59;  // ;
		public const int S_KEY_EQUAL = 61;  // =
		public const int S_KEY_A = 65;
		public const int S_KEY_B = 66;
		public const int S_KEY_C = 67;
		public const int S_KEY_D = 68;
		public const int S_KEY_E = 69;
		public const int S_KEY_F = 70;
		public const int S_KEY_G = 71;
		public const int S_KEY_H = 72;
		public const int S_KEY_I = 73;
		public const int S_KEY_J = 74;
		public const int S_KEY_K = 75;
		public const int S_KEY_L = 76;
		public const int S_KEY_M = 77;
		public const int S_KEY_N = 78;
		public const int S_KEY_O = 79;
		public const int S_KEY_P = 80;
		public const int S_KEY_Q = 81;
		public const int S_KEY_R = 82;
		public const int S_KEY_S = 83;
		public const int S_KEY_T = 84;
		public const int S_KEY_U = 85;
		public const int S_KEY_V = 86;
		public const int S_KEY_W = 87;
		public const int S_KEY_X = 88;
		public const int S_KEY_Y = 89;
		public const int S_KEY_Z = 90;
		public const int S_KEY_LEFT_BRACKET = 91;  // [
		public const int S_KEY_BACKSLASH = 92;  // \
		public const int S_KEY_RIGHT_BRACKET = 93;  // ]
		public const int S_KEY_GRAVE_ACCENT = 96;  // `
		public const int S_KEY_WORLD_1 = 161;  // non-US #1
		public const int S_KEY_WORLD_2 = 162;  // non-US #2

		// Function keys
		public const int S_KEY_ESCAPE = 256;
		public const int S_KEY_ENTER = 257;
		public const int S_KEY_TAB = 258;
		public const int S_KEY_BACKSPACE = 259;
		public const int S_KEY_INSERT = 260;
		public const int S_KEY_DELETE = 261;
		public const int S_KEY_RIGHT = 262;
		public const int S_KEY_LEFT = 263;
		public const int S_KEY_DOWN = 264;
		public const int S_KEY_UP = 265;
		public const int S_KEY_PAGE_UP = 266;
		public const int S_KEY_PAGE_DOWN = 267;
		public const int S_KEY_HOME = 268;
		public const int S_KEY_END = 269;
		public const int S_KEY_CAPS_LOCK = 280;
		public const int S_KEY_SCROLL_LOCK = 281;
		public const int S_KEY_NUM_LOCK = 282;
		public const int S_KEY_PRINT_SCREEN = 283;
		public const int S_KEY_PAUSE = 284;
		public const int S_KEY_F1 = 290;
		public const int S_KEY_F2 = 291;
		public const int S_KEY_F3 = 292;
		public const int S_KEY_F4 = 293;
		public const int S_KEY_F5 = 294;
		public const int S_KEY_F6 = 295;
		public const int S_KEY_F7 = 296;
		public const int S_KEY_F8 = 297;
		public const int S_KEY_F9 = 298;
		public const int S_KEY_F10 = 299;
		public const int S_KEY_F11 = 300;
		public const int S_KEY_F12 = 301;
		public const int S_KEY_F13 = 302;
		public const int S_KEY_F14 = 303;
		public const int S_KEY_F15 = 304;
		public const int S_KEY_F16 = 305;
		public const int S_KEY_F17 = 306;
		public const int S_KEY_F18 = 307;
		public const int S_KEY_F19 = 308;
		public const int S_KEY_F20 = 309;
		public const int S_KEY_F21 = 310;
		public const int S_KEY_F22 = 311;
		public const int S_KEY_F23 = 312;
		public const int S_KEY_F24 = 313;
		public const int S_KEY_F25 = 314;
		public const int S_KEY_KP_0 = 320;
		public const int S_KEY_KP_1 = 321;
		public const int S_KEY_KP_2 = 322;
		public const int S_KEY_KP_3 = 323;
		public const int S_KEY_KP_4 = 324;
		public const int S_KEY_KP_5 = 325;
		public const int S_KEY_KP_6 = 326;
		public const int S_KEY_KP_7 = 327;
		public const int S_KEY_KP_8 = 328;
		public const int S_KEY_KP_9 = 329;
		public const int S_KEY_KP_DECIMAL = 330;
		public const int S_KEY_KP_DIVIDE = 331;
		public const int S_KEY_KP_MULTIPLY = 332;
		public const int S_KEY_KP_SUBTRACT = 333;
		public const int S_KEY_KP_ADD = 334;
		public const int S_KEY_KP_ENTER = 335;
		public const int S_KEY_KP_EQUAL = 336;
		public const int S_KEY_LEFT_SHIFT = 340;
		public const int S_KEY_LEFT_CONTROL = 341;
		public const int S_KEY_LEFT_ALT = 342;
		public const int S_KEY_LEFT_SUPER = 343;
		public const int S_KEY_RIGHT_SHIFT = 344;
		public const int S_KEY_RIGHT_CONTROL = 345;
		public const int S_KEY_RIGHT_ALT = 346;
		public const int S_KEY_RIGHT_SUPER = 347;
		public const int S_KEY_MENU = 348;
			   
		public const int S_KEY_LAST = S_KEY_MENU;
			   
		public const int S_MOD_SHIFT = 0x0001;
		public const int S_MOD_CONTROL = 0x0002;
		public const int S_MOD_ALT = 0x0004;
		public const int S_MOD_SUPER = 0x0008;
		public const int S_MOD_CAPS_LOCK = 0x0010;
		public const int S_MOD_NUM_LOCK = 0x0020;
			   
		public const int S_MOUSE_BUTTON_1 = 0;
		public const int S_MOUSE_BUTTON_2 = 1;
		public const int S_MOUSE_BUTTON_3 = 2;
		public const int S_MOUSE_BUTTON_4 = 3;
		public const int S_MOUSE_BUTTON_5 = 4;
		public const int S_MOUSE_BUTTON_6 = 5;
		public const int S_MOUSE_BUTTON_7 = 6;
		public const int S_MOUSE_BUTTON_8 = 7;
		public const int S_MOUSE_BUTTON_LAST = S_MOUSE_BUTTON_8;
		public const int S_MOUSE_BUTTON_LEFT = S_MOUSE_BUTTON_1;
		public const int S_MOUSE_BUTTON_RIGHT = S_MOUSE_BUTTON_2;
		public const int S_MOUSE_BUTTON_MIDDLE = S_MOUSE_BUTTON_3;

		public TransformComponent transform;

		public UInt32 uuid;

		internal static unsafe delegate*<NativeString, void> SQ_LOGInternal;
		internal static unsafe delegate*<Vector3> RandVectorInternal;
		internal static unsafe delegate*<TransformComponent, UInt32, void> UpdateTransform;
		internal static unsafe delegate*<UInt32, TransformComponent> GetTransform;
		internal static unsafe delegate*<int, bool> IsKeyDownInternal;
		internal static unsafe delegate*<int, bool> IsKeyUpInternal;
		internal static unsafe delegate*<int, bool> IsMousePressedInternal;

		/// <summary>
		/// SQ_LOG a string to the Square Engine console.
		/// </summary>
		/// <param name="str">Takes in a string.</param>

		public void Log(NativeString str)
		{
			SQ_LOGInternal(str);
		}

		public bool IsKeyDown(int key)
		{
			return IsKeyDownInternal(key);
		}

		public bool IsKeyUp(int key)
		{
			return IsKeyUpInternal(key);
		}

		public bool IsMousePressed(int button)
		{
			return IsMousePressedInternal(button);
		}

		/// <summary>
		/// Generate a random unit vector.
		/// </summary>
		/// <returns>Returns a Square Vector3</returns>
		public Vector3 RandVector()
		{
			return RandVectorInternal();
		}

		public void PreCreate(UInt32 uuid)
		{
			transform = new TransformComponent();
			this.uuid = uuid;

			transform = GetTransform(uuid);
		}

		public void Create()
		{
			UpdateTransform(transform, uuid);
		}

		public void PreUpdate()
		{
			transform = GetTransform(uuid);
		}

		public void Update()
		{
			UpdateTransform(transform, uuid);
		}
	}
}

#pragma once
#include "Node.h"
#include "dx2dxMacros.h"
#include "ActionManager.h"

NS_DX2DX
{
	class Scene
		: public Node
	{
	private:
		DISALLOW_COPY_AND_ASSIGN(Scene);

		bool _IsPause = false;

	public:
		Scene();
		virtual ~Scene();

	public:
		void AddChild(Node* const child) { Node::AddChild(child); }
		void AddChild(Node* const child, int zOrder) { Node::AddChild(child, zOrder); }
		void AddChild(Scene* const scene) = delete;

		static Scene* Create();

		void Init();
		void Update();
		void Exit();

		virtual void OnInit() {};
		virtual void OnUpdate() {};
		virtual void OnExit() {};

		virtual void OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
			bool *pbNoFurtherProcessing, void *pUserContext) {};

		void Pause() { _IsPause = true; }
		void Resume() { _IsPause = false; }
		bool IsPause() { return _IsPause; }
	};
}


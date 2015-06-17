#pragma once
#include "dx2dx.h"

NS_DX2DX
{
	class Label
	: public Node
	{
	private:
		DISALLOW_COPY_AND_ASSIGN(Label);
		Label(std::wstring fontFile, int size, std::wstring string, bool italic);
		~Label();

		LPD3DXFONT _d3dxFont;
		std::wstring _String;
		bool _Italic;
		DWORD _Format;

	protected:
		virtual void Draw(LPD3DXSPRITE d3dxSprite) override;

	public:
		static Label* Create(std::wstring fontFile, int size, std::wstring string, bool italic = false);

		void SetString(std::wstring string);
		void SetFormat(DWORD format);
	};
}

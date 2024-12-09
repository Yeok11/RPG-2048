#pragma once
#include "Define.h"

class Core
{
	DECLARE_SINGLE(Core);
public:
	bool Init(HWND _hwnd);
	void GameLoop();
	void CleanUp();
	void CoreRender() {
		MainRender();
	}
	void CoreUpdate() {
		MainUpdate();
	}
private:
	void MainUpdate();
	void MainRender();
	void CreateGDI();
public:
	const HWND& GetHwnd() const { return m_hWnd; }
	// 이름 바꾸기
	const HDC& GetMainDC() const { return m_hDC; }
	const HDC& GetBackDC() const { return m_hBackDC; }
	const HBRUSH& GetBrush(BRUSH_TYPE _eType)
	{
		return m_colorBrushs[(UINT)_eType];
	}
	const HPEN& GetPen(PEN_TYPE _eType)
	{
		return m_colorPens[(UINT)_eType];
	}

private:
	HBRUSH m_colorBrushs[(UINT)BRUSH_TYPE::END] = {};
	HPEN m_colorPens[(UINT)PEN_TYPE::END] = {};

	HWND m_hWnd;
	HDC  m_hDC; // Main DC
	HDC  m_hBackDC; // 백버퍼 DC
	HBITMAP m_hBackBit; // 백버퍼의 bitmap

};
#pragma once
// GameManager
//SAFE_DELETE()
// ���� �̱���(���̳��� �̱���)
// ���� �̱���
#include "Define.h"
//#include "Object.h"
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
	// �̸� �ٲٱ�
	const HDC& GetMainDC() const { return m_hDC; }
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
	HDC  m_hBackDC; // ����� DC
	HBITMAP m_hBackBit; // ������� bitmap

};
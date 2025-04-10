#pragma once
class Collider;
class Component;
class Object
{
public:
	Object();
	virtual ~Object();
public:
	virtual void Update() abstract;
	virtual void LateUpdate();
	virtual void Render(HDC _hdc) abstract;
	void ComponentRender(HDC _hdc);
	void ComponentInit(Vec2 _vSize, Vec2 _vOffsetPos);
public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetSize(Vec2 _vSize) { m_vSize = _vSize; }
	Vec2& GetPos() { return m_vPos; }
	Vec2& GetSize() { return m_vSize; }
public:
	virtual void EnterCollision(Collider* _other);
	virtual void StayCollision(Collider* _other);
	virtual void ExitCollision(Collider* _other);
	const bool& GetIsDead() const { return m_IsDie; }
	void SetDead() { m_IsDie = true; }
	void SetName(wstring _name) { m_name = _name; }
	const wstring& GetName() const { return m_name; }

private:
	bool m_IsDie;
	wstring m_name;
public:
	template<typename T>
	void AddComponent()
	{
		T* com = new T;
		com->SetOwner(this);
		m_vecComponents.push_back(com);
	}
	template<typename T>
	T* GetComponent()
	{
		T* component = nullptr;
		for (Component* com : m_vecComponents)
		{
			component = dynamic_cast<T*>(com);
			if (component)
				break;
		}
		return component;
	}
	template <typename T>
	const T* GetComponent() const {
		T* component = nullptr;
		for (Component* com : m_vecComponents)
		{
			component = dynamic_cast<T*>(com);
			if (component)
				break;
		}
		return component;
	}
	template <typename T>
	const bool TryGetComponent() const {
		if (GetComponent<T>() == nullptr) {
			return false;
		}
		return true;
	}
private:
	//POINT m_ptPos;
	//POINT m_ptSize;
	Vec2 m_vPos;
	Vec2 m_vSize;
	vector<Component*> m_vecComponents;
};


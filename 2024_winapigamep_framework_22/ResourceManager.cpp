#include "pch.h"
#include "ResourceManager.h"
#include "Core.h"
#include "Texture.h"
void ResourceManager::Init()
{
	::GetCurrentDirectory(255, m_resourcePath);
	wcscat_s(m_resourcePath, 255, L"\\Resource\\");
	
	wcout << m_resourcePath;
	//::SetWindowText(GET_SINGLE(Core)->GetHwnd(), m_resourcePath);

 	FMOD::System_Create(&m_pSoundSystem); // 시스템 생성 함수
	// 채널수, 사운드 모드
	if (m_pSoundSystem != nullptr)
		m_pSoundSystem->init((int)SOUND_CHANNEL::END, FMOD_INIT_NORMAL, nullptr);

}

void ResourceManager::TileInit(wstring _imgName, OBJ_TYPE _objType)
{
	if (TextureLoad(_objType) != nullptr) return;

	wstring path = m_resourcePath;
	path += L"Texture\\" + _imgName;

	Texture* pTex = new Texture;
	pTex->Load(path);
	objectTexture.insert({ _objType, pTex });

	cout << "OBJ_TYPE Load : " << (int)_objType << " 성공" << endl;
}

Texture* ResourceManager::TextureLoad(const wstring& _key, const wstring& _path)
{
	Texture* pTex = TextureFind(_key);
	if (nullptr != pTex)
		return pTex;

	// 없어요 최초입니다. 만들어주세요.
	// 1. 경로 설정
	wstring texpath = m_resourcePath;
	texpath += _path;
	
	// 2. Texture 만들어야죠?
	pTex = new Texture;
	pTex->Load(texpath);
	pTex->SetKey(_key);
	pTex->SetPath(texpath);
	m_mapTextures.insert({_key,pTex});
	return pTex;
}

Texture* ResourceManager::TextureLoad(const OBJ_TYPE _type)
{
	auto iter = objectTexture.find(_type);
	if (iter != objectTexture.end())
		return iter->second;

	cout << "Tile Init 안함. Error";

	return nullptr;
}

Texture* ResourceManager::TextureFind(const wstring& _key)
{
	auto iter = m_mapTextures.find(_key);
	if (iter != m_mapTextures.end())
		return iter->second;
	return nullptr;
}

void ResourceManager::Release()
{
	map<wstring, Texture*>::iterator iter;
	for (iter = m_mapTextures.begin(); iter != m_mapTextures.end(); ++iter)
		delete iter->second;
	m_mapTextures.clear();

	// SOUND
	map<wstring, tSoundInfo*>::iterator itersod;
	for (itersod = m_mapSounds.begin(); itersod != m_mapSounds.end(); ++itersod)
	{
		if (nullptr != itersod->second)
			delete itersod->second;
	}
	m_mapSounds.clear();

	map<OBJ_TYPE, Texture*>::iterator iterOBJ;
	for (iterOBJ = objectTexture.begin(); iterOBJ != objectTexture.end(); ++iterOBJ)
	{
		if (nullptr != iterOBJ->second)
			delete iterOBJ->second;
	}
	objectTexture.clear();

	// 다 쓰고 난 후 시스템 닫고 반환
	m_pSoundSystem->close();
	m_pSoundSystem->release();
}

void ResourceManager::LoadSound(const wstring& _key, const wstring& _path, bool _isLoop)
{
	if (FindSound(_key))
		return;
	wstring strFilePath = m_resourcePath;
	strFilePath += _path;

	// wstring to string
	std::string str;
	str.assign(strFilePath.begin(), strFilePath.end());

	// 루프할지 말지 결정
	FMOD_MODE eMode = FMOD_LOOP_NORMAL; // 반복 출력
	if (!_isLoop)
		eMode = FMOD_DEFAULT; // 사운드 1번만 출력

	tSoundInfo* ptSound = new tSoundInfo;
	ptSound->IsLoop = _isLoop;
	// 사운드 객체를 만드는 것은 system임.
							//파일경로,  FMOD_MODE, NULL, &sound
	m_pSoundSystem->createSound(str.c_str(), eMode, nullptr, &ptSound->pSound);
	m_mapSounds.insert({ _key, ptSound });
}

void ResourceManager::Play(const wstring& _key)
{
	tSoundInfo* ptSound = FindSound(_key);
	if (!ptSound)
		return;
	m_pSoundSystem->update(); // play할때 update를 주기적으로 호출해야 사운드가 정지되지 않음.
	SOUND_CHANNEL eChannel = SOUND_CHANNEL::BGM;
	if (!ptSound->IsLoop)
		eChannel = SOUND_CHANNEL::EFFECT;
	// 사운드 재생 함수. &channel로 어떤 채널을 통해 재생되는지 포인터 넘김
	m_pSoundSystem->playSound(ptSound->pSound, nullptr, false, &m_pChannel[(UINT)eChannel]);
}

void ResourceManager::Stop(SOUND_CHANNEL _channel)
{
	m_pChannel[(UINT)_channel]->stop();
}

void ResourceManager::Volume(SOUND_CHANNEL _channel, float _vol)
{
	// 0.0 ~ 1.0 볼륨 조절
	m_pChannel[(UINT)_channel]->setVolume(_vol);
}

void ResourceManager::Pause(SOUND_CHANNEL _channel, bool _ispause)
{
	// bool값이 true면 일시정지. 단, 이 함수를 쓰려면 Createsound할때 
// FMOD_MODE가 FMOD_LOOP_NORMAL 이어야 함.
	m_pChannel[(UINT)_channel]->setPaused(_ispause);
}

tSoundInfo* ResourceManager::FindSound(const wstring& _key)
{
	map<wstring, tSoundInfo*>::iterator iter = m_mapSounds.find(_key);

	if (iter == m_mapSounds.end())
		return nullptr;
	return iter->second;
}

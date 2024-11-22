#include "pch.h"
#include "AudioSource.h"

AudioSource::AudioSource()
{
}

AudioSource::~AudioSource()
{
}

void AudioSource::LoadSound(const wstring& _key, const wstring& _path, bool _isLoop)
{
	GET_SINGLE(ResourceManager)->LoadSound(_key, _path, _isLoop);
}

void AudioSource::Play(const wstring& _key)
{
	GET_SINGLE(ResourceManager)->Play(_key);
}

void AudioSource::Stop(SOUND_CHANNEL _channel)
{
	GET_SINGLE(ResourceManager)->Stop(_channel);
}

void AudioSource::SetVolume(SOUND_CHANNEL _channel, float _vol)
{
	GET_SINGLE(ResourceManager)->Volume(_channel, _vol);
}

void AudioSource::Pause(SOUND_CHANNEL _channel, bool _ispause)
{
	GET_SINGLE(ResourceManager)->Pause(_channel, _ispause);
}

void AudioSource::LateUpdate()
{
}

void AudioSource::Render(HDC _hdc)
{
}

#pragma once
class ScoreManager
{
	DECLARE_SINGLE(ScoreManager);
private:
	int highScore = 0;
	int curScore = 0;

public:
	void Init()
	{
		curScore = 0;
	}

	void SetValue(int _value)
	{
		curScore = _value;

		if (highScore < _value) highScore = _value;
	}

	int GetScore() { return curScore; }
	int GetHighScore() { return highScore; }
};


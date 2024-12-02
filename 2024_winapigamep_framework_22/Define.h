#pragma once
// 매크로

#define DECLARE_SINGLE(type)	 \
private:						\
	type() {}					\
public:							\
	static type* GetInst()	\
	{							\
		static type m_pInst;	\
		return &m_pInst;		\
	}							\

#define GET_SINGLE(type) type::GetInst()
#define fDT GET_SINGLE(TimeManager)->GetDT()

#define KEY_CHECK(key, state) InputManager::GetInst()->GetKey(key) == state
#define GET_KEYNONE(key) KEY_CHECK(key, KEY_STATE::NONE)
#define GET_KEYUP(key) KEY_CHECK(key, KEY_STATE::UP)
#define GET_KEYDOWN(key) KEY_CHECK(key, KEY_STATE::DOWN)
#define GET_KEY(key) KEY_CHECK(key, KEY_STATE::PRESS)
#define GET_MOUSEPOS GET_SINGLE(InputManager)->GetMousePos()
// Render 매크로
#define RECT_RENDER(hdc, posx, posy, sizex, sizey) Rectangle(hdc, (int)(posx-sizex/2), (int)(posy-sizey/2), (int)(posx+sizex/2), (int)(posy+sizey/2))
#define ELLIPSE_RENDER(hdc, posx, posy, sizex, sizey) Ellipse(hdc, (int)(posx-sizex/2), (int)(posy-sizey/2), (int)(posx+sizex/2), (int)(posy+sizey/2))
#define RECT_MAKE(posx, posy, sizex, sizey) {posx-sizex/2, posy-sizey/2, posx+sizex/2, posy+sizey/2}

//내가 만든 매크로
#define MOUSE_ON_OBJECT(_size, _pos) ((_pos.x - _size.x < GET_MOUSEPOS.x) && (_pos.x + _size.x > GET_MOUSEPOS.x) && (_pos.y - _size.y < GET_MOUSEPOS.y) && (_pos.y + _size.y > GET_MOUSEPOS.y))

//// Easing
//#define Liner(t) (t)
//
//// Quad
//#define QuadIn(t) (t * t)
//#define QuadOut(t) (t * (2 - t))
//#define QuadInOut(t) (t < 0.5 ? 2 * t * t : -1 + (4 - 2 * t) * t)
//
//// Cubic
//#define CubicIn(t) (t * t * t)
//#define CubicOut(t) ((--t) * t * t + 1)
//#define CubicInOut(t) (t < 0.5 ? 4 * t * t * t : (t - 1) * (2 * t - 2) * (2 * t - 2) + 1)
//
//// Sine
//#define SineIn(t) (1 - std::cos(t * M_PI_2))
//#define SineOut(t) (std::sin(t * M_PI_2))
//#define SineInOut(t) (0.5 * (1 - std::cos(M_PI * t)))
//
//// Another
//#define BounceOut(t)                   \
//    if (t < 1 / 2.75f)                 \
//        return 7.5625f * t * t;        \
//    else if (t < 2 / 2.75f)            \
//        return 7.5625f * (t -= 1.5f / 2.75f) * t + 0.75f; \
//    else if (t < 2.5 / 2.75f)          \
//        return 7.5625f * (t -= 2.25f / 2.75f) * t + 0.9375f; \
//    else                               \
//        return 7.5625f * (t -= 2.625f / 2.75f) * t + 0.984375f;
//
//#define ElasticOut(t)                            \
//    if (t == 0)                                  \
//        return 0;                                \
//    else if (t == 1)                             \
//        return 1;                                \
//    else                                         \
//        return std::pow(2, -10 * t) * std::sin((t - 0.075) * (2 * M_PI) / 0.3) + 1;

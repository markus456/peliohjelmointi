#ifndef UI_HEADER_GUARD
#define UI_HEADER_GUARD
class Button{
protected:
	float _x,_y,_w,_h;
public:
	Button();
	Button(float,float,float,float);
	virtual void render();
	virtual void onClick(float,float);
};
#endif
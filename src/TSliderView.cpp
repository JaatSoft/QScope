/*
 *  TSliderView.cpp - Horizontal slider view
 *
 *  Created by Robert Polic, modified by Christian Bauer
 */

#include <InterfaceKit.h>

#include "TSliderView.h"


// Background color
const rgb_color fill_color = {216, 216, 216, 0};


// Knob image
#define KNOB_WIDTH		 (18 - 1)
#define KNOB_HEIGHT		 (16 - 1)

unsigned char knob[] = {
0x1b,0xc,0xc,0xc,0xc,0xc,0xd,0xc,0xc,0xc,0xc,0xc,0xc,0xc,0xd,
0xc,0x1b,0x1b,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0xc,0x1d,0x1d,0x1d,0x1d,0x1d,
0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,0x0,0x1b,0x3f,0x3f,0x3f,
0x3f,0x3f,0x3f,0xc,0x1d,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,
0x3f,0x3f,0x3f,0x11,0x0,0xf,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0xc,0x1d,0x3f,
0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,0x18,0x11,0x0,0xf,
0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0xc,0x1d,0x3f,0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,
0x1d,0x1d,0x1d,0x1d,0x1d,0x18,0x11,0x0,0xf,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,
0xc,0x1d,0x3f,0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,0x18,
0x11,0x0,0xf,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0xc,0x1d,0x3f,0x1d,0x1d,0x1d,
0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,0x18,0x11,0x0,0xf,0x3f,0x3f,0x3f,
0x3f,0x3f,0x3f,0xc,0x1d,0x3f,0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,
0x1d,0x1d,0x18,0x11,0x0,0xf,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0xc,0x1d,0x3f,
0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,0x18,0x11,0x0,0xf,
0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0xc,0x1d,0x3f,0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,
0x1d,0x1d,0x1d,0x1d,0x1b,0x18,0x11,0x0,0xf,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,
0xc,0x1d,0x3f,0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,0x3f,0x18,
0x11,0x0,0xf,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0xc,0x1d,0x3f,0x1d,0x1d,0x1d,
0x1d,0x1d,0x1d,0x1d,0x1d,0x1d,0x1b,0x3f,0x18,0x11,0x0,0xf,0x3f,0x3f,0x3f,
0x3f,0x3f,0x3f,0xc,0x1d,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,
0x18,0x18,0x18,0x11,0x0,0xf,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0xc,0x1d,0x11,
0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x0,0xf,
0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x1b,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf,0xf,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,
0x1b,0xf,0xf,0xf,0xf,0xf,0xf,0xf,0xf,0xf,0xf,0xf,0xf,0xf,0xf,
0xf,0xf,0x1b,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f
};


/*
 *  Slider constructor
 */

TSliderView::TSliderView(BRect rect, char *name, float val, slider_func func, void *arg)
			:BView(rect, name, B_FOLLOW_ALL, B_WILL_DRAW)
{
	BRect	r;

	fValue = val;
	callback = func;
	callback_arg = arg;

	// load in our canned slider knob bitmap
	r.Set(0, 0, ((KNOB_WIDTH + 7) & 0xfff8) - 1, KNOB_HEIGHT);
	fKnob = new BBitmap(r, B_COLOR_8_BIT);
	fKnob->SetBits((char*)knob, fKnob->BitsLength(), 0, B_COLOR_8_BIT);

	// create our offscreen drawing environment
	r = Bounds();
	back_width = r.Width();
	fSlider = new BBitmap(r, B_COLOR_8_BIT, TRUE);
	fSlider->AddChild(fOffView = new BView(r, "", B_FOLLOW_ALL, B_WILL_DRAW));
}


/*
 *  Slider destructor
 */

TSliderView::~TSliderView()
{
	delete fSlider;
	delete fKnob;
}


/*
 *  Redraw slider
 */

void TSliderView::Draw(BRect where)
{
	DrawSlider();
}


/*
 *  Slider was clicked
 */

void TSliderView::MouseDown(BPoint thePoint)
{
	uint32	buttons;
	float	old_value;
	float	temp;
	BPoint	where;
	BRect	r;

	r.left = ((back_width - KNOB_WIDTH - 4.0) * fValue) + 2.0;
	r.top = 0.0;
	r.right = r.left + KNOB_WIDTH;
	r.bottom = KNOB_HEIGHT;

	if (!r.Contains(thePoint)) {
		temp = (thePoint.x / (back_width - KNOB_WIDTH - 4.0)) -
							 ((KNOB_WIDTH / 2.0) / back_width);
		if (temp < 0.00)
			temp = 0.00;
		if (temp > 1.00)
			temp = 1.00;
		if (temp != fValue)
			SetValue(temp);
	}
	old_value = fValue;

	do {
		GetMouse(&where, &buttons);
		temp = old_value + ((where.x - thePoint.x) /
							(back_width - KNOB_WIDTH - 2.0));
		if (temp < 0.00)
			temp = 0.00;
		if (temp > 1.00)
			temp = 1.00;
		if (temp != fValue) {
			SetValue(temp);
		}
		Window()->Unlock();
		callback(temp, callback_arg);
		snooze(20000.0);	// be a good citizen
		Window()->Lock();
	} while (buttons);
}


/*
 *  Draw slider
 */

void TSliderView::DrawSlider()
{
	BRect	sr;
	BRect	dr;

	fSlider->Lock();
	sr = fOffView->Bounds();

	// slider background
	fOffView->SetHighColor(fill_color);
	fOffView->FillRect(sr);
	fOffView->SetHighColor(176, 176, 176);
	fOffView->StrokeLine(BPoint(0, 5), BPoint(0, 5));
	fOffView->StrokeLine(BPoint(0, 10), BPoint(0, 10));
	fOffView->StrokeLine(BPoint(back_width, 5), BPoint(back_width, 5));
	fOffView->SetHighColor(255, 255, 255);
	fOffView->StrokeLine(BPoint(1, 10), BPoint(back_width, 10));
	fOffView->StrokeLine(BPoint(back_width, 9), BPoint(back_width, 6));
	fOffView->SetHighColor(144, 144, 144);
	fOffView->StrokeLine(BPoint(0, 6), BPoint (0, 9));
	fOffView->StrokeLine(BPoint(1, 5), BPoint(back_width - 1, 5));
	fOffView->SetHighColor(0, 0, 0);
	fOffView->StrokeLine(BPoint(1, 6), BPoint(back_width - 1, 6));
	fOffView->StrokeLine(BPoint(1, 7), BPoint(back_width - 1, 7));
	fOffView->StrokeLine(BPoint(1, 8), BPoint(1, 9));
	fOffView->StrokeLine(BPoint(back_width - 1, 8), BPoint(back_width - 1, 9));
	fOffView->SetHighColor(64, 64, 64);
	sr.Set(2, 8, back_width - 2, 9);
	fOffView->FillRect(sr);

	// knob
	sr.Set(0, 0, KNOB_WIDTH, KNOB_HEIGHT);
	dr.left = ((back_width - KNOB_WIDTH - 4.0) * fValue) + 2.0;
	dr.top = 0;
	dr.right = dr.left + KNOB_WIDTH;
	dr.bottom = dr.top + KNOB_HEIGHT;
	fOffView->DrawBitmap(fKnob, sr, dr);
	fOffView->SetHighColor(0, 0, 0);

	fOffView->Sync();	// make sure offscreen drawing completes

	// copy offscreen to screen
	DrawBitmap(fSlider, BPoint(0, 0));

	fSlider->Unlock();
}


/*
 *  Set slider value
 */

void TSliderView::SetValue(float value)
{
	fValue = value;
	DrawSlider();
}


/*
 *  Get slider value
 */

float TSliderView::Value()
{
	return (fValue);
}
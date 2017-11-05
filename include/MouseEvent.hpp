#ifndef GILVAPAINT_MOUSEEVENT_HPP
#define GILVAPAINT_MOUSEEVENT_HPP

namespace GilvaPaint {

  class MouseEvent {
  private:
  public:
	MouseEvent() =default;
	~MouseEvent() noexcept {}

	virtual void onMove(Uint32 timestamp, Sint32 x, Sint32 y, Sint32 xrel, Sint32 yrel) noexcept =0;
	virtual void onButtonDown(Uint32 timestamp, Sint32 x, Sint32 y, Uint8 button)       noexcept =0;
	virtual void onButtonUp(Uint32 timestamp, Sint32 x, Sint32 y, Uint8 button)         noexcept =0;
	virtual void onWheel(Uint32 timestamp, Sint32 scroll)                               noexcept =0;
  };

}

#endif //GILVAPAINT_MOUSEEVENT_HPP

#include "Bindable.h"

ID3D11DeviceContext* Bindable::GetDeviceContext(Renderer& renderer) noexcept
{
	return renderer.device_context.Get();
}

ID3D11Device* Bindable::GetDevice(Renderer& renderer) noexcept
{
	return renderer.device.Get();
}

#pragma once

#include <string>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/ref_counted.hpp>


namespace godot
{
	class EventDeathWatch : public RefCounted
	{
		GDCLASS(EventDeathWatch, RefCounted);
	public:
		EventDeathWatch();
		~EventDeathWatch() override;

		static bool watch(Object *p_object, const Callable& callable);
	private:
		struct Binding;

		static void *_binding_token();
		static const GDExtensionInstanceBindingCallbacks *_bind_callbacks();
		static void _bind_methods();

		static void *create_callback(void *p_token, void *p_instance);
		static void free_callback(void *p_token, void *p_instance, void *p_binding);
		static Callable &EventDeathWatch::callback_trampoline();
	};
}

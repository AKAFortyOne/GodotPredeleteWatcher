#pragma once

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <string>
#include <unordered_map>

namespace godot
{
	class PredeleteWatcher : public RefCounted
	{
		GDCLASS(PredeleteWatcher, RefCounted);
	public:
		PredeleteWatcher();
		~PredeleteWatcher() override;

		static bool watch(Object *p_target, const Callable& callable);
	private:
		struct Binding;

		static void _bind_methods();

		static void *_instance_binding_token();
		static const GDExtensionInstanceBindingCallbacks *_instance_binding_callbacks();

		static void *create_callback(void *p_token, void *p_instance);
		static void free_callback(void *p_token, void *p_instance, void *p_binding);
	};
}

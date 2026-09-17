#include "EventDeathWatch.h"

#include "godot_cpp/classes/object.hpp"

using namespace godot;

struct EventDeathWatch::Binding
{
	GDObjectInstanceID id;
	Callable callable;
};

EventDeathWatch::EventDeathWatch()
{

}

EventDeathWatch::~EventDeathWatch()
{

}

void *EventDeathWatch::_binding_token()
{
	static constexpr const char *token = "FortyOne.SourceGenerator.EventDeathWatch";
	return const_cast<char*>(token);
}

const GDExtensionInstanceBindingCallbacks *EventDeathWatch::_bind_callbacks()
{
	static GDExtensionInstanceBindingCallbacks callbacks = {
		create_callback,
		free_callback,
		nullptr
	};
	return &callbacks;
}

void EventDeathWatch::_bind_methods()
{
	ClassDB::bind_static_method("EventDeathWatch", D_METHOD("watch", "target", "callable"), &EventDeathWatch::watch);
}

void *EventDeathWatch::create_callback(void *p_token, void *p_instance)
{
	const GDObjectInstanceID id = gdextension_interface::object_get_instance_id(p_instance);
	Binding* binding = memnew(EventDeathWatch::Binding);
	binding->id = id;
	binding->callable = callback_trampoline();
	return binding;
}

void EventDeathWatch::free_callback(void *p_token, void *p_instance, void *p_binding)
{
	auto binding = static_cast<Binding*>(p_binding);
	if (binding != nullptr)
	{
		binding->callable.call(binding->id);
		memdelete(binding);
	}
}

Callable &EventDeathWatch::callback_trampoline()
{
	static Callable *callable_cache = nullptr;
	if (callable_cache == nullptr) callable_cache = memnew(Callable);
	return *callable_cache;
}

bool EventDeathWatch::watch(Object *p_object, const Callable &callable)
{
	if (!p_object) return false;
	GodotObject *owner = p_object->_owner;
	auto exist_callbacks = static_cast<Binding*>(gdextension_interface::object_get_instance_binding(owner, _binding_token(), nullptr));
	if (exist_callbacks != nullptr) return (exist_callbacks->callable == callable);

	Callable &callable_cache = callback_trampoline();
	callable_cache = callable;
	gdextension_interface::object_get_instance_binding(owner, _binding_token(), _bind_callbacks());
	callable_cache = Callable();
	return true;
}

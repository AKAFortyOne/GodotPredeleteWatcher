#include "PredeleteWatcher.h"

#include <unordered_set>

#include "godot_cpp/classes/object.hpp"

using namespace godot;

struct PredeleteWatcher::Binding
{
	struct CallableHash
	{
		std::size_t operator()(const Callable &c) const
		{
			return static_cast<std::size_t>(c.hash());
		}
	};

	GDObjectInstanceID instance_id;
	std::unordered_set<Callable, CallableHash> callables;
};

PredeleteWatcher::PredeleteWatcher()
{}

PredeleteWatcher::~PredeleteWatcher()
{}

void PredeleteWatcher::_bind_methods()
{
	ClassDB::bind_static_method("PredeleteWatcher", D_METHOD("watch", "target", "callable"), &PredeleteWatcher::watch);
}

void *PredeleteWatcher::_instance_binding_token()
{
	static constexpr const char *token = "FortyOne.SourceGenerator.PredeleteWatcher";
	return const_cast<char*>(token);
}

const GDExtensionInstanceBindingCallbacks *PredeleteWatcher::_instance_binding_callbacks()
{
	static GDExtensionInstanceBindingCallbacks callbacks = {
		create_callback,
		free_callback,
		nullptr
	};
	return &callbacks;
}

void *PredeleteWatcher::create_callback(void *p_token, void *p_instance)
{
	Binding* binding = memnew(PredeleteWatcher::Binding);
	return binding;
}

void PredeleteWatcher::free_callback(void *p_token, void *p_instance, void *p_binding)
{
	auto binding = static_cast<Binding*>(p_binding);
	if (binding == nullptr) return;

	for (auto &callable: binding->callables)
	{
		callable.call(binding->instance_id);
	}
	memdelete(binding);
}

bool PredeleteWatcher::watch(Object *p_target, const Callable &callable)
{
	if (!p_target) return false;
	GodotObject *instance = p_target->_owner;

	auto binding = static_cast<Binding*>(gdextension_interface::object_get_instance_binding(instance, _instance_binding_token(), _instance_binding_callbacks()));
	if (binding == nullptr) return false;

	binding->instance_id = p_target->get_instance_id();

	auto &callables = binding->callables;
	callables.insert(callable);

	return true;
}

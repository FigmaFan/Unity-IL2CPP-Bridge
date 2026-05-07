# Unity IL2CPP Bridge

[![Stars][stars-shield]][stars-url] [![Forks][forks-shield]][forks-url] [![Contributors][contributors-shield]][contributors-url] [![License][license-shield]][license-url]

## About

**Unity IL2CPP Bridge** is a header-only C++17 library for resolving Unity IL2CPP metadata, exported runtime functions, and common UnityEngine APIs at runtime.

The library is designed for projects that need to interact with IL2CPP-based Unity applications without relying on hardcoded offsets for APIs that are exposed through IL2CPP exports. It can dynamically resolve assemblies, classes, methods, fields, strings, arrays, enums, and selected UnityEngine types.

The current implementation lives in `il2cpp_resolver.hpp` and is currently version **v2.9**.

Most APIs return a strongly typed `Result<T>` object, while pure status operations return `Il2CppStatus`. This makes failures explicit and avoids ambiguous null-only error handling.

`il2cpp::init()` waits briefly for `GameAssembly.dll`, resolves all required IL2CPP exports, and binds optional helpers such as `il2cpp_string_new`, `il2cpp_resolve_icall`, thread introspection functions, and other runtime utilities when available.

---

## Features

* **Runtime export binding** from `GameAssembly.dll`, including optional waiting until the module is loaded.
* **RAII thread attachment** via `ThreadScope`, with thread-local nested scope tracking.
* **Assembly and class resolution** by namespace, class name, and assembly name.
* **Method lookup** by name, optional parameter count, or managed parameter type names.
* **Overload disambiguation** through `il2cpp_type_get_name` and method iteration.
* **Internal call resolution** through `il2cpp::resolve_icall`.
* **Managed method invocation** through `call_function<Ret>(...)`.
* **Field helpers** for instance fields, static fields, and raw field offsets.
* **Object allocation** through `create_object`, with optional constructor invocation.
* **String helpers** for creating and converting managed `System.String` values.
* **Array helpers** for 1D IL2CPP arrays, including layout access, allocation, iteration, and managed fallbacks.
* **Enum helpers** for cached enum literal enumeration, value lookup, and name lookup.
* **System.Type helpers** through `il2cpp::Type::GetType`.
* **UnityEngine helpers** for common types and APIs such as:

  * `Object`
  * `Component`
  * `GameObject`
  * `Transform`
  * `Camera`
  * `Physics`
  * `PhysicsScene`
  * `Vector3`
  * `Quaternion`
  * `Ray`
  * `RaycastHit`

---

## Built With

* C++17
* Windows API / Win32
* MSVC recommended

---

## Getting Started

### Requirements

* Windows
* C++17-compatible compiler
* IL2CPP Unity application with `GameAssembly.dll`
* MSVC is recommended

### Installation

Include the resolver header:

```cpp
#include "il2cpp_resolver.hpp"
```

Initialize the bridge early, for example from your DLL initialization code:

```cpp
const auto status = il2cpp::init();

if (status != Il2CppStatus::OK) {
    // Log via to_string(status) and handle the failure.
}
```

You can override the target module name before including the header:

```cpp
#define IL2CPP_GAMEASSEMBLY_FILE "GameAssembly.dll"
#include "il2cpp_resolver.hpp"
```

The header also defines:

```cpp
#define IL2CPP_FALLBACK_ASSEMBLY "Assembly-CSharp"
```

This can be used by your own code as a default assembly fallback.

---

## Usage

## Result and Status Handling

Most APIs return `Result<T>`:

```cpp
auto method = il2cpp::get_method(
    "MyGame.Logic",
    "Game",
    "get_Player",
    "Assembly-CSharp"
);

if (!method) {
    // method.status contains the exact failure reason.
    // Use to_string(method.status) for logging.
    return;
}

auto* method_info = method.value;
```

`Result<void>` only carries a status value.

```cpp
auto result = il2cpp::call_function<void>(method.value, instance);

if (!result) {
    // result.status
}
```

Every `Il2CppStatus` value can be converted to a readable string:

```cpp
LOG("IL2CPP status: ", to_string(status));
```

---

## Thread Attachment

Most public APIs that touch IL2CPP create a `ThreadScope` internally.

If you call raw IL2CPP exports yourself, wrap that code in `il2cpp::ThreadScope`:

```cpp
{
    il2cpp::ThreadScope scope;

    // Direct IL2CPP export calls are safe here.
}
```

You can check whether the current thread is attached:

```cpp
if (il2cpp::is_current_thread_attached()) {
    // Current thread is already known to IL2CPP.
}
```

Nested scopes are tracked per thread, so repeated `ThreadScope` usage is safe.

---

## Assemblies, Classes, and Objects

### Resolve a class

```cpp
auto klass = il2cpp::find_class(
    "MyGame.Logic",
    "Game",
    "Assembly-CSharp"
);

if (!klass) {
    // klass.status contains the failure reason.
}
```

### Resolve the class of an existing object

```cpp
auto klass = il2cpp::get_object_class(some_object);

// Alias:
auto klass2 = il2cpp::object_get_class(some_object);
```

---

## Method Resolution

### Resolve by name and optional parameter count

If `param_count` is omitted, the resolver tries arities from `0` to `16` until `il2cpp_class_get_method_from_name` succeeds.

```cpp
auto getter = il2cpp::get_method(
    "MyGame.Logic",
    "Game",
    "get_Player",
    "Assembly-CSharp"
);
```

With explicit parameter count:

```cpp
auto method = il2cpp::get_method(
    "MyGame.Logic",
    "Player",
    "AddXp",
    "Assembly-CSharp",
    2
);
```

If you already have an `il2cppClass*`:

```cpp
auto method = il2cpp::get_method(
    klass.value,
    "Foo",
    std::nullopt
);
```

### Resolve overloads by managed parameter type names

Use this when multiple overloads have the same name or when parameter count alone is not precise enough.

Type names must match the names returned by `il2cpp_type_get_name`, for example:

* `System.Int32`
* `System.Single`
* `System.Boolean`
* `System.String`
* `UnityEngine.Vector3`
* `UnityEngine.Component&`

Trailing spaces and reference suffixes are normalized internally.

```cpp
auto method = il2cpp::get_method(
    "System",
    "String",
    "Substring",
    "mscorlib",
    std::vector<std::string>{
        "System.Int32",
        "System.Int32"
    }
);
```

Convenience overload:

```cpp
auto method = il2cpp::get_method(
    "System",
    "String",
    "Substring",
    "mscorlib",
    { "System.Int32", "System.Int32" }
);
```

---

## Internal Calls

`resolve_icall` resolves native Unity internal calls by name:

```cpp
auto resolved = il2cpp::resolve_icall(
    "UnityEngine.Transform::get_position_Injected"
);

if (resolved) {
    void* fn = resolved.value;

    // Cast to the exact native signature before calling.
}
```

Always cast internal calls according to the real Unity signature for your target version.

---

## Calling Managed Methods

`call_function<Ret>(methodInfo, args...)` casts `m_pMethodPointer` to:

```cpp
Ret(__fastcall*)(Args...)
```

and invokes it.

For instance methods, pass the object instance as the first argument.

> Note: Some Unity versions and generated methods append `MethodInfo*` to the native signature. `call_function` does not insert it automatically. Match the ABI expected by your target player.

### Static method

```cpp
auto method = il2cpp::get_method(
    "UnityEngine",
    "Time",
    "get_timeScale",
    "UnityEngine.CoreModule",
    0
);

if (method) {
    auto result = il2cpp::call_function<float>(method.value);

    if (result) {
        float time_scale = result.value;
    }
}
```

### Instance method

```cpp
void* player = /* Il2CppObject* */;

auto method = il2cpp::get_method(
    "MyGame",
    "Player",
    "GainXp",
    "Assembly-CSharp",
    2
);

if (method) {
    auto result = il2cpp::call_function<void>(
        method.value,
        player,
        100.0f,
        1
    );

    if (!result) {
        // result.status
    }
}
```

---

## Fields and Offsets

### Instance fields

```cpp
auto level = il2cpp::get_object_field_value<int>(
    instance,
    "MyGame",
    "Player",
    "m_Level",
    "Assembly-CSharp"
);
```

If you already have the declaring class:

```cpp
auto level = il2cpp::get_object_field_value<int>(
    instance,
    klass.value,
    "m_Level"
);
```

Set an instance field:

```cpp
auto status = il2cpp::set_object_field_value<int>(
    instance,
    "MyGame",
    "Player",
    "m_Level",
    10,
    "Assembly-CSharp"
);
```

### Static fields

```cpp
auto instance = il2cpp::get_static_field_value<void*>(
    klass.value,
    "instance"
);
```

```cpp
auto status = il2cpp::set_static_field_value<int>(
    klass.value,
    "SomeStaticCounter",
    42
);
```

### Raw field offsets

```cpp
auto offset = il2cpp::get_field_offset(
    "MyGame",
    "Player",
    "m_Level",
    "Assembly-CSharp"
);

if (offset) {
    int byte_offset = offset.value;
}
```

---

## Object Allocation

Allocate an object from an existing class pointer:

```cpp
auto object = il2cpp::create_object(klass.value);
```

By default, this allocates the object but does not call a constructor.

Allocate by name and optionally call a constructor:

```cpp
auto player = il2cpp::create_object<void*>(
    "MyGame",
    "Player",
    "Assembly-CSharp",
    initialXp,
    teamId
);
```

Constructor invocation resolves `.ctor` by matching argument count.

---

## Strings

`il2cpp::String` provides helpers for managed `System.String` values.

### Create a managed string

```cpp
auto str = il2cpp::String::CreateNewString("hello");

if (str) {
    void* system_string = str.value;
}
```

`CreateNewString` rejects empty input and returns `InvalidArgs`.

### Convert a managed string to `std::string`

```cpp
std::string value = il2cpp::String::convert_to_std_string(system_string);
```

String conversion resolves the backing fields of `System.String` in `mscorlib` or `System.Private.CoreLib`.

---

## Arrays

`il2cpp::Array` provides low-level helpers for 1D IL2CPP arrays.

The layout helpers access the standard IL2CPP array header:

```cpp
klass
monitor
bounds
max_length
items...
```

Prefer `length`, `get`, and `set` for blittable element types.

### Read elements

```cpp
auto len = il2cpp::Array::length(array);

if (len) {
    for (size_t i = 0; i < len.value; ++i) {
        auto element = il2cpp::Array::get<void*>(array, i);

        if (element) {
            void* object = element.value;
        }
    }
}
```

Reference types can use:

```cpp
auto object = il2cpp::Array::get_ref(array, 0);
```

### Write elements

```cpp
auto status = il2cpp::Array::set<int>(array, 0, 123);
```

### Access raw data

```cpp
auto* items = il2cpp::Array::data<void*>(array);
```

### Allocate a managed 1D array

Using an existing element class:

```cpp
auto array = il2cpp::Array::create_1d<void*>(
    elementClass,
    64
);
```

Resolve the element class by name:

```cpp
auto array = il2cpp::Array::create_1d<void*>(
    "System",
    "Object",
    "mscorlib",
    8
);
```

### Managed fallbacks

The managed fallback helpers call `System.Array` methods and try both `mscorlib` and `System.Private.CoreLib`.

```cpp
auto len = il2cpp::Array::length_managed(array);
auto value = il2cpp::Array::get_managed<void*>(array, 0LL);
```

---

## Enums

`il2cpp::Enum` can enumerate enum fields and cache the result.

```cpp
auto entries = il2cpp::Enum::get_entries(
    "MyGame",
    "ItemRarity",
    "Assembly-CSharp"
);

if (entries) {
    for (const auto& entry : *entries.value) {
        // entry.value
        // entry.name
    }
}
```

Lookup enum name by value:

```cpp
auto name = il2cpp::Enum::name_of(
    "MyGame",
    "ItemRarity",
    "Assembly-CSharp",
    3
);
```

Lookup enum value by name:

```cpp
auto value = il2cpp::Enum::value_of(
    "MyGame",
    "ItemRarity",
    "Assembly-CSharp",
    "Legendary"
);
```

---

## System.Type

Use `il2cpp::Type::GetType` to resolve managed runtime type objects.

```cpp
auto type = il2cpp::Type::GetType(
    "MyGame.Player, Assembly-CSharp"
);

if (type) {
    void* runtime_type = type.value;
}
```

You can also pass an existing managed `System.String`.

```cpp
auto type = il2cpp::Type::GetType(system_string);
```

---

## UnityEngine Helpers

`il2cpp::UnityEngine` contains convenience wrappers for common UnityEngine APIs.

The helpers internally try the relevant Unity assemblies, such as:

* `UnityEngine.CoreModule`
* `UnityEngine`
* `UnityEngine.PhysicsModule`

### Object names

```cpp
auto name = il2cpp::UnityEngine::Object::get_name(unity_object);

if (name) {
    std::cout << name.value << "\n";
}
```

A compatibility wrapper may also be available:

```cpp
auto name = il2cpp::UnityEngine::get_name(unity_object);
```

### Find objects by type

```cpp
auto type = il2cpp::Type::GetType(
    "UnityEngine.GameObject, UnityEngine.CoreModule"
);

if (type) {
    auto objects = il2cpp::UnityEngine::Object::FindObjectsByType(
        type.value,
        il2cpp::UnityEngine::FindObjectsInactive::Include,
        il2cpp::UnityEngine::FindObjectsSortMode::None
    );
}
```

### Transform access

```cpp
auto transform = il2cpp::UnityEngine::GameObject::get_transform(game_object);

if (transform) {
    auto position = il2cpp::UnityEngine::Transform::get_position(transform.value);

    if (position) {
        auto pos = position.value;
    }
}
```

For `Component` or `MonoBehaviour` derived objects:

```cpp
auto transform = il2cpp::UnityEngine::Component::get_transform(component);
```

### Camera projection

```cpp
auto camera = il2cpp::UnityEngine::Camera::get_main();

if (camera) {
    il2cpp::UnityEngine::Types::Vector3 world_pos{ 0.0f, 1.0f, 0.0f };

    auto screen = il2cpp::UnityEngine::Camera::WorldToScreenPoint(
        camera.value,
        world_pos
    );
}
```

### Physics raycast

```cpp
il2cpp::UnityEngine::Types::Vector3 origin{ 0.0f, 2.0f, 0.0f };
il2cpp::UnityEngine::Types::Vector3 direction{ 0.0f, -1.0f, 0.0f };
il2cpp::UnityEngine::Types::RaycastHit hit{};

auto result = il2cpp::UnityEngine::Physics::Raycast(
    origin,
    direction,
    hit,
    100.0f
);

if (result && result.value) {
    auto point = il2cpp::UnityEngine::RaycastHit::get_point(hit);
    auto normal = il2cpp::UnityEngine::RaycastHit::get_normal(hit);
    float distance = il2cpp::UnityEngine::RaycastHit::get_distance(hit);
}
```

### Math helpers

The `Vector3` and `Quaternion` namespaces provide plain C++ math helpers that mirror common Unity semantics without requiring managed allocation.

```cpp
auto forward = il2cpp::UnityEngine::Vector3::forward();
auto normalized = il2cpp::UnityEngine::Vector3::normalize(value);
auto distance = il2cpp::UnityEngine::Vector3::distance(a, b);
```

```cpp
auto rotation = il2cpp::UnityEngine::Quaternion::Euler(0.0f, 90.0f, 0.0f);
```

---

## Status Codes

All operations use `Il2CppStatus` to report failures.

Common statuses include:

### Success

* `OK`

### Loader and export resolution

* `GameAssemblyNotFound`
* `GetProcAddressFailed`

### Missing required exports

* `Missing_domain_get`
* `Missing_thread_attach`
* `Missing_domain_get_assemblies`
* `Missing_class_from_name`
* `Missing_class_get_method_from_name`
* `Missing_class_get_methods`
* `Missing_type_get_name`
* `Missing_class_get_field_from_name`
* `Missing_field_get_set`

### Runtime resolution failures

* `DomainUnavailable`
* `AssemblyNotFound`
* `ImageUnavailable`
* `ClassNotFound`
* `MethodNotFound`
* `FieldNotFound`

### Invocation and validation

* `MethodPointerNull`
* `ThreadAttachUnavailable`
* `InvalidArgs`

---

## Cleanup

`il2cpp::cleanup()` clears the mutex-protected assembly pointer cache.

It does not forcibly detach all attached threads. Outstanding `ThreadScope` destructors still run normally on their respective threads.

```cpp
il2cpp::cleanup();
```

---

## Notes

* Core BCL types may live in either `mscorlib` or `System.Private.CoreLib`. Several helpers try both automatically.
* Use explicit parameter counts or parameter type names when overloads would otherwise collide.
* Parameter type-name matching is strict, except for normalized trailing spaces and reference suffixes.
* `String::CreateNewString` rejects empty UTF-8 strings.
* `Array` layout helpers are intended for standard 1D IL2CPP arrays.
* Many Unity value-type APIs use injected methods such as `*_Injected`. The UnityEngine wrappers prefer those where appropriate.
* Resolution and cache access are guarded where applicable.
* Assembly pointers are cached after successful lookup.
* `NOMINMAX` is recommended before including Windows headers. The resolver defensively avoids Windows `min` / `max` macro conflicts where applicable.

---

## Contributing

Contributions are welcome.

Please open an issue or pull request with:

* a clear description,
* a minimal reproduction case,
* the Unity version or target environment where possible,
* and confirmation that the current header was tested.

---

## License

MIT — see [LICENSE](LICENSE).

[license-shield]: https://img.shields.io/github/license/FigmaFan/Unity-IL2CPP-Bridge.svg?style=for-the-badge
[license-url]: https://github.com/FigmaFan/Unity-IL2CPP-Bridge/blob/master/LICENSE
[stars-shield]: https://img.shields.io/github/stars/FigmaFan/Unity-IL2CPP-Bridge.svg?style=for-the-badge
[stars-url]: https://github.com/FigmaFan/Unity-IL2CPP-Bridge/stargazers
[forks-shield]: https://img.shields.io/github/forks/FigmaFan/Unity-IL2CPP-Bridge.svg?style=for-the-badge
[forks-url]: https://github.com/FigmaFan/Unity-IL2CPP-Bridge/network/members
[contributors-shield]: https://img.shields.io/github/contributors/FigmaFan/Unity-IL2CPP-Bridge.svg?style=for-the-badge
[contributors-url]: https://github.com/FigmaFan/Unity-IL2CPP-Bridge/graphs/contributors

#pragma once
// ==============================
// il2cpp_resolver.hpp (v2.7)
// ==============================

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

#include <cstdint>
#include <string>
#include <string_view>
#include <optional>
#include <unordered_map>
#include <mutex>
#include <type_traits>
#include <memory>
#include <vector>
#include <algorithm>
#include <cstring>

#define IL2CPP_GAMEASSEMBLY_FILE "GameAssembly.dll"
#define IL2CPP_FALLBACK_ASSEMBLY "Assembly-CSharp"

enum class Il2CppStatus : uint32_t {
	OK = 0,
	GameAssemblyNotFound,
	GetProcAddressFailed,
	Missing_domain_get,
	Missing_thread_attach,
	Missing_domain_get_assemblies,
	Missing_class_from_name,
	Missing_class_get_method_from_name,
	Missing_class_get_field_from_name,
	Missing_field_get_set,
	DomainUnavailable,
	AssemblyNotFound,
	ImageUnavailable,
	ClassNotFound,
	MethodNotFound,
	FieldNotFound,
	InvalidArgs,
	ThreadAttachUnavailable,
	MethodPointerNull,
};

template <typename T>
struct Result { Il2CppStatus status{ Il2CppStatus::OK }; T value{}; explicit operator bool() const { return status == Il2CppStatus::OK; } };
template <> struct Result<void> { Il2CppStatus status{ Il2CppStatus::OK }; explicit operator bool() const { return status == Il2CppStatus::OK; } };

inline const char* to_string(Il2CppStatus s) {
	switch (s) {
	case Il2CppStatus::OK: return "OK";
	case Il2CppStatus::GameAssemblyNotFound: return "GameAssemblyNotFound";
	case Il2CppStatus::GetProcAddressFailed: return "GetProcAddressFailed";
	case Il2CppStatus::Missing_domain_get: return "Missing_domain_get";
	case Il2CppStatus::Missing_thread_attach: return "Missing_thread_attach";
	case Il2CppStatus::Missing_domain_get_assemblies: return "Missing_domain_get_assemblies";
	case Il2CppStatus::Missing_class_from_name: return "Missing_class_from_name";
	case Il2CppStatus::Missing_class_get_method_from_name: return "Missing_class_get_method_from_name";
	case Il2CppStatus::Missing_class_get_field_from_name: return "Missing_class_get_field_from_name";
	case Il2CppStatus::Missing_field_get_set: return "Missing_field_get_set";
	case Il2CppStatus::DomainUnavailable: return "DomainUnavailable";
	case Il2CppStatus::AssemblyNotFound: return "AssemblyNotFound";
	case Il2CppStatus::ImageUnavailable: return "ImageUnavailable";
	case Il2CppStatus::ClassNotFound: return "ClassNotFound";
	case Il2CppStatus::MethodNotFound: return "MethodNotFound";
	case Il2CppStatus::FieldNotFound: return "FieldNotFound";
	case Il2CppStatus::InvalidArgs: return "InvalidArgs";
	case Il2CppStatus::ThreadAttachUnavailable: return "ThreadAttachUnavailable";
	case Il2CppStatus::MethodPointerNull: return "MethodPointerNull";
	default: return "Unknown";
	}
}

namespace il2cpp {
	namespace _internal {

		namespace unity_structs {
			struct il2cppImage { const char* m_pName; const char* m_oNameNoExt; };
			struct il2cppAssemblyName { const char* m_pName{}; const char* m_pCulture{}; const char* m_pHash{}; const char* m_pPublicKey{}; unsigned int m_uHash{}; int m_iHashLength{}; unsigned int m_uFlags{}; int m_iMajor{}; int m_iMinor{}; int m_iBuild{}; int m_bRevision{}; unsigned char m_uPublicKeyToken[8]{}; };
			struct il2cppAssembly { il2cppImage* m_pImage{}; unsigned int m_uToken{}; int m_ReferencedAssemblyStart{}; int m_ReferencedAssemblyCount{}; il2cppAssemblyName m_aName{}; };
			struct il2cppClass {
				void* m_pImage{}; void* m_pGC{}; const char* m_pName{}; const char* m_pNamespace{};
				void* m_pValue{}; void* m_pArgs{}; il2cppClass* m_pElementClass{}; il2cppClass* m_pCastClass{};
				il2cppClass* m_pDeclareClass{}; il2cppClass* m_pParentClass{}; void* m_pGenericClass{}; void* m_pTypeDefinition{};
				void* m_pInteropData{}; void* m_pFields{}; void* m_pEvents{}; void* m_pProperties{};
				void** m_pMethods{}; il2cppClass** m_pNestedTypes{}; il2cppClass** m_ImplementedInterfaces{};
				void* m_pInterfaceOffsets{}; void* m_pStaticFields{}; void* m_pRGCTX{};
			};
			struct il2cppObject { il2cppClass* m_pClass = nullptr; void* m_pMonitor = nullptr; };
			struct il2cppType { union { void* m_pDummy; unsigned int m_uClassIndex; il2cppType* m_pType; void* m_pArray; unsigned int m_uGenericParameterIndex; void* m_pGenericClass; }; unsigned int m_uAttributes : 16; unsigned int m_uType : 8; unsigned int m_uMods : 6; unsigned int m_uByref : 1; unsigned int m_uPinned : 1; };
			struct il2cppFieldInfo { const char* m_pName{}; il2cppType* m_pType{}; il2cppClass* m_pParentClass{}; int m_iOffset{}; int m_iAttributeIndex{}; unsigned int m_uToken{}; };
			struct il2cppParameterInfo { const char* m_pName{}; int m_iPosition{}; unsigned int m_uToken{}; il2cppType* m_pParameterType{}; };
			struct il2cppMethodInfo {
				void* m_pMethodPointer{}; void* m_pInvokerMethod{}; const char* m_pName{}; il2cppClass* m_pClass{}; il2cppType* m_pReturnType{}; il2cppParameterInfo* m_pParameters{};
				union { void* m_pRGCTX; void* m_pMethodDefinition; };
				union { void* m_pGenericMethod; void* m_pGenericContainer; };
				unsigned int m_uToken{}; unsigned short m_uFlags{}; unsigned short m_uFlags2{}; unsigned short m_uSlot{}; unsigned char m_uArgsCount{}; unsigned char m_uGeneric : 1; unsigned char m_uInflated : 1; unsigned char m_uWrapperType : 1; unsigned char m_uMarshaledFromNative : 1;
			};
			struct Il2CppRuntimeInterfaceOffsetPair { il2cppClass* interfaceType; int32_t offset; };
			struct Il2CppClass_1 {
				void* image; void* gc_desc; const char* name; const char* namespaze; il2cppType byval_arg; il2cppType this_arg;
				il2cppClass* element_class; il2cppClass* castClass; il2cppClass* declaringType; il2cppClass* parent;
				void* generic_class; void* typeMetadataHandle; void* interopData; il2cppClass* klass;
				void* fields; void* events; void* properties; void* methods; il2cppClass** nestedTypes; il2cppClass** implementedInterfaces; Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
			};
			struct Il2CppClass_2 {
				il2cppClass** typeHierarchy; void* unity_user_data; std::uint32_t initializationExceptionGCHandle; std::uint32_t cctor_started; std::uint32_t cctor_finished; size_t cctor_thread;
				void* genericContainerHandle; std::uint32_t instance_size; std::uint32_t actualSize; std::uint32_t element_size; std::int32_t native_size; std::uint32_t static_fields_size;
				std::uint32_t thread_static_fields_size; std::int32_t thread_static_fields_offset; std::uint32_t flags; std::uint32_t token;
				std::uint16_t method_count; std::uint16_t property_count; std::uint16_t field_count; std::uint16_t event_count; std::uint16_t nested_type_count; std::uint16_t vtable_count; std::uint16_t interfaces_count; std::uint16_t interface_offsets_count;
				std::uint8_t typeHierarchyDepth; std::uint8_t genericRecursionDepth; std::uint8_t rank; std::uint8_t minimumAlignment; std::uint8_t naturalAligment; std::uint8_t packingSize; std::uint8_t bitflags1; std::uint8_t bitflags2;
			};
			struct System_String_VTable { void* _[27]; }; // not used directly
			struct __declspec(align(8)) System_String_Fields { std::uint32_t _stringLength; std::uint16_t _firstChar; };
			struct System_String_o { void* klass; void* monitor; System_String_Fields fields; };
			typedef uintptr_t il2cpp_array_size_t;
			typedef int32_t il2cpp_array_lower_bound_t;
			struct Il2CppArrayBounds {
				il2cpp_array_size_t length;
				il2cpp_array_lower_bound_t lower_bound;
			};
		} // namespace unity_structs

		inline HMODULE p_game_assembly = nullptr;
		inline std::unordered_map<std::string, unity_structs::il2cppAssembly*> g_assembly_cache;
		inline std::mutex g_cache_mtx;

		inline Result<HMODULE> ensure_game_assembly() {
			if (p_game_assembly) return { Il2CppStatus::OK, p_game_assembly };
			for (int i = 0; i < 200 && !p_game_assembly; ++i) {
				p_game_assembly = ::GetModuleHandleA(IL2CPP_GAMEASSEMBLY_FILE);
				if (!p_game_assembly) ::Sleep(10);
			}
			if (!p_game_assembly) return { Il2CppStatus::GameAssemblyNotFound, nullptr };
			return { Il2CppStatus::OK, p_game_assembly };
		}

		template <class T>
		inline Result<T> resolve_export(std::string_view name) {
			auto mod = ensure_game_assembly();
			if (!mod) return { mod.status, nullptr };
			auto p = reinterpret_cast<T>(::GetProcAddress(mod.value, std::string(name).c_str()));
			if (!p) return { Il2CppStatus::GetProcAddressFailed, nullptr };
			return { Il2CppStatus::OK, p };
		}

		// Bound function pointers (set by ensure_exports on demand)
		inline void* (__fastcall* il2cpp_domain_get)(void) = nullptr;
		inline void* (__fastcall* il2cpp_thread_attach)(void*) = nullptr;
		inline void(__fastcall* il2cpp_thread_detach)(void*) = nullptr; // optional
		inline unity_structs::il2cppAssembly** (__fastcall* il2cpp_domain_get_assemblies)(void*, size_t*) = nullptr;
		inline unity_structs::il2cppClass* (__fastcall* il2cpp_class_from_name)(unity_structs::il2cppImage*, const char*, const char*) = nullptr;
		inline unity_structs::il2cppMethodInfo* (__fastcall* il2cpp_class_get_method_from_name)(unity_structs::il2cppClass*, const char*, int) = nullptr;
		inline unity_structs::il2cppFieldInfo* (__fastcall* il2cpp_class_get_field_from_name)(unity_structs::il2cppClass*, const char*) = nullptr;
		inline void(__fastcall* il2cpp_field_get_value)(void*, unity_structs::il2cppFieldInfo*, void*) = nullptr;
		inline void(__fastcall* il2cpp_field_set_value)(void*, unity_structs::il2cppFieldInfo*, void*) = nullptr;
		inline void(__fastcall* il2cpp_field_static_get_value)(unity_structs::il2cppFieldInfo*, void*) = nullptr;
		inline void(__fastcall* il2cpp_field_static_set_value)(unity_structs::il2cppFieldInfo*, void*) = nullptr;
		inline void* (__fastcall* il2cpp_string_new)(const char*) = nullptr;              // optional for core ops
		inline void* (__fastcall* il2cpp_object_new)(unity_structs::il2cppClass*) = nullptr;
		inline bool(__fastcall* il2cpp_class_is_enum)(const unity_structs::il2cppClass*) = nullptr; // optional
		inline const unity_structs::il2cppFieldInfo* (__fastcall* il2cpp_class_get_fields)(unity_structs::il2cppClass*, void**) = nullptr;
		inline void* (__fastcall* il2cpp_array_new)(unity_structs::il2cppClass*, size_t) = nullptr;

		// Optional helpers (may be null)
		inline void* (__fastcall* il2cpp_thread_current)(void) = nullptr;
		inline bool(__fastcall* il2cpp_is_vm_thread)(void*) = nullptr;

		// Lazy binding - called by public APIs
		inline Il2CppStatus ensure_exports() {
			auto bind_req = [](auto& dst, const char* name, Il2CppStatus err) -> Il2CppStatus {
				if (!dst) {
					auto r = resolve_export<std::remove_reference_t<decltype(dst)>>(name);
					if (r.status != Il2CppStatus::OK || !r.value) return err;
					dst = r.value;
				}
				return Il2CppStatus::OK;
			};
			auto bind_opt = [](auto& dst, const char* name) {
				if (!dst) {
					auto r = resolve_export<std::remove_reference_t<decltype(dst)>>(name);
					if (r.status == Il2CppStatus::OK && r.value) dst = r.value;
				}
			};

			if (auto s = bind_req(il2cpp_domain_get, "il2cpp_domain_get", Il2CppStatus::Missing_domain_get); s != Il2CppStatus::OK) return s;
			if (auto s = bind_req(il2cpp_thread_attach, "il2cpp_thread_attach", Il2CppStatus::Missing_thread_attach); s != Il2CppStatus::OK) return s;
			bind_opt(il2cpp_thread_detach, "il2cpp_thread_detach"); // optional

			if (auto s = bind_req(il2cpp_domain_get_assemblies, "il2cpp_domain_get_assemblies", Il2CppStatus::Missing_domain_get_assemblies); s != Il2CppStatus::OK) return s;
			if (auto s = bind_req(il2cpp_class_from_name, "il2cpp_class_from_name", Il2CppStatus::Missing_class_from_name); s != Il2CppStatus::OK) return s;
			if (auto s = bind_req(il2cpp_class_get_method_from_name, "il2cpp_class_get_method_from_name", Il2CppStatus::Missing_class_get_method_from_name); s != Il2CppStatus::OK) return s;
			if (auto s = bind_req(il2cpp_class_get_field_from_name, "il2cpp_class_get_field_from_name", Il2CppStatus::Missing_class_get_field_from_name); s != Il2CppStatus::OK) return s;
			if (auto s = bind_req(il2cpp_field_get_value, "il2cpp_field_get_value", Il2CppStatus::Missing_field_get_set); s != Il2CppStatus::OK) return s;
			if (auto s = bind_req(il2cpp_field_set_value, "il2cpp_field_set_value", Il2CppStatus::Missing_field_get_set); s != Il2CppStatus::OK) return s;
			if (auto s = bind_req(il2cpp_field_static_get_value, "il2cpp_field_static_get_value", Il2CppStatus::Missing_field_get_set); s != Il2CppStatus::OK) return s;
			if (auto s = bind_req(il2cpp_field_static_set_value, "il2cpp_field_static_set_value", Il2CppStatus::Missing_field_get_set); s != Il2CppStatus::OK) return s;
			if (auto s = bind_req(il2cpp_object_new, "il2cpp_object_new", Il2CppStatus::GetProcAddressFailed); s != Il2CppStatus::OK) return s;
			if (auto s = bind_req(il2cpp_class_get_fields, "il2cpp_class_get_fields", Il2CppStatus::GetProcAddressFailed); s != Il2CppStatus::OK) return s;
			if (auto s = bind_req(il2cpp_array_new, "il2cpp_array_new", Il2CppStatus::GetProcAddressFailed); s != Il2CppStatus::OK) return s;

			// Optional - do NOT fail the whole resolver if missing
			bind_opt(il2cpp_string_new, "il2cpp_string_new");
			bind_opt(il2cpp_class_is_enum, "il2cpp_class_is_enum");
			bind_opt(il2cpp_thread_current, "il2cpp_thread_current");
			bind_opt(il2cpp_is_vm_thread, "il2cpp_is_vm_thread");

			return Il2CppStatus::OK;
		}

		// Assembly lookup + cache (requires domain+assemblies; caller ensures ThreadScope)
		inline Result<unity_structs::il2cppAssembly*> find_assembly(std::string_view assembly_name) {
			if (assembly_name.empty()) return { Il2CppStatus::InvalidArgs, nullptr };
			if (auto s = ensure_exports(); s != Il2CppStatus::OK) return { s, nullptr };

			{
				std::scoped_lock lk(g_cache_mtx);
				if (auto it = g_assembly_cache.find(std::string(assembly_name)); it != g_assembly_cache.end())
					return { Il2CppStatus::OK, it->second };
			}

			auto domain = il2cpp_domain_get ? il2cpp_domain_get() : nullptr;
			if (!domain) return { Il2CppStatus::DomainUnavailable, nullptr };

			size_t count = 0;
			auto assemblies = il2cpp_domain_get_assemblies(domain, &count);
			if (!assemblies || count == 0) return { Il2CppStatus::AssemblyNotFound, nullptr };

			for (size_t i = 0; i < count; ++i) {
				const auto* a = assemblies[i];
				if (!a) continue;
				const char* meta = a->m_aName.m_pName;
				const char* noext = (a->m_pImage ? a->m_pImage->m_oNameNoExt : nullptr);
				if ((meta && assembly_name == meta) || (noext && assembly_name == noext)) {
					std::scoped_lock lk(g_cache_mtx);
					g_assembly_cache.emplace(std::string(assembly_name), assemblies[i]);
					return { Il2CppStatus::OK, assemblies[i] };
				}
			}
			return { Il2CppStatus::AssemblyNotFound, nullptr };
		}

	} // namespace _internal

	// ---------- ThreadScope (RAII) ----------
	struct ThreadScope {
		bool attached_by_us{ false };
		void* attached_thread{ nullptr };
		inline static thread_local int depth{ 0 };

		ThreadScope() {
			if (il2cpp::_internal::ensure_exports() != Il2CppStatus::OK) return;

			bool already_vm_attached = false;
			void* cur = nullptr;

			if (il2cpp::_internal::il2cpp_thread_current)
				cur = il2cpp::_internal::il2cpp_thread_current();

			if (cur) {
				already_vm_attached = true;
				++depth;
				return;
			}

			if (il2cpp::_internal::il2cpp_domain_get && il2cpp::_internal::il2cpp_thread_attach) {
				if (auto* dom = il2cpp::_internal::il2cpp_domain_get()) {
					attached_thread = il2cpp::_internal::il2cpp_thread_attach(dom);
					attached_by_us = (attached_thread != nullptr);
					if (attached_by_us) ++depth;
				}
			}
		}

		~ThreadScope() noexcept {
			if (depth > 0) --depth;
			if (attached_by_us && depth == 0 && il2cpp::_internal::il2cpp_thread_detach && attached_thread) {
				il2cpp::_internal::il2cpp_thread_detach(attached_thread);
			}
		}
	};

	// ---------- Init/Cleanup ----------
	inline Il2CppStatus init() {
		auto mod = _internal::ensure_game_assembly();
		if (!mod) return mod.status;
		return _internal::ensure_exports();
	}

	inline void cleanup() {
		std::scoped_lock lk(_internal::g_cache_mtx);
		_internal::g_assembly_cache.clear();
	}

	// ---------- Class & Method ----------
	inline Result<_internal::unity_structs::il2cppClass*>
	find_class(const std::string& ns, const std::string& class_name, const std::string& assembly_name) {
		ThreadScope scope;
		if (ns.empty() || class_name.empty() || assembly_name.empty()) return { Il2CppStatus::InvalidArgs, nullptr };

		auto a = _internal::find_assembly(assembly_name);
		if (!a) return { a.status, nullptr };
		if (!a.value->m_pImage) return { Il2CppStatus::ImageUnavailable, nullptr };

		auto* klass = _internal::il2cpp_class_from_name(a.value->m_pImage, ns.c_str(), class_name.c_str());
		if (!klass) return { Il2CppStatus::ClassNotFound, nullptr };
		return { Il2CppStatus::OK, klass };
	}

	inline Result<_internal::unity_structs::il2cppMethodInfo*>
	get_method(const std::string& ns, const std::string& class_name, const std::string& method_name,
			const std::string& assembly_name, std::optional<int> param_count = std::nullopt) {
		ThreadScope scope;
		if (ns.empty() || class_name.empty() || method_name.empty() || assembly_name.empty()) return { Il2CppStatus::InvalidArgs, nullptr };

		auto c = find_class(ns, class_name, assembly_name);
		if (!c) return { c.status, nullptr };

		using MI = _internal::unity_structs::il2cppMethodInfo*;
		MI mi = nullptr;
		if (param_count.has_value()) {
			mi = _internal::il2cpp_class_get_method_from_name(c.value, method_name.c_str(), *param_count);
		}
		else {
			for (int i = 0; i <= 16 && !mi; ++i) mi = _internal::il2cpp_class_get_method_from_name(c.value, method_name.c_str(), i);
		}
		if (!mi) return { Il2CppStatus::MethodNotFound, nullptr };
		if (!mi->m_pMethodPointer) return { Il2CppStatus::MethodPointerNull, mi };
		return { Il2CppStatus::OK, mi };
	}

	// ---------- Fields ----------
	inline Result<int> get_field_offset(const std::string& ns, const std::string& class_name,
		const std::string& field_name, const std::string& assembly_name) {
		ThreadScope scope;
		if (ns.empty() || class_name.empty() || field_name.empty() || assembly_name.empty()) return { Il2CppStatus::InvalidArgs, -1 };

		auto c = find_class(ns, class_name, assembly_name);
		if (!c) return { c.status, -1 };

		auto* fld = _internal::il2cpp_class_get_field_from_name(c.value, field_name.c_str());
		if (!fld) return { Il2CppStatus::FieldNotFound, -1 };
		return { Il2CppStatus::OK, fld->m_iOffset };
	}

	template <class T>
	inline Result<T> get_object_field_value(void* instance, const std::string& ns, const std::string& class_name,
		const std::string& field_name, const std::string& assembly_name) {
		ThreadScope scope;
		if (!instance) return { Il2CppStatus::InvalidArgs, T{} };

		auto c = find_class(ns, class_name, assembly_name);
		if (!c) return { c.status, T{} };

		auto* fld = _internal::il2cpp_class_get_field_from_name(c.value, field_name.c_str());
		if (!fld) return { Il2CppStatus::FieldNotFound, T{} };

		T out{};
		_internal::il2cpp_field_get_value(instance, fld, &out);
		return { Il2CppStatus::OK, out };
	}

	template <class T>
	inline Il2CppStatus set_object_field_value(void* instance, const std::string& ns, const std::string& class_name,
		const std::string& field_name, const T& value, const std::string& assembly_name) {
		ThreadScope scope;
		if (!instance) return Il2CppStatus::InvalidArgs;

		auto c = find_class(ns, class_name, assembly_name);
		if (!c) return c.status;

		auto* fld = _internal::il2cpp_class_get_field_from_name(c.value, field_name.c_str());
		if (!fld) return Il2CppStatus::FieldNotFound;

		_internal::il2cpp_field_set_value(instance, fld, const_cast<T*>(&value));
		return Il2CppStatus::OK;
	}

	template <class T>
	inline Result<T> get_static_field_value(_internal::unity_structs::il2cppClass* klass, const std::string& field_name) {
		ThreadScope scope;
		if (!klass || field_name.empty()) return { Il2CppStatus::InvalidArgs, T{} };
		auto* fld = _internal::il2cpp_class_get_field_from_name(klass, field_name.c_str());
		if (!fld) return { Il2CppStatus::FieldNotFound, T{} };
		T out{};
		_internal::il2cpp_field_static_get_value(fld, &out);
		return { Il2CppStatus::OK, out };
	}

	template <class T>
	inline Il2CppStatus set_static_field_value(_internal::unity_structs::il2cppClass* klass,
		const std::string& field_name, const T& value) 
	{
		ThreadScope scope;
		if (!klass || field_name.empty()) return Il2CppStatus::InvalidArgs;
		auto* fld = _internal::il2cpp_class_get_field_from_name(klass, field_name.c_str());
		if (!fld) return Il2CppStatus::FieldNotFound;
		_internal::il2cpp_field_static_set_value(fld, const_cast<T*>(&value));
		return Il2CppStatus::OK;
	}

	// ---------- Object Creation ----------
	template <typename T = void*>
	inline Result<T> create_object(_internal::unity_structs::il2cppClass* klass) {
		ThreadScope scope;
		if (!klass) return { Il2CppStatus::ClassNotFound, nullptr };
		if (!_internal::il2cpp_object_new) {
			if (auto s = _internal::ensure_exports(); s != Il2CppStatus::OK) return { s, nullptr };
		}
		if (!_internal::il2cpp_object_new) return { Il2CppStatus::GetProcAddressFailed, nullptr };
		auto obj = _internal::il2cpp_object_new(klass);
		if (!obj) return { Il2CppStatus::InvalidArgs, nullptr };
		return { Il2CppStatus::OK, reinterpret_cast<T>(obj) };
	}

	template <typename T = void*, typename... CtorArgs>
	inline Result<T> create_object(const std::string& ns, const std::string& class_name,
		const std::string& assembly_name, CtorArgs... ctor_args) {
		ThreadScope scope;
		auto klass = find_class(ns, class_name, assembly_name);
		if (!klass) return { klass.status, nullptr };
		auto r = create_object<T>(klass.value);
		if (!r) return r;
		if constexpr (sizeof...(CtorArgs) > 0) {
			auto mi_ctor = get_method(ns, class_name, ".ctor", assembly_name, sizeof...(CtorArgs));
			if (!mi_ctor) return { mi_ctor.status, nullptr };
			auto ctor_result = call_function<void>(mi_ctor.value, r.value, ctor_args...);
			if (!ctor_result) return { ctor_result.status, nullptr };
		}
		return r;
	}

	// ---------- Strings ----------
	namespace String {
		inline Result<void*> CreateNewString(const std::string& s) {
			ThreadScope scope;
			if (s.empty()) return { Il2CppStatus::InvalidArgs, nullptr };
			if (!_internal::il2cpp_string_new) {
				(void)_internal::ensure_exports();
				if (!_internal::il2cpp_string_new) return { Il2CppStatus::GetProcAddressFailed, nullptr };
			}
			return { Il2CppStatus::OK, _internal::il2cpp_string_new(s.c_str()) };
		}

		inline std::string convert_to_std_string(void* p_sys_str) {
			ThreadScope scope;
			if (!p_sys_str) return {};

			auto get_off = [](const std::string& ns, const std::string& cls, const std::string& field, const std::string& asmName) -> int {
				auto asmRes = _internal::find_assembly(asmName);
				if (!asmRes || !asmRes.value->m_pImage) return -1;
				auto* k = _internal::il2cpp_class_from_name(asmRes.value->m_pImage, ns.c_str(), cls.c_str());
				if (!k) return -1;
				auto* f = _internal::il2cpp_class_get_field_from_name(k, field.c_str());
				return f ? f->m_iOffset : -1;
				};

			int off_firstChar = get_off("System", "String", "_firstChar", "mscorlib");
			int off_len = get_off("System", "String", "_stringLength", "mscorlib");
			if (off_firstChar < 0 || off_len < 0) {
				off_firstChar = get_off("System", "String", "_firstChar", "System.Private.CoreLib");
				off_len = get_off("System", "String", "_stringLength", "System.Private.CoreLib");
			}
			if (off_firstChar < 0 || off_len < 0) return {};

			const char16_t* wstr = reinterpret_cast<const char16_t*>(reinterpret_cast<const char*>(p_sys_str) + off_firstChar);
			int32_t len = 0;
			if (memcpy_s(&len, sizeof(len), reinterpret_cast<const char*>(p_sys_str) + off_len, sizeof(int32_t)) != 0) {
				return {};
			}
			if (len <= 0) return {};

			int required = ::WideCharToMultiByte(CP_UTF8, 0, reinterpret_cast<LPCWCH>(wstr), len, nullptr, 0, nullptr, nullptr);
			if (required <= 0) return {};
			std::string out(static_cast<size_t>(required - 1), '\0');
			int written = ::WideCharToMultiByte(CP_UTF8, 0, reinterpret_cast<LPCWCH>(wstr), len, out.data(), required - 1, nullptr, nullptr);
			if (written <= 0) return {};
			out.resize(static_cast<size_t>(written));
			return out;
		}
	} // namespace String

	inline Result<void*> CreateNewString(const std::string& s) { return String::CreateNewString(s); }
	inline std::string   convert_to_std_string(void* p_sys_str) { return String::convert_to_std_string(p_sys_str); }

	// ---------- Managed Calls ----------
	template <typename Ret, typename... Args>
	inline auto call_function(_internal::unity_structs::il2cppMethodInfo* method, Args... args)
		-> std::conditional_t<std::is_void_v<Ret>, Result<void>, Result<Ret>> {
		ThreadScope scope;
		using R = std::conditional_t<std::is_void_v<Ret>, Result<void>, Result<Ret>>;
		if (!method) {
			if constexpr (std::is_void_v<Ret>) return R{ Il2CppStatus::MethodNotFound };
			else                               return R{ Il2CppStatus::MethodNotFound, Ret{} };
		}
		if (!method->m_pMethodPointer) {
			if constexpr (std::is_void_v<Ret>) return R{ Il2CppStatus::MethodPointerNull };
			else                               return R{ Il2CppStatus::MethodPointerNull, Ret{} };
		}
		using Fn = Ret(__fastcall*)(Args...);
		auto fn = reinterpret_cast<Fn>(method->m_pMethodPointer);
		if constexpr (std::is_void_v<Ret>) { fn(args...); return R{ Il2CppStatus::OK }; }
		else { return R{ Il2CppStatus::OK, fn(args...) }; }
	}

	// ---------- Arrays ----------
	namespace Array {

		template <typename T>
		struct Il2CppArray1D {
			void* klass;
			void* monitor;
			_internal::unity_structs::Il2CppArrayBounds* bounds;
			uintptr_t max_length;
			T m_Items[1];
		};

		inline Result<_internal::unity_structs::il2cppClass*>
		resolve_element_class(std::string_view ns, std::string_view name, std::string_view assembly) {
			static std::mutex mtx;
			static std::unordered_map<std::string, _internal::unity_structs::il2cppClass*> cache;

			const std::string key = std::string(ns) + "|" + std::string(name) + "|" + std::string(assembly);
			{
				std::lock_guard lk(mtx);
				if (auto it = cache.find(key); it != cache.end())
					return { Il2CppStatus::OK, it->second };
			}

			auto c = find_class(std::string(ns), std::string(name), std::string(assembly));
			if (!c || !c.value) return { c.status, nullptr };

			{
				std::lock_guard lk(mtx);
				cache.emplace(key, c.value);
			}

			return { Il2CppStatus::OK, c.value };
		}

		template<typename T>
		inline Result<Il2CppArray1D<T>*>
		create_1d(_internal::unity_structs::il2cppClass* elemClass, size_t length)
		{
			ThreadScope scope;

			if (!elemClass || length == 0)
				return { Il2CppStatus::InvalidArgs, nullptr };

			auto st = _internal::ensure_exports();
			if (st != Il2CppStatus::OK)
				return { st, nullptr };

			if (!_internal::il2cpp_array_new)
				return { Il2CppStatus::GetProcAddressFailed, nullptr };

			auto* raw = static_cast<Il2CppArray1D<T>*>(
				_internal::il2cpp_array_new(elemClass, length)
				);
			if (!raw)
				return { Il2CppStatus::InvalidArgs, nullptr };

			return { Il2CppStatus::OK, raw };
		}

		template<typename T>
		inline Result<Il2CppArray1D<T>*>
		create_1d(std::string_view ns,
				std::string_view name,
				std::string_view assembly,
				size_t length)
		{
			auto c = resolve_element_class(ns, name, assembly);
			if (!c || !c.value)
				return { c.status, nullptr };

			return create_1d<T>(c.value, length);
		}

		template<typename T>
		inline T* data(Il2CppArray1D<T>* arr)
		{
			return arr ? arr->m_Items : nullptr;
		}

		template<typename T>
		inline size_t length(Il2CppArray1D<T>* arr)
		{
			return arr ? static_cast<size_t>(arr->max_length) : 0;
		}

		inline Result<int> array_get_length_1d(void* arr) {
			ThreadScope scope;
			auto mi = get_method("System", "Array", "GetLength", "mscorlib", 1);
			if (!mi) mi = get_method("System", "Array", "GetLength", "System.Private.CoreLib", 1);
			if (!mi) return { mi.status, 0 };
			return call_function<int>(mi.value, arr, 0);
		}

		template <typename Ret>
		inline Result<Ret> array_get_element_1d(void* arr, long long idx) {
			ThreadScope scope;
			auto mi = get_method("System", "Array", "GetValue", "mscorlib", 1);
			if (!mi) mi = get_method("System", "Array", "GetValue", "System.Private.CoreLib", 1);
			if (!mi) return { mi.status, Ret{} };
			return call_function<Ret>(mi.value, arr, idx);
		}

	} // namespace Array

	// ---------- Enum Utils ----------
	namespace Enum {
		struct Key {
			std::string ns; std::string name; std::string assembly;
			bool operator==(const Key& o) const noexcept { return ns == o.ns && name == o.name && assembly == o.assembly; }
		};
		struct KeyHash {
			size_t operator()(const Key& k) const noexcept {
				std::hash<std::string> H; size_t h = H(k.ns);
				h ^= (H(k.name) << 1); h ^= (H(k.assembly) << 2); return h;
			}
		};
		struct EnumEntry { int32_t value; std::string name; };

		inline Result<std::shared_ptr<const std::vector<EnumEntry>>>
			get_entries(std::string_view ns, std::string_view name, std::string_view assembly) {
			ThreadScope scope;

			static std::unordered_map<Key, std::shared_ptr<const std::vector<EnumEntry>>, KeyHash> g_cache;
			static std::mutex m;

			Key key{ std::string(ns), std::string(name), std::string(assembly) };
			{
				std::lock_guard<std::mutex> lk(m);
				if (auto it = g_cache.find(key); it != g_cache.end()) return { Il2CppStatus::OK, it->second };
			}

			auto klass = find_class(key.ns, key.name, key.assembly);
			if (!klass) return { klass.status, nullptr };

			// If il2cpp_class_is_enum is missing, we skip the check and just enumerate fields.
			if (_internal::il2cpp_class_is_enum && !_internal::il2cpp_class_is_enum(klass.value))
				return { Il2CppStatus::InvalidArgs, nullptr };

			auto entries = std::make_shared<std::vector<EnumEntry>>();
			entries->reserve(16);

			void* iter = nullptr;
			while (true) {
				auto fi = _internal::il2cpp_class_get_fields(klass.value, &iter);
				if (!fi) break;
				if (!fi->m_pName) continue;
				if (std::strcmp(fi->m_pName, "value__") == 0) continue;
				int32_t v = 0;
				_internal::il2cpp_field_static_get_value(const_cast<_internal::unity_structs::il2cppFieldInfo*>(fi), &v);
				if (std::strlen(fi->m_pName)) entries->push_back({ v, std::string(fi->m_pName) });
			}

			std::sort(entries->begin(), entries->end(),
				[](auto& a, auto& b) { return a.value < b.value || (a.value == b.value && a.name < b.name); });
			entries->erase(std::unique(entries->begin(), entries->end(),
				[](auto& a, auto& b) { return a.value == b.value && a.name == b.name; }),
				entries->end());

			{ std::lock_guard<std::mutex> lk(m); g_cache.emplace(std::move(key), entries); }
			return { Il2CppStatus::OK, entries };
		}

		inline Result<std::string> name_of(std::string_view ns, std::string_view name, std::string_view assembly, int32_t value) {
			auto entries = get_entries(ns, name, assembly);
			if (!entries) return { entries.status, {} };
			const auto& vec = *entries.value;
			auto it = std::find_if(vec.begin(), vec.end(), [&](auto& e) { return e.value == value; });
			if (it == vec.end()) return { Il2CppStatus::FieldNotFound, {} };
			return { Il2CppStatus::OK, it->name };
		}

		inline Result<int32_t> value_of(std::string_view ns, std::string_view name, std::string_view assembly, std::string_view literal) {
			auto entries = get_entries(ns, name, assembly);
			if (!entries) return { entries.status, 0 };
			const auto& vec = *entries.value;
			auto it = std::find_if(vec.begin(), vec.end(), [&](auto& e) { return e.name == literal; });
			if (it == vec.end()) return { Il2CppStatus::FieldNotFound, 0 };
			return { Il2CppStatus::OK, it->value };
		}

		struct IndexMap {
			std::shared_ptr<const std::vector<EnumEntry>> entries;
			std::unordered_map<int32_t, int> value_to_index;
			int index_of(int32_t value) const {
				if (auto it = value_to_index.find(value); it != value_to_index.end()) return it->second;
				return 0;
			}
		};

		inline Result<IndexMap> index_map(std::string_view ns, std::string_view name, std::string_view assembly) {
			IndexMap M{};
			auto entries = get_entries(ns, name, assembly);
			if (!entries) return { entries.status, {} };
			M.entries = entries.value;
			M.value_to_index.reserve(M.entries->size());
			for (int i = 0; i < static_cast<int>(M.entries->size()); ++i) M.value_to_index.emplace((*M.entries)[i].value, i);
			return { Il2CppStatus::OK, std::move(M) };
		}
	} // namespace Enum

} // namespace il2cpp
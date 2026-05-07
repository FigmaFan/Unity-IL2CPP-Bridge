#pragma once
// il2cpp_resolver.hpp (v2.9)

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
#include <initializer_list>
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
	Missing_class_get_methods,
	Missing_type_get_name,
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
	case Il2CppStatus::Missing_class_get_methods: return "Missing_class_get_methods";
	case Il2CppStatus::Missing_type_get_name: return "Missing_type_get_name";
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
	template <typename T>
	struct Result { Il2CppStatus status{ Il2CppStatus::OK }; T value{}; explicit operator bool() const { return status == Il2CppStatus::OK; } };
	template <> struct Result<void> { Il2CppStatus status{ Il2CppStatus::OK }; explicit operator bool() const { return status == Il2CppStatus::OK; } };

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
			struct System_String_VTable { void* _[27]; };
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
		inline std::once_flag g_game_assembly_once;
		inline std::unordered_map<std::string, unity_structs::il2cppAssembly*> g_assembly_cache;
		inline std::mutex g_cache_mtx;

		inline Result<HMODULE> ensure_game_assembly() {
			std::call_once(g_game_assembly_once, [] {
				for (int i = 0; i < 200 && !p_game_assembly; ++i) {
					p_game_assembly = ::GetModuleHandleA(IL2CPP_GAMEASSEMBLY_FILE);
					if (!p_game_assembly) ::Sleep(10);
				}
				});
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

		inline void* (__fastcall* il2cpp_domain_get)(void) = nullptr;
		inline void* (__fastcall* il2cpp_thread_attach)(void*) = nullptr;
		inline void(__fastcall* il2cpp_thread_detach)(void*) = nullptr;
		inline unity_structs::il2cppAssembly** (__fastcall* il2cpp_domain_get_assemblies)(void*, size_t*) = nullptr;
		inline unity_structs::il2cppClass* (__fastcall* il2cpp_class_from_name)(unity_structs::il2cppImage*, const char*, const char*) = nullptr;
		inline unity_structs::il2cppMethodInfo* (__fastcall* il2cpp_class_get_method_from_name)(unity_structs::il2cppClass*, const char*, int) = nullptr;
		inline const unity_structs::il2cppMethodInfo* (__fastcall* il2cpp_class_get_methods)(unity_structs::il2cppClass*, void**) = nullptr;
		inline uint32_t(__fastcall* il2cpp_method_get_param_count)(const unity_structs::il2cppMethodInfo*) = nullptr;
		inline const unity_structs::il2cppType* (__fastcall* il2cpp_method_get_param)(const unity_structs::il2cppMethodInfo*, uint32_t) = nullptr;
		inline char* (__fastcall* il2cpp_type_get_name)(const unity_structs::il2cppType*) = nullptr;
		inline unity_structs::il2cppFieldInfo* (__fastcall* il2cpp_class_get_field_from_name)(unity_structs::il2cppClass*, const char*) = nullptr;
		inline void(__fastcall* il2cpp_field_get_value)(void*, unity_structs::il2cppFieldInfo*, void*) = nullptr;
		inline void(__fastcall* il2cpp_field_set_value)(void*, unity_structs::il2cppFieldInfo*, void*) = nullptr;
		inline void(__fastcall* il2cpp_field_static_get_value)(unity_structs::il2cppFieldInfo*, void*) = nullptr;
		inline void(__fastcall* il2cpp_field_static_set_value)(unity_structs::il2cppFieldInfo*, void*) = nullptr;
		inline void* (__fastcall* il2cpp_string_new)(const char*) = nullptr;
		inline void* (__fastcall* il2cpp_object_new)(unity_structs::il2cppClass*) = nullptr;
		inline bool(__fastcall* il2cpp_class_is_enum)(const unity_structs::il2cppClass*) = nullptr;
		inline const unity_structs::il2cppFieldInfo* (__fastcall* il2cpp_class_get_fields)(unity_structs::il2cppClass*, void**) = nullptr;
		inline void* (__fastcall* il2cpp_array_new)(unity_structs::il2cppClass*, size_t) = nullptr;
		inline void* (__fastcall* il2cpp_resolve_icall)(const char*) = nullptr;

		inline void* (__fastcall* il2cpp_thread_current)(void) = nullptr;
		inline bool(__fastcall* il2cpp_is_vm_thread)(void*) = nullptr;

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
			bind_opt(il2cpp_thread_detach, "il2cpp_thread_detach");

			if (auto s = bind_req(il2cpp_domain_get_assemblies, "il2cpp_domain_get_assemblies", Il2CppStatus::Missing_domain_get_assemblies); s != Il2CppStatus::OK) return s;
			if (auto s = bind_req(il2cpp_class_from_name, "il2cpp_class_from_name", Il2CppStatus::Missing_class_from_name); s != Il2CppStatus::OK) return s;
			if (auto s = bind_req(il2cpp_class_get_method_from_name, "il2cpp_class_get_method_from_name", Il2CppStatus::Missing_class_get_method_from_name); s != Il2CppStatus::OK) return s;
			if (auto s = bind_req(il2cpp_class_get_methods, "il2cpp_class_get_methods", Il2CppStatus::Missing_class_get_methods); s != Il2CppStatus::OK) return s;
			if (auto s = bind_req(il2cpp_type_get_name, "il2cpp_type_get_name", Il2CppStatus::Missing_type_get_name); s != Il2CppStatus::OK) return s;
			bind_opt(il2cpp_method_get_param_count, "il2cpp_method_get_param_count");
			bind_opt(il2cpp_method_get_param, "il2cpp_method_get_param");
			if (auto s = bind_req(il2cpp_class_get_field_from_name, "il2cpp_class_get_field_from_name", Il2CppStatus::Missing_class_get_field_from_name); s != Il2CppStatus::OK) return s;
			if (auto s = bind_req(il2cpp_field_get_value, "il2cpp_field_get_value", Il2CppStatus::Missing_field_get_set); s != Il2CppStatus::OK) return s;
			if (auto s = bind_req(il2cpp_field_set_value, "il2cpp_field_set_value", Il2CppStatus::Missing_field_get_set); s != Il2CppStatus::OK) return s;
			if (auto s = bind_req(il2cpp_field_static_get_value, "il2cpp_field_static_get_value", Il2CppStatus::Missing_field_get_set); s != Il2CppStatus::OK) return s;
			if (auto s = bind_req(il2cpp_field_static_set_value, "il2cpp_field_static_set_value", Il2CppStatus::Missing_field_get_set); s != Il2CppStatus::OK) return s;
			if (auto s = bind_req(il2cpp_object_new, "il2cpp_object_new", Il2CppStatus::GetProcAddressFailed); s != Il2CppStatus::OK) return s;
			if (auto s = bind_req(il2cpp_class_get_fields, "il2cpp_class_get_fields", Il2CppStatus::GetProcAddressFailed); s != Il2CppStatus::OK) return s;
			if (auto s = bind_req(il2cpp_array_new, "il2cpp_array_new", Il2CppStatus::GetProcAddressFailed); s != Il2CppStatus::OK) return s;

			bind_opt(il2cpp_string_new, "il2cpp_string_new");
			bind_opt(il2cpp_class_is_enum, "il2cpp_class_is_enum");
			bind_opt(il2cpp_thread_current, "il2cpp_thread_current");
			bind_opt(il2cpp_is_vm_thread, "il2cpp_is_vm_thread");
			bind_opt(il2cpp_resolve_icall, "il2cpp_resolve_icall");

			return Il2CppStatus::OK;
		}

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

		inline std::string_view trim_trailing_spaces(std::string_view s) {
			while (!s.empty() && s.back() == ' ') s.remove_suffix(1);
			return s;
		}

		inline std::string_view strip_ref_type_suffix(std::string_view s) {
			s = trim_trailing_spaces(s);
			while (!s.empty() && s.back() == '&') {
				s.remove_suffix(1);
				s = trim_trailing_spaces(s);
			}
			return s;
		}

		inline bool param_type_names_match(std::string_view expected, const char* actual_cstr) {
			if (!actual_cstr) return false;
			std::string_view actual(actual_cstr);
			if (expected == actual) return true;
			return strip_ref_type_suffix(expected) == strip_ref_type_suffix(actual);
		}

		inline const unity_structs::il2cppType* method_param_type_at(const unity_structs::il2cppMethodInfo* m, uint32_t idx) {
			if (il2cpp_method_get_param)
				return il2cpp_method_get_param(m, idx);
			if (m->m_pParameters && idx < static_cast<uint32_t>(m->m_uArgsCount))
				return m->m_pParameters[idx].m_pParameterType;
			return nullptr;
		}

		inline uint32_t method_visible_param_count(const unity_structs::il2cppMethodInfo* m) {
			if (il2cpp_method_get_param_count)
				return il2cpp_method_get_param_count(m);
			return static_cast<uint32_t>(m->m_uArgsCount);
		}

		inline Result<unity_structs::il2cppMethodInfo*>
			find_method_by_param_type_names(unity_structs::il2cppClass* klass,
				const std::string& method_name,
				const std::vector<std::string>& param_type_names) {
			if (!klass || method_name.empty()) return { Il2CppStatus::InvalidArgs, nullptr };
			if (!il2cpp_class_get_methods) return { Il2CppStatus::Missing_class_get_methods, nullptr };
			if (!il2cpp_type_get_name) return { Il2CppStatus::Missing_type_get_name, nullptr };

			void* iter = nullptr;
			while (const auto* mi = il2cpp_class_get_methods(klass, &iter)) {
				if (!mi->m_pName || std::strcmp(mi->m_pName, method_name.c_str()) != 0)
					continue;
				const uint32_t pc = method_visible_param_count(mi);
				if (pc != param_type_names.size())
					continue;
				bool sig_ok = true;
				for (uint32_t i = 0; i < pc; ++i) {
					const auto* pt = method_param_type_at(mi, i);
					if (!pt) {
						sig_ok = false;
						break;
					}
					const char* tname = il2cpp_type_get_name(pt);
					if (!param_type_names_match(param_type_names[static_cast<size_t>(i)], tname)) {
						sig_ok = false;
						break;
					}
				}
				if (!sig_ok) continue;
				return { Il2CppStatus::OK, const_cast<unity_structs::il2cppMethodInfo*>(mi) };
			}
			return { Il2CppStatus::MethodNotFound, nullptr };
		}

	} // namespace _internal

	struct ThreadScope {
		bool attached_by_us{ false };
		void* attached_thread{ nullptr };
		inline static thread_local int depth{ 0 };

		ThreadScope() {
			if (il2cpp::_internal::ensure_exports() != Il2CppStatus::OK) return;

			void* cur = nullptr;

			if (il2cpp::_internal::il2cpp_thread_current)
				cur = il2cpp::_internal::il2cpp_thread_current();

			if (cur) {
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

	inline bool is_current_thread_attached() {
		if (_internal::ensure_exports() != Il2CppStatus::OK) return false;
		if (!_internal::il2cpp_thread_current) return false;
		return _internal::il2cpp_thread_current() != nullptr;
	}

	inline Il2CppStatus init() {
		auto mod = _internal::ensure_game_assembly();
		if (!mod) return mod.status;
		return _internal::ensure_exports();
	}

	inline Result<void*> resolve_icall(std::string_view icall_name) {
		if (icall_name.empty()) return { Il2CppStatus::InvalidArgs, nullptr };
		if (auto s = _internal::ensure_exports(); s != Il2CppStatus::OK) return { s, nullptr };
		if (!_internal::il2cpp_resolve_icall) return { Il2CppStatus::GetProcAddressFailed, nullptr };

		const std::string name(icall_name);
		void* fn = _internal::il2cpp_resolve_icall(name.c_str());
		if (!fn) return { Il2CppStatus::MethodNotFound, nullptr };
		return { Il2CppStatus::OK, fn };
	}

	inline void cleanup() {
		std::scoped_lock lk(_internal::g_cache_mtx);
		_internal::g_assembly_cache.clear();
	}

	inline Result<_internal::unity_structs::il2cppClass*>
		find_class(const std::string& ns, const std::string& class_name, const std::string& assembly_name) {
		ThreadScope scope;
		if (class_name.empty() || assembly_name.empty()) return { Il2CppStatus::InvalidArgs, nullptr };

		auto a = _internal::find_assembly(assembly_name);
		if (!a) return { a.status, nullptr };
		if (!a.value->m_pImage) return { Il2CppStatus::ImageUnavailable, nullptr };

		auto* klass = _internal::il2cpp_class_from_name(a.value->m_pImage, ns.c_str(), class_name.c_str());
		if (!klass) return { Il2CppStatus::ClassNotFound, nullptr };
		return { Il2CppStatus::OK, klass };
	}

	inline Result<_internal::unity_structs::il2cppClass*> get_object_class(void* obj) {
		ThreadScope scope;
		if (!obj) return { Il2CppStatus::InvalidArgs, nullptr };
		const auto* o = reinterpret_cast<const _internal::unity_structs::il2cppObject*>(obj);
		if (!o->m_pClass) return { Il2CppStatus::ClassNotFound, nullptr };
		return { Il2CppStatus::OK, o->m_pClass };
	}

	inline Result<_internal::unity_structs::il2cppClass*> object_get_class(void* obj) {
		return get_object_class(obj);
	}

	inline Result<_internal::unity_structs::il2cppMethodInfo*>
		get_method(const std::string& ns, const std::string& class_name, const std::string& method_name,
			const std::string& assembly_name, std::optional<int> param_count = std::nullopt) {
		ThreadScope scope;
		if (class_name.empty() || method_name.empty() || assembly_name.empty()) return { Il2CppStatus::InvalidArgs, nullptr };

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

	inline Result<_internal::unity_structs::il2cppMethodInfo*>
		get_method(const std::string& ns, const std::string& class_name, const std::string& method_name,
			const std::string& assembly_name, const std::vector<std::string>& param_type_names) {
		ThreadScope scope;
		if (class_name.empty() || method_name.empty() || assembly_name.empty())
			return { Il2CppStatus::InvalidArgs, nullptr };
		if (auto s = _internal::ensure_exports(); s != Il2CppStatus::OK) return { s, nullptr };

		auto c = find_class(ns, class_name, assembly_name);
		if (!c) return { c.status, nullptr };

		auto found = _internal::find_method_by_param_type_names(c.value, method_name, param_type_names);
		if (!found) return found;
		if (!found.value->m_pMethodPointer) return { Il2CppStatus::MethodPointerNull, found.value };
		return { Il2CppStatus::OK, found.value };
	}

	inline Result<_internal::unity_structs::il2cppMethodInfo*>
		get_method(const std::string& ns, const std::string& class_name, const std::string& method_name,
			const std::string& assembly_name, std::initializer_list<std::string_view> param_type_names) {
		std::vector<std::string> storage;
		storage.reserve(param_type_names.size());
		for (std::string_view sv : param_type_names) storage.emplace_back(sv);
		return get_method(ns, class_name, method_name, assembly_name, storage);
	}

	inline Result<_internal::unity_structs::il2cppMethodInfo*>
		get_method(_internal::unity_structs::il2cppClass* klass, const std::string& method_name,
			std::optional<int> param_count = std::nullopt) {
		ThreadScope scope;
		if (!klass || method_name.empty()) return { Il2CppStatus::InvalidArgs, nullptr };

		using MI = _internal::unity_structs::il2cppMethodInfo*;
		MI mi = nullptr;
		if (param_count.has_value()) {
			mi = _internal::il2cpp_class_get_method_from_name(klass, method_name.c_str(), *param_count);
		}
		else {
			for (int i = 0; i <= 16 && !mi; ++i) mi = _internal::il2cpp_class_get_method_from_name(klass, method_name.c_str(), i);
		}
		if (!mi) return { Il2CppStatus::MethodNotFound, nullptr };
		if (!mi->m_pMethodPointer) return { Il2CppStatus::MethodPointerNull, mi };
		return { Il2CppStatus::OK, mi };
	}

	inline Result<_internal::unity_structs::il2cppMethodInfo*>
		get_method(_internal::unity_structs::il2cppClass* klass, const std::string& method_name,
			const std::vector<std::string>& param_type_names) {
		ThreadScope scope;
		if (!klass || method_name.empty()) return { Il2CppStatus::InvalidArgs, nullptr };
		if (auto s = _internal::ensure_exports(); s != Il2CppStatus::OK) return { s, nullptr };

		auto found = _internal::find_method_by_param_type_names(klass, method_name, param_type_names);
		if (!found) return found;
		if (!found.value->m_pMethodPointer) return { Il2CppStatus::MethodPointerNull, found.value };
		return { Il2CppStatus::OK, found.value };
	}

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
	inline Result<T> get_object_field_value(void* instance, _internal::unity_structs::il2cppClass* klass,
		const std::string& field_name) {
		ThreadScope scope;
		if (!instance || !klass || field_name.empty()) return { Il2CppStatus::InvalidArgs, T{} };

		auto* fld = _internal::il2cpp_class_get_field_from_name(klass, field_name.c_str());
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
			const int len = *reinterpret_cast<const int*>(reinterpret_cast<const char*>(p_sys_str) + off_len);
			if (len <= 0) return {};

			int required = ::WideCharToMultiByte(CP_UTF8, 0, reinterpret_cast<LPCWCH>(wstr), len, nullptr, 0, nullptr, nullptr);
			if (required <= 0) return {};
			std::string out(static_cast<size_t>(required), '\0');
			::WideCharToMultiByte(CP_UTF8, 0, reinterpret_cast<LPCWCH>(wstr), len, out.data(), required, nullptr, nullptr);
			return out;
		}
		
	} // namespace String

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

	namespace Array {
		struct Header {
			void* klass;
			void* monitor;
			_internal::unity_structs::Il2CppArrayBounds* bounds;
			uintptr_t max_length;
		};

		template <typename T>
		struct Il2CppArray1D {
			void* klass;
			void* monitor;
			_internal::unity_structs::Il2CppArrayBounds* bounds;
			uintptr_t max_length;
			T m_Items[1];
		};

		template <typename T>
		inline Il2CppArray1D<T>* as(void* arr) noexcept {
			return reinterpret_cast<Il2CppArray1D<T>*>(arr);
		}

		template <typename T>
		inline const Il2CppArray1D<T>* as(const void* arr) noexcept {
			return reinterpret_cast<const Il2CppArray1D<T>*>(arr);
		}

		template <typename T>
		inline T* data(void* arr) {
			if (!arr)
				return nullptr;

			return as<T>(arr)->m_Items;
		}

		template <typename T>
		inline const T* data(const void* arr) {
			if (!arr)
				return nullptr;

			return as<T>(arr)->m_Items;
		}

		inline Header* header(void* arr) noexcept {
			return reinterpret_cast<Header*>(arr);
		}

		inline const Header* header(const void* arr) noexcept {
			return reinterpret_cast<const Header*>(arr);
		}

		inline bool is_null(void* arr) noexcept {
			return arr == nullptr;
		}

		inline Result<size_t> length(void* arr) {
			if (!arr)
				return { Il2CppStatus::InvalidArgs, 0 };

			auto* h = header(arr);
			return { Il2CppStatus::OK, static_cast<size_t>(h->max_length) };
		}

		inline Result<int> length_i32(void* arr) {
			auto len = length(arr);
			if (!len)
				return { len.status, 0 };

			if (len.value > static_cast<size_t>(std::numeric_limits<int>::max()))
				return { Il2CppStatus::InvalidArgs, 0 };

			return { Il2CppStatus::OK, static_cast<int>(len.value) };
		}

		template <typename T>
		inline Result<T> get(void* arr, size_t idx) {
			if (!arr)
				return { Il2CppStatus::InvalidArgs, T{} };

			auto* h = header(arr);
			if (idx >= h->max_length)
				return { Il2CppStatus::InvalidArgs, T{} };

			T out{};
			std::memcpy(&out, data<T>(arr) + idx, sizeof(T));
			return { Il2CppStatus::OK, out };
		}

		template <typename T>
		inline Il2CppStatus set(void* arr, size_t idx, const T& value) {
			if (!arr)
				return Il2CppStatus::InvalidArgs;

			auto* h = header(arr);
			if (idx >= h->max_length)
				return Il2CppStatus::InvalidArgs;

			std::memcpy(data<T>(arr) + idx, &value, sizeof(T));
			return Il2CppStatus::OK;
		}

		template <typename T>
		inline Result<T*> at_ptr(void* arr, size_t idx) {
			if (!arr)
				return { Il2CppStatus::InvalidArgs, nullptr };

			auto* h = header(arr);
			if (idx >= h->max_length)
				return { Il2CppStatus::InvalidArgs, nullptr };

			return { Il2CppStatus::OK, data<T>(arr) + idx };
		}

		template <typename T>
		inline bool empty(void* arr) {
			if (!arr)
				return true;

			auto* h = header(arr);
			return h->max_length == 0;
		}

		inline Result<_internal::unity_structs::il2cppClass*>
			resolve_element_class(std::string_view ns, std::string_view name, std::string_view assembly) {
			static std::mutex mtx;
			static std::unordered_map<std::string, _internal::unity_structs::il2cppClass*> cache;

			if (name.empty() || assembly.empty())
				return { Il2CppStatus::InvalidArgs, nullptr };

			const std::string key =
				std::string(ns) + "|" + std::string(name) + "|" + std::string(assembly);

			{
				std::lock_guard lk(mtx);
				if (auto it = cache.find(key); it != cache.end())
					return { Il2CppStatus::OK, it->second };
			}

			auto c = find_class(std::string(ns), std::string(name), std::string(assembly));
			if (!c || !c.value)
				return { c.status, nullptr };

			{
				std::lock_guard lk(mtx);
				cache.emplace(key, c.value);
			}

			return { Il2CppStatus::OK, c.value };
		}

		template <typename T>
		inline Result<Il2CppArray1D<T>*> create_1d(
			_internal::unity_structs::il2cppClass* elem_class,
			size_t length
		) {
			ThreadScope scope;

			if (!elem_class)
				return { Il2CppStatus::InvalidArgs, nullptr };

			auto st = _internal::ensure_exports();
			if (st != Il2CppStatus::OK)
				return { st, nullptr };

			if (!_internal::il2cpp_array_new)
				return { Il2CppStatus::GetProcAddressFailed, nullptr };

			auto* raw = static_cast<Il2CppArray1D<T>*>(
				_internal::il2cpp_array_new(elem_class, length)
				);

			if (!raw)
				return { Il2CppStatus::InvalidArgs, nullptr };

			return { Il2CppStatus::OK, raw };
		}

		template <typename T>
		inline Result<Il2CppArray1D<T>*> create_1d(
			std::string_view ns,
			std::string_view name,
			std::string_view assembly,
			size_t length
		) {
			auto c = resolve_element_class(ns, name, assembly);
			if (!c || !c.value)
				return { c.status, nullptr };

			return create_1d<T>(c.value, length);
		}

		inline Result<int> length_managed(void* arr) {
			ThreadScope scope;

			if (!arr)
				return { Il2CppStatus::InvalidArgs, 0 };

			auto mi = get_method("System", "Array", "GetLength", "mscorlib", 1);
			if (!mi)
				mi = get_method("System", "Array", "GetLength", "System.Private.CoreLib", 1);

			if (!mi)
				return { mi.status, 0 };

			return call_function<int>(mi.value, arr, 0);
		}

		template <typename Ret>
		inline Result<Ret> get_managed(void* arr, long long idx) {
			ThreadScope scope;

			if (!arr || idx < 0)
				return { Il2CppStatus::InvalidArgs, Ret{} };

			auto mi = get_method("System", "Array", "GetValue", "mscorlib", 1);
			if (!mi)
				mi = get_method("System", "Array", "GetValue", "System.Private.CoreLib", 1);

			if (!mi)
				return { mi.status, Ret{} };

			return call_function<Ret>(mi.value, arr, idx);
		}

		template <typename T, typename Fn>
		inline Il2CppStatus for_each(void* arr, Fn&& fn) {
			if (!arr)
				return Il2CppStatus::InvalidArgs;

			auto len = length(arr);
			if (!len)
				return len.status;

			auto* items = data<T>(arr);
			if (!items)
				return Il2CppStatus::InvalidArgs;

			for (size_t i = 0; i < len.value; ++i) {
				fn(i, items[i]);
			}

			return Il2CppStatus::OK;
		}

		inline Result<void*> get_ref(void* arr, size_t idx) {
			return get<void*>(arr, idx);
		}

		inline Result<void*> first_ref(void* arr) {
			if (!arr)
				return { Il2CppStatus::OK, nullptr };

			auto len = length(arr);
			if (!len)
				return { len.status, nullptr };

			if (len.value == 0)
				return { Il2CppStatus::OK, nullptr };

			return get<void*>(arr, 0);
		}
	}

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
				if (fi->m_pName && std::strcmp(fi->m_pName, "value__") == 0) continue;
				if (!fi->m_pName) continue;
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

	namespace Type {

		namespace _detail {
			inline Result<_internal::unity_structs::il2cppMethodInfo*>
				resolve_get_type_method() {
				static constexpr const char* kAssemblyCandidates[] = {
					"mscorlib",
					"System.Private.CoreLib",
				};
				Il2CppStatus last = Il2CppStatus::MethodNotFound;
				for (auto* asm_name : kAssemblyCandidates) {
					auto m = il2cpp::get_method("System", "Type", "GetType", asm_name, 1);
					if (m) return m;
					last = m.status;
				}
				return { last, nullptr };
			}
		} // namespace _detail

		// System.Type.GetType(string) with an existing Il2Cpp string.
		inline Result<void*> GetType(void* type_name_il2cpp_string) {
			ThreadScope scope;
			if (!type_name_il2cpp_string) return { Il2CppStatus::InvalidArgs, nullptr };

			auto m = _detail::resolve_get_type_method();
			if (!m) return { m.status, nullptr };
			if (!m.value->m_pMethodPointer) return { Il2CppStatus::MethodPointerNull, nullptr };

			using Fn = void* (__fastcall*)(void*, _internal::unity_structs::il2cppMethodInfo*);
			auto fn = reinterpret_cast<Fn>(m.value->m_pMethodPointer);
			void* result = fn(type_name_il2cpp_string, m.value);
			if (!result) return { Il2CppStatus::ClassNotFound, nullptr };
			return { Il2CppStatus::OK, result };
		}

		// type_name example: "UnityEngine.GameObject, UnityEngine.CoreModule"
		inline Result<void*> GetType(const std::string& type_name) {
			ThreadScope scope;
			if (type_name.empty()) return { Il2CppStatus::InvalidArgs, nullptr };

			auto s = String::CreateNewString(type_name);
			if (!s) return { s.status, nullptr };
			return GetType(s.value);
		}

	} // namespace Type

	namespace UnityEngine {

		namespace _detail {
			inline Result<_internal::unity_structs::il2cppMethodInfo*>
				resolve_object_method(const char* method_name, int param_count) {
				static constexpr const char* kAssemblyCandidates[] = {
					"UnityEngine.CoreModule",
					"UnityEngine",
				};
				Il2CppStatus last = Il2CppStatus::MethodNotFound;
				for (auto* asm_name : kAssemblyCandidates) {
					auto m = il2cpp::get_method("UnityEngine", "Object", method_name, asm_name, param_count);
					if (m) return m;
					last = m.status;
				}
				return { last, nullptr };
			}

			inline Result<_internal::unity_structs::il2cppMethodInfo*>
				resolve_component_method(const char* method_name, int param_count) {
				static constexpr const char* kAssemblyCandidates[] = {
					"UnityEngine.CoreModule",
					"UnityEngine",
				};
				Il2CppStatus last = Il2CppStatus::MethodNotFound;
				for (auto* asm_name : kAssemblyCandidates) {
					auto m = il2cpp::get_method("UnityEngine", "Component", method_name, asm_name, param_count);
					if (m) return m;
					last = m.status;
				}
				return { last, nullptr };
			}

			inline Result<_internal::unity_structs::il2cppMethodInfo*>
				resolve_component_method(
					const char* method_name,
					std::initializer_list<std::string_view> param_type_names
				) {
				static constexpr const char* kAssemblyCandidates[] = {
					"UnityEngine.CoreModule",
					"UnityEngine",
				};

				Il2CppStatus last = Il2CppStatus::MethodNotFound;

				for (auto* asm_name : kAssemblyCandidates) {
					auto m = il2cpp::get_method(
						"UnityEngine",
						"Component",
						method_name,
						asm_name,
						param_type_names
					);

					if (m)
						return m;

					last = m.status;
				}

				return { last, nullptr };
			}

			inline Result<_internal::unity_structs::il2cppMethodInfo*>
				resolve_game_object_method(const char* method_name, int param_count) {
				static constexpr const char* kAssemblyCandidates[] = {
					"UnityEngine.CoreModule",
					"UnityEngine",
				};
				Il2CppStatus last = Il2CppStatus::MethodNotFound;
				for (auto* asm_name : kAssemblyCandidates) {
					auto m = il2cpp::get_method("UnityEngine", "GameObject", method_name, asm_name, param_count);
					if (m) return m;
					last = m.status;
				}
				return { last, nullptr };
			}

			inline Result<_internal::unity_structs::il2cppMethodInfo*>
				resolve_find_objects_by_type_method(int param_count) {
				return resolve_object_method("FindObjectsByType", param_count);
			}

			inline Result<_internal::unity_structs::il2cppMethodInfo*>
				resolve_transform_method(const char* method_name, int param_count) {
				static constexpr const char* kAssemblyCandidates[] = {
					"UnityEngine.CoreModule",
					"UnityEngine",
				};

				Il2CppStatus last = Il2CppStatus::MethodNotFound;

				for (auto* asm_name : kAssemblyCandidates) {
					auto m = il2cpp::get_method("UnityEngine", "Transform", method_name, asm_name, param_count);
					if (m) return m;
					last = m.status;
				}

				return { last, nullptr };
			}

			inline Result<_internal::unity_structs::il2cppMethodInfo*>
				resolve_quaternion_method(const char* method_name, int param_count) {
				static constexpr const char* kAssemblyCandidates[] = {
					"UnityEngine.CoreModule",
					"UnityEngine",
				};

				Il2CppStatus last = Il2CppStatus::MethodNotFound;

				for (auto* asm_name : kAssemblyCandidates) {
					auto m = il2cpp::get_method(
						"UnityEngine",
						"Quaternion",
						method_name,
						asm_name,
						param_count
					);

					if (m) return m;
					last = m.status;
				}

				return { last, nullptr };
			}

			inline Result<_internal::unity_structs::il2cppMethodInfo*>
				resolve_raycast_hit_method(const char* method_name, int param_count) {
				static constexpr const char* kAssemblyCandidates[] = {
					"UnityEngine.PhysicsModule",
				};

				Il2CppStatus last = Il2CppStatus::MethodNotFound;

				for (auto* asm_name : kAssemblyCandidates) {
					auto m = il2cpp::get_method(
						"UnityEngine",
						"RaycastHit",
						method_name,
						asm_name,
						param_count
					);

					if (m) return m;
					last = m.status;
				}

				return { last, nullptr };
			}

			inline Result<_internal::unity_structs::il2cppMethodInfo*>
				resolve_physics_method(const char* method_name, int param_count) {
				static constexpr const char* kAssemblyCandidates[] = {
					"UnityEngine.PhysicsModule",
				};

				Il2CppStatus last = Il2CppStatus::MethodNotFound;

				for (auto* asm_name : kAssemblyCandidates) {
					auto m = il2cpp::get_method(
						"UnityEngine",
						"Physics",
						method_name,
						asm_name,
						param_count
					);

					if (m) return m;
					last = m.status;
				}

				return { last, nullptr };
			}

			inline Result<_internal::unity_structs::il2cppMethodInfo*>
				resolve_physics_scene_method(const char* method_name, int param_count) {
				static constexpr const char* kAssemblyCandidates[] = {
					"UnityEngine.PhysicsModule",
				};

				Il2CppStatus last = Il2CppStatus::MethodNotFound;

				for (auto* asm_name : kAssemblyCandidates) {
					auto m = il2cpp::get_method(
						"UnityEngine",
						"PhysicsScene",
						method_name,
						asm_name,
						param_count
					);

					if (m) return m;
					last = m.status;
				}

				return { last, nullptr };
			}

			inline Result<_internal::unity_structs::il2cppMethodInfo*>
				resolve_camera_method(const char* method_name, int param_count) {
				static constexpr const char* kAssemblyCandidates[] = {
					"UnityEngine.CoreModule",
					"UnityEngine",
				};

				Il2CppStatus last = Il2CppStatus::MethodNotFound;

				for (auto* asm_name : kAssemblyCandidates) {
					auto m = il2cpp::get_method(
						"UnityEngine",
						"Camera",
						method_name,
						asm_name,
						param_count
					);

					if (m) return m;
					last = m.status;
				}

				return { last, nullptr };
			}
		} // namespace _detail

		enum class QueryTriggerInteraction : std::int32_t {
			UseGlobal = 0,
			Ignore = 1,
			Collide = 2
		};

		enum class FindObjectsSortMode : int32_t {
			None = 0,
			InstanceID = 1
		};

		enum class FindObjectsInactive : int32_t {
			Exclude = 0,
			Include = 1
		};

		enum class MonoOrStereoscopicEye : std::int32_t {
			Left = 0,
			Right = 1,
			Mono = 2,
		};

		inline Result<std::string> get_name(void* unity_object) {
			ThreadScope scope;

			if (!unity_object)
				return { Il2CppStatus::InvalidArgs, {} };

			auto method = _detail::resolve_object_method("get_name", 0);
			if (!method)
				return { method.status, {} };

			if (!method.value->m_pMethodPointer)
				return { Il2CppStatus::MethodPointerNull, {} };

			using Fn = void* (__fastcall*)(
				void* self,
				_internal::unity_structs::il2cppMethodInfo* method
				);

			auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

			void* str = fn(unity_object, method.value);
			if (!str)
				return { Il2CppStatus::OK, {} };

			return {
				Il2CppStatus::OK,
				il2cpp::String::convert_to_std_string(str)
			};
		}

		namespace Types {
			struct Vector2 {
				float x{};
				float y{};
			};
			struct Vector3 {
				float x{};
				float y{};
				float z{};
			};
			struct Quaternion {
				float x{};
				float y{};
				float z{};
				float w{};
			};
			struct Color {};
			struct Bounds {};
			struct PhysicsScene {
				std::int32_t m_Handle{};
			};
			struct Ray {
				Vector3 m_Origin{};
				Vector3 m_Direction{};
			};
			struct RaycastHit {
				Vector3 m_Point{};
				Vector3 m_Normal{};
				std::uint32_t m_FaceID{};
				float m_Distance{};
				Vector2 m_UV{};
				std::int32_t m_Collider{};
			};
		} // namespace Types

		namespace Vector3 {
			using Value = Types::Vector3;

			constexpr float kEpsilon = 1E-05f;
			constexpr float kEpsilonNormalSqrt = 1E-15f;

			inline constexpr Value zero() noexcept { return { 0.0f, 0.0f, 0.0f }; }
			inline constexpr Value one() noexcept { return { 1.0f, 1.0f, 1.0f }; }

			inline constexpr Value up() noexcept { return { 0.0f, 1.0f, 0.0f }; }
			inline constexpr Value down() noexcept { return { 0.0f, -1.0f, 0.0f }; }
			inline constexpr Value left() noexcept { return { -1.0f, 0.0f, 0.0f }; }
			inline constexpr Value right() noexcept { return { 1.0f, 0.0f, 0.0f }; }
			inline constexpr Value forward() noexcept { return { 0.0f, 0.0f, 1.0f }; }
			inline constexpr Value back() noexcept { return { 0.0f, 0.0f, -1.0f }; }

			inline Value add(const Value& a, const Value& b) noexcept {
				return { a.x + b.x, a.y + b.y, a.z + b.z };
			}

			inline Value sub(const Value& a, const Value& b) noexcept {
				return { a.x - b.x, a.y - b.y, a.z - b.z };
			}

			inline Value mul(const Value& v, float d) noexcept {
				return { v.x * d, v.y * d, v.z * d };
			}

			inline Value div(const Value& v, float d) noexcept {
				return { v.x / d, v.y / d, v.z / d };
			}

			inline float dot(const Value& a, const Value& b) noexcept {
				return a.x * b.x + a.y * b.y + a.z * b.z;
			}

			inline Value cross(const Value& lhs, const Value& rhs) noexcept {
				return {
					lhs.y * rhs.z - lhs.z * rhs.y,
					lhs.z * rhs.x - lhs.x * rhs.z,
					lhs.x * rhs.y - lhs.y * rhs.x
				};
			}

			inline float sqr_magnitude(const Value& v) noexcept {
				return v.x * v.x + v.y * v.y + v.z * v.z;
			}

			inline float magnitude(const Value& v) noexcept {
				return std::sqrt(sqr_magnitude(v));
			}

			inline float distance(const Value& a, const Value& b) noexcept {
				return magnitude(sub(a, b));
			}

			inline float distance_sqr(const Value& a, const Value& b) noexcept {
				return sqr_magnitude(sub(a, b));
			}

			inline Value normalize(const Value& v) noexcept {
				const float mag = magnitude(v);
				if (mag > kEpsilon) {
					return div(v, mag);
				}
				return zero();
			}

			inline Value scale(const Value& a, const Value& b) noexcept {
				return { a.x * b.x, a.y * b.y, a.z * b.z };
			}

			inline Value min(const Value& a, const Value& b) noexcept {
				return {
					std::min(a.x, b.x),
					std::min(a.y, b.y),
					std::min(a.z, b.z)
				};
			}

			inline Value max(const Value& a, const Value& b) noexcept {
				return {
					std::max(a.x, b.x),
					std::max(a.y, b.y),
					std::max(a.z, b.z)
				};
			}

			inline Value lerp_unclamped(const Value& a, const Value& b, float t) noexcept {
				return {
					a.x + (b.x - a.x) * t,
					a.y + (b.y - a.y) * t,
					a.z + (b.z - a.z) * t
				};
			}

			inline Value lerp(const Value& a, const Value& b, float t) noexcept {
				t = std::clamp(t, 0.0f, 1.0f);
				return lerp_unclamped(a, b, t);
			}

			inline bool nearly_equal(const Value& a, const Value& b, float epsilon = kEpsilon) noexcept {
				return distance_sqr(a, b) < epsilon * epsilon;
			}

			inline bool is_zero(const Value& v) noexcept {
				return v.x == 0.0f && v.y == 0.0f && v.z == 0.0f;
			}

			inline bool is_finite(const Value& v) noexcept {
				return std::isfinite(v.x) && std::isfinite(v.y) && std::isfinite(v.z);
			}

			inline std::string to_string(const Value& v) {
				char buffer[128]{};
				std::snprintf(buffer, sizeof(buffer), "(%.3f, %.3f, %.3f)", v.x, v.y, v.z);
				return buffer;
			}
		} // namespace Vector3

		namespace Quaternion {
			using Value = Types::Quaternion;
			using Vector3Value = Types::Vector3;
			
			constexpr float kEpsilon = 1e-6f;

			inline constexpr Value identity() noexcept { return { 0.0f, 0.0f, 0.0f, 1.0f }; }

			inline float dot(const Value& a, const Value& b) noexcept {
				return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
			}

			inline float sqr_magnitude(const Value& q) noexcept {
				return dot(q, q);
			}

			inline float magnitude(const Value& q) noexcept {
				return std::sqrt(sqr_magnitude(q));
			}

			inline Value normalize(const Value& q) noexcept {
				const float mag = magnitude(q);

				if (mag <= kEpsilon) {
					return identity();
				}

				const float inv = 1.0f / mag;
				return {
					q.x * inv,
					q.y * inv,
					q.z * inv,
					q.w * inv
				};
			}

			inline Value inverse(const Value& q) noexcept {
				const float sqr = sqr_magnitude(q);

				if (sqr <= kEpsilon) {
					return identity();
				}

				const float inv = 1.0f / sqr;

				return {
					-q.x * inv,
					-q.y * inv,
					-q.z * inv,
					 q.w * inv
				};
			}

			inline Value mul(const Value& lhs, const Value& rhs) noexcept {
				return {
					lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y,
					lhs.w * rhs.y + lhs.y * rhs.w + lhs.z * rhs.x - lhs.x * rhs.z,
					lhs.w * rhs.z + lhs.z * rhs.w + lhs.x * rhs.y - lhs.y * rhs.x,
					lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z
				};
			}

			inline Vector3Value mul(const Value& rotation, const Vector3Value& point) noexcept {
				const float x = rotation.x * 2.0f;
				const float y = rotation.y * 2.0f;
				const float z = rotation.z * 2.0f;

				const float xx = rotation.x * x;
				const float yy = rotation.y * y;
				const float zz = rotation.z * z;

				const float xy = rotation.x * y;
				const float xz = rotation.x * z;
				const float yz = rotation.y * z;

				const float wx = rotation.w * x;
				const float wy = rotation.w * y;
				const float wz = rotation.w * z;

				Vector3Value result{};
				result.x = (1.0f - (yy + zz)) * point.x + (xy - wz) * point.y + (xz + wy) * point.z;
				result.y = (xy + wz) * point.x + (1.0f - (xx + zz)) * point.y + (yz - wx) * point.z;
				result.z = (xz - wy) * point.x + (yz + wx) * point.y + (1.0f - (xx + yy)) * point.z;

				return result;
			}

			inline bool nearly_equal(const Value& a, const Value& b, float epsilon = kEpsilon) noexcept {
				return std::abs(dot(a, b)) > 1.0f - epsilon;
			}

			inline float angle(const Value& a, const Value& b) noexcept {
				const float d = std::min(std::abs(dot(a, b)), 1.0f);

				if (d > 1.0f - kEpsilon) {
					return 0.0f;
				}

				return std::acos(d) * 2.0f * 57.29577951308232f;
			}

			inline Vector3Value forward(const Value& rotation) noexcept {
				return mul(rotation, Vector3::forward());
			}

			inline Vector3Value right(const Value& rotation) noexcept {
				return mul(rotation, Vector3::right());
			}

			inline Vector3Value up(const Value& rotation) noexcept {
				return mul(rotation, Vector3::up());
			}

			inline Result<Value> LookRotation(const Vector3Value& forward, const Vector3Value& upwards = Vector3::up()) {
				ThreadScope scope;

				auto method = _detail::resolve_quaternion_method("LookRotation_Injected", 3);
				if (!method) return { method.status, {} };
				if (!method.value->m_pMethodPointer) return { Il2CppStatus::MethodPointerNull, {} };

				using Fn = void(__fastcall*)(
					const Vector3Value* forward,
					const Vector3Value* upwards,
					Value* ret,
					_internal::unity_structs::il2cppMethodInfo* method
					);

				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

				Value out{};
				fn(&forward, &upwards, &out, method.value);

				return { Il2CppStatus::OK, out };
			}

			inline Result<Value> Internal_FromEulerRad(const Vector3Value& euler_rad) {
				ThreadScope scope;

				auto method = _detail::resolve_quaternion_method("Internal_FromEulerRad_Injected", 2);
				if (!method) return { method.status, {} };
				if (!method.value->m_pMethodPointer) return { Il2CppStatus::MethodPointerNull, {} };

				using Fn = void(__fastcall*)(
					const Vector3Value* euler,
					Value* ret,
					_internal::unity_structs::il2cppMethodInfo* method
					);

				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

				Value out{};
				fn(&euler_rad, &out, method.value);

				return { Il2CppStatus::OK, out };
			}

			inline Result<Value> Euler(const Vector3Value& euler_degrees) {
				constexpr float deg_to_rad = 0.017453292519943295f;

				Vector3Value rad{
					euler_degrees.x * deg_to_rad,
					euler_degrees.y * deg_to_rad,
					euler_degrees.z * deg_to_rad
				};

				return Internal_FromEulerRad(rad);
			}

			inline Result<Value> Euler(float x, float y, float z) {
				return Euler(Vector3Value{ x, y, z });
			}

			inline Result<Vector3Value> Internal_ToEulerRad(const Value& rotation) {
				ThreadScope scope;

				auto method = _detail::resolve_quaternion_method("Internal_ToEulerRad_Injected", 2);
				if (!method) return { method.status, {} };
				if (!method.value->m_pMethodPointer) return { Il2CppStatus::MethodPointerNull, {} };

				using Fn = void(__fastcall*)(
					const Value* rotation,
					Vector3Value* ret,
					_internal::unity_structs::il2cppMethodInfo* method
					);

				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

				Vector3Value out{};
				fn(&rotation, &out, method.value);

				return { Il2CppStatus::OK, out };
			}

			inline Result<Vector3Value> ToEulerAngles(const Value& rotation) {
				constexpr float rad_to_deg = 57.29577951308232f;

				auto rad = Internal_ToEulerRad(rotation);
				if (!rad) return rad;

				return {
					Il2CppStatus::OK,
					Vector3Value{
						rad.value.x * rad_to_deg,
						rad.value.y * rad_to_deg,
						rad.value.z * rad_to_deg
					}
				};
			}

			inline Result<Value> AngleAxis(float angle_degrees, const Vector3Value& axis) {
				ThreadScope scope;

				auto method = _detail::resolve_quaternion_method("AngleAxis_Injected", 3);
				if (!method) return { method.status, {} };
				if (!method.value->m_pMethodPointer) return { Il2CppStatus::MethodPointerNull, {} };

				using Fn = void(__fastcall*)(
					float angle,
					const Vector3Value* axis,
					Value* ret,
					_internal::unity_structs::il2cppMethodInfo* method
					);

				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

				Value out{};
				fn(angle_degrees, &axis, &out, method.value);

				return { Il2CppStatus::OK, out };
			}
		} // namespace Quaternion

		namespace Ray {
			using Value = Types::Ray;
			using Vector3Value = Types::Vector3;

			inline Value create(const Vector3Value& origin, const Vector3Value& direction) noexcept {
				return {
					origin,
					Vector3::normalize(direction)
				};
			}

			inline const Vector3Value& get_origin(const Value& ray) noexcept {
				return ray.m_Origin;
			}

			inline void set_origin(Value& ray, const Vector3Value& origin) noexcept {
				ray.m_Origin = origin;
			}

			inline const Vector3Value& get_direction(const Value& ray) noexcept {
				return ray.m_Direction;
			}

			inline void set_direction(Value& ray, const Vector3Value& direction) noexcept {
				ray.m_Direction = Vector3::normalize(direction);
			}

			inline Vector3Value GetPoint(const Value& ray, float distance) noexcept {
				return Vector3::add(
					ray.m_Origin,
					Vector3::mul(ray.m_Direction, distance)
				);
			}

			inline bool is_valid(const Value& ray) noexcept {
				return Vector3::is_finite(ray.m_Origin)
					&& Vector3::is_finite(ray.m_Direction)
					&& Vector3::sqr_magnitude(ray.m_Direction) > Vector3::kEpsilon * Vector3::kEpsilon;
			}

			inline std::string to_string(const Value& ray) {
				return "Origin: " + Vector3::to_string(ray.m_Origin)
					+ ", Direction: " + Vector3::to_string(ray.m_Direction);
			}
		} // namespace Ray

		namespace Physics {
			constexpr std::int32_t IgnoreRaycastLayer = 1 << 2;
			constexpr std::int32_t DefaultRaycastLayers = ~IgnoreRaycastLayer;
			constexpr std::int32_t AllLayers = ~0;
			constexpr float Infinity = std::numeric_limits<float>::infinity();
		}

		namespace PhysicsScene {
			using Value = Types::PhysicsScene;

			inline bool has_handle(const Value& scene) noexcept {
				return scene.m_Handle != 0;
			}

			inline Result<bool> IsValid(Value scene) {
				ThreadScope scope;

				auto method = _detail::resolve_physics_scene_method("IsValid_Internal_Injected", 1);
				if (!method) return { method.status, false };
				if (!method.value->m_pMethodPointer)
					return { Il2CppStatus::MethodPointerNull, false };

				using Fn = bool(__fastcall*)(
					Value* physics_scene,
					_internal::unity_structs::il2cppMethodInfo* method
				);

				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

				return { Il2CppStatus::OK, fn(&scene, method.value) };
			}

			inline Result<bool> RaycastTest(
				Value scene,
				const Types::Ray& ray,
				float max_distance = Physics::Infinity,
				std::int32_t layer_mask = Physics::DefaultRaycastLayers,
				QueryTriggerInteraction query_trigger_interaction = QueryTriggerInteraction::UseGlobal
			) {
				ThreadScope scope;

				auto valid = IsValid(scene);
				if (!valid) return { valid.status, false };

				if (!valid.value) return { Il2CppStatus::InvalidArgs, false };

				auto method = _detail::resolve_physics_scene_method("Internal_RaycastTest_Injected", 5);
				if (!method) return { method.status, false };
				if (!method.value->m_pMethodPointer)
					return { Il2CppStatus::MethodPointerNull, false };

				using Fn = bool(__fastcall*)(
					Value* physics_scene,
					const Types::Ray* ray,
					float max_distance,
					std::int32_t layer_mask,
					QueryTriggerInteraction query_trigger_interaction,
					_internal::unity_structs::il2cppMethodInfo* method
				);

				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

				return {
					Il2CppStatus::OK,
					fn(&scene, &ray, max_distance, layer_mask, query_trigger_interaction, method.value)
				};
			}

			inline Result<bool> Raycast(
				Value scene,
				const Types::Ray& ray,
				Types::RaycastHit& hit,
				float max_distance = Physics::Infinity,
				std::int32_t layer_mask = Physics::DefaultRaycastLayers,
				QueryTriggerInteraction query_trigger_interaction = QueryTriggerInteraction::UseGlobal
			) {
				ThreadScope scope;

				auto valid = IsValid(scene);
				if (!valid)
					return { valid.status, false };

				if (!valid.value)
					return { Il2CppStatus::InvalidArgs, false };

				auto method = _detail::resolve_physics_scene_method("Internal_Raycast_Injected", 6);
				if (!method) return { method.status, false };
				if (!method.value->m_pMethodPointer)
					return { Il2CppStatus::MethodPointerNull, false };

				using Fn = bool(__fastcall*)(
					Value* physics_scene,
					const Types::Ray* ray,
					float max_distance,
					Types::RaycastHit* hit,
					std::int32_t layer_mask,
					QueryTriggerInteraction query_trigger_interaction,
					_internal::unity_structs::il2cppMethodInfo* method
				);

				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

				hit = {};

				const bool did_hit = fn(
					&scene,
					&ray,
					max_distance,
					&hit,
					layer_mask,
					query_trigger_interaction,
					method.value
				);

				return { Il2CppStatus::OK, did_hit };
			}

			inline Result<bool> Raycast(
				Value scene,
				const Types::Vector3& origin,
				const Types::Vector3& direction,
				Types::RaycastHit& hit,
				float max_distance = Physics::Infinity,
				std::int32_t layer_mask = Physics::DefaultRaycastLayers,
				QueryTriggerInteraction query_trigger_interaction = QueryTriggerInteraction::UseGlobal
			) {
				const auto ray = Ray::create(origin, direction);
				return Raycast(scene, ray, hit, max_distance, layer_mask, query_trigger_interaction);
			}
		} // namespace PhysicsScene

		namespace Physics {
			using Vector3Value = Types::Vector3;
			using RayValue = Types::Ray;
			using RaycastHitValue = Types::RaycastHit;
			using PhysicsSceneValue = Types::PhysicsScene;

			inline Result<Vector3Value> get_gravity() {
				ThreadScope scope;

				auto method = _detail::resolve_physics_method("get_gravity_Injected", 1);
				if (!method) return { method.status, {} };
				if (!method.value->m_pMethodPointer)
					return { Il2CppStatus::MethodPointerNull, {} };

				using Fn = void(__fastcall*)(
					Vector3Value* ret,
					_internal::unity_structs::il2cppMethodInfo* method
				);
				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

				Vector3Value out{};
				fn(&out, method.value);

				return { Il2CppStatus::OK, out };
			}

			inline Result<void*> GetColliderByInstanceID(int32_t instance_id) {
				ThreadScope scope;

				if (instance_id == 0)
					return { Il2CppStatus::OK, nullptr };

				auto method = _detail::resolve_physics_method("GetColliderByInstanceID", 1);
				if (!method) return { method.status, nullptr };
				if (!method.value->m_pMethodPointer)
					return { Il2CppStatus::MethodPointerNull, nullptr };

				using Fn = void* (__fastcall*)(
					int32_t instance_id,
					_internal::unity_structs::il2cppMethodInfo* method
					);

				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);
				return { Il2CppStatus::OK, fn(instance_id, method.value) };
			}

			inline Result<void*> GetBodyByInstanceID(int32_t instance_id) {
				ThreadScope scope;

				if (instance_id == 0)
					return { Il2CppStatus::OK, nullptr };

				auto method = _detail::resolve_physics_method("GetBodyByInstanceID", 1);
				if (!method) return { method.status, nullptr };
				if (!method.value->m_pMethodPointer)
					return { Il2CppStatus::MethodPointerNull, nullptr };

				using Fn = void* (__fastcall*)(
					int32_t instance_id,
					_internal::unity_structs::il2cppMethodInfo* method
					);

				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);
				return { Il2CppStatus::OK, fn(instance_id, method.value) };
			}

			inline Result<PhysicsSceneValue> get_defaultPhysicsScene() {
				ThreadScope scope;

				auto method = _detail::resolve_physics_method("get_defaultPhysicsScene_Injected", 1);
				if (!method) return { method.status, {} };
				if (!method.value->m_pMethodPointer)
					return { Il2CppStatus::MethodPointerNull, {} };

				using Fn = void(__fastcall*)(
					PhysicsSceneValue* ret,
					_internal::unity_structs::il2cppMethodInfo* method
					);

				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

				PhysicsSceneValue out{};
				fn(&out, method.value);

				return { Il2CppStatus::OK, out };
			}

			inline Result<void*> RaycastAllRaw(
				const Types::Ray& ray,
				float max_distance = Infinity,
				int32_t layer_mask = DefaultRaycastLayers,
				QueryTriggerInteraction query_trigger_interaction = QueryTriggerInteraction::UseGlobal
			) {
				ThreadScope scope;

				auto scene = get_defaultPhysicsScene();
				if (!scene) return { scene.status, nullptr };

				auto method = _detail::resolve_physics_method("Internal_RaycastAll_Injected", 5);
				if (!method) return { method.status, nullptr };
				if (!method.value->m_pMethodPointer)
					return { Il2CppStatus::MethodPointerNull, nullptr };

				using Fn = void* (__fastcall*)(
					Types::PhysicsScene* physics_scene,
					const Types::Ray* ray,
					float max_distance,
					int32_t mask,
					QueryTriggerInteraction query_trigger_interaction,
					_internal::unity_structs::il2cppMethodInfo* method
					);

				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

				return {
					Il2CppStatus::OK,
					fn(&scene.value, &ray, max_distance, layer_mask, query_trigger_interaction, method.value)
				};
			}

			inline Result<bool> Raycast(
				const Types::Ray& ray,
				Types::RaycastHit& hit,
				float max_distance = std::numeric_limits<float>::infinity(),
				std::int32_t layer_mask = DefaultRaycastLayers,
				QueryTriggerInteraction query_trigger_interaction = QueryTriggerInteraction::UseGlobal
			) {
				ThreadScope scope;

				auto scene = get_defaultPhysicsScene();
				if (!scene) return { scene.status, false };

				return PhysicsScene::Raycast(
					scene.value,
					ray,
					hit,
					max_distance,
					layer_mask,
					query_trigger_interaction
				);
			}

			inline Result<bool> Raycast(
				const Types::Vector3& origin,
				const Types::Vector3& direction,
				Types::RaycastHit& hit,
				float max_distance = std::numeric_limits<float>::infinity(),
				std::int32_t layer_mask = DefaultRaycastLayers,
				QueryTriggerInteraction query_trigger_interaction = QueryTriggerInteraction::UseGlobal
			) {
				const auto ray = Ray::create(origin, direction);

				return Raycast(
					ray,
					hit,
					max_distance,
					layer_mask,
					query_trigger_interaction
				);
			}

			inline Result<bool> RaycastTest(
				const Types::Ray& ray,
				float max_distance = std::numeric_limits<float>::infinity(),
				std::int32_t layer_mask = DefaultRaycastLayers,
				QueryTriggerInteraction query_trigger_interaction = QueryTriggerInteraction::UseGlobal
			) {
				ThreadScope scope;

				auto scene = get_defaultPhysicsScene();
				if (!scene) return { scene.status, false };

				return PhysicsScene::RaycastTest(
					scene.value,
					ray,
					max_distance,
					layer_mask,
					query_trigger_interaction
				);
			}

			inline Result<bool> RaycastTest(
				const Types::Vector3& origin,
				const Types::Vector3& direction,
				float max_distance = std::numeric_limits<float>::infinity(),
				std::int32_t layer_mask = DefaultRaycastLayers,
				QueryTriggerInteraction query_trigger_interaction = QueryTriggerInteraction::UseGlobal
			) {
				const auto ray = Ray::create(origin, direction);

				return RaycastTest(
					ray,
					max_distance,
					layer_mask,
					query_trigger_interaction
				);
			}
		} // namespace Physics

		namespace RaycastHit {
			using Value = Types::RaycastHit;
			using Vector3Value = Types::Vector3;
			using Vector2Value = Types::Vector2;

			inline const Vector3Value& get_point(const Value& hit) noexcept {
				return hit.m_Point;
			}

			inline void set_point(Value& hit, const Vector3Value& point) noexcept {
				hit.m_Point = point;
			}

			inline const Vector3Value& get_normal(const Value& hit) noexcept {
				return hit.m_Normal;
			}

			inline void set_normal(Value& hit, const Vector3Value& normal) noexcept {
				hit.m_Normal = normal;
			}

			inline float get_distance(const Value& hit) noexcept {
				return hit.m_Distance;
			}

			inline void set_distance(Value& hit, float distance) noexcept {
				hit.m_Distance = distance;
			}

			inline std::uint32_t get_face_id(const Value& hit) noexcept {
				return hit.m_FaceID;
			}

			inline Vector2Value get_uv(const Value& hit) noexcept {
				return hit.m_UV;
			}

			inline std::int32_t get_collider_instance_id(const Value& hit) noexcept {
				return hit.m_Collider;
			}

			inline bool has_collider(const Value& hit) noexcept {
				return hit.m_Collider != 0;
			}

			inline bool is_valid(const Value& hit) noexcept {
				return has_collider(hit)
					&& Vector3::is_finite(hit.m_Point)
					&& Vector3::is_finite(hit.m_Normal)
					&& std::isfinite(hit.m_Distance);
			}

			inline Result<void*> get_collider(Value& hit) {
				return Physics::GetColliderByInstanceID(hit.m_Collider);
			}

			inline Result<void*> get_transform(Value& hit) {
				ThreadScope scope;

				if (!has_collider(hit))
					return { Il2CppStatus::OK, nullptr };

				auto method = _detail::resolve_raycast_hit_method("get_transform", 0);
				if (!method) return { method.status, nullptr };
				if (!method.value->m_pMethodPointer)
					return { Il2CppStatus::MethodPointerNull, nullptr };

				using Fn = void* (__fastcall*)(
					Value* self,
					_internal::unity_structs::il2cppMethodInfo* method
					);

				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);
				return { Il2CppStatus::OK, fn(&hit, method.value) };
			}

			inline Result<void*> get_rigidbody(Value& hit) {
				ThreadScope scope;

				if (!has_collider(hit))
					return { Il2CppStatus::OK, nullptr };

				auto method = _detail::resolve_raycast_hit_method("get_rigidbody", 0);
				if (!method) return { method.status, nullptr };
				if (!method.value->m_pMethodPointer)
					return { Il2CppStatus::MethodPointerNull, nullptr };

				using Fn = void* (__fastcall*)(
					Value* self,
					_internal::unity_structs::il2cppMethodInfo* method
					);

				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);
				return { Il2CppStatus::OK, fn(&hit, method.value) };
			}
		} // namespace RaycastHit

		namespace Object {
			namespace _find_detail {
				inline Result<void*> first_from_object_array(void* array) {
					return Array::first_ref(array);
				}

				inline Result<void*> FindObjectsByTypeIcall(void* type_instance, FindObjectsInactive inactive, FindObjectsSortMode sort_mode) {
					ThreadScope scope;

					if (!type_instance) return { Il2CppStatus::InvalidArgs, nullptr };

					using Fn = void* (__fastcall*)(void*, int32_t, int32_t);
					static Fn s_find_objects_by_type_3 = nullptr;

					if (!s_find_objects_by_type_3) {
						auto resolved = il2cpp::resolve_icall(
							"UnityEngine.Object::FindObjectsByType(System.Type,UnityEngine.FindObjectsInactive,UnityEngine.FindObjectsSortMode)"
						);

						if (resolved && resolved.value) {
							s_find_objects_by_type_3 = reinterpret_cast<Fn>(resolved.value);
						}
					}

					if (!s_find_objects_by_type_3) return { Il2CppStatus::MethodNotFound, nullptr };

					return {
						Il2CppStatus::OK,
						s_find_objects_by_type_3(
							type_instance, 
							static_cast<int32_t>(inactive),
							static_cast<int32_t>(sort_mode)
						)
					};
				}
			}

			inline Result<void*> FindObjectsByType(
				void* type_instance,
				FindObjectsInactive find_objects_inactive,
				FindObjectsSortMode sort_mode
			);

			inline Result<void*> FindObjectsByType(
				void* type_instance,
				FindObjectsSortMode sort_mode = FindObjectsSortMode::None
			) {
				return FindObjectsByType(
					type_instance,
					FindObjectsInactive::Exclude,
					sort_mode
				);
			}

			inline Result<void*> FindObjectsByType(
				void* type_instance,
				FindObjectsInactive find_objects_inactive,
				FindObjectsSortMode sort_mode
			) {
				ThreadScope scope;

				if (!type_instance)
					return { Il2CppStatus::InvalidArgs, nullptr };

				auto method = _detail::resolve_find_objects_by_type_method(3);

				if (method && method.value->m_pMethodPointer) {
					using Fn = void* (__fastcall*)(
						void* type_instance,
						int32_t find_objects_inactive,
						int32_t sort_mode,
						_internal::unity_structs::il2cppMethodInfo* method
						);

					auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

					return {
						Il2CppStatus::OK,
						fn(
							type_instance,
							static_cast<int32_t>(find_objects_inactive),
							static_cast<int32_t>(sort_mode),
							method.value
						)
					};
				}

				auto icall3 = _find_detail::FindObjectsByTypeIcall(
					type_instance,
					find_objects_inactive,
					sort_mode
				);

				if (icall3)
					return icall3;

				if (!method)
					return { method.status, nullptr };

				return { Il2CppStatus::MethodPointerNull, nullptr };
			}

			inline Result<int32_t> GetInstanceID(void* unity_object) {
				ThreadScope scope;
				if (!unity_object) return { Il2CppStatus::InvalidArgs, 0 };

				auto method = _detail::resolve_object_method("GetInstanceID", 0);
				if (!method) return { method.status, 0 };
				if (!method.value->m_pMethodPointer) return { Il2CppStatus::MethodPointerNull, 0 };

				using Fn = int32_t(__fastcall*)(void*, _internal::unity_structs::il2cppMethodInfo*);
				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);
				return { Il2CppStatus::OK, fn(unity_object, method.value) };
			}

			inline Result<void*> GetTypeObject(void* unity_object) {
				ThreadScope scope;
				if (!unity_object) return { Il2CppStatus::InvalidArgs, nullptr };

				auto method = _detail::resolve_object_method("GetType", 0);
				if (!method) return { method.status, nullptr };
				if (!method.value->m_pMethodPointer) return { Il2CppStatus::MethodPointerNull, nullptr };

				using Fn = void* (__fastcall*)(void*, _internal::unity_structs::il2cppMethodInfo*);
				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);
				return { Il2CppStatus::OK, fn(unity_object, method.value) };
			}

			inline Result<std::string> GetTypeName(void* unity_object) {
				ThreadScope scope;
				auto type_obj = GetTypeObject(unity_object);
				if (!type_obj) return { type_obj.status, {} };
				if (!type_obj.value) return { Il2CppStatus::ClassNotFound, {} };

				static constexpr const char* kAsmCandidates[] = {
					"mscorlib",
					"System.Private.CoreLib"
				};
				Il2CppStatus last = Il2CppStatus::MethodNotFound;
				using Fn = void* (__fastcall*)(void*, _internal::unity_structs::il2cppMethodInfo*);

				for (auto* asm_name : kAsmCandidates) {
					auto m = il2cpp::get_method("System", "Type", "get_FullNameOrDefault", asm_name, 0);
					if (!m) { last = m.status; continue; }
					if (!m.value->m_pMethodPointer) return { Il2CppStatus::MethodPointerNull, {} };
					auto fn = reinterpret_cast<Fn>(m.value->m_pMethodPointer);
					void* str = fn(type_obj.value, m.value);
					if (str) return { Il2CppStatus::OK, il2cpp::String::convert_to_std_string(str) };
				}

				for (auto* asm_name : kAsmCandidates) {
					auto m = il2cpp::get_method("System", "Type", "get_NameOrDefault", asm_name, 0);
					if (!m) { last = m.status; continue; }
					if (!m.value->m_pMethodPointer) return { Il2CppStatus::MethodPointerNull, {} };
					auto fn = reinterpret_cast<Fn>(m.value->m_pMethodPointer);
					void* str = fn(type_obj.value, m.value);
					if (str) return { Il2CppStatus::OK, il2cpp::String::convert_to_std_string(str) };
				}

				return { last, {} };
			}

			inline Result<std::string> GetTypeFullName(void* unity_object) {
				ThreadScope scope;
				auto type_obj = GetTypeObject(unity_object);
				if (!type_obj) return { type_obj.status, {} };
				if (!type_obj.value) return { Il2CppStatus::ClassNotFound, {} };

				static constexpr const char* kAsmCandidates[] = {
					"mscorlib",
					"System.Private.CoreLib"
				};
				Il2CppStatus last = Il2CppStatus::MethodNotFound;
				for (auto* asm_name : kAsmCandidates) {
					auto m = il2cpp::get_method("System", "Type", "get_FullNameOrDefault", asm_name, 0);
					if (!m) { last = m.status; continue; }
					if (!m.value->m_pMethodPointer) return { Il2CppStatus::MethodPointerNull, {} };
					using Fn = void* (__fastcall*)(void*, _internal::unity_structs::il2cppMethodInfo*);
					auto fn = reinterpret_cast<Fn>(m.value->m_pMethodPointer);
					void* str = fn(type_obj.value, m.value);
					if (str) return { Il2CppStatus::OK, il2cpp::String::convert_to_std_string(str) };
				}
				return { last, {} };
			}

			inline Result<std::string> GetTypeShortName(void* unity_object) {
				ThreadScope scope;
				auto type_obj = GetTypeObject(unity_object);
				if (!type_obj) return { type_obj.status, {} };
				if (!type_obj.value) return { Il2CppStatus::ClassNotFound, {} };

				static constexpr const char* kAsmCandidates[] = {
					"mscorlib",
					"System.Private.CoreLib"
				};
				Il2CppStatus last = Il2CppStatus::MethodNotFound;
				for (auto* asm_name : kAsmCandidates) {
					auto m = il2cpp::get_method("System", "Type", "get_NameOrDefault", asm_name, 0);
					if (!m) { last = m.status; continue; }
					if (!m.value->m_pMethodPointer) return { Il2CppStatus::MethodPointerNull, {} };
					using Fn = void* (__fastcall*)(void*, _internal::unity_structs::il2cppMethodInfo*);
					auto fn = reinterpret_cast<Fn>(m.value->m_pMethodPointer);
					void* str = fn(type_obj.value, m.value);
					if (str) return { Il2CppStatus::OK, il2cpp::String::convert_to_std_string(str) };
				}
				return { last, {} };
			}

			inline Result<std::string> get_name(void* unity_object) {
				return UnityEngine::get_name(unity_object);
			}
		}

		namespace GameObject {

			inline Result<bool> get_activeSelf(void* game_object) {
				ThreadScope scope;
				if (!game_object) return { Il2CppStatus::InvalidArgs, false };

				auto method = _detail::resolve_game_object_method("get_activeSelf", 0);
				if (!method) return { method.status, false };
				if (!method.value->m_pMethodPointer) return { Il2CppStatus::MethodPointerNull, false };

				using Fn = bool(__fastcall*)(void*, _internal::unity_structs::il2cppMethodInfo*);
				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);
				return { Il2CppStatus::OK, fn(game_object, method.value) };
			}

			inline Result<bool> get_activeInHierarchy(void* game_object) {
				ThreadScope scope;
				if (!game_object) return { Il2CppStatus::InvalidArgs, false };

				auto method = _detail::resolve_game_object_method("get_activeInHierarchy", 0);
				if (!method) return { method.status, false };
				if (!method.value->m_pMethodPointer) return { Il2CppStatus::MethodPointerNull, false };

				using Fn = bool(__fastcall*)(void*, _internal::unity_structs::il2cppMethodInfo*);
				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);
				return { Il2CppStatus::OK, fn(game_object, method.value) };
			}

			inline Result<void*> get_transform(void* game_object) {
				ThreadScope scope;
				if (!game_object) return { Il2CppStatus::InvalidArgs, nullptr };

				auto method = _detail::resolve_game_object_method("get_transform", 0);
				if (!method) return { method.status, nullptr };
				if (!method.value->m_pMethodPointer) return { Il2CppStatus::MethodPointerNull, nullptr };

				using Fn = void* (__fastcall*)(void*, _internal::unity_structs::il2cppMethodInfo*);
				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);
				return { Il2CppStatus::OK, fn(game_object, method.value) };
			}

			inline Result<void*> GetComponents(void* game_object, void* type_instance) {
				ThreadScope scope;
				if (!game_object || !type_instance) return { Il2CppStatus::InvalidArgs, nullptr };

				// Use the same robust resolver path as other GameObject calls.
				// Signature-based lookup can fail across Unity/metadata variants even when method exists.
				auto method = _detail::resolve_game_object_method("GetComponents", 1);
				if (!method) return { method.status, nullptr };
				if (!method.value->m_pMethodPointer) return { Il2CppStatus::MethodPointerNull, nullptr };

				using Fn = void* (__fastcall*)(void*, void*, _internal::unity_structs::il2cppMethodInfo*);
				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);
				return { Il2CppStatus::OK, fn(game_object, type_instance, method.value) };
			}

		} // namespace GameObject

		namespace Transform {
			using Vector3Value = Types::Vector3;
			using QuaternionValue = Types::Quaternion;

			inline Result<Vector3Value> get_position(void* transform) {
				ThreadScope scope;
				if (!transform) return { Il2CppStatus::InvalidArgs, {} };

				auto method = _detail::resolve_transform_method("get_position_Injected", 1);
				if (!method) return { method.status, {} };
				if (!method.value->m_pMethodPointer) return { Il2CppStatus::MethodPointerNull, {} };

				using Fn = void(__fastcall*)(void*, Vector3Value*, _internal::unity_structs::il2cppMethodInfo*);
				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

				Vector3Value out{};
				fn(transform, &out, method.value);

				return { Il2CppStatus::OK, out };
			}

			inline Il2CppStatus set_position(void* transform, const Vector3Value& value) {
				ThreadScope scope;
				if (!transform) return Il2CppStatus::InvalidArgs;

				auto method = _detail::resolve_transform_method("set_position_Injected", 1);
				if (!method) return method.status;
				if (!method.value->m_pMethodPointer) return Il2CppStatus::MethodPointerNull;

				using Fn = void(__fastcall*)(void*, const Vector3Value*, _internal::unity_structs::il2cppMethodInfo*);
				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

				fn(transform, &value, method.value);
				return Il2CppStatus::OK;
			}

			inline Result<Vector3Value> get_localPosition(void* transform) {
				ThreadScope scope;
				if (!transform) return { Il2CppStatus::InvalidArgs, {} };

				auto method = _detail::resolve_transform_method("get_localPosition_Injected", 1);
				if (!method) return { method.status, {} };
				if (!method.value->m_pMethodPointer) return { Il2CppStatus::MethodPointerNull, {} };

				using Fn = void(__fastcall*)(void*, Vector3Value*, _internal::unity_structs::il2cppMethodInfo*);
				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

				Vector3Value out{};
				fn(transform, &out, method.value);

				return { Il2CppStatus::OK, out };
			}

			inline Il2CppStatus set_localPosition(void* transform, const Vector3Value& value) {
				ThreadScope scope;
				if (!transform) return Il2CppStatus::InvalidArgs;

				auto method = _detail::resolve_transform_method("set_localPosition_Injected", 1);
				if (!method) return method.status;
				if (!method.value->m_pMethodPointer) return Il2CppStatus::MethodPointerNull;

				using Fn = void(__fastcall*)(void*, const Vector3Value*, _internal::unity_structs::il2cppMethodInfo*);
				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

				fn(transform, &value, method.value);
				return Il2CppStatus::OK;
			}

			inline Result<Vector3Value> get_localScale(void* transform) {
				ThreadScope scope;
				if (!transform) return { Il2CppStatus::InvalidArgs, {} };

				auto method = _detail::resolve_transform_method("get_localScale_Injected", 1);
				if (!method) return { method.status, {} };
				if (!method.value->m_pMethodPointer) return { Il2CppStatus::MethodPointerNull, {} };

				using Fn = void(__fastcall*)(void*, Vector3Value*, _internal::unity_structs::il2cppMethodInfo*);
				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

				Vector3Value out{};
				fn(transform, &out, method.value);

				return { Il2CppStatus::OK, out };
			}

			inline Il2CppStatus set_localScale(void* transform, const Vector3Value& value) {
				ThreadScope scope;
				if (!transform) return Il2CppStatus::InvalidArgs;

				auto method = _detail::resolve_transform_method("set_localScale_Injected", 1);
				if (!method) return method.status;
				if (!method.value->m_pMethodPointer) return Il2CppStatus::MethodPointerNull;

				using Fn = void(__fastcall*)(void*, const Vector3Value*, _internal::unity_structs::il2cppMethodInfo*);
				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

				fn(transform, &value, method.value);
				return Il2CppStatus::OK;
			}

			inline Result<Vector3Value> get_lossyScale(void* transform) {
				ThreadScope scope;
				if (!transform) return { Il2CppStatus::InvalidArgs, {} };

				auto method = _detail::resolve_transform_method("get_lossyScale_Injected", 1);
				if (!method) return { method.status, {} };
				if (!method.value->m_pMethodPointer) return { Il2CppStatus::MethodPointerNull, {} };

				using Fn = void(__fastcall*)(void*, Vector3Value*, _internal::unity_structs::il2cppMethodInfo*);
				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

				Vector3Value out{};
				fn(transform, &out, method.value);

				return { Il2CppStatus::OK, out };
			}

			inline Result<QuaternionValue> get_rotation(void* transform) {
				ThreadScope scope;
				if (!transform) return { Il2CppStatus::InvalidArgs, {} };

				auto method = _detail::resolve_transform_method("get_rotation_Injected", 1);
				if (!method) return { method.status, {} };
				if (!method.value->m_pMethodPointer) return { Il2CppStatus::MethodPointerNull, {} };

				using Fn = void(__fastcall*)(void*, QuaternionValue*, _internal::unity_structs::il2cppMethodInfo*);
				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

				QuaternionValue out{};
				fn(transform, &out, method.value);

				return { Il2CppStatus::OK, out };
			}

			inline Il2CppStatus set_rotation(void* transform, const QuaternionValue& value) {
				ThreadScope scope;
				if (!transform) return Il2CppStatus::InvalidArgs;

				auto method = _detail::resolve_transform_method("set_rotation_Injected", 1);
				if (!method) return method.status;
				if (!method.value->m_pMethodPointer) return Il2CppStatus::MethodPointerNull;

				using Fn = void(__fastcall*)(void*, const QuaternionValue*, _internal::unity_structs::il2cppMethodInfo*);
				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

				fn(transform, &value, method.value);
				return Il2CppStatus::OK;
			}

			inline Result<QuaternionValue> get_localRotation(void* transform) {
				ThreadScope scope;
				if (!transform) return { Il2CppStatus::InvalidArgs, {} };

				auto method = _detail::resolve_transform_method("get_localRotation_Injected", 1);
				if (!method) return { method.status, {} };
				if (!method.value->m_pMethodPointer) return { Il2CppStatus::MethodPointerNull, {} };

				using Fn = void(__fastcall*)(void*, QuaternionValue*, _internal::unity_structs::il2cppMethodInfo*);
				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

				QuaternionValue out{};
				fn(transform, &out, method.value);

				return { Il2CppStatus::OK, out };
			}

			inline Il2CppStatus set_localRotation(void* transform, const QuaternionValue& value) {
				ThreadScope scope;
				if (!transform) return Il2CppStatus::InvalidArgs;

				auto method = _detail::resolve_transform_method("set_localRotation_Injected", 1);
				if (!method) return method.status;
				if (!method.value->m_pMethodPointer) return Il2CppStatus::MethodPointerNull;

				using Fn = void(__fastcall*)(void*, const QuaternionValue*, _internal::unity_structs::il2cppMethodInfo*);
				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

				fn(transform, &value, method.value);
				return Il2CppStatus::OK;
			}

			inline Result<void*> get_parent(void* transform) {
				ThreadScope scope;
				if (!transform) return { Il2CppStatus::InvalidArgs, nullptr };

				auto method = _detail::resolve_transform_method("get_parent", 0);
				if (!method) return { method.status, nullptr };
				if (!method.value->m_pMethodPointer) return { Il2CppStatus::MethodPointerNull, nullptr };

				using Fn = void* (__fastcall*)(void*, _internal::unity_structs::il2cppMethodInfo*);
				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

				return { Il2CppStatus::OK, fn(transform, method.value) };
			}

			inline Il2CppStatus SetParent(void* transform, void* parent, bool world_position_stays = true) {
				ThreadScope scope;
				if (!transform) return Il2CppStatus::InvalidArgs;

				auto method = _detail::resolve_transform_method("SetParent", 2);
				if (!method) return method.status;
				if (!method.value->m_pMethodPointer) return Il2CppStatus::MethodPointerNull;

				using Fn = void(__fastcall*)(void*, void*, bool, _internal::unity_structs::il2cppMethodInfo*);
				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

				fn(transform, parent, world_position_stays, method.value);
				return Il2CppStatus::OK;
			}

			inline Il2CppStatus set_parent(void* transform, void* parent) {
				return SetParent(transform, parent, true);
			}

			inline Result<void*> get_root(void* transform) {
				ThreadScope scope;
				if (!transform) return { Il2CppStatus::InvalidArgs, nullptr };

				auto method = _detail::resolve_transform_method("GetRoot", 0);
				if (!method) method = _detail::resolve_transform_method("get_root", 0);
				if (!method) return { method.status, nullptr };
				if (!method.value->m_pMethodPointer) return { Il2CppStatus::MethodPointerNull, nullptr };

				using Fn = void* (__fastcall*)(void*, _internal::unity_structs::il2cppMethodInfo*);
				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

				return { Il2CppStatus::OK, fn(transform, method.value) };
			}

			inline Result<int32_t> get_childCount(void* transform) {
				ThreadScope scope;
				if (!transform) return { Il2CppStatus::InvalidArgs, 0 };

				auto method = _detail::resolve_transform_method("get_childCount", 0);
				if (!method) return { method.status, 0 };
				if (!method.value->m_pMethodPointer) return { Il2CppStatus::MethodPointerNull, 0 };

				using Fn = int32_t(__fastcall*)(void*, _internal::unity_structs::il2cppMethodInfo*);
				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

				return { Il2CppStatus::OK, fn(transform, method.value) };
			}

			inline Result<void*> GetChild(void* transform, int32_t index) {
				ThreadScope scope;
				if (!transform || index < 0) return { Il2CppStatus::InvalidArgs, nullptr };

				auto count = get_childCount(transform);
				if (!count) return { count.status, nullptr };
				if (index >= count.value) return { Il2CppStatus::InvalidArgs, nullptr };

				auto method = _detail::resolve_transform_method("GetChild", 1);
				if (!method) return { method.status, nullptr };
				if (!method.value->m_pMethodPointer) return { Il2CppStatus::MethodPointerNull, nullptr };

				using Fn = void* (__fastcall*)(void*, int32_t, _internal::unity_structs::il2cppMethodInfo*);
				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

				return { Il2CppStatus::OK, fn(transform, index, method.value) };
			}

			inline Result<Vector3Value> TransformPoint(void* transform, const Vector3Value& position) {
				ThreadScope scope;
				if (!transform) return { Il2CppStatus::InvalidArgs, {} };

				auto method = _detail::resolve_transform_method("TransformPoint_Injected", 2);
				if (!method) return { method.status, {} };
				if (!method.value->m_pMethodPointer) return { Il2CppStatus::MethodPointerNull, {} };

				using Fn = void(__fastcall*)(void*, const Vector3Value*, Vector3Value*, _internal::unity_structs::il2cppMethodInfo*);
				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

				Vector3Value out{};
				fn(transform, &position, &out, method.value);

				return { Il2CppStatus::OK, out };
			}

			inline Result<Vector3Value> InverseTransformPoint(void* transform, const Vector3Value& position) {
				ThreadScope scope;
				if (!transform) return { Il2CppStatus::InvalidArgs, {} };

				auto method = _detail::resolve_transform_method("InverseTransformPoint_Injected", 2);
				if (!method) return { method.status, {} };
				if (!method.value->m_pMethodPointer) return { Il2CppStatus::MethodPointerNull, {} };

				using Fn = void(__fastcall*)(void*, const Vector3Value*, Vector3Value*, _internal::unity_structs::il2cppMethodInfo*);
				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

				Vector3Value out{};
				fn(transform, &position, &out, method.value);

				return { Il2CppStatus::OK, out };
			}

			inline Result<Vector3Value> TransformDirection(void* transform, const Vector3Value& direction) {
				ThreadScope scope;
				if (!transform) return { Il2CppStatus::InvalidArgs, {} };

				auto method = _detail::resolve_transform_method("TransformDirection_Injected", 2);
				if (!method) return { method.status, {} };
				if (!method.value->m_pMethodPointer) return { Il2CppStatus::MethodPointerNull, {} };

				using Fn = void(__fastcall*)(void*, const Vector3Value*, Vector3Value*, _internal::unity_structs::il2cppMethodInfo*);
				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

				Vector3Value out{};
				fn(transform, &direction, &out, method.value);

				return { Il2CppStatus::OK, out };
			}

			inline Result<Vector3Value> InverseTransformDirection(void* transform, const Vector3Value& direction) {
				ThreadScope scope;
				if (!transform) return { Il2CppStatus::InvalidArgs, {} };

				auto method = _detail::resolve_transform_method("InverseTransformDirection_Injected", 2);
				if (!method) return { method.status, {} };
				if (!method.value->m_pMethodPointer) return { Il2CppStatus::MethodPointerNull, {} };

				using Fn = void(__fastcall*)(void*, const Vector3Value*, Vector3Value*, _internal::unity_structs::il2cppMethodInfo*);
				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

				Vector3Value out{};
				fn(transform, &direction, &out, method.value);

				return { Il2CppStatus::OK, out };
			}

			inline Result<Types::Vector3> get_forward(void* transform) {
				auto rot = get_rotation(transform);
				if (!rot) return { rot.status, {} };
				return { Il2CppStatus::OK, Quaternion::forward(rot.value) };
			}

			inline Result<Types::Vector3> get_right(void* transform) {
				auto rot = get_rotation(transform);
				if (!rot) return { rot.status, {} };
				return { Il2CppStatus::OK, Quaternion::right(rot.value) };
			}

			inline Result<Types::Vector3> get_up(void* transform) {
				auto rot = get_rotation(transform);
				if (!rot) return { rot.status, {} };
				return { Il2CppStatus::OK, Quaternion::up(rot.value) };
			}
		} // namespace Transform

		namespace Component {

			inline Result<void*> get_gameObject(void* component) {
				ThreadScope scope;

				if (!component)
					return { Il2CppStatus::InvalidArgs, nullptr };

				auto method = _detail::resolve_component_method("get_gameObject", 0);
				if (!method)
					return { method.status, nullptr };

				if (!method.value->m_pMethodPointer)
					return { Il2CppStatus::MethodPointerNull, nullptr };

				using Fn = void* (__fastcall*)(
					void* self,
					_internal::unity_structs::il2cppMethodInfo* method
					);

				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

				return { Il2CppStatus::OK, fn(component, method.value) };
			}

			inline Result<void*> get_transform(void* component) {
				ThreadScope scope;

				if (!component)
					return { Il2CppStatus::InvalidArgs, nullptr };

				auto method = _detail::resolve_component_method("get_transform", 0);
				if (!method)
					return { method.status, nullptr };

				if (!method.value->m_pMethodPointer)
					return { Il2CppStatus::MethodPointerNull, nullptr };

				using Fn = void* (__fastcall*)(
					void* self,
					_internal::unity_structs::il2cppMethodInfo* method
				);

				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

				return { Il2CppStatus::OK, fn(component, method.value) };
			}

			inline Result<void*> GetComponent(void* component, void* type_instance) {
				ThreadScope scope;

				if (!component || !type_instance)
					return { Il2CppStatus::InvalidArgs, nullptr };

				auto method = _detail::resolve_component_method(
					"GetComponent",
					{ "System.Type" }
				);

				if (!method)
					return { method.status, nullptr };

				if (!method.value->m_pMethodPointer)
					return { Il2CppStatus::MethodPointerNull, nullptr };

				using Fn = void* (__fastcall*)(
					void* self,
					void* type_instance,
					_internal::unity_structs::il2cppMethodInfo* method
				);

				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

				return { Il2CppStatus::OK, fn(component, type_instance, method.value) };
			}

			inline Result<void*> GetComponent(void* component, const std::string& type_name) {
				if (!component || type_name.empty())
					return { Il2CppStatus::InvalidArgs, nullptr };

				auto type = il2cpp::Type::GetType(type_name);
				if (!type)
					return { type.status, nullptr };

				return GetComponent(component, type.value);
			}

			inline Result<void*> GetComponents(void* component, void* type_instance) {
				ThreadScope scope;

				if (!component || !type_instance)
					return { Il2CppStatus::InvalidArgs, nullptr };

				auto method = _detail::resolve_component_method(
					"GetComponents",
					{ "System.Type" }
				);

				if (!method)
					return { method.status, nullptr };

				if (!method.value->m_pMethodPointer)
					return { Il2CppStatus::MethodPointerNull, nullptr };

				using Fn = void* (__fastcall*)(
					void* self,
					void* type_instance,
					_internal::unity_structs::il2cppMethodInfo* method
				);

				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

				return { Il2CppStatus::OK, fn(component, type_instance, method.value) };
			}

			inline Result<void*> GetComponents(void* component, const std::string& type_name) {
				if (!component || type_name.empty())
					return { Il2CppStatus::InvalidArgs, nullptr };

				auto type = il2cpp::Type::GetType(type_name);
				if (!type)
					return { type.status, nullptr };

				return GetComponents(component, type.value);
			}

			inline Result<void*> GetComponentInChildren(
				void* component,
				void* type_instance,
				bool include_inactive = false
			) {
				ThreadScope scope;

				if (!component || !type_instance)
					return { Il2CppStatus::InvalidArgs, nullptr };

				auto method = _detail::resolve_component_method(
					"GetComponentInChildren",
					{ "System.Type", "System.Boolean" }
				);

				if (!method) {
					// Fallback for older Unity versions: GetComponentInChildren(Type)
					auto m1 = _detail::resolve_component_method(
						"GetComponentInChildren",
						{ "System.Type" }
					);

					if (!m1)
						return { method.status, nullptr };

					if (!m1.value->m_pMethodPointer)
						return { Il2CppStatus::MethodPointerNull, nullptr };

					using Fn1 = void* (__fastcall*)(
						void* self,
						void* type_instance,
						_internal::unity_structs::il2cppMethodInfo* method
						);

					auto fn1 = reinterpret_cast<Fn1>(m1.value->m_pMethodPointer);

					return { Il2CppStatus::OK, fn1(component, type_instance, m1.value) };
				}

				if (!method.value->m_pMethodPointer)
					return { Il2CppStatus::MethodPointerNull, nullptr };

				using Fn = void* (__fastcall*)(
					void* self,
					void* type_instance,
					bool include_inactive,
					_internal::unity_structs::il2cppMethodInfo* method
					);

				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

				return {
					Il2CppStatus::OK,
					fn(component, type_instance, include_inactive, method.value)
				};
			}

			inline Result<void*> GetComponentInChildren(
				void* component,
				const std::string& type_name,
				bool include_inactive = false
			) {
				if (!component || type_name.empty())
					return { Il2CppStatus::InvalidArgs, nullptr };

				auto type = il2cpp::Type::GetType(type_name);
				if (!type)
					return { type.status, nullptr };

				return GetComponentInChildren(component, type.value, include_inactive);
			}

			inline Result<void*> GetComponentsInChildren(
				void* component,
				void* type_instance,
				bool include_inactive = false
			) {
				ThreadScope scope;

				if (!component || !type_instance)
					return { Il2CppStatus::InvalidArgs, nullptr };

				auto method = _detail::resolve_component_method(
					"GetComponentsInChildren",
					{ "System.Type", "System.Boolean" }
				);

				if (!method)
					return { method.status, nullptr };

				if (!method.value->m_pMethodPointer)
					return { Il2CppStatus::MethodPointerNull, nullptr };

				using Fn = void* (__fastcall*)(
					void* self,
					void* type_instance,
					bool include_inactive,
					_internal::unity_structs::il2cppMethodInfo* method
					);

				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

				return {
					Il2CppStatus::OK,
					fn(component, type_instance, include_inactive, method.value)
				};
			}

			inline Result<void*> GetComponentsInChildren(
				void* component,
				const std::string& type_name,
				bool include_inactive = false
			) {
				if (!component || type_name.empty())
					return { Il2CppStatus::InvalidArgs, nullptr };

				auto type = il2cpp::Type::GetType(type_name);
				if (!type)
					return { type.status, nullptr };

				return GetComponentsInChildren(component, type.value, include_inactive);
			}

			inline Result<void*> GetComponentInParent(
				void* component,
				void* type_instance,
				bool include_inactive = false
			) {
				ThreadScope scope;

				if (!component || !type_instance)
					return { Il2CppStatus::InvalidArgs, nullptr };

				auto method = _detail::resolve_component_method(
					"GetComponentInParent",
					{ "System.Type", "System.Boolean" }
				);

				if (!method) {
					// Fallback for older Unity versions: GetComponentInParent(Type)
					auto m1 = _detail::resolve_component_method(
						"GetComponentInParent",
						{ "System.Type" }
					);

					if (!m1)
						return { method.status, nullptr };

					if (!m1.value->m_pMethodPointer)
						return { Il2CppStatus::MethodPointerNull, nullptr };

					using Fn1 = void* (__fastcall*)(
						void* self,
						void* type_instance,
						_internal::unity_structs::il2cppMethodInfo* method
						);

					auto fn1 = reinterpret_cast<Fn1>(m1.value->m_pMethodPointer);

					return { Il2CppStatus::OK, fn1(component, type_instance, m1.value) };
				}

				if (!method.value->m_pMethodPointer)
					return { Il2CppStatus::MethodPointerNull, nullptr };

				using Fn = void* (__fastcall*)(
					void* self,
					void* type_instance,
					bool include_inactive,
					_internal::unity_structs::il2cppMethodInfo* method
					);

				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

				return {
					Il2CppStatus::OK,
					fn(component, type_instance, include_inactive, method.value)
				};
			}

			inline Result<void*> GetComponentInParent(
				void* component,
				const std::string& type_name,
				bool include_inactive = false
			) {
				if (!component || type_name.empty())
					return { Il2CppStatus::InvalidArgs, nullptr };

				auto type = il2cpp::Type::GetType(type_name);
				if (!type)
					return { type.status, nullptr };

				return GetComponentInParent(component, type.value, include_inactive);
			}

			inline Result<void*> GetComponentsInParent(
				void* component,
				void* type_instance,
				bool include_inactive = false
			) {
				ThreadScope scope;

				if (!component || !type_instance)
					return { Il2CppStatus::InvalidArgs, nullptr };

				auto method = _detail::resolve_component_method(
					"GetComponentsInParent",
					{ "System.Type", "System.Boolean" }
				);

				if (!method)
					return { method.status, nullptr };

				if (!method.value->m_pMethodPointer)
					return { Il2CppStatus::MethodPointerNull, nullptr };

				using Fn = void* (__fastcall*)(
					void* self,
					void* type_instance,
					bool include_inactive,
					_internal::unity_structs::il2cppMethodInfo* method
					);

				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

				return {
					Il2CppStatus::OK,
					fn(component, type_instance, include_inactive, method.value)
				};
			}

			inline Result<void*> GetComponentsInParent(
				void* component,
				const std::string& type_name,
				bool include_inactive = false
			) {
				if (!component || type_name.empty())
					return { Il2CppStatus::InvalidArgs, nullptr };

				auto type = il2cpp::Type::GetType(type_name);
				if (!type)
					return { type.status, nullptr };

				return GetComponentsInParent(component, type.value, include_inactive);
			}

			inline Result<bool> TryGetComponent(
				void* component,
				void* type_instance,
				void*& out_component
			) {
				ThreadScope scope;

				out_component = nullptr;

				if (!component || !type_instance)
					return { Il2CppStatus::InvalidArgs, false };

				auto method = _detail::resolve_component_method(
					"TryGetComponent",
					{ "System.Type", "UnityEngine.Component&" }
				);

				if (!method)
					return { method.status, false };

				if (!method.value->m_pMethodPointer)
					return { Il2CppStatus::MethodPointerNull, false };

				using Fn = bool(__fastcall*)(
					void* self,
					void* type_instance,
					void** out_component,
					_internal::unity_structs::il2cppMethodInfo* method
					);

				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

				const bool ok = fn(component, type_instance, &out_component, method.value);

				return { Il2CppStatus::OK, ok };
			}

			inline Result<bool> TryGetComponent(
				void* component,
				const std::string& type_name,
				void*& out_component
			) {
				out_component = nullptr;

				if (!component || type_name.empty())
					return { Il2CppStatus::InvalidArgs, false };

				auto type = il2cpp::Type::GetType(type_name);
				if (!type)
					return { type.status, false };

				return TryGetComponent(component, type.value, out_component);
			}

		} // namespace Component

		namespace SceneManagement {

			namespace _detail {

				inline Result<_internal::unity_structs::il2cppMethodInfo*>
					resolve_scene_manager_method(const char* method_name, int param_count) {
					static constexpr const char* kAssemblyCandidates[] = {
						"UnityEngine.CoreModule",
						"UnityEngine",
					};
					Il2CppStatus last = Il2CppStatus::MethodNotFound;
					for (auto* asm_name : kAssemblyCandidates) {
						auto m = il2cpp::get_method("UnityEngine.SceneManagement", "SceneManager",
							method_name, asm_name, param_count);
						if (m) return m;
						last = m.status;
					}
					return { last, nullptr };
				}

				inline Result<_internal::unity_structs::il2cppMethodInfo*>
					resolve_scene_method(const char* method_name, int param_count) {
					static constexpr const char* kAssemblyCandidates[] = {
						"UnityEngine.CoreModule",
						"UnityEngine",
					};
					Il2CppStatus last = Il2CppStatus::MethodNotFound;
					for (auto* asm_name : kAssemblyCandidates) {
						auto m = il2cpp::get_method("UnityEngine.SceneManagement", "Scene",
							method_name, asm_name, param_count);
						if (m) return m;
						last = m.status;
					}
					return { last, nullptr };
				}

				inline Result<_internal::unity_structs::il2cppMethodInfo*>
					resolve_game_object_method(const char* method_name, int param_count) {
					static constexpr const char* kAssemblyCandidates[] = {
						"UnityEngine.CoreModule",
						"UnityEngine",
					};
					Il2CppStatus last = Il2CppStatus::MethodNotFound;
					for (auto* asm_name : kAssemblyCandidates) {
						auto m = il2cpp::get_method("UnityEngine", "GameObject",
							method_name, asm_name, param_count);
						if (m) return m;
						last = m.status;
					}
					return { last, nullptr };
				}

			} // namespace _detail

			// Temporary storage for UnityEngine.SceneManagement.Scene value returns.
			// This is used only as ABI transport for value-type return/sret; we do not parse raw fields.
			constexpr std::size_t kSceneValueBufferBytes = 128;

			// Reads Scene.handle via managed API methods on the scene value.
			inline Result<int32_t> scene_handle_from_value_buffer(void* scene_value_ptr) {
				ThreadScope scope;
				if (!scene_value_ptr) return { Il2CppStatus::InvalidArgs, 0 };

				static constexpr const char* kHandleGetterNames[] = { "get_handle", "get_Handle" };
				for (const char* getter : kHandleGetterNames) {
					auto m = _detail::resolve_scene_method(getter, 0);
					if (m && m.value->m_pMethodPointer) {
						using Fn = int32_t(__fastcall*)(void*, _internal::unity_structs::il2cppMethodInfo*);
						auto fn = reinterpret_cast<Fn>(m.value->m_pMethodPointer);
						return { Il2CppStatus::OK, fn(scene_value_ptr, m.value) };
					}
				}

				// Fallback: Scene.GetHashCode() maps to handle in many Unity versions.
				// Prefer this over raw-field access to keep compatibility across layout changes.
				auto hash_method = _detail::resolve_scene_method("GetHashCode", 0);
				if (hash_method && hash_method.value->m_pMethodPointer) {
					using Fn = int32_t(__fastcall*)(void*, _internal::unity_structs::il2cppMethodInfo*);
					auto fn = reinterpret_cast<Fn>(hash_method.value->m_pMethodPointer);
					return { Il2CppStatus::OK, fn(scene_value_ptr, hash_method.value) };
				}
				return { Il2CppStatus::MethodNotFound, 0 };
			}

			// UnityEngine.SceneManagement.SceneManager.GetActiveScene() -> Scene (by ref / sret into buffer).
			inline Il2CppStatus get_active_scene_value(void* scene_value_out, std::size_t scene_value_size) {
				ThreadScope scope;
				if (!scene_value_out || scene_value_size < kSceneValueBufferBytes)
					return Il2CppStatus::InvalidArgs;

				auto method = _detail::resolve_scene_manager_method("GetActiveScene", 0);
				if (!method) return method.status;
				if (!method.value->m_pMethodPointer) return Il2CppStatus::MethodPointerNull;

				std::memset(scene_value_out, 0, scene_value_size);

				using Fn = void(__fastcall*)(void*, _internal::unity_structs::il2cppMethodInfo*);
				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);
				fn(scene_value_out, method.value);
				return Il2CppStatus::OK;
			}

			inline Result<int32_t> get_active_scene_handle() {
				ThreadScope scope;
				alignas(16) unsigned char scene_buf[kSceneValueBufferBytes]{};
				const auto st = get_active_scene_value(scene_buf, sizeof(scene_buf));
				if (st != Il2CppStatus::OK) return { st, 0 };
				return scene_handle_from_value_buffer(scene_buf);
			}

			inline Result<std::string> scene_name_from_value_buffer(void* scene_value_ptr) {
				ThreadScope scope;
				if (!scene_value_ptr) return { Il2CppStatus::InvalidArgs, {} };

				static constexpr const char* kGetterNames[] = { "get_name", "get_Name" };
				for (const char* getter : kGetterNames) {
					auto m = _detail::resolve_scene_method(getter, 0);
					if (!m || !m.value->m_pMethodPointer) continue;
					using Fn = void* (__fastcall*)(void*, _internal::unity_structs::il2cppMethodInfo*);
					auto fn = reinterpret_cast<Fn>(m.value->m_pMethodPointer);
					void* str = fn(scene_value_ptr, m.value);
					if (str) return { Il2CppStatus::OK, il2cpp::String::convert_to_std_string(str) };
				}
				return { Il2CppStatus::MethodNotFound, {} };
			}

			inline Result<std::string> get_active_scene_name() {
				ThreadScope scope;
				alignas(16) unsigned char scene_buf[kSceneValueBufferBytes]{};
				const auto st = get_active_scene_value(scene_buf, sizeof(scene_buf));
				if (st != Il2CppStatus::OK) return { st, {} };
				return scene_name_from_value_buffer(scene_buf);
			}

			// UnityEngine.GameObject.get_scene -> Scene into buffer; then read handle.
			inline Result<int32_t> game_object_scene_handle(void* game_object) {
				ThreadScope scope;
				if (!game_object) return { Il2CppStatus::InvalidArgs, 0 };

				auto method = _detail::resolve_game_object_method("get_scene", 0);
				if (!method) return { method.status, 0 };
				if (!method.value->m_pMethodPointer) return { Il2CppStatus::MethodPointerNull, 0 };

				alignas(16) unsigned char scene_buf[kSceneValueBufferBytes]{};
				std::memset(scene_buf, 0, sizeof(scene_buf));

				using Fn = void(__fastcall*)(void*, void*, _internal::unity_structs::il2cppMethodInfo*);
				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);
				fn(game_object, scene_buf, method.value);

				return scene_handle_from_value_buffer(scene_buf);
			}

			inline Result<std::string> game_object_scene_name(void* game_object) {
				ThreadScope scope;
				if (!game_object) return { Il2CppStatus::InvalidArgs, {} };

				auto method = _detail::resolve_game_object_method("get_scene", 0);
				if (!method) return { method.status, {} };
				if (!method.value->m_pMethodPointer) return { Il2CppStatus::MethodPointerNull, {} };

				alignas(16) unsigned char scene_buf[kSceneValueBufferBytes]{};
				std::memset(scene_buf, 0, sizeof(scene_buf));
				using Fn = void(__fastcall*)(void*, void*, _internal::unity_structs::il2cppMethodInfo*);
				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);
				fn(game_object, scene_buf, method.value);

				return scene_name_from_value_buffer(scene_buf);
			}

		} // namespace SceneManagement

		namespace Camera {
			using Vector2Value = Types::Vector2;
			using Vector3Value = Types::Vector3;
			using RayValue = Types::Ray;

			inline Result<void*> get_main() {
				ThreadScope scope;

				auto method = _detail::resolve_camera_method("get_main", 0);
				if (!method) return { method.status, nullptr };
				if (!method.value->m_pMethodPointer)
					return { Il2CppStatus::MethodPointerNull, nullptr };

				using Fn = void* (__fastcall*)(
					_internal::unity_structs::il2cppMethodInfo* method
				);

				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);
				return { Il2CppStatus::OK, fn(method.value) };
			}

			inline Result<void*> get_current() {
				ThreadScope scope;

				auto method = _detail::resolve_camera_method("get_current", 0);
				if (!method) return { method.status, nullptr };
				if (!method.value->m_pMethodPointer)
					return { Il2CppStatus::MethodPointerNull, nullptr };

				using Fn = void* (__fastcall*)(
					_internal::unity_structs::il2cppMethodInfo* method
					);

				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);
				return { Il2CppStatus::OK, fn(method.value) };
			}

			inline Result<float> get_fieldOfView(void* camera) {
				ThreadScope scope;

				if (!camera)
					return { Il2CppStatus::InvalidArgs, 0.0f };

				auto method = _detail::resolve_camera_method("get_fieldOfView", 0);
				if (!method) return { method.status, 0.0f };
				if (!method.value->m_pMethodPointer)
					return { Il2CppStatus::MethodPointerNull, 0.0f };

				using Fn = float(__fastcall*)(
					void* self,
					_internal::unity_structs::il2cppMethodInfo* method
					);

				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);
				return { Il2CppStatus::OK, fn(camera, method.value) };
			}

			inline Result<float> get_nearClipPlane(void* camera) {
				ThreadScope scope;

				if (!camera)
					return { Il2CppStatus::InvalidArgs, 0.0f };

				auto method = _detail::resolve_camera_method("get_nearClipPlane", 0);
				if (!method) return { method.status, 0.0f };
				if (!method.value->m_pMethodPointer)
					return { Il2CppStatus::MethodPointerNull, 0.0f };

				using Fn = float(__fastcall*)(
					void* self,
					_internal::unity_structs::il2cppMethodInfo* method
					);

				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);
				return { Il2CppStatus::OK, fn(camera, method.value) };
			}

			inline Result<float> get_farClipPlane(void* camera) {
				ThreadScope scope;

				if (!camera)
					return { Il2CppStatus::InvalidArgs, 0.0f };

				auto method = _detail::resolve_camera_method("get_farClipPlane", 0);
				if (!method) return { method.status, 0.0f };
				if (!method.value->m_pMethodPointer)
					return { Il2CppStatus::MethodPointerNull, 0.0f };

				using Fn = float(__fastcall*)(
					void* self,
					_internal::unity_structs::il2cppMethodInfo* method
					);

				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);
				return { Il2CppStatus::OK, fn(camera, method.value) };
			}

			inline Result<Vector3Value> WorldToScreenPoint(
				void* camera,
				const Vector3Value& position,
				MonoOrStereoscopicEye eye = MonoOrStereoscopicEye::Mono
			) {
				ThreadScope scope;

				if (!camera)
					return { Il2CppStatus::InvalidArgs, {} };

				auto method = _detail::resolve_camera_method("WorldToScreenPoint_Injected", 3);
				if (!method) return { method.status, {} };
				if (!method.value->m_pMethodPointer)
					return { Il2CppStatus::MethodPointerNull, {} };

				using Fn = void(__fastcall*)(
					void* self,
					const Vector3Value* position,
					std::int32_t eye,
					Vector3Value* ret,
					_internal::unity_structs::il2cppMethodInfo* method
				);

				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

				Vector3Value out{};
				fn(camera, &position, static_cast<std::int32_t>(eye), &out, method.value);

				return { Il2CppStatus::OK, out };
			}

			inline Result<Vector3Value> ScreenToWorldPoint(
				void* camera,
				const Vector3Value& position,
				MonoOrStereoscopicEye eye = MonoOrStereoscopicEye::Mono
			) {
				ThreadScope scope;

				if (!camera)
					return { Il2CppStatus::InvalidArgs, {} };

				auto method = _detail::resolve_camera_method("ScreenToWorldPoint_Injected", 3);
				if (!method) return { method.status, {} };
				if (!method.value->m_pMethodPointer)
					return { Il2CppStatus::MethodPointerNull, {} };

				using Fn = void(__fastcall*)(
					void* self,
					const Vector3Value* position,
					std::int32_t eye,
					Vector3Value* ret,
					_internal::unity_structs::il2cppMethodInfo* method
					);

				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

				Vector3Value out{};
				fn(camera, &position, static_cast<std::int32_t>(eye), &out, method.value);

				return { Il2CppStatus::OK, out };
			}

			inline Result<RayValue> ScreenPointToRay(
				void* camera,
				const Vector2Value& position,
				MonoOrStereoscopicEye eye = MonoOrStereoscopicEye::Mono
			) {
				ThreadScope scope;

				if (!camera)
					return { Il2CppStatus::InvalidArgs, {} };

				auto method = _detail::resolve_camera_method("ScreenPointToRay_Injected", 3);
				if (!method) return { method.status, {} };
				if (!method.value->m_pMethodPointer)
					return { Il2CppStatus::MethodPointerNull, {} };

				using Fn = void(__fastcall*)(
					void* self,
					const Vector2Value* position,
					std::int32_t eye,
					RayValue* ret,
					_internal::unity_structs::il2cppMethodInfo* method
					);

				auto fn = reinterpret_cast<Fn>(method.value->m_pMethodPointer);

				RayValue out{};
				fn(camera, &position, static_cast<std::int32_t>(eye), &out, method.value);

				return { Il2CppStatus::OK, out };
			}
		}

	} // namespace UnityEngine

} // namespace il2cpp

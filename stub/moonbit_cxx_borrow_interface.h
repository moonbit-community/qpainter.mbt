#pragma once

#if __cplusplus < 202302L
#if defined(__GNUC__)
#error "use GCC14 or higher version"

#elif defined(_MSC_VER)
#error "use MSVC19.43 or higher version"

#elif defined(__CLANG__)
#error "use clang18 or higher version"
#error "ponder::di not support clang."
#endif

// TODO add C++ language feature testing
// https://github.com/llvm/llvm-project/issues/137099

// https://en.cppreference.com/w/cpp/language/member_functions#Explicit_object_member_functions
// gcc14 clang18 MSVC19.43
#endif

#include <concepts>
#include <type_traits>
#include <compare>

extern "C" {
#include <moonbit.h> // moonbit.h now doesn't support C++ FFI
MOONBIT_EXPORT void *moonbit_malloc_array(enum moonbit_block_kind kind,
                                          int elem_size_shift, int32_t len);
}

#undef DeriveNewtypeFrom
#undef DeriveContainerAttribute
#define DeriveNewtype(_DeriveNewtype_Self, _DeriveNewtype_Repr)                \
  using Repr = _DeriveNewtype_Repr;                                            \
  using Self = _DeriveNewtype_Self;                                            \
  Repr repr;                                                                   \
  constexpr static Self from(Repr r) noexcept { return Self{.repr = r}; }

#define DeriveContainerAttribute(_DeriveContainer_value_type)                  \
  using value_type = _DeriveContainer_value_type;                              \
  using size_type = Int;                                                       \
  using difference_type = Int;                                                 \
  using pointer = value_type *;                                                \
  using iterator = pointer;                                                    \
  using reference = value_type &;                                              \
  using const_pointer = value_type const *;                                    \
  using const_reference = value_type const &;                                  \
  using const_iterator = const_pointer;

namespace concepts {
using ::std::derived_from;
using ::std::same_as;

template <typename B, typename D>
concept is_base_of = derived_from<D, B>;

template <typename T>
concept aggregate = ::std::is_aggregate_v<T>;

template <typename T>
concept trivially_assignable = ::std::is_trivially_assignable_v<T, T>;

} // namespace concepts

namespace moonbit {
namespace ast_match {
struct option_i32 {};
struct option_i64 {};
struct option_ref {};
template <typename _> struct moonbit_meta : std::false_type {};
template <typename _> struct integer : std::false_type {};
template <typename _> struct floating_point : std::false_type {};
template <typename _> struct scalar_misc : std::false_type {};
} // namespace ast_match

// https://docs.moonbitlang.com/en/latest/language/ffi.html#types
namespace basic_types {
template <typename T> struct Base;
struct Bool;
struct Int16;
struct UInt16;
struct Int;
struct UInt;
struct Int64;
struct UInt64;
struct Double;
struct Float;
struct Char;
struct Byte;
struct Unit;
struct String;
template <typename T> struct Ref;
template <typename T> struct Extern;
} // namespace basic_types

namespace abi {
using ::concepts::is_base_of;
using ::concepts::same_as;

template <typename T>
concept c = ::concepts::aggregate<T> && ::concepts::trivially_assignable<T>;
// ABI References
// [MSVC C++ x64
// ABI](https://learn.microsoft.com/en-us/cpp/build/x64-software-conventions?view=msvc-170)
// [Itanium C++ ABI](https://itanium-cxx-abi.github.io/cxx-abi/abi.html)
template <typename T>
concept cxx = !c<T>;
constexpr ::std::size_t pointer_size = sizeof(void *);

template <typename T>
concept base_interface = requires(T t) {
  typename T::Repr;
  typename T::Self;
  same_as<T, typename T::Self>;
  { t.repr } -> same_as<typename T::Repr &>;
  { t.increment_strong_count() } -> same_as<void>;
  { t.decrement_strong_count() } -> same_as<void>;
  { t.template to_integral<int>() } -> same_as<int>;
  { t.template to_floating_point<float>() } -> same_as<float>;
  { t.to_int_hash_seed() } -> same_as<int32_t>;
};

using basic_types::Base;
template <typename T>
concept moonbit = c<T> && sizeof(T) <= pointer_size && is_base_of<Base<T>, T>;
} // namespace abi

namespace compound_types {
template <abi::moonbit T> struct FixedArray;
template <abi::moonbit T> struct Array;
template <abi::moonbit R, abi::moonbit... Args> struct Closure;

template <abi::moonbit T, typename Kind> struct Option;

} // namespace compound_types

namespace basic_concepts {
template <typename T>
concept integer = ast_match::integer<T>::value;

template <typename T>
concept floating_point = ast_match::floating_point<T>::value;

template <typename T>
concept reference =
    sizeof(T) == abi::pointer_size && ast_match::moonbit_meta<T>::value &&
    requires(T t) { ::std::is_pointer_v<typename T::Repr>; };

} // namespace basic_concepts

namespace compound_concepts {
namespace basic = basic_concepts;
template <typename T>
concept arithmetic = basic::integer<T> || basic::floating_point<T>;

template <typename T>
concept scalar = arithmetic<T> || ast_match::scalar_misc<T>::value;
} // namespace compound_concepts

namespace concepts {
using namespace basic_concepts;
using namespace compound_concepts;
} // namespace concepts

namespace persistent_types {
template <abi::moonbit T>
  requires(concepts::reference<T>)
struct Rc;
}

namespace types {
using namespace basic_types;
using namespace compound_types;
using namespace persistent_types;
} // namespace types

} // namespace moonbit
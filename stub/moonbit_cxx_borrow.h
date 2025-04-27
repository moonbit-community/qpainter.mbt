#pragma once

#include "moonbit_cxx_borrow_interface.h"

namespace moonbit {

namespace ast_match {
using namespace types;

template <> struct moonbit_meta<String> : std::true_type {};
template <typename T> struct moonbit_meta<FixedArray<T>> : std::true_type {};
template <typename T> struct moonbit_meta<Array<T>> : std::true_type {};
template <typename T> struct moonbit_meta<Ref<T>> : std::true_type {};

template <typename R, typename... Args>
struct moonbit_meta<Closure<R, Args...>> : std::true_type {};
template <typename T>
struct moonbit_meta<::moonbit::compound_types::Option<T, option_ref>>
    : std::true_type {};

template <> struct integer<Int> : std::true_type {};
template <> struct integer<UInt> : std::true_type {};
template <> struct integer<Int64> : std::true_type {};
template <> struct integer<UInt64> : std::true_type {};
template <> struct integer<Byte> : std::true_type {};
template <typename T>
struct integer<compound_types::Option<T, option_i32>> : std::true_type {};
template <typename T>
struct integer<compound_types::Option<T, option_i64>> : std::true_type {};

template <> struct floating_point<Float> : std::true_type {};
template <> struct floating_point<Double> : std::true_type {};

template <> struct scalar_misc<Bool> : std::true_type {};
template <> struct scalar_misc<Char> : std::true_type {};
template <> struct scalar_misc<Unit> : std::true_type {};
template <typename T> struct scalar_misc<Extern<T>> : std::true_type {};

using ::std::conditional_t;

template <typename T>
using option_kind_t = conditional_t<
    integer<T>::value,
    conditional_t<
        sizeof(T) < (abi::pointer_size >> 1), option_i32,
        conditional_t<sizeof(T) < (abi::pointer_size), option_i64, option_ref>>,
    option_ref>;

template <typename T>
using option_repr_t =
    conditional_t<integer<T>::value,
                  conditional_t<sizeof(T) < (abi::pointer_size >> 1), Int,
                                conditional_t<sizeof(T) < (abi::pointer_size),
                                              Int64, Ref<T>>>,
                  Ref<T>>;

} // namespace ast_match

} // namespace moonbit

// basic types definition

namespace moonbit::basic_types {
template <typename Self> struct Base {
  void increment_strong_count(this Self self) noexcept {
    if constexpr (concepts::reference<Self>) {
      moonbit_incref(self.repr);
    }
  }
  void decrement_strong_count(this Self self) noexcept {
    if constexpr (concepts::reference<Self>) {
      moonbit_decref(self.repr);
    }
  }
  template <::std::integral T>
  constexpr T to_integral(this Self self) noexcept {
    if constexpr (concepts::arithmetic<Self>) {
      return static_cast<T>(self.repr);
    } else {
      static_assert(false, "This type not support to_integral");
    }
  }

  template <::std::integral T>
  constexpr T to_hash_seed(this Self self) noexcept {
    return static_cast<T>(self.repr);
  }
  constexpr int32_t to_int_hash_seed(this Self self) noexcept {
    return self.template to_hash_seed<int32_t>(self);
  }

  template <::std::floating_point T>
  constexpr T to_floating_point(this Self self) noexcept {
    if constexpr (concepts::arithmetic<Self>) {
      return static_cast<T>(self.repr);
    } else {
      static_assert(false, "This type not support to_floating_point");
    }
  }
#undef DeriveMoonbitBasicType
#define DeriveMoonbitBasicType(_DeriveMoonbitBasicType_Name,                   \
                               _DeriveMoonbitBasicType_Repr)                   \
  struct _DeriveMoonbitBasicType_Name : Base<_DeriveMoonbitBasicType_Name> {   \
    DeriveNewtype(_DeriveMoonbitBasicType_Name, _DeriveMoonbitBasicType_Repr); \
  };
};

struct Bool : Base<Bool> {
  DeriveNewtype(Bool, int32_t);
  explicit operator bool() const noexcept { return repr; }
};

DeriveMoonbitBasicType(Int, int32_t);
DeriveMoonbitBasicType(UInt, uint32_t);
DeriveMoonbitBasicType(Int16, int16_t);
DeriveMoonbitBasicType(UInt16, uint16_t);
DeriveMoonbitBasicType(Int64, int64_t);
DeriveMoonbitBasicType(UInt64, uint64_t);
DeriveMoonbitBasicType(Byte, uint8_t);
// Unicode Code Point
DeriveMoonbitBasicType(Char, int32_t);
DeriveMoonbitBasicType(Float, float);
DeriveMoonbitBasicType(Double, double);
DeriveMoonbitBasicType(Unit, int32_t);
// DeriveMoonbitBasicType(String, uint16_t const *);

constexpr Unit Trivial{};
constexpr Bool True = Bool::from(1);
constexpr Bool False = Bool::from(0);

struct String : Base<String> {
  DeriveNewtype(String, uint16_t const *);
  DeriveContainerAttribute(uint16_t);
  const_pointer begin(this String self) noexcept { return self.repr; }
  const_pointer end(this String self) noexcept {
    return self.repr + self.length().repr;
  }
  Int length(this String self) noexcept {
    return Int::from(Moonbit_array_length(self.repr));
  }
  int16_t code_unit(this String self, Int index) noexcept {
    return self.repr[index.repr];
  }
};

template <typename T> struct Extern : Base<Extern<T>> {
  DeriveNewtype(Extern<T>, T *);
  constexpr T *operator->(this Self self) noexcept { return self.repr; }
  constexpr T &operator*(this Self self) noexcept { return *self.repr; }
};
template <typename T> struct Ref : Base<Ref<T>> {
  using Self = Ref<T>;
  using Repr = T *;
  Repr repr;
  constexpr T *operator->(this Self self) noexcept { return self.repr; }
  constexpr T &operator*(this Self self) noexcept { return *self.repr; }

  static void finalizer(void *obj) {
    auto ptr = static_cast<T *>(obj);
    ptr->~T();
  }

  template <typename... Args>
    requires(::std::constructible_from<T, Args...>)
  static Ref<T> from(Args... args) noexcept {
    void *obj = moonbit_make_external_object(Ref<T>::finalizer, sizeof(T));
    return {.repr = new (obj) T{(args)...}};
  }
};

} // namespace moonbit::basic_types

namespace moonbit::compound_types {
using moonbit::basic_types::Base;
using moonbit::basic_types::Int;
template <abi::moonbit T> struct FixedArray : Base<FixedArray<T>> {
  using Self = FixedArray<T>;
  using Repr = T *;
  DeriveContainerAttribute(T);
  Repr repr;
  Int length(this Self self) noexcept {
    return Int::from(Moonbit_array_length(self.repr));
  }
  pointer begin(this Self self) noexcept { return self.repr; }
  pointer end(this Self self) noexcept {
    return self.repr + self.length().repr;
  }
  T &operator[](this Self self, Int index) noexcept {
    return self.repr[index.repr];
  }
};

template <abi::moonbit T> struct Array : Base<Array<T>> {
  using Self = Array<T>;
  struct Underlying {
    Int len;
    T *data;
  };
  using Repr = Underlying *;
  DeriveContainerAttribute(T);
  Repr repr;
  Int length(this Self self) noexcept { return self.repr->len; }
  pointer begin(this Self self) noexcept { return self.repr; }
  pointer end(this Self self) noexcept {
    return self.repr->data + self.repr->len;
  }
  T &operator[](this Self self, Int index) noexcept {
    return self.repr->data[index.repr];
  }
};

template <abi::moonbit R, abi::moonbit... Args>
struct Closure : Base<Closure<R, Args...>> {
  using Self = Closure<R, Args...>;
  //
  // Closure Underlying Type payload memory layout
  //
  // {
  //
  // code : function pointer
  //
  // freevar1 : unknown
  //
  // freevar2 : unknown
  //
  // freevar3 : unknown
  //
  // }
  struct Underlying {
    using Self = Underlying;
    using Context = Underlying *;
    using Code = R (*)(Self *self, Args... args) noexcept;
    Code code;
  };
  using Code = Underlying::Code;
  using Context = Underlying::Context;
  using Repr = Underlying *;
  Repr repr;

  R operator()(this Self self,
               Args... args) noexcept { // do not use & or && here
    self.increment_strong_count();
    (..., args.increment_strong_count());

    Code code = self.repr->code;
    Context context = self.repr;
    return code(context, args...);
  }
};
template <abi::moonbit T, typename Kind = ast_match::option_kind_t<T>>
struct Option : Base<Option<T, Kind>> {
  using Repr = ast_match::option_repr_t<T>;
  Repr repr;
  bool is_none() noexcept {
    using namespace ::concepts;
    if constexpr (same_as<Kind, ast_match::option_i32>) {
      return -1 == repr.repr;
    } else if constexpr (same_as<Kind, ast_match::option_i64>) {
      return 4294967296ll == repr.repr;
    } else {
      return 0 == Moonbit_object_tag(repr.repr);
    }
  }
  bool is_some() noexcept { return !is_none(); }
};

} // namespace moonbit::compound_types

namespace moonbit::persistent_types {
// Rc is similar ::std::shared_ptr, Rc not in moonbit abi
// This intende to store moonbit reference value in C++ side.
template <abi::moonbit T>
  requires(concepts::reference<T>)
struct Rc {
  using Self = Rc<T>;
  using Repr = T;
  T repr;

  explicit Rc(T r) noexcept : repr(r) { this->repr.increment_strong_count(); }
  Rc(Self const &other) noexcept {
    this->repr = other.repr;
    this->repr.increment_strong_count();
  }
  Self &operator=(Self const &other) noexcept {
    this->repr.decrement_strong_count();
    this->repr = other.repr;
  }
  ~Rc() noexcept { this->repr.decrement_strong_count(); }
};
} // namespace moonbit::persistent_types

namespace moonbit::operators {
using namespace moonbit::concepts;
using namespace moonbit::types;

template <arithmetic A> constexpr A operator+(A x, A y) noexcept {
  return A::from(x.repr + y.repr);
}

template <arithmetic A> constexpr A operator-(A x, A y) noexcept {
  return A::from(x.repr - y.repr);
}
template <arithmetic A> constexpr A operator*(A x, A y) noexcept {
  return A::from(x.repr * y.repr);
}

template <arithmetic A> constexpr A operator/(A x, A y) noexcept {
  return A::from(x.repr / y.repr);
}

template <arithmetic A> constexpr A operator%(A x, A y) noexcept {
  return A::from(x.repr % y.repr);
}

template <arithmetic A>
constexpr std::strong_ordering operator<=>(A x, A y) noexcept {
  return x.repr <=> y.repr;
}
template <arithmetic A> constexpr bool operator<(A x, A y) noexcept {
  return x.repr < y.repr;
}

template <integer A> constexpr A operator<<(A x, int b) noexcept {
  return A{x.repr << b};
}
template <integer A> constexpr A operator>>(A x, int b) noexcept {
  return A{x.repr >> b};
}

template <arithmetic A> constexpr Bool reinterpret_as_bool(A x) noexcept {
  return Bool::from(x.repr);
}
} // namespace moonbit::operators

namespace moonbit::type_check {
using namespace moonbit::concepts;
using namespace moonbit::types;

static_assert(reference<String>);
static_assert(reference<FixedArray<Int>>);
static_assert(reference<Array<Int>>);

static_assert(abi::moonbit<Int>);
static_assert(abi::moonbit<UInt>);
static_assert(abi::moonbit<String>);
static_assert(abi::moonbit<FixedArray<Int>>);
static_assert(abi::moonbit<FixedArray<FixedArray<Int>>>);
static_assert(abi::moonbit<Closure<Int, Int, Int>>);

enum class MouseEvent {};

static_assert(!reference<Extern<MouseEvent>>);
static_assert(!abi::moonbit<Rc<Ref<MouseEvent>>>);
static_assert(abi::cxx<Rc<Ref<MouseEvent>>>);

} // namespace moonbit::type_check